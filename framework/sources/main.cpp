//*****************************************************************************
//
// メイン処理
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/application_manager.h"

#include "debug_tool/debug_manager.h"
#include "debug_tool/debug_console.h"
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
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE preview_hinstance, LPSTR command_line,int command_show)
{
#ifdef _DEBUG
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// 未使用宣言
	UNREFERENCED_PARAMETER(preview_hinstance);
	UNREFERENCED_PARAMETER(command_line);
	UNREFERENCED_PARAMETER(command_show);

	// アプリケーションマネージャー
	CApplicationManager* application_manager = NULL;

	// アプリケーションマネージャーの生成
	application_manager = new CApplicationManager(hinstance);

	// デバッグの初期化
	CDebugManager::instance()->set_application_manager(application_manager);

	// デバッグ開始
	CDebugManager::Run();

	// アプリケーションマネージャーの初期化
	if(application_manager->Init())
	{
		// アプリケーションマネージャーの更新
		application_manager->Run();
	}
	else
	{
		// アプリケーションの初期化失敗
	}

	// デバッグ終了
	CDebugManager::Stop();

	// アプリケーションマネージャーの開放
	SAFE_RELEASE(application_manager);

	return 0;
}

//---------------------------------- EOF --------------------------------------
