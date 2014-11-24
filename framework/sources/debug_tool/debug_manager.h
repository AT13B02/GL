//*****************************************************************************
//
// �f�o�b�O�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _DEBUG_MANAGER_H_
#define _DEBUG_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/basic.h"
#include "debug_tool/debug_console.h"

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
class CApplicationManager;
class CDebugConsole;
class CThread;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDebugManager : public CBasic
{
public:
	// �f�o�b�O�X���b�h�𗧂Ă�
	static void Run(void);

	// �f�o�b�O�X���b�h�𗧂Ă�
	static void Stop(void){instance_.is_run_ = false;}

	// �C���X�^���X�̎擾
	static CDebugManager* instance(void){return &instance_;}

	// �X�V���b�Z�[�W
	void UpdateMessage(void){is_update_ = true;}

	// �A�v���P�[�V�����}�l�[�W���[�̐ݒ�
	void set_application_manager(CApplicationManager* application_manger){application_manager_ = application_manger;}

	// �f�o�b�O�R���\�[���̎擾
	CDebugConsole* debug_console(void){return debug_console_;}
protected:

private:
	// �R���X�g���N�^
	CDebugManager(void);
	// �f�X�g���N�^
	~CDebugManager(void);

	// ������
	bool Init(void);
	// �X�V
	void Update(void);
	// �`��
	void Draw(void);
	// �I��
	void Uninit(void);

	static CDebugManager instance_;
	volatile bool is_run_;
	volatile bool is_update_;

	CDebugConsole* debug_console_;
	CThread* thread_;
	CApplicationManager* application_manager_;
	static void Thread(void);
};

#endif // _DEBUG_MANAGER_H_

//---------------------------------- EOF --------------------------------------
