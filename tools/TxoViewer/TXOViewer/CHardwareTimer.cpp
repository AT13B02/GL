//=============================================================================
//
// �n�[�h�E�F�A�^�C�}�[�N���X [CHardwareTimer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CHardwareTimer.h"

//*****************************************************************************
// �ÓI�����o�ϐ�������
//*****************************************************************************
// �^�C�}�[�X�^�[�g�t���O
bool	CHardwareTimer::m_bTimerStarted = false;
// �^�C�}�[�G���h�t���O
bool	CHardwareTimer::m_bTimerEnded = false;

//=============================================================================
// �R���X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
CHardwareTimer::CHardwareTimer() :
m_uStart(0),
m_uEnd(0),
m_fFPS(0)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
CHardwareTimer::~CHardwareTimer()
{
}

//=============================================================================
// �^�C�}�[�Z�b�g�A�b�v
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
void CHardwareTimer::SetupTimer(void)
{
	if(!m_bTimerStarted)
	{
		timeBeginPeriod(1);
		m_bTimerStarted = true;
	}
}

//=============================================================================
// �^�C�}�[�G���h
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
void CHardwareTimer::EndTimer(void)
{
	if(!m_bTimerEnded)
	{
		timeEndPeriod(1);
		m_bTimerEnded = true;
	}
}

//=============================================================================
// ������
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
void CHardwareTimer::Init(void)
{
	m_uStart = m_uEnd = timeGetTime();
	m_fFPS = 0.0f;
}

//=============================================================================
// �X�V
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
bool CHardwareTimer::Update(void)
{
	m_uEnd = timeGetTime();

	if((m_uEnd - m_uStart) >= 1000.f / 60.f)
	{
		// FPS�ݒ�
		m_fFPS = 1000.f / (m_uEnd - m_uStart);
		// �J�n���Ԃ�ݒ�
		m_uStart = m_uEnd;

		// �^�C�}�[�o��
		return true;
	}

	// �^�C�}�[�o�߂��ĂȂ�
	return false;
}

//=============================================================================
// FPS�擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//=============================================================================
float CHardwareTimer::GetFPS(void)
{
	return m_fFPS;
}

// EOF