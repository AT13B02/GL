//=============================================================================
//
// �E�B���h�E�N���X [CWindow.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CWindow.h"
#include "Debug.h"

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
// �E�B���h�E�X�^�C��
const int CWindow::GAME_WINDOW = (WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX));

//=============================================================================
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
CWindow::CWindow()
{
}

//=============================================================================
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
CWindow::~CWindow()
{
	// �E�B���h�E�N���X�o�^����
	UnregisterClass(m_strClassName.c_str(), GetModuleHandle(NULL));
}

//=============================================================================
// ��������
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
HRESULT CWindow::Create(DWORD uWidth, DWORD uHeight, const char* pCaption, const char* pClassName, WNDPROC pWndProc, CWindow** ppWindow)
{
	(*ppWindow) = new CWindow();

	HRESULT hr = NULL != (*ppWindow) ? S_OK : E_FAIL;
	if(FAILED(hr))
	{
		return hr;
	}

	hr = (*ppWindow)->Create(uWidth, uHeight, pCaption, pClassName, pWndProc);

	return hr;
}

//=============================================================================
// �J��
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
void CWindow::Release()
{
	delete this;
}

//=============================================================================
// ���b�Z�[�W����
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
CWindow::Message CWindow::ProcMessage(MSG& msg)
{
	// ���b�Z�[�W������ꍇ����
	Message message = MESSAGE_OK;
	BOOL bIsMessageExist = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
	if(TRUE == bIsMessageExist)
	{
		// �I�����b�Z�[�W������ꂽ�ꍇ
		if(msg.message == WM_QUIT)
		{
			message = MESSAGE_TERMINATE;
		}
		// �����Ă��Ȃ��ꍇ
		else
		{
			// ���b�Z�[�W�̖|��Ƒ��o
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return message;
}

//=============================================================================
// �E�B���h�E�n���h���擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
const HWND& CWindow::GetWindowHandle()
{
	return m_hWnd;
}

//=============================================================================
// �E�B���h�E�����擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
const DWORD& CWindow::GetWindowWidth()
{
	return m_uWindowWidth;
}

//=============================================================================
// �E�B���h�E�c���擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
const DWORD& CWindow::GetWindowHeight()
{
	return m_uWindowHeight;
}

//=============================================================================
// �L���v�V�����ݒ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
void CWindow::SetCaption(const char* pCaption)
{
	m_strCaption = pCaption;
	// �E�B���h�E�̃L���v�V������ݒ�
	SetWindowText(m_hWnd, m_strCaption.c_str());
}

//=============================================================================
// ������������
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
HRESULT CWindow::Create(DWORD uWidth, DWORD uHeight, const char* pCaption, const char* pClassName, WNDPROC pWndProc)
{
	HRESULT hr = E_FAIL;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	m_uWindowWidth = uWidth;
	m_uWindowHeight = uHeight;

	m_strCaption = pCaption;
	m_strClassName = pClassName;
	
	RECT rc;
	// �E�B���h�E��`�͈͐ݒ�
	rc.top		= 0;
	rc.left		= 0;
	rc.right	= m_uWindowWidth;
	rc.bottom	= m_uWindowHeight;
	
	// �E�B���h�E�N���X������
	WNDCLASSEX wcex = 
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		pWndProc,	// �E�B���h�E�v���V�[�W���֐�
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		NULL,
		pClassName,
		NULL
	};
	
	// �E�B���h�E�N���X�o�^
	if(FAILED(RegisterClassEx(&wcex)))
	{
		MessageBox(NULL, "�E�B���h�E�N���X�o�^���s", "�G���[", MB_OK);
		return E_FAIL;
	}
	
	// �E�B���h�E�����킹
	AdjustWindowRect(
		&rc,		// �E�B���h�E��
		GAME_WINDOW, // �E�B���h�E�X�^�C��
		FALSE);		// ���j���[�̗L��
	
	// �E�B���h�E���W�ݒ�
	// �^�X�N�o�[���������f�B�X�v���C���擾
	int nDisplayWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int nDisplayHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	
	// �E�B���h�E�쐬
	int nWindowWidth = rc.right - rc.left;	// �E�B���h�E����
	int nWindowHeight = rc.bottom - rc.top;	// �E�B���h�E�c��
	int nWindowPosX = (nDisplayWidth >> 1) - (nWindowWidth >> 1);	// �E�B���h�E����X���W
	int nWindowPosY = (nDisplayHeight >> 1) - (nWindowHeight >> 1);	// �E�B���h�E����Y���W

	// �E�B���h�E�̍쐬
	m_hWnd = CreateWindowEx(0,
		m_strClassName.c_str(),
		m_strCaption.c_str(),
		// �Ϙg�A�ő剻�{�^������菜��
		GAME_WINDOW,
		nWindowPosX,
		nWindowPosY,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	// �쐬���s�\��
	if(!m_hWnd)
	{
		MessageBox(NULL, "�E�B���h�E�쐬���s", "�G���[", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// �E�B���h�E�\��
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
void CWindow::ShowWindow()
{
	// �E�B���h�E�\��
	::ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

// EOF