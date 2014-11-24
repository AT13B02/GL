//*****************************************************************************
//
// メインウィンドウ処理
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "main_window.h"
#include "common/thread/thread.h"
#include "common/common.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const u32 CMainWindow::DEFAULT_WIDTH = DEFAULT_SCREEN_WIDTH;	// 横幅
const u32 CMainWindow::DEFAULT_HEIGHT = DEFAULT_SCREEN_HEIGHT;	// 縦幅
const s8* CMainWindow::CLASS_NAME = "MainWindow";				// クラス名
const s8* CMainWindow::CAPTION_NAME = "framework";				// キャプション名

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CMainWindow::CMainWindow(HINSTANCE hinstance)
{
	WNDCLASSEX wndclassex =
	{
		sizeof(WNDCLASSEX),				// 構造体のサイズ
		CS_CLASSDC,						// スタイル
		WindowProcedure,				// プロシージャの関数ポインタ
		0,								// 
		0,								// 
		hinstance,						// インスタンス
		NULL,							// アイコン
		LoadCursor(NULL, IDC_ARROW),	// マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),		// 背景色
		NULL,							// メニュー
		CLASS_NAME,						// ウィンドウのクラス名
		NULL							// アイコン
	};

	message_loop_flag_ = true;

	window_data_._hinstance = hinstance;
	window_data_._wndclassex = wndclassex;
	window_data_._width = DEFAULT_WIDTH;
	window_data_._height = DEFAULT_HEIGHT;

	// ウィンドウクラスの登録
	RegisterClassEx(&wndclassex);

	// ウィンドウの作成
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
// デストラクタ
//=============================================================================
CMainWindow::~CMainWindow(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CMainWindow::Init(void)
{
	message_loop_flag_ = true;

	// ウインドウの表示
	ShowWindow(window_data_._hwnd,SW_SHOW);

	// ウィンドウの更新開始
	UpdateWindow(window_data_._hwnd);

	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMainWindow::Uninit(void)
{
	// ウィンドウクラスの破棄
	UnregisterClass(CLASS_NAME,window_data_._hinstance);
}

//=============================================================================
// メッセージの確認
//=============================================================================
bool CMainWindow::CheckMessage(void)
{
	MSG msg;
	bool bMessageFlag = PeekMessage(&msg,NULL,0,0,PM_REMOVE) == TRUE;

	if(bMessageFlag)
	{
		// PostQuitMessage()が呼ばれたらループ終了
		if(msg.message == WM_QUIT)
		{
			message_loop_flag_ = false;
		}
		else
		{
			// メッセージの翻訳と送出
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return bMessageFlag;
}

//=============================================================================
// ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK CMainWindow::WindowProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:			// ウィンドウを破棄
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:			// キー入力
		switch(wParam)
		{
		case VK_ESCAPE:			// エスケープキー
			// ウィンドウの破棄
			DestroyWindow(hWnd);
			break;
		case VK_INSERT:			// インサートキー
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//=============================================================================
// ウィンドウプロシージャ
//=============================================================================
void CMainWindow::Message(CMainWindow* main_window)
{
	MSG msg;

	while(main_window->message_loop_flag_)
	{
		GetMessage(&msg,NULL,0,0);

		// PostQuitMessage()が呼ばれたらループ終了
		if(msg.message == WM_QUIT)
		{
			main_window->message_loop_flag_ = false;
		}
		else
		{
			// メッセージの翻訳と送出
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

//-----------------------------------EOF---------------------------------------
