//********************************************************************
// UDP�f�[�^����M�v���O����
// ���C���̏���(main.cpp)
// aughter: NAOKI NOJIRI  20236
//********************************************************************
//********************************************************************
// �C���N���[�h
//********************************************************************
#include "main.h"
#include <stdio.h>
#include <WinSock2.h>

//********************************************************************
// ���C�u�����̃����N
//********************************************************************
#pragma comment(lib, "ws2_32.lib")

//********************************************************************
// �}�N��
//********************************************************************
#define HOST_NAME_LENGTH (256)

//********************************************************************
// �v���g�^�C�v�錾
//********************************************************************
void ReciveData(NETWORK_DATA* pData, sockaddr_in* pSendAdr);

static int current_player_max = 0;		// �v���C���[���ʔԍ��̌��ݍő�l
static SOCKET sockRecv;
static struct sockaddr_in sockAddrIn;
static struct sockaddr_in from_addr;
//====================================================================
// ���C������
//====================================================================
void main(void)
{
	PHOSTENT pHostent = NULL;
	
	
	// WinSock�̏�����
	WSADATA WSADData;
	WSAStartup(MAKEWORD(2, 2), &WSADData);

	// �\�P�b�g����
	sockRecv =  socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	char yes = '1';
	// �u���[�h�L���X�g����
	if(setsockopt(sockRecv, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes)) < 0)
	{
		printf("error");
	}

	// ���M�A�h���X�̐ݒ�
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	sockAddrIn.sin_addr.s_addr = inet_addr("255.255.255.255");
	sockAddrIn.sin_port = htons(20002);
	sockAddrIn.sin_family = AF_INET;

	// ��M�A�h���X�̐ݒ�
	memset(&sockAddrIn, 0, sizeof(sockAddrIn));
	from_addr.sin_port = htons(20001);
	from_addr.sin_family = AF_INET;
	from_addr.sin_addr.s_addr = INADDR_ANY;
	int i = sizeof(sockAddrIn);
	// �\�P�b�g�ƃ|�[�g�̌���
	if(bind(sockRecv, (struct sockaddr *)&from_addr, sizeof(from_addr)) < 0) 
	{
		perror("bind");
		return;
	}

	while(1)
	{
		// �f�[�^��M
		NETWORK_DATA Data = {0};
		Data.my_ID = -1;

		int SockaddrInSize = sizeof(from_addr);
		int ilen = recvfrom(sockRecv,(char*)&Data,sizeof(NETWORK_DATA),0,(sockaddr*)&from_addr,&SockaddrInSize);
		if(ilen <= 0)
		{
		//	continue;
		}

		// ���̃Q�[�����ǂ����̔��f
		if(strcmp(Data.game_ID, kGameID) != 0)
		{
			continue;
		}

		ReciveData(&Data, &from_addr);
	}
	
	// ����
	closesocket(sockRecv);
	
	// WinSock�̏I��
	WSACleanup();

	rewind(stdin);
	getchar();
}

//====================================================================================
// ��M
//====================================================================================
void ReciveData(NETWORK_DATA* pData, sockaddr_in* pSendAdr)
{
	// WinSock�̏�����
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
				printf("���s\n");
			}
			else
			{
				current_player_max++;

				printf("��M\n");
			}
		break;

		default:
			printf("�Ȃɂ���M\n");
		break;
	}
}

//-----EOF-------