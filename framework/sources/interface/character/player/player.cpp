//*****************************************************************************
//
// �v���C���[�N���X
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "player.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/input/input_manager.h"

#include "../character_manager.h"
#include "../bullet/bullet_manager.h"
#include "../bullet/bullet.h"

//network
#include "../../network/network_manager.h"
#include "../../network/network_client.h"
#include "../../network/network_data_buffer.h"
#include "../../network/windows_sockets.h"

#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const f32 CPlayer::SPEED = 0.5f;
const f32 CPlayer::SPEED_DEST = 0.3f;
const f32 CPlayer::ROTATION_DEST = 0.3f;
const f32 CPlayer::BULLET_LAUNCH_HEIGHT_OFFSET = 20.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(CInterfaceManager* interface_manager)
{
	
	//�C���^�[�t�F�[�X�}�l�[�W���[�̕ۑ�
	interface_manager_ = interface_manager;

	death_flag_ = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CPlayer::Init(void)
{
	// �I�u�W�F�N�g���f���̐���
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	
	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);

	//�l������
	position_ = VECTOR3(0.0f,0.0f,0.0f);
	rotation_ = VECTOR3(0.0f,0.0f,0.0f);
	scale_    = VECTOR3(1.0f,1.0f,1.0f);

	
	//�ړ��ڕW�l�ϐ�
	VECTOR3 pos_dest_ = VECTOR3(0.0f,0.0f,0.0f );
	VECTOR3 rot_dest_ = VECTOR3(0.0f,0.0f,0.0f );

	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->RequestID();
	//�X�V���Ȃ�
	update_ = false;

	//interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->RequestID();
	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{

	VECTOR3 front_vector = front_vector_;
	VECTOR3 right_vector = right_vector_;
	VECTOR3 center_vector = front_vector + right_vector;

	front_vector._y = 0.0f;
	front_vector.Normalize();

	right_vector._y = 0.0f;
	right_vector.Normalize();

	// �ړ��x�N�g����O���x�N�g���ɐݒ�
	move_vector_ = front_vector;

	// ����ړ�
	if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		move_vector_ = (front_vector - right_vector).Normalize();
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 45.0f;
	}
	// �E��ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		move_vector_ = (front_vector + right_vector).Normalize();
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 135.0f;
	}
	// �����ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		move_vector_ = (-front_vector - right_vector).Normalize();
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 45.0f;
	}
	// �E���ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		move_vector_ = (-front_vector + right_vector).Normalize();
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 135.0f;
	}
	// �E�ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		move_vector_ = right_vector;
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 180.0f;
	}
	// ���ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		move_vector_ = -right_vector;
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN;
	}
	// ���ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W))
	{
		move_vector_ = front_vector;
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 90.0f;
	}
	// ��O�ړ�
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S))
	{
		move_vector_ = -front_vector;
		rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 90.0f;
	}
	else
	{
		// �ړ����ĂȂ�
		move_vector_._x = 0.0f;
		move_vector_._y = 0.0f;
		move_vector_._z = 0.0f;
	}
	
	// �ړ��ʉ��Z
	position_ += move_vector_ * SPEED;

	rotation_dest_._y = GetRotationNormalize(rotation_dest_._y);

	f32 def = rotation_dest_._y - rotation_._y;

	def = GetRotationNormalize(def);
	rotation_._y += def * 0.1f;	// ������

	rotation_._y = GetRotationNormalize(rotation_._y);

	// �e�̔���
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_SPACE))
	{
		VECTOR3 crate_position = position_;
		crate_position._y += BULLET_LAUNCH_HEIGHT_OFFSET;
		VECTOR3 launch_vector(front_vector_);
		const f32 LAUNCH_OFFSET_Y = 0.34f;
		launch_vector._y += LAUNCH_OFFSET_Y;
		launch_vector = launch_vector.RotationAxis(VECTOR3(0.0f, 1.0f, 0.0f), -(rotation_._y + 180.0f) * MTH_DEGREE);
		launch_vector.Normalize();
		interface_manager_
			->network_manager()
			->GetNetworkClient()
			->GetWinSock()
			->SendDataBullet(&crate_position
							,&launch_vector
							,1.0f);
	}

	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDataCharcter(&position_,&rotation_,0);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// �`��
	object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"yukidaruma");
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
}

//=============================================================================
// �v���C���[�ړ������擾
//=============================================================================
const VECTOR3& CPlayer::get_move_vector()
{
	return move_vector_;
}

//=============================================================================
// �v���C���[�ړ��X�s�[�h�擾
//=============================================================================
const f32 CPlayer::get_move_speed()
{
	return SPEED;
}

//---------------------------------- EOF --------------------------------------

//=============================================================================
// id�̎擾
//=============================================================================
int CPlayer::player_id(void)
{
	//�l�b�g���[�N�o�b�t�@�̎擾
	CHARCTER_INFO *net_chara_buf = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetCharcterInfoBuffer();
	return net_chara_buf->player_id;
}
//---------------------------------- EOF --------------------------------------
