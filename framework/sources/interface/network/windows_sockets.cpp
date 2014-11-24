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
#include "network_data.h"
#include <stdio.h>

#include "common.h"

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

	m_pIpAddress = new char[nLen + 1];

	// IPアドレスの設定
	strcpy(m_pIpAddress,pIpAddress);
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
	CDebugConsole* pDebugConsole = CDebug::GetDebugManager()->GetDebugConsole();
	
	// WinSockの使用開始
	if(WSAStartup(MAKEWORD(2,2),&WsaData))
	{
		pDebugConsole->Print("WindowsSocketsのスタートアップ失敗\n");
		return false;
	}
	
	//ソケットの生成
	m_Socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	// ソケットの生成の確認
	if(m_Socket == INVALID_SOCKET)
	{
		pDebugConsole->Print("ソケットの生成失敗\n");
		return false;
	}

	// マルチキャスト受信許可
	int value = 1;
	setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value) );

	// ソケットアドレスの設定
	m_Sendaddr.sin_port = htons(20000);
	m_Sendaddr.sin_family= AF_INET;
	m_Sendaddr.sin_addr.s_addr = inet_addr(m_pIpAddress);

	// 受信アドレス
	m_Recieveaddr.sin_port = htons(20001);
	m_Recieveaddr.sin_family= AF_INET;
	m_Recieveaddr.sin_addr.s_addr = INADDR_ANY;

	// バインド
	bind(m_Socket,(sockaddr*)&m_Recieveaddr,sizeof(m_Recieveaddr));

	// マルチキャストグループに参加
	ip_mreq mreq;
	memset( &mreq, 0, sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = inet_addr(m_pIpAddress);//マルチキャストアドレス
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt(m_Socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mreq,sizeof(mreq));

	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CWindowsSockets::Uninit(void)
{
	SAFE_DELETE_ARRAY(m_pIpAddress);

	closesocket(m_Socket);
}

//=============================================================================
// データの送信
//=============================================================================
void CWindowsSockets::SendData(char* pData,int nSize)
{
	sendto(m_Socket,(char*)pData,nSize,0,(struct sockaddr*)&m_Sendaddr,sizeof(sockaddr_in));
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
// データの送信
//=============================================================================
void CWindowsSockets::ReceiveData(char* pOutData)
{
	int SockaddrInSize = sizeof(struct sockaddr_in);
	sockaddr_in From;

	recvfrom(m_Socket,(char*)pOutData,sizeof(NETWORK_DATA),0,(sockaddr*)&From,&SockaddrInSize);
}

//---------------------------------- EOF --------------------------------------
