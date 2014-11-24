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
#include "interface/input/input_manager.h"
#include "interface/input/device/keyboard.h"
#include "interface/input/device/mouse.h"
#include "interface/input/event_buffer.h"
#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CInputManager::CInputManager(WINDOW_DATA* window_data)
{
	// �C�x���g�o�b�t�@�̐���
	event_buffer_ = new CEventBuffer(window_data);

	// �L�[�{�[�h�f�o�C�X�̐���
	device_list_.push_back(new CKeyboard(event_buffer_));

	// �}�E�X�f�o�C�X�̐���
	device_list_.push_back(new CMouse(event_buffer_));
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CInputManager::~CInputManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CInputManager::Init(void)
{
	// �C�x���g�o�b�t�@�̏�����
	if(!event_buffer_->Init())
	{
		return false;
	}

	// �f�o�C�X�̏�����
	for(auto it = device_list_.begin();it < device_list_.end();++it)
	{
		if(!(*it)->Init()) {
			return false;
		}
	}
	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CInputManager::Update(void)
{
	// �f�o�C�X�̏I��
	for(auto it = device_list_.begin();it < device_list_.end();++it)
	{
		(*it)->Update();
	}
}

//=============================================================================
// �I������
//=============================================================================
void CInputManager::Uninit(void)
{
	// �f�o�C�X�̏I��
	for(auto it = device_list_.begin();it < device_list_.end();++it)
	{
		(*it)->Uninit();
		delete (*it);
	}

	// �f�o�C�X�̔j��
	device_list_.clear();

	// �C�x���g�o�b�t�@�̏I��
	if(event_buffer_ != NULL)
	{
		event_buffer_->Uninit();
		delete event_buffer_;
		event_buffer_ = NULL;
	}
}

//=============================================================================
// �v���X�L�[�̊m�F����
//=============================================================================
bool CInputManager::CheckPress(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kPressBit ? true:false;
}

//=============================================================================
// �g���K�[�L�[�̊m�F��������
//=============================================================================
bool CInputManager::CheckTrigger(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kTriggerBit ? true:false;
}

//=============================================================================
// �����[�X�L�[�̊m�F��������
//=============================================================================
bool CInputManager::CheckRelease(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kReleaseBit ? true:false;
}

//=============================================================================
// ���s�[�g�L�[�̊m�F��������
//=============================================================================
bool CInputManager::CheckRepeat(INPUT_EVENT input_event)
{
	return event_buffer_->input_event_list(input_event) & kRepeatBit ? true:false;
}

//=============================================================================
// ���s�[�g�L�[�̊m�F��������
//=============================================================================
s32 CInputManager::GetValue(INPUT_EVENT_VALUE input_event_value)
{
	return event_buffer_->input_event_value_list(input_event_value);
}

//---------------------------------- EOF --------------------------------------
