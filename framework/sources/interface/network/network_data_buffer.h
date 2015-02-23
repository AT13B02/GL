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
#include "../../basic/basic.h"
#include "network_data.h"
#include "../../common/math/vector/vector3.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
static const int kMaxPlayer = 4;
static const int kMaxHP = 100;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	char from_addr[16];
}FROM_ADDERS;

typedef struct
{
	bool end_push_flag;
	int player_id;
	int animation_id;
	VECTOR3 position;
	VECTOR3 rotation;
	int hp;
}CHARCTER_INFO;

typedef struct
{
	bool end_push_flag;
	int player_id;
	float speed;
	VECTOR3 position;
	VECTOR3 front_vector;
}BULLET_INFO;

typedef struct
{
	bool recive_position;
	bool recive_rotation;
	bool recive_animation_ID;
	bool recive_speed;
	bool recive_frontvector;
	bool recive_hp;
}RECIVE_STATE;

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************


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
	void Push(NETWORK_DATA* pData);

	// ID���Z�b�g**�v���C���[��e�͌Ăяo���Ȃ�***
	void SetID(int player_id);

	// ID���Q�b�g
	int GetID(void){return m_MyID;};

	// �L�����N�^�[���o�b�t�@�擾
	CHARCTER_INFO* GetCharcterInfoBuffer(void);

	// �e���o�b�t�@�擾
	BULLET_INFO* GetBulletInfoBuffer(void);

	// �Q�[���V�[���I���t���O���Z�b�g
	void SetGameSceneEndFlag(bool flag){m_GameSceneEnd = flag;};
	// �Q�[���V�[���I���t���O���Q�b�g
	bool GetGameSceneEndFlag(void){return m_GameSceneEnd;};

	// ���S����ɕύX
	void ChangeDeath(int player_id){m_DeathFlag[player_id] = true;};

	// ���S�t���O�Q�b�g
	bool GetCharDeathFlag(int player_id){return m_DeathFlag[player_id];};

	// �t���O������
	void InitFlag(void);

protected:
	// �L�����f�[�^�̒ǉ�
	void PushCharcter(NETWORK_DATA* pData);

	// �e�f�[�^�̒ǉ�
	void PushBullet(NETWORK_DATA* pData);

private:
	char m_InitAddres[16];
	CHARCTER_INFO m_CharcterInfoBuffer[kMaxPlayer];
	BULLET_INFO m_BulletInfoBuffer[kMaxPlayer];
	int m_MyID;
	RECIVE_STATE m_ReciveState[kMaxPlayer];
	RECIVE_STATE m_ReciveStateBullet[kMaxPlayer];
	bool m_GameSceneEnd;
	bool m_DeathFlag[kMaxPlayer];
};

#endif	// _NETWORK_DATA_BUFFER_H_

//---------------------------------- EOF --------------------------------------
