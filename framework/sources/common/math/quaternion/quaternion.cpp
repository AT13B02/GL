//*****************************************************************************
//
// �N�H�[�^�j�I���N���X
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "common/math/math.h"
#include "common/math/quaternion/quaternion.h"
#include "common/math/vector/vector3.h"

//=============================================================================
// ��]��
//=============================================================================
QUATERNION QUATERNION::RotationAxis(const VECTOR3& axis, const f32 angle)
{
	_x = axis._x * sinf(angle * 0.5f);
	_y = axis._y * sinf(angle * 0.5f);
	_z = axis._z * sinf(angle * 0.5f);
	_w = cosf(angle * 0.5f);

	return (*this);
}

//=============================================================================
// �N�H�[�^�j�I�������]�ʂ��擾
//=============================================================================
VECTOR3 QUATERNION::YawPitchRollFromQuaternion(const QUATERNION& q)
{
	// �s��̗v�f�ɕϊ����Ă���I�C���[�p�ɕϊ�����
	float sinPitch = -2.0f * (q._y * q._z - q._w * q._x);

	VECTOR3 out;

	// �W���o�����b�N���l��
	if(fabs(sinPitch) > 0.99999f)
	{
		// �^�ォ�^���ɌŒ�
		out._x = static_cast<float>(MTH_PI) * 0.5f;

		// �Ƃ肠�������[����0�ɐݒ�
		out._y = atan2f(-q._x * q._z + q._w * q._y, 0.5f - q._y * q._y - q._z * q._z);
		out._z = 0.0f;
	}
	else
	{
		// ���ʂɊp�x���v�Z����
		out._x = asinf(sinPitch);
		out._y = atan2f(q._x * q._z + q._w * q._y, 0.5f - q._x * q._x - q._y * q._y);
		out._z = atan2f(q._x * q._y + q._w * q._z, 0.5f - q._x * q._x - q._z * q._z);
	}

	return out;
}

//=============================================================================
// ��Z
//=============================================================================
QUATERNION QUATERNION::operator*(const QUATERNION& rhs) const
{
	QUATERNION temp;
	
	temp._w = _w * rhs._w - (_x * rhs._x + _y * rhs._y + _z * rhs._z); 
	temp._x = _w * rhs._x + rhs._w * _x + _y * rhs._z - _z * rhs._y;
	temp._y = _w * rhs._y + rhs._w * _y + _z * rhs._x - _x * rhs._z;
	temp._z = _w * rhs._z + rhs._w * _z + _x * rhs._y - _y * rhs._x;

	return temp;
}

//=============================================================================
// ��Z���
//=============================================================================
QUATERNION& QUATERNION::operator*=(const QUATERNION& rhs)
{
	_w = _w * rhs._w - (_x * rhs._x + _y * rhs._y + _z * rhs._z); 
	_x = _w * rhs._x + rhs._w * _x + _y * rhs._z - _z * rhs._y;
	_y = _w * rhs._y + rhs._w * _y + _z * rhs._x - _x * rhs._z;
	_z = _w * rhs._z + rhs._w * _z + _x * rhs._y - _y * rhs._x;

	return *this;
}

//---------------------------------- EOF --------------------------------------
