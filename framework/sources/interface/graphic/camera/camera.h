//*****************************************************************************
//
// �J�����N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/basic.h"

// common
#include "common/math/math.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CCamera : public CBasic
{
public:
	// �쐬����
	static CCamera* Create(CDeviceHolder* device_holder);

	// ����������
	bool Init(void);

	// �X�V����
	void Update(void);

	// �J�����̐ݒ�
	virtual void Set(void) = 0;

	// �J�����̍s����擾
	MATRIX4x4& view_matrix(void){return view_matrix_;}

	// �J�����̋t�s����擾
	MATRIX4x4& inverse_matrix(void){return inverse_matrix_;}

	// ���_�̐ݒ�
	void SetEye(const VECTOR3& eye);

	// �����_�̐ݒ�
	void SetLookAt(const VECTOR3& look_at);

	// ���_����̃��[�e�[�V�����̐ݒ�
	void SetRotationEye(const VECTOR3& rotation);

	// �����_����̃��[�e�[�V�����̐ݒ�
	void SetRotationLookAt(const VECTOR3& rotation);

	// �p�[�X�y�N�e�B�u�̐ݒ�
	void SetPerspective(const f32& perspective_degree,const f32& perspective_aspect,const f32& perspective_near,const f32& perspective_far);

protected:
	// �R���X�g���N�^
	CCamera(CDeviceHolder* device_holder);

	// �f�X�g���N�^
	virtual ~CCamera(void);

	// �O���t�B�b�N�f�o�C�X
	CDeviceHolder* device_holder_;

	// ���_
	VECTOR3 eye_;

	// �����_
	VECTOR3 look_at_;

	// ������x�N�g��
	VECTOR3 up_;

	// ���_�ƒ����_�̋���
	f32 length_;

	// ���_�ƒ����_�̊p�x
	VECTOR3 rotation_;

	// �p�[�X�y�N�e�B�u�p�x
	f32 perspective_degree_;

	// �p�[�X�y�N�e�B�u�A�X�y�N�g��
	f32 perspective_aspect_;

	// �p�[�X�y�N�e�B�u�j�A�l
	f32 perspective_near_;

	// �p�[�X�y�N�e�B�u�t�@�[�l
	f32 perspective_far_;

	// �v���W�F�N�V�����s��
	MATRIX4x4 projection_matrix_;

	// �r���[�}�g���N�X
	MATRIX4x4 view_matrix_;

	// �J�����̋t�s��
	MATRIX4x4 inverse_matrix_;

private:
	// ���[�e�[�V�����̐��K��
	VECTOR3 NormalizeRotation(const VECTOR3& rotation);
};

#endif	// _GL_CAMERA_H_

//---------------------------------- EOF --------------------------------------
