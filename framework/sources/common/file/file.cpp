//*****************************************************************************
//
// ファイル関連
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <stdio.h>
#include <string.h>

#include "common/file/file.h"
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
// 拡張子取得
//=============================================================================
void GetExtensionName(s8* out[],const s8* filename)
{
	s32 len = 0;
	s32 dot = 0;	// 文字列の最後からドットまでの文字数

	// NULLチェック
	if(filename == NULL)
	{
		return;
	}

	// ファイル名の長さの取得
	len = strlen(filename);

	// 拡張子位置を見つける
	for(s32 i = 0;i < len;i++)
	{
		if(filename[len - i] == '.')
		{
			dot = i;
		}
	}

	*out = new char[dot + 1];

	strcpy(*out,&filename[len - dot + 1]);

}
//-----------------------------------EOF---------------------------------------
