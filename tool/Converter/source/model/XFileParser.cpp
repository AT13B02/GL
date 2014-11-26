// X�t�@�C���p�[�X
#include "XfileParser.h"
#include "Debug.h"

// �t�@�C���p�[�X
void XFileParser::ParseFile(char* pFileName)
{
	char aCommand[256];
	std::ifstream ifs(pFileName);

	// �t�@�C�����R�s�[
	strFileName = pFileName;

	if(!ifs.is_open())
	{
#ifdef _DEBUG
		_asm int 3;
#else
		return;
#endif
	}

	bool bIsLoop = true;
	while(bIsLoop)
	{
		// �R�}���h
		ifs >> aCommand;
		// �I�[�ɒB����
		if(!ifs)
		{
			bIsLoop = false;
			continue;
		}

		// ���_���W
		if(0 == strncmp(aCommand, "Mesh", sizeof(aCommand)))
		{
			// �s���܂œǂݎ̂�
			ifs.ignore(1000, '\n');
			ParsePosition(ifs);
		}
		// �@��
		else if(0 == strncmp(aCommand, "MeshNormals", sizeof(aCommand)))
		{
			// �s���܂œǂݎ̂�
			ifs.ignore(1000, '\n');
			ParseNormal(ifs);
		}
		// �e�N�X�`�����W
		else if(0 == strncmp(aCommand, "MeshTextureCoords", sizeof(aCommand)))
		{
			// �s���܂œǂݎ̂�
			ifs.ignore(1000, '\n');
			ParseTexCoord(ifs);
		}
		// �}�e���A���ǂݍ���
		else if(0 == strncmp(aCommand, "MeshMaterialList", sizeof(aCommand)))
		{
			// �s���܂œǂݎ̂�
			ifs.ignore(1000, '\n');
			ParseMaterial(ifs);
		}

		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');
	}

	// �ʃf�[�^����
	int nMaxFace = PosNorIndex.GetLength();
	Vtx3Face buf3Face;
	for(int i = 0; i < nMaxFace; i++)
	{
		VtxFacePosNorMatIndex *pIdx = PosNorIndex.GetPtr(i);
		
#ifdef _DEBUG
		int nMaxIdx = pIdx->idxPos.GetLength();
#endif
		for(int f = 0; f < pIdx->idxPos.GetLength() - 2; f++)
		{
			buf3Face = DivideFace(f, *pIdx);

			Vtx3FaceIndex.Add(buf3Face);
		}
	}

	// �A�g���r���[�g�ݒ�
	for(size_t i = 0; i < outAttribute.GetNumData(); i++)
	{
		outAttribute[i].vtxStart = 0;
		outAttribute[i].vtxNum = outPosition.GetNumData();
	}

	// ���_�E�C���f�b�N�X�f�[�^����
	CreateVertexAndIndex();
}

// �Ǝ��t�H�[�}�b�g�ŏo��(OpenGL)
void XFileParser::WriteBinDataGL()
{
	DataHeader dh;
	
	// �f�[�^�w�b�_�ݒ�
	// ���_��
	dh.uVtx = outPosition.GetNumData();
	// �C���f�b�N�X��
	dh.uIdx = index.GetNumData();
	// �}�e���A����
	dh.uMat = material.GetLength();
	// �A�g���r���[�g��
	dh.uAtt = outAttribute.GetNumData();

	// �C���f�b�N�X�X���b�v
	int nSwap0 = 0;
	int nSwap1 = 0;
	int idx = 0;
	int idxMax = 0;
	for(int iMat = 0; iMat < (int)outAttribute.GetNumData(); iMat++)
	{
		idx = outAttribute[iMat].idxStart + 4;
		idxMax = outAttribute[iMat].idxStart + outAttribute[iMat].idxNum;
		for(; idx < idxMax - 4; idx += 10)
		{
			// �O�p�`���\�����钸�_�̍ŏ��ƍŌ������
			// ���_0��0
			nSwap0 = index[idx];
			index[idx] = index[idx + 3];
			index[idx + 3] = nSwap0;

			// ���_0��1
			nSwap1 = index[idx + 1];
			index[idx + 1] = index[idx + 4];
			index[idx + 4] = nSwap1;
		}
		if(0 == (outAttribute[iMat].idxNum % 2))
		{
			int idx = idxMax - 4;
			nSwap0 = index[idx + 1];
			index[idx] = index[idx + 3];
			index[idx + 1] = index[idx + 3];
			index[idx + 3] = nSwap0;
		}
	}

	// �t�@�C������
	FILE* pFile = nullptr;

	// �t�@�C�������o��
	strFileName += "o";
	fopen_s(&pFile, strFileName.GetStr(), "wb");

	// �w�b�_�����o��
	fwrite(&dh, sizeof(dh), 1, pFile);

	// ���_�f�[�^
	fwrite(outPosition.GetData(), sizeof(Vector3), outPosition.GetNumData(), pFile);
	// �@���f�[�^
	fwrite(outNormal.GetData(), sizeof(Vector3), outNormal.GetNumData(), pFile);
	// �e�N�X�`���f�[�^
	fwrite(outTexcoord.GetData(), sizeof(Vector2), outTexcoord.GetNumData(), pFile);
	// �C���f�b�N�X�f�[�^
	fwrite(index.GetData(), sizeof(unsigned), index.GetNumData(), pFile);
	// �}�e���A���f�[�^
	for(int nMat = 0; nMat < material.GetLength(); nMat++)
	{
		fwrite(material.GetPtr(nMat), sizeof(TexMaterial), 1, pFile);
	}
	// �A�g���r���[�g�f�[�^
	fwrite(outAttribute.GetData(), sizeof(MeshAttribute), outAttribute.GetNumData(), pFile);

	fclose(pFile);

	printf("�ϊ� : %s\n", strFileName.GetStr());
}

// ���_�ǂݍ���
void XFileParser::ParsePosition(std::ifstream &ifs)
{
	// ���_���W���ǂݍ���
	int nNumPos;
	ifs >> nNumPos;
	// �s���܂œǂݎ̂�
	ifs.ignore(1000, '\n');

	char aDelim[16];

	// �z��m��
	position.Allocate(nNumPos);

	Vector3 bufPos(0, 0, 0);
	int nPos = 0;
	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		ifs >> bufPos.x;
		ifs.ignore(10, ';');
		ifs >> bufPos.y;
		ifs.ignore(10, ';');
		ifs >> bufPos.z;
		ifs.ignore(10, ';');

		// ���W�ɓo�^
		position[nPos] = bufPos;

		ifs >> aDelim;
		// �S���ǂݍ��񂾂̂ŏI��
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');

		nPos++;
	}

	// ���_�ʐݒ�
	int nNumPosFace = 0;
	ifs >> nNumPosFace;
	ifs.ignore(1000, '\n');

	PosNorIndex.Allocate(nNumPosFace);
	bLoopFlag = true;
	nPos = 0;
	int nNumVtx = 3;
	while(bLoopFlag)
	{
		// �ʂ��\�����钸�_��
		ifs >> nNumVtx;
		PosNorIndex[nPos].idxPos.Allocate(nNumVtx);
		ifs.ignore(10, ';');

		for(int i = 0; i < nNumVtx - 1; i++)
		{
			ifs >> PosNorIndex[nPos].idxPos[i];
			ifs.ignore(10, ',');
		}

		ifs >> PosNorIndex[nPos].idxPos[nNumVtx - 1];
		ifs.ignore(10, ';');

		ifs >> aDelim;
		// �S���ǂݍ��񂾂̂ŏI��
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');

		nPos++;
	}
}

// �@���ǂݍ���
void XFileParser::ParseNormal(std::ifstream &ifs)
{
	int nNumNormal = 0;
	char aDelim[16];
	// �@������
	ifs >> nNumNormal;

	// �z��m��
	normal.Allocate(nNumNormal);
	// �s���܂œǂݎ̂�
	ifs.ignore(1000, '\n');

	Vector3 bufNor(0, 0, 0);
	int nNor = 0;
	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		ifs >> bufNor.x;
		ifs.ignore(10, ';');
		ifs >> bufNor.y;
		ifs.ignore(10, ';');
		ifs >> bufNor.z;
		ifs.ignore(10, ';');

		// �@���ɓo�^
		normal[nNor] = bufNor;

		ifs >> aDelim;
		// �S���ǂݍ��񂾂̂ŏI��
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');

		nNor++;
	}

	// �@���ʐݒ�
	int nNumNorFace = 0;
	ifs >> nNumNorFace;
	ifs.ignore(1000, '\n');

	bLoopFlag = true;
	nNor = 0;
	int nNumNor = 3;
	while(bLoopFlag)
	{
		// �ʂ��\�����钸�_��
		ifs >> nNumNor;
		PosNorIndex[nNor].idxNor.Allocate(nNumNor);
		ifs.ignore(10, ';');

		for(int i = 0; i < nNumNor - 1; i++)
		{
			ifs >> PosNorIndex[nNor].idxNor[i];
			ifs.ignore(10, ',');
		}

		ifs >> PosNorIndex[nNor].idxNor[nNumNor - 1];
		ifs.ignore(10, ';');

		ifs >> aDelim;
		// �S���ǂݍ��񂾂̂ŏI��
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');

		nNor++;
	}
}

// �e�N�X�`�����W�ǂݍ���
void XFileParser::ParseTexCoord(std::ifstream &ifs)
{
	int nNumTex = 0;
	// �e�N�X�`������
	ifs >> nNumTex;

	// �z��m��
	texcoord.Allocate(nNumTex);
	// �s���܂œǂݎ̂�
	ifs.ignore(1000, '\n');

	Vector2 bufTex(0, 0);
	int nTex = 0;
	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		ifs >> bufTex.x;
		ifs.ignore(10, ';');
		ifs >> bufTex.y;
		ifs.ignore(10, ';');

		// �e�N�X�`�����W�ɓo�^
		texcoord[nTex] = bufTex;

		// �S���ǂݍ��񂾂̂ŏI��
		if(';' == ifs.peek())
		{
			bLoopFlag = false;
		}
		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');

		nTex++;
	}
}

// �}�e���A���ǂݍ���
void XFileParser::ParseMaterial(std::ifstream &ifs)
{
	int nNumMaterial = 1;
	char aDelim[16];
	// �}�e���A������
	ifs >> nNumMaterial;
	ifs.ignore(1000, '\n');

	// �ʂ̐��͂��łɓǂݍ���
	ifs.ignore(1000, '\n');

	int nMat = 0;
	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		ifs >> PosNorIndex[nMat].idxMat;

		ifs >> aDelim;
		// �S���ǂݍ��񂾂̂ŏI��
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// �s���܂œǂݎ̂�
		ifs.ignore(1000, '\n');

		nMat++;
	}

	char aCommand[32];

	// �}�e���A���z��
	material.Allocate(nNumMaterial);
	for(int i = 0; i < nNumMaterial; i++)
	{
		ifs >> aCommand;
		if(0 != strncmp(aCommand, "Material", sizeof(aCommand)))
		{
			_Assert(0);
		}

		ifs.ignore(1000, '\n');

		ifs >> material[i].mat.Diffuse.r;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Diffuse.g;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Diffuse.b;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Diffuse.a;

		ifs.ignore(1000, '\n');

		ifs >> material[i].mat.SpecPower;

		ifs.ignore(1000, '\n');

		// �A���r�G���g�͂Ȃ��̂�0������
		material[i].mat.Ambient = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		ifs >> material[i].mat.Specular.r;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Specular.g;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Specular.b;
		ifs.ignore(10, ';');
		material[i].mat.Specular.a = 1.0f;

		ifs.ignore(1000, '\n');

		ifs >> material[i].mat.Emissive.r;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Emissive.g;
		ifs.ignore(10, ';');
		ifs >> material[i].mat.Emissive.b;
		ifs.ignore(10, ';');
		material[i].mat.Emissive.a = 1.0f;
		
		ifs.ignore(1000, '\n');

		memset(material[i].TexFileName, 0, sizeof(material[i].TexFileName));

		ifs >> aCommand;
		if(0 == strncmp(aCommand, "TextureFilename", sizeof(aCommand)))
		{
			ifs.ignore(1000, '\n');

			// �ꕶ�����ǂ�
			int idx = 0;
			char c;
			ifs >> c;
			while(c != ';')
			{
				if(c != '\"')
				{
					material[i].TexFileName[idx] = c;
					// �������񂾎������C���f�b�N�X�𑝂₷
					idx++;
#ifdef _DEBUG
					if(idx >= MAX_PATH){
						_Assert(0);
					}
#endif
				}

				ifs >> c;
			}
			kb::CString temp(material[i].TexFileName);
			int id = temp.SearchTokenIndexL('.') + 1;
			char ext[] = "txo";
			int strId = 0;
			while(id + strId < temp.GetLength())
			{
				temp[id + strId] = ext[strId];
				strId++;
			}
			while(strId < sizeof(ext) - 1)
			{
				temp += &ext[strId];
				strId++;
			}
			for(int str = 0; str < temp.GetLength(); str++)
			{
				material[i].TexFileName[str] = temp[str];
			}

			ifs.ignore(1000, '}');
			ifs.ignore(1000, '\n');
		} // �e�N�X�`���ǂݍ���

		ifs.ignore(1000, '\n');
	}
}

// �ʕ�������
// �w�肵���ԍ��̃C���f�b�N�X���番������
XFileParser::Vtx3Face XFileParser::DivideFace(int nIndex, VtxFacePosNorMatIndex& idx)
{
	Vtx3Face face;

	face.postex[0] = idx.idxPos[0];
	face.nor[0] = idx.idxNor[0];
	for(int i = 1; i < 3; i++)
	{
		face.postex[i] = idx.idxPos[nIndex + i];
		face.nor[i] = idx.idxNor[nIndex + i];
	}

	face.mat = idx.idxMat;

	return face;
}

// ���_�E�C���f�b�N�X����
void XFileParser::CreateVertexAndIndex()
{
	// �}�e���A���Ń\�[�g
	int nNumMat = material.GetLength();
	CGrowableArray<Vtx3Face> *sorted = new CGrowableArray<Vtx3Face>[nNumMat];

	// �\�[�g�p�z��ɐU�蕪��
	for(int s = 0; s < Vtx3FaceIndex.GetLength(); s++)
	{
		Vtx3Face *pFace = Vtx3FaceIndex.GetPtr(s);

		sorted[pFace->mat].Add(*pFace);
	}

	// ���b�V���A�g���r���[�g����
	for(int iAtt = 0; iAtt < nNumMat; iAtt++)
	{
		MeshAttribute att;
		att.idxStart = 0;
		att.idxNum = 0;
		att.vtxStart = 0;
		att.vtxNum = 0;
		att.faceNum = 0;
		outAttribute.Add(att);
	}

	// ���_�E�C���f�b�N�X�쐬
	Vertex buf;
	int nIndex = 0;
	for(int iMat = 0; iMat < nNumMat; iMat++)
	{
		// �J�n�C���f�b�N�X��
		outAttribute[iMat].idxStart = index.GetNumData();

		Vtx3Face *pV = &(sorted[iMat].GetIdDat(0));

		if(sorted[iMat].GetNumData() >= 2)
		{
			// �X�g���b�v�ō��
			// �ŏ��̎O�p
			for(int iVtx = 0; iVtx < 3; iVtx++)
			{
				// ���_�E�C���f�b�N�X�ǉ�
				AddVertexAndIndex(*pV, iVtx, &buf);
			}
			// �O�p�`�̍Ō�̏d���C���f�b�N�X
			AddVertexAndIndex(*pV, 2, &buf);
			for(int iFace = 1; iFace < (int)sorted[iMat].GetNumData() - 1; iFace++)
			{
				pV = &(sorted[iMat].GetIdDat(iFace));

				// �O�p�`�̍ŏ��̏d���C���f�b�N�X
				AddVertexAndIndex(*pV, 0, &buf);
				for(int iVtx = 0; iVtx < 3; iVtx++)
				{
					// ���_�E�C���f�b�N�X�ǉ�
					AddVertexAndIndex(*pV, iVtx, &buf);
				}
				AddVertexAndIndex(*pV, 2, &buf);
			}
			pV = &(sorted[iMat].GetIdDat(sorted[iMat].GetNumData() - 1));
			// �O�p�`�̍Ō�̏d���C���f�b�N�X
			AddVertexAndIndex(*pV, 0, &buf);
		}
		// �Ō�̎O�p
		for(int iVtx = 0; iVtx < 3; iVtx++)
		{
			// ���_�E�C���f�b�N�X�ǉ�
			AddVertexAndIndex(*pV, iVtx, &buf);
		}

		// �C���f�b�N�X��
		outAttribute[iMat].idxNum = index.GetNumData() - outAttribute[iMat].idxStart;
		// �v���~�e�B�u���ݒ�
		outAttribute[iMat].faceNum = index.GetNumData() - 2;
	}

	delete[] sorted;
}

// ���_�E�C���f�b�N�X�ǉ�
void XFileParser::AddVertexAndIndex(Vtx3Face& faceInfo, const int faceIndex, Vertex* pVtx)
{
	pVtx->pos = position[faceInfo.postex[faceIndex]];
	pVtx->nor = normal[faceInfo.nor[faceIndex]];
	pVtx->tex = texcoord[faceInfo.postex[faceIndex]];	// ���_���W�ƑΉ����Ă�
	// ���_�o�^
	DWORD EntriedIndex = AddVertex((UINT)faceInfo.postex[faceIndex] + 1, pVtx);

	// �C���f�b�N�X�ǉ�
	index.Add(EntriedIndex);
#ifdef _DEBUG
	printf("PT N M I: %d %d %d %d\n", faceInfo.postex[faceIndex], faceInfo.nor[faceIndex], faceInfo.mat, EntriedIndex);
#endif
}

// �d�����_�������ꍇ�A�n�b�V���e�[�u���ɒǉ�
DWORD XFileParser::AddVertex(UINT uHash, XFileParser::Vertex *pVtx)
{
	// ���ݓo�^���钸�_�����݂��Ă��Ȃ��ꍇ�A�V�����L���b�V���G���g���[���쐬����
	// ���̌�A�C���f�b�N�X���X�g�ɒ��_�̃C���f�b�N�X��ۑ�
	DWORD uIndex = 0;
	// ���X�g���Ɋ��ɓo�^���ꂽ���_�����݂��Ă���t���O
	bool bFoundFlag = false;

	// ���_���X�g���𖈉񒲂ׂĂ���Ɣ��ɒx���̂ŁA
	// �I�u�W�F�t�@�C�����ɋL�q���ꂽ���_���W�̃C���f�b�N�X�����
	// �n�b�V���e�[�u���ɒ��_�C���f�b�N�X��ۑ�����
	if((UINT)VertexCache.GetNumData() > uHash)
	{
		// �n�b�V���e�[�u���̐擪�擾
		CacheEntry* pEntry = VertexCache.GetIdDat(uHash);

		// �I�[�܂ŒT��
		while(pEntry != NULL)
		{
			Vertex TempVtx;
			TempVtx.pos = *(outPosition.GetData() + pEntry->uIndex);
			TempVtx.tex = *(outTexcoord.GetData() + pEntry->uIndex);
			TempVtx.nor = *(outNormal.GetData() + pEntry->uIndex);

			// ���łɓ������_�����X�g���ɓo�^����Ă����ꍇ�A
			// �����ꏊ�̃C���f�b�N�X���Q�Ƃ�����
			if(memcmp(&TempVtx, pVtx, sizeof(Vertex)) == 0)
			{
				bFoundFlag = true;
				uIndex = pEntry->uIndex;
				break;
			}

			// ���̃L���b�V����T��
			pEntry = pEntry->pNext;
		}
	}

	// ���X�g���ɒ��_�����݂��Ă��Ȃ������Ƃ��A�V�����n�b�V���G���g���[�쐬
	if(!bFoundFlag)
	{
		// �V�������_�C���f�b�N�X
		uIndex = outPosition.GetNumData();
		// ���_���W
		outPosition.Add(pVtx->pos);
		// �e�N�X�`�����W
		outTexcoord.Add(pVtx->tex);
		// �@��
		outNormal.Add(pVtx->nor);

		// �n�b�V���e�[�u���ɒ��_�C���f�b�N�X��ǉ�
		CacheEntry* pNewEntry = new CacheEntry;
		if(pNewEntry == NULL)
		{
			// �����Ȃ�4�o�C�g�ő吔��Ԃ�
			return (DWORD)-1;
		}

		pNewEntry->uIndex = uIndex;
		pNewEntry->pNext = NULL;

		// �L���b�V����K�v�Ȓ����܂ő��₷(�����Ȃ�1000�Ƃ�������1000�܂ő�����)
		while((UINT)VertexCache.GetNumData() <= uHash)
		{
			VertexCache.Add(NULL);
		}

		// ���X�g�̍Ō���ɃL���b�V���G���g���[��ǉ�
		CacheEntry* pCurEntry = VertexCache.GetIdDat(uHash);
		// �w�肳�ꂽ�L���b�V�����k��
		if(pCurEntry == NULL)
		{
			// �e�[�u���ɒǉ�
			VertexCache.SetAt((int)uHash, pNewEntry);
		}
		else
		{
			// �Ō����T��
			while(pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}
			// �Ō���ɒǉ�
			pCurEntry->pNext = pNewEntry;
		}
	}

	return uIndex;
}

// EOF