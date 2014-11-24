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
	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CSceneGame::Update(void)
{
	//test_camera_->SetEye();
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
	CCameraManager* camera_manager = object_manager->camera_manager();

	CBillboard* billboard = new CBillboard(device_holder);

	billboard->set_size(VECTOR2(10,10));

	billboard->Set();

	// タイトルフォルダのロード
	texture_manager->Load("resources/texture/game");

	// オブジェクトの生成
	test_object_key_ = object_3d_manager->AddList(billboard);

	// カメラの取得
	test_camera_ = camera_manager->GetCamera(camera_manager->CreateCamera());

}

//---------------------------------- EOF --------------------------------------
