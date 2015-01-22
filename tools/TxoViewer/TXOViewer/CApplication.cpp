//=============================================================================
//
// アプリケーションクラス [CApplication.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CApplication.h"
#include "CWindowManager.h"
#include "CRenderer.h"
#include "CManager.h"
#include "CHardwareTimer.h"
#include "Debug.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CApplication::CApplication()
	:	m_pWindowManager(nullptr),
	m_pRenderer(nullptr),
	m_pManager(nullptr),
	m_pArg(nullptr)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CApplication::~CApplication()
{
}

//=============================================================================
// アプリケーションスタート
//=============================================================================
int CApplication::Run(const char* pArg)
{
	CApplication* pApp;
	bool bFlase = false;
	bFlase = Create(pArg, &pApp);
	if(nullptr == pApp)
	{
		return -1;
	}
	else if(false == bFlase)
	{
		pApp->Release();
		return -1;
	}
	
	MSG Msg;					// メッセージ構造体
	Msg.message = WM_NULL;		// ヌルクリア

	CWindow* pWindow = pApp->m_pWindowManager->GetWindow(0);

	// ウィンドウ表示
	pWindow->ShowWindow();
	
	// タイマー
	CHardwareTimer timer;
	timer.SetupTimer();

	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		// 終了
		if(CWindow::MESSAGE_TERMINATE == pWindow->ProcMessage(Msg))
		{
			bLoopFlag = false;
		}
		// 更新
		else if(timer.Update())
		{
#ifdef _DEBUG
			char aCap[256];

			sprintf_s(aCap, 255, "%f", timer.GetFPS());

			// ウィンドウのキャプションをFPS
			pWindow->SetCaption(aCap);
#endif
			pApp->Update();
		}
	}

	// アプリケーション開放
	pApp->Release();
	
	// タイマー終了
	timer.EndTimer();

	// メッセージを返す
	return (int)Msg.wParam;
}

//=============================================================================
// 生成
//=============================================================================
bool CApplication::Create(const char* pArg, CApplication** ppApplication)
{
	(*ppApplication) = new CApplication();
	
	if(nullptr == (*ppApplication))
	{
		_AssertExpr(0, "アプリケーションの生成に失敗");
		return false;
	}

	return (*ppApplication)->Initialize(pArg);
}

//=============================================================================
// 初期化
//=============================================================================
bool CApplication::Initialize(const char* pArg)
{
	m_pArg = pArg;

	if(false == CWindowManager::Create(&m_pWindowManager))
	{
		return false;
	}
	m_pWindowManager->Add("TxoViewer", "kbr_txo_viewer", 512, 512);

	// レンダラ生成
	if(FAILED(CRenderer::Create(
		m_pWindowManager->GetWindowHandle(0),
		FALSE,
		m_pWindowManager->GetWindowWidth(0),
		m_pWindowManager->GetWindowHeight(0),
		&m_pRenderer)))
	{
		return false;
	}

	// マネージャ生成
	if(FAILED(CManager::Create(
		GetModuleHandle(NULL),
		this,
		&m_pManager)))
	{
		return false;
	}

	return true;
}

//=============================================================================
// 開放
//=============================================================================
void CApplication::Release()
{
	m_pManager->Release();
	m_pRenderer->Release();
	m_pWindowManager->Release();

	delete this;
}

//=============================================================================
// 更新
//=============================================================================
void CApplication::Update()
{
	// マネージャー更新
	m_pManager->Update();
	// マネージャー描画
	m_pManager->Draw();
}

// EOF