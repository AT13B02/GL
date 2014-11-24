//*****************************************************************************
//
// �C���v�b�g�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "interface/input/device/mouse.h"
#include "interface/input/event_buffer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMouse::CMouse(CEventBuffer* event_buffer) : CInputDevice(event_buffer)
{
	direct_input_device_ = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMouse::~CMouse(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CMouse::Init(void)
{
	HRESULT hresult = E_FAIL;

	// �f�o�C�X���ʂ̏�����
	if(!CInputDevice::Init())
	{
		return false;
	}

	if(direct_input_device_ == NULL)
	{
		// �f�o�C�X�̍쐬
		hresult = event_buffer_->direct_input()->CreateDevice(GUID_SysMouse,&direct_input_device_,NULL);

		// �G���[����
		if(FAILED(hresult))
		{
			return false;
		}
	}

	// �f�[�^�t�H�[�}�b�g�ݒ�
	hresult = direct_input_device_->SetDataFormat(&c_dfDIMouse2);

	// �G���[����
	if(FAILED(hresult))
	{
		return false;
	}

	// �������[�h�̐ݒ�(���̃A�v���P�[�V�����Ƃ̃f�o�C�X�̋��L���@)
	hresult = direct_input_device_->SetCooperativeLevel(event_buffer_->window_data()->_hwnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	// �G���[����
	if(FAILED(hresult))
	{
		return false;
	}

	// �}�E�X�ւ̃A�N�Z�X�����擾
	direct_input_device_->Acquire();

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CMouse::Update(void)
{
	POINT pos;
	DIMOUSESTATE2 temp_state = {NULL};

	// �}�E�X�̏��擾
	if(SUCCEEDED(direct_input_device_->GetDeviceState(sizeof(temp_state),&temp_state)))
	{
		// �X�N���[�����W�擾
		GetCursorPos(&pos);

		// �X�N���[�����W����N���C�A���g���W�ɕϊ�
		ScreenToClient(event_buffer_->window_data()->_hwnd,&pos);

		// ���W��ݒ�
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_X,pos.x);
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_Y,pos.y);

		// ������ݒ�
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_MOVE_X,temp_state.lX);
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_MOVE_Y,temp_state.lY);

		// �X�N���[���ʎ擾
		event_buffer_->set_input_event_value_list(INPUT_EVENT_VALUE_MOUSE_SCROLL,temp_state.lZ);
	}
	else
	{
		// �A�N�Z�X�����Ď擾
		direct_input_device_->Acquire();
	}

	for(int i = 0; i < kKeyMax;++i)
	{
		const bool press_key = (temp_state.rgbButtons[i] & kPushBit) ? true : false;

		// �g���K�[�L�[�̎Z�o
		const bool trigger_key = (preview_key_[i] ^ press_key) & press_key;

		// �����[�X�L�[�̎Z�o
		const bool release_key = (preview_key_[i] ^ press_key) & !press_key;

		// �v���r���[�L�[�̕ۑ�
		preview_key_[i] = press_key;

		event_buffer_->set_input_event_list(static_cast<INPUT_EVENT>(INPUT_EVENT_LCLICK + i),press_key,trigger_key,release_key);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CMouse::Uninit(void)
{
	CInputDevice::Uninit();
}

//EOF