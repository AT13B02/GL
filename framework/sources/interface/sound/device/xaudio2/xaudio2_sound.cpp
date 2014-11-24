//*****************************************************************************
//
// XAudio2サウンド処理 [xaudio2_sound.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/03/28(Fri)
// Version		: 1.00
// Update Date	: 2014/09/11(Thu)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "sound.h"
#include "xaudio2_sound.h"
#include "sound_device.h"
#include "xaudio2.h"

#include "common.h"

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

	m_nSoundId = -1;

	m_pSourceVoice = NULL;

	m_pDataAudio = NULL;

	m_SizeAudio = 0;

	m_bPlayFlag = false;

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
	if(m_pSourceVoice != NULL)
	{
		m_pSourceVoice->DestroyVoice();
		m_pSourceVoice = NULL;

		// オーディオデータの開放
		SAFE_DELETE(m_pDataAudio);
	}

	CSound::Uninit();
}

//=============================================================================
// ロード処理
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

	// ファイル名の保存
	SetFilename(pFilename);

	// バッファのクリア
	memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

	// サウンドデータファイルの生成
	hFile = CreateFile(pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

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
	
	// フォーマットチェック
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

	// オーディオデータ読み込み
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
	
	// ソースボイスの生成
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

	// オーディオバッファの登録
	m_pSourceVoice->SubmitSourceBuffer(&buffer);

	return true;
}

//=============================================================================
// 再生処理
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

	// 再生中
	if(m_bPlayFlag)
	{
		// 停止
		Stop();
	}

	// オーディオバッファの登録
	m_pSourceVoice->SubmitSourceBuffer(&buffer);

	// 再生
	m_pSourceVoice->Start(0);

	// 再生フラグを立てる
	m_bPlayFlag = true;
}

//=============================================================================
// 停止処理
//=============================================================================
void CXAudio2Sound::Stop(void)
{
	// 再生中
	if(m_bPlayFlag)
	{
		// 一時停止
		m_pSourceVoice->Stop(0);

		// オーディオバッファの削除
		m_pSourceVoice->FlushSourceBuffers();
	}

	// 再生フラグを折る
	m_bPlayFlag = false;
}

//=============================================================================
// 一時停止処理
//=============================================================================
void CXAudio2Sound::Pause(void)
{
	// 再生中
	if(m_bPlayFlag)
	{
		// 一時停止
		m_pSourceVoice->Stop(0);
	}

	// 再生フラグを折る
	m_bPlayFlag = false;
}

//---------------------------------- EOF --------------------------------------
