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
class CAttitudeControllerManager;

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

	// �v���C���[�}�l�[�W���[�̎擾
	CPlayerManager* player_manager(void){return player_manager_;}

	// �L�����N�^�[�J�����}�l�[�W���[�̎擾
	CCharacterCameraManager* character_camera_manager(void){return character_camera_manager_;}

	// �p������}�l�[�W���[�̎擾
	CAttitudeControllerManager* attitude_controller_manager(void){return attitude_controller_manager_;}

private:
	CPlayerManager* player_manager_;
	CCharacterCameraManager* character_camera_manager_;
	CAttitudeControllerManager* attitude_controller_manager_;
};

#endif // _CHARACTER_MANAGER_H_

//---------------------------------- EOF --------------------------------------
