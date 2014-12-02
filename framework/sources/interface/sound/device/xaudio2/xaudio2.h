//*****************************************************************************
//
// XAudio�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _XAUDIO_H_
#define _XAUDIO_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <xaudio2.h>

// basic
#include "basic/basic.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CXAudio2 : public CBasic
{
public:
	// �R���X�g���N�^
	CXAudio2(void);

	// �f�X�g���N�^
	virtual ~CXAudio2(void);

	// ������
	bool Init(void);

	// �I��
	void Uninit(void);

	// �`�����N�̃`�F�b�N
	HRESULT CheckChunk(HANDLE h_file, DWORD format, DWORD *chunk_size, DWORD *chunk_data_position);

	// �`�����N�f�[�^�̓ǂݍ���
	HRESULT ReadChunkData(HANDLE h_file, void* buffer, DWORD buffer_size, DWORD buffer_offset);

	// XAudio2�̎擾
	IXAudio2* x_audio2(void){return xaudio2_;}

	// XAudio2�̎擾
	IXAudio2MasteringVoice* mastering_voice(void){return mastering_voice_;}

protected:

private:
	IXAudio2* xaudio2_;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X

	IXAudio2MasteringVoice* mastering_voice_;		// �}�X�^�[�{�C�X
};

#endif // _XAUDIO_H_

//---------------------------------- EOF --------------------------------------
