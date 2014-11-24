//*****************************************************************************
//
// キーボードクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "interface/input/device/keyboard.h"
#include "interface/input/event_buffer.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CKeyboard::CKeyboard(CEventBuffer* event_buffer) : CInputDevice(event_buffer)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CKeyboard::~CKeyboard(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CKeyboard::Init(void)
{
	// デバイス共通の初期化
	if(!CInputDevice::Init())
	{
		return false;
	}

	HRESULT hResult = E_FAIL;

	LPDIRECTINPUT8 direct_input = event_buffer_->direct_input();

	// デバイスオブジェクトを作成
	hResult = direct_input->CreateDevice(GUID_SysKeyboard,&direct_input_device_,NULL);

	if(FAILED(hResult))
	{
		return false;
	}

	// データフォーマットを設定
	hResult = direct_input_device_->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hResult))
	{
		return false;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hResult = direct_input_device_->SetCooperativeLevel(event_buffer_->window_data()->_hwnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(FAILED(hResult))
	{
		return false;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	direct_input_device_->Acquire();

	// キーデータの初期化
	ZeroMemory(preview_key_,kKeyMax);

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CKeyboard::Update(void)
{
	u8 key_state[kKeyMax];
	bool press_key;
	bool trigger_key;
	bool release_key;

	if(FAILED(direct_input_device_->GetDeviceState(sizeof(key_state),key_state)))
	{
		ZeroMemory(key_state,sizeof(key_state));
		direct_input_device_->Acquire();
	}

	for(int i = 0;i < kKeyMax;++i)
	{
		// プレスキーの算出
		press_key = (key_state[i] & 0x80) ? true : false;

		// トリガーキーの算出
		trigger_key = (press_key ^ preview_key_[i]) & press_key;

		// リリースキーの算出
		release_key = (press_key ^ preview_key_[i]) & !press_key;

		// プレビューキーの保存
		preview_key_[i] = press_key;

		// イベントバッファにデータを保存方法の検討
		event_buffer_->set_input_event_list(static_cast<INPUT_EVENT>(i),press_key,trigger_key,release_key);
	}
}

//=============================================================================
// 終了
//=============================================================================
void CKeyboard::Uninit(void)
{
	CInputDevice::Uninit();
}

//---------------------------------- EOF --------------------------------------
