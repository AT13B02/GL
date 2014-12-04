//*****************************************************************************
//
// XAudio2サウンド処理 [xaudio2_sound.h]
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// sound
#include "interface/sound/sound.h"
#include "interface/sound/xaudio2/xaudio2_sound.h"
#include "interface/sound/device/sound_device.h"
#include "interface/sound/device/xaudio2/xaudio2.h"

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define _CRT_SECURE_NO_WARNINGS

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
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
// デストラクタ
//=============================================================================
CXAudio2Sound::~CXAudio2Sound(void)
{
}

//=============================================================================
// 初期化処理
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
// 終了処理
//=============================================================================
void CXAudio2Sound::Uninit(void)
{
	// 停止
	Stop();

	// ソースボイスの破棄
	if(source_voice_ != NULL)
	{
		source_voice_->DestroyVoice();
		source_voice_ = NULL;

		// オーディオデータの開放
		SAFE_DELETE(data_audio_);
	}

	CSound::Uninit();
}

//=============================================================================
// ロード処理
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

	// ファイル名の保存
	SetFilename(filename);

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if(hFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	// ファイルポインタを先頭に移動
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
		return false;
	}
	
	// WAVEファイルのチェック
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
	
	// フォーマットチェック
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

	// オーディオデータ読み込み
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
	
	// ソースボイスの生成
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

	// オーディオバッファの登録
	source_voice_->SubmitSourceBuffer(&buffer);

	return true;
}

//=============================================================================
// 再生処理
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

	// 再生中
	if(is_play_)
	{
		// 停止
		Stop();
	}

	// オーディオバッファの登録
	source_voice_->SubmitSourceBuffer(&buffer);

	// 再生
	source_voice_->Start(0);

	// 再生フラグを立てる
	is_play_ = true;
}

//=============================================================================
// 停止処理
//=============================================================================
void CXAudio2Sound::Stop(void)
{
	// 再生中
	if(is_play_)
	{
		// 一時停止
		source_voice_->Stop(0);

		// オーディオバッファの削除
		source_voice_->FlushSourceBuffers();
	}

	// 再生フラグを折る
	is_play_ = false;
}

//=============================================================================
// 一時停止処理
//=============================================================================
void CXAudio2Sound::Pause(void)
{
	// 再生中
	if(is_play_)
	{
		// 一時停止
		source_voice_->Stop(0);
	}

	// 再生フラグを折る
	is_play_ = false;
}

//---------------------------------- EOF --------------------------------------
