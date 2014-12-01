//*****************************************************************************
//
// OpenGLテクスチャクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <stdio.h>
// basic
#include "basic/application.h"

#ifdef _USING_OPENGL_
// graphic
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/device/opengl/opengl.h"
#include "interface/graphic/texture/opengl/gl_texture.h"

// common
#include "common/file/file.h"
#include "common/image/image.h"
#include "common/image/tga.h"
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CGLTexture::CGLTexture(CDeviceHolder* device_holder) : CTexture(device_holder)
{
	// テクスチャを読み込みしていない状態にする
	m_nTexture = 0;

}

//=============================================================================
// デストラクタ
//=============================================================================
CGLTexture::~CGLTexture(void)
{
}

//=============================================================================
// ロード処理
//=============================================================================
bool CGLTexture::Init(void)
{
	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGLTexture::Uninit(void)
{
	glDeleteTextures(1,&m_nTexture);

	CTexture::Uninit();
}

//=============================================================================
// ロード処理
//=============================================================================
bool CGLTexture::Load(const char* pFilename)
{
	EXTENSION Extension;

	if(m_nTexture != 0)
	{
		// すでに読み込みしている
		return false;
	}

	// ファイル名の設定
	SetFilename(pFilename);

	// 拡張子の判別
	Extension = GetExtension(pFilename);

	// 拡張子で読み込み方法を変更
	switch(Extension)
	{
	// TGAファイル
	case EXTENSION_TGA:
		// TGAのロード
		m_nTexture = LoadTga(pFilename);
		break;

	// PNGファイル
	case EXTENSION_PNG:
		m_nTexture = LoadPng(pFilename);
		break;
	// TXOファイル
	case EXTENSION_TXO:
		m_nTexture = LoadTxo(pFilename);
		break;
	// 対応していないファイル
	default:
		return false;
	}

	// テクスチャのバインド
	glBindTexture(GL_TEXTURE_2D,m_nTexture);

	// アライメントの設定
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	// 横方向をリピートする
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

	// 縦方向をリピートする
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	// 線形補間する
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	// テクスチャの選択破棄
	glBindTexture(GL_TEXTURE_2D,0);
	
	return true;
}

//=============================================================================
// 設定処理
//=============================================================================
bool CGLTexture::Set(void)
{
	glBindTexture(GL_TEXTURE_2D,m_nTexture);

	if(glIsTexture(m_nTexture))
	{
		int a = 0;
	}
	return true;
}

//=============================================================================
// 設定処理
//=============================================================================
void CGLTexture::Unset(void)
{
	glBindTexture(GL_TEXTURE_2D,0);
}

//=============================================================================
// TGAファイル読み込み処理
//=============================================================================
unsigned int CGLTexture::LoadTga(const char* pFilename)
{
	unsigned int nTexture = 0;		// テクスチャネーム
	unsigned short nWidth;			// 画像の横幅
	unsigned short nHeight;			// 画像の縦幅
	unsigned char *pImage;			// イメージデータ
	IMAGE Image;

	if(!LoadTGATexture(pFilename,&Image,true))
	{
		return 0;
	}

	pImage = ConvertCharFromImage(Image);

	nWidth = Image._width;
	nHeight = Image._height;

	SAFE_DELETE_ARRAY(Image._color);

	// テクスチャ生成
	glGenTextures(1,&nTexture);

	// テクスチャの選択
	glBindTexture(GL_TEXTURE_2D,nTexture);

	// テクスチャのロード
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,nWidth,nHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pImage);

	// イメージの破棄
	delete[] pImage;

	if(glIsTexture(nTexture))
	{
		int a = 0;
	}

	return nTexture;

}

//=============================================================================
// TXOファイルのロード
//=============================================================================
unsigned int CGLTexture::LoadTxo(const char* pFilename)
{
	unsigned int nTexture = 0;		// テクスチャネーム
	unsigned short nWidth;			// 画像の横幅
	unsigned short nHeight;			// 画像の縦幅
	unsigned char *pImage;			// イメージデータ
	
	// テクスチャデータ読み込み
	// ファイルポインタ
	FILE *file = nullptr;
	// ファイルオープン
	fopen_s(&file, pFilename, "rb");
	if(!file)
	{
		return FALSE;
	}

	// 幅読み込み
	fread(&nWidth, sizeof(unsigned short), 1, file);
	fread(&nHeight, sizeof(unsigned short), 1, file);
	// バッファ生成
	unsigned bufferSize = nWidth * nHeight * 4;
	pImage = new unsigned char[bufferSize];
	fread(pImage, bufferSize, 1, file);

	// ファイルクローズ
	fclose(file);

	// テクスチャ生成
	glGenTextures(1,&nTexture);

	// テクスチャの選択
	glBindTexture(GL_TEXTURE_2D,nTexture);

	// テクスチャのロード
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,nWidth,nHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pImage);

	// イメージの破棄
	delete[] pImage;

	if(glIsTexture(nTexture))
	{
		int a = 0;
	}

	return nTexture;
}

//=============================================================================
// TGAファイル読み込み処理
//=============================================================================
unsigned int CGLTexture::LoadPng(const char* pFilename)
{
	return 0;
}

//=============================================================================
// 拡張子識別処理
//=============================================================================
CGLTexture::EXTENSION CGLTexture::GetExtension(const char* pFilename)
{
	char* pExtension;
	CGLTexture::EXTENSION Ret = EXTENSION_NONE;

	GetExtensionName(&pExtension,pFilename);

	// TGAか判断
	if(!strcmp(pExtension,"tga"))
	{
		Ret = EXTENSION_TGA;
	}
	else if(!strcmp(pExtension,"png"))
	{
		Ret = EXTENSION_PNG;
	}
	else if(!strcmp(pExtension,"txo"))
	{
		Ret = EXTENSION_TXO;
	}

	SAFE_DELETE_ARRAY(pExtension);

	return Ret;
}

#endif // _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
