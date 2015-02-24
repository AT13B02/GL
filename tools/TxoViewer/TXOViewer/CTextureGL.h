//=============================================================================
//
// テクスチャクラス [CTextureGL.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================
#pragma once
#ifndef __KBR_TEXTURE_GL_H__
#define __KBR_TEXTURE_GL_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "OpenGL.h"

//*****************************************************************************
// テクスチャクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//*****************************************************************************
class CTextureGL
{
public:

	CTextureGL();

	~CTextureGL();
	
	// テクスチャロード
	static BOOL LoadFromFile(const char* pFileName, CTextureGL** ppTexture);

	// テクスチャバッファへのポインタを取得
	unsigned char* GetBufferPointer(void);

	// テクスチャ開放
	void Release(void);

	// テクスチャ設定
	void SetTex2D(void);

private:
	
	// テクスチャロード
	BOOL LoadFromFile(const char* pFileName);

private:

	// テクスチャ識別番号
	unsigned int m_uIndex;
	// テクスチャバッファ
	unsigned char* m_pTex;

	// テクスチャ横幅
	unsigned short m_uWidth;
	// テクスチャ縦幅
	unsigned short m_uHeight;
};

typedef CTextureGL* LPCTEXTUREGL;

#endif	// __KBR_TEXTURE_GL_H__

// EOF