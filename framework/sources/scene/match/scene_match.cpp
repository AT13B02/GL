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
#include "scene/match/scene_match.h"
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

//network
#include "interface/interface_manager.h"
#include "interface/network/network_manager.h"
#include "interface/network/network_client.h"
#include "interface/network/network_data_buffer.h"
#include "interface/network/windows_sockets.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
const float CSceneMatch::PLAYER_DISP_OFFSET_X = 600.0f;
const float CSceneMatch::PLAYER_DISP_OFFSET_Y = 70.0f;
const float CSceneMatch::PLAYER_DISP_START_Y =180.0f;
const VECTOR2 CSceneMatch::HOST_DECITION_DEFAULT_POS(600.0f,600.0f);
const VECTOR2 CSceneMatch::LOGO_DEFAULT_POS(600.0f,60.0f);

const char* CSceneMatch::p_texture_names[TEXTURE_TYPE_MAX] = 
{
	"field001",//logo
	"field001",//player
	"field001",//player
	"field001",//player
	"field001",//player
	"field001",//host
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSceneMatch::CSceneMatch(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	test_object_key_ = -1;
	test_2d_key_ = -1;

	host_decision_key_ = -1;
	flash_timer_ = 0;
	draw_flag_ = false;
	for(int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{ 
		player_Disp_2d_key_[nPlayer] = -1;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneMatch::~CSceneMatch(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CSceneMatch::Init(void)
{
	if(!CScene::Init())
	{
		return false;
	}
	player_Disp_2d_pos_ = VECTOR3(0,0,0);

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CSceneMatch::Update(void)
{
	int my_id = 99;
	my_id = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetID();
	
	// 全員準備完了してたら
	if(interface_manager_->network_manager()->GetNetworkClient()->GetEndAllPlayerPrepareFlag())
	{
		if(my_id == 0)	// IDNo0のみ可能な処理
		{
			if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
			{
				// ゲーム開始通知を送る
				interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendGameStart();
			}
		}
	}

	else
	{
		// 準備完了通知
		if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
		{
			interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDataPrepare(my_id);
			player_Disp_2d_pos_._x += 50.f;
		}
	}

	// ゲーム開始なら
	if(interface_manager_->network_manager()->GetNetworkClient()->GetStartGameFlag())
	{
		set_next_scene(new CGameFactory());
	}
	
	//TODO
	flash_timer_++;
	if(flash_timer_ > FLASH_ALL_TIME)
	{
		flash_timer_ = 0;
	}

	if(flash_timer_ < FLASH_ALL_TIME * 0.5)
	{
		draw_flag_ = true;
	}
	else
	{
		draw_flag_ = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void CSceneMatch::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// 描画
	//object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(90,0,0),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"");
	//object_2d_manager->Draw(test_2d_key_,VECTOR2(),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"");
	object_2d_manager->Draw(host_decision_key_,HOST_DECITION_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_HOST_DECISION]);
	object_2d_manager->Draw(logo_key_,LOGO_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_LOGO]);

	int my_id = 0;
	my_id = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetID();

	for(int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		if(my_id == nPlayer)
		{
			if(draw_flag_)
			{
				object_2d_manager->Draw(player_Disp_2d_key_[nPlayer],VECTOR2(PLAYER_DISP_OFFSET_X + player_Disp_2d_pos_._x,nPlayer * PLAYER_DISP_OFFSET_Y +CSceneMatch::PLAYER_DISP_START_Y),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[1+nPlayer]);
			}
		}
		else
		{
			object_2d_manager->Draw(player_Disp_2d_key_[nPlayer],VECTOR2(PLAYER_DISP_OFFSET_X,nPlayer * PLAYER_DISP_OFFSET_Y +CSceneMatch::PLAYER_DISP_START_Y),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[1+nPlayer]);
		}
	}
}

//=============================================================================
// 終了
//=============================================================================
void CSceneMatch::Uninit(void)
{
}

//=============================================================================
// ロード
//=============================================================================
void CSceneMatch::Load(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CDeviceHolder* device_holder = graphic_manager->device_holder();
	CTextureManager* texture_manager = graphic_manager->texture_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	texture_manager->Load("resources/texture/game");

	CRectangle3D* billboard = new CRectangle3D(device_holder);

	billboard->set_size(VECTOR2(200,200));
	
	billboard->Set();

	// タイトルフォルダのロード
	texture_manager->Load("resources/texture/title");

	// オブジェクトの生成
	test_object_key_ = object_3d_manager->AddList(billboard);

	// リクエストID
	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->RequestID();

	CRectangle2D* p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(200,200));
	p_rect2D->Set();
	test_2d_key_ = object_2d_manager->AddList(p_rect2D);

	for(int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		CRectangle2D* p_rect2D = new CRectangle2D(device_holder);
		p_rect2D->set_size(VECTOR2(512,64));
		p_rect2D->Set();
		player_Disp_2d_key_[nPlayer] = object_2d_manager->AddList(p_rect2D);
	}

	//host board loading
	p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(128,128));
	p_rect2D->Set();
	host_decision_key_ = object_2d_manager->AddList(p_rect2D);

	//logo text loading
	p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(512,128));
	p_rect2D->Set();
	logo_key_ = object_2d_manager->AddList(p_rect2D);
}

//=============================================================================
// 自分のファクトリーの生成
//=============================================================================
CSceneFactory* CSceneMatch::MakeFactory(void)
{
	return new CMatchFactory();
}

//---------------------------------- EOF --------------------------------------
