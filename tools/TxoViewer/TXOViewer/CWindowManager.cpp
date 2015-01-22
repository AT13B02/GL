//=============================================================================
//
// ウィンドウマネージャクラス [CWindowManager.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CWindowManager.h"
#include "CWindow.h"
#include <fstream>
#include "Debug.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CWindowManager::CWindowManager()
	:	m_uNumWindow(0),
		m_ppWindow(0)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CWindowManager::~CWindowManager()
{
}

//=============================================================================
// 生成
//=============================================================================
bool CWindowManager::Create(CWindowManager** ppManager)
{
	(*ppManager) = new CWindowManager();

	if(nullptr == (*ppManager))
	{
		_Assert((*ppManager));
		return false;
	}

	return true;
}

//=============================================================================
// 開放
//=============================================================================
void CWindowManager::Release()
{
	for(int i = 0; i < m_uNumWindow; i++)
	{
		m_ppWindow[i]->Release();
		m_ppWindow[i] = nullptr;
	}
	
	delete[] m_ppWindow;
	m_ppWindow = nullptr;
	m_uNumWindow = 0;

	delete this;
}

//=============================================================================
// ウィンドウを追加
//=============================================================================
const int CWindowManager::Add(const char* pFileName)
{
	// 新しいウィンドウ配列を作る
	CWindow** ppNewWindow = new CWindow*[m_uNumWindow + 1];
	
	if(nullptr != m_ppWindow)
	{
		for(int i = 0; i < m_uNumWindow; i++)
		{
			ppNewWindow[i] = m_ppWindow[i];
		}

		delete[] m_ppWindow;
		m_ppWindow = nullptr;
	}

	m_ppWindow = ppNewWindow;
	m_uNumWindow = m_uNumWindow + 1;

	// ウィンドウ生成
	return CreateNewWindow(pFileName);
}

//=============================================================================
// 新しいウィンドウの生成
// Author : Ryo Kobayashi
// Last Update : 2014/6/8
//=============================================================================
const int CWindowManager::Add(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight)
{
	// 新しいウィンドウ配列を作る
	CWindow** ppNewWindow = new CWindow*[m_uNumWindow + 1];
	
	if(nullptr != m_ppWindow)
	{
		for(int i = 0; i < m_uNumWindow; i++)
		{
			ppNewWindow[i] = m_ppWindow[i];
		}

		delete[] m_ppWindow;
		m_ppWindow = nullptr;
	}

	m_ppWindow = ppNewWindow;
	m_uNumWindow = m_uNumWindow + 1;

	// ウィンドウ生成
	return CreateNewWindow(pCaption, pClassName, uWidth, uHeight);
}

//=============================================================================
// メッセージ処理
//=============================================================================
CWindow::Message CWindowManager::ProcMessage(const unsigned uIndex, MSG& msg)
{
	return m_ppWindow[uIndex]->ProcMessage(msg);
}

//=============================================================================
// ウィンドウハンドル取得
//=============================================================================
const HWND& CWindowManager::GetWindowHandle(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->GetWindowHandle();
}

//=============================================================================
// ウィンドウ横幅取得
//=============================================================================
const DWORD& CWindowManager::GetWindowWidth(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->GetWindowWidth();
}

//=============================================================================
// ウィンドウ縦幅取得
//=============================================================================
const DWORD& CWindowManager::GetWindowHeight(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->GetWindowHeight();
}

//=============================================================================
// キャプション設定
//=============================================================================
void CWindowManager::SetCaption(const unsigned uIndex,const char* pCaption)
{
	return m_ppWindow[uIndex]->SetCaption(pCaption);
}

//=============================================================================
// ウィンドウ表示
//=============================================================================
void CWindowManager::ShowWindow(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->ShowWindow();
}

//=============================================================================
// ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK CWindowManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// メッセージによって分岐
	switch(uMsg)
	{
		// ウィンドウ破棄
	case WM_DESTROY:
		// 終了メッセージ送出
		PostQuitMessage(0);
		break;

		// キー入力
	case WM_KEYDOWN:
		// キー入力処理
		KeyInputProc(hWnd, wParam);
		break;
		
		// ウィンドウサイズ変更時
	case WM_SIZE:
		break;
		
	default:
		break;
	}

	// 標準処理に投げる
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// 新しいウィンドウの生成
// Author : Ryo Kobayashi
// Last Update : 2014/6/8
//=============================================================================
const int CWindowManager::CreateNewWindow(const char* pFileName)
{
	int nNewWindowIndex = (int)m_uNumWindow - 1;

	unsigned uWindowWidth = 800;
	unsigned uWindowHeight = 600;
	char aCaption[256] = "WINDOW";
	char aClassName[256] = "WINDOW_CLASS";

	std::ifstream ifs(pFileName);

	if(ifs.is_open())
	{
		ifs >> uWindowWidth;
		ifs.ignore(10, '\n');
		ifs >> uWindowHeight;
		ifs.ignore(10, '\n');
		ifs >> aCaption;
		ifs.ignore(10, '\n');
		ifs >> aClassName;
		ifs.ignore(10, '\n');
	}

	// 生成
	if(FAILED(CWindow::Create(uWindowWidth, uWindowHeight, aCaption, aClassName, WndProc, &m_ppWindow[nNewWindowIndex])))
	{
		return -1;
	}

	return m_uNumWindow;
}

//=============================================================================
// 新しいウィンドウ生成
// Author : Ryo Kobayashi
// Last Update : 2014/12/15
//=============================================================================
const int CWindowManager::CreateNewWindow(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight)
{
	int nNewWindowIndex = (int)m_uNumWindow - 1;

	if(!pCaption)
	{
		pCaption = "WINDOW";
	}
	if(!pClassName)
	{
		pClassName = "WINDOW_CLASS";
	}

	// 生成
	if(FAILED(CWindow::Create(uWidth, uHeight, pCaption, pClassName, WndProc, &m_ppWindow[nNewWindowIndex])))
	{
		return -1;
	}

	return m_uNumWindow;
}

//=============================================================================
// キー入力処理
// Author : Ryo Kobayashi
// Last Update : 2014/6/8
//=============================================================================
void CWindowManager::KeyInputProc(HWND hWnd, WPARAM wParam)
{
	switch(wParam)
	{
		// エスケープが押されたとき
	case VK_ESCAPE:
		if(IDYES == MessageBox(NULL, "終了しますか？", "", MB_YESNO))
		{
			DestroyWindow(hWnd);	// 親ウィンドウのハンドルを取得
		}
		break;
	}
}

// EOF