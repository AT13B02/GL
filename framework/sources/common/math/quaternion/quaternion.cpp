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
// クォータニオンから回転量を取得
//=============================================================================
VECTOR3 QUATERNION::YawPitchRollFromQuaternion(const QUATERNION& q)
{
	// 行列の要素に変換してからオイラー角に変換する
	float sinPitch = -2.0f * (q._y * q._z - q._w * q._x);

	VECTOR3 out;

	// ジンバルロックを考慮
	if(fabs(sinPitch) > 0.99999f)
	{
		// 真上か真下に固定
		out._x = static_cast<float>(MTH_PI) * 0.5f;

		// とりあえずロールを0に設定
		out._y = atan2f(-q._x * q._z + q._w * q._y, 0.5f - q._y * q._y - q._z * q._z);
		out._z = 0.0f;
	}
	else
	{
		// 普通に角度を計算する
		out._x = asinf(sinPitch);
		out._y = atan2f(q._x * q._z + q._w * q._y, 0.5f - q._x * q._x - q._y * q._y);
		out._z = atan2f(q._x * q._y + q._w * q._z, 0.5f - q._x * q._x - q._z * q._z);
	}

	return out;
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
