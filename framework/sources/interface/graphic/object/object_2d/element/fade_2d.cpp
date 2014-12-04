//*****************************************************************************
//
// ��`2D�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/application.h"

// interface
#include "interface/interface_manager.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/vertex/vertex_2d.h"
#include "interface/graphic/object/object_2d/element/fade_2d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/texture/texture.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
// common
#include "common/common.h"

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
CFade2D::CFade2D(CDeviceHolder* device_holder,CInterfaceManager* interface_manager) : CObject2D(device_holder,OBJECT_2D_TYPE_RECTANGLE)
,alpha_(1.0f)
{
	rectangle_2d_ =new  CRectangle2D(device_holder);
	rectangle_2d_->set_size(VECTOR2(DEFAULT_SCREEN_WIDTH,DEFAULT_SCREEN_HEIGHT));
	rectangle_2d_->set_point(CRectangle2D::POINT_LEFT_UP);
	rectangle_2d_->Set();

	interface_manager_ = interface_manager;
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	rectangle_2d_key_ = object_2d_manager->AddList(rectangle_2d_);

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade2D::~CFade2D(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CFade2D::Init(void)
{
	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CFade2D::Draw(CObject2DData* object_2d_data)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	alpha_ -= 0.01f;
	rectangle_2d_->set_color(COLOR4F(1.0f,1.0f,1.0f,alpha_));
	rectangle_2d_->Set();

	object_2d_manager->Draw(rectangle_2d_key_,VECTOR2(0,0),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"field000");
}

//=============================================================================
// �I��
//=============================================================================
void CFade2D::Uninit (void)
{
	SAFE_RELEASE(rectangle_2d_);
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CFade2D::Set(void)
{
	rectangle_2d_->Set();
}


#if 0
//=============================================================================
// �ݒ菈��
//=============================================================================
void CFade2D::Set(void)
{
	switch(m_Point)
	{
		case POINT_CENTER:
		{
			m_Position[0] = VECTOR2(-m_Size.x * 0.5f,-m_Size.y * 0.5f);
			m_Position[1] = VECTOR2(-m_Size.x * 0.5f, m_Size.y * 0.5f);
			m_Position[2] = VECTOR2( m_Size.x * 0.5f,-m_Size.y * 0.5f);
			m_Position[3] = VECTOR2( m_Size.x * 0.5f, m_Size.y * 0.5f);
			break;
		}
		case POINT_LEFT_UP:
		{
			m_Position[0] = VECTOR2(    0.0f,    0.0f);
			m_Position[1] = VECTOR2(    0.0f,m_Size.y);
			m_Position[2] = VECTOR2(m_Size.x,    0.0f);
			m_Position[3] = VECTOR2(m_Size.x,m_Size.y);
			break;
		}
		case POINT_LEFT_MIDDLE:
		{
			m_Position[0] = VECTOR2(    0.0f,-m_Size.y * 0.5f);
			m_Position[1] = VECTOR2(    0.0f, m_Size.y * 0.5f);
			m_Position[2] = VECTOR2(m_Size.x,-m_Size.y * 0.5f);
			m_Position[3] = VECTOR2(m_Size.x, m_Size.y * 0.5f);
			break;
		}
		case POINT_LEFT_DOWN:
		{
			m_Position[0] = VECTOR2(    0.0f,-m_Size.y);
			m_Position[1] = VECTOR2(    0.0f,     0.0f);
			m_Position[2] = VECTOR2(m_Size.x,-m_Size.y);
			m_Position[3] = VECTOR2(m_Size.x,     0.0f);
			break;
		}
		case POINT_RIGHT_UP:
		{
			m_Position[0] = VECTOR2(-m_Size.x,    0.0f);
			m_Position[1] = VECTOR2(-m_Size.x,m_Size.y);
			m_Position[2] = VECTOR2(     0.0f,    0.0f);
			m_Position[3] = VECTOR2(     0.0f,m_Size.y);
			break;
		}
		case POINT_RIGHT_MIDDLE:
		{
			m_Position[0] = VECTOR2(-m_Size.x,-m_Size.y * 0.5f);
			m_Position[1] = VECTOR2(-m_Size.x, m_Size.y * 0.5f);
			m_Position[2] = VECTOR2(     0.0f,-m_Size.y * 0.5f);
			m_Position[3] = VECTOR2(     0.0f, m_Size.y * 0.5f);
			break;
		}
		case POINT_RIGHT_DOWN:
		{
			m_Position[0] = VECTOR2(-m_Size.x,-m_Size.y);
			m_Position[1] = VECTOR2(-m_Size.x,     0.0f);
			m_Position[2] = VECTOR2(     0.0f,-m_Size.y);
			m_Position[3] = VECTOR2(     0.0f,     0.0f);
			break;
		}
		case POINT_MIDDLE_UP:
		{
			m_Position[0] = VECTOR2(-m_Size.x * 0.5f,    0.0f);
			m_Position[1] = VECTOR2(-m_Size.x * 0.5f,m_Size.y);
			m_Position[2] = VECTOR2( m_Size.x * 0.5f,    0.0f);
			m_Position[3] = VECTOR2( m_Size.x * 0.5f,m_Size.y);
			break;
		}
		case POINT_MIDDLE_DOWN:
		{
			m_Position[0] = VECTOR2(-m_Size.x * 0.5f,-m_Size.y);
			m_Position[1] = VECTOR2(-m_Size.x * 0.5f,     0.0f);
			m_Position[2] = VECTOR2( m_Size.x * 0.5f,-m_Size.y);
			m_Position[3] = VECTOR2( m_Size.x * 0.5f,     0.0f);
			break;
		}
	}
}
#endif
//---------------------------------- EOF --------------------------------------
