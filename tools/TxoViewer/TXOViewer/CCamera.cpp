//=============================================================================
//
// �J�������� [CCamera.cpp]
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CCamera.h"
#include "main.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************
#ifdef ASPECT16_9	// �A�X�y�N�g��16:9
const float CAMERA_PARAM::DEFAULT_ASPECT_RATIO = 16.0f / 9.0f;
#else	// ����ȊO�̂Ƃ��̊�{�A�X�y�N�g��
const float CAMERA_PARAM::DEFAULT_ASPECT_RATIO = 4.0f / 3.0f;
#endif

//=============================================================================
// �R���X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//=============================================================================
CCamera::CCamera()
{
	// �J�����p�����[�^�ݒ�
	// ���W
	m_param.pos				= Vector3(0.0f, 0.0f, 0.0f);
	// �����_���W
	m_param.ray				= Vector3(0.0f, 0.0f, 1.0f);
	// ������x�N�g��
	m_param.up				= Vector3(0.0f, 1.0f, 0.0f);
	// ��p
	m_param.fAoV			= KB_PI / 4.0f;
	// �A�X�y�N�g��
	m_param.fAspectRatio	= CAMERA_PARAM::DEFAULT_ASPECT_RATIO;
	// �j�A�N���b�v��
	m_param.fNear			= 10.f;
	// �t�@�[�N���b�v��
	m_param.fFar			= 2000.f;

	// ��
	m_fLeft = 0.0f;
	// ��
	m_fTop = 0.0f;
	// �E
	m_fRight = 960.0f;
	// ��
	m_fBottom = 540.0f;
}

//=============================================================================
// �f�X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �J�������Z�b�g�A�b�v
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//=============================================================================
void CCamera::Setup(void)
{
	// �ˉe�s�񏉊���
	Matrix4x4Identity(&m_matProj);
	// �E��n�Ŏ����ݒ�
	// �ˉe�s��(����p�A�A�X�y�N�g��A�j�A�ʁA�t�@�[��)
	SetProjectionMatrixRH(&m_matProj,
								m_param.fAoV,
								m_param.fAspectRatio,
								m_param.fNear,
								m_param.fFar);

	// �r���[�s�񏉊���
	Matrix4x4Identity(&m_matView);
	// �E��n�Ńr���[�ݒ�
	SetViewMatrixRH(&m_matView,
						m_param.pos,
						m_param.ray,
						m_param.up);

	// �r���[�t�s��ݒ�
	Matrix4x4Inverse(&m_matInvView, m_matView);

	// ����ˉe�s��
	Matrix4x4Multiply(&m_matViewProj, m_matView, m_matProj);

	// �I���\�[�s��
	SetOrthoMatrixRH(
		&m_matOrtho,
		m_fLeft, m_fTop, m_fRight, m_fBottom, 0.0f, 1.0f);
}

//=============================================================================
// �J�����̍��W��ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̍��W
//=============================================================================
void CCamera::SetPosition(const Vector3& pos)
{
	m_param.pos.x = pos.x;
	m_param.pos.y = pos.y;
	m_param.pos.z = pos.z;
}

//=============================================================================
// �J�����̍��W��ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̍��W
//=============================================================================
const Vector3& CCamera::GetPosition(void)
{
	return m_param.pos;
}

//=============================================================================
// �J�����̒����_���W��ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̒����_���W
//=============================================================================
void CCamera::SetRay(const Vector3& ray)
{
	m_param.ray.x = ray.x;
	m_param.ray.y = ray.y;
	m_param.ray.z = ray.z;
}

//=============================================================================
// �J�����̏�����x�N�g���̐ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̏�����x�N�g��
//=============================================================================
void CCamera::SetUpVector(const Vector3& up)
{
	m_param.up.x = up.x;
	m_param.up.y = up.y;
	m_param.up.z = up.z;
}

//=============================================================================
// �J�����̉�p�ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̉�p
//=============================================================================
void CCamera::SetAoV(const float& fAoV)
{
	m_param.fAoV = fAoV;
}

//=============================================================================
// �J�����̃A�X�y�N�g��ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̃A�X�y�N�g��
//=============================================================================
void CCamera::SetAspectRatio(const float& fAspectRatio)
{
	m_param.fAspectRatio = fAspectRatio;
}

//=============================================================================
// �J�����̃N���b�v�ʐݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����̃j�A�N���b�v��
// arg2		: �J�����̃t�@�[�N���b�v��
//=============================================================================
void CCamera::SetClipPlane(const float& fNear, const float& fFar)
{
	m_param.fNear = fNear;
	m_param.fFar = fFar;
}

//=============================================================================
// �J�����p�����[�^�ݒ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: �J�����p�����[�^
//=============================================================================
void CCamera::SetCameraParam(const CAMERA_PARAM& param)
{
	m_param = param;
}

//=============================================================================
// �J�����̃p�����[�^�擾
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: �J�����̃p�����[�^
// arg		: void
//=============================================================================
const CAMERA_PARAM& CCamera::GetCameraParam(void)
{
	return m_param;
}

//=============================================================================
// �J�����̃r���[�s��擾
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: �J�����̃r���[�s��
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetViewMatrix(void)
{
	return m_matView;
}

//=============================================================================
// �J�����̃r���[�t�s��擾
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: �J�����̃r���[�t�s��
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetInvViewMatrix(void)
{
	return m_matInvView;
}

//=============================================================================
// �J�����̎ˉe�s��擾
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: �J�����̎ˉe�s��
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetProjMatrix(void)
{
	return m_matProj;
}

//=============================================================================
// ����s��Ǝˉe�s����������s���Ԃ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/6/9
//
// ret		: ����s��Ǝˉe�s����������s��
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetViewProjMatrix(void)
{
	return m_matViewProj;
}

//=============================================================================
// ����s��Ǝˉe�s����������s���Ԃ�
// Author : Ryo Kobayashi
// LastUpdate	: 2014/12/8
//
// ret		: �I���\�[�s��
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetOrtho(void)
{
	return m_matOrtho;
}

// EOF