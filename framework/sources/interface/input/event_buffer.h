//*****************************************************************************
//
// �C���v�b�g�C�x���g�o�b�t�@�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _EVENT_BUFFER_H_
#define _EVENT_BUFFER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "interface/input/input_alias.h"
#include "basic/main_window.h"
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>

//*****************************************************************************
// �C���v�b�g�C�x���g�o�b�t�@�N���X
//*****************************************************************************
class CEventBuffer
{
public:
	// �R���X�g���N�^
	CEventBuffer(WINDOW_DATA* window_data);

	// �f�X�g���N�^
	virtual ~CEventBuffer(void);

	// ������
	bool Init(void);

	// �I��
	void Uninit(void);

	// �_�C���N�g�C���v�b�g�̎擾
	LPDIRECTINPUT8 direct_input(void){return direct_input_;}

	// �C���v�b�g�C�x���g�f�[�^�̎擾
	u8 input_event_list(INPUT_EVENT input_event){return input_event_list_[input_event];}

	// �C���v�b�g�C�x���g�f�[�^�̊i�[
	void set_input_event_list(INPUT_EVENT input_event,bool press,bool trigger,bool release)
	{
		input_event_list_[input_event] = (press << 0) + (trigger << 1) + (release << 2); 
	}

	// �C���v�b�g�C�x���g�o�����[�f�[�^�̎擾
	s32 input_event_value_list(INPUT_EVENT_VALUE input_event_value){return input_event_value_list_[input_event_value];}

	// �C���v�b�g�C�x���g�o�����[�f�[�^�̐ݒ�
	void set_input_event_value_list(INPUT_EVENT_VALUE input_event_value,s32 value){ input_event_value_list_[input_event_value] = value; };

	// �E�B���h�E�n���h���̎擾
	WINDOW_DATA* window_data(void){return window_data_;}

 private:
	LPDIRECTINPUT8 direct_input_;
	u8 input_event_list_[INPUT_EVENT_MAX];
	s32 input_event_value_list_[INPUT_EVENT_VALUE_MAX];
	WINDOW_DATA* window_data_;
};

#endif // _EVENT_BUFFER_H_

//-----------------------------------EOF---------------------------------------
