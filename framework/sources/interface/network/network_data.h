//*****************************************************************************
//
// ネットワークデータクラス [network_data.h]
//
// Author		: KENJI KABUTOMORI
//				  NAOKI NOJIRI
// Date			: 2014/09/17(Wed)
// Version		: 1.01
// Update Date	: 2014/12/01(Mon)
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _NETWORK_DATA_H_
#define _NETWORK_DATA_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "../../basic/basic.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static const char* kGameID = "class_B_2";		// ゲーム(班)識別子

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	short Type;
}NETWORK_DATA_EVENT;

typedef struct
{
	float x, y, z;
}NETWORK_DATA_POSITION;

typedef struct
{
	float x, y, z;
}NETWORK_DATA_ROTATION;

typedef struct
{
	float speed;
}NETWORK_DATA_SPEED;

typedef struct
{
	float x, y, z;
}NETWORK_DATA_FRONT_VECTOR;

typedef struct
{
	int animation_ID;
}NETWORK_DATA_ANIMATION_ID;

// 送信するもの
typedef enum NETWORK_DATA_TYPE
{
	NETWORK_DATA_TYPE_EVENT					= 0,
	NETWORK_DATA_TYPE_REQUEST_PLAYER_NUMBER	= 1,	// IDほしい
	NETWORK_DATA_TYPE_POSITION				= 2,	// posです
	NETWORK_DATA_TYPE_ROTATION				= 3,	// rotです
	NETWORK_DATA_TYPE_SPEED					= 4,	// spdです
	NETWORK_DATA_TYPE_FRONT_VECTOR			= 5,	// frontVecです
	NETWORK_DATA_TYPE_ANIMATION_ID			= 6,	// アニメーション番号です
	NETWORK_DATA_TYPE_ALL_SEND				= 7,	// 全部送りました
	NETWORK_DATA_TYPE_SEND_PLAYER_NUMBER	= 8,	// ID送ります
	NETWORK_DATA_TYPE_GO_TO_RESULT			= 9,	// リザルトへ
	NETWORK_DATA_TYPE_SEND_READY			= 10,	// 準備完了しました(自分)
	NETWORK_DATA_TYPE_CHECK_END_PREPARE		= 11,	// 全員準備完了したかの確認
	NETWORK_DATA_TYPE_END_PREPARE			= 12,	// 全員準備完了
	NETWORK_DATA_TYPE_NOT_END_PREPARE		= 13,	// まだ準備完了してない
	NETWORK_DATA_TYPE_GO_TO_GAME			= 14,	// ゲーム開始
	NETWORK_DATA_TYPE_DEATH					= 15,	// やられた
	NETWORK_DATA_TYPE_END_GAME				= 16,	// ゲーム終了通知
	NETWORK_DATA_TYPE_RECIVE_DEATH			= 17,	// デスフラグ受信
	NETWORK_DATA_TYPE_END					= 18,
};

// 自身は何か
typedef enum NETWORK_MY_TYPE
{
	MY_TYPE_CHARCTER = 0,
	MY_TYPE_BULLET,
	MY_TYPE_EFFECT,
	MY_TYPE_MAX
};

typedef struct
{
	char				game_ID[16];// 班識別ID
	NETWORK_MY_TYPE		my_type;	// 自分のタイプ（何かをあらわす）
	int					my_ID;		// プレイヤーID
	NETWORK_DATA_TYPE	data_type;	// 何の情報か

	union
	{
		NETWORK_DATA_EVENT			event;
		NETWORK_DATA_POSITION		position;
		NETWORK_DATA_ROTATION		rotation;
		NETWORK_DATA_SPEED			speed;
		NETWORK_DATA_FRONT_VECTOR	front_vector;
		NETWORK_DATA_ANIMATION_ID	animation_ID;
	};
}NETWORK_DATA;

#endif	// _NETWORK_DATA_H_

//---------------------------------- EOF --------------------------------------
