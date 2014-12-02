//*****************************************************************************
//
// XAudioクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _XAUDIO_H_
#define _XAUDIO_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <xaudio2.h>

// basic
#include "basic/basic.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CXAudio2 : public CBasic
{
public:
	// コンストラクタ
	CXAudio2(void);

	// デストラクタ
	virtual ~CXAudio2(void);

	// 初期化
	bool Init(void);

	// 終了
	void Uninit(void);

	// チャンクのチェック
	HRESULT CheckChunk(HANDLE h_file, DWORD format, DWORD *chunk_size, DWORD *chunk_data_position);

	// チャンクデータの読み込み
	HRESULT ReadChunkData(HANDLE h_file, void* buffer, DWORD buffer_size, DWORD buffer_offset);

	// XAudio2の取得
	IXAudio2* x_audio2(void){return xaudio2_;}

	// XAudio2の取得
	IXAudio2MasteringVoice* mastering_voice(void){return mastering_voice_;}

protected:

private:
	IXAudio2* xaudio2_;							// XAudio2オブジェクトへのインターフェイス

	IXAudio2MasteringVoice* mastering_voice_;		// マスターボイス
};

#endif // _XAUDIO_H_

//---------------------------------- EOF --------------------------------------
