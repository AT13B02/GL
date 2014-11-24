//*****************************************************************************
//
// �I�u�W�F�N�g2D�}�l�[�W���[�N���X [object_2d_manager.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object_2d.h"
#include "object_2d_list.h"
#include "object_2d_data.h"
#include "object_2d_buffer.h"
#include "object_2d_manager.h"

#include "renderstate.h"
#include "renderstate_manager.h"

#include "graphics_device.h"

#include "common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject2DManager::CObject2DManager(CGraphicsDevice* pGraphicsDevice,CRenderstateManager* pRenderstateManager)
{
	// �O���t�B�b�N�f�o�C�X�̐ݒ�
	m_pGraphicsDevice = pGraphicsDevice;

	// �����_�[�X�e�[�g�}�l�[�W���[�̐ݒ�
	m_pRenderstateManager = pRenderstateManager;

	// �I�u�W�F�N�g���X�g�̐���
	for(int i = 0;i < LIST_TYPE_MAX;i++)
	{
		m_apObject2DList[i] = new CObject2DList();
	}

	m_bChangeFlag = false;

	// �I�u�W�F�N�g�o�b�t�@�̐���
	m_pBuffer = new CObject2DBuffer();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject2DManager::~CObject2DManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CObject2DManager::Init(void)
{
	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject2DManager::Draw(void)
{
	m_pRenderstateManager->GetRenderstate(CRenderstateManager::TYPE_2D)->Set();

	m_pBuffer->Draw();

	m_pRenderstateManager->GetRenderstate(CRenderstateManager::TYPE_2D)->Unset();
}

//=============================================================================
// �I������
//=============================================================================
void CObject2DManager::Uninit(void)
{
	// �I�u�W�F�N�g���X�g�̊J��
	for(int i = 0;i < LIST_TYPE_MAX;i++)
	{
		SAFE_RELEASE(m_apObject2DList[i]);
	}

	// �o�b�t�@�̊J��
	SAFE_RELEASE(m_pBuffer);

}

//=============================================================================
// �ǉ�����
//=============================================================================
int CObject2DManager::Add(CObject2D* pObject2D,int nListType)
{
	if(nListType < 0 || nListType >= LIST_TYPE_MAX)
	{
		return -1;
	}

	return m_apObject2DList[nListType]->Add(pObject2D);
}

//=============================================================================
// �ύX����
//=============================================================================
void CObject2DManager::Change(void)
{
	if(m_bChangeFlag)
	{
		CObject2DList* pObjectList = NULL;
		pObjectList = m_apObject2DList[LIST_TYPE_USE];
		m_apObject2DList[LIST_TYPE_USE] = m_apObject2DList[LIST_TYPE_LOAD];
		m_apObject2DList[LIST_TYPE_LOAD] = pObjectList;
		pObjectList->Refresh();
		m_bChangeFlag = false;
	}
}

//=============================================================================
// �ύX����
//=============================================================================
void CObject2DManager::RaiseChangeFlag(void)
{
	m_bChangeFlag = true;
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos)
{
	Draw(nObjectNumber,Pos,NULL);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,CTexture* pTexture)
{
	Draw(nObjectNumber,Pos,0.0f,pTexture);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,float fRot,CTexture* pTexture)
{
	Draw(nObjectNumber,Pos,fRot,VECTOR2(1.0f,1.0f),pTexture);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,CTexture* pTexture)
{
	MATRIX4x4 Matrix;

	Matrix.SetIdentity();

	Draw(nObjectNumber,Pos,fRot,Scale,Matrix,pTexture);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture)
{
	Draw(nObjectNumber,Pos,fRot,Scale,Matrix,pTexture,NULL);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture,CRenderstate* pRenderstate)
{
	CObject2DData* pData = NULL;
	CObject2D* pObject2D = m_apObject2DList[LIST_TYPE_USE]->GetObject2D(nObjectNumber);

	// �I�u�W�F�N�g�ԍ��̊m�F
	if(pObject2D == NULL)
	{
		return;
	}

	// �o�b�t�@�̐���
	pData = new CObject2DData();

	// �o�b�t�@�ԍ��̐ݒ�
	pData->SetObject(pObject2D);

	// ���W�̐ݒ�
	pData->SetPosition(Pos);

	// ��]�p�̐ݒ�
	pData->SetRotation(fRot);

	// �X�P�[���̐ݒ�
	pData->SetScale(Scale);

	// �}�g���b�N�X�̐ݒ�
	pData->SetMatrix(Matrix);

	// �e�N�X�`���̐ݒ�
	pData->SetTexture(pTexture);

	// �����_�[�X�e�[�g�̐ݒ�
	pData->SetRenderstate(pRenderstate);

	// �o�b�t�@���X�g�ɕۑ�
	m_pBuffer->Add(pData);
}

//---------------------------------- EOF --------------------------------------
