//*****************************************************************************
//
// ���C������
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/application_manager.h"

#include "debug_tool/debug_manager.h"
#include "debug_tool/debug_console.h"
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
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE preview_hinstance, LPSTR command_line,int command_show)
{
#ifdef _DEBUG
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// ���g�p�錾
	UNREFERENCED_PARAMETER(preview_hinstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(command_show);

	// �A�v���P�[�V�����}�l�[�W���[
	CApplicationManager* application_manager = NULL;

	// �A�v���P�[�V�����}�l�[�W���[�̐���
	application_manager = new CApplicationManager(hinstance);

	// �f�o�b�O�̏�����
	CDebugManager::instance()->set_application_manager(application_manager);

	// �f�o�b�O�J�n
	CDebugManager::Run();

	// �A�v���P�[�V�����}�l�[�W���[�̏�����
	if(application_manager->Init())
	{
		// �A�v���P�[�V�����}�l�[�W���[�̍X�V
		application_manager->Run();
	}
	else
	{
		// �A�v���P�[�V�����̏��������s
	}

	// �f�o�b�O�I��
	CDebugManager::Stop();

	// �A�v���P�[�V�����}�l�[�W���[�̊J��
	SAFE_RELEASE(application_manager);

	return 0;
}

//---------------------------------- EOF --------------------------------------
