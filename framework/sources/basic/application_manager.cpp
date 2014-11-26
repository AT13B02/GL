//*****************************************************************************
//
// アプリケーションマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "fps_manager.h"
#include "main_window.h"
#include "application_manager.h"
#include "scene/scene_manager.h"
#include "interface/interface_manager.h"

#include "common/thread/thread.h"
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
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

	// メインウィンドウの作成
	main_window_ = new CMainWindow(hinstance);

	// ウィンドウハンドルの取得
	hwnd_ = main_window_->hwnd();

	// FPSマネージャーの生成
	fps_manager_ = new CFpsManager();

	// インターフェースマネージャーの生成
	interface_manager_ = new CInterfaceManager(main_window_->window_data());

	// シーンマネージャーの生成
	scene_manager_ = new CSceneManager(interface_manager_);

	// スレッドの生成
	thread_ = new CThread();
}

//=============================================================================
// デストラクタ
//=============================================================================
CApplicationManager::~CApplicationManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CApplicationManager::Init(void)
{
	// ループフラグを立てる
	loop_flag_ = true;

	// 更新フラグを立てる
	update_flag_ = true;

	// メインウィンドウの初期化
	main_window_->Init();

	// スレッドの初期化
	thread_->Init();

	// FPSマネージャーの初期化
	INIT(fps_manager_);

	// インターフェースマネージャーの初期化
	INIT(interface_manager_);

	// シーンマネージャーの初期化
	INIT(scene_manager_);

	// スレッドの開始
	thread_->Start(Thread,this);

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CApplicationManager::Update(void)
{
	// FPSの確認
	if(fps_manager_->CheckFps())
	{
		// FPS管理の更新
		fps_manager_->Update();

		// インターフェースマネージャーの更新
		if(interface_manager_ != NULL)
		{
			interface_manager_->Update();
		}

		// 更新フラグを確認
		if(update_flag_)
		{
			// シーンの更新
			if(scene_manager_ != NULL)
			{
				scene_manager_->Update();
			}
		}

		// シーンの描画
		if(scene_manager_ != NULL)
		{
			scene_manager_->Draw();
		}

		// インターフェースマネージャーの描画
		if(interface_manager_ != NULL)
		{
			interface_manager_->Draw();
		}

		// デバッグマネージャーの更新
		DEBUG_TOOL.UpdateMessage();
	}
}

//=============================================================================
// 終了
//=============================================================================
void CApplicationManager::Uninit(void)
{
	loop_flag_ = false;

	update_flag_ = false;

	// ウィンドウの開放
	SAFE_RELEASE(main_window_);

	// スレッドの開放
	SAFE_RELEASE(thread_);

	// FPS管理の終了
	SAFE_RELEASE(fps_manager_);

	// シーンマネージャーの破棄
	SAFE_RELEASE(scene_manager_);

	// インターフェースマネージャーの破棄
	SAFE_RELEASE(interface_manager_);
}

//=============================================================================
// ループ
//=============================================================================
void CApplicationManager::Run(void)
{
	// メッセージループ
	while(main_window_->message_loop_flag())
	{
		// メッセージの確認
		main_window_->CheckMessage();
	}
}

//=============================================================================
// スレッド処理
//=============================================================================
void CApplicationManager::Thread(CApplicationManager* application_manager)
{
	// メインループ
	while(application_manager->loop_flag_)
	{
		// アプリケーションの更新
		application_manager->Update();
	}
}

//---------------------------------- EOF --------------------------------------
