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
#include "explosion/explosion_manager.h"
#include "field/field_manager.h"
#include "collision/collision_manager.h"
#include "attitude_controller/attitude_controller_manager.h"
#include "interface/character/player/network_player.h"
#include "interface/character/box/box_manager.h"
#include "interface/character/player_status/life_2d/life_2d_manager.h"
#include "interface/character/player_status/user_number_2d/icon_2d_manager.h"
// common
#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacterManager::CCharacterManager(void)
{
	//ネットプレイヤー初期化
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		network_player_[ i ] = NULL;
	}

	// プレイヤーマネージャーの生成
	player_manager_ = new CPlayerManager();

	// キャラクターカメラマネージャーの生成
	character_camera_manager_ = new CCharacterCameraManager();

	// バレットマネージャーの生成
	bullet_manager_ = new CBulletManager();
	
	// 爆発マネージャーの生成
	explosion_manager_ = new CExplosionManager();

	// フィールドマネージャーの生成
	field_manager_ = new CFieldManager();

	// 姿勢制御マネージャーの生成
	attitude_controller_manager_ = new CAttitudeControllerManager();

	// 衝突判定マネージャーの生成
	collision_manager_ = new CCollisionManager(this);

	// ボックスマネージャの生成
	box_manager_ = new CBoxManager();

	//ライフマネージャーの生成
	life_2d_manager_ = new CLife2DManager();

	//アイコンマネージャーの生成
	icon_2d_manager_ = new CIcon2DManager();
}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacterManager::~CCharacterManager(void)
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

	// 爆発マネージャーの初期化
	INIT(explosion_manager_);

	// フィールドマネージャーの初期化
	INIT(field_manager_);

	// 姿勢制御コントローラーマネージャーの初期化
	INIT(attitude_controller_manager_);

	// 衝突判定マネージャーの初期化
	INIT(collision_manager_);
	
	// ボックスマネージャーの初期化
	INIT(box_manager_);

	// ライフマネージャーの初期化
	INIT( life_2d_manager_ );

	// アイコンマネージャーの初期化
	INIT( icon_2d_manager_ );
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

	// 爆発マネージャーの更新
	explosion_manager_->Update();

	// フィールドマネージャーの更新
	field_manager_->Update();

	// キャラクターカメラマネージャーの更新
	character_camera_manager_->Update();

	// 衝突判定マネージャーの更新
	collision_manager_->Update();
	
	// ボックスマネージャーの更新
	box_manager_->Update();

	// ライフマネージャーの更新
	life_2d_manager_->Update();

	// アイコンマネージャーの更新
	icon_2d_manager_->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CCharacterManager::Draw(void)
{
	// フィールドマネージャーの描画
	field_manager_->Draw();

	// プレイヤーマネージャーの描画
	player_manager_->Draw();

	// バレットマネージャーの描画
	bullet_manager_->Draw();

	// 爆発マネージャーの更新
	explosion_manager_->Draw();

	// ボックスマネージャーの描画
	box_manager_->Draw();

	// ライフマネージャーの描画
	life_2d_manager_->Draw();

	// アイコンマネージャーの描画
	icon_2d_manager_->Draw();
}

//=============================================================================
// クリア
//=============================================================================
void CCharacterManager::Clear(void)
{
	//ネットプレイヤー初期化
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		SAFE_RELEASE(network_player_[ i ]);
	}

	// プレイヤーマネージャーの開放
	player_manager_->Uninit();

	// キャラクターカメラマネージャーの開放
	character_camera_manager_->Uninit();

	// バレットマネージャーの開放
	bullet_manager_->Uninit();
	
	// 爆発マネージャーの開放
	explosion_manager_->Uninit();

	// フィールドマネージャーの開放
	field_manager_->Uninit();

	// 姿勢制御マネージャーの開放
	attitude_controller_manager_->Uninit();

	// 衝突判定マネージャーの開放
	collision_manager_->Uninit();

	// ボックスマネージャーの開放
	box_manager_->Uninit();

	// ライフマネージャーの解放
	life_2d_manager_->Uninit();

	// アイコンマネージャーの解放
	icon_2d_manager_->Uninit();
}

//=============================================================================
// 終了
//=============================================================================
void CCharacterManager::Uninit(void)
{
	//ネットワークプレイヤーの終了処理
	for( int i = 0; i < kMaxPlayer; i++ )
	{
		if( network_player_[ i ] != NULL )
		{
			network_player_[ i ] -> Uninit();

			delete network_player_[ i ];

			network_player_[ i ] = NULL;
		}
	}

	// プレイヤーマネージャーの開放
	SAFE_RELEASE(player_manager_);

	// キャラクターカメラマネージャーの開放
	SAFE_RELEASE(character_camera_manager_);

	// バレットマネージャーの開放
	SAFE_RELEASE(bullet_manager_);
	
	// 爆発マネージャーの開放
	SAFE_RELEASE(explosion_manager_);

	// フィールドマネージャーの開放
	SAFE_RELEASE(field_manager_);

	// 姿勢制御マネージャーの開放
	SAFE_RELEASE(attitude_controller_manager_);

	// 衝突判定マネージャーの開放
	SAFE_RELEASE(collision_manager_);
	
	// ボックスマネージャーの開放
	SAFE_RELEASE(box_manager_);

	// ライフマネージャーの解放
	SAFE_RELEASE( life_2d_manager_ );

	// ライフマネージャーの解放
	SAFE_RELEASE( icon_2d_manager_ );
}

//---------------------------------- EOF --------------------------------------
