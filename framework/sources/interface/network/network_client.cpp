//*****************************************************************************
//
// ネットワーククライアントクラス [network_client.cpp]
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
#include "network_client.h"
#include "../../common/thread/thread.h"
#include "windows_sockets.h"
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

//*****************************************************************************
// スタティックメンバ変数
//*****************************************************************************
s8 CNetworkClient::m_myID = -1;
//=============================================================================
// コンストラクタ
//=============================================================================
CNetworkClient::CNetworkClient(void)
{
	// スレッド
	m_pThread = NULL;

	m_bLoopFlag = true;
	m_myID = -1;
	m_bAllPlayerPrepare = false;
	m_bStartGame = false;
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
	// Winsockの作成
	m_pWinsock = new CWindowsSockets("255.255.255.255");
	// Winsockの初期化
	INIT(m_pWinsock);

	// バッファの作成
	m_pNetworkDataBuffer = new CNetworkDataBuffer;
	//INIT(m_pNetworkDataBuffer);
	m_pNetworkDataBuffer->Init();

	// スレッドの作成
	m_pThread = new CThread;
	// スレッドの初期化
	INIT(m_pThread);

	// 受信スレッドの起動
	m_pThread->Start(ReceiveThread,this);

	// バッファポインタセット
	m_pWinsock->SetNetworkDataBufferPointer(m_pNetworkDataBuffer);

	// 準備完了フラグ初期化
	m_bAllPlayerPrepare = false;

	// ゲームスタートフラグ初期化
	m_bStartGame = false;

	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CNetworkClient::Uninit(void)
{
	NETWORK_DATA SendData = {0};

	SendData.data_type = NETWORK_DATA_TYPE_END;
	SendData.my_ID = m_myID;
	strcpy(SendData.game_ID, kGameID);

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
	char addres[16] = {"\0"};
	sockaddr_in from_adders;
	while(pNetworkClient->m_bLoopFlag)
	{
		NETWORK_DATA Data = {0};
		Data.my_ID = -1;
		
		// データの受信
		int ilen = pNetworkClient->m_pWinsock->ReceiveData(&Data, &from_adders);

		if(ilen <= 0)
		{
			//continue;
		}

		// このゲームかどうかの判断
		if(strcmp(Data.game_ID, kGameID) != 0)
		{
			continue;
		}

		// ネットワーク終了なら
		if(Data.data_type == NETWORK_DATA_TYPE_END && m_myID == Data.my_ID)
		{
			pNetworkClient->m_bLoopFlag = false;
		}

		// ＩＤセット
		if(Data.data_type == NETWORK_DATA_TYPE_SEND_PLAYER_NUMBER && m_myID < 0)
		{
			pNetworkClient->m_pNetworkDataBuffer->SetID(Data.my_ID);
			m_myID = Data.my_ID;
		}
		
		// リザルトへ行くなら
		else if(Data.data_type == NETWORK_DATA_TYPE_GO_TO_RESULT)
		{
			pNetworkClient->m_pNetworkDataBuffer->SetGameSceneEndFlag(true);
		}

		// 全員準備完了してたら
		else if(Data.data_type == NETWORK_DATA_TYPE_END_PREPARE)
		{
			pNetworkClient->m_bAllPlayerPrepare = true;
		}

		// まだ全員準備完了してないなら
		else if(Data.data_type == NETWORK_DATA_TYPE_NOT_END_PREPARE)
		{
			pNetworkClient->m_bAllPlayerPrepare = false;
		}

		// ゲーム開始
		else if(Data.data_type == NETWORK_DATA_TYPE_GO_TO_GAME)
		{
			pNetworkClient->m_bStartGame = true;
		}

		// ゲーム終了
		else if(Data.data_type == NETWORK_DATA_TYPE_END_GAME)
		{
			pNetworkClient->GetWinSock()->SendDataGoToResultScene();
		}

		// 死亡フラグ受信
		else if(Data.data_type == NETWORK_DATA_TYPE_RECIVE_DEATH)
		{
			pNetworkClient->GetNetworkDataBuffer()->ChangeDeath(Data.my_ID);
		}

		// オブジェクトのデータなら
		else
		{
			// データを格納
			pNetworkClient->m_pNetworkDataBuffer->Push(&Data);
		}
	}


	return 0;
}

//---------------------------------- EOF --------------------------------------
