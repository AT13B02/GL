//*****************************************************************************
//
// ���C���E�B���h�E����
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "main_window.h"
#include "common/thread/thread.h"
#include "common/common.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const u32 CMainWindow::DEFAULT_WIDTH = DEFAULT_SCREEN_WIDTH;	// ����
const u32 CMainWindow::DEFAULT_HEIGHT = DEFAULT_SCREEN_HEIGHT;	// �c��
const s8* CMainWindow::CLASS_NAME = "MainWindow";				// �N���X��
const s8* CMainWindow::CAPTION_NAME = "framework";				// �L���v�V������

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMainWindow::CMainWindow(HINSTANCE hinstance)
{
	WNDCLASSEX wndclassex =
	{
		sizeof(WNDCLASSEX),				// �\���̂̃T�C�Y
		CS_CLASSDC,						// �X�^�C��
		WindowProcedure,				// �v���V�[�W���̊֐��|�C���^
		0,								// 
		0,								// 
		hinstance,						// �C���X�^���X
		NULL,							// �A�C�R��
		LoadCursor(NULL, IDC_ARROW),	// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �w�i�F
		NULL,							// ���j���[
		CLASS_NAME,						// �E�B���h�E�̃N���X��
		NULL							// �A�C�R��
	};

	message_loop_flag_ = true;

	window_data_._hinstance = hinstance;
	window_data_._wndclassex = wndclassex;
	window_data_._width = DEFAULT_WIDTH;
	window_data_._height = DEFAULT_HEIGHT;

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wndclassex);

	// �E�B���h�E�̍쐬
	window_data_._hwnd = CreateWindowEx(0,
						CLASS_NAME,
						CAPTION_NAME,
						WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZE | WS_MINIMIZEBOX,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						window_data_._width + GetSystemMetrics(SM_CXDLGFRAME) * 2,
						window_data_._height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
						NULL,
						NULL,
						NULL,
						NULL);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMainWindow::~CMainWindow(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CMainWindow::Init(void)
{
	message_loop_flag_ = true;

	// �E�C���h�E�̕\��
	ShowWindow(window_data_._hwnd,SW_SHOW);

	// �E�B���h�E�̍X�V�J�n
	UpdateWindow(window_data_._hwnd);

	return true;
}

//=============================================================================
// �I������
//=============================================================================
void CMainWindow::Uninit(void)
{
	// �E�B���h�E�N���X�̔j��
	UnregisterClass(CLASS_NAME,window_data_._hinstance);
}

//=============================================================================
// ���b�Z�[�W�̊m�F
//=============================================================================
bool CMainWindow::CheckMessage(void)
{
	MSG msg;
	bool bMessageFlag = PeekMessage(&msg,NULL,0,0,PM_REMOVE) == TRUE;

	if(bMessageFlag)
	{
		// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
		if(msg.message == WM_QUIT)
		{
			message_loop_flag_ = false;
		}
		else
		{
			// ���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return bMessageFlag;
}

//=============================================================================
// �E�B���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK CMainWindow::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:			// �E�B���h�E��j��
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			// �L�[����
		switch(wParam)
		{
		case VK_ESCAPE:			// �G�X�P�[�v�L�[
			// �E�B���h�E�̔j��
			DestroyWindow(hWnd);
			break;
		case VK_INSERT:			// �C���T�[�g�L�[
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//=============================================================================
// �E�B���h�E�v���V�[�W��
//=============================================================================
void CMainWindow::Message(CMainWindow* main_window)
{
	MSG msg;

	while(main_window->message_loop_flag_)
	{
		GetMessage(&msg,NULL,0,0);

		// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
		if(msg.message == WM_QUIT)
		{
			main_window->message_loop_flag_ = false;
		}
		else
		{
			// ���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

//-----------------------------------EOF---------------------------------------
