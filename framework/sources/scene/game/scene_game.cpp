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
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();



	// TODO 描画テスト
	object_3d_manager->Draw(test_rectangle_3d_key_,VECTOR3(0.0f,0.0f,0.0f),VECTOR3(-90.0f,0.0f,0.0f),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000",NULL);
	object_3d_manager->Draw(test_billboard_key_,VECTOR3(0.0f,0.0f,0.0f),VECTOR3(0.0f,0.0f,0.0f),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000",NULL);
	object_3d_manager->Draw(test_model_key_,VECTOR3(),VECTOR3(0.0f,0.0f,0.0f),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"",NULL);
	object_2d_manager->Draw(test_rectangle_2d_key_,VECTOR2(),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"field000",NULL);
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
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	CCameraManager* camera_manager = object_manager->camera_manager();
	CModelManager* model_manager = graphic_manager->model_manager();
	CLightManager* light_manager = graphic_manager->light_manager();

	// ゲームのテクスチャのロード
	texture_manager->Load("resources/texture/game");

	// ゲームのモデルのロード
	model_manager->Load("resources/model/game");

	// ライトの設定
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetPosition(VECTOR3(1.0f,0.5f,1.0f).Normalize());
	light_manager->Add(light);






	// TODO 以下テストプログラム

	// カメラ
	test_camera_ = new CCharacterCamera(interface_manager_);
	test_camera_->Init();

	// ビルボード
	CBillboard* billboard = new CBillboard(device_holder);
	billboard->set_size(VECTOR2(10.0f,10.0f));
	billboard->Set();
	test_billboard_key_ = object_3d_manager->AddList(billboard);

	// モデル
	CObjectModel* object_model = new CObjectModel(device_holder,"ship");
	test_model_key_ = object_3d_manager->AddList(object_model);

	// 矩形3D
	CRectangle3D* rectangle_3d = new CRectangle3D(device_holder);
	rectangle_3d->set_size(VECTOR2(10.0f,10.0f));
	rectangle_3d->set_point(CRectangle3D::POINT_CENTER);
	rectangle_3d->Set();
	test_rectangle_3d_key_ = object_3d_manager->AddList(rectangle_3d);

	// 矩形2D
	CRectangle2D* rectangle_2d = new CRectangle2D(device_holder);
	rectangle_2d->set_size(VECTOR2(100.0f,100.0f));
	rectangle_2d->set_point(CRectangle2D::POINT_LEFT_UP);
	rectangle_2d->Set();
	test_rectangle_2d_key_ = object_2d_manager->AddList(rectangle_2d);
}

//---------------------------------- EOF --------------------------------------
