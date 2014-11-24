//*****************************************************************************
//
// �A�v���P�[�V�����}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _APPLICATION_MANAGER_H_
#define _APPLICATION_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic.h"
#include <windows.h>

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
// �N���X�̑O���Q��
//*****************************************************************************
class CMainWindow;
class CFpsManager;
class CSceneManager;
class CInterfaceManager;
class CThread;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CApplicationManager : public CBasic
{
public:
	// �R���X�g���N�^
	CApplicationManager(HINSTANCE hinstance);

	// �f�X�g���N�^
	~CApplicationManager(void);

	// ����������
	bool Init(void);

	// �X�V����
	void Update(void);

	// �I������
	void Uninit(void);

	// ���s
	void Run(void);

	// �f�o�b�O�p
	CInterfaceManager* interface_manager(void){return interface_manager_;}

	// �X�V�t���O��؂芷��
	void SwitchUpdateFlag(void){update_flag_ ^= true;}
private:
	// �C���X�^���X
	HINSTANCE hinstance_;

	// �E�B���h�E�n���h��
	HWND hwnd_;

	// ���C���E�B���h�E
	CMainWindow* main_window_;

	// FPS�}�l�[�W���[
	CFpsManager* fps_manager_;

	// �V�[���}�l�[�W���[
	CSceneManager* scene_manager_;

	// �C���^�[�t�F�[�X�}�l�[�W���[
	CInterfaceManager* interface_manager_;

	// �X���b�h
	CThread* thread_;

	// ���[�v�t���O
	bool volatile loop_flag_;

	// �X�V�t���O
	bool volatile update_flag_;

	// �X���b�h
	static void Thread(CApplicationManager* application_manager);
};

#endif	// _APPLICATION_MANAGER_H_

//---------------------------------- EOF --------------------------------------
