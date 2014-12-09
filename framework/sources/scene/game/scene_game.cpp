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
#include "interface/character/camera/character_camera.h"
#include "interface/character/camera/character_camera_manager.h"
#include "interface/character/bullet/bullet_manager.h"
#include "interface/character/bullet/bullet.h"

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
	// キャラクターの初期化

	// マップの初期化

	// カメラの初期化

	// ネットワークの初期化

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CSceneGame::Update(void)
{
	// ネットワーク受信データの確認

	// 受信データを元に更新(生成や座標の調整)

	// 当たり判定

	// サーバーにデータ送信
}

//=============================================================================
// 描画
//=============================================================================
void CSceneGame::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// TODO 描画テスト
	object_3d_manager->Draw(test_meshfield_key_,VECTOR3(0.0f,0.0f,0.0f),VECTOR3(0.0f,0.0f,0.0f),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000");
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneGame::Uninit(void)
{
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
	CCharacterCameraManager* character_camera_manager = character_manager->character_camera_manager();
	CBulletManager* bullet_manager = character_manager->bullet_manager();
	// ゲームのテクスチャのロード
	texture_manager->Load("resources/texture/game");

	// ゲームのモデルのロード
	model_manager->Load("resources/model/game");

	// ライトの設定
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(1.0f,0.0f,0.0f).Normalize());
	light_manager->Add(light);

	// プレイヤーの生成
	CPlayer* player = new CPlayer(interface_manager_);
	player->Init();
	player_manager->Push(player);

	// バレットの生成
	CBullet* bullet = new CBullet( interface_manager_ );
	bullet->CreateBullet( VECTOR3(0,0,0) , VECTOR3(0,0,0) );
	bullet_manager->Push(bullet);

	// カメラの生成
	CCharacterCamera* camera = new CCharacterCamera(interface_manager_);
	camera->Init();
	character_camera_manager->Push(camera);





	// TODO 以下テストプログラム

	// メッシュフィールド
	CMeshfield* mesh_field = new CMeshfield(device_holder);
	mesh_field->Init();
	mesh_field->set_grid_number(10,10);
	mesh_field->set_grid_length(100.0f,100.0f);
	mesh_field->Set();
	test_meshfield_key_ = object_3d_manager->AddList(mesh_field);
}

//---------------------------------- EOF --------------------------------------
