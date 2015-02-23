//*****************************************************************************
//
// 箱クラス
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "box.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

#include "../character_manager.h"

#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBox::CBox(CInterfaceManager* interface_manager)
{
	//インターフェースマネージャーの保存
	interface_manager_ = interface_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBox::~CBox(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CBox::Init(void)
{
	// オブジェクトモデルの生成
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);
	
	//値初期化
	position_ = VECTOR3(0.0f,0.0f,0.0f);
	rotation_ = VECTOR3(0.0f,0.0f,0.0f);
	scale_    = VECTOR3(1.0f,1.0f,1.0f);

	// 当たり判定初期化
	collision_.add(-25.0f,  0.0f, -25.0f);
	collision_.add( 25.0f, 50.0f,  25.0f);

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBox::Update(void)
{
}

//=============================================================================
// 終了処理
//=============================================================================
void CBox::Uninit(void)
{
}

//=============================================================================
//描画
//=============================================================================
void CBox::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"yukidaruma");
}

//=============================================================================
// 座標設定
//=============================================================================
void CBox::position(const VECTOR3& position)
{
	position_._x = position._x;
	position_._y = position._y;
	position_._z = position._z;
}

//=============================================================================
// 座標設定
//=============================================================================
void CBox::position(const f32 x, const f32 y, const f32 z)
{
	position_._x = x;
	position_._y = y;
	position_._z = z;
}

//=============================================================================
// 座標取得
//=============================================================================
const VECTOR3& CBox::position()
{
	return position_;
}

//=============================================================================
// 当たり判定取得
//=============================================================================
const AABB& CBox::collision()
{
	return collision_;
}

// EOF