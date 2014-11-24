//*****************************************************************************
//
// �L�[�{�[�h�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "interface/input/device/keyboard.h"
#include "interface/input/event_buffer.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CKeyboard::CKeyboard(CEventBuffer* event_buffer) : CInputDevice(event_buffer)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CKeyboard::~CKeyboard(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CKeyboard::Init(void)
{
	// �f�o�C�X���ʂ̏�����
	if(!CInputDevice::Init())
	{
		return false;
	}

	HRESULT hResult = E_FAIL;

	LPDIRECTINPUT8 direct_input = event_buffer_->direct_input();

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hResult = direct_input->CreateDevice(GUID_SysKeyboard,&direct_input_device_,NULL);

	if(FAILED(hResult))
	{
		return false;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hResult = direct_input_device_->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hResult))
	{
		return false;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hResult = direct_input_device_->SetCooperativeLevel(event_buffer_->window_data()->_hwnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));

	if(FAILED(hResult))
	{
		return false;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	direct_input_device_->Acquire();

	// �L�[�f�[�^�̏�����
	ZeroMemory(preview_key_,kKeyMax);

	return true;
}

//=============================================================================
// �X�V
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
		// �v���X�L�[�̎Z�o
		press_key = (key_state[i] & 0x80) ? true : false;

		// �g���K�[�L�[�̎Z�o
		trigger_key = (press_key ^ preview_key_[i]) & press_key;

		// �����[�X�L�[�̎Z�o
		release_key = (press_key ^ preview_key_[i]) & !press_key;

		// �v���r���[�L�[�̕ۑ�
		preview_key_[i] = press_key;

		// �C�x���g�o�b�t�@�Ƀf�[�^��ۑ����@�̌���
		event_buffer_->set_input_event_list(static_cast<INPUT_EVENT>(i),press_key,trigger_key,release_key);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CKeyboard::Uninit(void)
{
	CInputDevice::Uninit();
}

//---------------------------------- EOF --------------------------------------
