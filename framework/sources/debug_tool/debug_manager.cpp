//*****************************************************************************
//
// �f�o�b�O�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "debug_manager.h"
#include "debug_console.h"

#include "basic/application_manager.h"
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"

#include "common/thread/thread.h"
#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
CDebugManager CDebugManager::instance_;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CDebugManager::CDebugManager(void)
{
#ifdef _DEBUG
	application_manager_ = NULL;
	debug_console_ = NULL;
#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CDebugManager::~CDebugManager(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CDebugManager::Init(void)
{
#ifdef _DEBUG
	debug_console_ = new CDebugConsole();

	// ������
	INIT(debug_console_);

	// �R���\�[�����B��
	//debug_console_->Hide();

	is_run_ = true;
	is_update_ = true;
	is_live_ = true;
#endif
	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CDebugManager::Update(void)
{
#ifdef _DEBUG
	if(application_manager_ != NULL)
	{
		CInterfaceManager* interface_manager = application_manager_->interface_manager();
		CInputManager* input_manager = interface_manager->input_manager();

		if(input_manager->CheckRelease(INPUT_EVENT_F12))
		{
			debug_console_->SwitchWindow();
		}
	}
#endif
}

//=============================================================================
// �`��
//=============================================================================
void CDebugManager::Draw(void)
{
#ifdef _DEBUG
	// �f�o�b�O�R���\�[���̕`��
	debug_console_->Draw();
#endif
}

//=============================================================================
// �I��
//=============================================================================
void CDebugManager::Uninit(void)
{
#ifdef _DEBUG
	SAFE_RELEASE(debug_console_);
	is_live_ = false;
#endif
}


//=============================================================================
// �X���b�h�̊J�n
//=============================================================================
void CDebugManager::Run(void)
{
#ifdef _DEBUG
	instance_.Init();

	instance_.thread_ = new CThread();

	instance_.thread_->Init();

	instance_.thread_->Start(Thread,nullptr);
#endif
}

//=============================================================================
// �X���b�h�̏I��
//=============================================================================
void CDebugManager::Stop(void)
{
#ifdef _DEBUG
	is_run_ = false;

	SAFE_RELEASE(thread_);

	Uninit();
#endif
}

//=============================================================================
// �X���b�h�̊J�n
//=============================================================================
void CDebugManager::Thread(void)
{
#ifdef _DEBUG
	while(instance_.is_run_)
	{
		if(instance_.is_update_)
		{
			instance_.Update();
			instance_.Draw();
			instance_.is_update_ = false;
		}
	}
#endif
}

//-----------------------------------EOF---------------------------------------
