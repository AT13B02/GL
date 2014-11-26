//=============================================================================
//
// OBJ�N���X [CMeshOBJ.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CMeshOBJ.h"
#include "CVBO.h"
#include "CIndexBuffer.h"
#include <stdio.h>

//*****************************************************************************
// �A�g���r���[�g
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
struct MeshAttribute
{
	u32 idxStart;	// �J�n�C���f�b�N�X
	u32 idxNum;	// �C���f�b�N�X��
	u32 vtxStart;	// �J�n���_�ԍ�
	u32 vtxNum;	// ���_��
	u32 faceNum;	// �v���~�e�B�u��
};

// �f�[�^�w�b�_
struct XOHeader
{
	u32 uVtx;
	u32 uIdx;
	u32 uMat;
	u32 uAtt;
};

//=============================================================================
// �R���X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
CMeshOBJ::CMeshOBJ() :
m_uNumVertex(0),
m_pVtxBuff(NULL),
m_pTexCoordBuff(NULL),
m_pNormalBuff(NULL),
m_uNumIndex(0),
m_pIdxBuff(NULL),
m_uNumSubset(0),
m_pAttribute(NULL),
m_uNumMaterial(0),
m_pMaterial(NULL)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
CMeshOBJ::~CMeshOBJ()
{
}

//=============================================================================
// ��������
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
HRESULT CMeshOBJ::Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial, CMeshOBJ** ppOBJ)
{
	HRESULT hr;

	// ���b�V������
	(*ppOBJ) = new CMeshOBJ();

	// ���b�V����������
	hr = (*ppOBJ)->Create(pFileName, pNumSubset, ppMaterial);

	return hr;
}

//=============================================================================
// �J������
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
void CMeshOBJ::Release(void)
{
	// ���_�J��
	m_pVtxBuff->Release();
	m_pTexCoordBuff->Release();
	m_pNormalBuff->Release();

	// �C���f�b�N�X�J��
	m_pIdxBuff->Release();
	
	// �T�u�Z�b�g�J��
	if(m_pAttribute)
	{
		delete [] m_pAttribute;
	}

	if(m_pMaterial)
	{
		delete [] m_pMaterial;
	}

	// ���ȉ��
	delete this;
}

//=============================================================================
// �`�揈��
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
void CMeshOBJ::DrawSubset(u32 uIndex)
{
	// ���_�z��L����
	m_pVtxBuff->ValidateArrayValue();
	// �@���z��L����
	m_pNormalBuff->ValidateArrayValue();
	// �e�N�X�`���z��L����
	m_pTexCoordBuff->ValidateArrayValue();

	// �C���f�b�N�X�o�C���h
	m_pIdxBuff->BindBuffer();

	// �`��
	u32 uOffsetIdx = m_pAttribute[uIndex].idxStart * sizeof(u32);
	glDrawElements(GL_TRIANGLE_STRIP, m_pAttribute[uIndex].idxNum, GL_UNSIGNED_INT, (void*)uOffsetIdx);

	// �z�񖳌���
	m_pVtxBuff->InvalidateArrayValue();
	m_pNormalBuff->InvalidateArrayValue();
	m_pTexCoordBuff->InvalidateArrayValue();

	// �C���f�b�N�X�o�C���h����
	m_pIdxBuff->UnbindBuffer();
}

//=============================================================================
// ��������
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
HRESULT CMeshOBJ::Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial)
{
	// ���b�V���t�@�C���ǂݍ���
	FILE *pFile;

	// �t�@�C���I�[�v��
	pFile = fopen(pFileName, "rb");
	if(!pFile)
	{
		return E_FAIL;
	}

	// �w�b�_
	XOHeader xo;
	// �w�b�_�ǂݍ���
	fread(&xo, sizeof(xo), 1, pFile);

	// ���_���R�s�[
	m_uNumVertex = xo.uVtx;

	// ���_�f�[�^����
	// ���W
	CVBO::CreateBuffer(m_uNumVertex * sizeof(VECTOR3), 3, GL_VERTEX_ARRAY, &m_pVtxBuff);
	// �e�N�X�`�����W
	CVBO::CreateBuffer(m_uNumVertex * sizeof(VECTOR2), 2, GL_TEXTURE_COORD_ARRAY, &m_pTexCoordBuff);
	// �@��
	CVBO::CreateBuffer(m_uNumVertex * sizeof(VECTOR3), 3, GL_NORMAL_ARRAY, &m_pNormalBuff);

	// ���_�o�b�t�@�A�N�Z�X�|�C���^
	VECTOR3 *pVtx = NULL;
	VECTOR2 *pTexCoord = NULL;
	VECTOR3 *pNormal = NULL;

	// ���_���W�A�N�Z�X
	m_pVtxBuff->GetBufferPointer((void**)&pVtx);
	// ���_���W�f�[�^�ǂݍ���
	fread(pVtx, m_uNumVertex * sizeof(VECTOR3), 1, pFile);
	// �@���A�N�Z�X
	m_pNormalBuff->GetBufferPointer((void**)&pNormal);
	// �@���f�[�^�ǂݍ���
	fread(pNormal, m_uNumVertex * sizeof(VECTOR3), 1, pFile);
	// �e�N�X�`�����W�A�N�Z�X
	m_pTexCoordBuff->GetBufferPointer((void**)&pTexCoord);
	// �e�N�X�`�����W�f�[�^�ǂݍ���
	fread(pTexCoord, m_uNumVertex * sizeof(VECTOR2), 1, pFile);

	// �C���f�b�N�X�f�[�^����
	m_uNumIndex = xo.uIdx;
	CIndexBuffer::CreateBuffer(m_uNumIndex * sizeof(u32), &m_pIdxBuff);
	// �C���f�b�N�X�f�[�^�ǂݍ���
	u32 *pIdx = NULL;
	m_pIdxBuff->GetBufferPointer((void**)&pIdx);
	fread(pIdx, m_uNumIndex * sizeof(u32), 1, pFile);

	// VRAM��Ƀo�b�t�@����
	m_pIdxBuff->GenBuffer();
	
	m_uNumMaterial = xo.uMat;
	// �}�e���A������
	m_pMaterial = new MeshMaterial[m_uNumMaterial];
	// �}�e���A���ǂݍ���
	fread(m_pMaterial, m_uNumMaterial * sizeof(MeshMaterial), 1, pFile);
	// �}�e���A���ݒ�
	(*ppMaterial) = m_pMaterial;
	
	m_uNumSubset = xo.uAtt;
	// �T�u�Z�b�g���R�s�[
	*pNumSubset = m_uNumSubset;
	// �T�u�Z�b�g�������A�g���r���[�g����
	m_pAttribute = new MeshAttribute[m_uNumSubset];
	// �t�@�C���ǂݍ���
	fread(m_pAttribute, m_uNumSubset * sizeof(MeshAttribute), 1, pFile);
	
	// �t�@�C���N���[�Y
	fclose(pFile);

	return S_OK;
}

// EOF