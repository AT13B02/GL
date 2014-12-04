//*****************************************************************************
//
// オブジェクト2Dマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/object_2d_list.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"
#include "interface/graphic/object/object_2d/object_2d_buffer.h"
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
CObject2DManager::CObject2DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager)
{
	// グラフィックデバイスの設定
	device_holder_ = device_holder;

	// レンダーステートマネージャーの設定
	renderstate_manager_ = renderstate_manager;

	// テクスチャマネージャの設定
	texture_manager_ = texture_manager;

	// カメラマネージャーの設定
	camera_manager_ = camera_manager;

	// ライトマネージャーの設定
	light_manager_ = light_manager;

	// オブジェクトリストの生成
	object_2d_list_ = new CObject2DList();

	// オブジェクトバッファの生成
	object_2d_buffer_ = new CObject2DBuffer();
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject2DManager::~CObject2DManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CObject2DManager::Init(void)
{
	INIT(object_2d_list_);
	INIT(object_2d_buffer_);
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject2DManager::Draw(void)
{
	CCamera* camera = NULL;

	//light Setting

	//RenderState Setting
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_2D)->Set();

	//for(int i = 0;i < camera_manager_->number_count();i++)
	//{
		// カメラの設定と設定したカメラの取得
		//camera = camera_manager_->SetCamera(i);

		// バッファの描画処理
		object_2d_buffer_->Draw(camera,texture_manager_);
	//}

	// TODO バッファの破棄 スレッドを分けたらなくなる
	object_2d_buffer_->Refresh();

	//End of RenderState
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_2D)->Unset();
	
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject2DManager::Uninit(void)
{
	// オブジェクトリストの開放
	SAFE_RELEASE(object_2d_list_);

	// バッファの開放
	SAFE_RELEASE(object_2d_buffer_);
}

//=============================================================================
// オブジェクト追加処理
//=============================================================================
u32 CObject2DManager::AddList(CObject2D* object_2d)
{
	return object_2d_list_->AddList(object_2d);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const u32& object_key,const VECTOR2& position,const float rotation,const VECTOR2& scale,MATRIX4x4 matrix,const std::string& texture_name)
{
	CObject2DData* object_2d_data = NULL;
	CObject2D* object_2d = object_2d_list_->GetListData(object_key);

	// オブジェクト番号の確認
	if(object_2d == NULL)
	{
		return;
	}

	// バッファの生成
	object_2d_data = new CObject2DData();

	// バッファ番号の設定
	object_2d_data->set_object_2d(object_2d);

	// 座標の設定
	object_2d_data->set_position(position);

	// 回転角の設定
	object_2d_data->set_rotation(rotation);

	// スケールの設定
	object_2d_data->set_scale(scale);

	// マトリックスの設定
	object_2d_data->set_matrix(matrix);

	// テクスチャの設定
	object_2d_data->set_texture_name(texture_name);

	// レンダーステートの設定
	object_2d_data->set_renderstate(NULL);

	// バッファリストに追加
	object_2d_buffer_->AddList(object_2d_data);
}

//---------------------------------- EOF --------------------------------------
