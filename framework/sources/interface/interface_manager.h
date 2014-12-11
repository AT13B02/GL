//*****************************************************************************
//
// �C���^�[�t�F�[�X�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _INTERFACE_MANAGER_H_
#define _INTERFACE_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/basic.h"
#include "basic/main_window.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �萔��`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CInputManager;
class CSoundManager;
class CGraphicManager;
class CNetworkManager;
class CCharacterManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CInterfaceManager : public CBasic
{
public:
	// �R���X�g���N�^
	CInterfaceManager(WINDOW_DATA* window_data);

	// �f�X�g���N�^
	~CInterfaceManager(void);

	// ����������
	bool Init(void);

	// �X�V����
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �I������
	void Uninit(void);

	// ���[�h�J�n
	void BeginLoad(void);

	// ���[�h�I��
	void EndLoad(void);

	// �E�B���h�E�f�[�^�̎擾
	WINDOW_DATA* window_data(void){return window_data_;}

	// �C���v�b�g�}�l�[�W���[�̎擾
	CInputManager* input_manager(void){return input_manager_;}

	// �T�E���h�}�l�[�W���[�̎擾
	CSoundManager* sound_manager(void){return sound_manager_;}

	// �O���t�B�b�N�}�l�[�W���[�̎擾
	CGraphicManager* graphic_manager(void){return graphic_manager_;}

	// �l�b�g���[�N�}�l�[�W���[�̎擾
	CNetworkManager* network_manager(void){return network_manager_;}

	//�L�����N�^�}�l�[�W���[�̎擾
	CCharacterManager* character_manager( void ){ return character_manager_; }

protected:

private:
	WINDOW_DATA* window_data_;
	CInputManager* input_manager_;
	CSoundManager* sound_manager_;
	CGraphicManager* graphic_manager_;
	CNetworkManager* network_manager_;
	CCharacterManager* character_manager_;
};

#endif // _INTERFACE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
