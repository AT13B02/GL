//*****************************************************************************
//
// ネットワーククライアントクラス [network_client.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/17(Wed)
// Version		: 1.00
// Update Date	: 2014/09/17(Wed)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "network_client.h"
#include "thread.h"
#include "windows_sockets.h"
#include "network_data_buffer.h"
#include "common.h"

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
CNetworkClient::CNetworkClient(void)
{
	// スレッド
	m_pThread = NULL;

	// スレッドの作成
	m_pThread = new CThread();

	// Winsockの作成
	m_pWinsock = new CWindowsSockets("239.0.0.9");

	// バッファの作成
	m_pNetworkDataBuffer = new CNetworkDataBuffer();
}

//=============================================================================
// デストラクタ
//=============================================================================
CNetworkClient::~CNetworkClient(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CNetworkClient::Init(void)
{
	// Winsockの初期化
	INIT(m_pWinsock);


	INIT(m_pNetworkDataBuffer);

	// スレッドの初期化
	INIT(m_pThread);

	// 受信スレッドの起動
	m_pThread->Start(ReceiveThread,this);

	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CNetworkClient::Uninit(void)
{
	NETWORK_DATA SendData;

	SendData.Type = NETWORK_DATA_TYPE_END;

	// 自分にデータを送信し、受信を終了させる
	m_pWinsock->SendDataMyself((char*)&SendData,sizeof(NETWORK_DATA));

	// スレッドの開放
	SAFE_RELEASE(m_pThread);

	// Winsockの開放
	SAFE_RELEASE(m_pWinsock);

	// ネットワークデータバッファの開放
	SAFE_RELEASE(m_pNetworkDataBuffer);
}

//=============================================================================
// 受信スレッド
//=============================================================================
unsigned __stdcall CNetworkClient::ReceiveThread(CNetworkClient* pNetworkClient)
{
	while(pNetworkClient->m_bLoopFlag)
	{
		NETWORK_DATA Data;

		// データの受信
		pNetworkClient->m_pWinsock->ReceiveData((char*)&Data);

		if(Data.Type == NETWORK_DATA_TYPE_END)
		{
			pNetworkClient->m_bLoopFlag = false;
		}
		else
		{
			// データを格納
			pNetworkClient->m_pNetworkDataBuffer->Push(Data);
		}
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
