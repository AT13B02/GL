//*****************************************************************************
//
// XAudio2�T�E���h���� [xaudio2_sound.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/03/28(Fri)
// Version		: 1.00
// Update Date	: 2014/09/11(Thu)
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _XAUDIO2_SOUND_H_
#define _XAUDIO2_SOUND_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "sound.h"
#include <xaudio2.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CSoundDevice;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CXAudio2Sound : public CSound
{
public:
	// �R���X�g���N�^
	CXAudio2Sound(CSoundDevice* pSoundDevice);

	// �f�X�g���N�^
	virtual ~CXAudio2Sound(void);

	// ������
	bool Init(void);

	// �I��
	void Uninit(void);

	// ���[�h
	bool Load(const char* pFilename);

	// �Đ�
	void Play(bool bLoopFlag);

	// ��~
	void Stop(void);

	// �ꎞ��~
	void Pause(void);

	// ��Ԃ̎擾
	bool GetStatus(void){return m_bPlayFlag;}
	// �{�����[���̐ݒ�
	//void SetVolume();

protected:

private:
	// �T�E���h�f�o�C�X
	CSoundDevice* m_pSoundDevice;

	// �v���C�t���O
	bool m_bPlayFlag;

	int m_nSoundId;											// �T�E���hID
	IXAudio2SourceVoice* m_pSourceVoice;					// �\�[�X�{�C�X
	BYTE* m_pDataAudio;										// �I�[�f�B�I�f�[�^
	DWORD m_SizeAudio;										// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif // _XAUDIO2_SOUND_H_

//---------------------------------- EOF --------------------------------------
