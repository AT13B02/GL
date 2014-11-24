//*****************************************************************************
//
// オブジェクトマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/light/light_manager.h"
//#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/renderstate/state/renderstate.h"
//#include "interface/graphic/texture/texture_manager.h"
//#include "interface/graphic/camera/camera_manager.h"

// common
#include "common/common.h"

//*****************************************************************************
// 定数定義
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
CObjectManager::CObjectManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CModelManager* model_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager)
{
	// デバイスホルダーの設定
	device_holder_ = device_holder;

	// テクスチャマネージャーの設定
	texture_manager_ = texture_manager;

	// モデルマネージャーの設定
	model_manager_ = model_manager;

	// レンダーステートマネージャーの設定
	renderstate_manager_ = renderstate_manager;

	// カメラマネージャーの生成
	camera_manager_ = camera_manager;

	// ライトマネージャーの生成
	light_manager_ = light_manager_;

	// オブジェクト2Dマネージャーの生成
	//object_2d_manager_ = new CObject2DManager(graphic_device_,renderstate_manager);

	// オブジェクト3Dマネージャーの生成
	object_3d_manager_ = new CObject3DManager(device_holder_,texture_manager_,renderstate_manager_,model_manager_,camera_manager_,light_manager_);
}

//=============================================================================
// デストラクタ
//=============================================================================
CObjectManager::~CObjectManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CObjectManager::Init(void)
{
	// テクスチャマネージャーの初期化
	//INIT(texture_manager_);

	// レンダーステートマネージャーの初期化
	//INIT(renderstate_manager_);

	// オブジェクト2Dマネージャーの初期化
	//INIT(object_2d_manager_);

	// オブジェクト3Dマネージャーの初期化
	//INIT(object_3d_manager_);

	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CObjectManager::Draw(void)
{
	CRenderstate* renderstate_all = NULL;

	if(renderstate_manager_ != NULL)
	{
		renderstate_all = renderstate_manager_->renderstate(CRenderstateManager::TYPE_ALL);
	}

	if(renderstate_all != NULL)
	{
		renderstate_all->Set();
	}

	if(object_3d_manager_ != NULL)
	{
		// オブジェクト3Dの描画
		object_3d_manager_->Draw();
	}

	// オブジェクト2Dの描画
	//object_2d_manager_->Draw();

	// レンダーステートの解除
	if(renderstate_all != NULL)
	{
		// レンダーステートの解除
		renderstate_all->Unset();
	}

}

//=============================================================================
// 終了処理
//=============================================================================
void CObjectManager::Uninit(void)
{
	// オブジェクト3Dマネージャーの開放
	SAFE_RELEASE(object_3d_manager_);

	// オブジェクト2Dマネージャーの開放
	//SAFE_RELEASE(object_3d_manager_);

	// カメラマネージャーの開放
	SAFE_RELEASE(camera_manager_);

	// ライトマネージャーの開放
	//SAFE_RELEASE(light_manager_);
}

//---------------------------------- EOF --------------------------------------
