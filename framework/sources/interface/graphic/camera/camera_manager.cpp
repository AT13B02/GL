//*****************************************************************************
//
// カメラマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/application.h"

// graphic
#ifdef _USING_OPENGL_
#include "interface/graphic/device/opengl/opengl.h"
#endif
#ifdef _USING_DIRECTX_
#include "interface/graphic/device/directx/directx.h"
#endif
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"

// common
#include "common/math/math.h"
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
CCameraManager::CCameraManager(CDeviceHolder* device_holder)
{
	number_count_ = 0;

	device_holder_ = device_holder;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCameraManager::~CCameraManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CCameraManager::Init(void)
{
	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCameraManager::Update(void)
{
	for(auto it = camera_.begin();it != camera_.end();++it)
	{
		// 更新
		it->second->Update();
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CCameraManager::Uninit(void)
{
	for(auto it = camera_.begin();it != camera_.end();++it)
	{
		// 更新
		SAFE_RELEASE(it->second);
	}

	camera_.clear();
}

//=============================================================================
// 設定処理
//=============================================================================
CCamera* CCameraManager::SetCamera(const u32& idx)
{
	auto it = camera_.begin();

	for(int i = 0;(i < idx) && (it != camera_.end());++i)
	{
		++it;
	}

	it->second->Set();

	return it->second;
}

//=============================================================================
// 取得処理
//=============================================================================
CCamera* CCameraManager::GetCamera(const u32& key)
{
	CCamera* camera = NULL;

	auto it = camera_.find(key);

	if(it != camera_.end())
	{
		camera = it->second;
	}

	return camera;
}

//=============================================================================
// 作成処理
//=============================================================================
u32 CCameraManager::CreateCamera(void)
{
	CCamera* camera = CCamera::Create(device_holder_);

	u32 key = CreateKey();

	camera_.insert(std::pair<u32,CCamera*>(key,camera));

	number_count_++;

	return key;
}

//=============================================================================
// 削除処理
//=============================================================================
bool CCameraManager::EraseCamera(const u32& key)
{
	auto it = camera_.find(key);

	if(it != camera_.end())
	{
		number_count_--;

		// カメラの削除
		SAFE_RELEASE((*it).second);

		// リストから削除
		camera_.erase(key);

		return true;
	}

	return false;
}

//=============================================================================
// キー作成処理
//=============================================================================
u32 CCameraManager::CreateKey(void)
{
	bool is_find = false;
	u32 key = 0;

	while(!is_find)
	{
		key = rand();

		if(camera_.find(key) == camera_.end())
		{
			is_find = true;
		}
	}

	return key;
}

//---------------------------------- EOF --------------------------------------
