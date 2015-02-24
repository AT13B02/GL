//*****************************************************************************
//
// ビルボードクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/element/object_3d.h"

// common
#include "common/image/color/color4f.h"

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
class CVertex3D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CBillboard : public CObject3D
{
public:
	// コンストラクタ
	CBillboard(CDeviceHolder* device_holder);

	// デストラクタ
	virtual ~CBillboard(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(CObject3DData* object_3d_data);

	// 終了処理
	void Uninit(void);

	// 頂点情報の設定
	void Set(void);

	// サイズの設定
	void set_size(const VECTOR2& size){size_ = size;}

	// テクスチャ座標の設定
	void set_texcoord(const f32& left,const f32& right,const f32& top,const f32& bottom){left_ = left;right_ = right;top_ = top;bottom_ = bottom;}

	// カラーの設定
	void set_color(const COLOR4F& Color){for(int i = 0;i < VERTEX_MAX;i++){color_[i] = Color;}}

	// カラーの設定
	void set_color(const COLOR4F& LeftTop,const COLOR4F& RightTop,const COLOR4F& LeftBottom,const COLOR4F& RightBottom){color_[0] = LeftTop;color_[1] = LeftBottom;color_[2] = RightTop;color_[3] = RightBottom;}

protected:



private:
	static const int VERTEX_MAX = (4);

	// サイズ
	VECTOR2 size_;

	// 色
	COLOR4F color_[VERTEX_MAX];

	// テクスチャ座標
	f32 left_;
	f32 right_;
	f32 top_;
	f32 bottom_;

	// 頂点座標
	VECTOR2 position_[VERTEX_MAX];

	// 頂点情報
	CVertex3D* vertex_3d_;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
