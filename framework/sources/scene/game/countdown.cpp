//*****************************************************************************
//
// カウントダウンクラス
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "countdown.h"

// scene
#include "scene/game/scene_game.h"
#include "scene/factory/scene_factory.h"

// interface
#include "interface/interface_manager.h"

// input
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"
#include "interface/input/input_alias.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/light/light_manager.h"
#include "interface/graphic/light/light.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/object/object_3d/element/meshfield.h"

// character
#include "interface/character/character_manager.h"
#include "interface/character/player/player_manager.h"
#include "interface/character/player/player.h"
#include "interface/character/field/field.h"
#include "interface/character/field/field_manager.h"
#include "interface/character/camera/player_camera.h"
#include "interface/character/camera/character_camera_manager.h"
#include "interface/character/attitude_controller/attitude_controller.h"
#include "interface/character/attitude_controller/attitude_controller_manager.h"
#include "interface/character/bullet/bullet_manager.h"
#include "interface/character/player/network_player.h"

//network
#include "interface/network/network_manager.h"
#include "interface/network/network_client.h"

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const f32 CCountDown::ADD_SCALSE = 1/60.0f;
const f32 CCountDown::ADD_TEXTURE_UV = 1/4.0f;
const f32 CCountDown::WIDTH = 200.0f;
const f32 CCountDown::HEIGHT = 300.0f;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCountDown::CCountDown(CInterfaceManager* interface_manager)
{
	//インターフェースポインタ保存
	interface_manager_ = interface_manager;

	//各値初期化
	countdown_polygon = NULL;
	scl_ = 0.0f;
	alpha_ = 1.0f;
	right_ = ADD_TEXTURE_UV;
	left_ = 0.0f;
	top_ = 0.0f;
	bottom_ = 1.0f;

	countdown_comp_ = false;

	//カウントダウン用のポリゴン作成
	countdown_polygon = new CRectangle2D(interface_manager->graphic_manager()->device_holder());
	countdown_polygon->set_size(VECTOR2((f32)WIDTH,(f32)HEIGHT));
	countdown_polygon->set_point(CRectangle2D::POINT_CENTER);
	countdown_polygon->set_texcoord( left_, right_, top_, bottom_ );
	countdown_polygon->Set();

	interface_manager_ = interface_manager;
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	countdown_polygon_key_ = object_2d_manager->AddList(countdown_polygon);

}

//=============================================================================
// デストラクタ
//=============================================================================
CCountDown::~CCountDown(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CCountDown::Init(void)
{

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CCountDown::Update(void)
{
	//スケール値更新
	scl_ += ADD_SCALSE;

	//１になったら次へ
	if( scl_ > 1.0f )
	{
		//Ｕ値更新
		left_ = right_;
		right_ += ADD_TEXTURE_UV;

		//Ｕ値が1.0以上になったらカウント終了
		if( right_ > 1.0f )
		{
			countdown_comp_ = true;
		}

		//テクスチャセット
		countdown_polygon->set_texcoord( left_, right_, top_, bottom_ );
		countdown_polygon->Set();


		scl_ = 0.0f;

	}
}

//=============================================================================
// 描画
//=============================================================================
void CCountDown::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	object_2d_manager->Draw(countdown_polygon_key_,VECTOR2(DEFAULT_SCREEN_WIDTH / 2,DEFAULT_SCREEN_HEIGHT / 2),0.0f,VECTOR2(scl_,scl_),
								MATRIX4x4(),"countdown");
}

//=============================================================================
// 終了処理
//=============================================================================
void CCountDown::Uninit(void)
{

}



//---------------------------------- EOF --------------------------------------
