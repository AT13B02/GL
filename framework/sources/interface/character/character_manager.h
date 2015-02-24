//*****************************************************************************
//
// �L�����N�^�}�l�[�W���[�N���X
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/basic.h"

// character
#include "interface/character/character_manager_interface.h"
#include "interface/network/network_data_buffer.h"


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CPlayerManager;
class CCharacterCameraManager;
class CBulletManager;
class CFieldManager;
class CAttitudeControllerManager;
class CCollisionManager;
class CNetWorkPlayer;
class CBoxManager;
class CLife2DManager;
class CIcon2DManager;
//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCharacterManager : public CBasic
{
public:
	// �R���X�g���N�^
	CCharacterManager(void);

	// �f�X�g���N�^
	~CCharacterManager(void);

	// ����������
	bool Init(void);

	// �`��
	void Draw(void);

	// �I������
	void Uninit(void);

	// �X�V����
	void Update(void);

	// �N���A
	void Clear(void);

	// �v���C���[�}�l�[�W���[�̎擾
	CPlayerManager* player_manager(void){return player_manager_;}

	// �L�����N�^�[�J�����}�l�[�W���[�̎擾
	CCharacterCameraManager* character_camera_manager(void){return character_camera_manager_;}

	// �o���b�g�}�l�[�W���[�擾
	CBulletManager* bullet_manager(void){return bullet_manager_;}

	// �t�B�[���h�}�l�[�W���[�̎擾
	CFieldManager* field_manager(void){return field_manager_;}

	//�l�b�g���[�N�v���C���[�擾
	CNetWorkPlayer* network_player( int id ){ return network_player_[ id ]; }

	//�l�b�g���[�N�v���C���[�Z�b�g����
	 void SetNetworkPlayer( CNetWorkPlayer* net_player, int id ){ network_player_[ id ] = net_player; }

	// �p������}�l�[�W���[�̎擾
	CAttitudeControllerManager* attitude_controller_manager(void){return attitude_controller_manager_;}

	// �{�b�N�X�}�l�[�W���̎擾
	CBoxManager* box_manager(){return box_manager_;}

	// ���C�t�}�l�[�W���[�̎擾
	CLife2DManager* life_2d_manager( void ){ return life_2d_manager_ ; }

	// �A�C�R���}�l�[�W���[�̎擾
	CIcon2DManager* icon_2d_manager( void ){ return icon_2d_manager_ ; }
private:
	CPlayerManager* player_manager_;
	CCharacterCameraManager* character_camera_manager_;
	CBulletManager* bullet_manager_;
	CFieldManager* field_manager_;
	CAttitudeControllerManager* attitude_controller_manager_;
	CCollisionManager* collision_manager_;
	CNetWorkPlayer* network_player_[ kMaxPlayer ];
	CBoxManager* box_manager_;
	CLife2DManager* life_2d_manager_;
	CIcon2DManager* icon_2d_manager_;
};

#endif // _CHARACTER_MANAGER_H_

//---------------------------------- EOF --------------------------------------
