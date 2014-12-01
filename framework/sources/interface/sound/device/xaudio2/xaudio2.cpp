//*****************************************************************************
//
// XAudioクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// sound
#include "xaudio2.h"

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CXAudio2::CXAudio2(void)
{
	xaudio2_ = NULL;
	mastering_voice_ = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CXAudio2::~CXAudio2(void)
{
}

//=============================================================================
// サウンドの初期化処理
//=============================================================================
bool CXAudio2::Init(void)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&xaudio2_, 0);

	if(FAILED(hr))
	{
		// COMライブラリの終了処理
		CoUninitialize();
		return false;
	}

	// マスターボイスの生成
	hr = xaudio2_->CreateMasteringVoice(&mastering_voice_);

	if(FAILED(hr))
	{
		if(xaudio2_ != NULL)
		{
			// XAudio2オブジェクトの開放
			xaudio2_->Release();
			xaudio2_ = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return false;
	}

	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CXAudio2::Uninit(void)
{
	if(mastering_voice_ != NULL)
	{
		// マスターボイスの破棄
		mastering_voice_->DestroyVoice();
		mastering_voice_ = NULL;
	}

	// XAudio2の破棄
	SAFE_RELEASE(xaudio2_);

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CXAudio2::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CXAudio2::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}


//---------------------------------- EOF --------------------------------------
