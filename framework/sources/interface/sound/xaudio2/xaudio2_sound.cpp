//*****************************************************************************
//
// XAudio2�T�E���h���� [xaudio2_sound.h]
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// sound
#include "interface/sound/sound.h"
#include "interface/sound/xaudio2/xaudio2_sound.h"
#include "interface/sound/device/sound_device.h"
#include "interface/sound/device/xaudio2/xaudio2.h"

// common
#include "common/common.h"

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
CXAudio2Sound::CXAudio2Sound(CSoundDevice* sound_device) : CSound(sound_device)
{
	is_play_ = false;

	sound_id_ = -1;

	source_voice_ = NULL;

	data_audio_ = NULL;

	size_audio_ = 0;
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

	sound_id_ = -1;

	source_voice_ = NULL;

	data_audio_ = NULL;

	size_audio_ = 0;

	is_play_ = false;

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
	if(source_voice_ != NULL)
	{
		source_voice_->DestroyVoice();
		source_voice_ = NULL;

		// �I�[�f�B�I�f�[�^�̊J��
		SAFE_DELETE(data_audio_);
	}

	CSound::Uninit();
}

//=============================================================================
// ���[�h����
//=============================================================================
bool CXAudio2Sound::Load(const s8* filename)
{
	HANDLE hFile;
	HRESULT hr;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �t�@�C�����̕ۑ�
	SetFilename(filename);

	// �o�b�t�@�̃N���A
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// �T�E���h�f�[�^�t�@�C���̐���
	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

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
	hr = sound_device_->device()->CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}

	hr = sound_device_->device()->ReadChunkData(hFile,&dwFiletype,sizeof(DWORD),dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}
	if(dwFiletype != 'EVAW')
	{
		return false;
	}
	
	// �t�H�[�}�b�g�`�F�b�N
	hr = sound_device_->device()->CheckChunk(hFile,' tmf',&dwChunkSize,&dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}
	hr = sound_device_->device()->ReadChunkData(hFile,&wfx,dwChunkSize,dwChunkPosition);
	if(FAILED(hr))
	{
		return false;
	}

	// �I�[�f�B�I�f�[�^�ǂݍ���
	hr = sound_device_->device()->CheckChunk(hFile,'atad', &size_audio_, &dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}

	data_audio_ = new BYTE[size_audio_];

	hr = sound_device_->device()->ReadChunkData(hFile,data_audio_,size_audio_,dwChunkPosition);

	if(FAILED(hr))
	{
		return false;
	}
	
	// �\�[�X�{�C�X�̐���
	hr = sound_device_->device()->xaudio2()->CreateSourceVoice(&source_voice_, &(wfx.Format));

	if(FAILED(hr))
	{
		return false;
	}

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = size_audio_;
	buffer.pAudioData = data_audio_;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = 0;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	source_voice_->SubmitSourceBuffer(&buffer);

	return true;
}

//=============================================================================
// �Đ�����
//=============================================================================
void CXAudio2Sound::Play(bool bLoopFlag)
{
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = size_audio_;
	buffer.pAudioData = data_audio_;
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
	if(is_play_)
	{
		// ��~
		Stop();
	}

	// �I�[�f�B�I�o�b�t�@�̓o�^
	source_voice_->SubmitSourceBuffer(&buffer);

	// �Đ�
	source_voice_->Start(0);

	// �Đ��t���O�𗧂Ă�
	is_play_ = true;
}

//=============================================================================
// ��~����
//=============================================================================
void CXAudio2Sound::Stop(void)
{
	// �Đ���
	if(is_play_)
	{
		// �ꎞ��~
		source_voice_->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		source_voice_->FlushSourceBuffers();
	}

	// �Đ��t���O��܂�
	is_play_ = false;
}

//=============================================================================
// �ꎞ��~����
//=============================================================================
void CXAudio2Sound::Pause(void)
{
	// �Đ���
	if(is_play_)
	{
		// �ꎞ��~
		source_voice_->Stop(0);
	}

	// �Đ��t���O��܂�
	is_play_ = false;
}

//---------------------------------- EOF --------------------------------------
