//*****************************************************************************
//
// プレイヤークラス
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************


//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// warning消し
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"
#include "common/math/vector/vector3.h"

//character
#include "player_manager.h"
#include "interface/character/character_interface.h"


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static const int kDefaultDamage = 10;

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPlayer : public CCharacterInterface
{
public:
	// コンストラクタ
	CPlayer(CInterfaceManager* interface_manager);

	// デストラクタ
	~CPlayer(void);

	// 初期化処理
	bool Init(void);

	// 更新処理
	void Update(void);

	// 終了処理
	void Uninit(void);

	// 描画処理
	void Draw(void);

	// ポジションの取得
	const VECTOR3& position(void) const {return position_;}

	// ポジションの設定
	void set_position(const VECTOR3& position){position_ = position;}

	// 角度の取得
	const VECTOR3& rotation(void) const {return rotation_;}

	// 角度の設定
	void set_rotation(const VECTOR3& rotation){rotation_ = rotation;}

	// idの取得
	int player_id(void);
	
	// 死亡フラグアクセサ
	bool death_flag(void){return death_flag_;};
	void SetDeathFlag(bool flag);

	// HPアクセサ
	void set_hp(s16 hp){hp_ = hp;};
	s16 hp(void){return hp_;};

	// ダメージ関数
	void Damage(int damage);
	
	// プレイヤー移動方向取得
	const VECTOR3& get_move_vector();

	// プレイヤー移動スピード取得
	const f32 get_move_speed();

protected:
	// インターフェースマネージャーのポインタ
	CInterfaceManager* interface_manager_;

	// オブジェクトキー
	u32 object_key_;

	// 各種値
	VECTOR3 position_;
	VECTOR3 rotation_;
	VECTOR3 scale_;
	VECTOR3 move_vector_;
	s16		hp_;

private:
	// スピード
	static const f32 SPEED;
	static const f32 SPEED_DEST;
	static const f32 ROTATION_DEST;
	static const f32 BULLET_LAUNCH_HEIGHT_OFFSET;
	//移動目標値変数
	VECTOR3 rotation_dest_;
	bool update_;

	bool death_flag_;
};

//---------------------------------- EOF --------------------------------------

#endif // _PLAYER_H_