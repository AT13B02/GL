//********************************************************************
// UDPデータ送受信プログラム
// メインの処理(main.h)
// aughter: NAOKI NOJIRI  20236
//********************************************************************
#ifndef _MAIN_H_
#define _MAIN_H_

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
	NETWORK_DATA_TYPE_REQUEST_PLAYER_NUMBER	= 1,
	NETWORK_DATA_TYPE_POSITION				= 2,
	NETWORK_DATA_TYPE_ROTATION				= 3,
	NETWORK_DATA_TYPE_SPEED					= 4,
	NETWORK_DATA_TYPE_FRONT_VECTOR			= 5,
	NETWORK_DATA_TYPE_ANIMATION_ID			= 6,
	NETWORK_DATA_TYPE_ALL_SEND				= 7,
	NETWORK_DATA_TYPE_SEND_PLAYER_NUMBER	= 8,
	NETWORK_DATA_TYPE_GO_TO_RESULT			= 9,
	NETWORK_DATA_TYPE_END					= 10,
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
	char				game_ID[16];	// 班識別ID
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



#endif
//-----EOF--------