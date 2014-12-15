//*****************************************************************************
//
// GL���f���N���X
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "gl_model.h"
#include <stdio.h>

// opengl
#include "interface/graphic/device/opengl/opengl.h"

// common
#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CGLModel::CGLModel(CDeviceHolder* device_holder) :
CModel(device_holder)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGLModel::~CGLModel(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CGLModel::Init(void)
{
	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CGLModel::Uninit(void)
{
	SAFE_RELEASE(m_pVtxBuffer);

	SAFE_DELETE_ARRAY(m_pMaterial);
	SAFE_DELETE_ARRAY(m_pMeshAttribute);
}

//=============================================================================
// ���[�h
//=============================================================================
bool CGLModel::Load(const s8* filename)
{
	FILE *pFile = NULL;

	fopen_s(&pFile, filename, "rb");

	if(!pFile)
	{
		return false;
	}

	// �w�b�_�ǂݍ���
	DataHeader dh;
	fread(&dh, sizeof(dh), 1, pFile);

	// ���_����
	m_pVtxBuffer = CVertex3D::Create(device_holder_, dh.uVtx);
	// �C���f�b�N�X����
	m_pVtxBuffer->CreateIndex(dh.uIdx);

	// ���_�ǂݍ���
	CVertex3D::VERTEX_3D *pVtx;
	CVertex3D::VERTEX_3D_INDEX *pIdx;
	m_pVtxBuffer->Lock(&pVtx, &pIdx);
	// ���_���W
	fread(pVtx->_position, sizeof(VECTOR3), dh.uVtx, pFile);
	// �@��
	fread(pVtx->_normal, sizeof(VECTOR3), dh.uVtx, pFile);
	// ���_�J���[
	for(int i = 0; i < dh.uVtx; i++)
	{
		pVtx->_color[i]._red =	1.0f;
		pVtx->_color[i]._green = 1.0f;
		pVtx->_color[i]._blue = 1.0f;
		pVtx->_color[i]._alpha = 1.0f;
	}
	// �e�N�X�`�����W
	fread(pVtx->_texcoord, sizeof(VECTOR2), dh.uVtx, pFile);
	// �C���f�b�N�X
	fread(pIdx->_position, sizeof(u32), dh.uIdx, pFile);
	memcpy(pIdx->_normal, pIdx->_position, sizeof(u32) * dh.uIdx);
	memcpy(pIdx->_color, pIdx->_position, sizeof(u32) * dh.uIdx);
	memcpy(pIdx->_texcoord, pIdx->_position, sizeof(u32) * dh.uIdx);

	m_pVtxBuffer->Unlock();

	// �}�e���A��
	m_uNumMaterial = dh.uMat;
	m_pMaterial = new TexMaterial[dh.uMat];
	fread(m_pMaterial, sizeof(TexMaterial), dh.uMat, pFile);
	
	// �A�g���r���[�g�ǂݍ���
	m_pMeshAttribute = new MeshAttribute[dh.uAtt];
	fread(m_pMeshAttribute, sizeof(MeshAttribute), dh.uAtt, pFile);

	fclose(pFile);

	return true;
}

//=============================================================================
// �`��
//=============================================================================
void CGLModel::Draw(const MATRIX4x4& matrix)
{
	// �f�t�H���g�}�e���A���擾
	VECTOR4 diffuse;
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&diffuse);

	for(u32 uAtt = 0; uAtt < m_uNumMaterial; uAtt++)
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&m_pMaterial->mat.Diffuse);
		m_pVtxBuffer->Draw(matrix, m_pMeshAttribute[uAtt].idxStart, m_pMeshAttribute[uAtt].idxNum);
	}

	glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&diffuse);
}

// EOF