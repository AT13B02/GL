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
	meshfield_->set_grid_length(50.0f,50.0f);
	meshfield_->set_grid_number(10,10);
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
}

//=============================================================================
// 高さ取得
//=============================================================================
f32 CField::get_height(const VECTOR3& in_position, VECTOR3* p_out_normal)
{
	return meshfield_->get_height(in_position, p_out_normal);
}

//---------------------------------- EOF --------------------------------------
