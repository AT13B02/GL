//*****************************************************************************
//
// �G�l�~�[�}�l�[�W���[�N���X [enemy_manager.cpp]
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
#include "enemy_manager.h"
#include "common.h"

#include "object_manager.h"
#include "object_2d_manager.h"

#include "enemy_test.h"
#include "enemy_test3d.h"

#include "list.h"
#include "texture_manager.h"

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
CEnemyManager::CEnemyManager(CObjectManager* pObjectManager)
{
	m_pObjectManager = pObjectManager;

	// �G�l�~�[���X�g�𐶐�
	m_pEnemyList = new CList<CEnemy*>();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyManager::~CEnemyManager(void)
{
	CEnemy* pEnemy = NULL;

	for(int i = 0;i < CEnemy::ENEMY_TYPE_MAX;i++)
	{
		// 
		SAFE_DELETE(m_aObjectNumber[i]);
	}

	// ���X�g��擪��
	m_pEnemyList->Begin();

	// ���X�g���I������܂ő�����
	while(m_pEnemyList->Current() != NULL)
	{
		// �G�l�~�[�����o��
		pEnemy = m_pEnemyList->Pop();

		// NULL�`�F�b�N
		if(pEnemy != NULL)
		{
			// ���X�g����O��
			m_pEnemyList->RaiseDeathFlag();

			// �G�l�~�[�̊J��
			SAFE_RELEASE(pEnemy);
		}

		// ���̃��X�g��
		m_pEnemyList->Next();
	}

	// �G�l�~�[���X�g��j��
	SAFE_RELEASE(m_pEnemyList);
}

//=============================================================================
// ����������
//=============================================================================
bool CEnemyManager::Init(void)
{
	CEnemy* pEnemy = NULL;
	int* nNumbers = NULL;
	CTextureManager* pTextureManager = m_pObjectManager->GetTextureManager();

	// �I�u�W�F�N�g�𐶐�
	for(int i = 0;i < CEnemy::ENEMY_TYPE_MAX;i++)
	{
		// �G�l�~�[�̐���
		pEnemy = CreateEnemy((CEnemy::ENEMY_TYPE)(i),false);

		if(pEnemy != NULL)
		{
			// �G�l�~�[�ɑ΂��ăI�u�W�F�N�g�̐������˗�
			pEnemy->CreateObject(&nNumbers);

			m_aObjectNumber[i] = nNumbers;
		}
		else
		{
			m_aObjectNumber[i] = NULL;
		}

		// �G�l�~�[�̔j��
		SAFE_RELEASE(pEnemy);
	}

	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyManager::Update(void)
{
	CEnemy* pEnemy = NULL;

	// ���X�g��擪��
	m_pEnemyList->Begin();

	// ���X�g���I������܂ő�����
	while(m_pEnemyList->Current() != NULL)
	{
		// �G�l�~�[�����o��
		pEnemy = m_pEnemyList->Pop();

		// NULL�`�F�b�N
		if(pEnemy != NULL)
		{
			pEnemy->Update();
		}

		// ���̃��X�g��
		m_pEnemyList->Next();
	}
}

//=============================================================================
// ���S�t���O���m�F���Ĕj������
//=============================================================================
void CEnemyManager::KillRaiseDeathFlag(void)
{
	CEnemy* pEnemy = NULL;

	// ���X�g��擪��
	m_pEnemyList->Begin();

	// ���X�g���I������܂ő�����
	while(m_pEnemyList->Current() != NULL)
	{
		// �G�l�~�[�����o��
		pEnemy = m_pEnemyList->Pop();

		// NULL�`�F�b�N
		if(pEnemy != NULL)
		{
			// ���S�t���O���m�F
			if(pEnemy->GetDeathFlag())
			{
				// ���X�g����O��
				m_pEnemyList->RaiseDeathFlag();
				// �G�l�~�[�̊J��
				SAFE_RELEASE(pEnemy);
			}
		}

		// ���̃��X�g��
		m_pEnemyList->Next();
	}

	// ���S�t���O�𗧂��Ă���̂����X�g�������
	m_pEnemyList->KillRaiseDeathFlag();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyManager::Draw(void)
{
	CEnemy* pEnemy = NULL;

	// ���X�g��擪��
	m_pEnemyList->Begin();

	// ���X�g���I������܂ő�����
	while(m_pEnemyList->Current() != NULL)
	{
		// �G�l�~�[�����o��
		pEnemy = m_pEnemyList->Pop();

		// NULL�`�F�b�N
		if(pEnemy != NULL)
		{
			pEnemy->Draw();
		}

		// ���̃��X�g��
		m_pEnemyList->Next();
	}
}

//=============================================================================
// �G�l�~�[�̐���
//=============================================================================
CEnemy* CEnemyManager::CreateEnemy(CEnemy::ENEMY_TYPE EnemyType,bool bListFlag)
{
	CEnemy* pEnemy = NULL;

	switch (EnemyType)
	{
		// �e�X�g
		case (CEnemy::ENEMY_TYPE_TEST):
		{
			pEnemy = new CEnemyTest(m_pObjectManager,m_aObjectNumber[CEnemy::ENEMY_TYPE_TEST]);
			break;
		}
		// �e�X�g
		case (CEnemy::ENEMY_TYPE_TEST3D):
		{
			pEnemy = new CEnemyTest3D(m_pObjectManager,m_aObjectNumber[CEnemy::ENEMY_TYPE_TEST3D]);
			break;
		}
		default:
		{
			break;
		}
	}

	// �G�l�~�[�̐��������Ă�����
	if(pEnemy != NULL)
	{
		// ���X�g�����t���O���I���̎�
		if(bListFlag)
		{
			// ���X�g�ɓo�^
			m_pEnemyList->Push(pEnemy);
		}
	}

	return pEnemy;
}

//---------------------------------- EOF --------------------------------------
