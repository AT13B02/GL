//*****************************************************************************
//
// ネットゲームアシスタントクラス
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// scene
#include "scene/game/network_command_assistant.h"
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

//network
#include "interface/network/network_manager.h"
#include "interface/network/network_client.h"

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
CNetworkCommandAssistant::CNetworkCommandAssistant(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNetworkCommandAssistant::~CNetworkCommandAssistant(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CNetworkCommandAssistant::Init(void)
{
	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CNetworkCommandAssistant::Update(void)
{
	//ネットワークバッファの取得
	CHARCTER_INFO *net_chara_buf = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetCharcterInfoBuffer();

	
	//ネットのプレイヤーにアップデートしてー
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		if( net_chara_flag_buf[ i ] == false )
		{
			//つくる
		}
		
		//そいつをアップデート
	}

	//弾バッファの取得
	BULLET_INFO *net_bullet_buf = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetBulletInfoBuffer();
	
	for(int i = 0; i < kMaxPlayer; i++)
	{
		if( net_bullet_buf->end_push_flag == true )
		{
			CBullet* bullet = new CBullet(interface_manager_);

			bullet->Init();
			bullet->SetParameter(net_bullet_buf->position,
								net_bullet_buf->front_vector, 
								net_bullet_buf->speed,
								net_bullet_buf->player_id);
			
			interface_manager_->character_manager()->bullet_manager()->Push(bullet);

			net_bullet_buf->end_push_flag = false;
		}
	}
}


//=============================================================================
// 終了処理
//=============================================================================
void CNetworkCommandAssistant::Uninit(void)
{
}



//---------------------------------- EOF --------------------------------------
