//*****************************************************************************
//
// �l�b�g���[�N�N���C�A���g�N���X [network_client.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/17(Wed)
// Version		: 1.00
// Update Date	: 2014/09/17(Wed)
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "network_client.h"
#include "thread.h"
#include "windows_sockets.h"
#include "network_data_buffer.h"
#include "common.h"

//*****************************************************************************
// �}�N����`
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
CNetworkClient::CNetworkClient(void)
{
	// �X���b�h
	m_pThread = NULL;

	// �X���b�h�̍쐬
	m_pThread = new CThread();

	// Winsock�̍쐬
	m_pWinsock = new CWindowsSockets("239.0.0.9");

	// �o�b�t�@�̍쐬
	m_pNetworkDataBuffer = new CNetworkDataBuffer();
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
	// Winsock�̏�����
	INIT(m_pWinsock);


	INIT(m_pNetworkDataBuffer);

	// �X���b�h�̏�����
	INIT(m_pThread);

	// ��M�X���b�h�̋N��
	m_pThread->Start(ReceiveThread,this);

	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CNetworkClient::Uninit(void)
{
	NETWORK_DATA SendData;

	SendData.Type = NETWORK_DATA_TYPE_END;

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
	while(pNetworkClient->m_bLoopFlag)
	{
		NETWORK_DATA Data;

		// �f�[�^�̎�M
		pNetworkClient->m_pWinsock->ReceiveData((char*)&Data);

		if(Data.Type == NETWORK_DATA_TYPE_END)
		{
			pNetworkClient->m_bLoopFlag = false;
		}
		else
		{
			// �f�[�^���i�[
			pNetworkClient->m_pNetworkDataBuffer->Push(Data);
		}
	}

	return 0;
}

//---------------------------------- EOF --------------------------------------
