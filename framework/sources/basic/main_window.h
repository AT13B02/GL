//*****************************************************************************
//
// メインウィンドウ処理
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <windows.h>
#include "basic.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _WINDOW_DATA
{
	HWND _hwnd;
	HINSTANCE _hinstance;
	WNDCLASSEX _wndclassex;
	u32 _width;
	u32 _height;
}WINDOW_DATA;

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CThread;
class CWindowData;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMainWindow : public CBasic
{
public:
	// コンストラクタ
	CMainWindow(HINSTANCE hinstance);

	// デストラクタ
	~CMainWindow(void);

	// 初期化処理
	bool Init(void);

	// 終了処理
	void Uninit(void);

	// メッセージの確認
	bool CheckMessage(void);

	// メッセージループフラグの確認
	bool message_loop_flag(void){return message_loop_flag_;}

	// ウィンドウハンドルの取得
	HWND hwnd(void){return hwnd_;}

	// インスタンスの取得
	HINSTANCE hinstance(void){return hinstance_;}

	// ウィンドウデータの取得
	WINDOW_DATA* window_data(void){return &window_data_;}

private:
	static const u32 DEFAULT_WIDTH;
	static const u32 DEFAULT_HEIGHT;
	static const s8* CLASS_NAME;
	static const s8* CAPTION_NAME;

	HWND hwnd_;
	HINSTANCE hinstance_;
	WNDCLASSEX wndclassex_;
	bool volatile message_loop_flag_;

	WINDOW_DATA window_data_;

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static void Message(CMainWindow* main_window);

};

#endif // _MAIN_WINDOW_H_

//-----------------------------------EOF---------------------------------------
