//*****************************************************************************
//
// インプットマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/basic.h"
#include "interface/input/input_alias.h"
#include "basic/main_window.h"
#include <vector>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CInputDevice;
class CEventBuffer;

//*****************************************************************************
// インプットマネージャークラス
//*****************************************************************************
class CInputManager : public CBasic
{
public:
	CInputManager(WINDOW_DATA* window_data);
	virtual ~CInputManager(void);

	// 初期化処理
	bool Init(void);

	// 更新処理
	void Update(void);

	// 終了処理
	void Uninit(void);

	// プレスキーの確認
	bool CheckPress(INPUT_EVENT input_event);

	// トリガーキーの確認
	bool CheckTrigger(INPUT_EVENT input_event);

	// リリースキーの確認
	bool CheckRelease(INPUT_EVENT input_event);

	// リピートキーの確認
	bool CheckRepeat(INPUT_EVENT input_event);

	// イベントバリューの値を取得
	s32 GetValue(INPUT_EVENT_VALUE input_event_value);

private:
	static const u8 kPressBit = 0x01;
	static const u8 kTriggerBit = 0x02;
	static const u8 kReleaseBit = 0x04;
	static const u8 kRepeatBit = 0x08;

	std::vector<CInputDevice*> device_list_;

	CEventBuffer* event_buffer_;
};

#endif // _INPUT_MANAGER_H_

//-----------------------------------EOF---------------------------------------
