//*****************************************************************************
//
// WindowsSockets�N���X [windows_sockets.h]
//
// Author		: ���X ���j
// Date			: 2014/05/07(Wed)
// Version		: 1.00
// Modified by	: ���X ���j
// Update date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _WINDOWS_SOCKET_H_
#define _WINDOWS_SOCKET_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "../../basic/basic.h"
#include <winsock.h>
#include "../../common/math/vector/vector3.h"
#include "network_data.h"
//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib,"wsock32.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CNetworkData;
class CNetworkDataBuffer;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CWindowsSockets : public CBasic
{
public:
	// �R���X�g���N�^
	CWindowsSockets(const char* pIpAddress);

	// �f�X�g���N�^
	virtual ~CWindowsSockets(void);

	// ����������
	bool Init(void);

	// �I������
	void Uninit(void);

	// �v���C���[ID���N�G�X�g
	void RequestID(void);

	// �o�b�t�@�̃|�C���^�Z�b�g
	void SetNetworkDataBufferPointer(CNetworkDataBuffer* buffer_pointer){m_DataBuffer = buffer_pointer;};

	// ���������𑼂̃v���C���[�ɒʒm
	void SendDataPrepare(int my_id);

	// �Q�[���J�n�ʒm�𑗂�
	void SendGameStart(void);

	// ���U���g�ɐ؂�ւ��ʒm
	void SendDataGoToResultScene(void);

	// �f�[�^�̑��M
	void SendDataCharcter(VECTOR3* position, VECTOR3* rotation, int animation_id, int hp);	// �v���C���[
	void SendDataBullet(VECTOR3* position, VECTOR3* front_vector, float speed);		// �e

	void SendDataMyself(char* pData,int nSize);

	// �f�[�^�̎�M
	int ReceiveData(NETWORK_DATA* pOutData, sockaddr_in* from_addres);

	// ���������m�F
	void CheckAllPlayerPrepare(int my_id);

	// ���S�t���O���M
	void SendDeathFlag(int my_id);

protected:

private:
	SOCKET m_Socket;
	char m_pIpAddress[256];
	struct sockaddr_in m_Sendaddr;
	struct sockaddr_in m_Recieveaddr;
	CNetworkDataBuffer* m_DataBuffer;

	// �}���`�L���X�g�A�h���X

	// ���M��A�h���X

	// ���M���̃|�[�g�ԍ�

	// ��M���̃|�[�g�ԍ�
};

#endif	// _WINDOWS_SOCKET_H_

//---------------------------------- EOF --------------------------------------
