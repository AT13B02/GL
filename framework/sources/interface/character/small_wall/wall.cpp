//*****************************************************************************
//
// 壁クラス
// Author		: ooigawa kazuma
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "wall.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"

#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/input/input_manager.h"

#include "../character_manager.h"

#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CWall::CWall( CInterfaceManager* interface_manager , WALL_KIND wall_kind)
{
	//インターフェースマネージャーの保存
	interface_manager_ = interface_manager;
	wall_kind_ = wall_kind;
	CObjectModel* object_model ;
	switch( wall_kind_ )
	{
	case WALL_KIND_BIG:
		// オブジェクトモデルの生成
		object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"big_wall");
		break;
	case WALL_KIND_SMALL:
		// オブジェクトモデルの生成
		object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"small_wall");
		break;
	}
	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);

}
//=============================================================================
// デストラクタ
//=============================================================================
CWall::~CWall( void )
{
}
//=============================================================================
// 初期化
//=============================================================================
bool CWall::Init( void )
{
	//変数初期化
	position_	= VECTOR3( 0.0f , 0.0f , 0.0f );
	rotation_	= VECTOR3( 0.0f , 0.0f , 0.0f );
	scale_		= VECTOR3( 1.0f , 1.0f , 1.0f );

	return true;
}
//=============================================================================
// 更新
//=============================================================================
void CWall::Update( void )
{
}
//=============================================================================
// 描画処理
//=============================================================================
void CWall::Draw( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	switch( wall_kind_ )
	{
	case WALL_KIND_BIG:
		// 描画
		object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"big_wall");
		break;
	case WALL_KIND_SMALL:
		// 描画
		object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"small_wall");
		break;
	}

}