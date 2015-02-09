//*****************************************************************************
//
// ユーザーナンバー(2D)クラス
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************
#include "user_number_2d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CUserNumber2D::CUserNumber2D(CInterfaceManager* interface_manager , s32 max_length )
{
	interface_manager_ = interface_manager;
	max_length_ = max_length;
	length_ = max_length;
}

//=============================================================================
// デストラクタ
//=============================================================================
CUserNumber2D::~CUserNumber2D(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
void CUserNumber2D::SetParameter(const VECTOR2& position , const s32& player_id )
{
	position_ = position;
	player_id_ = player_id;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CUserNumber2D::Init(void)
{
	// オブジェクトビルボードの生成
	rectangle_2d_ = new CRectangle2D(interface_manager_->graphic_manager()->device_holder());
	rectangle_2d_->set_size(VECTOR2((f32)max_length_,10.0f));
	rectangle_2d_->set_color( COLOR4F( 1.0f , 1.0f , 1.0f , 1.0f ) );
	rectangle_2d_->Set();

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_2d_manager()->AddList(rectangle_2d_);
	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CUserNumber2D::Update(void)
{
	rectangle_2d_->set_size( VECTOR2((f32)length_ , 10.0f ));
	rectangle_2d_->Set();
}

//=============================================================================
// 描画処理
//=============================================================================
void CUserNumber2D::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// 描画
	object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"snowball001");
}

//=============================================================================
// 終了処理
//=============================================================================
void CUserNumber2D::Uninit( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	//HACK
	object_2d_manager->Uninit();

}
//=============================================================================
// 消去処理
//=============================================================================
void CUserNumber2D::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
