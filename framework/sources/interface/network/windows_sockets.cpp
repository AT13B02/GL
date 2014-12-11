//*****************************************************************************
//
// WindowsSockets処理 [windows_sockets.cpp]
//
// Author		: 兜森 健史
// Date			: 2014/05/07(Wed)
// Version		: 1.00
// Modified by	: 兜森 健史
// Update date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "windows_sockets.h"
#include <stdio.h>

#include "../../common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
//*****************************************************************************
const int PORT_NUMBER = 20000;

//*****************************************************************************
// 構造体定義
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
CWindowsSockets::CWindowsSockets(const char* pIpAddress)
{
	int nLen = 0;

	nLen = strlen(pIpAddress);

	// IPアドレスの設定
	strcpy(m_pIpAddress,("255.255.255.255\0"));
}

//=============================================================================
// デストラクタ
//=============================================================================
CWindowsSockets::~CWindowsSockets(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CWindowsSockets::Init(void)
{
	WSADATA WsaData;		// WindowsSocketsSocketAPIデータ
	// IPアドレスの設定
	strcpy(m_pIpAddress,("255.255.255.255\0"));
	
	// WinSockの使用開始
	if(WSAStartup(MAKEWORD(2,2),&WsaData))
	{
		DEBUG_TOOL.debug_console()->Print("WindowsSocketsのスタートアップ失敗\n");
		return false;
	}
	
	//ソケットの生成
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// ソケットの生成の確認
	if(m_Socket == INVALID_SOCKET)
	{
		DEBUG_TOOL.debug_console()->Print("ソケットの生成失敗\n");
		return false;
	}

	char yes = '1';
	// ブロードキャスト許可
	setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));

	// 送信アドレスの設定
	memset(&m_Sendaddr, 0, sizeof(m_Sendaddr));
	m_Sendaddr.sin_addr.s_addr = inet_addr(m_pIpAddress);
	m_Sendaddr.sin_port = htons(20002);
	m_Sendaddr.sin_family = AF_INET;

	// 受信アドレス
	memset(&m_Recieveaddr, 0, sizeof(m_Recieveaddr));
	m_Recieveaddr.sin_addr.s_addr = INADDR_ANY;
	m_Recieveaddr.sin_port = htons(20002);
	m_Recieveaddr.sin_family= AF_INET;
	int len = sizeof(m_Recieveaddr);

	// バインド
	if(bind(m_Socket,(struct sockaddr*)&m_Recieveaddr,len) < 0)
	{
		int i;
		i = WSAGetLastError();
		i = i;
	}

//	// マルチキャストグループに参加
//	ip_mreq mreq;
//	memset( &mreq, 0, sizeof(mreq) );
//	mreq.imr_multiaddr.s_addr = inet_addr(m_pIpAddress);//マルチキャストアドレス
//	mreq.imr_interface.s_addr = INADDR_ANY;
//	setsockopt(m_Socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mreq,sizeof(mreq));

	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CWindowsSockets::Uninit(void)
{
	closesocket(m_Socket);
}

//=============================================================================
// データの送信
//=============================================================================
void CWindowsSockets::SendDataCharcter(VECTOR3* position, VECTOR3* rotation, int animation_id, int player_id)
{
	NETWORK_DATA Data = {0};
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.my_ID = player_id;
	sockaddr_in Send;

	Send.sin_port = m_Sendaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr = m_Sendaddr.sin_addr;

	Data.data_type = NETWORK_DATA_TYPE_POSITION;
	{
		Data.position.x = position->_x;
		Data.position.y = position->_y;
		Data.position.z = position->_z;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	Data.data_type = NETWORK_DATA_TYPE_ROTATION;
	{
		Data.rotation.x = rotation->_x;
		Data.rotation.y = rotation->_y;
		Data.rotation.z = rotation->_z;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	Data.data_type = NETWORK_DATA_TYPE_ANIMATION_ID;
	{
		Data.animation_ID.animation_ID = animation_id;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	// 全て送った通知を出す
	Data.data_type = NETWORK_DATA_TYPE_ALL_SEND;
	{
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}
}

//=============================================================================
// データの送信
//=============================================================================
void CWindowsSockets::SendDataBullet(VECTOR3* position, VECTOR3* front_vector, float speed, int player_id)
{
	NETWORK_DATA Data = {0};
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_BULLET;
	Data.my_ID = player_id;
	sockaddr_in Send;

	Send.sin_port = m_Sendaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr.s_addr = m_Sendaddr.sin_addr.s_addr;

	Data.data_type = NETWORK_DATA_TYPE_POSITION;
	{
		Data.position.x = position->_x;
		Data.position.y = position->_y;
		Data.position.z = position->_z;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	Data.data_type = NETWORK_DATA_TYPE_FRONT_VECTOR;
	{
		Data.front_vector.x = front_vector->_x;
		Data.front_vector.y = front_vector->_y;
		Data.front_vector.z = front_vector->_z;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	Data.data_type = NETWORK_DATA_TYPE_SPEED;
	{
		Data.speed.speed = speed;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	// 全て送った通知を出す
	Data.data_type = NETWORK_DATA_TYPE_ALL_SEND;
	{
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}
}
//=============================================================================
// データの送信
//=============================================================================
void CWindowsSockets::RequestID(void)
{
	//TODO
	m_Sendaddr.sin_port = htons(20001);

	NETWORK_DATA Data = {0};
	Data.my_ID = -1;
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.data_type = NETWORK_DATA_TYPE_REQUEST_PLAYER_NUMBER;
	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&m_Sendaddr, sizeof(m_Sendaddr));

	//TODO
	m_Sendaddr.sin_port = htons(20002);
}


//=============================================================================
// データの送信
//=============================================================================
void CWindowsSockets::SendDataMyself(char* pData,int nSize)
{
	sockaddr_in Send;

	Send.sin_port = m_Recieveaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr.s_addr = m_Sendaddr.sin_addr.s_addr;

	sendto(m_Socket,(char*)pData,nSize,0,(struct sockaddr*)&Send,sizeof(sockaddr_in));
}

//=============================================================================
// データの受信
//=============================================================================
int CWindowsSockets::ReceiveData(NETWORK_DATA* pOutData, sockaddr_in* from_addres)
{
	struct sockaddr_in from_addr;
	int SockaddrInSize = sizeof(from_addr);

	int ilen = recvfrom(m_Socket,(char*)pOutData,sizeof(NETWORK_DATA),0,(struct sockaddr*)&from_addr,&SockaddrInSize);
	
	return ilen;
}

//---------------------------------- EOF --------------------------------------
