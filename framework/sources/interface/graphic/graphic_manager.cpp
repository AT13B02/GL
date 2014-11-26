//*****************************************************************************
//
// グラフィックマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/camera/camera_manager.h"
//#include "interface/graphic/light/light_manager.h"

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
CGraphicManager::CGraphicManager(WINDOW_DATA* window_data)
{
	// デバイスホルダーの生成
	device_holder_ = new CDeviceHolder(window_data);

	// レンダーステートマネージャーの生成
	renderstate_manager_ = new CRenderstateManager(device_holder_);

	// テクスチャマネージャーの生成
	texture_manager_ = new CTextureManager(device_holder_);

	// モデルマネージャーの生成
	model_manager_ = new CModelManager(device_holder_);

	// カメラマネージャーの生成
	camera_manager_ = new CCameraManager(device_holder_);

	// ライトマネージャーの生成
	light_manager_ = NULL;

	// オブジェクトマネージャーの生成
	object_manager_ = new CObjectManager(device_holder_,texture_manager_,model_manager_,renderstate_manager_,camera_manager_,light_manager_);
}

//=============================================================================
// デストラクタ
//=============================================================================
CGraphicManager::~CGraphicManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CGraphicManager::Init(void)
{
	// グラフィックデバイスの初期化
	INIT(device_holder_);

	// テクスチャマネージャーの初期化
	INIT(texture_manager_);

	// レンダーステートマネージャーの初期化
	INIT(renderstate_manager_);

	// オブジェクトマネージャーの初期化
	INIT(object_manager_);

	// モデルマネージャーの初期化
	INIT(model_manager_);

	// カメラマネージャーの初期化
	INIT(camera_manager_);

	// ライトマネージャーの初期化
	//INIT(light_manager_);

	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CGraphicManager::Draw(void)
{
	// 描画開始
	device_holder_->BeginDraw();

	// 描画
	object_manager_->Draw();

	// 描画終了
	device_holder_->EndDraw();
}

//=============================================================================
// 終了処理
//=============================================================================
void CGraphicManager::Uninit(void)
{
	// オブジェクトマネージャーの開放
	SAFE_RELEASE(object_manager_);

	// カメラマネージャーの開放
	SAFE_RELEASE(camera_manager_);

	// ライトマネージャーの開放
	//SAFE_RELEASE(light_manager_);

	// モデルマネージャーの開放
	SAFE_RELEASE(model_manager_);

	// レンダーステートマネージャーの開放
	SAFE_RELEASE(renderstate_manager_);

	// テクスチャマネージャーの開放
	SAFE_RELEASE(texture_manager_);

	// デバイスホルダーの開放
	SAFE_RELEASE(device_holder_);
}

//=============================================================================
// ロード開始
//=============================================================================
void CGraphicManager::BeginLoad(void)
{
	device_holder_->BeginLoad();
}

//=============================================================================
// ロード終了
//=============================================================================
void CGraphicManager::EndLoad(void)
{
	device_holder_->EndLoad();
}

//---------------------------------- EOF --------------------------------------
