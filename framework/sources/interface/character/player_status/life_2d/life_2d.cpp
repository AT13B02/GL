//*****************************************************************************
//
// ���C�t(2D)�N���X
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "life_2d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLife2D::CLife2D(CInterfaceManager* interface_manager , s32 max_life , s32 max_length )
{
	interface_manager_ = interface_manager;
	max_life_ = max_life;
	life_ = max_life;
	max_length_ = max_length;
	length_ = max_length;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLife2D::~CLife2D(void)
{
}

//=============================================================================
// ��������
//=============================================================================
void CLife2D::SetParameter(const VECTOR2& position , const s32& player_id )
{
	position_ = position;
	player_id_ = player_id;
}

//=============================================================================
// ����������
//=============================================================================
bool CLife2D::Init(void)
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	rectangle_2d_ = new CRectangle2D(interface_manager_->graphic_manager()->device_holder());
	rectangle_2d_->set_size(VECTOR2((f32)max_length_,10.0f));
	rectangle_2d_->set_color( COLOR4F( 0.0f , 1.0f , 0.0f , 1.0f ) );
	rectangle_2d_->Set();

	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_2d_manager()->AddList(rectangle_2d_);
	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CLife2D::Update(void)
{
	length_ = life_ / max_life_ * max_length_;
	rectangle_2d_->set_size( VECTOR2((f32)length_ , 10.0f ));
	rectangle_2d_->set_color( COLOR4F( 1.0f - static_cast<f32>(life_ / max_life_) , static_cast<f32>(life_ / max_life_) , 0.0f , 1.0f ) );
	rectangle_2d_->Set();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLife2D::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// �`��
	object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"snowball001");
}

//=============================================================================
// �I������
//=============================================================================
void CLife2D::Uninit( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	//HACK
	object_2d_manager->Uninit();
}
//=============================================================================
// ��������
//=============================================================================
void CLife2D::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
