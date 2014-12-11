//*****************************************************************************
//
// バレットクラス
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************
#include "bullet.h"
//billboard
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
void CBullet::SetParameter(const VECTOR3& position,const VECTOR3& vector,const f32& speed)
{
	position_ = position;
	vector_ = vector;
	speed_ = speed;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CBullet::Init(void)
{
	// オブジェクトビルボードの生成
	CBillboard* object_bill = new CBillboard(interface_manager_->graphic_manager()->device_holder());
	object_bill->set_size(VECTOR2(10.0f,10.0f));
	object_bill->Set();

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_bill);

	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	position_ += vector_ * speed_;
}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,position_,VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000");
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit( void )
{
}

//---------------------------------- EOF --------------------------------------
