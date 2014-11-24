//*****************************************************************************
//
// �l�b�g���[�N�f�[�^�o�b�t�@�N���X [network_data_buffer.h]
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

#ifndef _NETWORK_DATA_BUFFER_H_
#define _NETWORK_DATA_BUFFER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic.h"
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
namespace std
{
	template < class T > class allocator;
	template < class T, class Allocator > class list;
}

#define LIST_FWD(x_type)  std::list<x_type, std::allocator<x_type> >

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CNetworkDataBuffer : public CBasic
{
public:
	// �R���X�g���N�^
	CNetworkDataBuffer(void);

	// �f�X�g���N�^
	virtual ~CNetworkDataBuffer(void);

	// ����������
	bool Init(void);

	// �I������
	void Uninit(void);

	// �f�[�^�̒ǉ�
	void Push(NETWORK_DATA pData);

	// �f�[�^�̎��o��
	NETWORK_DATA Pop(void);

	// �󂩊m�F
	bool Empty(void);

	// �ύX
	void Change(void);

	void RaiseChangeFlag(void){m_bChangeFlag = true;}
	bool GetChangeFlag(void){return m_bChangeFlag;}
protected:

private:
	enum LIST_TYPE
	{
		LIST_TYPE_USE = 0,
		LIST_TYPE_CONTAINER,
		LIST_TYPE_MAX
	};
	LIST_FWD(NETWORK_DATA)* m_pList[LIST_TYPE_MAX];

	bool m_bChangeFlag;
};

#endif	// _NETWORK_DATA_BUFFER_H_

//---------------------------------- EOF --------------------------------------
