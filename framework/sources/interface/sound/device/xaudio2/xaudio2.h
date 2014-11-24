//*****************************************************************************
//
// XAudio���� [xaudio2.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/11(Thu)
// Version		: 1.00
// Update Date	: 2014/09/11(Thu)
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
#include "basic.h"
#include <xaudio2.h>

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
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);

	// �`�����N�f�[�^�̓ǂݍ���
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// XAudio2�̎擾
	IXAudio2* GetXAudio2(void){return m_pXAudio2;}

	// XAudio2�̎擾
	IXAudio2MasteringVoice* GetMasteringVoice(void){return m_pMasteringVoice;}

protected:

private:
	IXAudio2* m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X

	IXAudio2MasteringVoice* m_pMasteringVoice;		// �}�X�^�[�{�C�X
};

#endif // _XAUDIO_H_

//---------------------------------- EOF --------------------------------------
