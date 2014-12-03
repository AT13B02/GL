//*****************************************************************************
//
// 矩形3Dクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/application.h"

// graphic
#include "interface/graphic/vertex/vertex_3d.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/texture/texture.h"

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
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
CRectangle3D::CRectangle3D(CDeviceHolder* device_holder) : CObject3D(device_holder,OBJECT_3D_TYPE_RECTANGLE)
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

	vertex_3d_ = CVertex3D::Create(device_holder,4);
}

//=============================================================================
// デストラクタ
//=============================================================================
CRectangle3D::~CRectangle3D(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CRectangle3D::Init(void)
{
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CRectangle3D::Draw(CObject3DData* object_3d_data)
{
	MATRIX4x4 matrix;
	CTextureManager* texture_manager = object_3d_data->texture_manager();
	CTexture* texture = texture_manager->Get(object_3d_data->texture_name().c_str());
	CRenderstate* renderstate = object_3d_data->renderstate();

	matrix = GetWorldMatrix(object_3d_data);

	CObject3D::Draw(matrix,vertex_3d_,texture,renderstate);
}

//=============================================================================
// 終了
//=============================================================================
void CRectangle3D::Uninit (void)
{
	SAFE_RELEASE(vertex_3d_);
}

//=============================================================================
// 設定処理
//=============================================================================
void CRectangle3D::Set(void)
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
			position_[0] = VECTOR2(    0.0f,-size_._y);
			position_[1] = VECTOR2(    0.0f,     0.0f);
			position_[2] = VECTOR2(size_._x,-size_._y);
			position_[3] = VECTOR2(size_._x,     0.0f);
			break;
		}
		case POINT_LEFT_MIDDLE:
		{
			position_[0] = VECTOR2(    0.0f,-size_._y * 0.5f);
			position_[1] = VECTOR2(    0.0f, size_._y * 0.5f);
			position_[2] = VECTOR2(size_._x,-size_._y * 0.5f);
			position_[3] = VECTOR2(size_._x, size_._y * 0.5f);
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
			position_[0] = VECTOR2(-size_._x,-size_._y);
			position_[1] = VECTOR2(-size_._x,     0.0f);
			position_[2] = VECTOR2(     0.0f,-size_._y);
			position_[3] = VECTOR2(     0.0f,     0.0f);
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
			position_[0] = VECTOR2(-size_._x * 0.5f,-size_._y);
			position_[1] = VECTOR2(-size_._x * 0.5f,     0.0f);
			position_[2] = VECTOR2( size_._x * 0.5f,-size_._y);
			position_[3] = VECTOR2( size_._x * 0.5f,     0.0f);
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

	CVertex3D::VERTEX_3D* pVertex3D = NULL;

	vertex_3d_->Lock(&pVertex3D,NULL);

	// 頂点座標の設定
	pVertex3D->_position[0] = VECTOR3(position_[0]._x,position_[0]._y,0.0f);
	pVertex3D->_position[1] = VECTOR3(position_[2]._x,position_[2]._y,0.0f);
	pVertex3D->_position[2] = VECTOR3(position_[1]._x,position_[1]._y,0.0f);
	pVertex3D->_position[3] = VECTOR3(position_[3]._x,position_[3]._y,0.0f);

	// 法線情報の設定
	pVertex3D->_normal[0] = VECTOR3(0.0f,0.0f,-1.0f);
	pVertex3D->_normal[1] = VECTOR3(0.0f,0.0f,-1.0f);
	pVertex3D->_normal[2] = VECTOR3(0.0f,0.0f,-1.0f);
	pVertex3D->_normal[3] = VECTOR3(0.0f,0.0f,-1.0f);

	// テクスチャ座標の設定
	pVertex3D->_texcoord[0] = VECTOR2(left_,top_);
	pVertex3D->_texcoord[1] = VECTOR2(right_,top_);
	pVertex3D->_texcoord[2] = VECTOR2(left_,bottom_);
	pVertex3D->_texcoord[3] = VECTOR2(right_,bottom_);

	// 色情報の設定
	pVertex3D->_color[0] = color_[0];
	pVertex3D->_color[1] = color_[2];
	pVertex3D->_color[2] = color_[3];
	pVertex3D->_color[3] = color_[1];

	// 頂点情報をアンロックする
	vertex_3d_->Unlock();
}

//---------------------------------- EOF --------------------------------------
