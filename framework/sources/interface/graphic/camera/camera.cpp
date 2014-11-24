//*****************************************************************************
//
// �J�����N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/application.h"

// graphic
#ifdef _USING_OPENGL_
#include "interface/graphic/camera/opengl/gl_camera.h"
#endif
#ifdef _USING_DIRECTX_
#include "interface/graphic/camera/directx/dx_camera.h"
#endif
#include "interface/graphic/camera/camera.h"

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
CCamera::CCamera(CDeviceHolder* device_holder)
{
	device_holder_ = device_holder;

	eye_     = VECTOR3( 0.0f, 0.0f,10.0f);
	look_at_ = VECTOR3( 0.0f, 0.0f, 0.0f);
	up_      = VECTOR3( 0.0f, 1.0f, 0.0f);

	// ���_�ƒ����_�̋��������߂�
	length_ = sqrtf(((eye_._x - look_at_._x) * (eye_._x - look_at_._x)) + 
					((eye_._y - look_at_._y) * (eye_._y - look_at_._y)) + 
					((eye_._z - look_at_._z) * (eye_._z - look_at_._z)));

	// ���_�ƒ����_�̊p�x�����߂�
	rotation_._y = atan2f(look_at_._z - eye_._z,look_at_._x - eye_._x);
	rotation_._x = atan2f(look_at_._x - eye_._y,look_at_._z - eye_._z);
	rotation_._z = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera(void)
{
}

//=============================================================================
// �쐬����
//=============================================================================
CCamera* CCamera::Create(CDeviceHolder* device_holder)
{
	CCamera* camera = NULL;

#ifdef _USING_DIRECTX_
	camera = new CDXCamera(device_holder);
#endif

#ifdef _USING_OPENGL_
	camera = new CGLCamera(device_holder);
#endif

	return camera;
}

//=============================================================================
// ����������
//=============================================================================
bool CCamera::Init(void)
{
	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
}

//=============================================================================
// ���_�̐ݒ菈��
//=============================================================================
void CCamera::SetEye(const VECTOR3& eye)
{
	eye_ = eye;

	// ���_�ƒ����_�̋��������߂�
	length_ = sqrtf(((eye_._x - look_at_._x) * (eye_._x - look_at_._x)) + 
				    ((eye_._y - look_at_._y) * (eye_._y - look_at_._y)) + 
				    ((eye_._z - look_at_._z) * (eye_._z - look_at_._z)));

	// ���_�ƒ����_�̊p�x�����߂�
	rotation_._y = atan2f(look_at_._z - eye_._z,look_at_._x - eye_._x);
	rotation_._x = atan2f(look_at_._x - eye_._y,look_at_._z - eye_._z);
	rotation_._z = 0.0f;
}

//=============================================================================
// �����_�̐ݒ菈��
//=============================================================================
void CCamera::SetLookAt(const VECTOR3& look_at)
{
	look_at_ = look_at;

	// ���_�ƒ����_�̋��������߂�
	length_ = sqrtf(((eye_._x - look_at_._x) * (eye_._x - look_at_._x)) + 
				    ((eye_._y - look_at_._y) * (eye_._y - look_at_._y)) + 
				    ((eye_._z - look_at_._z) * (eye_._z - look_at_._z)));

	// ���_�ƒ����_�̊p�x�����߂�
	rotation_._y = atan2f(look_at_._z - eye_._z,look_at_._x - eye_._x);
	rotation_._x = atan2f(look_at_._x - eye_._y,look_at_._z - eye_._z);
	rotation_._z = 0.0f;
}

//=============================================================================
// ���_�����]�p�̐ݒ菈��
//=============================================================================
void CCamera::SetRotationEye(const VECTOR3& rotation)
{
	rotation_ = rotation;
}

//=============================================================================
// �����_�����]�p�̐ݒ菈��
//=============================================================================
void CCamera::SetRotationLookAt(const VECTOR3& rotation)
{
}

//=============================================================================
// �p�[�X�y�N�e�B�u�̐ݒ菈��
//=============================================================================
void CCamera::SetPerspective(const f32& perspective_degree,const f32& perspective_aspect,const f32& perspective_near,const f32& perspective_far)
{
	perspective_degree_ = perspective_degree;
	perspective_aspect_ = perspective_aspect;
	perspective_near_ = perspective_near;
	perspective_far_ = perspective_far;
}

//=============================================================================
// ���[�e�[�V�����̐��K������
//=============================================================================
VECTOR3 CCamera::NormalizeRotation(const VECTOR3& rotation)
{
	VECTOR3 out_rotation;

	if(rotation._y > (f32)(180.0f * MTH_DEGREE))
	{
		out_rotation._y = 2 * MTH_PI - rotation._y;
	}

	if(rotation._y < (f32)(-180.0f * MTH_DEGREE))
	{
		out_rotation._y = 2 * -MTH_PI + rotation._y;
	}

	return out_rotation;
}

//---------------------------------- EOF --------------------------------------
