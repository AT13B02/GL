//*****************************************************************************
//
// タイトルクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _SCENE_MATCH_H_
#define _SCENE_MATCH_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "scene/scene.h"

#include "common/math/vector/vector2.h"
#include "common/math/vector/vector3.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方宣言
//*****************************************************************************
class CSound;
class CRectangle2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSceneMatch : public CScene
{
public:
	// コンストラクタ
	CSceneMatch(CInterfaceManager* interface_manager);

	// デストラクタ
	virtual ~CSceneMatch(void);

	// 初期化
	bool Init(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 終了
	void Uninit(void);

	// ロード
	void Load(void);

	// 自分のファクトリーの作成
	CSceneFactory* MakeFactory(void);

protected:

private:

	typedef enum TEXTURE_TYPE_
	{
		TEXTURE_TYPE_LOGO,
		TEXTURE_TYPE_PLAYER1,
		TEXTURE_TYPE_PLAYER2,
		TEXTURE_TYPE_PLAYER3,
		TEXTURE_TYPE_PLAYER4,
		TEXTURE_TYPE_HOST_DECISION,
		TEXTURE_TYPE_PLAYER1_READY,
		TEXTURE_TYPE_PLAYER2_READY,
		TEXTURE_TYPE_PLAYER3_READY,
		TEXTURE_TYPE_PLAYER4_READY,
		TEXTURE_TYPE_MAX,
	}TEXTURE_TYPE;

	static const char* p_texture_names[TEXTURE_TYPE_MAX];

	static const int PLAYER_MAX = 4;
	static const float PLAYER_DISP_OFFSET_X;
	static const float PLAYER_DISP_OFFSET_Y;
	static const float PLAYER_DISP_START_Y;

	static const float PLAYER_DISP_READY_OFFSET_X;
	static const float PLAYER_DISP_READY_OFFSET_Y;
	static const float PLAYER_DISP_READY_START_Y;

	static const VECTOR2 HOST_DECITION_DEFAULT_POS;
	static const VECTOR2 LOGO_DEFAULT_POS;
	u32 test_object_key_;
	u32 test_2d_key_;


	u32 player_Disp_2d_key_[PLAYER_MAX]; //プレイヤーマッチング表示
	u32 player_ready_disp_2d_key_[PLAYER_MAX]; //プレイヤーマッチング準備表示
	u32 host_decision_key_;				 //ホストが決定を押すときに必要
	u32 logo_key_;						 //ロゴ表示に必要

	CRectangle2D* p_rectRedy[PLAYER_MAX];
	CRectangle2D* p_rect_all_ready_logo;

	
	//TODO
	static const u32 FLASH_ALL_TIME = 40;//点滅の全体時間
	bool draw_flag_;
	u32 flash_timer_;					 //点滅用タイマー
	VECTOR3 player_Disp_2d_pos_;

	bool flag[ PLAYER_MAX ];

	bool changeFlag;
};

#endif	// _SCENE_TITLE_H_

//---------------------------------- EOF --------------------------------------
