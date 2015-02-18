//*****************************************************************************
//
// �l�b�g���[�N�N���C�A���g�N���X [network_client.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/17(Wed)
// Version		: 1.00
// Update Date	: 2014/09/17(Wed)
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "../../basic/basic.h"
#include <winsock.h>
#include "network_data.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CThread;
class CWindowsSockets;
class CNetworkDataBuffer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNetworkClient : public CBasic
{
public:
	// �R���X�g���N�^
	CNetworkClient(void);

	// �f�X�g���N�^
	virtual ~CNetworkClient(void);

	// ����������
	bool Init(void);

	// �I������
	void Uninit(void);

	// �l�b�g���[�N�f�[�^�o�b�t�@
	CNetworkDataBuffer* GetNetworkDataBuffer(void){return m_pNetworkDataBuffer;}

	CWindowsSockets* GetWinSock(void){return m_pWinsock;};

	// �S�������������Ă邩�̃t���O�A�N�Z�T
	bool GetEndAllPlayerPrepareFlag(void){return m_bAllPlayerPrepare;};
	void SetEndAllPlayerPrepareFlag(bool flag){m_bAllPlayerPrepare = flag;};

	// �Q�[���X�^�[�g�̃t���O�A�N�Z�T
	bool GetStartGameFlag(void){return m_bStartGame;};
	void SetStartGameFlag(bool flag){m_bStartGame = flag;};

protected:

private:
	CThread*			m_pThread;
	bool volatile		m_bLoopFlag;
	CWindowsSockets*	m_pWinsock;
	CNetworkDataBuffer* m_pNetworkDataBuffer;
	static s8			m_myID;
	bool				m_bAllPlayerPrepare;
	bool				m_bStartGame;

	// ��M�X���b�h����
	static unsigned __stdcall ReceiveThread(CNetworkClient* pNetworkClient);
};

#endif	// _NETWORK_CLIENT_H_

//---------------------------------- EOF --------------------------------------
