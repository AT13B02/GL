//*****************************************************************************
//
// 爆発クラス
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "common/math/math.h"
#include "../character_interface.h"

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
// クラスの前方参照
//*****************************************************************************
class CInterfaceManager;
class CBillboard;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CExplosion : public CCharacterInterface
{
public:
	// コンストラクタ
	CExplosion(CInterfaceManager* interface_manager);

	// デストラクタ
	~CExplosion(void);

	// 初期化
	bool Init(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 終了
	void Uninit(void);

	// パラメータの設定
	void SetParameter(const VECTOR3& position, const s16 u_division_num, const s16 v_division_num, const s16 animation_change_count  );

	//位置取得
	VECTOR3 position( void ){ return position_; }

	//位置セット
	void set_position( const VECTOR3& pos ){ position_ = pos ;}

	//弾消去
	void Erase( void );

private:
	static const f32 DEFAULT_RADIUS;
	u32 object_key_;
	VECTOR3 position_;
	f32 radius_;

	CBillboard *billboard_;					//ビルボード
	s16 u_division_num_;						//分割数
	s16 v_division_num_;						//分割数

	s16 u_division_count;						//分割
	s16 v_division_count;						//分割

	s16 animation_change_count_;			//アニメーション変更カウント
	s16 animation_count_;					//カウンタ

	//テクスチャ
	f32 left_; 
	f32 right_;
	f32 top_;
	f32 bottom_;

	CInterfaceManager* interface_manager_;
};
#endif //_BULLET_H_
//---------------------------------- EOF --------------------------------------
