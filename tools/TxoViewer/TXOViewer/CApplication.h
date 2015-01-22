//=============================================================================
//
// アプリケーションクラス [CApplication.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================
#pragma once
#ifndef __KBR_CAPPLICATION_H__
#define __KBR_CAPPLICATION_H__

// 前方参照
class CWindowManager;
class CRenderer;
class CManager;

//*****************************************************************************
// アプリケーションクラス
// Author : Ryo Kobayashi
//*****************************************************************************
class CApplication
{
public:

	CApplication();

	~CApplication();

	// アプリケーションスタート
	static int Run(const char* pArg);

	// ウィンドウマネージャ取得
	CWindowManager* GetWindowManager(){ return m_pWindowManager; }

	// レンダラ取得
	CRenderer* GetRenderer(){ return m_pRenderer; }

	// マネージャ取得
	CManager* GetManager(){ return m_pManager; }

	// アプリケーション引数取得
	const char* GetArgument(){ return m_pArg; }

private:

	// 生成
	static bool Create(const char* pArg, CApplication** ppApplication);

	// 初期化
	bool Initialize(const char* pArg);

	// 開放
	void Release();

	// 更新
	void Update();

private:

	// ウィンドウ
	CWindowManager* m_pWindowManager;

	// レンダラ
	CRenderer* m_pRenderer;

	// マネージャ
	CManager* m_pManager;

	// 引数
	const char* m_pArg;
};

#endif	// __KBR_CAPPLICATION_H__

// EOF