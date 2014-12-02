//*****************************************************************************
//
// ���C�g�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/application.h"

#ifdef _USING_OPENGL_
// graphic
#include "interface/graphic/light/opengl/gl_light.h"
#include "interface/graphic/device/opengl/opengl.h"

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
CGLLight::CGLLight(CDeviceHolder* device_holder) : CLight(device_holder)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGLLight::~CGLLight(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CGLLight::Init(void)
{
	return true;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CGLLight::Set(void)
{
	if(light_index_ < 0 || light_index_ >= LIGHT_MAX)
	{
		return;
	}

	s32 light_index = GL_LIGHT0 + light_index_;
	// ���C�g�L����
	glEnable(light_index);
	switch(light_type_)
	{
		// ���s����
		case TYPE_DIRECTIONAL:
			{
				VECTOR4 dir;
				dir._x = -vector_._x;
				dir._y = -vector_._y;
				dir._z = -vector_._z;
				dir._w = 0.0f;
				glLightfv(light_index, GL_POSITION, (GLfloat*)&dir);
			}
			break;
			
		// �_����
		case TYPE_POINT:
			{
				glLightfv(light_index, GL_POSITION, (GLfloat*)&position_);
				glLightf(light_index, GL_CONSTANT_ATTENUATION, att_constant_);
				glLightf(light_index, GL_LINEAR_ATTENUATION, att_linear_);
				glLightf(light_index, GL_QUADRATIC_ATTENUATION, att_quadratic_);
			}
			break;
	}

	glLightfv(light_index, GL_DIFFUSE, (GLfloat*)&diffuse_);
	glLightfv(light_index, GL_AMBIENT, (GLfloat*)&ambient_);
	glLightfv(light_index, GL_SPECULAR, (GLfloat*)&specular_);
	glLightfv(light_index, GL_EMISSION, (GLfloat*)&emissive_);
	glLightf(light_index, GL_SHININESS, spec_power_);
}

//=============================================================================
// ���C�g�̐ݒ��؂�
//=============================================================================
void CGLLight::Unset(void)
{
	// ���C�g������
	glDisable(GL_LIGHT0 + light_index_);
}

#endif // _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
