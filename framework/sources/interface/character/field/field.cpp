//*****************************************************************************
//
// フィールドクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "field.h"
#include "interface/graphic/object/object_3d/element/meshfield.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

#include "../character_manager.h"
#include "../bullet/bullet_manager.h"
#include "../bullet/bullet.h"

#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CField::CField(CInterfaceManager* interface_manager)
{
	// インターフェースマネージャーの保存
	interface_manager_ = interface_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CField::~CField(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CField::Init(void)
{
	// オブジェクトモデルの生成
	meshfield_ = new CMeshfield(interface_manager_->graphic_manager()->device_holder());
	meshfield_->Init();
	meshfield_->set_length_grid(50.0f,50.0f);
	meshfield_->set_number_grid(10,10);
	meshfield_->set_height_seed(0);
	meshfield_->Set();

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(meshfield_);

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CField::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CField::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000");
}

//=============================================================================
// 終了処理
//=============================================================================
void CField::Uninit(void)
{
	// ここで呼ぶと落ちる！！！！！！
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	
	//object_3d_manager->EraseList(object_key_);
}

//=============================================================================
// 高さ取得
//=============================================================================
f32 CField::GetHeight(const VECTOR3& in_position, VECTOR3* p_out_normal) const
{
	return meshfield_->GetHeight(in_position,p_out_normal);
}

//=============================================================================
// フィールドX座標最大値
//=============================================================================
f32 CField::get_max_x(void) const
{
	return meshfield_->max_x();
}

//=============================================================================
// フィールドX座標最小値
//=============================================================================
f32 CField::get_min_x(void) const
{
	return meshfield_->min_x();
}

//=============================================================================
// フィールドZ座標最大値
//=============================================================================
f32 CField::get_max_z(void) const
{
	return meshfield_->max_z();
}

//=============================================================================
// フィールドZ座標最小値
//=============================================================================
f32 CField::get_min_z(void) const
{
	return meshfield_->min_z();
}

//---------------------------------- EOF --------------------------------------
