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
// �C���N���[�h
//*****************************************************************************
#include "sound.h"
#include "xaudio2_sound.h"
#include "sound_device.h"
#include "xaudio2.h"

#include "common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CXAudio2Sound::CXAudio2Sound(CSoundDevice* pSoundDevice)
{
	m_bPlayFlag = false;

	m_nSoundId = -1;

	m_pSourceVoice = NULL;

	m_pDataAudio = NULL;

	m_SizeAudio = 0;

	m_pSoundDevice = pSoundDevice;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CXAudio2Sound::~CXAudio2Sound(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CXAudio2Sound::Init(void)
{
	CSound::Init();

	m_nSoundId = -1;

	m_pSourceVoice = NULL;

	m_pDataAudio = NULL;

	m_SizeAudio = 0;

	m_bPlayFlag = false;

	return true;
}

//=============================================================================
// �I������
//=============================================================================
void CXAudio2Sound::Uninit(void)
{
	// ��~
	Stop();

	// �\�[�X�{�C�X�̔j��
	if(m_pSourceVoice != NULL)
	{
		m_pSourceVoice->DestroyVoice();
		m_pSourceVoice = NULL;

		// �I�[�f�B�I�f�[�^�̊J��
		SAFE_DELETE(m_pDataAudio);
	}

	CSound::Uninit();
}

//=============================================================================
// ���[�h����
//=============================================================================
bool CXAudio2Sound::Load(const char* pFilename)
{
	HANDLE hFile;
	HRESULT hr;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �t�@�C�����̕ۑ�
	SetFilename(pFilename);

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// �t�@�C���|�C���^��擪�Ɉړ�
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return false;
	}
	
	// WAVE�t�@�C���̃`�F�b�N
	hr = m_pSoundDevice->GetDevice()->CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}

	hr = m_pSoundDevice->GetDevice()->ReadChunkData(hFile,&dwFiletype,sizeof(DWORD),dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}
	if(dwFiletype != 'EVAW')
	{
		return false;
	}
	
	// �t�H�[�}�b�g�`�F�b�N
	hr = m_pSoundDevice->GetDevice()->CheckChunk(hFile,' tmf',&dwChunkSize,&dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}
	hr = m_pSoundDevice->GetDevice()->ReadChunkData(hFile,&wfx,dwChunkSize,dwChunkPosition);
	if(FAILED(hr))
	{
		return false;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = m_pSoundDevice->GetDevice()->CheckChunk(hFile,'atad', &m_SizeAudio, &dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}

	m_pDataAudio = (BYTE*)malloc(m_SizeAudio);

	hr = m_pSoundDevice->GetDevice()->ReadChunkData(hFile,m_pDataAudio,m_SizeAudio,dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}
	
	// �\�[�X�{�C�X�̐���
	hr = m_pSoundDevice->GetDevice()->GetXAudio2()->CreateSourceVoice(&m_pSourceVoice, &(wfx.Format));

	if(FAILED(hr))
	{
		return false;
	}

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_SizeAudio;
	buffer.pAudioData = m_pDataAudio;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_pSourceVoice->SubmitSourceBuffer(&buffer);

	return true;
}

//=============================================================================
// �Đ�����
//=============================================================================
void CXAudio2Sound::Play(bool bLoopFlag)
{
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_SizeAudio;
	buffer.pAudioData = m_pDataAudio;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;

	if(bLoopFlag)
	{
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else
	{
		buffer.LoopCount  = 0;
	}

	// �Đ���
	if(m_bPlayFlag)
	{
		// ��~
		Stop();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_pSourceVoice->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_pSourceVoice->Start(0);

	// �Đ��t���O�𗧂Ă�
	m_bPlayFlag = true;
}

//=============================================================================
// ��~����
//=============================================================================
void CXAudio2Sound::Stop(void)
{
	// �Đ���
	if(m_bPlayFlag)
	{
		// �ꎞ��~
		m_pSourceVoice->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_pSourceVoice->FlushSourceBuffers();
	}

	// �Đ��t���O��܂�
	m_bPlayFlag = false;
}

//=============================================================================
// �ꎞ��~����
//=============================================================================
void CXAudio2Sound::Pause(void)
{
	// �Đ���
	if(m_bPlayFlag)
	{
		// �ꎞ��~
		m_pSourceVoice->Stop(0);
	}

	// �Đ��t���O��܂�
	m_bPlayFlag = false;
}

//---------------------------------- EOF --------------------------------------
