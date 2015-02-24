//=============================================================================
//
// ハードウェアタイマークラス [CHardwareTimer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//
//=============================================================================
#pragma once
#ifndef __KBR_CHARDWARE_TIMER_H__
#define __KBR_CHARDWARE_TIMER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>

//*****************************************************************************
// ライブラリリンク
//*****************************************************************************
#pragma comment (lib, "winmm.lib")	// これが無いとtime~関数が使えない

//*****************************************************************************
// ハードウェアタイマークラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/9/30
//*****************************************************************************
class CHardwareTimer
{
public:

	CHardwareTimer();

	~CHardwareTimer();

	// タイマーセットアップ
	static void SetupTimer(void);

	// タイマーエンド
	static void EndTimer(void);

	// 初期化
	void Init(void);

	// 更新
	bool Update(void);
	
	// FPS取得
	float GetFPS(void);

private:

	// タイマースタートフラグ
	static bool	m_bTimerStarted;
	// タイマーエンドフラグ
	static bool	m_bTimerEnded;

	// 開始時間
	DWORD	m_uStart;
	// 終了時間
	DWORD	m_uEnd;
	// FPS
	float m_fFPS;
};

#endif	// __KBR_CHARDWARE_TIMER_H__

// EOF