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
#include "explosion/explosion_manager.h"
#include "field/field_manager.h"
#include "collision/collision_manager.h"
#include "attitude_controller/attitude_controller_manager.h"
#include "interface/character/player/network_player.h"
#include "interface/character/box/box_manager.h"
#include "interface/character/player_status/life_2d/life_2d_manager.h"
#include "interface/character/player_status/user_number_2d/icon_2d_manager.h"
// common
#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCharacterManager::CCharacterManager(void)
{
	//�l�b�g�v���C���[������
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		network_player_[ i ] = NULL;
	}

	// �v���C���[�}�l�[�W���[�̐���
	player_manager_ = new CPlayerManager();

	// �L�����N�^�[�J�����}�l�[�W���[�̐���
	character_camera_manager_ = new CCharacterCameraManager();

	// �o���b�g�}�l�[�W���[�̐���
	bullet_manager_ = new CBulletManager();
	
	// �����}�l�[�W���[�̐���
	explosion_manager_ = new CExplosionManager();

	// �t�B�[���h�}�l�[�W���[�̐���
	field_manager_ = new CFieldManager();

	// �p������}�l�[�W���[�̐���
	attitude_controller_manager_ = new CAttitudeControllerManager();

	// �Փ˔���}�l�[�W���[�̐���
	collision_manager_ = new CCollisionManager(this);

	// �{�b�N�X�}�l�[�W���̐���
	box_manager_ = new CBoxManager();

	//���C�t�}�l�[�W���[�̐���
	life_2d_manager_ = new CLife2DManager();

	//�A�C�R���}�l�[�W���[�̐���
	icon_2d_manager_ = new CIcon2DManager();
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

	// �����}�l�[�W���[�̏�����
	INIT(explosion_manager_);

	// �t�B�[���h�}�l�[�W���[�̏�����
	INIT(field_manager_);

	// �p������R���g���[���[�}�l�[�W���[�̏�����
	INIT(attitude_controller_manager_);

	// �Փ˔���}�l�[�W���[�̏�����
	INIT(collision_manager_);
	
	// �{�b�N�X�}�l�[�W���[�̏�����
	INIT(box_manager_);

	// ���C�t�}�l�[�W���[�̏�����
	INIT( life_2d_manager_ );

	// �A�C�R���}�l�[�W���[�̏�����
	INIT( icon_2d_manager_ );
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

	// �����}�l�[�W���[�̍X�V
	explosion_manager_->Update();

	// �t�B�[���h�}�l�[�W���[�̍X�V
	field_manager_->Update();

	// �L�����N�^�[�J�����}�l�[�W���[�̍X�V
	character_camera_manager_->Update();

	// �Փ˔���}�l�[�W���[�̍X�V
	collision_manager_->Update();
	
	// �{�b�N�X�}�l�[�W���[�̍X�V
	box_manager_->Update();

	// ���C�t�}�l�[�W���[�̍X�V
	life_2d_manager_->Update();

	// �A�C�R���}�l�[�W���[�̍X�V
	icon_2d_manager_->Update();
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

	// �����}�l�[�W���[�̍X�V
	explosion_manager_->Draw();

	// �{�b�N�X�}�l�[�W���[�̕`��
	box_manager_->Draw();

	// ���C�t�}�l�[�W���[�̕`��
	life_2d_manager_->Draw();

	// �A�C�R���}�l�[�W���[�̕`��
	icon_2d_manager_->Draw();
}

//=============================================================================
// �N���A
//=============================================================================
void CCharacterManager::Clear(void)
{
	//�l�b�g�v���C���[������
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		SAFE_RELEASE(network_player_[ i ]);
	}

	// �v���C���[�}�l�[�W���[�̊J��
	player_manager_->Uninit();

	// �L�����N�^�[�J�����}�l�[�W���[�̊J��
	character_camera_manager_->Uninit();

	// �o���b�g�}�l�[�W���[�̊J��
	bullet_manager_->Uninit();
	
	// �����}�l�[�W���[�̊J��
	explosion_manager_->Uninit();

	// �t�B�[���h�}�l�[�W���[�̊J��
	field_manager_->Uninit();

	// �p������}�l�[�W���[�̊J��
	attitude_controller_manager_->Uninit();

	// �Փ˔���}�l�[�W���[�̊J��
	collision_manager_->Uninit();

	// �{�b�N�X�}�l�[�W���[�̊J��
	box_manager_->Uninit();

	// ���C�t�}�l�[�W���[�̉��
	life_2d_manager_->Uninit();

	// �A�C�R���}�l�[�W���[�̉��
	icon_2d_manager_->Uninit();
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
	
	// �����}�l�[�W���[�̊J��
	SAFE_RELEASE(explosion_manager_);

	// �t�B�[���h�}�l�[�W���[�̊J��
	SAFE_RELEASE(field_manager_);

	// �p������}�l�[�W���[�̊J��
	SAFE_RELEASE(attitude_controller_manager_);

	// �Փ˔���}�l�[�W���[�̊J��
	SAFE_RELEASE(collision_manager_);
	
	// �{�b�N�X�}�l�[�W���[�̊J��
	SAFE_RELEASE(box_manager_);

	// ���C�t�}�l�[�W���[�̉��
	SAFE_RELEASE( life_2d_manager_ );

	// ���C�t�}�l�[�W���[�̉��
	SAFE_RELEASE( icon_2d_manager_ );
}

//---------------------------------- EOF --------------------------------------
