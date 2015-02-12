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
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/character/camera/character_camera_manager.h"
#include "interface/graphic/light/light_manager.h"
#include "interface/graphic/light/light.h"
//#include "interface/character/camera/player_camera.h"
#include "interface/character/field/field.h"
#include "interface/character/field/field_manager.h"
#include "interface/character/character_manager.h"
#include "interface/character/camera/result_camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
// scene
#include "scene/game/scene_game.h"
#include "scene/factory/scene_factory.h"
#include "interface/graphic/model/model_manager.h"
// interface
#include "interface/interface_manager.h"

// common
#include "common/common.h"

const VECTOR2 CSceneResult::LOGO_DEFAULT_POS(600.0f,60.0f);
const VECTOR2 CSceneResult::PRESSKEY_DEFAULT_POS(600.0f,600.0f);

bool CSceneResult::m_bResult = true;
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
const char* CSceneResult::p_texture_names[TEXTURE_TYPE_MAX] = 
{
	"WinLogo02",	//Win
	"LoseLogo2",	//Lose
	"pleaseEnter2",	//PressEnter
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneResult::CSceneResult(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	test_object_key_ = -1;
	model_key_ = -1;
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
		set_next_scene(new CMatchFactory());
	}
}

//=============================================================================
// 描画
//=============================================================================
void CSceneResult::Draw(void)
{
	CGraphicManager* graphic_manager	= interface_manager_->graphic_manager();
	CObjectManager* object_manager		= graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	
	//object_2d_manager->Draw(logo_key_,LOGO_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_LOGO]);

	if(m_bResult)
	{
		object_2d_manager->Draw(logo_key_,LOGO_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_WIN]);
	}
	else
	{	
		object_2d_manager->Draw(logo_key_,LOGO_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_LOSE]);
	}
	//object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"");
	//object_2d_manager->Draw(press_key_,PRESSKEY_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_LOGO]);
	object_2d_manager->Draw(press_key_,PRESSKEY_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_PRESSENTER]);
	object_3d_manager->Draw(model_key_,VECTOR3(0,40,60),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"");
}

//=============================================================================
// 終了
//=============================================================================
void CSceneResult::Uninit(void)
{
	CCharacterManager* character_manager = interface_manager_->character_manager();
	character_manager->Clear();

	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	
	CCharacterCameraManager* character_camera_manager = character_manager->character_camera_manager();
	character_camera_manager->Uninit();

	//CFieldManager* field_manager = character_manager->field_manager();
	//field_manager->Release();
	//SAFE_RELEASE(field_manager);

	//character_camera_manager->
	//object_2d_manager->Uninit();
	//object_3d_manager->Uninit();

	//SAFE_RELEASE(character_manager);
	//character_manager->Uninit();
	//CFieldManager* field_manager = character_manager->field_manager();
	//SAFE_RELEASE(field_manager);
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
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	CCharacterManager* character_manager= interface_manager_->character_manager();
	CFieldManager* field_manager		= character_manager->field_manager();
	CLightManager* light_manager		= graphic_manager->light_manager();
	CModelManager* model_manager		= graphic_manager->model_manager();
	CCharacterCameraManager* character_camera_manager = character_manager->character_camera_manager();

	CRectangle3D* billboard = new CRectangle3D(device_holder);
	billboard->set_size(VECTOR2(200,200));
	billboard->Set();

	model_manager->Load("resources/model/result");
	// タイトルフォルダのロード
	//texture_manager->Load("resources/texture/game");
	texture_manager->Load("resources/texture/result");

	// オブジェクトの生成
	test_object_key_ = object_3d_manager->AddList(billboard);

	//2d
	CRectangle2D* p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(200,200));
	p_rect2D->Set();
	logo_key_ = object_2d_manager->AddList(p_rect2D);

	//画面下
	p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(400,200));
	p_rect2D->Set();
	press_key_= object_2d_manager->AddList(p_rect2D);;

	// ライトの設定
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(1.0f,0.0f,0.0f).Normalize());
	light_manager->Add(light);

	// ライトの設定
	light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(0.0f,-1.0f,0.0f).Normalize());
	light_manager->Add(light);

	// カメラの生成
	CResultCamera* camera = new CResultCamera(interface_manager_);
	camera->Init();
	character_camera_manager->Push(camera);

	CField* field = new CField(interface_manager_);
	field->Init();
	field_manager->Push(field);

	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	model_key_ = object_3d_manager->AddList(object_model);
}

//=============================================================================
// 自分のファクトリーの生成
//=============================================================================
CSceneFactory* CSceneResult::MakeFactory(void)
{
	return new CResultFactory();
}

void CSceneResult::SetResultFlag(bool fResult)
{
	m_bResult = false;
}

//---------------------------------- EOF --------------------------------------
