//*****************************************************************************
//
// シーンマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// scene
#include "scene/scene.h"
#include "scene/factory/scene_factory.h"
#include "scene/scene_manager.h"
#include "scene/load/scene_load.h"

#include "interface/interface_manager.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/device/device_holder.h"

// sound
#include "interface/sound/sound_manager.h"

// common
#include "common/thread/thread.h"
#include "common/common.h"

//fade
#include "interface/graphic/object/object_2d/element/fade_2d.h"

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
CSceneManager::CSceneManager(CInterfaceManager* interface_manager)
{
	// シーンの初期化
	scene_ = NULL;

	// ロードフラグの初期化
	load_flag_ = false;

	// スレッドの初期化
	thread_ = NULL;

	// インターフェースマネージャーの設定
	interface_manager_ = interface_manager;

	// ロード中用のシーンを生成
	load_ = new CSceneLoad(interface_manager);

	// 次のシーンの設定
	next_scene_ = new CTitleFactory();

	// フェード
	fade_2d_ = new CFade2D(interface_manager_->graphic_manager()->device_holder(),interface_manager_);
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneManager::~CSceneManager(void)
{
	
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CSceneManager::Init(void)
{
	// ロード中のシーンのデータをロード
	load_->Load();

	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneManager::Update(void)
{
	// ロードしていないことを確認
	if(!load_flag_)
	{
		if(thread_ != NULL)
		{
			// スレッドが終了していたら
			if(thread_->CheckEnd())
			{
				// スレッドクラスの破棄
				SAFE_RELEASE(thread_);

				// 描画モードをメインに切り換える
				interface_manager_->graphic_manager()->device_holder()->SetDrawMode(CGraphicDevice::DEVICE_MODE_MAIN);
			}
		}

		// シーンが存在しているか確認
		if(scene_ != NULL)
		{
			scene_->Update();

			// 次のシーンが存在しない時
			if(next_scene_ == NULL)
			{
				next_scene_ = scene_->next_scene();
			}
		}

		// 次のシーンが存在するとき
		if(next_scene_ != NULL)
		{
			// ロードフラグをオン
			load_flag_ = true;

			// ロード処理の初期化
			load_->Init();

			// スレッドの生成
			thread_ = new CThread();

			// 描画モードをロードに切り換える
			interface_manager_->graphic_manager()->device_holder()->SetDrawMode(CGraphicDevice::DEVICE_MODE_LOAD);
			interface_manager_->graphic_manager()->device_holder()->BeginDraw();

			// スレッドでロード開始
			thread_->Start(Load,this);
		}
	}
	else
	{
		if(load_ != NULL)
		{
			// ロード中の更新
			load_->Update();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneManager::Draw(void)
{
	fade_2d_->Draw(nullptr);

	// ロードしていないことを確認
	if(!load_flag_)
	{
		if(scene_ != NULL)
		{
			// 描画処理
			scene_->Draw();
		}
	}
	else
	{
		if(load_ != NULL)
		{
			load_->Draw();
		}
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneManager::Uninit(void)
{
	// スレッドの破棄
	SAFE_DELETE(thread_);

	// シーンの破棄
	SAFE_RELEASE(scene_);

	// ロード中用のシーンの破棄
	SAFE_RELEASE(load_);

	// 次のシーンの破棄
	SAFE_DELETE(next_scene_);

	// フェードの破棄
	SAFE_DELETE(fade_2d_);
}

//=============================================================================
// ロード処理
//=============================================================================
void CSceneManager::Load(CSceneManager* scene_manager)
{
	// シーンマネージャーが存在するとき
	if(scene_manager != NULL)
	{
		// 現在のシーンがあったら
		if(scene_manager->scene_ != NULL)
		{
			// シーンが同じとき
			if(scene_manager->scene_->scene_type() == scene_manager->next_scene_->scene_type())
			{
				// 初期化
				scene_manager->scene_->Init();

				// ロードの終了
				scene_manager->load_flag_ = false;
			}
			else
			{
				// 現在のシーンの開放
				SAFE_RELEASE(scene_manager->scene_);
			}
		}

		// ロードする
		if(scene_manager->load_flag_)
		{
			// インターフェースを読み込みモードにする
			scene_manager->interface_manager_->graphic_manager()->device_holder()->SetLoadMode(CGraphicDevice::DEVICE_MODE_MAIN);

			// ロード開始
			scene_manager->interface_manager_->BeginLoad();

			// シーンの生成
			scene_manager->scene_ = scene_manager->next_scene_->Make(scene_manager->interface_manager_);

			// 読み込み処理
			scene_manager->scene_->Load();

			// 初期化処理
			scene_manager->scene_->Init();

			// 次のシーンを破棄
			SAFE_DELETE(scene_manager->next_scene_);

			// インターフェースの読み込みモードを終了する
			scene_manager->interface_manager_->EndLoad();
		}
	}

	// ロードの終了
	scene_manager->load_flag_ = false;
}

//---------------------------------- EOF --------------------------------------
