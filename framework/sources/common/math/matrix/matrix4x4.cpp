//*****************************************************************************
//
// 行列クラス
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
// 単位行列の設定
//=============================================================================
void MATRIX4x4::SetIdentity(void)
{
	_11 = 1.0f; _12 = 0.0f; _13 = 0.0f; _14 = 0.0f;
	_21 = 0.0f; _22 = 1.0f; _23 = 0.0f; _24 = 0.0f;
	_31 = 0.0f; _32 = 0.0f; _33 = 1.0f; _34 = 0.0f;
	_41 = 0.0f; _42 = 0.0f; _43 = 0.0f; _44 = 1.0f;
}

//=============================================================================
// 平行移動行列の設定
//=============================================================================
void MATRIX4x4::SetTlanslation(const f32& tlanslate_x,const f32& tlanslate_y,const f32& tlanslate_z)
{
	SetIdentity();

	_41 = tlanslate_x;
	_42 = tlanslate_y;
	_43 = tlanslate_z;
}

//=============================================================================
// 平行移動行列の設定
//=============================================================================
void MATRIX4x4::SetTlanslation(const VECTOR3& vector)
{
	SetTlanslation(vector._x,vector._y,vector._z);
}

//=============================================================================
// スケール行列の設定
//=============================================================================
void MATRIX4x4::SetScaling(const f32& scale_x,const f32& scale_y,const f32& scale_z)
{
	SetIdentity();

	_11 = scale_x;
	_22 = scale_y;
	_33 = scale_z;
}

//=============================================================================
// YawPitchRoll回転行列の設定
//=============================================================================
void MATRIX4x4::SetYawPitchRoll(const f32& rot_x,const f32& rot_y,const f32& rot_z)
{
	f32 sin_x = sinf(rot_x);
	f32 cos_x = cosf(rot_x);
	f32 sin_y = sinf(rot_y);
	f32 cos_y = cosf(rot_y);
	f32 sin_z = sinf(rot_z);
	f32 cos_z = cosf(rot_z);

	// 単位行列を設定
	SetIdentity();

	_11 = cos_y * cos_z - sin_x * sin_y * sin_z;
	_12 = cos_y * sin_z + sin_x * sin_y * cos_z;
	_13 = -cos_x * sin_y;
	_21 = -cos_x * sin_z;
	_22 = cos_x * cos_z;
	_23 = sin_x;
	_31 = sin_y * cos_z + cos_y * sin_x * sin_z;
	_32 = sin_y * sin_z - cos_y * sin_x * cos_z;
	_33 = cos_y * cos_x;

}

//=============================================================================
// 任意軸回転行列の設定
//=============================================================================
 void MATRIX4x4::SetRotationArbitraryAxis(const VECTOR3& axis,const f32& angle)
{
	f32 axis_x_mul_axis_y    = axis._x * axis._y;
	f32 axis_x_mul_axis_z    = axis._x * axis._z;
	f32 axis_y_mul_axis_z    = axis._y * axis._z;
	f32 cos_angle         = cosf(angle);
	f32 one_minus_cos_angle = 1 - cos_angle;
	f32 sin_angle         = sinf(angle);
	f32 axis_x_mul_sin_angle = axis._x * sin_angle;
	f32 axis_y_mul_sin_angle = axis._y * sin_angle;
	f32 axis_z_mul_sin_angle = axis._z * sin_angle;

	SetIdentity();

	_11 = axis._x * axis._x * one_minus_cos_angle +         cos_angle;
	_12 = axis_x_mul_axis_y  * one_minus_cos_angle + axis_z_mul_sin_angle;
	_13 = axis_x_mul_axis_z  * one_minus_cos_angle - axis_y_mul_sin_angle;
	_21 = axis_x_mul_axis_y  * one_minus_cos_angle - axis_z_mul_sin_angle;
	_22 = axis._y * axis._y * one_minus_cos_angle +         cos_angle;
	_23 = axis_y_mul_axis_z  * one_minus_cos_angle + axis_x_mul_sin_angle;
	_31 = axis_x_mul_axis_z  * one_minus_cos_angle + axis_y_mul_sin_angle;
	_32 = axis_y_mul_axis_z  * one_minus_cos_angle - axis_x_mul_sin_angle;
	_33 = axis._z * axis._z * one_minus_cos_angle +         cos_angle;
}

//=============================================================================
// カメラのパースペクティブ行列の設定
//=============================================================================
void MATRIX4x4::SetPerspectiveFovLH(const f32& degree,const f32& aspect,const f32& near,const f32& far)
{
	f32 div = tanf(degree * MTH_DEGREE * 0.5f);
	f32 far_minus_near = far - near;

	// ゼロチェック
	if((div >= -0.00005f && div <= 0.00005f) || far_minus_near <= 0.0f || aspect <= 0.f)
	{
		// 何もせずに返す
		return;
	}

	// 行列に値を設定
	_11 = 1.0f / (aspect * div);
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;
	_21 = 0.0f;
	_22 = 1.0f / div;
	_23 = 0.0f;
	_24 = 0.0f;
	_31 = 0.0f;
	_32 = 0.0f;
	_33 = far / far_minus_near;
	_34 = 1.0f;
	_41 = 0.0f;
	_42 = 0.0f;
	_43 = -(far * near) / far_minus_near;
	_44 = 0.0f;
}

//=============================================================================
// カメラのパースペクティブ行列の設定
//=============================================================================
void MATRIX4x4::SetPerspectiveFovRH(const f32& degree,const f32& aspect,const f32& near,const f32& far)
{
	f32 div = tanf(degree * MTH_DEGREE * 0.5f);
	f32 far_minus_near = far - near;
	// ゼロチェック
	if((div >= -0.00005f && div <= 0.00005f) || far_minus_near <= 0.0f || aspect <= 0.f)
	{
		// 何もせずに返す
		return;
	}

	// 行列に値を設定
	_11 = 1.0f / (aspect * div);
	_12 = 0.0f;
	_13 = 0.0f;
	_14 = 0.0f;
	_21 = 0.0f;
	_22 = 1.0f / div;
	_23 = 0.0f;
	_24 = 0.0f;
	_31 = 0.0f;
	_32 = 0.0f;
	_33 = -(far + near) / far_minus_near;
	_34 = -1.0f;
	_41 = 0.0f;
	_42 = 0.0f;
	_43 = -2 * (far * near) / far_minus_near;
	_44 = 0.0f;
}

//=============================================================================
// カメラのビュー行列の設定
//=============================================================================
void MATRIX4x4::SetLookAtLH(const VECTOR3& eye,const VECTOR3& look_at,const VECTOR3& up)
{
	// 注視ベクトル設定
	VECTOR3 norm_ray;	// 注視ベクトル
	VECTOR3 norm_right;	// 右方向ベクトル
	VECTOR3	norm_up;
	VECTOR3 inv_pos;

	norm_ray._x = look_at._x - eye._x;
	norm_ray._y = look_at._y - eye._y;
	norm_ray._z = look_at._z - eye._z;

	// 注視ベクトルを正規化
	norm_ray.Normalize();

	// 右方向ベクトルを算出
	norm_right = up.CrossProduct(norm_ray);

	// 正規化
	norm_right.Normalize();

	// 上方向ベクトルを設定
	norm_up = norm_ray.CrossProduct(norm_right);
	
	// 現在の座標の逆位置を求める
	inv_pos._x = -(eye._x * norm_right._x + eye._y * norm_right._y + eye._z * norm_right._z);
	inv_pos._y = -(eye._x * norm_up._x	+ eye._y * norm_up._y	+ eye._z * norm_up._z);
	inv_pos._z = -(eye._x * norm_ray._x	+ eye._y * norm_ray._y	+ eye._z * norm_ray._z);
	
	// 行列に値を設定
	_11 = norm_right._x;
	_21 = norm_right._y;
	_31 = norm_right._z;
	_12 = norm_up._x;
	_22 = norm_up._y;
	_32 = norm_up._z;
	_13 = norm_ray._x;
	_23 = norm_ray._y;
	_33 = norm_ray._z;
	_41 = inv_pos._x;
	_42 = inv_pos._y;
	_43 = inv_pos._z;
	_14 = 0.0f;
	_24 = 0.0f;
	_34 = 0.0f;
	_44 = 1.0f;
}

//=============================================================================
// カメラのビュー行列の設定
//=============================================================================
void MATRIX4x4::SetLookAtRH(const VECTOR3& eye,const VECTOR3& look_at,const VECTOR3& up)
{
	// 注視ベクトル設定
	VECTOR3 norm_ray;	// 注視ベクトル
	VECTOR3 norm_right;	// 右方向ベクトル
	VECTOR3 norm_up;
	VECTOR3 inv_pos;

	norm_ray._x = eye._x - look_at._x;
	norm_ray._y = eye._y - look_at._y;
	norm_ray._z = eye._z - look_at._z;

	// 注視ベクトルを正規化
	norm_ray.Normalize();

	// 右方向ベクトルを算出
	norm_right = up.CrossProduct(norm_ray);

	// 右方向ベクトルを正規化
	norm_right.Normalize();

	// 上方向ベクトルを設定
	norm_up = norm_ray.CrossProduct(norm_right);

	// 現在の座標の逆位置を求める
	inv_pos._x = -(eye._x * norm_right._x + eye._y * norm_right._y + eye._z * norm_right._z);
	inv_pos._y = -(eye._x * norm_up._x    + eye._y * norm_up._y    + eye._z * norm_up._z);
	inv_pos._z = -(eye._x * norm_ray._x   + eye._y * norm_ray._y   + eye._z * norm_ray._z);
	
	// 行列に値を設定
	_11 = norm_right._x;
	_21 = norm_right._y;
	_31 = norm_right._z;
	_12 = norm_up._x;
	_22 = norm_up._y;
	_32 = norm_up._z;
	_13 = norm_ray._x;
	_23 = norm_ray._y;
	_33 = norm_ray._z;
	_41 = inv_pos._x;
	_42 = inv_pos._y;
	_43 = inv_pos._z;
	_14 = 0.0f;
	_24 = 0.0f;
	_34 = 0.0f;
	_44 = 1.0f;
}

//=============================================================================
// 行列式の取得
//=============================================================================
f32 MATRIX4x4::GetDeterminant(void)
{
	f32 i11 = _11 * (
		_33 * (_22 * _44 - _24 * _42) +
		_34 * (_23 * _42 - _22 * _43) +
		_32 * (_24 * _43 - _23 * _44));
	f32 i12 = _12 * -(
		_33 * (_21 * _44 - _24 * _41) +
		_34 * (_23 * _41 - _21 * _43) +
		_31 * (_24 * _43 - _23 * _44));
	f32 i13 = _13 * (
		_32 * (_21 * _44 - _24 * _41) +
		_34 * (_22 * _41 - _21 * _42) +
		_31 * (_24 * _42 - _22 * _44));
	f32 i14 = _14 * -(
		_32 * (_21 * _43 - _23 * _41) +
		_33 * (_22 * _41 - _21 * _42) +
		_31 * (_23 * _42 - _22 * _43));

	return (i11 + i12 + i13 + i14);
}

//=============================================================================
// 逆行列の取得
//=============================================================================
MATRIX4x4 MATRIX4x4::GetInverse(void)
{
	// 行列式取得
	f32 det = 0.0f;
	MATRIX4x4 matrix;

	det = GetDeterminant();

	// 行列式の値が非常に小さいとき、なにもしない
	if(det <= 0.000005f && det >= -0.000005f)
	{
		return *this;
	}

	// 行列式の逆数
	f32 invDet = 1.0f / det;

	// 余因子算出
	f32 i11 = 
		_22 * _33 * _44 - _24 * _33 * _42 +
		_23 * _34 * _42 - _22 * _34 * _43 +
		_24 * _32 * _43 - _23 * _32 * _44;
	f32 i12 = -(
		_23 * _34 * _41 - _21 * _34 * _43 +
		_24 * _31 * _43 - _23 * _31 * _44 +
		_21 * _33 * _44 - _24 * _33 * _41);
	f32 i13 =
		_24 * _31 * _42 - _22 * _31 * _44 +
		_21 * _32 * _44 - _24 * _32 * _41 +
		_22 * _34 * _41 - _21 * _34 * _42;
	f32 i14 = -(
		_21 * _32 * _43 - _23 * _32 * _41 +
		_22 * _33 * _41 - _21 * _33 * _42 +
		_23 * _31 * _42 - _22 * _31 * _43);
	f32 i21 = -(
		_32 * _43 * _14 - _34 * _43 * _12 +
		_33 * _44 * _12 - _32 * _44 * _13 +
		_34 * _42 * _13 - _33 * _42 * _14);
	f32 i22 = 
		_33 * _44 * _11 - _31 * _44 * _13 +
		_34 * _41 * _13 - _33 * _41 * _14 +
		_31 * _43 * _14 - _34 * _43 * _11;
	f32 i23 = -(
		_34 * _41 * _12 - _32 * _41 * _14 +
		_31 * _42 * _14 - _34 * _42 * _11 +
		_32 * _44 * _11 - _31 * _44 * _12);
	f32 i24 = 
		_31 * _42 * _13 - _33 * _42 * _11 +
		_32 * _43 * _11 - _31 * _43 * _12 +
		_33 * _41 * _12 - _32 * _41 * _13;
	f32 i31 = 
		_42 * _13 * _24 - _44 * _13 * _22 +
		_43 * _14 * _22 - _42 * _14 * _23 +
		_44 * _12 * _23 - _43 * _12 * _24;
	f32 i32 = -(
		_43 * _14 * _21 - _41 * _14 * _23 +
		_44 * _11 * _23 - _43 * _11 * _24 +
		_41 * _13 * _24 - _44 * _13 * _21);
	f32 i33 =
		_44 * _11 * _22 - _42 * _11 * _24 +
		_41 * _12 * _24 - _44 * _12 * _21 +
		_42 * _14 * _21 - _41 * _14 * _22;
	f32 i34 = -(
		_41 * _12 * _23 - _43 * _12 * _21 +
		_42 * _13 * _21 - _41 * _13 * _22 +
		_43 * _11 * _22 - _42 * _11 * _23);
	f32 i41 = -(
		_12 * _23 * _34 - _14 * _23 * _32 +
		_13 * _24 * _32 - _12 * _24 * _33 +
		_14 * _22 * _33 - _13 * _22 * _34);
	f32 i42 =
		_13 * _24 * _31 - _11 * _24 * _33 +
		_14 * _21 * _33 - _13 * _21 * _34 +
		_11 * _23 * _34 - _14 * _23 * _31;
	f32 i43 = -(
		_14 * _21 * _32 - _12 * _21 * _34 +
		_11 * _22 * _34 - _14 * _22 * _31 +
		_12 * _24 * _31 - _11 * _24 * _32);
	f32 i44 = 
		_11 * _22 * _33 - _13 * _22 * _31 +
		_12 * _23 * _31 - _11 * _23 * _32 +
		_13 * _21 * _32 - _12 * _21 * _33;

	// 逆行列設定
	matrix._11 = i11 * invDet;
	matrix._12 = i21 * invDet;
	matrix._13 = i31 * invDet;
	matrix._14 = i41 * invDet;
	matrix._21 = i12 * invDet;
	matrix._22 = i22 * invDet;
	matrix._23 = i32 * invDet;
	matrix._24 = i42 * invDet;
	matrix._31 = i13 * invDet;
	matrix._32 = i23 * invDet;
	matrix._33 = i33 * invDet;
	matrix._34 = i43 * invDet;
	matrix._41 = i14 * invDet;
	matrix._42 = i24 * invDet;
	matrix._43 = i34 * invDet;
	matrix._44 = i44 * invDet;

	return matrix;
}

//=============================================================================
// 回転行列の逆行列の取得
//=============================================================================
MATRIX4x4 MATRIX4x4::GetInverseRotation(void)
{
	return MATRIX4x4( _11, _21, _31,0.0f,
					  _12, _22, _32,0.0f,
					  _13, _23, _33,0.0f,
					 0.0f,0.0f,0.0f,1.0f);
}

//=============================================================================
// 転置行列の取得
//=============================================================================
MATRIX4x4 MATRIX4x4::GetTranspose(void)
{
	return MATRIX4x4( _11, _21, _31, _41,
					  _12, _22, _32, _42,
					  _13, _23, _33, _43,
					  _14, _24, _34, _44);
}

//=============================================================================
// オイラー角の取得
//=============================================================================
VECTOR3 MATRIX4x4::GetEulerAngle(void)
{
	f32 sin_pitch = _23;
	VECTOR3 rotation;

	// asinが不正な値にならないようにする
	if(sin_pitch <= -1.0f)
	{
		rotation._x = -(f32)(MTH_PI) * 0.5f;
	}
	else if(sin_pitch >= 1.0f)
	{
		rotation._x = (f32)(MTH_PI) * 0.5f;
	}
	else
	{
		rotation._x = asinf(sin_pitch);
	}

	// ジンバルロックを考慮
	if(fabs(sin_pitch) > 0.99999f)
	{
		// cos(Pitch)を0と仮定して計算
		// ロールかヘディングを0に設定してどちらかを計算
		rotation._z = 0.0f;
		rotation._y = atan2f(_31,_11);
	}
	else
	{
		rotation._y = atan2f(-_13,_33);
		rotation._z = atan2f(-_21,_22);
	}

	return rotation;
}

//=============================================================================
// 乗算演算子のオーバーロード
//=============================================================================
MATRIX4x4 MATRIX4x4::operator*(const f32& value) const
{
	return MATRIX4x4(_11 * value,_12 * value,_13 * value,_14 * value,
					 _21 * value,_22 * value,_23 * value,_24 * value,
					 _31 * value,_32 * value,_33 * value,_34 * value,
					 _41 * value,_42 * value,_43 * value,_44 * value);
}

//=============================================================================
// 除算演算子のオーバーロード
//=============================================================================
MATRIX4x4 MATRIX4x4::operator/(const f32& value) const
{
	f32 inv = 0.0f;

	if(value == 0.0f)
	{
		return *this;
	}

	inv = 1.0f / value;

	return MATRIX4x4(_11 * inv,_12 * inv,_13 * inv,_14 * inv,
					 _21 * inv,_22 * inv,_23 * inv,_24 * inv,
					 _31 * inv,_32 * inv,_33 * inv,_34 * inv,
					 _41 * inv,_42 * inv,_43 * inv,_44 * inv);
}

//=============================================================================
// 乗算代入演算子のオーバーロード
//=============================================================================
MATRIX4x4& MATRIX4x4::operator*=(const f32& value)
{
	_11 *= value;
	_12 *= value;
	_13 *= value;
	_14 *= value;
	_21 *= value;
	_22 *= value;
	_23 *= value;
	_24 *= value;
	_31 *= value;
	_32 *= value;
	_33 *= value;
	_34 *= value;
	_41 *= value;
	_42 *= value;
	_43 *= value;
	_44 *= value;

	return *this;
}

//=============================================================================
// 除算代入演算子のオーバーロード
//=============================================================================
MATRIX4x4& MATRIX4x4::operator/=(const f32& value)
{
	f32 inv = 0.0f;

	if(value == 0.0f)
	{
		return *this;
	}

	inv = 1.0f / value;

	_11 *= inv;
	_12 *= inv;
	_13 *= inv;
	_14 *= inv;
	_21 *= inv;
	_22 *= inv;
	_23 *= inv;
	_24 *= inv;
	_31 *= inv;
	_32 *= inv;
	_33 *= inv;
	_34 *= inv;
	_41 *= inv;
	_42 *= inv;
	_43 *= inv;
	_44 *= inv;

	return *this;
}

//=============================================================================
// 加算演算子のオーバーロード
//=============================================================================
MATRIX4x4 MATRIX4x4::operator+(const MATRIX4x4& matrix) const
{
	return MATRIX4x4(_11 + matrix._11,_12 + matrix._12,_13 + matrix._13,_14 + matrix._14,
					 _21 + matrix._21,_22 + matrix._22,_23 + matrix._23,_24 + matrix._24,
					 _31 + matrix._31,_32 + matrix._32,_33 + matrix._33,_34 + matrix._34,
					 _41 + matrix._41,_42 + matrix._42,_43 + matrix._43,_44 + matrix._44);
}

//=============================================================================
// 減算演算子のオーバーロード
//=============================================================================
MATRIX4x4 MATRIX4x4::operator-(const MATRIX4x4& matrix) const
{
	return MATRIX4x4(_11 - matrix._11,_12 - matrix._12,_13 - matrix._13,_14 - matrix._14,
					 _21 - matrix._21,_22 - matrix._22,_23 - matrix._23,_24 - matrix._24,
					 _31 - matrix._31,_32 - matrix._32,_33 - matrix._33,_34 - matrix._34,
					 _41 - matrix._41,_42 - matrix._42,_43 - matrix._43,_44 - matrix._44);
}

//=============================================================================
// 乗算演算子のオーバーロード
//=============================================================================
MATRIX4x4 MATRIX4x4::operator*(const MATRIX4x4& matrix) const
{
	MATRIX4x4 Mat;

	Mat._11 = _11 * matrix._11 + _12 * matrix._21 + _13 * matrix._31 + _14 * matrix._41;
	Mat._12 = _11 * matrix._12 + _12 * matrix._22 + _13 * matrix._32 + _14 * matrix._42;
	Mat._13 = _11 * matrix._13 + _12 * matrix._23 + _13 * matrix._33 + _14 * matrix._43;
	Mat._14 = _11 * matrix._14 + _12 * matrix._24 + _13 * matrix._34 + _14 * matrix._44;

	Mat._21 = _21 * matrix._11 + _22 * matrix._21 + _23 * matrix._31 + _24 * matrix._41;
	Mat._22 = _21 * matrix._12 + _22 * matrix._22 + _23 * matrix._32 + _24 * matrix._42;
	Mat._23 = _21 * matrix._13 + _22 * matrix._23 + _23 * matrix._33 + _24 * matrix._43;
	Mat._24 = _21 * matrix._14 + _22 * matrix._24 + _23 * matrix._34 + _24 * matrix._44;

	Mat._31 = _31 * matrix._11 + _32 * matrix._21 + _33 * matrix._31 + _34 * matrix._41;
	Mat._32 = _31 * matrix._12 + _32 * matrix._22 + _33 * matrix._32 + _34 * matrix._42;
	Mat._33 = _31 * matrix._13 + _32 * matrix._23 + _33 * matrix._33 + _34 * matrix._43;
	Mat._34 = _31 * matrix._14 + _32 * matrix._24 + _33 * matrix._34 + _34 * matrix._44;

	Mat._41 = _41 * matrix._11 + _42 * matrix._21 + _43 * matrix._31 + _44 * matrix._41;
	Mat._42 = _41 * matrix._12 + _42 * matrix._22 + _43 * matrix._32 + _44 * matrix._42;
	Mat._43 = _41 * matrix._13 + _42 * matrix._23 + _43 * matrix._33 + _44 * matrix._43;
	Mat._44 = _41 * matrix._14 + _42 * matrix._24 + _43 * matrix._34 + _44 * matrix._44;

	return Mat;
}

//=============================================================================
// 加算代入演算子のオーバーロード
//=============================================================================
MATRIX4x4& MATRIX4x4::operator+=(const MATRIX4x4& matrix)
{
	_11 += matrix._11;
	_12 += matrix._12;
	_13 += matrix._13;
	_14 += matrix._14;

	_21 += matrix._21;
	_22 += matrix._22;
	_23 += matrix._23;
	_24 += matrix._24;

	_31 += matrix._31;
	_32 += matrix._32;
	_33 += matrix._33;
	_34 += matrix._34;

	_41 += matrix._41;
	_42 += matrix._42;
	_43 += matrix._43;
	_44 += matrix._44;

	return *this;
}

//=============================================================================
// 減算代入演算子のオーバーロード
//=============================================================================
MATRIX4x4& MATRIX4x4::operator-=(const MATRIX4x4& matrix)
{
	_11 -= matrix._11;
	_12 -= matrix._12;
	_13 -= matrix._13;
	_14 -= matrix._14;

	_21 -= matrix._21;
	_22 -= matrix._22;
	_23 -= matrix._23;
	_24 -= matrix._24;

	_31 -= matrix._31;
	_32 -= matrix._32;
	_33 -= matrix._33;
	_34 -= matrix._34;

	_41 -= matrix._41;
	_42 -= matrix._42;
	_43 -= matrix._43;
	_44 -= matrix._44;

	return *this;
}

//=============================================================================
// 乗算代入演算子のオーバーロード
//=============================================================================
MATRIX4x4& MATRIX4x4::operator*=(const MATRIX4x4& matrix)
{
	_11 = _11 * matrix._11 + _12 * matrix._21 + _13 * matrix._31 + _14 * matrix._41;
	_12 = _11 * matrix._12 + _12 * matrix._22 + _13 * matrix._32 + _14 * matrix._42;
	_13 = _11 * matrix._13 + _12 * matrix._23 + _13 * matrix._33 + _14 * matrix._43;
	_14 = _11 * matrix._14 + _12 * matrix._24 + _13 * matrix._34 + _14 * matrix._44;

	_21 = _21 * matrix._11 + _22 * matrix._21 + _23 * matrix._31 + _24 * matrix._41;
	_22 = _21 * matrix._12 + _22 * matrix._22 + _23 * matrix._32 + _24 * matrix._42;
	_23 = _21 * matrix._13 + _22 * matrix._23 + _23 * matrix._33 + _24 * matrix._43;
	_24 = _21 * matrix._14 + _22 * matrix._24 + _23 * matrix._34 + _24 * matrix._44;

	_31 = _31 * matrix._11 + _32 * matrix._21 + _33 * matrix._31 + _34 * matrix._41;
	_32 = _31 * matrix._12 + _32 * matrix._22 + _33 * matrix._32 + _34 * matrix._42;
	_33 = _31 * matrix._13 + _32 * matrix._23 + _33 * matrix._33 + _34 * matrix._43;
	_34 = _31 * matrix._14 + _32 * matrix._24 + _33 * matrix._34 + _34 * matrix._44;

	_41 = _41 * matrix._11 + _42 * matrix._21 + _43 * matrix._31 + _44 * matrix._41;
	_42 = _41 * matrix._12 + _42 * matrix._22 + _43 * matrix._32 + _44 * matrix._42;
	_43 = _41 * matrix._13 + _42 * matrix._23 + _43 * matrix._33 + _44 * matrix._43;
	_44 = _41 * matrix._14 + _42 * matrix._24 + _43 * matrix._34 + _44 * matrix._44;

	return *this;
}

//=============================================================================
// 代入演算子のオーバーロード
//=============================================================================
void MATRIX4x4 ::operator=(const MATRIX4x4& matrix)
{
	_11 = matrix._11;
	_12 = matrix._12;
	_13 = matrix._13;
	_14 = matrix._14;

	_21 = matrix._21;
	_22 = matrix._22;
	_23 = matrix._23;
	_24 = matrix._24;

	_31 = matrix._31;
	_32 = matrix._32;
	_33 = matrix._33;
	_34 = matrix._34;

	_41 = matrix._41;
	_42 = matrix._42;
	_43 = matrix._43;
	_44 = matrix._44;

}

//-----------------------------------EOF---------------------------------------
