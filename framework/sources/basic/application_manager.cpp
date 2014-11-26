//*****************************************************************************
//
// �A�v���P�[�V�����}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "fps_manager.h"
#include "main_window.h"
#include "application_manager.h"
#include "scene/scene_manager.h"
#include "interface/interface_manager.h"

#include "common/thread/thread.h"
#include "common/common.h"

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
CApplicationManager::CApplicationManager(HINSTANCE hinstance)
{
	hinstance_ = hinstance;
	hwnd_ = NULL;
	fps_manager_ = NULL;
	interface_manager_ = NULL;
	scene_manager_ = NULL;
	loop_flag_ = true;
	update_flag_ = true;

	// ���C���E�B���h�E�̍쐬
	main_window_ = new CMainWindow(hinstance);

	// �E�B���h�E�n���h���̎擾
	hwnd_ = main_window_->hwnd();

	// FPS�}�l�[�W���[�̐���
	fps_manager_ = new CFpsManager();

	// �C���^�[�t�F�[�X�}�l�[�W���[�̐���
	interface_manager_ = new CInterfaceManager(main_window_->window_data());

	// �V�[���}�l�[�W���[�̐���
	scene_manager_ = new CSceneManager(interface_manager_);

	// �X���b�h�̐���
	thread_ = new CThread();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CApplicationManager::~CApplicationManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CApplicationManager::Init(void)
{
	// ���[�v�t���O�𗧂Ă�
	loop_flag_ = true;

	// �X�V�t���O�𗧂Ă�
	update_flag_ = true;

	// ���C���E�B���h�E�̏�����
	main_window_->Init();

	// �X���b�h�̏�����
	thread_->Init();

	// FPS�}�l�[�W���[�̏�����
	INIT(fps_manager_);

	// �C���^�[�t�F�[�X�}�l�[�W���[�̏�����
	INIT(interface_manager_);

	// �V�[���}�l�[�W���[�̏�����
	INIT(scene_manager_);

	// �X���b�h�̊J�n
	thread_->Start(Thread,this);

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CApplicationManager::Update(void)
{
	// FPS�̊m�F
	if(fps_manager_->CheckFps())
	{
		// FPS�Ǘ��̍X�V
		fps_manager_->Update();

		// �C���^�[�t�F�[�X�}�l�[�W���[�̍X�V
		if(interface_manager_ != NULL)
		{
			interface_manager_->Update();
		}

		// �X�V�t���O���m�F
		if(update_flag_)
		{
			// �V�[���̍X�V
			if(scene_manager_ != NULL)
			{
				scene_manager_->Update();
			}
		}

		// �V�[���̕`��
		if(scene_manager_ != NULL)
		{
			scene_manager_->Draw();
		}

		// �C���^�[�t�F�[�X�}�l�[�W���[�̕`��
		if(interface_manager_ != NULL)
		{
			interface_manager_->Draw();
		}

		// �f�o�b�O�}�l�[�W���[�̍X�V
		DEBUG_TOOL.UpdateMessage();
	}
}

//=============================================================================
// �I��
//=============================================================================
void CApplicationManager::Uninit(void)
{
	loop_flag_ = false;

	update_flag_ = false;

	// �E�B���h�E�̊J��
	SAFE_RELEASE(main_window_);

	// �X���b�h�̊J��
	SAFE_RELEASE(thread_);

	// FPS�Ǘ��̏I��
	SAFE_RELEASE(fps_manager_);

	// �V�[���}�l�[�W���[�̔j��
	SAFE_RELEASE(scene_manager_);

	// �C���^�[�t�F�[�X�}�l�[�W���[�̔j��
	SAFE_RELEASE(interface_manager_);
}

//=============================================================================
// ���[�v
//=============================================================================
void CApplicationManager::Run(void)
{
	// ���b�Z�[�W���[�v
	while(main_window_->message_loop_flag())
	{
		// ���b�Z�[�W�̊m�F
		main_window_->CheckMessage();
	}
}

//=============================================================================
// �X���b�h����
//=============================================================================
void CApplicationManager::Thread(CApplicationManager* application_manager)
{
	// ���C�����[�v
	while(application_manager->loop_flag_)
	{
		// �A�v���P�[�V�����̍X�V
		application_manager->Update();
	}
}

//---------------------------------- EOF --------------------------------------
