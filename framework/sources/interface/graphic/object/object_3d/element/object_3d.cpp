//*****************************************************************************
//
// オブジェクト3Dクラス
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
#include "interface/graphic/object/object_3d/object_3d_data.h"
#include "interface/graphic/object/object_3d/element/object_3d.h"
#include "interface/graphic/vertex/vertex_3d.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/texture/texture.h"
#include "interface/graphic/renderstate/state/renderstate.h"
#include "interface/graphic/renderstate/renderstate_manager.h"

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
CObject3D::CObject3D(CDeviceHolder* device_holder,OBJECT_3D_TYPE object_3d_type)
{
	device_holder_ = device_holder;

	object_3d_type_ = object_3d_type;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3D::~CObject3D(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
MATRIX4x4 CObject3D::GetWorldMatrix(CObject3DData* object_3d_data) const
{
	VECTOR3 position = object_3d_data->position();
	VECTOR3 rotation = object_3d_data->rotation();
	VECTOR3 scale = object_3d_data->scale();
	MATRIX4x4 matrix = object_3d_data->matrix();

	MATRIX4x4 translation_matrix;
	MATRIX4x4 rotation_matrix;
	MATRIX4x4 scale_matrix;
	MATRIX4x4 world_matrix;

#ifdef _USING_DIRECTX_
	//Pos.z *= -1;
	//Rot.y *= -1;
	//Rot.x *= -1;
#endif
	translation_matrix.SetTlanslation(position._x,position._y,position._z);

	rotation_matrix.SetYawPitchRoll(rotation._x * MTH_DEGREE,rotation._y * MTH_DEGREE,rotation._z * MTH_DEGREE);

	scale_matrix.SetScaling(scale._x,scale._y,scale._z);

	// ワールドマトリクスの計算
	world_matrix = scale_matrix * rotation_matrix * translation_matrix * matrix;

	return world_matrix;
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject3D::Draw(const MATRIX4x4& matrix,CVertex3D* vertex_3d,CTexture* texture,CRenderstateManager* renderstate_manager,std::list<u32> renderstate_list)
{
	for(auto it = renderstate_list.begin();it != renderstate_list.end();++it)
	{
		renderstate_manager->renderstate((CRenderstateManager::TYPE)*it)->Set();
	}

	if(texture != NULL)
	{
		texture->Set();
	}

	if(vertex_3d != NULL)
	{
		vertex_3d->Draw(matrix);
	}

	if(texture != NULL)
	{
		texture->Unset();
	}

	for(auto it = renderstate_list.begin();it != renderstate_list.end();++it)
	{
		renderstate_manager->renderstate((CRenderstateManager::TYPE)*it)->Unset();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject3D::Draw(const MATRIX4x4& matrix,CModel* model,CRenderstateManager* renderstate_manager,std::list<u32> renderstate_list)
{
	for(auto it = renderstate_list.begin();it != renderstate_list.end();++it)
	{
		renderstate_manager->renderstate((CRenderstateManager::TYPE)*it)->Set();
	}

	if(model != NULL)
	{
		model->Draw(matrix);
	}

	for(auto it = renderstate_list.begin();it != renderstate_list.end();++it)
	{
		renderstate_manager->renderstate((CRenderstateManager::TYPE)*it)->Unset();
	}
}

//---------------------------------- EOF --------------------------------------
