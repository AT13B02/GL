//*****************************************************************************
//
// タイトルクラス
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
#include "interface/character/character_manager.h"

// input
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"
#include "interface/input/input_alias.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TITLE_LOGO_POS_X_INIT      (500)
#define TITLE_LOGO_POS_Y_INIT      (500)
#define TITLE_LOGO_TEX_SIZE_X_INIT (670)
#define TITLE_LOGO_TEX_SIZE_Y_INIT (100)
#define TITLE_LOGO_TEX_NAME        ("title")
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneTitle::CSceneTitle(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	test_object_key_ = -1;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneTitle::~CSceneTitle(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CSceneTitle::Init(void)
{
	if(!CScene::Init())
	{
		return false;
	}

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CSceneTitle::Update(void)
{
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
	{
		set_next_scene(new CResultFactory());
	}
}

//=============================================================================
// 描画
//=============================================================================
void CSceneTitle::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// 描画
	object_2d_manager->Draw(test_object_key_,VECTOR2(500,500),0,VECTOR2(1.0f,1.0f),MATRIX4x4(),"title");
}

//=============================================================================
// 終了
//=============================================================================
void CSceneTitle::Uninit(void)
{
	CCharacterManager* character_manager = interface_manager_->character_manager();
	character_manager->Clear();
}

//=============================================================================
// ロード
//=============================================================================
void CSceneTitle::Load(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CDeviceHolder* device_holder = graphic_manager->device_holder();
	CTextureManager* texture_manager = graphic_manager->texture_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	CRectangle2D* Porigon = new CRectangle2D(device_holder);

	Porigon->set_size(VECTOR2(670,100));

	Porigon->Set();

	// タイトルフォルダのロード
	texture_manager->Load("resources/texture/title");

	// オブジェクトの生成
	test_object_key_ = object_2d_manager->AddList(Porigon);
}

//=============================================================================
// 自分のファクトリーの生成
//=============================================================================
CSceneFactory* CSceneTitle::MakeFactory(void)
{
	return new CResultFactory();
}

//---------------------------------- EOF --------------------------------------
