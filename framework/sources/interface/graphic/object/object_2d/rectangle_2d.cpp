//*****************************************************************************
//
// 矩形2Dクラス [rectangle_2d.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/10/11(Thu)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "application.h"

#ifdef _USING_OPENGL_
#include "gl_rectangle_2d.h"
#endif

#ifdef _USING_DIRECTX_
#include "dx_rectangle_2d.h"
#endif

#include "rectangle_2d.h"
#include "common.h"

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
// コンストラクタ
//=============================================================================
CRectangle2D::CRectangle2D(void)
{
	// サイズの初期化
	m_Size.x = 0.0f;
	m_Size.y = 0.0f;

	// テクスチャ座標の初期化
	m_fLeft   = 0.0f;
	m_fRight  = 1.0f;
	m_fTop    = 0.0f;
	m_fBottom = 1.0f;

	for(int i = 0;i < VERTEX_MAX;i++)
	{
		// 色の初期化
		m_Color[i] = COLOR4F(1.0f,1.0f,1.0f,1.0f);
	}
	// 中心点の初期化
	m_Point = POINT_CENTER;
}

//=============================================================================
// デストラクタ
//=============================================================================
CRectangle2D::~CRectangle2D(void)
{
}

//=============================================================================
// 作成処理
//=============================================================================
CRectangle2D* CRectangle2D::Create(CGraphicsDevice* pGraphicsDevice)
{
	CRectangle2D* pRectangle = NULL;

#ifdef _USING_OPENGL_
	pRectangle = new CGLRectangle2D(pGraphicsDevice);
#endif

#ifdef _USING_DIRECTX_
	pRectangle = new CDXRectangle2D(pGraphicsDevice);
#endif

	return pRectangle;
}

//=============================================================================
// 設定処理
//=============================================================================
void CRectangle2D::Set(void)
{
	switch(m_Point)
	{
		case POINT_CENTER:
		{
			m_Position[0] = VECTOR2(-m_Size.x * 0.5f,-m_Size.y * 0.5f);
			m_Position[1] = VECTOR2(-m_Size.x * 0.5f, m_Size.y * 0.5f);
			m_Position[2] = VECTOR2( m_Size.x * 0.5f,-m_Size.y * 0.5f);
			m_Position[3] = VECTOR2( m_Size.x * 0.5f, m_Size.y * 0.5f);
			break;
		}
		case POINT_LEFT_UP:
		{
			m_Position[0] = VECTOR2(    0.0f,    0.0f);
			m_Position[1] = VECTOR2(    0.0f,m_Size.y);
			m_Position[2] = VECTOR2(m_Size.x,    0.0f);
			m_Position[3] = VECTOR2(m_Size.x,m_Size.y);
			break;
		}
		case POINT_LEFT_MIDDLE:
		{
			m_Position[0] = VECTOR2(    0.0f,-m_Size.y * 0.5f);
			m_Position[1] = VECTOR2(    0.0f, m_Size.y * 0.5f);
			m_Position[2] = VECTOR2(m_Size.x,-m_Size.y * 0.5f);
			m_Position[3] = VECTOR2(m_Size.x, m_Size.y * 0.5f);
			break;
		}
		case POINT_LEFT_DOWN:
		{
			m_Position[0] = VECTOR2(    0.0f,-m_Size.y);
			m_Position[1] = VECTOR2(    0.0f,     0.0f);
			m_Position[2] = VECTOR2(m_Size.x,-m_Size.y);
			m_Position[3] = VECTOR2(m_Size.x,     0.0f);
			break;
		}
		case POINT_RIGHT_UP:
		{
			m_Position[0] = VECTOR2(-m_Size.x,    0.0f);
			m_Position[1] = VECTOR2(-m_Size.x,m_Size.y);
			m_Position[2] = VECTOR2(     0.0f,    0.0f);
			m_Position[3] = VECTOR2(     0.0f,m_Size.y);
			break;
		}
		case POINT_RIGHT_MIDDLE:
		{
			m_Position[0] = VECTOR2(-m_Size.x,-m_Size.y * 0.5f);
			m_Position[1] = VECTOR2(-m_Size.x, m_Size.y * 0.5f);
			m_Position[2] = VECTOR2(     0.0f,-m_Size.y * 0.5f);
			m_Position[3] = VECTOR2(     0.0f, m_Size.y * 0.5f);
			break;
		}
		case POINT_RIGHT_DOWN:
		{
			m_Position[0] = VECTOR2(-m_Size.x,-m_Size.y);
			m_Position[1] = VECTOR2(-m_Size.x,     0.0f);
			m_Position[2] = VECTOR2(     0.0f,-m_Size.y);
			m_Position[3] = VECTOR2(     0.0f,     0.0f);
			break;
		}
		case POINT_MIDDLE_UP:
		{
			m_Position[0] = VECTOR2(-m_Size.x * 0.5f,    0.0f);
			m_Position[1] = VECTOR2(-m_Size.x * 0.5f,m_Size.y);
			m_Position[2] = VECTOR2( m_Size.x * 0.5f,    0.0f);
			m_Position[3] = VECTOR2( m_Size.x * 0.5f,m_Size.y);
			break;
		}
		case POINT_MIDDLE_DOWN:
		{
			m_Position[0] = VECTOR2(-m_Size.x * 0.5f,-m_Size.y);
			m_Position[1] = VECTOR2(-m_Size.x * 0.5f,     0.0f);
			m_Position[2] = VECTOR2( m_Size.x * 0.5f,-m_Size.y);
			m_Position[3] = VECTOR2( m_Size.x * 0.5f,     0.0f);
			break;
		}
	}
}

//---------------------------------- EOF --------------------------------------
