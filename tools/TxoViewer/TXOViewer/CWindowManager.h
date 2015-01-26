//=============================================================================
//
// ウィンドウマネージャクラス [CWindowManager.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================
#pragma once
#ifndef __KBR_CWINDOW_MANAGER_H__
#define __KBR_CWINDOW_MANAGER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CWindow.h"

//*****************************************************************************
// ウィンドウマネージャクラス
// Author : Ryo Kobayashi
//*****************************************************************************
class CWindowManager
{
public:

	CWindowManager();

	~CWindowManager();

	// 生成
	static bool Create(CWindowManager** ppManager);
	
	// 開放
	void Release();

	// ウィンドウを追加
	// 追加したらIDを返す
	const int Add(const char* pFileName);
	const int Add(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight);

	// ウィンドウ取得
	CWindow* GetWindow(const unsigned uIndex){ return m_ppWindow[uIndex]; }
	
	// メッセージ処理
	CWindow::Message ProcMessage(const unsigned uIndex, MSG& msg);

	// ウィンドウハンドル取得
	const HWND& GetWindowHandle(const unsigned uIndex);

	// ウィンドウ横幅取得
	const DWORD& GetWindowWidth(const unsigned uIndex);

	// ウィンドウ縦幅取得
	const DWORD& GetWindowHeight(const unsigned uIndex);

	// キャプション設定
	void SetCaption(const unsigned uIndex,const char* pCaption);

	// ウィンドウ表示
	void ShowWindow(const unsigned uIndex);
	
	// ウィンドウプロシージャ
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	// 新しいウィンドウの生成
	const int CreateNewWindow(const char* pFileName);
	const int CreateNewWindow(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight);
	
	// キー入力
	static void KeyInputProc(HWND hWnd, WPARAM wParam);

private:

	unsigned m_uNumWindow;
	CWindow** m_ppWindow;
};

#endif	// __KBR_CWINDOW_MANAGER_H__

// EOF