//*****************************************************************************
//
// オブジェクト2Dクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/application.h"

// graphic
#include "interface/graphic/object/object_2d/object_2d_data.h"
#include "interface/graphic/object/object_2d/object_2d.h"
#include "interface/graphic/vertex/vertex_2d.h"
#include "interface/graphic/texture/texture.h"
#include "interface/graphic/renderstate/state/renderstate.h"

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
CObject2D::CObject2D(CDeviceHolder* device_holder,OBJECT_2D_TYPE object_2d_type)
{
	device_holder_ = device_holder;

	object_2d_type_ = object_2d_type;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject2D::~CObject2D(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject2D::Draw(const MATRIX4x4& matrix,CVertex2D* vertex_2d,CTexture* texture,CRenderstate* renderstate)
{
	if(renderstate != NULL)
	{
		renderstate->Set();
	}

	if(texture != NULL)
	{
		texture->Set();
	}

	if(vertex_2d != NULL)
	{
		vertex_2d->Draw(matrix);
	}

	if(renderstate != NULL)
	{
		renderstate->Unset();
	}

	if(texture != NULL)
	{
		texture->Unset();
	}
}

//=============================================================================
// ワールドマトリックスの計算処理
//=============================================================================
MATRIX4x4 CObject2D::GetWorldMatrix(CObject2DData* object_2d_data)
{
	VECTOR2 position = object_2d_data->position();
	f32 rotation = object_2d_data->rotation();
	VECTOR2 scale = object_2d_data->scale();
	MATRIX4x4 matrix = object_2d_data->matrix();

	MATRIX4x4 translation_matrix;
	MATRIX4x4 rotation_matrix;
	MATRIX4x4 scale_matrix;
	MATRIX4x4 world_matrix;

#ifdef _USING_DIRECTX_
	//Pos.z *= -1;
	//Rot.y *= -1;
	//Rot.x *= -1;
#endif
	translation_matrix.SetTlanslation(position._x,position._y,0.0f);

	rotation_matrix.SetYawPitchRoll(0.0f,rotation * MTH_DEGREE,0.0f);

	scale_matrix.SetScaling(scale._x,scale._y,1.0f);

	// ワールドマトリクスの計算
	world_matrix = scale_matrix * rotation_matrix * translation_matrix * matrix;

	return world_matrix;
}

//---------------------------------- EOF --------------------------------------
