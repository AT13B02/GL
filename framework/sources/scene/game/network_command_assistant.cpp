//*****************************************************************************
//
// �l�b�g�Q�[���A�V�X�^���g�N���X
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
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

//network
#include "interface/network/network_manager.h"
#include "interface/network/network_client.h"

#include "../../interface/character/field/field.h"

// common
#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNetworkCommandAssistant::CNetworkCommandAssistant(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNetworkCommandAssistant::~CNetworkCommandAssistant(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CNetworkCommandAssistant::Init(void)
{

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CNetworkCommandAssistant::Update(void)
{
	//�l�b�g���[�N�o�b�t�@�̎擾
	CHARCTER_INFO *net_chara_buf = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetCharcterInfoBuffer();
	
	CCharacterManager *character_manager = interface_manager_->character_manager();
	
	//�l�b�g�̃v���C���[�ɃA�b�v�f�[�g���ā[
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
				//����
				CNetWorkPlayer* player = new CNetWorkPlayer(interface_manager_);
				player->Init();
			
				//�|�C���^�ۑ�
				character_manager->SetNetworkPlayer( player, net_chara_buf->player_id );
				player->SetCharID(net_chara_buf->player_id);
				SetInitPosPlayer(player, net_chara_buf->player_id);
			}

			else
			{
				//�X�V
				character_manager->network_player( net_chara_buf->player_id )->set_position( net_chara_buf->position );
				character_manager->network_player( net_chara_buf->player_id )->set_rotation( net_chara_buf->rotation );
				character_manager->network_player( net_chara_buf->player_id )->set_hp( net_chara_buf->hp );
				character_manager->network_player( net_chara_buf->player_id )->Update();
			}
			// ������ӂ�HP�\���ς�����
			//
			//

			net_chara_buf->end_push_flag = false;
		}
	}

	//�e�o�b�t�@�̎擾
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
// �`��
//=============================================================================
void CNetworkCommandAssistant::Draw(void)
{
	CCharacterManager *character_manager = interface_manager_->character_manager();
	
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		// ���S�t���O�����Ă���`�悵�Ȃ�
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
// �I������
//=============================================================================
void CNetworkCommandAssistant::Uninit(void)
{

}

// �f�X
void CNetworkCommandAssistant::Death(int id)
{
	CCharacterManager *character_manager = interface_manager_->character_manager();
	character_manager->network_player( id )->Uninit();
}


void CNetworkCommandAssistant::SetInitPosPlayer(CNetWorkPlayer* pPlayer, int id)
{
	std::list<CField*> field_list = interface_manager_->character_manager()->field_manager()->character_list();
	auto field_it = field_list.begin();

	if(field_it == field_list.end())
	{
		interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetBufPos(VECTOR3(0,0,0), id);
	}

	switch(id)
	{
		case 0:
			pPlayer->set_position(VECTOR3((*field_it)->get_min_x(),0,(*field_it)->get_min_z()));
			interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetBufPos(VECTOR3((*field_it)->get_min_x(),0,(*field_it)->get_min_z()), id);
			
		break;

		case 1:
			pPlayer->set_position(VECTOR3((*field_it)->get_min_x(),0,(*field_it)->get_max_z()));
			interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetBufPos(VECTOR3((*field_it)->get_min_x(),0,(*field_it)->get_max_z()), id);

		break;

		case 2:
			pPlayer->set_position(VECTOR3((*field_it)->get_max_x(),0,(*field_it)->get_min_z()));
			interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetBufPos(VECTOR3((*field_it)->get_max_x(),0,(*field_it)->get_min_z()), id);

		break;

		case 3:
			pPlayer->set_position(VECTOR3((*field_it)->get_max_x(),0,(*field_it)->get_max_z()));
			interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetBufPos(VECTOR3((*field_it)->get_max_x(),0,(*field_it)->get_max_z()), id);

		break;

		default:
			pPlayer->set_position(VECTOR3(0,0,0));
			interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetBufPos(VECTOR3(0,0,0), id);

			break;
	}
}
//---------------------------------- EOF --------------------------------------
