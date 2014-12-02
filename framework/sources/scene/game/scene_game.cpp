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
#include "scene/title/scene_title.h"
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
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"

// character
#include "interface/character/camera/character_camera.h"

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

	// キャラクターの更新

	// サーバーにデータ送信

	// TODO テスト
	test_camera_->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CSceneGame::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000",NULL);
	object_3d_manager->Draw(test_object_key_2_,VECTOR3(),VECTOR3(90.0f,0.0f,0.0f),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000",NULL);
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneGame::Uninit(void)
{
	SAFE_RELEASE(test_camera_);
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
	CCameraManager* camera_manager = object_manager->camera_manager();
	CModelManager* model_manager = graphic_manager->model_manager();

	// プレイヤーの生成

	// マップの生成

	// カメラの生成

	// ライトの生成

	// TODO 以下テストプログラム
	test_camera_ = new CCharacterCamera(interface_manager_);

	test_camera_->Init();

	//CRectangle3D* billboard = new CRectangle3D(device_holder);

	//billboard->set_size(VECTOR2(10,10));

	//billboard->Set();

	// ゲームのテクスチャのロード
	texture_manager->Load("resources/texture/game");

	// オブジェクトの生成
	//test_object_key_ = object_3d_manager->AddList(billboard);

	// ゲームのモデルのロード
	model_manager->Load("resources/model/game");

	// オブジェクトモデルの生成
	CObjectModel* object_model = new CObjectModel(device_holder,"ship");

	// オブジェクトリストに追加
	test_object_key_ = object_3d_manager->AddList(object_model);

	CRectangle3D* rectangle = new CRectangle3D(device_holder);

	rectangle->set_size(VECTOR2(1000.0f,1000.0f));

	rectangle->set_point(CRectangle3D::POINT_CENTER);

	rectangle->Set();

	test_object_key_2_ = object_3d_manager->AddList(rectangle);
}

//---------------------------------- EOF --------------------------------------
