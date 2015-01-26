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
#define TIKATIKA_CHANGE_POINT       (30)

#define TITLE_LOGO_POS_X_INIT       (650)
#define TITLE_LOGO_POS_Y_INIT       (100)
#define TITLE_LOGO_TEX_SIZE_X_INIT  (670)
#define TITLE_LOGO_TEX_SIZE_Y_INIT  (100)
#define TITLE_LOGO_SCL_X_INIT       (1)
#define TITLE_LOGO_SCL_Y_INIT       (1)
#define TITLE_LOGO_TEX_NAME         ("title")

#define TITLE_ENTER_POS_X_INIT      (650)
#define TITLE_ENTER_POS_Y_INIT      (600)
#define TITLE_ENTER_TEX_SIZE_X_INIT (609)
#define TITLE_ENTER_TEX_SIZE_Y_INIT (62)
#define TITLE_ENTER_SCL_X_INIT      (1)
#define TITLE_ENTER_SCL_Y_INIT      (1)
#define TITLE_ENTER_TEX_NAME        ("pleaseEnter")
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
	logo_object_key_ = -1;
	enter_object_key_ = -1;
	daruma_object_key_ = -1;
	field_object_key_ = -1;

	tikatika_=true;
	tikatika_counter=0;
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
		set_next_scene(new CGameFactory());
	}

	tikatika_counter++;
	if(tikatika_counter>=TIKATIKA_CHANGE_POINT)
	{
		tikatika_counter=0;
		tikatika_=!tikatika_;
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
	object_2d_manager->Draw(logo_object_key_,VECTOR2(TITLE_LOGO_POS_X_INIT,TITLE_LOGO_POS_Y_INIT),0,VECTOR2(TITLE_LOGO_SCL_X_INIT,TITLE_LOGO_SCL_Y_INIT),MATRIX4x4(),TITLE_LOGO_TEX_NAME);
	if(tikatika_)
	{
		object_2d_manager->Draw(logo_object_key_,VECTOR2(TITLE_ENTER_POS_X_INIT,TITLE_ENTER_POS_Y_INIT),0,VECTOR2(TITLE_ENTER_SCL_X_INIT,TITLE_ENTER_SCL_Y_INIT),MATRIX4x4(),TITLE_ENTER_TEX_NAME);
	}
}
//=============================================================================
// 終了
//=============================================================================
void CSceneTitle::Uninit(void)
{
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


	// タイトルフォルダのロード
	texture_manager->Load("resources/texture/title");

	//ロゴポリゴン生成
	CRectangle2D* Logo = new CRectangle2D(device_holder);
	Logo->set_size(VECTOR2(TITLE_LOGO_TEX_SIZE_X_INIT,TITLE_LOGO_TEX_SIZE_Y_INIT));
	Logo->Set();
	logo_object_key_ = object_2d_manager->AddList(Logo);

	//プリーズエンターポリゴン生成
	CRectangle2D* Enter = new CRectangle2D(device_holder);
	Enter->set_size(VECTOR2(TITLE_ENTER_TEX_SIZE_X_INIT,TITLE_ENTER_TEX_SIZE_Y_INIT));
	Enter->Set();
	enter_object_key_ = object_2d_manager->AddList(Enter);
}

//=============================================================================
// 自分のファクトリーの生成
//=============================================================================
CSceneFactory* CSceneTitle::MakeFactory(void)
{
	return new CTitleFactory();
}

//---------------------------------- EOF --------------------------------------
