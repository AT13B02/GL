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
#include "scene/result/scene_result.h"
#include "scene/factory/scene_factory.h"

// input
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"
#include "interface/input/input_alias.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"

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
CSceneResult::CSceneResult(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	test_object_key_ = -1;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneResult::~CSceneResult(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CSceneResult::Init(void)
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
void CSceneResult::Update(void)
{
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
	{
		set_next_scene(new CTitleFactory());
	}
}

//=============================================================================
// 描画
//=============================================================================
void CSceneResult::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"");
}

//=============================================================================
// 終了
//=============================================================================
void CSceneResult::Uninit(void)
{
}

//=============================================================================
// ロード
//=============================================================================
void CSceneResult::Load(void)
{
	CGraphicManager* graphic_manager	= interface_manager_->graphic_manager();
	CDeviceHolder* device_holder		= graphic_manager->device_holder();
	CTextureManager* texture_manager	= graphic_manager->texture_manager();
	CObjectManager* object_manager		= graphic_manager->object_manager();
	CObject3DManager* object_3d_manager	= object_manager->object_3d_manager();

	CRectangle3D* billboard = new CRectangle3D(device_holder);
	billboard->set_size(VECTOR2(200,200));
	billboard->Set();

	// タイトルフォルダのロード
	texture_manager->Load("resources/texture/title");

	// オブジェクトの生成
	test_object_key_ = object_3d_manager->AddList(billboard);
}

//=============================================================================
// 自分のファクトリーの生成
//=============================================================================
CSceneFactory* CSceneResult::MakeFactory(void)
{
	return new CResultFactory();
}

//---------------------------------- EOF --------------------------------------
