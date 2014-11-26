//*****************************************************************************
//
// OpenGL3D���_�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/application.h"

#ifdef _USING_OPENGL_
// graphic
#include "interface/graphic/vertex/opengl/gl_vertex_3d.h"
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/device/opengl/opengl.h"

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
CGLVertex3D::CGLVertex3D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number) : CVertex3D(device_holder,position_number,normal_number,color_number,texcoord_number)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGLVertex3D::~CGLVertex3D(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGLVertex3D::Draw(const MATRIX4x4& matrix)
{
	glEnable(GL_TEXTURE_2D);

	// �r���[�̐ݒ�J�n
	glMatrixMode(GL_MODELVIEW);

	// �r���[�s���ޔ�
	glPushMatrix();

	// �}�g���b�N�X�̐ݒ�
	glMultMatrixf((f32*)&matrix);

	// �|���S���`��̊J�n(�}�`�̕`��`����ݒ�)
	glBegin(GL_TRIANGLE_STRIP);

	if(use_index_)
	{
		for(int i = 0;i < index_number_;i++)
		{
			// �F�̐ݒ�
			glColor4f(vertex_3d_._color[vertex_3d_index_._color[i]]._red,vertex_3d_._color[vertex_3d_index_._color[i]]._green,vertex_3d_._color[vertex_3d_index_._color[i]]._blue,vertex_3d_._color[vertex_3d_index_._color[i]]._alpha);

			// �e�N�X�`�����W
			glTexCoord2f(vertex_3d_._texcoord[vertex_3d_index_._texcoord[i]]._x,vertex_3d_._texcoord[vertex_3d_index_._texcoord[i]]._y);

			// �@��
			glNormal3f(vertex_3d_._normal[vertex_3d_index_._normal[i]]._x,vertex_3d_._normal[vertex_3d_index_._normal[i]]._y,vertex_3d_._normal[vertex_3d_index_._normal[i]]._z);

			// ���_���W
			glVertex3f(vertex_3d_._position[vertex_3d_index_._position[i]]._x,vertex_3d_._position[vertex_3d_index_._position[i]]._y,vertex_3d_._position[vertex_3d_index_._position[i]]._z);
		}
	}
	else
	{
		for(int i = 0;i < primitive_number_ + 2;i++)
		{
			// �F�̐ݒ�
			glColor4f(vertex_3d_._color[i]._red,vertex_3d_._color[i]._green,vertex_3d_._color[i]._blue,vertex_3d_._color[i]._alpha);

			// �e�N�X�`�����W
			glTexCoord2f(vertex_3d_._texcoord[i]._x,vertex_3d_._texcoord[i]._y);

			// �@��
			glNormal3f(vertex_3d_._normal[i]._x,vertex_3d_._normal[i]._y,vertex_3d_._normal[i]._z);

			// ���_���W
			glVertex3f(vertex_3d_._position[i]._x,vertex_3d_._position[i]._y,vertex_3d_._position[i]._z);
		}
	}
	// �|���S���`��̏I��
	glEnd();

	// ���[���h�s��̔j��
	glPopMatrix();
}

//=============================================================================
// ��������
//=============================================================================
void CGLVertex3D::Unlock(void)
{

}

#endif	// _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
