//*****************************************************************************
//
// ネットワークマネージャークラス [network_data_buffer.cpp]
//
// Author		: KENJI KABUTOMORI
//				  NAOKI NOJIRI
// Date			: 2014/09/17(Wed)
// Version		: 1.01
// Update Date	: 2014/12/01(Mon)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "network_data_buffer.h"
#include "../../common/common.h"

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
CNetworkDataBuffer::CNetworkDataBuffer(void)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CNetworkDataBuffer::~CNetworkDataBuffer(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CNetworkDataBuffer::Init(void)
{
	for(int i = 0; i < kMaxPlayer; ++i)
	{
		m_CharcterInfoBuffer[i].animation_id = 0;
		m_CharcterInfoBuffer[i].player_id = 0;
		m_CharcterInfoBuffer[i].position = VECTOR3(0.f, 0.f, 0.f);
		m_CharcterInfoBuffer[i].rotation = VECTOR3(0.f, 0.f, 0.f);
		m_CharcterInfoBuffer[i].end_push_flag = false;

		m_BulletInfoBuffer[i].position = VECTOR3(0.f, 0.f, 0.f);
		m_BulletInfoBuffer[i].front_vector = VECTOR3(0.f, 0.f, 0.f);
		m_BulletInfoBuffer[i].player_id = -1;
		m_BulletInfoBuffer[i].speed = 0.f;
		m_BulletInfoBuffer[i].end_push_flag = false;
	}
	ZeroMemory(&m_InitAddres, sizeof(m_InitAddres));
	m_MyID = -1;
	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CNetworkDataBuffer::Uninit(void)
{
}

//=============================================================================
// データの格納
//=============================================================================
void CNetworkDataBuffer::Push(NETWORK_DATA* Data)
{
	if(Data->my_type == MY_TYPE_CHARCTER)
	{
		PushCharcter(Data);
	}

	else if(Data->my_type == MY_TYPE_BULLET)
	{
		PushBullet(Data);
	}
}

//=============================================================================
// キャラデータの追加
//=============================================================================
void CNetworkDataBuffer::PushCharcter(NETWORK_DATA* pData)
{
	if(pData->my_ID < 0 || pData->my_ID >= kMaxPlayer)
	{
		return;
	}

	switch(pData->data_type)
	{
		case NETWORK_DATA_TYPE_POSITION:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].position._x = pData->position.x;
			m_CharcterInfoBuffer[pData->my_ID].position._y = pData->position.y;
			m_CharcterInfoBuffer[pData->my_ID].position._z = pData->position.z;
		break;

		case NETWORK_DATA_TYPE_ROTATION:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].rotation._x = pData->rotation.x;
			m_CharcterInfoBuffer[pData->my_ID].rotation._y = pData->rotation.y;
			m_CharcterInfoBuffer[pData->my_ID].rotation._z = pData->rotation.z;
		break;

		case NETWORK_DATA_TYPE_ANIMATION_ID:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].animation_id = pData->animation_ID.animation_ID;
		break;

		case NETWORK_DATA_TYPE_ALL_SEND:
			m_CharcterInfoBuffer[pData->my_ID].player_id = pData->my_ID;
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = true;
		break;

		default:
		break;
	}
}

//=============================================================================
// 弾データの追加
//=============================================================================
void CNetworkDataBuffer::PushBullet(NETWORK_DATA* pData)
{
	if(pData->my_ID < 0 || pData->my_ID >= kMaxPlayer)
	{
		return;
	}

	switch(pData->data_type)
	{
		case NETWORK_DATA_TYPE_POSITION:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_BulletInfoBuffer[pData->my_ID].position._x = pData->position.x;
			m_BulletInfoBuffer[pData->my_ID].position._y = pData->position.y;
			m_BulletInfoBuffer[pData->my_ID].position._z = pData->position.z;
		break;

		case NETWORK_DATA_TYPE_FRONT_VECTOR:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_BulletInfoBuffer[pData->my_ID].front_vector._x = pData->front_vector.x;
			m_BulletInfoBuffer[pData->my_ID].front_vector._y = pData->front_vector.y;
			m_BulletInfoBuffer[pData->my_ID].front_vector._z = pData->front_vector.z;
		break;

		case NETWORK_DATA_TYPE_SPEED:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_BulletInfoBuffer[pData->my_ID].speed = pData->speed.speed;
		break;

		case NETWORK_DATA_TYPE_ALL_SEND:
			m_CharcterInfoBuffer[pData->my_ID].player_id = pData->my_ID;
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = true;
		break;

		default:
		break;
	}
}

//=============================================================================
// IDをセット
//=============================================================================
void CNetworkDataBuffer::SetID(NETWORK_DATA* pData)
{
	m_MyID = pData->my_ID;
}

//---------------------------------- EOF --------------------------------------
