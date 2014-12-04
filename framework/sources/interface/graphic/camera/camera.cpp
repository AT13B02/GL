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

	// �r���[�̐ݒ�
	SetView(VECTOR3(0.0f,0.0f,10.0f),VECTOR3(0.0f,0.0f,0.0f),VECTOR3(0.0f,1.0f,0.0f));

	// �f�t�H���g�̃p�[�X�y�N�e�B�u�̐ݒ�
	SetPerspective(60.0f,16.0f / 9.0f,1.0f,1000.0f);
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
	SetPosition(eye,look_at_);
}

//=============================================================================
// �����_�̐ݒ菈��
//=============================================================================
void CCamera::SetLookAt(const VECTOR3& look_at)
{
	SetPosition(eye_,look_at);
}

//=============================================================================
// ���_�ƒ����_�̐ݒ菈��
//=============================================================================
void CCamera::SetPosition(const VECTOR3& eye,const VECTOR3& look_at)
{
	SetView(eye,look_at,up_);
}

//=============================================================================
// ������x�N�g���̐ݒ�
//=============================================================================
void CCamera::SetUp(const VECTOR3& up)
{
	SetView(eye_,look_at_,up);
}

//=============================================================================
// ���s�ړ�
//=============================================================================
void CCamera::SetTranslation(const VECTOR3& translation)
{
	eye_ += translation;
	look_at_ += translation;
}

//=============================================================================
// ���_���璍���_�ݒ�
//=============================================================================
void CCamera::SetLookAtFromEye(const VECTOR3& eye)
{
	look_at_._x = eye._x + length_ * cosf(rotation_._x * MTH_DEGREE) * cosf(rotation_._y * MTH_DEGREE);
	look_at_._y = eye._y;// - 10.0f;// + length_ * sinf(rotation_._x);
	look_at_._z = eye._z + length_ * cosf(rotation_._x * MTH_DEGREE) * sinf(rotation_._y * MTH_DEGREE);

	SetEye(eye);
}

//=============================================================================
// ���_�̉�]�p�̐ݒ菈��
//=============================================================================
void CCamera::SetRotationEyeToLookAt(const VECTOR3& rotation)
{
	rotation_ = NormalizeRotation(rotation);

	SetLookAtFromEye(eye_);
}

//=============================================================================
// �����_�̉�]�p�̐ݒ菈��
//=============================================================================
void CCamera::SetRotationLookAtToEye(const VECTOR3& rotation)
{
}

//=============================================================================
// �p�[�X�y�N�e�B�u�̐ݒ菈��
//=============================================================================
void CCamera::SetPerspective(const f32& perspective_degree,const f32& perspective_aspect,const f32& perspective_near,const f32& perspective_far)
{
	perspective_degree_ = perspective_degree;
	perspective_aspect_ = perspective_aspect;
	perspective_near_   = perspective_near;
	perspective_far_    = perspective_far;
}

//=============================================================================
// �r���[�̐ݒ菈��
//=============================================================================
void CCamera::SetView(const VECTOR3& eye,const VECTOR3& look_at,const VECTOR3& up)
{
	eye_ = eye;
	look_at_ = look_at;
	up_ = up;

	// ���_�ƒ����_�̋��������߂�
	length_ = sqrtf(((look_at._x - eye._x) * (look_at._x - eye._x)) + 
				    ((look_at._y - eye._y) * (look_at._y - eye._y)) + 
				    ((look_at._z - eye._z) * (look_at._z - eye._z)));

	// ���_�ƒ����_�̊p�x�����߂�
	rotation_._y = atan2f(look_at._z - eye._z,look_at._x - eye._x) * MTH_RADIAN;
	rotation_._x = atan2f(look_at_._y - eye_._y,look_at_._z - eye._z) * MTH_RADIAN;
	rotation_._z = 0.0f * MTH_RADIAN;

	// ���K��
	rotation_ = NormalizeRotation(rotation_);

	// �O���x�N�g�������߂�
	front_vector_ = look_at - eye;
	front_vector_._y = 0.0f;
	front_vector_.Normalize();

	// �E�x�N�g�������߂�
	right_vector_ = front_vector_.CrossProduct(up);
}

//=============================================================================
// ���[�e�[�V�����̐��K������
//=============================================================================
VECTOR3 CCamera::NormalizeRotation(const VECTOR3& rotation)
{
	VECTOR3 out_rotation = rotation;

	if(rotation._y >= (f32)(180.0f))
	{
		out_rotation._y = -360.0f + rotation._y;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	if(rotation._y <= (f32)(-180.0f))
	{
		out_rotation._y = -360.0f + rotation._y;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	if(rotation._x >= 90.0f)
	{
		//out_rotation._y = rotation._y + 180.0f;
		out_rotation._x = 180.0f - rotation._x;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	if(rotation._x <= -90.0f)
	{
		//out_rotation._y = rotation._y - 180.0f;
		out_rotation._x = 180.0f + rotation._x;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	return out_rotation;
}

//---------------------------------- EOF --------------------------------------
