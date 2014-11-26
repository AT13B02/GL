//*****************************************************************************
//
// OpenGL�J�����N���X
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
#include "interface/graphic/device/opengl/opengl.h"
#include "interface/graphic/camera/opengl/gl_camera.h"
#include "interface/graphic/device/device_holder.h"

// common
#include "common/math/math.h"
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
CGLCamera::CGLCamera(CDeviceHolder* device_holder) : CCamera(device_holder)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGLCamera::~CGLCamera(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CGLCamera::Init(void)
{
	return true;
}

//=============================================================================
// �I������
//=============================================================================
void CGLCamera::Uninit(void)
{

}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CGLCamera::Set(void)
{
	// ���C�g�̃I�t
	glDisable(GL_LIGHTING);

	// �v���W�F�N�V�����s��̐ݒ�J�n
	glMatrixMode(GL_PROJECTION);

	// �P�ʍs��̐ݒ�
	glLoadIdentity();

	// �v���W�F�N�V�����s��̐���
	projection_matrix_.SetPerspectiveFovRH(60.0f,(f32)DEFAULT_SCREEN_WIDTH / (f32)DEFAULT_SCREEN_HEIGHT,1.0f,100.0f);

	// �v���W�F�N�V�����s��̐ݒ�
	//gluPerspective(60.0,(double)DEFAULT_SCREEN_WIDTH / (double)DEFAULT_SCREEN_HEIGHT,1.0,100.0);

	// �v���W�F�N�V�����s��̐ݒ�
	glMultMatrixf((f32*)&projection_matrix_);

	// �r���[�̐ݒ�J�n(�J����)
	glMatrixMode(GL_MODELVIEW);

	// �P�ʍs��̐ݒ�
	glLoadIdentity();

	// �r���[�s��̍쐬
	view_matrix_.SetLookAtRH(eye_,look_at_,up_);

	// �r���[�s��̐ݒ�
	glMultMatrixf((f32*)&view_matrix_);

	// �r���[�s��̐ݒ�
	//gluLookAt((double)eye_._x,(double)eye_._y,(double)eye_._z,look_at_._x,look_at_._y,look_at_._z,up_._x,up_._y,up_._z);

	// �J�����̍s����擾
	//glGetFloatv(GL_MODELVIEW_MATRIX,(f32*)&m_CameraMatrix);

	// 
	DEBUG_TOOL.debug_console()->Print("���_(%.1f,%.1f,%.1f)\n",eye_._x,eye_._y,eye_._z);
	DEBUG_TOOL.debug_console()->Print("�����_(%.1f,%.1f,%.1f)\n",look_at_._x,look_at_._y,look_at_._z);

	// �J�����̋t�s����擾
	inverse_matrix_ = view_matrix_.GetInverse();
}

#endif

//---------------------------------- EOF --------------------------------------
