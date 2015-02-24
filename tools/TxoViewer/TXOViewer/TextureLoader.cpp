//=============================================================================
//
// テクスチャロード処理 [TextureLoader.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/22
//
// 2014/4/22 TGAフォーマットを追加
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "TextureLoader.h"
#include "Debug.h"
#include <stdio.h>

//*****************************************************************************
// 定数定義
//*****************************************************************************
// テクスチャイメージフォーマット
enum IMAGE_FORMAT
{
	BMP = 0,	// ビットマップ
	TGA,		// TGA
	JPG,		// JPEG
	PNG,		// PNG
	TXO		// 独自定義TXOファイル
};

//*****************************************************************************
// TGAヘッダ定義
//*****************************************************************************
struct TGAHeader
{
	BYTE thFiled;		// フィールド長
	BYTE thColorMap;	// カラーマップ(0:なし, 1:あり)
	BYTE thImageFormat;	// 画像形式(2:フルカラー, 10:フルカラーランレングス圧縮)
	unsigned short thColorMapEntry;
	unsigned short thColorMapLength;
	BYTE thColorMapEntrySize;
	short thX;			// X座標(何に使うか不明)
	short thY;			// Y座標(何に使うか不明)
	unsigned short thWidth;	// 画像横幅
	unsigned short thHeight;// 画像縦幅
	BYTE thColorDepth;	// 色深度
	BYTE thAttribute;	// 0~3:属性 4,5:格納情報(ともに0が使いやすい)
};

//*****************************************************************************
// PNGヘッダ定義
//*****************************************************************************
struct PNG_IHDR
{
	int ihLength;		// チャンクデータサイズ
	int ihChunkType;	// チャンクデータタイプ
	int ihWidth;		// データ横幅
	int ihHeight;	// データ縦幅
	BYTE ihDepth;		// ビット深度
	BYTE ihColorType;		// カラータイプ
	BYTE ihCompressionMethod;// データ圧縮手法
	BYTE ihFilteringMethod;	// フィルタ手法
	BYTE ihInterraceMethod;	// インターレース手法
	int ihCRC;			// ChunkTypeとChunkDataを基に計算される何か
};

//*****************************************************************************
// プロトタイプ関数
//*****************************************************************************
// 画像フォーマットチェック
int CheckFormat(char* pFormatName);
// ビットマップチェック
BOOL IsBitmap(char* pFormatName);
// TGAチェック
BOOL IsTGA(char* pFormatName);
// JPEGチェック
BOOL IsJPEG(char* pFormatName);
// PNGチェック
BOOL IsPNG(char* pFormatName);
// TXOチェック
BOOL IsTXO(char* pFormatName);

// ビットマップロード
BOOL LoadBitmapFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// TGAロード
BOOL LoadTGAFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// JPEGロード
BOOL LoadJPEGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// PNGロード
BOOL LoadPNGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// TXOロード
BOOL LoadTXOFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);

//*****************************************************************************
// 関数ポインタ
//*****************************************************************************
// ローダテーブル
BOOL (*TexLoader[])(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight) =
{
	LoadBitmapFromFile,	// Bitmap
	LoadTGAFromFile,	// TGA
	LoadJPEGFromFile,	// JPEG
	LoadPNGFromFile,	// PNG
	LoadTXOFromFile	// TXO
};

//=============================================================================
// テクスチャロード処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: BOOL		成功 : TRUE
//						失敗 : FALSE
// arg1		: char*		テクスチャ名
// arg2		: char**	テクスチャデータへのポインタ
// arg3		: unsigned short*	テクスチャ横幅へのポインタ
// arg4		: unsigned short*	テクスチャ縦幅へのポインタ
//=============================================================================
BOOL LoadTexture(const char* pTexName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	// 画像フォーマット
	int nFormat = -1;

	// テクスチャ名解析
	for(int i = 0; pTexName[i] != '\0'; i++)
	{
		// 拡張子のドット(.)を発見
		if(pTexName[i] == '.')
		{
			// 後に続く拡張子を調べる
			nFormat = CheckFormat((char*)&pTexName[i + 1]);
			// ループを抜ける
			break;
		}
	}

	// 該当するフォーマットが存在しなかった
	if(nFormat == -1)
	{
		// エラーを返す
		return FALSE;
	}

	// 拡張子から読み込み方法を変化させる
	if(!(*TexLoader[nFormat])(pTexName, ppTex, pWidth, pHeight))
	{
		// テクスチャの読み込みに失敗
		_AssertExpr(0, "テクスチャの読み込みに失敗");
		return FALSE;
	}

	// 読み込み成功
	return TRUE;
}

//=============================================================================
// テクスチャ開放処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: void
// arg1		: char*		テクスチャ名
// arg2		: char**	テクスチャデータへのポインタ
//=============================================================================
void DeleteTexture(unsigned char** ppTex)
{
	// テクスチャデータ開放
	delete[] (*ppTex);
}

//============================================================================
// 画像フォーマットチェック
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : 該当したフォーマット定数を返す
//						失敗 : -1を返す
// arg1		: char*		フォーマット名
//=============================================================================
int CheckFormat(char* pFormatName)
{
	// Bitmapだった場合
	if(IsBitmap(pFormatName))
	{
		// Bitmapフォーマット定数を返す
		return BMP;
	}
	// TGAだった場合
	if(IsTGA(pFormatName))
	{
		// Bitmapフォーマット定数を返す
		return TGA;
	}
	// JPEGだった場合
	else if(IsJPEG(pFormatName))
	{
		// JPEGフォーマット定数を返す
		return JPG;
	}
	// PNGだった場合
	else if(IsPNG(pFormatName))
	{
		// PNGフォーマット定数を返す
		return PNG;
	}
	// TXOだった場合
	else if(IsTXO(pFormatName))
	{
		return TXO;
	}
	// どれにも該当しない場合
	else
	{
		_AssertExpr(0, "予期しないファイルフォーマットが指定されました");
	}

	// エラーを返す
	return -1;
}

//============================================================================
// ビットマップチェック
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : 該当したフォーマット定数を返す
//						失敗 : -1を返す
// arg1		: char*		フォーマット名
//=============================================================================
BOOL IsBitmap(char* pFormatName)
{
	// フォーマット名が一致
	if( pFormatName[0] == 'b' &&
		pFormatName[1] == 'm' &&
		pFormatName[2] == 'p' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// 一致しなかったとき
	return FALSE;
}

//============================================================================
// TGAチェック
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/22
//
// ret		: int		成功 : 該当したフォーマット定数を返す
//						失敗 : -1を返す
// arg1		: char*		フォーマット名
//=============================================================================
BOOL IsTGA(char* pFormatName)
{
	// フォーマット名が一致
	if( pFormatName[0] == 't' &&
		pFormatName[1] == 'g' &&
		pFormatName[2] == 'a' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// 一致しなかったとき
	return FALSE;
}

//============================================================================
// JPEGチェック
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : 該当したフォーマット定数を返す
//						失敗 : -1を返す
// arg1		: char*		フォーマット名
//=============================================================================
BOOL IsJPEG(char* pFormatName)
{
	// フォーマット名が一致
	if( pFormatName[0] == 'j' &&
		pFormatName[1] == 'p' &&
		pFormatName[2] == 'g' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// 一致しなかったとき
	return FALSE;
}

//============================================================================
// PNGチェック
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : 該当したフォーマット定数を返す
//						失敗 : -1を返す
// arg1		: char*		フォーマット名
//=============================================================================
BOOL IsPNG(char* pFormatName)
{
	// フォーマット名が一致
	if( pFormatName[0] == 'p' &&
		pFormatName[1] == 'n' &&
		pFormatName[2] == 'g' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// 一致しなかったとき
	return FALSE;
}

//============================================================================
// TXOチェック
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//
// ret		: int		成功 : 該当したフォーマット定数を返す
//						失敗 : -1を返す
// arg1		: char*		フォーマット名
//=============================================================================
BOOL IsTXO(char* pFormatName)
{
	// フォーマット名が一致
	if( pFormatName[0] == 't' &&
		pFormatName[1] == 'x' &&
		pFormatName[2] == 'o' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// 一致しなかったとき
	return FALSE;
}

//============================================================================
// ビットマップロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : TRUE
//						失敗 : FALSE
// arg1		: char*		ファイル名
// arg2		: char**	テクスチャポインタ
//=============================================================================
BOOL LoadBitmapFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	// ビットマップファイルヘッダ
	BITMAPFILEHEADER bmfh;
	// ビットマップインフォヘッダ
	BITMAPINFOHEADER bmih;

	// ファイルポインタ
	FILE *pFile = NULL;

	// ファイルオープン
	pFile = fopen(pFileName, "rb");

	// ファイルがヌル
	if(!pFile)
	{
		_AssertExpr(pFile, "BMPファイルを開けません");
		return FALSE;
	}

	// ファイルヘッダ読み込み
	fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, pFile);
	// インフォヘッダ読み込み
	fread(&bmih, sizeof(BITMAPINFOHEADER), 1, pFile);

	// 画像サイズ取得
	int nImgWidth = bmih.biWidth;
	int nImgHeight = bmih.biHeight;

	// サイズコピー
	*pWidth = nImgWidth;
	*pHeight = nImgHeight;

	// 1ライン当たりのバイト数
	int nLine = nImgWidth * 4;	// rgbaの4バイトっていう前提

	// バッファ確保
	(*ppTex) = new unsigned char[nImgHeight * nLine];
	_AssertExpr((*ppTex), "BMPテクスチャ用バッファの確保に失敗");

	// 画像データ読み込み
	char b = 0;
	char g = 0;
	char r = 0;
	for(int y = nImgHeight - 1; y >= 0; y--)
	{
		for(int x = 0; x < nLine; x += 4)
		{
			fread(&b, 1, 1, pFile);
			fread(&g, 1, 1, pFile);
			fread(&r, 1, 1, pFile);
			ppTex[0][y * nLine + x    ] = r;
			ppTex[0][y * nLine + x + 1] = g;
			ppTex[0][y * nLine + x + 2] = b;
			ppTex[0][y * nLine + x + 3] = 0xff;
		}
	}

	// ファイルクローズ
	fclose(pFile);

	return TRUE;
}

//============================================================================
// TGAロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/22
//
// ret		: int		成功 : TRUE
//						失敗 : FALSE
// arg1		: char*		ファイル名
// arg2		: char**	テクスチャポインタ
//=============================================================================
BOOL LoadTGAFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	// TGAファイルヘッダ
	TGAHeader tga;
	// ファイルポインタ
	FILE *pFile;

	// ファイルオープン
	pFile = fopen(pFileName, "rb");

	// ファイルを開けなかったとき
	if(!pFile)
	{
		return FALSE;
	}

	// ヘッダ情報中の先頭12バイトをコピー
	fread(&tga, 12, 1, pFile);

	// 縦幅と横幅の取得
	fread(&tga.thWidth, 2, 1, pFile);
	fread(&tga.thHeight, 2, 1, pFile);
	*pWidth = tga.thWidth;
	*pHeight = tga.thHeight;

	// ヘッダの最後の部分を読み込む
	fread(&tga.thColorDepth, 1, 1, pFile);
	fread(&tga.thAttribute, 1, 1, pFile);
	
	// 1ライン当たりのバイト数
	int nLine = tga.thWidth * 4;	// rgbaの4バイトっていう前提

	// バッファ確保
	(*ppTex) = new unsigned char[tga.thHeight * nLine];
	_AssertExpr((*ppTex), "TGAテクスチャ用バッファの確保に失敗");
	
	// ループ増加変数
	int nLoopIncrement = 1;
	// 最小、最大
	int nStart = 0;
	int nEnd = tga.thHeight;

	// 上から下に読み込み
	if(tga.thAttribute & 0x20)
	{
		nLoopIncrement = 1;
		nStart = 0;
		nEnd = tga.thHeight;
	}
	// 下から上に読み込み
	else
	{
		nLoopIncrement = -1;
		nStart = tga.thHeight - 1;
		nEnd = -1;
	}

	// 画像データ読み込み
	// 色深度が24ビットのとき
	if(tga.thColorDepth == 24)
	{
		struct bgr
		{
			BYTE b, g, r;
		};
		bgr bgrColor;

		// ループ処理
		for(int y = nStart; y != nEnd; y += nLoopIncrement)
		{
			for(int x = 0; x < nLine; x += 4)
			{
				fread(&bgrColor, sizeof(bgr), 1, pFile);
				ppTex[0][y * nLine + x    ] = bgrColor.r;
				ppTex[0][y * nLine + x + 1] = bgrColor.g;
				ppTex[0][y * nLine + x + 2] = bgrColor.b;
				ppTex[0][y * nLine + x + 3] = 0xFF;
			}
		}
	}
	// 色深度が32ビットのとき
	else if(tga.thColorDepth == 32)
	{
		struct bgra
		{
			BYTE b, g, r, a;
		};
		bgra color;

		for(int y = nStart; y != nEnd; y += nLoopIncrement)
		{
			for(int x = 0; x < nLine; x += 4)
			{
				fread(&color, sizeof(bgra), 1, pFile);
				ppTex[0][y * nLine + x    ] = color.r;
				ppTex[0][y * nLine + x + 1] = color.g;
				ppTex[0][y * nLine + x + 2] = color.b;
				ppTex[0][y * nLine + x + 3] = color.a;
			}
		}
	}
	else
	{
		_AssertExpr(0, "有効な色深度ではありません");
		return FALSE;
	}

	// ファイルクローズ
	fclose(pFile);

	return TRUE;
}

//============================================================================
// JPEGロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : TRUE
//						失敗 : FALSE
// arg1		: char*		ファイル名
// arg2		: char**	テクスチャポインタ
//=============================================================================
BOOL LoadJPEGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	return TRUE;
}

//============================================================================
// PNGロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		成功 : TRUE
//						失敗 : FALSE
// arg1		: char*		ファイル名
// arg2		: char**	テクスチャポインタ
//=============================================================================
BOOL LoadPNGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	_AssertExpr(0, "PNGファイルはサポートされていません");
	// PNGファイルのバイトオーダーはビッグエンディアン
	PNG_IHDR png;

	// ファイルポインタ
	FILE *pFile;
	// ファイルオープン
	pFile = fopen(pFileName, "rb");
	if(!pFile)
	{
		return FALSE;
	}

	// シグネチャ読み込み
	BYTE sig[8];
	fread(sig, 8, 1, pFile);

	// ヘッダ読み込み
	fread(&png, 16, 1, pFile);
	fread(&png.ihDepth, 1, 1, pFile);
	fread(&png.ihColorType, 1, 1, pFile);
	fread(&png.ihCompressionMethod, 1, 1, pFile);
	fread(&png.ihFilteringMethod, 1, 1, pFile);
	fread(&png.ihInterraceMethod, 1, 1, pFile);
	fread(&png.ihCRC, 4, 1, pFile);
	png.ihLength = (png.ihLength >> 24) + (((png.ihLength >> 16) & 0xff) << 8) + (((png.ihLength >> 8) & 0xff) << 16) + ((png.ihLength & 0xff) << 24);
	png.ihChunkType = (png.ihChunkType >> 24) + (((png.ihChunkType >> 16) & 0xff) << 8) + (((png.ihChunkType >> 8) & 0xff) << 16) + ((png.ihChunkType & 0xff) << 24);
	png.ihWidth = (png.ihWidth >> 24) + (((png.ihWidth >> 16) & 0xff) << 8) + (((png.ihWidth >> 8) & 0xff) << 16) + ((png.ihWidth & 0xff) << 24);
	png.ihHeight = (png.ihHeight >> 24) + (((png.ihHeight >> 16) & 0xff) << 8) + (((png.ihHeight >> 8) & 0xff) << 16) + ((png.ihHeight & 0xff) << 24);
	png.ihCRC = (png.ihCRC >> 24) + (((png.ihCRC >> 16) & 0xff) << 8) + (((png.ihCRC >> 8) & 0xff) << 16) + ((png.ihCRC & 0xff) << 24);
	
	// 画像サイズ設定
	*pWidth = png.ihWidth;
	*pHeight = png.ihHeight;

	// イメージデータサイズ
	int imgDatSize;
	// イメージデータチャンクタイプ
	int imgChunkType;
	fread(&imgDatSize, 4, 1, pFile);
	fread(&imgChunkType, 4, 1, pFile);
	imgDatSize = (imgDatSize >> 24) + (((imgDatSize >> 16) & 0xff) << 8) + (((imgDatSize >> 8) & 0xff) << 16) + ((imgDatSize & 0xff) << 24);
	imgChunkType = (imgChunkType >> 24) + (((imgChunkType >> 16) & 0xff) << 8) + (((imgChunkType >> 8) & 0xff) << 16) + ((imgChunkType & 0xff) << 24);

	// 1ライン当たりのバイト数
	int nLine = png.ihWidth * 4;	// rgbaの4バイトっていう前提

	// バッファ確保
	(*ppTex) = new unsigned char[png.ihHeight * nLine];

	// カラータイプによって読み込む大きさを変える
	// RGB
	if(png.ihColorType == 2)
	{
		struct rgb
		{
			BYTE r, g, b;
		};
		rgb color;
		for(int y = 0; y < png.ihHeight; y++)
		{
			for(int x = 0; x < nLine; x += 4)
			{
				fread(&color, 3, 1, pFile);
				ppTex[0][y * nLine + x    ] = color.r;
				ppTex[0][y * nLine + x + 1] = color.g;
				ppTex[0][y * nLine + x + 2] = color.b;
				ppTex[0][y * nLine + x + 3] = 0xff;
			}
		}
	}
	// RGBA
	else if(png.ihColorType == 6)
	{
		fread(*ppTex, nLine * png.ihHeight, 1, pFile);
	}
	else
	{
		return FALSE;
	}

	// ファイルクローズ
	fclose(pFile);

	return TRUE;
}

//============================================================================
// TXOロード
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//
// ret		: int		成功 : TRUE
//						失敗 : FALSE
// arg1		: char*		ファイル名
// arg2		: char**	テクスチャポインタ
//=============================================================================
BOOL LoadTXOFromFile(const char *filename_pointer, unsigned char** texture_double_pointer, unsigned short* width_pointer, unsigned short* height_pointer)
{
	// ファイルポインタ
	FILE *file = nullptr;
	// ファイルオープン
	fopen_s(&file, filename_pointer, "rb");
	if(!file)
	{
		return FALSE;
	}

	// 幅読み込み
	fread(width_pointer, sizeof(unsigned short), 1, file);
	fread(height_pointer, sizeof(unsigned short), 1, file);
	// バッファ生成
	unsigned bufferSize = (*width_pointer) * (*height_pointer) * 4;
	(*texture_double_pointer) = new unsigned char[bufferSize];
	fread((*texture_double_pointer), bufferSize, 1, file);

	fclose(file);

	return TRUE;
}

// EOF