//*****************************************************************************
//
// WindowsSockets���� [windows_sockets.cpp]
//
// Author		: ���X ���j
// Date			: 2014/05/07(Wed)
// Version		: 1.00
// Modified by	: ���X ���j
// Update date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "windows_sockets.h"
#include <stdio.h>
#include "network_data_buffer.h"

#include "../../common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �萔��`
//*****************************************************************************
const int PORT_NUMBER = 20000;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWindowsSockets::CWindowsSockets(const char* pIpAddress)
{
	int nLen = 0;

	nLen = strlen(pIpAddress);

	// IP�A�h���X�̐ݒ�
	strcpy(m_pIpAddress,("255.255.255.255\0"));

	m_DataBuffer = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWindowsSockets::~CWindowsSockets(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CWindowsSockets::Init(void)
{
	WSADATA WsaData;		// WindowsSocketsSocketAPI�f�[�^
	// IP�A�h���X�̐ݒ�
	strcpy(m_pIpAddress,("255.255.255.255\0"));
	
	// WinSock�̎g�p�J�n
	if(WSAStartup(MAKEWORD(2,2),&WsaData))
	{
		DEBUG_TOOL.debug_console()->Print("WindowsSockets�̃X�^�[�g�A�b�v���s\n");
		return false;
	}
	
	//�\�P�b�g�̐���
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	// �\�P�b�g�̐����̊m�F
	if(m_Socket == INVALID_SOCKET)
	{
		DEBUG_TOOL.debug_console()->Print("�\�P�b�g�̐������s\n");
		return false;
	}

	char yes = '1';
	// �u���[�h�L���X�g����
	setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(yes));

	// ���M�A�h���X�̐ݒ�
	memset(&m_Sendaddr, 0, sizeof(m_Sendaddr));
	m_Sendaddr.sin_addr.s_addr = inet_addr(m_pIpAddress);
	m_Sendaddr.sin_port = htons(20002);
	m_Sendaddr.sin_family = AF_INET;

	// ��M�A�h���X
	memset(&m_Recieveaddr, 0, sizeof(m_Recieveaddr));
	m_Recieveaddr.sin_addr.s_addr = INADDR_ANY;
	m_Recieveaddr.sin_port = htons(20002);
	m_Recieveaddr.sin_family= AF_INET;
	int len = sizeof(m_Recieveaddr);

	// �o�C���h
	if(bind(m_Socket,(struct sockaddr*)&m_Recieveaddr,len) < 0)
	{
		int i;
		i = WSAGetLastError();
		i = i;
	}

//	// �}���`�L���X�g�O���[�v�ɎQ��
//	ip_mreq mreq;
//	memset( &mreq, 0, sizeof(mreq) );
//	mreq.imr_multiaddr.s_addr = inet_addr(m_pIpAddress);//�}���`�L���X�g�A�h���X
//	mreq.imr_interface.s_addr = INADDR_ANY;
//	setsockopt(m_Socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mreq,sizeof(mreq));

	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CWindowsSockets::Uninit(void)
{
	closesocket(m_Socket);
}

//=============================================================================
// �f�[�^�̑��M
//=============================================================================
void CWindowsSockets::SendDataCharcter(VECTOR3* position, VECTOR3* rotation, int animation_id, int hp)
{
	NETWORK_DATA Data = {0};
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.my_ID = m_DataBuffer->GetID();
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

	Data.data_type = NETWORK_DATA_TYPE_HP;
	{
		Data.HP.hp = hp;
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}

	// �S�đ������ʒm���o��
	Data.data_type = NETWORK_DATA_TYPE_ALL_SEND;
	{
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}
}

//=============================================================================
// �f�[�^�̑��M
//=============================================================================
void CWindowsSockets::SendDataBullet(VECTOR3* position, VECTOR3* front_vector, float speed)
{
	NETWORK_DATA Data = {0};
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_BULLET;
	Data.my_ID = m_DataBuffer->GetID();
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

	// �S�đ������ʒm���o��
	Data.data_type = NETWORK_DATA_TYPE_ALL_SEND;
	{
		sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
	}
}


//=============================================================================
// ID�̃��N�G�X�g
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
// ���U���g�ɐ؂�ւ��ʒm
//=============================================================================
void CWindowsSockets::SendDataGoToResultScene(void)
{
	//TODO
	m_Sendaddr.sin_port = htons(20001);

	NETWORK_DATA Data = {0};
	Data.my_ID = -1;
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.data_type = NETWORK_DATA_TYPE_GO_TO_RESULT;
	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&m_Sendaddr, sizeof(m_Sendaddr));

	//TODO
	m_Sendaddr.sin_port = htons(20002);

	// �S�v���C���[�ɒʒm
	Data.my_ID = m_DataBuffer->GetID();
	sockaddr_in Send;

	Send.sin_port = m_Sendaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr.s_addr = m_Sendaddr.sin_addr.s_addr;

	Data.data_type = NETWORK_DATA_TYPE_GO_TO_RESULT;

	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
}

//=============================================================================
// ���������𑼂̃v���C���[�ɒʒm
//=============================================================================
void CWindowsSockets::SendDataPrepare(int my_id)
{
	//TODO
	m_Sendaddr.sin_port = htons(20001);

	NETWORK_DATA Data = {0};
	Data.my_ID = my_id;
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.data_type = NETWORK_DATA_TYPE_SEND_READY;
	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&m_Sendaddr, sizeof(m_Sendaddr));

	//TODO
	m_Sendaddr.sin_port = htons(20002);

	// ���̃v���C���[�ɒʒm
	Data.my_ID = my_id;
	sockaddr_in Send;

	Send.sin_port = m_Sendaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr.s_addr = m_Sendaddr.sin_addr.s_addr;

	Data.data_type = NETWORK_DATA_TYPE_SEND_READY;

	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
}

//=============================================================================
// �����������`�F�b�N
//=============================================================================
void CWindowsSockets::CheckAllPlayerPrepare(int my_id)
{
	//TODO
	m_Sendaddr.sin_port = htons(20001);

	NETWORK_DATA Data = {0};
	Data.my_ID = my_id;
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.data_type = NETWORK_DATA_TYPE_CHECK_END_PREPARE;
	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&m_Sendaddr, sizeof(m_Sendaddr));

	//TODO
	m_Sendaddr.sin_port = htons(20002);
}

//=============================================================================
// �Q�[���J�n�ʒm�𑗂�
//=============================================================================
void CWindowsSockets::SendGameStart(void)
{
	// �S�v���C���[�ɒʒm
	NETWORK_DATA Data = {0};
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_BULLET;
	Data.my_ID = m_DataBuffer->GetID();
	sockaddr_in Send;

	Send.sin_port = m_Sendaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr.s_addr = m_Sendaddr.sin_addr.s_addr;

	Data.data_type = NETWORK_DATA_TYPE_GO_TO_GAME;

	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));

	//TODO
	m_Sendaddr.sin_port = htons(20001);

	Data.data_type = NETWORK_DATA_TYPE_GO_TO_GAME;
	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&m_Sendaddr, sizeof(m_Sendaddr));

	//TODO
	m_Sendaddr.sin_port = htons(20002);
}

//=============================================================================
// �f�[�^�̑��M
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
// �f�[�^�̎�M
//=============================================================================
int CWindowsSockets::ReceiveData(NETWORK_DATA* pOutData, sockaddr_in* from_addres)
{
	struct sockaddr_in from_addr;
	int SockaddrInSize = sizeof(from_addr);

	int ilen = recvfrom(m_Socket,(char*)pOutData,sizeof(NETWORK_DATA),0,(struct sockaddr*)&from_addr,&SockaddrInSize);
	
	return ilen;
}

//=============================================================================
// ���S�t���O���M
//=============================================================================
void CWindowsSockets::SendDeathFlag(int my_id)
{
	//TODO
	m_Sendaddr.sin_port = htons(20001);

	NETWORK_DATA Data = {0};
	Data.my_ID = my_id;
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_CHARCTER;
	Data.data_type = NETWORK_DATA_TYPE_DEATH;
	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&m_Sendaddr, sizeof(m_Sendaddr));

	//TODO
	m_Sendaddr.sin_port = htons(20002);

	// �S�v���C���[�ɒʒm
	strcpy(Data.game_ID, kGameID);
	Data.my_type = MY_TYPE_BULLET;
	Data.my_ID = m_DataBuffer->GetID();
	sockaddr_in Send;

	Send.sin_port = m_Sendaddr.sin_port;
	Send.sin_family= AF_INET;
	Send.sin_addr.s_addr = m_Sendaddr.sin_addr.s_addr;

	Data.data_type = NETWORK_DATA_TYPE_RECIVE_DEATH;

	sendto(m_Socket,(char*)&Data, sizeof(Data), 0, (struct sockaddr*)&Send, sizeof(Send));
}
//---------------------------------- EOF --------------------------------------
