//=============================================================================
//
// テクスチャクラス [CTextureGL.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CTextureGL.h"
#include "TextureLoader.h"
#include "Debug.h"

//=============================================================================
// コンストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureGL::CTextureGL() :
m_uIndex(0),
m_pTex(NULL),
m_uWidth(0),
m_uHeight(0)
{
}

//=============================================================================
// デストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureGL::~CTextureGL()
{
}

//=============================================================================
// テクスチャロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureGL::LoadFromFile(const char* pFileName, CTextureGL** ppTexture)
{
	// テクスチャ生成
	(*ppTexture) = new CTextureGL();

	if(!(*ppTexture)->LoadFromFile(pFileName))
	{
		return FALSE;
	}

	return TRUE;
}

//=============================================================================
// テクスチャバッファへのポインタを取得
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
unsigned char* CTextureGL::GetBufferPointer(void)
{
	return m_pTex;
}

//=============================================================================
// テクスチャロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureGL::LoadFromFile(const char* pFileName)
{
	LoadTexture(pFileName, &m_pTex, &m_uWidth, &m_uHeight);

	// 読み込み失敗時
	if(!m_pTex)
	{
		_asm int 3;
		return FALSE;
	}
	
	// テクスチャ生成
	glGenTextures(1, &m_uIndex);
	// 参照テクスチャ設定
	glBindTexture(GL_TEXTURE_2D, m_uIndex);

	// 1ピクセルに対する処理(UNPACK_ALIGNMENT), 1バイト
	// 4バイトアラインメントをすると高速になる
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// S軸方向(横)方向ラップ方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// T軸方向(縦)方向ラップ方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 拡大時補間方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 縮小時補間方法
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// テクスチャ適用
	glTexImage2D(
		GL_TEXTURE_2D,	// テクスチャ形式(固定)
		0,				// ミップマップレベル(0だと無し)
		GL_RGBA,		// テクスチャフォーマット(みたまんま)
		m_uWidth,		// テクスチャ横幅
		m_uHeight,		// テクスチャ縦幅
		0,				// テクスチャ周りのボーダー(なんかの効果で使うかも？)
		GL_RGBA,		// テクスチャメモリブロックフォーマット(上のフォーマットと同じ)
		GL_UNSIGNED_BYTE,// テクスチャ1成分(R,A,etc.)の型
		m_pTex);		// テクスチャ参照先
	
	// テクスチャ参照先開放
	glBindTexture(GL_TEXTURE_2D, 0);

	return TRUE;
}

//=============================================================================
// テクスチャ開放
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
void CTextureGL::Release(void)
{
	// VRAM上のテクスチャを開放
	glDeleteTextures(1, &m_uIndex);
	// テクスチャデリート
	DeleteTexture(&m_pTex);
	delete this;
}

//=============================================================================
// テクスチャ設定
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
void CTextureGL::SetTex2D(void)
{
	glBindTexture(GL_TEXTURE_2D, m_uIndex);
}

// EOF