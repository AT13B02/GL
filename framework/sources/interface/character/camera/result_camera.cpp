//*****************************************************************************
//
// タイトルカメラクラス
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "interface/character/camera/result_camera.h"

#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/graphic_manager.h"

#include "interface/input/input_manager.h"
#include "interface/input/input_manager.h"

#include "interface/interface_manager.h"

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
CResultCamera::CResultCamera(CInterfaceManager* interface_manager) : CCharacterCamera(interface_manager)
{
	move_speed_ = 0;
	camera_key_ = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CResultCamera::~CResultCamera(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CResultCamera::Init(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	WINDOW_DATA* window_data = interface_manager_->window_data();
	CCameraManager* camera_manager = graphic_manager->camera_manager();
	camera_key_ = camera_manager->CreateCamera();
	CCamera* camera = camera_manager->GetCamera(camera_key_);

	// 初期化失敗
	if(!camera->Init())
	{
		// 作ったカメラを削除
		camera_manager->EraseCamera(camera_key_);
		return false;
	}

	// 初期座標の設定
	//camera->SetPosition(VECTOR3(0.0f,10.0f,100.0f),VECTOR3(0.0f,0.0f,0.0f));
	//camera->SetPosition(VECTOR3(0.0f,60.0f,100.0f),VECTOR3(0.0f,0.0f,0.0f));
	camera->SetPosition(VECTOR3(0.0f,90.0f,130.0f),VECTOR3(0.0f,0.0f,0.0f));

	// パースペクティブの設定
	camera->SetPerspective(60.0f,((f32)(window_data->_width) / window_data->_height),1.0f,10000.0f);

	move_speed_ = 1.0f;

	length_ = 50.0f;

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CResultCamera::Update(void)
{
	//角度更新
	//rot_ += 2.0f;
	//角度調整
	//if( rot_ > 180 )
	//{
	//	rot_ = -180.0f;
	//}
	//
	////セット
	//interface_manager_->graphic_manager()->camera_manager()->GetCamera(camera_key_)->SetRotationEyeToLookAt(VECTOR3(0.0f, rot_, 0.0f));
}

//=============================================================================
// 終了
//=============================================================================
void CResultCamera::Uninit(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	WINDOW_DATA* window_data = interface_manager_->window_data();
	CCameraManager* camera_manager = graphic_manager->camera_manager();
	CCamera* camera = camera_manager->GetCamera(camera_key_);

	camera_manager->EraseCamera(camera_key_);
}

//---------------------------------- EOF --------------------------------------
