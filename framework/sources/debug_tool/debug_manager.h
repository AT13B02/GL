//*****************************************************************************
//
// デバッグマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _DEBUG_MANAGER_H_
#define _DEBUG_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/basic.h"
#include "debug_tool/debug_console.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CApplicationManager;
class CDebugConsole;
class CThread;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDebugManager : public CBasic
{
public:
	// デバッグスレッドを立てる
	static void Run(void);

	// デバッグスレッドを立てる
	static void Stop(void){instance_.is_run_ = false;}

	// インスタンスの取得
	static CDebugManager* instance(void){return &instance_;}

	// 更新メッセージ
	void UpdateMessage(void){is_update_ = true;}

	// アプリケーションマネージャーの設定
	void set_application_manager(CApplicationManager* application_manger){application_manager_ = application_manger;}

	// デバッグコンソールの取得
	CDebugConsole* debug_console(void){return debug_console_;}
protected:

private:
	// コンストラクタ
	CDebugManager(void);
	// デストラクタ
	~CDebugManager(void);

	// 初期化
	bool Init(void);
	// 更新
	void Update(void);
	// 描画
	void Draw(void);
	// 終了
	void Uninit(void);

	static CDebugManager instance_;
	volatile bool is_run_;
	volatile bool is_update_;

	CDebugConsole* debug_console_;
	CThread* thread_;
	CApplicationManager* application_manager_;
	static void Thread(void);
};

#endif // _DEBUG_MANAGER_H_

//---------------------------------- EOF --------------------------------------
