//*****************************************************************************
//
// �l�b�g���[�N�N���C�A���g�N���X [network_client.cpp]
//
// Author		: KENJI KABUTOMORI
//				  NAOKI NOJIRI
// Date			: 2014/09/17(Wed)
// Version		: 1.01
// Update Date	: 2014/12/01(Mon)
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "network_client.h"
#include "../../common/thread/thread.h"
#include "windows_sockets.h"
#include "network_data_buffer.h"
#include "../../common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �X�^�e�B�b�N�����o�ϐ�
//*****************************************************************************
int CNetworkClient::m_myID = -1;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNetworkClient::CNetworkClient(void)
{
	// �X���b�h
	m_pThread = NULL;

	m_bLoopFlag = true;
	m_myID = -1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNetworkClient::~CNetworkClient(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CNetworkClient::Init(void)
{
	// Winsock�̍쐬
	m_pWinsock = new CWindowsSockets("255.255.255.255");
	// Winsock�̏�����
	INIT(m_pWinsock);

	// �o�b�t�@�̍쐬
	m_pNetworkDataBuffer = new CNetworkDataBuffer;
	//INIT(m_pNetworkDataBuffer);
	m_pNetworkDataBuffer->Init();

	// �X���b�h�̍쐬
	m_pThread = new CThread;
	// �X���b�h�̏�����
	INIT(m_pThread);

	// ��M�X���b�h�̋N��
	m_pThread->Start(ReceiveThread,this);

	// �o�b�t�@�|�C���^�Z�b�g
	m_pWinsock->SetNetworkDataBufferPointer(m_pNetworkDataBuffer);
	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CNetworkClient::Uninit(void)
{
	NETWORK_DATA SendData = {0};

	SendData.data_type = NETWORK_DATA_TYPE_END;
	SendData.my_ID = m_myID;
	strcpy(SendData.game_ID, kGameID);

	// �����Ƀf�[�^�𑗐M���A��M���I��������
	m_pWinsock->SendDataMyself((char*)&SendData,sizeof(NETWORK_DATA));

	// �X���b�h�̊J��
	SAFE_RELEASE(m_pThread);

	// Winsock�̊J��
	SAFE_RELEASE(m_pWinsock);

	// �l�b�g���[�N�f�[�^�o�b�t�@�̊J��
	SAFE_RELEASE(m_pNetworkDataBuffer);
}

//=============================================================================
// ��M�X���b�h
//=============================================================================
unsigned __stdcall CNetworkClient::ReceiveThread(CNetworkClient* pNetworkClient)
{
	char addres[16] = {"\0"};
	sockaddr_in from_adders;
	while(pNetworkClient->m_bLoopFlag)
	{
		NETWORK_DATA Data = {0};
		Data.my_ID = -1;
		
		// �f�[�^�̎�M
		int ilen = pNetworkClient->m_pWinsock->ReceiveData(&Data, &from_adders);

		if(ilen <= 0)
		{
			//continue;
		}

		// ���̃Q�[�����ǂ����̔��f
		if(strcmp(Data.game_ID, kGameID) != 0)
		{
			continue;
		}

		// �l�b�g���[�N�I���Ȃ�
		if(Data.data_type == NETWORK_DATA_TYPE_END && m_myID == Data.my_ID)
		{
			pNetworkClient->m_bLoopFlag = false;
		}
		// �h�c�Z�b�g
		if(Data.data_type == NETWORK_DATA_TYPE_SEND_PLAYER_NUMBER && m_myID < 0)
		{
			pNetworkClient->m_pNetworkDataBuffer->SetID(Data.my_ID);
			m_myID = Data.my_ID;
//			CDebugManager &p = DEBUG_TOOL;
//			p.debug_console()->Print("��MMY_ID = %d\n", m_myID);
		}
		// ���U���g�֍s���Ȃ�
		else if(Data.data_type == NETWORK_DATA_TYPE_GO_TO_RESULT)
		{
			pNetworkClient->m_pNetworkDataBuffer->SetGameSceneEndFlag(true);
		}
		else
		{
			// �f�[�^���i�[
			pNetworkClient->m_pNetworkDataBuffer->Push(&Data);
		}
	}


	return 0;
}

//---------------------------------- EOF --------------------------------------
