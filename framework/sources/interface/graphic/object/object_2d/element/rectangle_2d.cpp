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
#include "basic/application.h"

// graphic
#include "interface/graphic/vertex/vertex_2d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/texture/texture.h"

// common
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
// コンストラクタ
//=============================================================================
CRectangle2D::CRectangle2D(CDeviceHolder* device_holder) : CObject2D(device_holder,OBJECT_2D_TYPE_RECTANGLE)
{
	left_   = 0.0f;
	right_  = 1.0f;
	top_    = 0.0f;
	bottom_ = 1.0f;

	point_ = POINT_CENTER;

	size_ = VECTOR2(0.0f,0.0f);


	for(int i = 0;i < VERTEX_MAX;i++)
	{
		color_[i] = COLOR4F(1.0f,1.0f,1.0f,1.0f);
	}

	vertex_2d_ = CVertex2D::Create(device_holder,4);
}

//=============================================================================
// デストラクタ
//=============================================================================
CRectangle2D::~CRectangle2D(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CRectangle2D::Init(void)
{
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CRectangle2D::Draw(CObject2DData* object_2d_data)
{
	MATRIX4x4 matrix;
	CTextureManager* texture_manager = object_2d_data->texture_manager();
	CTexture* texture = texture_manager->Get(object_2d_data->texture_name().c_str());
	CRenderstate* renderstate = object_2d_data->renderstate();

	matrix = GetWorldMatrix(object_2d_data);

	CObject2D::Draw(matrix,vertex_2d_,texture,renderstate);
}

//=============================================================================
// 終了
//=============================================================================
void CRectangle2D::Uninit (void)
{
	SAFE_RELEASE(vertex_2d_);
}

//=============================================================================
// 設定処理
//=============================================================================
void CRectangle2D::Set(void)
{
	switch(point_)
	{
		case POINT_CENTER:
		{
			position_[0] = VECTOR2(-size_._x * 0.5f,-size_._y * 0.5f);
			position_[1] = VECTOR2(-size_._x * 0.5f, size_._y * 0.5f);
			position_[2] = VECTOR2( size_._x * 0.5f,-size_._y * 0.5f);
			position_[3] = VECTOR2( size_._x * 0.5f, size_._y * 0.5f);
			break;
		}
		case POINT_LEFT_UP:
		{
			position_[0] = VECTOR2(    0.0f,     0.0f);
			position_[1] = VECTOR2(    0.0f,-size_._y);
			position_[2] = VECTOR2(size_._x,     0.0f);
			position_[3] = VECTOR2(size_._x,-size_._y);
			break;
		}
		case POINT_LEFT_MIDDLE:
		{
			position_[0] = VECTOR2(    0.0f, size_._y * 0.5f);
			position_[1] = VECTOR2(    0.0f,-size_._y * 0.5f);
			position_[2] = VECTOR2(size_._x, size_._y * 0.5f);
			position_[3] = VECTOR2(size_._x,-size_._y * 0.5f);
			break;
		}
		case POINT_LEFT_DOWN:
		{
			position_[0] = VECTOR2(    0.0f,size_._y);
			position_[1] = VECTOR2(    0.0f,    0.0f);
			position_[2] = VECTOR2(size_._x,size_._y);
			position_[3] = VECTOR2(size_._x,    0.0f);
			break;
		}
		case POINT_RIGHT_UP:
		{
			position_[0] = VECTOR2(-size_._x,     0.0f);
			position_[1] = VECTOR2(-size_._x,-size_._y);
			position_[2] = VECTOR2(     0.0f,     0.0f);
			position_[3] = VECTOR2(     0.0f,-size_._y);
			break;
		}
		case POINT_RIGHT_MIDDLE:
		{
			position_[0] = VECTOR2(-size_._x, size_._y * 0.5f);
			position_[1] = VECTOR2(-size_._x,-size_._y * 0.5f);
			position_[2] = VECTOR2(     0.0f, size_._y * 0.5f);
			position_[3] = VECTOR2(     0.0f,-size_._y * 0.5f);
			break;
		}
		case POINT_RIGHT_DOWN:
		{
			position_[0] = VECTOR2(-size_._x,size_._y);
			position_[1] = VECTOR2(-size_._x,    0.0f);
			position_[2] = VECTOR2(     0.0f,size_._y);
			position_[3] = VECTOR2(     0.0f,    0.0f);
			break;
		}
		case POINT_MIDDLE_UP:
		{
			position_[0] = VECTOR2(-size_._x * 0.5f,     0.0f);
			position_[1] = VECTOR2(-size_._x * 0.5f,-size_._y);
			position_[2] = VECTOR2( size_._x * 0.5f,     0.0f);
			position_[3] = VECTOR2( size_._x * 0.5f,-size_._y);
			break;
		}
		case POINT_MIDDLE_DOWN:
		{
			position_[0] = VECTOR2(-size_._x * 0.5f,size_._y);
			position_[1] = VECTOR2(-size_._x * 0.5f,    0.0f);
			position_[2] = VECTOR2( size_._x * 0.5f,size_._y);
			position_[3] = VECTOR2( size_._x * 0.5f,    0.0f);
			break;
		}
	}

	CVertex2D::VERTEX_2D* pVertex2D = NULL;

	vertex_2d_->Lock(&pVertex2D,NULL);

	// 頂点座標の設定
	pVertex2D->_position[0] = VECTOR2(position_[0]._x,position_[0]._y);
	pVertex2D->_position[1] = VECTOR2(position_[2]._x,position_[2]._y);
	pVertex2D->_position[2] = VECTOR2(position_[1]._x,position_[1]._y);
	pVertex2D->_position[3] = VECTOR2(position_[3]._x,position_[3]._y);

	// テクスチャ座標の設定
	pVertex2D->_texcoord[0] = VECTOR2(left_,top_);
	pVertex2D->_texcoord[1] = VECTOR2(right_,top_);
	pVertex2D->_texcoord[2] = VECTOR2(left_,bottom_);
	pVertex2D->_texcoord[3] = VECTOR2(right_,bottom_);

	// 色情報の設定
	pVertex2D->_color[0] = color_[0];
	pVertex2D->_color[1] = color_[2];
	pVertex2D->_color[2] = color_[3];
	pVertex2D->_color[3] = color_[1];

	// 頂点情報をアンロックする
	vertex_2d_->Unlock();
}


#if 0
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
#endif
//---------------------------------- EOF --------------------------------------
