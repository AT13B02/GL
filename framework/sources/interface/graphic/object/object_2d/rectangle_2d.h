//*****************************************************************************
//
// 矩形2Dクラス [object_2d.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _RECTANGLE_2D_H_
#define _RECTANGLE_2D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object_2d.h"

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
class CTexture;
class CGraphicsDevice;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CRectangle2D : public CObject2D
{
public:
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

	// 作成処理
	static CRectangle2D* Create(CGraphicsDevice* pGraphicsDevice);

	// 頂点情報の設定
	virtual void Set(void);

	// サイズの設定
	void SetSize(const VECTOR2& Size){m_Size = Size;}

	// テクスチャ座標の設定
	void SetTexcoord(const float& fLeft,const float& fRight,const float& fTop,const float& fBottom){m_fLeft = fLeft;m_fRight = fRight;m_fTop = fTop;m_fBottom = fBottom;}

	// カラーの設定
	void SetColor(const COLOR4F& Color){for(int i = 0;i < VERTEX_MAX;i++){m_Color[i] = Color;}}

	// カラーの設定
	void SetColor(const COLOR4F& LeftTop,const COLOR4F& RightTop,const COLOR4F& LeftBottom,const COLOR4F& RightBottom){m_Color[0] = LeftTop;m_Color[1] = LeftBottom;m_Color[2] = RightTop;m_Color[3] = RightBottom;}

	// 中心の設定
	void SetPoint(POINT Point){m_Point = Point;}

protected:
	static const int VERTEX_MAX = (4);

	// コンストラクタ
	CRectangle2D(void);

	// デストラクタ
	virtual ~CRectangle2D(void);

	// サイズ
	VECTOR2 m_Size;

	// 色
	COLOR4F m_Color[VERTEX_MAX];

	// テクスチャ座標
	float m_fLeft;
	float m_fRight;
	float m_fTop;
	float m_fBottom;

	// 中心点
	POINT m_Point;

	// 頂点座標
	VECTOR2 m_Position[VERTEX_MAX];

private:

};

#endif	// _RECTANGLE_2D_H_

//---------------------------------- EOF --------------------------------------
