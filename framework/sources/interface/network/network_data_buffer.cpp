//*****************************************************************************
//
// �l�b�g���[�N�}�l�[�W���[�N���X [network_data_buffer.cpp]
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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CNetworkDataBuffer::CNetworkDataBuffer(void)
{
	for(int i = 0; i < kMaxPlayer; ++i)
	{
		m_ReciveState[i].recive_animation_ID = false;
		m_ReciveState[i].recive_frontvector = false;
		m_ReciveState[i].recive_position = false;
		m_ReciveState[i].recive_rotation = false;
		m_ReciveState[i].recive_speed = false;
	}
	m_GameSceneEnd = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CNetworkDataBuffer::~CNetworkDataBuffer(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CNetworkDataBuffer::Init(void)
{
	for(int i = 0; i < kMaxPlayer; ++i)
	{
		m_CharcterInfoBuffer[i].animation_id = 0;
		m_CharcterInfoBuffer[i].player_id = 0;
		m_CharcterInfoBuffer[i].position = VECTOR3(0.f, 0.f, 0.f);
		m_CharcterInfoBuffer[i].rotation = VECTOR3(0.f, 0.f, 0.f);
		m_CharcterInfoBuffer[i].end_push_flag = false;

		m_BulletInfoBuffer[i].position = VECTOR3(0.f, 0.f, 0.f);
		m_BulletInfoBuffer[i].front_vector = VECTOR3(0.f, 0.f, 0.f);
		m_BulletInfoBuffer[i].player_id = -1;
		m_BulletInfoBuffer[i].speed = 0.f;
		m_BulletInfoBuffer[i].end_push_flag = false;
	}
	ZeroMemory(&m_InitAddres, sizeof(m_InitAddres));
	m_MyID = -1;
	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CNetworkDataBuffer::Uninit(void)
{
}

//=============================================================================
// �f�[�^�̊i�[
//=============================================================================
void CNetworkDataBuffer::Push(NETWORK_DATA* Data)
{
	if(Data->my_type == MY_TYPE_CHARCTER)
	{
		PushCharcter(Data);
	}

	else if(Data->my_type == MY_TYPE_BULLET)
	{
		PushBullet(Data);
	}
}

//=============================================================================
// �L�����f�[�^�̒ǉ�
//=============================================================================
void CNetworkDataBuffer::PushCharcter(NETWORK_DATA* pData)
{
	if(pData->my_ID < 0 || pData->my_ID >= kMaxPlayer)
	{
		return;
	}

	switch(pData->data_type)
	{
		case NETWORK_DATA_TYPE_POSITION:
			//m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].position._x = pData->position.x;
			m_CharcterInfoBuffer[pData->my_ID].position._y = pData->position.y;
			m_CharcterInfoBuffer[pData->my_ID].position._z = pData->position.z;

			m_ReciveState[pData->my_ID].recive_position = true;
		break;

		case NETWORK_DATA_TYPE_ROTATION:
			//m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].rotation._x = pData->rotation.x;
			m_CharcterInfoBuffer[pData->my_ID].rotation._y = pData->rotation.y;
			m_CharcterInfoBuffer[pData->my_ID].rotation._z = pData->rotation.z;

			m_ReciveState[pData->my_ID].recive_rotation = true;
		break;

		case NETWORK_DATA_TYPE_ANIMATION_ID:
			//m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].animation_id = pData->animation_ID.animation_ID;

			m_ReciveState[pData->my_ID].recive_animation_ID = true;
		break;

		case NETWORK_DATA_TYPE_ALL_SEND:
			//m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].player_id = pData->my_ID;

			// �����Ƌl�܂��Ă�Ȃ�
			if(m_ReciveState[pData->my_ID].recive_animation_ID == true
				&& m_ReciveState[pData->my_ID].recive_position == true
				&& m_ReciveState[pData->my_ID].recive_rotation == true)
			{
				m_CharcterInfoBuffer[pData->my_ID].end_push_flag = true;
			}

			// �t���O���Ƃ�
			m_ReciveState[pData->my_ID].recive_animation_ID = false;
			m_ReciveState[pData->my_ID].recive_position = false;
			m_ReciveState[pData->my_ID].recive_rotation = false;
		break;

		default:
		break;
	}
}

//=============================================================================
// �e�f�[�^�̒ǉ�
//=============================================================================
void CNetworkDataBuffer::PushBullet(NETWORK_DATA* pData)
{
	if(pData->my_ID < 0 || pData->my_ID >= kMaxPlayer)
	{
		return;
	}

	switch(pData->data_type)
	{
		case NETWORK_DATA_TYPE_POSITION:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_BulletInfoBuffer[pData->my_ID].position._x = pData->position.x;
			m_BulletInfoBuffer[pData->my_ID].position._y = pData->position.y;
			m_BulletInfoBuffer[pData->my_ID].position._z = pData->position.z;

			m_ReciveState[pData->my_ID].recive_position = true;
		break;

		case NETWORK_DATA_TYPE_FRONT_VECTOR:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_BulletInfoBuffer[pData->my_ID].front_vector._x = pData->front_vector.x;
			m_BulletInfoBuffer[pData->my_ID].front_vector._y = pData->front_vector.y;
			m_BulletInfoBuffer[pData->my_ID].front_vector._z = pData->front_vector.z;

			m_ReciveState[pData->my_ID].recive_rotation = true;
		break;

		case NETWORK_DATA_TYPE_SPEED:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_BulletInfoBuffer[pData->my_ID].speed = pData->speed.speed;

			m_ReciveState[pData->my_ID].recive_speed = true;
		break;

		case NETWORK_DATA_TYPE_ALL_SEND:
			m_CharcterInfoBuffer[pData->my_ID].end_push_flag = false;
			m_CharcterInfoBuffer[pData->my_ID].player_id = pData->my_ID;

			// �����Ƌl�܂��Ă�Ȃ�
			if(m_ReciveState[pData->my_ID].recive_speed == true
				&& m_ReciveState[pData->my_ID].recive_position == true
				&& m_ReciveState[pData->my_ID].recive_rotation == true)
			{
				m_CharcterInfoBuffer[pData->my_ID].end_push_flag = true;
			}

			// �t���O���Ƃ�
			m_ReciveState[pData->my_ID].recive_speed = false;
			m_ReciveState[pData->my_ID].recive_position = false;
			m_ReciveState[pData->my_ID].recive_rotation = false;
		break;

		default:
		break;
	}
}

//=============================================================================
// ID���Z�b�g
//=============================================================================
void CNetworkDataBuffer::SetID(NETWORK_DATA* pData)
{
	m_MyID = pData->my_ID;
}

//=============================================================================
// �L�����N�^�[���o�b�t�@�擾
//=============================================================================
CHARCTER_INFO* CNetworkDataBuffer::GetCharcterInfoBuffer(void)
{
	return &m_CharcterInfoBuffer[0];
};

//=============================================================================
// �e���o�b�t�@�擾
//=============================================================================
BULLET_INFO* CNetworkDataBuffer::GetBulletInfoBuffer(void)
{
	return &m_BulletInfoBuffer[0];
};

//---------------------------------- EOF --------------------------------------
