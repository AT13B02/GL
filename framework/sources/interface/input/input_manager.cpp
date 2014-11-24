//*****************************************************************************
//
// インプットマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "interface/input/input_manager.h"
#include "interface/input/device/keyboard.h"
#include "interface/input/device/mouse.h"
#include "interface/input/event_buffer.h"
#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CInputManager::CInputManager(WINDOW_DATA* window_data)
{
	// イベントバッファの生成
	event_buffer_ = new CEventBuffer(window_data);

	// キーボードデバイスの生成
	device_list_.push_back(new CKeyboard(event_buffer_));

	// マウスデバイスの生成
	device_list_.push_back(new CMouse(event_buffer_));
}

//=============================================================================
// デストラクタ
//=============================================================================
CInputManager::~CInputManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CInputManager::Init(void)
{
	// イベントバッファの初期化
	if(!event_buffer_->Init())
	{
		return false;
	}

	// デバイスの初期化
	for(auto it = device_list_.begin();it < device_list_.end();++it)
	{
		if(!(*it)->Init()) {
			return false;
		}
	}
	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CInputManager::Update(void)
{
	// デバイスの終了
	for(auto it = device_list_.begin();it < device_list_.end();++it)
	{
		(*it)->Update();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CInputManager::Uninit(void)
{
	// デバイスの終了
	for(auto it = device_list_.begin();it < device_list_.end();++it)
	{
		(*it)->Uninit();
		delete (*it);
	}

	// デバイスの破棄
	device_list_.clear();

	// イベントバッファの終了
	if(event_buffer_ != NULL)
	{
		event_buffer_->Uninit();
		delete event_buffer_;
		event_buffer_ = NULL;
	}
}

//=============================================================================
// プレスキーの確認処理
//=============================================================================
bool CInputManager::CheckPress(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kPressBit ? true:false;
}

//=============================================================================
// トリガーキーの確認処理処理
//=============================================================================
bool CInputManager::CheckTrigger(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kTriggerBit ? true:false;
}

//=============================================================================
// リリースキーの確認処理処理
//=============================================================================
bool CInputManager::CheckRelease(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kReleaseBit ? true:false;
}

//=============================================================================
// リピートキーの確認処理処理
//=============================================================================
bool CInputManager::CheckRepeat(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kRepeatBit ? true:false;
}

//=============================================================================
// リピートキーの確認処理処理
//=============================================================================
s32 CInputManager::GetValue(INPUT_EVENT_VALUE input_event_value)
{
	return event_buffer_->input_event_value_list(input_event_value);
}

//---------------------------------- EOF --------------------------------------
