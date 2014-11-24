//*****************************************************************************
//
// �C���v�b�g�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _INPUT_MANAGER_H_
#define _INPUT_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/basic.h"
#include "interface/input/input_alias.h"
#include "basic/main_window.h"
#include <vector>

//*****************************************************************************
// �O���錾
//*****************************************************************************
class CInputDevice;
class CEventBuffer;

//*****************************************************************************
// �C���v�b�g�}�l�[�W���[�N���X
//*****************************************************************************
class CInputManager : public CBasic
{
public:
	CInputManager(WINDOW_DATA* window_data);
	virtual ~CInputManager(void);

	// ����������
	bool Init(void);

	// �X�V����
	void Update(void);

	// �I������
	void Uninit(void);

	// �v���X�L�[�̊m�F
	bool CheckPress(INPUT_EVENT input_event);

	// �g���K�[�L�[�̊m�F
	bool CheckTrigger(INPUT_EVENT input_event);

	// �����[�X�L�[�̊m�F
	bool CheckRelease(INPUT_EVENT input_event);

	// ���s�[�g�L�[�̊m�F
	bool CheckRepeat(INPUT_EVENT input_event);

	// �C�x���g�o�����[�̒l���擾
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
