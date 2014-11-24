//*****************************************************************************
//
// XAudio処理 [xaudio2.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/11(Thu)
// Version		: 1.00
// Update Date	: 2014/09/11(Thu)
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
#include "basic.h"
#include <xaudio2.h>

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
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);

	// チャンクデータの読み込み
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// XAudio2の取得
	IXAudio2* GetXAudio2(void){return m_pXAudio2;}

	// XAudio2の取得
	IXAudio2MasteringVoice* GetMasteringVoice(void){return m_pMasteringVoice;}

protected:

private:
	IXAudio2* m_pXAudio2;							// XAudio2オブジェクトへのインターフェイス

	IXAudio2MasteringVoice* m_pMasteringVoice;		// マスターボイス
};

#endif // _XAUDIO_H_

//---------------------------------- EOF --------------------------------------
