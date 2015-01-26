//=============================================================================
//
// マネージャ [CManager.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//
//=============================================================================
#pragma once
#ifndef __KBR_MANAGER_H__
#define __KBR_MANAGER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>

// 前方参照
class CApplication;
class CRenderer;
class CWindowManager;
class CTextureGL;

//*****************************************************************************
// マネージャクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/9
//*****************************************************************************
class CManager
{
public:

	CManager();

	~CManager(){}

	// マネージャ作成
	static HRESULT Create(HINSTANCE hInstance, CApplication* pApplication, CManager** ppManager);

	// 開放
	void Release(void);

	// 初期化
	HRESULT Init(HINSTANCE hInstance,
				CApplication* pApplication);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

private:
	
	// 開放
	void Uninit(void);

	// イメージ出力
	void DrawRenderedImage();

private:

	// アプリケーション
	CApplication* m_pApplication;

	// レンダラ
	CRenderer* m_pRenderer;

	// ウィンドウマネージャ
	CWindowManager* m_pWindowManager;
	
	// グローバル変数
	CTextureGL *m_pTexture;

};

#endif	// __KBR_MANAGER_H__

// EOF