//*****************************************************************************
//
// �v���C���[�N���X
//
// Author		: Chiharu Kamiyama
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

#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
const f32 CPlayer::SPEED = 0.5f;
const f32 CPlayer::SPEED_DEST = 0.3f;
const f32 CPlayer::ROTATION_DEST = 0.3f;



//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(CInterfaceManager* interface_manager)
{
	//�C���^�[�t�F�[�X�}�l�[�W���[�̕ۑ�
	interface_manager_ = interface_manager;
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
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"ship");
	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList( object_model );

	//�l������
	pos_   = VECTOR3( 0.0f, 0.0f, 0.0f );
	rot_   = VECTOR3( 0.0f, 0.0f, 0.0f );
	scale_ = VECTOR3( 1.0f, 1.0f, 1.0f );

	
	//�ړ��ڕW�l�ϐ�
	VECTOR3 pos_dest_ = VECTOR3( 0.0f, 0.0f, 0.0f );
	VECTOR3 rot_dest_ = VECTOR3( 0.0f, 0.0f, 0.0f );

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	//�J�����̊p�x�������Ă���
	f32 camera_rot_y = 0.0f;

	//�J�����̑O�x�N�g���ƉE�x�N�g�������Ă���
	VECTOR3 camera_flont_vec = VECTOR3( 0.0f, 1.0f, 0.0f );
	VECTOR3 camera_right_vec = VECTOR3( 1.0f, 0.0f, 0.0f );



	//�E�ړ�
	if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_D ) )
	{
		//�E�΂ߌ��
		if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_S ) )
		{
			//�J�����̊p�x�������Ă���
			rot_._y = camera_rot_y + MTH_PI/2;
			//�ړ�
			pos_dest_ = pos_ + ((camera_right_vec + camera_flont_vec  ) / 2) * SPEED;
		}
		//�E�΂ߑO
		else if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_W ) )
		{
			//�J�����̊p�x�������Ă���
			rot_._y = camera_rot_y + MTH_PI *3; 
			//�ړ�
			pos_dest_ = pos_ + ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;
		}
		else
		{
			//�J�����̊p�x�������Ă���
			rot_._y = camera_rot_y + MTH_PI/2; 
			//�ړ�
			pos_dest_ = pos_ + ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;

		}
	}
	//���ړ�
	if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_A ) )
	{		
		//�E�΂ߌ��
		if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_S ) )
		{
			//�J�����̊p�x�������Ă���
			rot_dest_._y = camera_rot_y - MTH_PI/4;
			//�ړ�
			pos_dest_ = pos_ + ((camera_right_vec + camera_flont_vec  ) / 2) * SPEED;
		}
		//�E�΂ߑO
		else if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_W) )
		{
			//�J�����̊p�x�������Ă���
			rot_dest_._y = camera_rot_y - MTH_PI/4 * 5; 
			//�ړ�
			pos_dest_ = pos_dest_ + ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;
		}
		else
		{
			//�J�����̊p�x�������Ă���
			rot_dest_._y = camera_rot_y - MTH_PI/2; 
			//�ړ�
			pos_dest_ = pos_ - ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;

		}
	}
	
	//���ړ�
	if(( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_W )))
	{
		pos_dest_ = pos_ - camera_flont_vec * SPEED;
		rot_dest_._y = camera_rot_y + MTH_PI;
	}

	//��O�ړ�
	if(( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_S )))
	
	{
		pos_dest_ = pos_ + camera_flont_vec * SPEED;
		rot_dest_._y = camera_rot_y;
	}


	pos_._x += ( pos_dest_._x - pos_._x ) * SPEED_DEST;
	pos_._z += ( pos_dest_._z - pos_._z ) * SPEED_DEST;

	rot_._y += ( rot_dest_._y - rot_._y ) * ROTATION_DEST;

	DEBUG_TOOL.debug_console()->Print("Player Pos  : %.1f, %.1f, %.1f\n", pos_._x, pos_._y, pos_._z);
	DEBUG_TOOL.debug_console()->Print("Player Rot  : %.1f, %.1f, %.1f\n", rot_._x, rot_._y, rot_._z);

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
	object_3d_manager->Draw(object_key_,pos_,rot_,scale_,MATRIX4x4(),"");
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
}

//---------------------------------- EOF --------------------------------------
