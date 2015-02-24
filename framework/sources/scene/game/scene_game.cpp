//*****************************************************************************
//
// ゲームクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// scene
#include "scene/game/scene_game.h"
#include "scene/result/scene_result.h"
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
#include "interface/graphic/object/object_3d/element/meshfield.h"
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
#include "interface/character/box/box.h"
#include "interface/character/box/box_manager.h"

//network
#include "interface/interface_manager.h"
#include "interface/network/network_manager.h"
#include "interface/network/network_client.h"
#include "interface/network/network_data_buffer.h"
#include "interface/network/windows_sockets.h"


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
CSceneGame::CSceneGame(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_GAME)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneGame::~CSceneGame(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CSceneGame::Init(void)
{
	interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->InitFlag();
	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CSceneGame::Update(void)
{
	//TODO
	CCharacterManager* character_manager = interface_manager_->character_manager();
	CPlayerManager* player_manager = character_manager->player_manager();
	std::list<CPlayer*> player_list = player_manager->character_list();

	network_command_assistant_ -> Update();

	// ゲーム終了なら
	if(interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetGameSceneEndFlag())
	{
		for(auto player_it = player_list.begin(); player_it != player_list.end(); ++player_it)
		{
			if((*player_it)->death_flag())
			{
				CSceneResult::SetResultFlag(false);
			}
			else
			{
				CSceneResult::SetResultFlag(true);
			}
		}
		set_next_scene(new CResultFactory());
		interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetGameSceneEndFlag(false);
	}
}

//=============================================================================
// 描画
//=============================================================================
void CSceneGame::Draw(void)
{
	network_command_assistant_ -> Draw();
	
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	object_3d_manager->Draw(
		meshsky_key_,
		VECTOR3(0,0,0), VECTOR3(0,0,0), VECTOR3(1,1,1),
		MATRIX4x4(), "sky003");
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneGame::Uninit(void)
{
	CCharacterManager* character_manager = interface_manager_->character_manager();
	character_manager->Clear();
	SAFE_RELEASE( network_command_assistant_ );

	CPlayerManager* player_manager = character_manager->player_manager();
	std::list<CPlayer*> player_list = player_manager->character_list();
	for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
	{
		(*player_it)->SetDeathFlag(false);
	}

	interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->SetGameSceneEndFlag(false);
}

//=============================================================================
// 自分のファクトリーの生成
//=============================================================================
CSceneFactory* CSceneGame::MakeFactory(void)
{
	// ゲームファクトリーの生成
	return new CGameFactory();
}

//=============================================================================
// ロード処理
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
	CBoxManager* box_manager = character_manager->box_manager();

	// ゲームのテクスチャのロード
	texture_manager->Load("resources/texture/game");

	// ゲームのモデルのロード
	model_manager->Load("resources/model/game");

	VECTOR3 lightVec( 0.0f , 0.0f , 0.0f );

	// ライトの設定
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	lightVec = VECTOR3( -1.0f , -1.0f , -1.0f ).Normalize();
	light->SetDirection(lightVec);
	light_manager->Add(light);

	// ライトの設定
	light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	lightVec = VECTOR3( 1.0f , 0.0f , 1.0f ).Normalize();
	light->SetDirection(lightVec);
	light_manager->Add(light);

	// ライトの設定
	light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	lightVec = VECTOR3( 0.0f , 1.0f , -5.0f ).Normalize();
	light->SetDirection(lightVec);
	light_manager->Add(light);


	//ネットワークコマンダーの作成
	network_command_assistant_ = new CNetworkCommandAssistant( interface_manager_ );
	network_command_assistant_ -> Init();

	// プレイヤーの生成
	CPlayer* player = new CPlayer(interface_manager_);
	//CPlayer* player = new CNetWorkPlayer(interface_manager_);
	player->Init();
	player_manager->set_player( player );
	player_manager->Push(player);

/*
	CPlayer* player2 = new CNetWorkPlayer(interface_manager_);
	player2->Init();
	player_manager->Push(player2);
*/
	// カメラの生成
	CPlayerCamera* camera = new CPlayerCamera(interface_manager_,player);
	camera->Init();
	character_camera_manager->Push(camera);

	// 姿勢制御の生成
	CAttitudeController* attitude_controller = new CAttitudeController(interface_manager_);
	attitude_controller->set_axis(VECTOR3(0.0f,1.0f,0.0f));
	attitude_controller->Push(player);
	attitude_controller->Push(camera);
	attitude_controller_manager->Push(attitude_controller);

	// スカイドーム
	CMeshdome* pMeshdome = new CMeshdome(device_holder);
	pMeshdome->Init();
	pMeshdome->SetGridNumber(10, 10);
	pMeshdome->set_radius(1000);
	pMeshdome->Set();
	meshsky_key_ = object_3d_manager->AddList(pMeshdome);

	// フィールドの生成
	CField* field = new CField(interface_manager_);
	field->Init();
	field_manager->Push(field);

	// フィールドに障害物追加
	CBox* box = new CBox(interface_manager_);
	box->Init();

	// TODO : フィールドから高さを取得する
	VECTOR3 boxPos(100.0f, 0.0f, 100.0f);
	box->position(boxPos._x, field->GetHeight(boxPos, nullptr), boxPos._z);
	box_manager->Push(box);

	CBox* box2 = new CBox(interface_manager_);
	box2->Init();

	VECTOR3 boxPos2(200.0f, 0.0f, 200.0f);
	box2->position(boxPos2._x, field->GetHeight(boxPos2, nullptr), boxPos2._z);
	box_manager->Push(box2);

}

//---------------------------------- EOF --------------------------------------
