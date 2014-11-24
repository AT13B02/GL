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
#include "network_data.h"
#include <stdio.h>

#include "common.h"

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

	m_pIpAddress = new char[nLen + 1];

	// IP�A�h���X�̐ݒ�
	strcpy(m_pIpAddress,pIpAddress);
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
	CDebugConsole* pDebugConsole = CDebug::GetDebugManager()->GetDebugConsole();
	
	// WinSock�̎g�p�J�n
	if(WSAStartup(MAKEWORD(2,2),&WsaData))
	{
		pDebugConsole->Print("WindowsSockets�̃X�^�[�g�A�b�v���s\n");
		return false;
	}
	
	//�\�P�b�g�̐���
	m_Socket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);

	// �\�P�b�g�̐����̊m�F
	if(m_Socket == INVALID_SOCKET)
	{
		pDebugConsole->Print("�\�P�b�g�̐������s\n");
		return false;
	}

	// �}���`�L���X�g��M����
	int value = 1;
	setsockopt( m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&value, sizeof(value) );

	// �\�P�b�g�A�h���X�̐ݒ�
	m_Sendaddr.sin_port = htons(20000);
	m_Sendaddr.sin_family= AF_INET;
	m_Sendaddr.sin_addr.s_addr = inet_addr(m_pIpAddress);

	// ��M�A�h���X
	m_Recieveaddr.sin_port = htons(20001);
	m_Recieveaddr.sin_family= AF_INET;
	m_Recieveaddr.sin_addr.s_addr = INADDR_ANY;

	// �o�C���h
	bind(m_Socket,(sockaddr*)&m_Recieveaddr,sizeof(m_Recieveaddr));

	// �}���`�L���X�g�O���[�v�ɎQ��
	ip_mreq mreq;
	memset( &mreq, 0, sizeof(mreq) );
	mreq.imr_multiaddr.s_addr = inet_addr(m_pIpAddress);//�}���`�L���X�g�A�h���X
	mreq.imr_interface.s_addr = INADDR_ANY;
	setsockopt(m_Socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&mreq,sizeof(mreq));

	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CWindowsSockets::Uninit(void)
{
	SAFE_DELETE_ARRAY(m_pIpAddress);

	closesocket(m_Socket);
}

//=============================================================================
// �f�[�^�̑��M
//=============================================================================
void CWindowsSockets::SendData(char* pData,int nSize)
{
	sendto(m_Socket,(char*)pData,nSize,0,(struct sockaddr*)&m_Sendaddr,sizeof(sockaddr_in));
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
// �f�[�^�̑��M
//=============================================================================
void CWindowsSockets::ReceiveData(char* pOutData)
{
	int SockaddrInSize = sizeof(struct sockaddr_in);
	sockaddr_in From;

	recvfrom(m_Socket,(char*)pOutData,sizeof(NETWORK_DATA),0,(sockaddr*)&From,&SockaddrInSize);
}

//---------------------------------- EOF --------------------------------------
