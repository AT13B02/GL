// Xファイルパース
#include "XfileParser.h"
#include "Debug.h"

// ファイルパース
void XFileParser::ParseFile(char* pFileName)
{
	char aCommand[256];
	std::ifstream ifs(pFileName);

	// ファイル名コピー
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
		// コマンド
		ifs >> aCommand;
		// 終端に達した
		if(!ifs)
		{
			bIsLoop = false;
			continue;
		}

		// 頂点座標
		if(0 == strncmp(aCommand, "Mesh", sizeof(aCommand)))
		{
			// 行末まで読み捨て
			ifs.ignore(1000, '\n');
			ParsePosition(ifs);
		}
		// 法線
		else if(0 == strncmp(aCommand, "MeshNormals", sizeof(aCommand)))
		{
			// 行末まで読み捨て
			ifs.ignore(1000, '\n');
			ParseNormal(ifs);
		}
		// テクスチャ座標
		else if(0 == strncmp(aCommand, "MeshTextureCoords", sizeof(aCommand)))
		{
			// 行末まで読み捨て
			ifs.ignore(1000, '\n');
			ParseTexCoord(ifs);
		}
		// マテリアル読み込み
		else if(0 == strncmp(aCommand, "MeshMaterialList", sizeof(aCommand)))
		{
			// 行末まで読み捨て
			ifs.ignore(1000, '\n');
			ParseMaterial(ifs);
		}

		// 行末まで読み捨て
		ifs.ignore(1000, '\n');
	}

	// 面データ生成
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

	// アトリビュート設定
	for(size_t i = 0; i < outAttribute.GetNumData(); i++)
	{
		outAttribute[i].vtxStart = 0;
		outAttribute[i].vtxNum = outPosition.GetNumData();
	}

	// 頂点・インデックスデータ生成
	CreateVertexAndIndex();
}

// 独自フォーマットで出力(OpenGL)
void XFileParser::WriteBinDataGL()
{
	DataHeader dh;
	
	// データヘッダ設定
	// 頂点数
	dh.uVtx = outPosition.GetNumData();
	// インデックス数
	dh.uIdx = index.GetNumData();
	// マテリアル数
	dh.uMat = material.GetLength();
	// アトリビュート数
	dh.uAtt = outAttribute.GetNumData();

	// インデックススワップ
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
			// 三角形を構成する頂点の最初と最後を交換
			// 頂点0の0
			nSwap0 = index[idx];
			index[idx] = index[idx + 3];
			index[idx + 3] = nSwap0;

			// 頂点0の1
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

	// ファイル処理
	FILE* pFile = nullptr;

	// ファイル書き出し
	strFileName += "o";
	fopen_s(&pFile, strFileName.GetStr(), "wb");

	// ヘッダ書き出し
	fwrite(&dh, sizeof(dh), 1, pFile);

	// 頂点データ
	fwrite(outPosition.GetData(), sizeof(Vector3), outPosition.GetNumData(), pFile);
	// 法線データ
	fwrite(outNormal.GetData(), sizeof(Vector3), outNormal.GetNumData(), pFile);
	// テクスチャデータ
	fwrite(outTexcoord.GetData(), sizeof(Vector2), outTexcoord.GetNumData(), pFile);
	// インデックスデータ
	fwrite(index.GetData(), sizeof(unsigned), index.GetNumData(), pFile);
	// マテリアルデータ
	for(int nMat = 0; nMat < material.GetLength(); nMat++)
	{
		fwrite(material.GetPtr(nMat), sizeof(TexMaterial), 1, pFile);
	}
	// アトリビュートデータ
	fwrite(outAttribute.GetData(), sizeof(MeshAttribute), outAttribute.GetNumData(), pFile);

	fclose(pFile);

	printf("変換 : %s\n", strFileName.GetStr());
}

// 頂点読み込み
void XFileParser::ParsePosition(std::ifstream &ifs)
{
	// 頂点座標数読み込み
	int nNumPos;
	ifs >> nNumPos;
	// 行末まで読み捨て
	ifs.ignore(1000, '\n');

	char aDelim[16];

	// 配列確保
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

		// 座標に登録
		position[nPos] = bufPos;

		ifs >> aDelim;
		// 全部読み込んだので終了
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// 行末まで読み捨て
		ifs.ignore(1000, '\n');

		nPos++;
	}

	// 頂点面設定
	int nNumPosFace = 0;
	ifs >> nNumPosFace;
	ifs.ignore(1000, '\n');

	PosNorIndex.Allocate(nNumPosFace);
	bLoopFlag = true;
	nPos = 0;
	int nNumVtx = 3;
	while(bLoopFlag)
	{
		// 面を構成する頂点数
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
		// 全部読み込んだので終了
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// 行末まで読み捨て
		ifs.ignore(1000, '\n');

		nPos++;
	}
}

// 法線読み込み
void XFileParser::ParseNormal(std::ifstream &ifs)
{
	int nNumNormal = 0;
	char aDelim[16];
	// 法線総数
	ifs >> nNumNormal;

	// 配列確保
	normal.Allocate(nNumNormal);
	// 行末まで読み捨て
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

		// 法線に登録
		normal[nNor] = bufNor;

		ifs >> aDelim;
		// 全部読み込んだので終了
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// 行末まで読み捨て
		ifs.ignore(1000, '\n');

		nNor++;
	}

	// 法線面設定
	int nNumNorFace = 0;
	ifs >> nNumNorFace;
	ifs.ignore(1000, '\n');

	bLoopFlag = true;
	nNor = 0;
	int nNumNor = 3;
	while(bLoopFlag)
	{
		// 面を構成する頂点数
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
		// 全部読み込んだので終了
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// 行末まで読み捨て
		ifs.ignore(1000, '\n');

		nNor++;
	}
}

// テクスチャ座標読み込み
void XFileParser::ParseTexCoord(std::ifstream &ifs)
{
	int nNumTex = 0;
	// テクスチャ総数
	ifs >> nNumTex;

	// 配列確保
	texcoord.Allocate(nNumTex);
	// 行末まで読み捨て
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

		// テクスチャ座標に登録
		texcoord[nTex] = bufTex;

		// 全部読み込んだので終了
		if(';' == ifs.peek())
		{
			bLoopFlag = false;
		}
		// 行末まで読み捨て
		ifs.ignore(1000, '\n');

		nTex++;
	}
}

// マテリアル読み込み
void XFileParser::ParseMaterial(std::ifstream &ifs)
{
	int nNumMaterial = 1;
	char aDelim[16];
	// マテリアル総数
	ifs >> nNumMaterial;
	ifs.ignore(1000, '\n');

	// 面の数はすでに読み込んだ
	ifs.ignore(1000, '\n');

	int nMat = 0;
	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		ifs >> PosNorIndex[nMat].idxMat;

		ifs >> aDelim;
		// 全部読み込んだので終了
		if(';' == aDelim[0])
		{
			bLoopFlag = false;
		}
		// 行末まで読み捨て
		ifs.ignore(1000, '\n');

		nMat++;
	}

	char aCommand[32];

	// マテリアル配列
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

		// アンビエントはないので0を入れる
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

			// 一文字ずつ読む
			int idx = 0;
			char c;
			ifs >> c;
			while(c != ';')
			{
				if(c != '\"')
				{
					material[i].TexFileName[idx] = c;
					// 書き込んだ時だけインデックスを増やす
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
		} // テクスチャ読み込み

		ifs.ignore(1000, '\n');
	}
}

// 面分割処理
// 指定した番号のインデックスから分割処理
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

// 頂点・インデックス生成
void XFileParser::CreateVertexAndIndex()
{
	// マテリアルでソート
	int nNumMat = material.GetLength();
	CGrowableArray<Vtx3Face> *sorted = new CGrowableArray<Vtx3Face>[nNumMat];

	// ソート用配列に振り分け
	for(int s = 0; s < Vtx3FaceIndex.GetLength(); s++)
	{
		Vtx3Face *pFace = Vtx3FaceIndex.GetPtr(s);

		sorted[pFace->mat].Add(*pFace);
	}

	// メッシュアトリビュート生成
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

	// 頂点・インデックス作成
	Vertex buf;
	int nIndex = 0;
	for(int iMat = 0; iMat < nNumMat; iMat++)
	{
		// 開始インデックス数
		outAttribute[iMat].idxStart = index.GetNumData();

		Vtx3Face *pV = &(sorted[iMat].GetIdDat(0));

		if(sorted[iMat].GetNumData() >= 2)
		{
			// ストリップで作る
			// 最初の三角
			for(int iVtx = 0; iVtx < 3; iVtx++)
			{
				// 頂点・インデックス追加
				AddVertexAndIndex(*pV, iVtx, &buf);
			}
			// 三角形の最後の重複インデックス
			AddVertexAndIndex(*pV, 2, &buf);
			for(int iFace = 1; iFace < (int)sorted[iMat].GetNumData() - 1; iFace++)
			{
				pV = &(sorted[iMat].GetIdDat(iFace));

				// 三角形の最初の重複インデックス
				AddVertexAndIndex(*pV, 0, &buf);
				for(int iVtx = 0; iVtx < 3; iVtx++)
				{
					// 頂点・インデックス追加
					AddVertexAndIndex(*pV, iVtx, &buf);
				}
				AddVertexAndIndex(*pV, 2, &buf);
			}
			pV = &(sorted[iMat].GetIdDat(sorted[iMat].GetNumData() - 1));
			// 三角形の最後の重複インデックス
			AddVertexAndIndex(*pV, 0, &buf);
		}
		// 最後の三角
		for(int iVtx = 0; iVtx < 3; iVtx++)
		{
			// 頂点・インデックス追加
			AddVertexAndIndex(*pV, iVtx, &buf);
		}

		// インデックス数
		outAttribute[iMat].idxNum = index.GetNumData() - outAttribute[iMat].idxStart;
		// プリミティブ数設定
		outAttribute[iMat].faceNum = index.GetNumData() - 2;
	}

	delete[] sorted;
}

// 頂点・インデックス追加
void XFileParser::AddVertexAndIndex(Vtx3Face& faceInfo, const int faceIndex, Vertex* pVtx)
{
	pVtx->pos = position[faceInfo.postex[faceIndex]];
	pVtx->nor = normal[faceInfo.nor[faceIndex]];
	pVtx->tex = texcoord[faceInfo.postex[faceIndex]];	// 頂点座標と対応してる
	// 頂点登録
	DWORD EntriedIndex = AddVertex((UINT)faceInfo.postex[faceIndex] + 1, pVtx);

	// インデックス追加
	index.Add(EntriedIndex);
#ifdef _DEBUG
	printf("PT N M I: %d %d %d %d\n", faceInfo.postex[faceIndex], faceInfo.nor[faceIndex], faceInfo.mat, EntriedIndex);
#endif
}

// 重複頂点だった場合、ハッシュテーブルに追加
DWORD XFileParser::AddVertex(UINT uHash, XFileParser::Vertex *pVtx)
{
	// 現在登録する頂点が存在していない場合、新しいキャッシュエントリーを作成する
	// その後、インデックスリストに頂点のインデックスを保存
	DWORD uIndex = 0;
	// リスト内に既に登録された頂点が存在しているフラグ
	bool bFoundFlag = false;

	// 頂点リスト内を毎回調べていると非常に遅いので、
	// オブジェファイル内に記述された頂点座標のインデックスを基に
	// ハッシュテーブルに頂点インデックスを保存する
	if((UINT)VertexCache.GetNumData() > uHash)
	{
		// ハッシュテーブルの先頭取得
		CacheEntry* pEntry = VertexCache.GetIdDat(uHash);

		// 終端まで探索
		while(pEntry != NULL)
		{
			Vertex TempVtx;
			TempVtx.pos = *(outPosition.GetData() + pEntry->uIndex);
			TempVtx.tex = *(outTexcoord.GetData() + pEntry->uIndex);
			TempVtx.nor = *(outNormal.GetData() + pEntry->uIndex);

			// すでに同じ頂点がリスト内に登録されていた場合、
			// 同じ場所のインデックスを参照させる
			if(memcmp(&TempVtx, pVtx, sizeof(Vertex)) == 0)
			{
				bFoundFlag = true;
				uIndex = pEntry->uIndex;
				break;
			}

			// 次のキャッシュを探索
			pEntry = pEntry->pNext;
		}
	}

	// リスト内に頂点が存在していなかったとき、新しいハッシュエントリー作成
	if(!bFoundFlag)
	{
		// 新しい頂点インデックス
		uIndex = outPosition.GetNumData();
		// 頂点座標
		outPosition.Add(pVtx->pos);
		// テクスチャ座標
		outTexcoord.Add(pVtx->tex);
		// 法線
		outNormal.Add(pVtx->nor);

		// ハッシュテーブルに頂点インデックスを追加
		CacheEntry* pNewEntry = new CacheEntry;
		if(pNewEntry == NULL)
		{
			// 符号なし4バイト最大数を返す
			return (DWORD)-1;
		}

		pNewEntry->uIndex = uIndex;
		pNewEntry->pNext = NULL;

		// キャッシュを必要な長さまで増やす(いきなり1000とか来たら1000まで増える)
		while((UINT)VertexCache.GetNumData() <= uHash)
		{
			VertexCache.Add(NULL);
		}

		// リストの最後尾にキャッシュエントリーを追加
		CacheEntry* pCurEntry = VertexCache.GetIdDat(uHash);
		// 指定されたキャッシュがヌル
		if(pCurEntry == NULL)
		{
			// テーブルに追加
			VertexCache.SetAt((int)uHash, pNewEntry);
		}
		else
		{
			// 最後尾を探索
			while(pCurEntry->pNext != NULL)
			{
				pCurEntry = pCurEntry->pNext;
			}
			// 最後尾に追加
			pCurEntry->pNext = pNewEntry;
		}
	}

	return uIndex;
}

// EOF