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
#include "interface/character/player/network_player.h"

#include "interface/character/player_status/life_2d/life_2d_manager.h"
#include "interface/character/player_status/life_2d/life_2d.h"
#include "interface/character/player_status/user_number_2d/icon_2d_manager.h"
#include "interface/character/player_status/user_number_2d/icon_2d.h"

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
	
	CCharacterManager *character_manager = interface_manager_->character_manager();
	
	//ネットのプレイヤーにアップデートしてー
	for( int i = 0; i < kMaxPlayer; i++, net_chara_buf++)
	{
		if(net_chara_buf->player_id < 0)
		{
			continue;
		}
		if( net_chara_buf->end_push_flag == true )
		{
			if( character_manager->network_player( net_chara_buf->player_id ) == NULL )
			{
				//つくる
				CNetWorkPlayer* player = new CNetWorkPlayer(interface_manager_);
				player->Init();
			
				//ポインタ保存
				character_manager->SetNetworkPlayer( player, net_chara_buf->player_id );

				//UI設定
				// icon
				character_manager->icon_2d_manager()->Push( 
					character_manager->icon_2d_manager()->Create( 
					interface_manager_ , net_chara_buf->player_id , 5.0f ) );
				// life
				CLife2D* life = character_manager->life_2d_manager()->Create( 
					interface_manager_ , 100 , 100 , net_chara_buf->player_id );
				player->set_life_2d( life );
				character_manager->life_2d_manager()->Push( player->get_life_2d() );

			}

			//更新
			character_manager->network_player( net_chara_buf->player_id )->set_position( net_chara_buf->position );
			character_manager->network_player( net_chara_buf->player_id )->set_rotation( net_chara_buf->rotation );
			character_manager->network_player( net_chara_buf->player_id )->set_hp( net_chara_buf->hp );
			character_manager->network_player( net_chara_buf->player_id )->Update();

			// ここら辺でHP表示変えたい
			//
			//

			net_chara_buf->end_push_flag = false;
		}
	}

	//弾バッファの取得
	BULLET_INFO *net_bullet_buf = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetBulletInfoBuffer();
	
	for(int i = 0; i < kMaxPlayer; i++,net_bullet_buf++)
	{
		if(net_bullet_buf->player_id < 0)
		{
			continue;
		}
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
// 描画
//=============================================================================
void CNetworkCommandAssistant::Draw(void)
{
	CCharacterManager *character_manager = interface_manager_->character_manager();
	
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		// 死亡フラグ立ってたら描画しない
		if(interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetCharDeathFlag(i))
		{
			continue;
		}

		if( character_manager->network_player( i ) != NULL )
		{
			character_manager->network_player( i ) ->Draw();
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CNetworkCommandAssistant::Uninit(void)
{

}

// デス
void CNetworkCommandAssistant::Death(int id)
{
	CCharacterManager *character_manager = interface_manager_->character_manager();
	character_manager->network_player( id )->Uninit();
}

//---------------------------------- EOF --------------------------------------
