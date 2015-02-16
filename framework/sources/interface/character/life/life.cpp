//*****************************************************************************
//
// ライフクラス
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************
#include "life.h"
//billboard
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CLife::CLife(CInterfaceManager* interface_manager , s32 max_life , s32 max_length )
{
	interface_manager_ = interface_manager;
	max_life_ = max_life;
	life_ = max_life;
	max_length_ = max_length;
	length_ = max_length;
}

//=============================================================================
// デストラクタ
//=============================================================================
CLife::~CLife(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
void CLife::SetParameter(const VECTOR3& position , const s32& player_id )
{
	position_ = position;
	player_id_ = player_id;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CLife::Init(void)
{
	// オブジェクトビルボードの生成
	object_bill_ = new CBillboard(interface_manager_->graphic_manager()->device_holder());
	object_bill_->set_size(VECTOR2((f32)max_length_,10.0f));
	object_bill_->set_color( COLOR4F( 0.0f , 1.0f , 0.0f , 1.0f ) );
	object_bill_->Set();

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_bill_);
	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CLife::Update(void)
{
	length_ = life_ / max_life_ * max_length_;
	object_bill_->set_size( VECTOR2((f32)length_ , 10.0f ));
	object_bill_->set_color( COLOR4F( 1.0f - life_ / max_life_ , life_ / max_life_ , 0.0f , 1.0f ) );
	object_bill_->Set();
}

//=============================================================================
// 描画処理
//=============================================================================
void CLife::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,position_,VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"snowball001");
}

//=============================================================================
// 終了処理
//=============================================================================
void CLife::Uninit( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	object_3d_manager->EraseList( object_key_ );

}
//=============================================================================
// 消去処理
//=============================================================================
void CLife::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
