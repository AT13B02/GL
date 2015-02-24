//*****************************************************************************
//
// キャラクタマネージャークラス
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _CHARACTER_MANAGER_H_
#define _CHARACTER_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"

// character
#include "interface/character/character_manager_interface.h"
#include "interface/network/network_data_buffer.h"


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CPlayerManager;
class CCharacterCameraManager;
class CBulletManager;
class CFieldManager;
class CAttitudeControllerManager;
class CCollisionManager;
class CNetWorkPlayer;
class CBoxManager;
class CLife2DManager;
class CIcon2DManager;
//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCharacterManager : public CBasic
{
public:
	// コンストラクタ
	CCharacterManager(void);

	// デストラクタ
	~CCharacterManager(void);

	// 初期化処理
	bool Init(void);

	// 描画
	void Draw(void);

	// 終了処理
	void Uninit(void);

	// 更新処理
	void Update(void);

	// クリア
	void Clear(void);

	// プレイヤーマネージャーの取得
	CPlayerManager* player_manager(void){return player_manager_;}

	// キャラクターカメラマネージャーの取得
	CCharacterCameraManager* character_camera_manager(void){return character_camera_manager_;}

	// バレットマネージャー取得
	CBulletManager* bullet_manager(void){return bullet_manager_;}

	// フィールドマネージャーの取得
	CFieldManager* field_manager(void){return field_manager_;}

	//ネットワークプレイヤー取得
	CNetWorkPlayer* network_player( int id ){ return network_player_[ id ]; }

	//ネットワークプレイヤーセット処理
	 void SetNetworkPlayer( CNetWorkPlayer* net_player, int id ){ network_player_[ id ] = net_player; }

	// 姿勢制御マネージャーの取得
	CAttitudeControllerManager* attitude_controller_manager(void){return attitude_controller_manager_;}

	// ボックスマネージャの取得
	CBoxManager* box_manager(){return box_manager_;}

	// ライフマネージャーの取得
	CLife2DManager* life_2d_manager( void ){ return life_2d_manager_ ; }

	// アイコンマネージャーの取得
	CIcon2DManager* icon_2d_manager( void ){ return icon_2d_manager_ ; }
private:
	CPlayerManager* player_manager_;
	CCharacterCameraManager* character_camera_manager_;
	CBulletManager* bullet_manager_;
	CFieldManager* field_manager_;
	CAttitudeControllerManager* attitude_controller_manager_;
	CCollisionManager* collision_manager_;
	CNetWorkPlayer* network_player_[ kMaxPlayer ];
	CBoxManager* box_manager_;
	CLife2DManager* life_2d_manager_;
	CIcon2DManager* icon_2d_manager_;
};

#endif // _CHARACTER_MANAGER_H_

//---------------------------------- EOF --------------------------------------
