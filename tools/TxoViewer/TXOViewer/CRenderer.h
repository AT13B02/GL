//=============================================================================
//
// レンダリングクラス [CRenderer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/18
//
//=============================================================================
#pragma once
#ifndef __KBR_RENDERER_GL_H__
#define __KBR_RENDERER_GL_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include "OpenGL.h"
#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ErrorMessage(msg) MessageBox(NULL, msg, "ERROR", MB_OK | MB_ICONSTOP | MB_TASKMODAL);

//*****************************************************************************
// 前方参照
//*****************************************************************************
class CRenderTexture;

//*****************************************************************************
// レンダリングクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/8
//*****************************************************************************
class CRenderer
{
public:

	CRenderer();

	~CRenderer();

	// 生成処理
	static HRESULT Create(
		HWND hWnd, 
		BOOL bWindow, 
		unsigned uBackBufferWidth, 
		unsigned uBackBufferHeight, 
		CRenderer** ppRender);

	// 開放
	void Release();

	// 描画開始
	void BeginDraw();
	// 描画終了
	void EndDraw();

	// バックバッファサイズ取得
	const unsigned& GetBackBufferWidth(){ return m_uBackBufferWidth; }
	const unsigned& GetBackBufferHeight(){ return m_uBackBufferHeight; }

private:

	// 初期化
	HRESULT Init(HWND hWnd, BOOL bWindow, unsigned uBackBufferWidth, unsigned uBackBufferHeight);

private:
	
	// ウィンドウハンドル
	HWND		m_hWnd;
	// デバイスコンテキスト
	HDC			m_hdc;
	// OpenGLコンテキスト
	HGLRC		m_glRC;

	// バックバッファ横幅
	unsigned m_uBackBufferWidth;
	// バックバッファ縦幅
	unsigned m_uBackBufferHeight;

	// クリアカラー
	float m_Clear_Red;
	float m_Clear_Green;
	float m_Clear_Blue;
};

#endif	// __KBR_RENDERER_GL_H__

// EOF