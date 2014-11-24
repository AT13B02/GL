//*****************************************************************************
//
// インプットイベントバッファクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _EVENT_BUFFER_H_
#define _EVENT_BUFFER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "interface/input/input_alias.h"
#include "basic/main_window.h"
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//*****************************************************************************
// インプットイベントバッファクラス
//*****************************************************************************
class CEventBuffer
{
public:
	// コンストラクタ
	CEventBuffer(WINDOW_DATA* window_data);

	// デストラクタ
	virtual ~CEventBuffer(void);

	// 初期化
	bool Init(void);

	// 終了
	void Uninit(void);

	// ダイレクトインプットの取得
	LPDIRECTINPUT8 direct_input(void){return direct_input_;}

	// インプットイベントデータの取得
	u8 input_event_list(INPUT_EVENT input_event){return input_event_list_[input_event];}

	// インプットイベントデータの格納
	void set_input_event_list(INPUT_EVENT input_event,bool press,bool trigger,bool release)
	{
		input_event_list_[input_event] = (press << 0) + (trigger << 1) + (release << 2); 
	}

	// インプットイベントバリューデータの取得
	s32 input_event_value_list(INPUT_EVENT_VALUE input_event_value){return input_event_value_list_[input_event_value];}

	// インプットイベントバリューデータの設定
	void set_input_event_value_list(INPUT_EVENT_VALUE input_event_value,s32 value){ input_event_value_list_[input_event_value] = value; };

	// ウィンドウハンドルの取得
	WINDOW_DATA* window_data(void){return window_data_;}

 private:
	LPDIRECTINPUT8 direct_input_;
	u8 input_event_list_[INPUT_EVENT_MAX];
	s32 input_event_value_list_[INPUT_EVENT_VALUE_MAX];
	WINDOW_DATA* window_data_;
};

#endif // _EVENT_BUFFER_H_

//-----------------------------------EOF---------------------------------------
