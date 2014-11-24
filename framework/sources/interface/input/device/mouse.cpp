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
#include "interface/input/device/mouse.h"
#include "interface/input/event_buffer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CMouse::CMouse(CEventBuffer* event_buffer) : CInputDevice(event_buffer)
{
	direct_input_device_ = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CMouse::~CMouse(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CMouse::Init(void)
{
	HRESULT hresult = E_FAIL;

	// デバイス共通の初期化
	if(!CInputDevice::Init())
	{
		return false;
	}

	if(direct_input_device_ == NULL)
	{
		// デバイスの作成
		hresult = event_buffer_->direct_input()->CreateDevice(GUID_SysMouse,&direct_input_device_,NULL);

		// エラー処理
		if(FAILED(hresult))
		{
			return false;
		}
	}

	// データフォーマット設定
	hresult = direct_input_device_->SetDataFormat(&c_dfDIMouse2);

	// エラー処理
	if(FAILED(hresult))
	{
		return false;
	}

	// 協調モードの設定(他のアプリケーションとのデバイスの共有方法)
	hresult = direct_input_device_->SetCooperativeLevel(event_buffer_->window_data()->_hwnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// エラー処理
	if(FAILED(hresult))
	{
		return false;
	}

	// マウスへのアクセス権を取得
	direct_input_device_->Acquire();

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CMouse::Update(void)
{
	POINT pos;
	DIMOUSESTATE2 temp_state = {NULL};

	// マウスの情報取得
	if(SUCCEEDED(direct_input_device_->GetDeviceState(sizeof(temp_state),&temp_state)))
	{
		// スクリーン座標取得
		GetCursorPos(&pos);

		// スクリーン座標からクライアント座標に変換
		ScreenToClient(event_buffer_->window_data()->_hwnd,&pos);

		// 座標を設定
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_X,pos.x);
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_Y,pos.y);

		// 差分を設定
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_MOVE_X,temp_state.lX);
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_MOVE_Y,temp_state.lY);

		// スクロール量取得
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_SCROLL,temp_state.lZ);
	}
	else
	{
		// アクセス権を再取得
		direct_input_device_->Acquire();
	}

	for(int i = 0; i < kKeyMax;++i)
	{
		const bool press_key = (temp_state.rgbButtons[i] & kPushBit) ? true : false;

		// トリガーキーの算出
		const bool trigger_key = (preview_key_[i] ^ press_key) & press_key;

		// リリースキーの算出
		const bool release_key = (preview_key_[i] ^ press_key) & !press_key;

		// プレビューキーの保存
		preview_key_[i] = press_key;

		event_buffer_->set_input_event_list(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),press_key,trigger_key,release_key);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CMouse::Uninit(void)
{
	CInputDevice::Uninit();
}

//EOF