//=============================================================================
//
// ウィンドウクラス [CWindow.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CWindow.h"
#include "Debug.h"

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************
// ウィンドウスタイル
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
	// ウィンドウクラス登録解除
	UnregisterClass(m_strClassName.c_str(), GetModuleHandle(NULL));
}

//=============================================================================
// 生成処理
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
// 開放
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
void CWindow::Release()
{
	delete this;
}

//=============================================================================
// メッセージ処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
CWindow::Message CWindow::ProcMessage(MSG& msg)
{
	// メッセージがある場合処理
	Message message = MESSAGE_OK;
	BOOL bIsMessageExist = PeekMessage(&msg, 0, 0, 0, PM_REMOVE);
	if(TRUE == bIsMessageExist)
	{
		// 終了メッセージが送られた場合
		if(msg.message == WM_QUIT)
		{
			message = MESSAGE_TERMINATE;
		}
		// 送られていない場合
		else
		{
			// メッセージの翻訳と送出
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return message;
}

//=============================================================================
// ウィンドウハンドル取得
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
const HWND& CWindow::GetWindowHandle()
{
	return m_hWnd;
}

//=============================================================================
// ウィンドウ横幅取得
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
const DWORD& CWindow::GetWindowWidth()
{
	return m_uWindowWidth;
}

//=============================================================================
// ウィンドウ縦幅取得
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
const DWORD& CWindow::GetWindowHeight()
{
	return m_uWindowHeight;
}

//=============================================================================
// キャプション設定
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
void CWindow::SetCaption(const char* pCaption)
{
	m_strCaption = pCaption;
	// ウィンドウのキャプションを設定
	SetWindowText(m_hWnd, m_strCaption.c_str());
}

//=============================================================================
// 内部生成処理
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
	// ウィンドウ矩形範囲設定
	rc.top		= 0;
	rc.left		= 0;
	rc.right	= m_uWindowWidth;
	rc.bottom	= m_uWindowHeight;
	
	// ウィンドウクラス初期化
	WNDCLASSEX wcex = 
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		pWndProc,	// ウィンドウプロシージャ関数
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
	
	// ウィンドウクラス登録
	if(FAILED(RegisterClassEx(&wcex)))
	{
		MessageBox(NULL, "ウィンドウクラス登録失敗", "エラー", MB_OK);
		return E_FAIL;
	}
	
	// ウィンドウ幅合わせ
	AdjustWindowRect(
		&rc,		// ウィンドウ幅
		GAME_WINDOW, // ウィンドウスタイル
		FALSE);		// メニューの有無
	
	// ウィンドウ座標設定
	// タスクバーを除いたディスプレイ幅取得
	int nDisplayWidth = GetSystemMetrics(SM_CXFULLSCREEN);
	int nDisplayHeight = GetSystemMetrics(SM_CYFULLSCREEN);
	
	// ウィンドウ作成
	int nWindowWidth = rc.right - rc.left;	// ウィンドウ横幅
	int nWindowHeight = rc.bottom - rc.top;	// ウィンドウ縦幅
	int nWindowPosX = (nDisplayWidth >> 1) - (nWindowWidth >> 1);	// ウィンドウ左上X座標
	int nWindowPosY = (nDisplayHeight >> 1) - (nWindowHeight >> 1);	// ウィンドウ左上Y座標

	// ウィンドウの作成
	m_hWnd = CreateWindowEx(0,
		m_strClassName.c_str(),
		m_strCaption.c_str(),
		// 可変枠、最大化ボタンを取り除く
		GAME_WINDOW,
		nWindowPosX,
		nWindowPosY,
		nWindowWidth,
		nWindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);
	
	// 作成失敗表示
	if(!m_hWnd)
	{
		MessageBox(NULL, "ウィンドウ作成失敗", "エラー", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

//=============================================================================
// ウィンドウ表示
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//=============================================================================
void CWindow::ShowWindow()
{
	// ウィンドウ表示
	::ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
}

// EOF