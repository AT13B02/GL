//*****************************************************************************
//
// �L�����N�^�}�l�[�W���[�N���X
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// character
#include "character_manager.h"
#include "player/player_manager.h"
#include "camera/character_camera_manager.h"
#include "bullet/bullet_manager.h"
#include "field/field_manager.h"
#include "attitude_controller/attitude_controller_manager.h"
#include "interface/character/player/network_player.h"

// common
#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacterManager::CCharacterManager(void)
{
	// �v���C���[�}�l�[�W���[�̐���
	player_manager_ = new CPlayerManager();

	// �L�����N�^�[�J�����}�l�[�W���[�̐���
	character_camera_manager_ = new CCharacterCameraManager();

	// �o���b�g�}�l�[�W���[�̐���
	bullet_manager_ = new CBulletManager();

	// �t�B�[���h�}�l�[�W���[�̐���
	field_manager_ = new CFieldManager();

	// �p������}�l�[�W���[�̐���
	attitude_controller_manager_ = new CAttitudeControllerManager();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCharacterManager::~CCharacterManager(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CCharacterManager::Init(void)
{
	// �v���C���[�}�l�[�W���[�̏�����
	INIT(player_manager_);

	// �J�����}�l�[�W���[�̏�����
	INIT(character_camera_manager_);

	// �o���b�g�}�l�[�W���[�̏�����
	INIT(bullet_manager_);

	// �t�B�[���h�}�l�[�W���[�̏�����
	INIT(field_manager_);

	// �p������R���g���[���[�}�l�[�W���[�̏�����
	INIT(attitude_controller_manager_);

	//�l�b�g�v���C���[������
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		network_player_[ i ] = NULL;
	}

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CCharacterManager::Update(void)
{
	// �p������R���g���[���[�̍X�V
	attitude_controller_manager_->Update();

	// �v���C���[�}�l�[�W���[�̍X�V
	player_manager_->Update();

	// �o���b�g�}�l�[�W���[�̍X�V
	bullet_manager_->Update();

	// �t�B�[���h�}�l�[�W���[�̍X�V
	field_manager_->Update();

	// �L�����N�^�[�J�����}�l�[�W���[�̍X�V
	character_camera_manager_->Update();

	//�l�b�g�v���C���[�X�V
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		if(network_player_[ i ] != nullptr)
		{
			network_player_[ i ]->Update();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CCharacterManager::Draw(void)
{
	// �t�B�[���h�}�l�[�W���[�̕`��
	field_manager_->Draw();

	// �v���C���[�}�l�[�W���[�̕`��
	player_manager_->Draw();

	// �o���b�g�}�l�[�W���[�̕`��
	bullet_manager_->Draw();

	//�l�b�g�v���C���[�`��
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		if(network_player_[ i ] != nullptr)
		{
			network_player_[ i ]->Draw();
		}
	}
}

//=============================================================================
// �I��
//=============================================================================
void CCharacterManager::Uninit(void)
{
	//�l�b�g���[�N�v���C���[�̏I������
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		if( network_player_[ i ] != NULL )
		{
			network_player_[ i ] -> Uninit();

			delete network_player_[ i ];

			network_player_[ i ] = NULL;
		}
	}

	// �v���C���[�}�l�[�W���[�̊J��
	SAFE_RELEASE(player_manager_);

	// �L�����N�^�[�J�����}�l�[�W���[�̊J��
	SAFE_RELEASE(character_camera_manager_);

	// �o���b�g�}�l�[�W���[�̊J��
	SAFE_RELEASE(bullet_manager_);

	// �t�B�[���h�}�l�[�W���[�̊J��
	SAFE_RELEASE(field_manager_);

	// �p������}�l�[�W���[�̊J��
	SAFE_RELEASE(attitude_controller_manager_);


}

//---------------------------------- EOF --------------------------------------
