//*****************************************************************************
//
// キャラクタマネージャークラス
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// character
#include "character_manager.h"
#include "player/player_manager.h"
#include "camera/character_camera_manager.h"
#include "bullet/bullet_manager.h"
#include "attitude_controller/attitude_controller_manager.h"

// common
#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacterManager::CCharacterManager()
{
	// プレイヤーマネージャーの生成
	player_manager_ = new CPlayerManager();

	// キャラクターカメラマネージャーの生成
	character_camera_manager_ = new CCharacterCameraManager();

	// バレットマネージャーの生成
	bullet_manager_ = new CBulletManager();

	// 姿勢制御マネージャーの生成
	attitude_controller_manager_ = new CAttitudeControllerManager();
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacterManager::~CCharacterManager()
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CCharacterManager::Init(void)
{
	// プレイヤーマネージャーの初期化
	INIT(player_manager_);

	// カメラマネージャーの初期化
	INIT(character_camera_manager_);

	// バレットマネージャーの初期化
	INIT(bullet_manager_);

	// 姿勢制御コントローラーマネージャーの初期化
	INIT(attitude_controller_manager_);

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CCharacterManager::Update(void)
{
	// 姿勢制御コントローラーの更新
	attitude_controller_manager_->Update();

	// プレイヤーマネージャーの更新
	player_manager_->Update();

	// バレットマネージャーの更新
	bullet_manager_->Update();

	// キャラクターカメラマネージャーの更新
	character_camera_manager_->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CCharacterManager::Draw(void)
{
	// プレイヤーマネージャーの描画
	player_manager_->Draw();

	// バレットマネージャーの描画
	bullet_manager_->Draw();
}

//=============================================================================
// 終了
//=============================================================================
void CCharacterManager::Uninit(void)
{
	// プレイヤーマネージャーの開放
	SAFE_RELEASE(player_manager_);

	// キャラクターカメラマネージャーの開放
	SAFE_RELEASE(character_camera_manager_);

	// バレットマネージャーの開放
	SAFE_RELEASE(bullet_manager_);

	// 姿勢制御マネージャーの開放
	SAFE_RELEASE(attitude_controller_manager_);
}

//---------------------------------- EOF --------------------------------------
