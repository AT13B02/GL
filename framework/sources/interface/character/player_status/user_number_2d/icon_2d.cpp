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
#include "icon_2d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
const f32 CIcon2D::POLYGON_SIZE = 15.0f;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CIcon2D::CIcon2D(CInterfaceManager* interface_manager , int player_id , f32 scale )
{
	interface_manager_ = interface_manager;
	scale_ = scale;
	player_id_ = player_id;
	scale_ = scale;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CIcon2D::~CIcon2D(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CIcon2D::Init(void)
{
	// �I�u�W�F�N�g�̐���
	rectangle_2d_ = new CRectangle2D(interface_manager_->graphic_manager()->device_holder());
	rectangle_2d_->set_size(VECTOR2( POLYGON_SIZE * scale_ , POLYGON_SIZE * scale_ ));
	rectangle_2d_->set_color( COLOR4F( 1.0f , 1.0f , 1.0f , 1.0f ) );
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
void CIcon2D::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CIcon2D::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// �`��
	switch( player_id_ )
	{
	case PLAYER_ID_1P:
		position_ = VECTOR2( 100.0f , 500.0f );
		object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"1Picon");
		break;
	case PLAYER_ID_2P:
		position_ = VECTOR2( 200.0f , 500.0f );
		object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"2Picon");
		break;
	case PLAYER_ID_3P:
		position_ = VECTOR2( 300.0f , 500.0f );
		object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"3Picon");
		break;
	case PLAYER_ID_4P:
		position_ = VECTOR2( 400.0f , 500.0f );
		object_2d_manager->Draw(object_key_,position_,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"4Picon");
		break;
	}
}

//=============================================================================
// �I������
//=============================================================================
void CIcon2D::Uninit( void )
{
}

//=============================================================================
// ��������
//=============================================================================
void CIcon2D::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
