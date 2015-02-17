//*****************************************************************************
//
// �l�b�g���[�N�f�[�^�N���X [network_data.h]
//
// Author		: KENJI KABUTOMORI
//				  NAOKI NOJIRI
// Date			: 2014/09/17(Wed)
// Version		: 1.01
// Update Date	: 2014/12/01(Mon)
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _NETWORK_DATA_H_
#define _NETWORK_DATA_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "../../basic/basic.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
static const char* kGameID = "class_B_2";		// �Q�[��(��)���ʎq

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	short Type;
}NETWORK_DATA_EVENT;

typedef struct
{
	float x, y, z;
}NETWORK_DATA_POSITION;

typedef struct
{
	float x, y, z;
}NETWORK_DATA_ROTATION;

typedef struct
{
	float speed;
}NETWORK_DATA_SPEED;

typedef struct
{
	float x, y, z;
}NETWORK_DATA_FRONT_VECTOR;

typedef struct
{
	int animation_ID;
}NETWORK_DATA_ANIMATION_ID;

// ���M�������
typedef enum NETWORK_DATA_TYPE
{
	NETWORK_DATA_TYPE_EVENT					= 0,
	NETWORK_DATA_TYPE_REQUEST_PLAYER_NUMBER	= 1,	// ID�ق���
	NETWORK_DATA_TYPE_POSITION				= 2,	// pos�ł�
	NETWORK_DATA_TYPE_ROTATION				= 3,	// rot�ł�
	NETWORK_DATA_TYPE_SPEED					= 4,	// spd�ł�
	NETWORK_DATA_TYPE_FRONT_VECTOR			= 5,	// frontVec�ł�
	NETWORK_DATA_TYPE_ANIMATION_ID			= 6,	// �A�j���[�V�����ԍ��ł�
	NETWORK_DATA_TYPE_ALL_SEND				= 7,	// �S������܂���
	NETWORK_DATA_TYPE_SEND_PLAYER_NUMBER	= 8,	// ID����܂�
	NETWORK_DATA_TYPE_GO_TO_RESULT			= 9,	// ���U���g��
	NETWORK_DATA_TYPE_SEND_READY			= 10,	// �����������܂���(����)
	NETWORK_DATA_TYPE_CHECK_END_PREPARE		= 11,	// �S�����������������̊m�F
	NETWORK_DATA_TYPE_END_PREPARE			= 12,	// �S����������
	NETWORK_DATA_TYPE_NOT_END_PREPARE		= 13,	// �܂������������ĂȂ�
	NETWORK_DATA_TYPE_GO_TO_GAME			= 14,	// �Q�[���J�n
	NETWORK_DATA_TYPE_DEATH					= 15,	// ���ꂽ
	NETWORK_DATA_TYPE_END_GAME				= 16,	// �Q�[���I���ʒm
	NETWORK_DATA_TYPE_RECIVE_DEATH			= 17,	// �f�X�t���O��M
	NETWORK_DATA_TYPE_END					= 18,
};

// ���g�͉���
typedef enum NETWORK_MY_TYPE
{
	MY_TYPE_CHARCTER = 0,
	MY_TYPE_BULLET,
	MY_TYPE_EFFECT,
	MY_TYPE_MAX
};

typedef struct
{
	char				game_ID[16];// �ǎ���ID
	NETWORK_MY_TYPE		my_type;	// �����̃^�C�v�i����������킷�j
	int					my_ID;		// �v���C���[ID
	NETWORK_DATA_TYPE	data_type;	// ���̏��

	union
	{
		NETWORK_DATA_EVENT			event;
		NETWORK_DATA_POSITION		position;
		NETWORK_DATA_ROTATION		rotation;
		NETWORK_DATA_SPEED			speed;
		NETWORK_DATA_FRONT_VECTOR	front_vector;
		NETWORK_DATA_ANIMATION_ID	animation_ID;
	};
}NETWORK_DATA;

#endif	// _NETWORK_DATA_H_

//---------------------------------- EOF --------------------------------------
