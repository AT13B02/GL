//*****************************************************************************
//
// ネットワークデータバッファクラス [network_data_buffer.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/17(Wed)
// Version		: 1.00
// Update Date	: 2014/09/17(Wed)
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _NETWORK_DATA_BUFFER_H_
#define _NETWORK_DATA_BUFFER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "../../basic/basic.h"
#include "network_data.h"
#include "../../common/math/vector/vector3.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static const int kMaxPlayer = 4;
static const int kMaxHP = 100;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	char from_addr[16];
}FROM_ADDERS;

typedef struct
{
	bool end_push_flag;
	int player_id;
	int animation_id;
	VECTOR3 position;
	VECTOR3 rotation;
	int hp;
}CHARCTER_INFO;

typedef struct
{
	bool end_push_flag;
	int player_id;
	float speed;
	VECTOR3 position;
	VECTOR3 front_vector;
}BULLET_INFO;

typedef struct
{
	bool recive_position;
	bool recive_rotation;
	bool recive_animation_ID;
	bool recive_speed;
	bool recive_frontvector;
	bool recive_hp;
}RECIVE_STATE;

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CNetworkDataBuffer : public CBasic
{
public:
	// コンストラクタ
	CNetworkDataBuffer(void);

	// デストラクタ
	virtual ~CNetworkDataBuffer(void);

	// 初期化処理
	bool Init(void);

	// 終了処理
	void Uninit(void);

	// データの追加
	void Push(NETWORK_DATA* pData);

	// IDをセット**プレイヤーや弾は呼び出さない***
	void SetID(int player_id);

	// IDをゲット
	int GetID(void){return m_MyID;};

	// キャラクター情報バッファ取得
	CHARCTER_INFO* GetCharcterInfoBuffer(void);

	// 弾情報バッファ取得
	BULLET_INFO* GetBulletInfoBuffer(void);

	// ゲームシーン終了フラグをセット
	void SetGameSceneEndFlag(bool flag){m_GameSceneEnd = flag;};
	// ゲームシーン終了フラグをゲット
	bool GetGameSceneEndFlag(void){return m_GameSceneEnd;};

	// 死亡判定に変更
	void ChangeDeath(int player_id){m_DeathFlag[player_id] = true;};

	// 死亡フラグゲット
	bool GetCharDeathFlag(int player_id){return m_DeathFlag[player_id];};

	// フラグ初期化
	void InitFlag(void);

protected:
	// キャラデータの追加
	void PushCharcter(NETWORK_DATA* pData);

	// 弾データの追加
	void PushBullet(NETWORK_DATA* pData);

private:
	char m_InitAddres[16];
	CHARCTER_INFO m_CharcterInfoBuffer[kMaxPlayer];
	BULLET_INFO m_BulletInfoBuffer[kMaxPlayer];
	int m_MyID;
	RECIVE_STATE m_ReciveState[kMaxPlayer];
	RECIVE_STATE m_ReciveStateBullet[kMaxPlayer];
	bool m_GameSceneEnd;
	bool m_DeathFlag[kMaxPlayer];
};

#endif	// _NETWORK_DATA_BUFFER_H_

//---------------------------------- EOF --------------------------------------
