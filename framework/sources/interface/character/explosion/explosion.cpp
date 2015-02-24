//*****************************************************************************
//
// �o���b�g�N���X
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "explosion.h"
//billboard
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const f32 CExplosion::DEFAULT_RADIUS = 20.0f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion(void)
{
}

//=============================================================================
// ��������
//=============================================================================
void CExplosion::SetParameter(const VECTOR3& position, const s16 u_division_num, const s16 v_division_num, const s16 animation_change_count)
{
	position_ = position;
	u_division_num_ = u_division_num;
	v_division_num_ = v_division_num;
	animation_change_count_ = animation_change_count;
}

//=============================================================================
// ����������
//=============================================================================
bool CExplosion::Init(void)
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	billboard_ = new CBillboard(interface_manager_->graphic_manager()->device_holder());
	billboard_->set_size(VECTOR2(50.0f,50.0f));

	//�e�N�X�`���ݒ�
	left_   = 0.0f;
	right_  = 1.0f / u_division_num_;
	top_    = 0.0f;
	bottom_ = 1.0f / v_division_num_;

	billboard_->set_texcoord( left_, right_, top_, bottom_ );

	//�Z�b�g
	billboard_->Set();

	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(billboard_);
	radius_ = DEFAULT_RADIUS;

	animation_count_ = 0;
	u_division_count = 0;
	v_division_count = 0;

	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	//�A�j���[�V�����ύX�J�E���g�ɂȂ�����e�N�X�`���ύX??
	if( animation_count_ % animation_change_count_ == 0 )
	{
 		u_division_count++;

		if( ( u_division_count >= u_division_num_ ) && ( v_division_count < v_division_num_ ) )
		{
			u_division_count = 0;
			v_division_count++;

			left_ = 0.0f;
			right_ = 1.0f / u_division_num_;

			top_ = bottom_;
			bottom_ = bottom_ + ( 1.0f / v_division_num_ );
		}
		else if(( u_division_count >= u_division_num_ ) &&( v_division_count >= v_division_num_ ))
		{
			Erase();
		}
		else
		{
			left_ = right_;
			right_ = right_ + ( 1.0f / u_division_num_ );

		}

		billboard_->set_texcoord( left_, right_, top_,  bottom_);
		billboard_->Set();

	}

	//�J�E���g����
	animation_change_count_++;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// �`��
	object_3d_manager->Draw(object_key_,position_,VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"explosion");
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit( void )
{


}
//=============================================================================
// �e��������
//=============================================================================
void CExplosion::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
