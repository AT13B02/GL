//=============================================================================
//
// テクスチャ変換クラス [CTextureConverter.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//
//=============================================================================
#pragma once
#ifndef __KBR_TEXTURE_GL_H__
#define __KBR_TEXTURE_GL_H__

#include <Windows.h>

//*****************************************************************************
// テクスチャ変換クラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//*****************************************************************************
class CTextureConverter
{
public:

	CTextureConverter();

	~CTextureConverter();
	
	// テクスチャ変換
	BOOL Convert(const char* pFileName);

private:
	
	// テクスチャロード
	BOOL LoadFromFile(const char* pFileName);

private:

	// テクスチャバッファ
	unsigned char* m_pBuffer;

	// テクスチャ横幅
	unsigned short m_uWidth;
	// テクスチャ縦幅
	unsigned short m_uHeight;
};

#endif	// __KBR_TEXTURE_GL_H__

// EOF