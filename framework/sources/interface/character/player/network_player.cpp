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

#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

CNetWorkPlayer::CNetWorkPlayer(CInterfaceManager* interface_manager)
	:CPlayer(interface_manager)
{
	interface_manager->network_manager()->GetNetworkClient()->GetWinSock()->RequestID();
}

CNetWorkPlayer::~CNetWorkPlayer(void)
{

}

void CNetWorkPlayer::Update(void)
{
	int animationNo =0;
	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDataCharcter(&pos_,&rot_,animationNo);


	CPlayer::Update();
}

void CNetWorkPlayer::Uninit(void)
{
	CPlayer::Uninit();
}

void CNetWorkPlayer::Draw(void)
{
#if 1
	CHARCTER_INFO *charcterInfo =nullptr;
	object_key_;

	charcterInfo = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetCharcterInfoBuffer();

	for(int i =0; i <4; i++)
	{
		//myself
		if(charcterInfo[i].player_id == interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetID())
		{
			//interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDataCharcter(&pos_,&rot_,animationNo,interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetID());

			CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
			CObjectManager* object_manager = graphic_manager->object_manager();
			CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

			// 描画
			object_3d_manager->Draw(object_key_,charcterInfo[i].position,charcterInfo[i].rotation,scale_,MATRIX4x4(),"");
			
			break;
		}
	}
#endif

	//CPlayer::Draw();


}