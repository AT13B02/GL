//=============================================================================
//
// ウィンドウクラス [CWindow.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//
//=============================================================================
#pragma once
#ifndef __KBR_CWINDOW_H__
#define __KBR_CWINDOW_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <string>

//*****************************************************************************
// ウィンドウクラス
// Author : Ryo Kobayashi
//*****************************************************************************
class CWindow
{
public:

	enum Message
	{
		MESSAGE_OK,			// メッセージが処理された
		MESSAGE_TERMINATE	// 終了メッセージが来た
	};

	CWindow();

	~CWindow();

	// 生成処理
	static HRESULT Create(DWORD uWidth, DWORD uHeight, const char* pCaption, const char* pClassName, WNDPROC pWndProc, CWindow** ppWindow);

	// 開放
	void Release();

	// メッセージ処理
	Message ProcMessage(MSG& msg);

	// ウィンドウハンドル取得
	const HWND& GetWindowHandle();

	// ウィンドウ横幅取得
	const DWORD& GetWindowWidth();

	// ウィンドウ縦幅取得
	const DWORD& GetWindowHeight();

	// キャプション設定
	void SetCaption(const char* pCaption);

	// ウィンドウ表示
	void ShowWindow();

private:

	// 内部生成処理
	HRESULT Create(DWORD uWidth, DWORD uHeight, const char* pCaption, const char* pClassName, WNDPROC pWndProc);

private:

	// ウィンドウハンドル
	HWND m_hWnd;

	// ウィンドウ横幅
	DWORD m_uWindowWidth;
	// ウィンドウ縦幅
	DWORD m_uWindowHeight;

	// ウィンドウクラス名
	std::string m_strClassName;

	// ウィンドウキャプション
	std::string m_strCaption;
	
	// ウィンドウスタイル
	static const int GAME_WINDOW;
};

#endif	// __KBR_CWINDOW_H__

// EOF