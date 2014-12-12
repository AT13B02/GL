//********************************************************************
// UDPデータ送受信プログラム
// メインの処理(main.cpp)
// aughter: NAOKI NOJIRI  20236
//********************************************************************
//********************************************************************
// インクルード
//********************************************************************
#include "main.h"
#include <stdio.h>
#include <WinSock2.h>

//********************************************************************
// ライブラリのリンク
//********************************************************************
#pragma comment(lib, "ws2_32.lib")

//********************************************************************
// マクロ
//********************************************************************
#define HOST_NAME_LENGTH (256)

//********************************************************************
// プロトタイプ宣言
//********************************************************************
void ReciveData(NETWORK_DATA* pData, sockaddr_in* pSendAdr);

static int current_player_max = 0;		// プレイヤー識別番号の現在最大値
static SOCKET sockRecv;
static struct sockaddr_in sockAddrIn;
static struct sockaddr_in from_addr;
//====================================================================
// メイン処理
//====================================================================
void main(void)
{
	PHOSTENT pHostent = NULL;
	
	
	// WinSockの初期化
	WSADATA WSADData;
	WSAStartup(MAKEWORD(2, 2), &WSADData);

	// ソケット生成
	sockRecv =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	char yes = '1';
	// ブロードキャスト許可
	if(setsockopt(sockRecv, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) < 0)
	{
		printf("error");
	}

	// 送信アドレスの設定
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	sockAddrIn.sin_addr.s_addr = inet_addr("255.255.255.255");
	sockAddrIn.sin_port = htons(20002);
	sockAddrIn.sin_family = AF_INET;

	// 受信アドレスの設定
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	from_addr.sin_port = htons(20001);
	from_addr.sin_family = AF_INET;
	from_addr.sin_addr.s_addr = INADDR_ANY;
	int i = sizeof(sockAddrIn);
	// ソケットとポートの結合
	if(bind(sockRecv, (struct sockaddr *)&from_addr, sizeof(from_addr)) < 0) 
	{
		perror("bind");
		return;
	}

	while(1)
	{
		// データ受信
		NETWORK_DATA Data = {0};
		Data.my_ID = -1;

		int SockaddrInSize = sizeof(from_addr);
		int ilen = recvfrom(sockRecv,(char*)&Data,sizeof(NETWORK_DATA),0,(sockaddr*)&from_addr,&SockaddrInSize);
		if(ilen <= 0)
		{
		//	continue;
		}

		// このゲームかどうかの判断
		if(strcmp(Data.game_ID, kGameID) != 0)
		{
			continue;
		}

		ReciveData(&Data, &from_addr);
	}
	
	// 閉じる
	closesocket(sockRecv);
	
	// WinSockの終了
	WSACleanup();

	rewind(stdin);
	getchar();
}

//====================================================================================
// 受信
//====================================================================================
void ReciveData(NETWORK_DATA* pData, sockaddr_in* pSendAdr)
{
	// WinSockの初期化
	WSADATA WSADData;
	WSAStartup(MAKEWORD(2, 2), &WSADData);
	struct sockaddr_in sendAddr = *pSendAdr;
	switch(pData->data_type)
	{
		case NETWORK_DATA_TYPE_REQUEST_PLAYER_NUMBER:
			NETWORK_DATA data;
			memcpy(&data, pData, sizeof(data));
			data.data_type = NETWORK_DATA_TYPE_SEND_PLAYER_NUMBER;
			data.my_ID = current_player_max;
			if(sendto(sockRecv,(char*)&data, sizeof(data), 0, (const struct sockaddr*)&sendAddr, sizeof(sendAddr)) < 0)
			{
				int i;
				i = WSAGetLastError();
				i = i;
				printf("失敗\n");
			}
			else
			{
				current_player_max++;

				printf("受信\n");
			}
		break;

		case NETWORK_DATA_TYPE_GO_TO_RESULT:
			current_player_max = 0;
		break;

		default:
			printf("なにか受信\n");
		break;
	}
}

//-----EOF-------