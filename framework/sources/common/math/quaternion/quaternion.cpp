//*****************************************************************************
//
// クォータニオンクラス
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "common/math/math.h"
#include "common/math/quaternion/quaternion.h"
#include "common/math/vector/vector3.h"

//=============================================================================
// 回転軸
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
// 乗算
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
// 乗算代入
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
