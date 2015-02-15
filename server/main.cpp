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
static const int HOST_NAME_LENGTH = 256;
static const int MAX_PLAYER_NUM = 4;

//********************************************************************
// プロトタイプ宣言
//********************************************************************
void ReciveData(NETWORK_DATA* pData, sockaddr_in* pSendAdr);

//********************************************************************
// static変数
//********************************************************************
static int current_player_max = 0;		// プレイヤー識別番号の現在最大値
static SOCKET sockRecv;
static struct sockaddr_in sockAddrIn;
static struct sockaddr_in from_addr;
static bool prepare_start[MAX_PLAYER_NUM];
//====================================================================
// メイン処理
//====================================================================
void main(void)
{
	PHOSTENT pHostent = NULL;
	
	// 準備完了フラグ初期化
	for(int index = 0; index < MAX_PLAYER_NUM; ++index)
	{
		prepare_start[index] = false;
	}

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
		{
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
				printf("受信\n");
				printf("送信No:%d\n", data.my_ID);
				current_player_max++;
			}
			break;
		}

		// 準備できた
		case NETWORK_DATA_TYPE_SEND_READY:
		{
			prepare_start[pData->my_ID] = true;
			break;
		}

		// 全員準備できたかどうか
		case NETWORK_DATA_TYPE_CHECK_END_PREPARE:
		{
			NETWORK_DATA data;
			memcpy(&data, pData, sizeof(data));

			// 準備できた人数チェック
			int end_prepare_num = 0;
			for(int player_id = 0; player_id < MAX_PLAYER_NUM; ++player_id)
			{
				if(prepare_start[player_id])
				{
					end_prepare_num++;
				}
			}

			// 全員準備完了してる
			if(end_prepare_num >= current_player_max && current_player_max > 0)
			{
				data.data_type = NETWORK_DATA_TYPE_END_PREPARE;
				if(sendto(sockRecv,(char*)&data, sizeof(data), 0, (const struct sockaddr*)&sendAddr, sizeof(sendAddr)) < 0)
				{
					int i;
					i = WSAGetLastError();
					i = i;
					printf("失敗\n");
				}
				else
				{
					//printf("準備完了！\n");
				}
			}

			// 準備完了してない
			else
			{
				data.data_type = NETWORK_DATA_TYPE_NOT_END_PREPARE;
				if(sendto(sockRecv,(char*)&data, sizeof(data), 0, (const struct sockaddr*)&sendAddr, sizeof(sendAddr)) < 0)
				{
					int i;
					i = WSAGetLastError();
					i = i;
					printf("失敗\n");
				}
				else
				{
					//printf("準備まだです\n");
				}
			}

			break;
		}

		// リザルトへ
		case NETWORK_DATA_TYPE_GO_TO_RESULT:
		{
			current_player_max = 0;
			for(int player_id = 0; player_id < MAX_PLAYER_NUM; ++player_id)
			{
				prepare_start[player_id] = false;
			}
			break;
		}

		default:
		{
			printf("なにか受信\n");
			break;
		}
	}
}

//-----EOF-------