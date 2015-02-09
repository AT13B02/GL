//*****************************************************************************
//
// �Q�[���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// scene
#include "scene/game/scene_game.h"
#include "scene/factory/scene_factory.h"

// interface
#include "interface/interface_manager.h"

//game
#include "network_command_assistant.h"

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
#include "interface/graphic/object/object_3d/element/meshdome.h"

// character
#include "interface/character/character_manager.h"
#include "interface/character/player/player_manager.h"
#include "interface/character/player/network_player.h"
#include "interface/character/player/player.h"
#include "interface/character/field/field.h"
#include "interface/character/field/field_manager.h"
#include "interface/character/camera/player_camera.h"
#include "interface/character/camera/character_camera_manager.h"
#include "interface/character/attitude_controller/attitude_controller.h"
#include "interface/character/attitude_controller/attitude_controller_manager.h"
#include "scene/game/countdown.h"

//network
#include "interface/interface_manager.h"
#include "interface/network/network_manager.h"
#include "interface/network/network_client.h"
#include "interface/network/network_data_buffer.h"
#include "interface/network/windows_sockets.h"


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
CSceneGame::CSceneGame(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_GAME)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneGame::~CSceneGame(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CSceneGame::Init(void)
{
	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CSceneGame::Update(void)
{
	//�J�E���g�_�E�����I����Ă�����
	if( countdown_->countdown_comp() )
	{
		//�v���C���[���X�V�t���O�����Ă��Ȃ�������X�V
		player_->set_update(true);
	}
	//�I����ĂȂ�������J�E���g�_�E���X�V
	else
	{
		countdown_ -> Update();
	}
	
	network_command_assistant_ -> Update();
}

//=============================================================================
// �`��
//=============================================================================
void CSceneGame::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	if( !( countdown_->countdown_comp()) )
	{
		countdown_ -> Draw();
	}

	network_command_assistant_ -> Draw();
	object_3d_manager->Draw(test_meshdome_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),"sky000");

}

//=============================================================================
// �I������
//=============================================================================
void CSceneGame::Uninit(void)
{
	SAFE_RELEASE( network_command_assistant_ );
	SAFE_RELEASE( countdown_ );
}

//=============================================================================
// �����̃t�@�N�g���[�̐���
//=============================================================================
CSceneFactory* CSceneGame::MakeFactory(void)
{
	// �Q�[���t�@�N�g���[�̐���
	return new CGameFactory();
}

//=============================================================================
// ���[�h����
//=============================================================================
void CSceneGame::Load(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CDeviceHolder* device_holder = graphic_manager->device_holder();
	CTextureManager* texture_manager = graphic_manager->texture_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	CCameraManager* camera_manager = object_manager->camera_manager();
	CModelManager* model_manager = graphic_manager->model_manager();
	CLightManager* light_manager = graphic_manager->light_manager();
	CCharacterManager* character_manager = interface_manager_->character_manager();
	CPlayerManager* player_manager = character_manager->player_manager();
	CFieldManager* field_manager = character_manager->field_manager();
	CCharacterCameraManager* character_camera_manager = character_manager->character_camera_manager();
	CAttitudeControllerManager* attitude_controller_manager = character_manager->attitude_controller_manager();

	// �Q�[���̃e�N�X�`���̃��[�h
	texture_manager->Load("resources/texture/game");

	// �Q�[���̃��f���̃��[�h
	model_manager->Load("resources/model/game");

	// ���C�g�̐ݒ�
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(1.0f,0.0f,0.0f).Normalize());
	light_manager->Add(light);

	// ���C�g�̐ݒ�
	light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(0.0f,-1.0f,0.0f).Normalize());
	light_manager->Add(light);

	//�l�b�g���[�N�R�}���_�[�̍쐬
	network_command_assistant_ = new CNetworkCommandAssistant( interface_manager_ );
	network_command_assistant_ -> Init();

	//�J�E���g�_�E���̍쐬
	countdown_ = new CCountDown( interface_manager_ );
	countdown_ -> Init();

	// �v���C���[�̐���
	player_ = new CPlayer(interface_manager_);
	//CPlayer* player = new CNetWorkPlayer(interface_manager_);
	player_->Init();
	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->RequestID();
	player_manager->set_player( player_ );
	player_manager->Push(player_);

/*
	CPlayer* player2 = new CNetWorkPlayer(interface_manager_);
	player2->Init();
	player_manager->Push(player2);
*/
	// �J�����̐���
	CPlayerCamera* camera = new CPlayerCamera(interface_manager_,player_);
	camera->Init();
	character_camera_manager->Push(camera);

	// �p������̐���
	CAttitudeController* attitude_controller = new CAttitudeController(interface_manager_);
	attitude_controller->set_axis(VECTOR3(0.0f,1.0f,0.0f));
	attitude_controller->Push(player_);
	attitude_controller->Push(camera);
	attitude_controller_manager->Push(attitude_controller);

	// �t�B�[���h�̐���
	CField* field = new CField(interface_manager_);
	field->Init();
	field_manager->Push(field);

	CMeshdome* meshdome = new CMeshdome(device_holder);
	meshdome->set_radius(3000.0f);
	meshdome->SetGridNumber(10,10);
	meshdome->Set();
	test_meshdome_key_ = object_3d_manager->AddList(meshdome);
}

//---------------------------------- EOF --------------------------------------
