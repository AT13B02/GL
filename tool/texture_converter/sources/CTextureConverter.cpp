//=============================================================================
//
// テクスチャクラス [CTextureConverter.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CTextureConverter.h"
#include "TextureLoader.h"
#include "kbString.h"
#include <stdio.h>
#include "Debug.h"

//=============================================================================
// コンストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureConverter::CTextureConverter() :
m_pBuffer(NULL),
m_uWidth(0),
m_uHeight(0)
{
}

//=============================================================================
// デストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureConverter::~CTextureConverter()
{
}

//=============================================================================
// テクスチャロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureConverter::Convert(const char* pFileName)
{
	// テクスチャ生成
	CTextureConverter conv;

	if(!conv.LoadFromFile(pFileName))
	{
		return FALSE;
	}

	return TRUE;
}

//=============================================================================
// テクスチャロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureConverter::LoadFromFile(const char* pFileName)
{
	LoadTexture(pFileName, &m_pBuffer, &m_uWidth, &m_uHeight);

	// 読み込み失敗時
	if(!m_pBuffer)
	{
		_asm int 3;
		return FALSE;
	}

	kb::CString fn(pFileName);
	// ファイル名設定
	int id = fn.SearchTokenIndexL('.') + 1;
	char ext[] = "txo";
	int strId = 0;
	while(id + strId < fn.GetLength())
	{
		fn[id + strId] = ext[strId];
		strId++;
	}
	while(strId < sizeof(ext) - 1)
	{
		fn += &ext[strId];
		strId++;
	}
	// ファイルオープン
	FILE* pFile = nullptr;
	fopen_s(&pFile, fn.GetStr(), "wb");
	// 横幅
	fwrite(&m_uWidth, sizeof(m_uWidth), 1, pFile);
	// 縦幅
	fwrite(&m_uHeight, sizeof(m_uHeight), 1, pFile);
	// データ(rgbaの4バイト)
	fwrite(m_pBuffer, 4, m_uWidth * m_uHeight, pFile);
	fclose(pFile);

	printf("変換 : %s\n", fn.GetStr());

	delete[] m_pBuffer;
	
	return TRUE;
}

// EOF