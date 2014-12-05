//*****************************************************************************
//
// 矩形3Dクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _RECTANGLE_3D_H_
#define _RECTANGLE_3D_H_

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
class CRectangle3D : public CObject3D
{
public:
	// コンストラクタ
	CRectangle3D(CDeviceHolder* device_holder);

	// デストラクタ
	virtual ~CRectangle3D(void);

	enum POINT
	{
		POINT_CENTER = 0,
		POINT_LEFT_UP,
		POINT_LEFT_MIDDLE,
		POINT_LEFT_DOWN,
		POINT_RIGHT_UP,
		POINT_RIGHT_MIDDLE,
		POINT_RIGHT_DOWN,
		POINT_MIDDLE_UP,
		POINT_MIDDLE_DOWN,
		POINT_MAX,
	};

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(CObject3DData* pObject3DData);

	// 終了処理
	void Uninit(void);

	// 頂点情報の設定
	virtual void Set(void);

	// サイズの設定
	void set_size(const VECTOR2& size){size_ = size;}

	// テクスチャ座標の設定
	void set_texcoord(const f32& left,const f32& right,const f32& top,const f32& bottom){left_ = left;right_ = right;top_ = top;bottom_ = bottom;}

	// カラーの設定
	void set_color(const COLOR4F& color){for(int i = 0;i < VERTEX_MAX;i++){color_[i] = color;}}

	// カラーの設定
	void set_color(const COLOR4F& left_top,const COLOR4F& right_top,const COLOR4F& left_bottom,const COLOR4F& right_bottom){color_[0] = left_top;color_[1] = left_bottom;color_[2] = right_top;color_[3] = right_bottom;}

	// 中心の設定
	void set_point(POINT point){point_ = point;}
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

	// 中心点
	POINT point_;

	// 頂点座標
	VECTOR2 position_[VERTEX_MAX];

	// 頂点情報
	CVertex3D* vertex_3d_;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
