//*****************************************************************************
//
// tgaファイル関連
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "tga.h"
#include <stdio.h>

//*****************************************************************************
// warning消し
//*****************************************************************************
#pragma warning (disable : 4005)
#pragma warning (disable : 4996)

//*****************************************************************************
// マクロ定義
//*****************************************************************************
bool LoadTGAHeader(FILE* file,TGAHEADERFORMAT* tga_header_format);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// TGAファイル読み込み処理
//=============================================================================
bool LoadTGATexture(const s8* filename,IMAGE* out_image,bool convert_flag)
{
	COLOR4F* color;				// 色情報
	TGAHEADERFORMAT tga_header_format;		// ヘッダ情報
	int color_size = 0;				// 色情報数
	IMAGE image;
	IMAGE work;
	FILE* file = NULL;;

	file = fopen(filename,"rb");

	if(file == NULL)
	{
		return false;
	}

	// ヘッダ情報のロード
	LoadTGAHeader(file,&tga_header_format);

	// 色情報があるところまで飛ぶ
	fseek(file,18,SEEK_SET);

	// 色情報数を取得
	color_size = tga_header_format._image_width * tga_header_format._image_height;

	// RGBA
	if(tga_header_format._bit_per_pixel == 32)
	{
		// 色情報を作成
		color = new COLOR4F[color_size];

		for(int i = 0;i < color_size;i++)
		{
			u8 work = 0;

			// B
			fread(&work,1,1,file);

			color[i]._blue = ((float)((int)(work))) / 255.0f;

			// G
			fread(&work,1,1,file);

			color[i]._green = ((float)((int)(work))) / 255.0f;

			// R
			fread(&work,1,1,file);

			color[i]._red = ((float)(((int)(work)))) / 255.0f;

			// A
			fread(&work,1,1,file);

			color[i]._alpha = ((float)((int)(work))) / 255.0f;

		}
	}
	// RGB
	else if(tga_header_format._bit_per_pixel == 24)
	{
		// 色情報を作成
		color = new COLOR4F[color_size];

		for(int i = 0;i < color_size;i++)
		{
			u8 work = 0;

			// B
			fread(&work,1,1,file);

			color[i]._blue = (float)((int)(work)) / 255.0f;

			// G
			fread(&work,1,1,file);

			color[i]._green = (float)((int)(work)) / 255.0f;

			// R
			fread(&work,1,1,file);

			color[i]._red = (float)((int)(work)) / 255.0f;

			// A
			color[i]._alpha = 1.0f;
		}
	}
	else
	{
		return false;
	}

	// イメージの横幅を格納
	image._width = tga_header_format._image_width;

	// イメージの縦幅を格納
	image._height = tga_header_format._image_height;

	// 色情報を格納
	image._color = color;

	// 変換フラグを確認
	if(convert_flag)
	{
		if(tga_header_format._discnpter & 0x10)
		{
			// 左右変換
			FlipHorizontalImage(&work,image);
			delete[] image._color;
			image._color = work._color;
		}

		if(!(tga_header_format._discnpter & 0x20))
		{
			// 上下変換
			FlipVerticalImage(&work,image);
			delete[] image._color;
			image._color = work._color;
		}
	}

	*out_image = image;

	return true;
}

//=============================================================================
// TGAファイルのヘッダ読み込み処理
//=============================================================================
bool LoadTGAHeader(FILE* file,TGAHEADERFORMAT* tga_header_format)
{
	// ファイルの先頭に移動
	fseek(file,0,SEEK_SET);

	// IDの読み込み
	fread(&tga_header_format->_id,1,1,file);

	// カラーマップの読み込み
	fread(&tga_header_format->_color_map_type,1,1,file);

	// イメージタイプの読み込み
	fread(&tga_header_format->_image_type,1,1,file);

	// カラーマップインデックスの読み込み
	fread(&tga_header_format->_color_map_index,2,1,file);

	// カラーマップレングスの読み込み
	fread(&tga_header_format->_color_map_length,2,1,file);
	fread(&tga_header_format->_color_map_size,1,1,file);
	fread(&tga_header_format->_image_orign_x,2,1,file);
	fread(&tga_header_format->_image_orign_y,2,1,file);
	fread(&tga_header_format->_image_width,2,1,file);
	fread(&tga_header_format->_image_height,2,1,file);
	fread(&tga_header_format->_bit_per_pixel,1,1,file);
	fread(&tga_header_format->_discnpter,1,1,file);

	return true;
}

//-----------------------------------EOF---------------------------------------
