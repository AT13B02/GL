//=============================================================================
//
// �n�[�h�E�F�A�^�C�}�[�N���X [CHardwareTimer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//
//=============================================================================
#pragma once
#ifndef __KBR_CHARDWARE_TIMER_H__
#define __KBR_CHARDWARE_TIMER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>

//*****************************************************************************
// ���C�u���������N
//*****************************************************************************
#pragma comment (lib, "winmm.lib")	// ���ꂪ������time~�֐����g���Ȃ�

//*****************************************************************************
// �n�[�h�E�F�A�^�C�}�[�N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//*****************************************************************************
class CHardwareTimer
{
public:

	CHardwareTimer();

	~CHardwareTimer();

	// �^�C�}�[�Z�b�g�A�b�v
	static void SetupTimer(void);

	// �^�C�}�[�G���h
	static void EndTimer(void);

	// ������
	void Init(void);

	// �X�V
	bool Update(void);
	
	// FPS�擾
	float GetFPS(void);

private:

	// �^�C�}�[�X�^�[�g�t���O
	static bool	m_bTimerStarted;
	// �^�C�}�[�G���h�t���O
	static bool	m_bTimerEnded;

	// �J�n����
	DWORD	m_uStart;
	// �I������
	DWORD	m_uEnd;
	// FPS
	float m_fFPS;
};

#endif	// __KBR_CHARDWARE_TIMER_H__

// EOF