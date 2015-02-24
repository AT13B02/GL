//*****************************************************************************
//
// プレイヤークラス
//
// Author		: Tomohiro Kouno
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "network_player.h"
#include "interface/interface_manager.h"
#include "../../network/network_manager.h"
#include "../../network/network_client.h"
#include "../../network/network_data_buffer.h"
#include "../../network/windows_sockets.h"

#include "interface/character/character_manager.h"
#include "../player_status/life_2d/life_2d.h"

#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

CNetWorkPlayer::CNetWorkPlayer(CInterfaceManager* interface_manager)
	:CPlayer(interface_manager)
{
	// オブジェクトモデルの生成
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);
}

CNetWorkPlayer::~CNetWorkPlayer(void)
{

}

void CNetWorkPlayer::Update(void)
{
	int animationNo =0;
	if( life_2d_ != NULL )
	{
		life_2d_->set_life( hp_ );
	}

//	CPlayer::Update();
}

void CNetWorkPlayer::Uninit(void)
{
	//CPlayer::Uninit();
}

void CNetWorkPlayer::Draw(void)
{
#if 1
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"");

#endif

	//CPlayer::Draw();


}