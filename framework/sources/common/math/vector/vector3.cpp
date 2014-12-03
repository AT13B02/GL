//*****************************************************************************
//
// 3次元ベクトルクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "common/math/math.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 単位ベクトル化
//=============================================================================
const VECTOR3& VECTOR3::Normalize(void)
{
	float fMagnitude = Magnitude();

	// 0除算の確認
	if (fMagnitude != 0.0f)
	{
		_x /= fMagnitude;
		_y /= fMagnitude;
		_z /= fMagnitude;
	}

	return *this;
}

//=============================================================================
// ベクトルの大きさを取得
//=============================================================================
float VECTOR3::Magnitude(void) const
{
	return sqrtf(_x * _x + _y * _y + _z * _z);
}

//=============================================================================
// ベクトルの内積計算
//=============================================================================
float VECTOR3::DotProduct(const VECTOR3& vector) const
{
	return _x * vector._x + _y * vector._y + _z * vector._z;
}

//=============================================================================
// ベクトルの外積計算
//=============================================================================
VECTOR3 VECTOR3::CrossProduct(const VECTOR3& vector) const
{
	VECTOR3 Cross;

	Cross._x = _y * vector._z - _z * vector._y;
	Cross._y = _z * vector._x - _x * vector._z;
	Cross._z = _x * vector._y - _y * vector._x;

	return Cross;
}

//=============================================================================
// スカラーとの足算
//=============================================================================
VECTOR3 VECTOR3::operator+(const float& fValue) const
{
	return VECTOR3(_x + fValue,_y + fValue,_z + fValue);
}

//=============================================================================
// スカラーとの引算
//=============================================================================
VECTOR3 VECTOR3::operator-(const float& fValue) const
{
	return VECTOR3(_x - fValue,_y - fValue,_z - fValue);
}

//=============================================================================
// スカラーとの掛算
//=============================================================================
VECTOR3 VECTOR3::operator*(const float& fValue) const
{
	return VECTOR3(_x * fValue,_y * fValue,_z * fValue);
}

//=============================================================================
// スカラーとの割算
//=============================================================================
VECTOR3 VECTOR3::operator/(const float& fValue) const
{
	if(fValue != 0)
	{
		float fInv = 1 / fValue;
		return VECTOR3(_x * fInv,_y * fInv,_z * fInv);
	}

	return *this;
}

//=============================================================================
// スカラーとの足算
//=============================================================================
VECTOR3& VECTOR3::operator+=(const float& fValue)
{
	_x += fValue;
	_y += fValue;
	_z += fValue;

	return *this;
}

//=============================================================================
// スカラーとの引算
//=============================================================================
VECTOR3& VECTOR3::operator-=(const float& fValue)
{
	_x -= fValue;
	_y -= fValue;
	_z -= fValue;

	return *this;
}

//=============================================================================
// スカラーとの掛算
//=============================================================================
VECTOR3& VECTOR3::operator*=(const float& fValue)
{
	_x *= fValue;
	_y *= fValue;
	_z *= fValue;

	return *this;
}

//=============================================================================
// スカラーとの割算
//=============================================================================
VECTOR3& VECTOR3::operator/=(const float& fValue)
{
	float fInv;

	if(fValue != 0)
	{
		fInv = 1 / fValue;

		_x *= fInv;
		_y *= fInv;
		_z *= fInv;
	}

	return *this;
}

//=============================================================================
// ベクトルとの足算
//=============================================================================
VECTOR3 VECTOR3::operator+(const VECTOR3& vector) const
{
	return VECTOR3(_x + vector._x,_y + vector._y,_z + vector._z);
}

//=============================================================================
// ベクトルとの引算
//=============================================================================
VECTOR3 VECTOR3::operator-(const VECTOR3& vector) const
{
	return VECTOR3(_x - vector._x,_y - vector._y,_z - vector._z);
}

//=============================================================================
// ベクトルとの足算
//=============================================================================
VECTOR3& VECTOR3::operator+=(const VECTOR3& vector)
{
	_x += vector._x;
	_y += vector._y;
	_z += vector._z;

	return *this;
}

//=============================================================================
// ベクトルとの引算
//=============================================================================
VECTOR3& VECTOR3::operator-=(const VECTOR3& vector)
{
	_x -= vector._x;
	_y -= vector._y;
	_z -= vector._z;

	return *this;
}

//-----------------------------------EOF---------------------------------------
