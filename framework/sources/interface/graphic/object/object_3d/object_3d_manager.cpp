//*****************************************************************************
//
// オブジェクト3Dマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_list.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"
#include "interface/graphic/object/object_3d/object_3d_buffer.h"
#include "interface/graphic/object/object_3d/element/object_3d.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/renderstate/state/renderstate.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/light/light_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/device/device_holder.h"

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
CObject3DManager::CObject3DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CModelManager* model_manager,CCameraManager* camera_manager,CLightManager* light_manager)
{
	// グラフィックデバイスの設定
	device_holder_ = device_holder;

	// レンダーステートマネージャーの設定
	renderstate_manager_ = renderstate_manager;

	// テクスチャマネージャの設定
	texture_manager_ = texture_manager;

	// カメラマネージャーの設定
	camera_manager_ = camera_manager;

	// モデルマネージャーの設定
	model_manager_ = model_manager;

	// ライトマネージャーの設定
	light_manager_ = light_manager;

	// オブジェクトリストの生成
	object_3d_list_ = new CObject3DList();

	// オブジェクトバッファの生成
	object_3d_buffer_ = new CObject3DBuffer();
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3DManager::~CObject3DManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CObject3DManager::Init(void)
{
	INIT(object_3d_list_);
	INIT(object_3d_buffer_);
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject3DManager::Draw(void)
{
	CCamera* camera = NULL;

	// レンダーステートの設定
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_3D)->Set();

	for(int i = 0;i < camera_manager_->number_count();i++)
	{
		// カメラの設定と設定したカメラの取得
		camera = camera_manager_->SetCamera(i);

		// ライトの設定
		light_manager_->Set();

		// バッファの描画処理
		object_3d_buffer_->Draw(camera,texture_manager_,model_manager_);
	}

	// ライトの解除
	light_manager_->Unset();

	// TODO バッファの破棄 スレッドを分けたらなくなる
	object_3d_buffer_->Refresh();

	// レンダーステートの解除
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_3D)->Unset();
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject3DManager::Uninit(void)
{
	// オブジェクトリストの開放
	SAFE_RELEASE(object_3d_list_);

	// バッファの開放
	SAFE_RELEASE(object_3d_buffer_);
}

//=============================================================================
// オブジェクト追加処理
//=============================================================================
u32 CObject3DManager::AddList(CObject3D* object_3d)
{
	return object_3d_list_->AddList(object_3d);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject3DManager::Draw(const u32& object_key,const VECTOR3& position,const VECTOR3& rotation,const VECTOR3& scale,MATRIX4x4 matrix,const std::string& texture_name,CRenderstate* renderstate)
{
	CObject3DData* object_3d_data = NULL;
	CObject3D* object_3d = object_3d_list_->GetListData(object_key);

	// オブジェクト番号の確認
	if(object_3d == NULL)
	{
		return;
	}

	// バッファの生成
	object_3d_data = new CObject3DData();

	// バッファ番号の設定
	object_3d_data->set_object_3d(object_3d);

	// 座標の設定
	object_3d_data->set_position(position);

	// 回転角の設定
	object_3d_data->set_rotation(rotation);

	// スケールの設定
	object_3d_data->set_scale(scale);

	// マトリックスの設定
	object_3d_data->set_matrix(matrix);

	// テクスチャの設定
	object_3d_data->set_texture_name(texture_name);

	// レンダーステートの設定
	object_3d_data->set_renderstate(renderstate);

	// バッファリストに追加
	object_3d_buffer_->AddList(object_3d_data);
}

//---------------------------------- EOF --------------------------------------
