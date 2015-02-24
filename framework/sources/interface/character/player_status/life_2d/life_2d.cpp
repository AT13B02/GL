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
#include "../user_number_2d/icon_2d.h"
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
CLife2D::CLife2D(CInterfaceManager* interface_manager , s32 max_life , s32 max_length , int player_id )
{
	interface_manager_ = interface_manager;
	max_life_ = max_life;
	life_ = max_life;
	max_length_ = max_length;
	length_ = max_length;
	player_id_ = player_id;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLife2D::~CLife2D(void)
{
}
//=============================================================================
// ����������
//=============================================================================
bool CLife2D::Init(void)
{
	// �I�u�W�F�N�g�̐���
	rectangle_2d_ = new CRectangle2D(interface_manager_->graphic_manager()->device_holder());
	rectangle_2d_->set_size(VECTOR2((f32)max_length_,10.0f));
	rectangle_2d_->set_color( COLOR4F( 0.0f , 1.0f , 0.0f , 1.0f ) );
	rectangle_2d_->set_point(CRectangle2D::POINT_CENTER);
	rectangle_2d_->set_texcoord( 0.0f , 1.0f , 0.0f , 1.0f );
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
	if( life_ < 0 )
	{
		life_ = 0;
	}
	length_ = static_cast<s32>(( static_cast<f32>(life_) / max_life_ ) * max_length_);
	rectangle_2d_->set_size( VECTOR2((f32)length_ , 10.0f ));
	rectangle_2d_->set_color( COLOR4F( 1.0f - (static_cast<f32>(life_) / max_life_) , (static_cast<f32>(life_) / max_life_) , 0.0f , 1.0f ) );
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
	switch( player_id_ )
	{
	case PLAYER_ID_1P:
		position_ = VECTOR2( 100.0f , 550.0f );
		break;
	case PLAYER_ID_2P:
		position_ = VECTOR2( 150.0f , 550.0f );
		break;
	case PLAYER_ID_3P:
		position_ = VECTOR2( 200.0f , 550.0f );
		break;
	case PLAYER_ID_4P:
		position_ = VECTOR2( 250.0f , 550.0f );
		break;
	}

	object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"gage");
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
