//*****************************************************************************
//
// �C���^�[�t�F�[�X�}�l�[�W���[�N���X [interface_manager.cpp]
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "interface/interface_manager.h"

// input
#include "interface/input/input_manager.h"

// graphic
#include "interface/graphic/graphic_manager.h"

// character
#include "interface/character/character_manager.h"

// sound
//#include "interface/sound/sound_manager.h"

// network
#include "interface/network/network_manager.h"

#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInterfaceManager::CInterfaceManager(WINDOW_DATA* window_data)
{
	window_data_ = window_data;

	input_manager_ = new CInputManager(window_data);
	graphic_manager_ = new CGraphicManager(window_data);
	sound_manager_ = NULL;//new CSoundManager();
	network_manager_ = new CNetworkManager();
	character_manager_ = new CCharacterManager();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInterfaceManager::~CInterfaceManager(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CInterfaceManager::Init(void)
{
	// �C���v�b�g�}�l�[�W���[�̏�����
	INIT(input_manager_);

	// �O���t�B�b�N�}�l�[�W���[�̏�����
	INIT(graphic_manager_);

	// �T�E���h�}�l�[�W���[�̏�����
	//INIT(sound_manager_);

	// �l�b�g���[�N�}�l�[�W���[�̏�����
	INIT(network_manager_);

	//�L�����N�^�}�l�[�W���[�̏�����
	INIT(character_manager_);

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CInterfaceManager::Update(void)
{
	// �C���v�b�g�}�l�[�W���[�̍X�V
	input_manager_->Update();

	// �L�����N�^�[�}�l�[�W���[�̍X�V
	character_manager_->Update();
}

//=============================================================================
// �`��
//=============================================================================
void CInterfaceManager::Draw(void)
{
	// �L�����N�^�[�̕`��
	character_manager_->Draw();

	// �O���t�B�b�N�}�l�[�W���[�̕`��
	graphic_manager_->Draw();
}

//=============================================================================
// �I��
//=============================================================================
void CInterfaceManager::Uninit(void)
{
	
	//�L�����N�^�}�l�[�W���̉��
	SAFE_RELEASE(character_manager_);

	// �C���v�b�g�}�l�[�W���[�̊J��
	SAFE_RELEASE(input_manager_);

	// �O���t�B�b�N�}�l�[�W���[�̊J��
	SAFE_RELEASE(graphic_manager_);

	// �T�E���h�}�l�[�W���[�̊J��
	//SAFE_RELEASE(sound_manager_);

	// �l�b�g���[�N�}�l�[�W���[�̊J��
	SAFE_RELEASE(network_manager_);

}

//=============================================================================
// ���[�h�J�n
//=============================================================================
void CInterfaceManager::BeginLoad(void)
{
	graphic_manager_->BeginLoad();
}

//=============================================================================
// ���[�h�I��
//=============================================================================
void CInterfaceManager::EndLoad(void)
{
	graphic_manager_->EndLoad();
}

//-----------------------------------EOF---------------------------------------
