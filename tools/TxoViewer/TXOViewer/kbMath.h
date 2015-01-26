//=============================================================================
//
// 独自定義の数学ユーティリティ [kbMath.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/15
//
//=============================================================================
#pragma once
#ifndef __KB_MATH_H__
#define __KB_MATH_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <float.h>		// (倍精度)浮動小数定義
#include <math.h>		// 独自定義関数がボトルネックになったら使う

//*****************************************************************************
// このファイルに入ってるクラスと関数
/*

Vector2 クラス
Vector3 クラス
Vector4 クラス
Matrix4x4 クラス
Quaternion クラス
Plane クラス
AARectクラス
AABB クラス

// 平方根関数
double inline __declspec (naked) __fastcall sqrtFast(double n)
float inline __declspec (naked) __fastcall sqrtFast(float n)
// コサイン関数
double inline __declspec (naked) __fastcall cosFast(double n)
float inline __declspec (naked) __fastcall cosFast(float n)
// サイン関数
double inline __declspec (naked) __fastcall sinFast(double n)
float inline __declspec (naked) __fastcall sinFast(float n)
// タンジェント関数
double inline __declspec (naked) __fastcall tanFast(double n)
float inline __declspec (naked) __fastcall tanFast(float n)
// アークコサイン関数
double inline __declspec (naked) __fastcall acosFast(double n)
float inline __declspec (naked) __fastcall acosFast(float n)
// アークサイン関数
double inline __declspec (naked) __fastcall asinFast(double n)
float inline __declspec (naked) __fastcall asinFast(float n)
// アークタンジェント関数
double inline __declspec (naked) __fastcall atanFast(double n)
float inline __declspec (naked) __fastcall atanFast(float n)
// アークタンジェント関数(2引数)
double inline __declspec (naked) __fastcall atan2Fast(double y, double x)
float inline __declspec (naked) __fastcall atan2Fast(float y, float x)

// 2Dベクトル
// 2Dベクトル内積
void Vector2Dot(float* pOut, const Vector2& vec0, const Vector2& vec1)
// 2Dベクトル外積
void Vector2Cross(float* pOut, const Vector2& vec0, const Vector2& vec1)

// 3Dベクトル
// ベクトル加算処理
void Vector3Add(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// ベクトル減算処理
void Vector3Sub(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// ベクトルを正規化する
void Vector3Normalize(Vector3* pOut, const Vector3& vec0)
// ベクトルの内積を算出
void Vector3Dot(float* pOut, const Vector3& vec0, const Vector3& vec1)
// 正規化したベクトルの内積を算出
void Vector3NormalizeDot(float* pOut, const Vector3& vec0, const Vector3& vec1)
// ベクトルの外積を算出
void Vector3Cross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// 正規化したベクトルの外積を算出
void Vector3NormalizeCross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// ベクトルの行列変換
void Vector3Transform(Vector4 *pOut, const Vector3& vec, const Matrix4x4& mtx)
// 3D座標をw = 1に射影する変換
void Vector3TransformCoord(Vector3 *pOut, const Vector3& nor, const Matrix4x4& mtx)
// 法線の変換
void Vector3TransformNormal(Vector3 *pOut, const Vector3& nor, const Matrix4x4& mtx)
// 壁擦りベクトル算出
void Vector3ScratchWall(Vector3 *pOut, const Vector3& in, const Vector3& normal)
// 反射ベクトル算出
void Vector3Reflection(Vector3 *pOut, const Vector3& in, const Vector3& normal)

// 行列
// 行列加算
void Matrix4x4Add(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
// 行列減算
void Matrix4x4Sub(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
// 行列乗算
void Matrix4x4Multiply(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
// 行列初期化
void Matrix4x4Identity(Matrix4x4 *pOut);
// 転置行列作成
void Matrix4x4Transpose(Matrix4x4 *pOut, const Matrix4x4& mtxTrns)
// 行列式算出
void Matrix4x4Determinant(float *pOut, const Matrix4x4& mtx)
// 逆行列作成
void Matrix4x4Inverse(Matrix4x4 *pOut, const Matrix4x4& mtx)
// スケール行列作成
void Matrix4x4Scaling(Matrix4x4 *pOut, const float& sx, const float &sy, const float& sz)
// YawPitchRoll回転行列作成
void Matrix4x4YawPitchRoll(Matrix4x4 *pOut, const float& pitch, const float& yaw, const float& roll)
// 平行移動行列作成
void Matrix4x4Translation(Matrix4x4 *pOut, const float& tx, const float& ty, const float& tz)
// 行列を拡大、回転、平行移動成分に分解
void Matrix4x4Decompose(Vector3* pTrans, Quaternion* pRot, Vector3* pScale, const Matrix4x4& mtx)
// 任意軸回転行列作成
void Matrix4x4RotationArbitraryAxis(Matrix4x4 *pOut, const Vector3& axis, const float& angle)
// 行列からオイラー角に変換
void Matrix4x4ToEulerAngle(Vector3 *pOut, const Matrix4x4& mtx)
// 行列からクォータニオンに変換
void Matrix4x4ToQuaternion(Quaternion* pOut, const Matrix4x4& mtx)

// クォータニオン
// 以下で使用するクォータニオン乗算は、一般的な式と異なる。乗算の定義を変更することにより、
// q = bap(ba)-1 のような右から左の乗算を
// q = (-ab)p(ab) の左から右への乗算へと変えた(結果は同じ)
// クォータニオン乗算
void QuaternionMultiply(Quaternion *pOut, const Quaternion& q1, const Quaternion& q2)
// クォータニオン内積
void QuaternionDot(float* pOut, const Quaternion& q1, const Quaternion& q2)
// 恒等クォータニオン作成
void QuaternionIdentity(Quaternion *pOut)
// クォータニオン正規化
void QuaternionNormalize(Quaternion *pOut, const Quoternion& q) 
// 共役クォータニオン作成
void QuaternionConjugate(Quaternion *pOut, const Quaternion& q)
// 逆クォータニオン(共役と正規化されたクォータニオン)作成
void QuaternionInverse(Quaternion *pOut, const Quaternion& q)
// 指定した軸と回転量でクォータニオンを作成
void QuaternionRotationAxis(Quoaternion *pOut, const Vector3& axis, float angle)
// 指定した2つのクォータニオンの球面線形補間されたクォータニオンを作成
void QuaternionSlerp(Quaternion *pOut, const Quaternion& q1, const Quaternion& q2, float t)
// オイラー角からクォータニオンへの変換
void EulerAngleToQuaternion(Quaternion *pOut, const Vector3& rot)
// クォータニオンからオイラー角に変換
void QuaternionToEulerAngle(Vector3 *pOut, const Quaternion& q)
// クォータニオンから行列に変換
void QuaternionToMatrix4x4(Matrix4x4 *pOut, const Quaternion& q)

// 指定した座標を任意軸で回転
void Vector3RotationAxis(Vector3* pOut, const Vector3& pos, const Vector3& axis, const float& angle)

// 平面
// 平面と点の境界判定
void PlaneDotVector3(float *pOut, const Plane& pl, const Vector3& point)
// 点と法線から平面を算出する
void PlaneFromPointNormal(Plane *pOut, const Vector3& p, const Vector3& nor)
// 3点から平面を算出する
void PlaneFromPoints(Plane *pOut, const Vector3& p0, const Vector3& p1, const Vector3& p2)
// 平面を正規化する
void PlaneNormalize(Plane *pOut, const Plane& pl)
// 平面の回転
void PlaneRotation(Plane *pOut, const Plane& pl, const Matrix4x4& rot)
// 平面と光線の交差した座標
bool PlaneRayIntersect(Vector3 *pOut, const Plane& pl, const Vector3& pos, const Vector3& ray)
// 平面と線分の交差した座標
bool PlaneLineSegmentIntersect(Vector3 *pOut, const Plane& pl, const Vector3& p0, const Vector3& p1)

// ワールド行列作成
void SetWorldMatrix(Matrix4x4 *pOut, const Vector3 &trans, const Vector3 &rot, const Vector3 &scl)
// ワールド逆行列作成
void SetWorldInverseMatrix(Matrix4x4 *pOut, const Matrix4x4& mtx)
// ビュー行列作成
void SetViewMatrixLH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
void SetViewMatrixRH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
// 三軸からビュー行列作成
void SetViewMatrixFromAxis(Matrix4x4* pOut, const Vector3& pos, const Vector3& right, const Vector3& up, const Vector3& front)
// 射影行列作成
void SetProjectionMatrixLH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
void SetProjectionMatrixRH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
// 平行投影行列作成
void SetOrthoMatrixRH(Matrix4x4 *pOut, float fLeft, float fTop, float fRight, float fBottom, float fNear, float fFar)
// ビューポート行列作成
void SetViewport(float x, float y, float fWidth, float fHeight, float nearSurface, float farSurface)

// スクリーン座標をワールド座標に変換し、ワールド座標と光線を出力(左手系)
void ScreenToWorldPositionLH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)
// スクリーン座標をワールド座標に変換し、ワールド座標と光線を出力(右手系)
void ScreenToWorldPositionRH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)

// 指定した二つの値の線形補間を算出
template<typename T>
void ComputeLerp(T* pOut, const T& p0, const T& p1, float t)

// 原点を中心にした角速度を算出
void ComputeAngularVelocity(Vector3* pOut, const Vector3& pos,const Vector3& vec)

// 中心を指定した角速度を算出
void ComputeAngularVelocity(Vector3* pOut, const Vector3& center, const Vector3& pos, const Vector3& vec)

// 二つのベクトルから、一方の反射ベクトルを算出
bool ComputeCollideLineToLineXZ(
Vector3* pCollidePoint,
float* pRate,	// 侵入したときのベクトルの比率
Vector3* pReflectVec,
Vector3 pos0st,
Vector3 pos0ed,
Vector3 pos1st,
Vector3 pos1ed)
*/
//*****************************************************************************

//*****************************************************************************
// 数学に便利?なマクロ定義
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
// 円周率
#define KB_PI			(3.141592653589f)
// 度数法の1度
#define ONE_DEGREE		(KB_PI / 180.0f)
// 2の平方根の逆数
#define ONE_OVER_RT2	(0.7071067811865475f)

//*****************************************************************************
// 2次ベクトルクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/26
//*****************************************************************************
class Vector2
{
public:

	Vector2(){}
	Vector2(float x, float y) :
	x(x), y(y)
	{}

	~Vector2(){}

	// オーバーロード演算子
	// 加算
	Vector2 operator+(const Vector2& rhs) const
	{
		return Vector2(this->x + rhs.x, this->y + rhs.y);
	}
	// 加算記号前置
	Vector2 operator+(void) const
	{
		return *this;
	}
	// 加算代入
	Vector2& operator+=(const Vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}
	// 減算
	Vector2 operator-(const Vector2& rhs) const
	{
		return Vector2(this->x - rhs.x, this->y - rhs.y);
	}
	// 減算記号前置
	Vector2 operator-(void) const
	{
		return Vector2(-this->x, -this->y);
	}
	// 減算代入
	Vector2& operator-=(const Vector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}
	// 乗算
	Vector2 operator*(const float& rhs) const
	{
		return Vector2(this->x * rhs, this->y * rhs);
	}
	// 乗算代入
	Vector2& operator*=(const float& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;

		return *this;
	}
	// 除算
	Vector2 operator/(const float& rhs) const
	{
		return Vector2(this->x / rhs, this->y / rhs);
	}
	// 除算代入
	Vector2& operator/=(const float& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;

		return *this;
	}

	// メンバ変数
	float x, y;
};

//*****************************************************************************
// 3次ベクトルクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
class Vector3
{
public:

	Vector3(){}
	Vector3(float x, float y, float z) :
	x(x), y(y), z(z)
	{}

	~Vector3(){}

	// オーバーロード演算子
	// 加算
	Vector3 operator+(const Vector3& rhs) const
	{
		return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}
	// 加算記号前置
	Vector3 operator+(void) const
	{
		return *this;
	}
	// 加算代入
	Vector3& operator+=(const Vector3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}
	// 減算
	Vector3 operator-(const Vector3& rhs) const
	{
		return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}
	// 減算記号前置
	Vector3 operator-(void) const
	{
		return Vector3(-this->x, -this->y, -this->z);
	}
	// 減算代入
	Vector3& operator-=(const Vector3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}
	// 乗算
	Vector3 operator*(const float& rhs) const
	{
		return Vector3(this->x * rhs, this->y * rhs, this->z * rhs);
	}
	// 乗算代入
	Vector3& operator*=(const float& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return *this;
	}
	// 除算
	Vector3 operator/(const float& rhs) const
	{
		return Vector3(this->x / rhs, this->y / rhs, this->z / rhs);
	}
	// 除算代入
	Vector3& operator/=(const float& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return *this;
	}

	// メンバ変数
	float x, y, z;
};

//*****************************************************************************
// 4次ベクトルクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
class Vector4
{
public:

	Vector4(){}
	Vector4(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w)
	{}

	~Vector4(){}

	// オーバーロード演算子
	// 加算
	Vector4 operator+(const Vector4& rhs) const
	{
		return Vector4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
	}
	// 加算記号前置
	Vector4 operator+(void) const
	{
		return *this;
	}
	// 加算代入
	Vector4& operator+=(const Vector4& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;

		return *this;
	}
	// 減算
	Vector4 operator-(const Vector4& rhs) const
	{
		return Vector4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
	}
	// 減算記号前置
	Vector4 operator-(void) const
	{
		return Vector4(-this->x, -this->y, -this->z, -this->w);
	}
	// 減算代入
	Vector4& operator-=(const Vector4& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;

		return *this;
	}
	// 乗算
	Vector4 operator*(const float& rhs) const
	{
		return Vector4(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs);
	}
	// 乗算代入
	Vector4& operator*=(const float& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->w *= rhs;

		return *this;
	}
	// 除算
	Vector4 operator/(const float& rhs) const
	{
		return Vector4(this->x / rhs, this->y / rhs, this->z / rhs, this->w / rhs);
	}
	// 除算代入
	Vector4& operator/=(const float& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->w /= rhs;

		return *this;
	}

	// メンバ変数(同次座標でも色でも使える)
	union{
		struct{
			float x, y, z, w;
		};
		struct{
			float r, g, b, a;
		};
	};
};

//*****************************************************************************
// 4x4行列クラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
class Matrix4x4
{
public:

	Matrix4x4() :
	_11(1.0f), _12(0.0f), _13(0.0f), _14(0.0f),
	_21(0.0f), _22(1.0f), _23(0.0f), _24(0.0f),
	_31(0.0f), _32(0.0f), _33(1.0f), _34(0.0f),
	_41(0.0f), _42(0.0f), _43(0.0f), _44(1.0f)
	{}
	Matrix4x4(float _11, float _12, float _13, float _14,
			  float _21, float _22, float _23, float _24,
			  float _31, float _32, float _33, float _34,
			  float _41, float _42, float _43, float _44) :
	_11(_11), _12(_12), _13(_13), _14(_14),
	_21(_21), _22(_22), _23(_23), _24(_24),
	_31(_31), _32(_32), _33(_33), _34(_34),
	_41(_41), _42(_42), _43(_43), _44(_44)
	{}
	
	~Matrix4x4(){}

	// オーバーロード演算子
	// 加算
	Matrix4x4 operator+(const Matrix4x4& rhs) const
	{
		Matrix4x4 temp;

		temp._11 = this->_11 + rhs._11; temp._12 = this->_12 + rhs._12; temp._13 = this->_13 + rhs._13; temp._14 = this->_14 + rhs._14;
		temp._21 = this->_21 + rhs._21; temp._22 = this->_22 + rhs._22; temp._23 = this->_23 + rhs._23; temp._24 = this->_24 + rhs._24;
		temp._31 = this->_31 + rhs._31; temp._32 = this->_32 + rhs._32; temp._33 = this->_33 + rhs._33; temp._34 = this->_34 + rhs._34;
		temp._41 = this->_41 + rhs._41; temp._42 = this->_42 + rhs._42; temp._43 = this->_43 + rhs._43; temp._44 = this->_44 + rhs._44;

		return temp;
	}
	// 前置加算記号
	Matrix4x4 operator+() const
	{
		return *this;
	}
	// 加算代入
	Matrix4x4& operator+=(const Matrix4x4& rhs)
	{
		this->_11 = this->_11 + rhs._11; this->_12 = this->_12 + rhs._12; this->_13 = this->_13 + rhs._13; this->_14 = this->_14 + rhs._14;
		this->_21 = this->_21 + rhs._21; this->_22 = this->_22 + rhs._22; this->_23 = this->_23 + rhs._23; this->_24 = this->_24 + rhs._24;
		this->_31 = this->_31 + rhs._31; this->_32 = this->_32 + rhs._32; this->_33 = this->_33 + rhs._33; this->_34 = this->_34 + rhs._34;
		this->_41 = this->_41 + rhs._41; this->_42 = this->_42 + rhs._42; this->_43 = this->_43 + rhs._43; this->_44 = this->_44 + rhs._44;

		return *this;
	}
	// 減算
	Matrix4x4 operator-(const Matrix4x4& rhs) const
	{
		Matrix4x4 temp;

		temp._11 = this->_11 - rhs._11; temp._12 = this->_12 - rhs._12; temp._13 = this->_13 - rhs._13; temp._14 = this->_14 - rhs._14;
		temp._21 = this->_21 - rhs._21; temp._22 = this->_22 - rhs._22; temp._23 = this->_23 - rhs._23; temp._24 = this->_24 - rhs._24;
		temp._31 = this->_31 - rhs._31; temp._32 = this->_32 - rhs._32; temp._33 = this->_33 - rhs._33; temp._34 = this->_34 - rhs._34;
		temp._41 = this->_41 - rhs._41; temp._42 = this->_42 - rhs._42; temp._43 = this->_43 - rhs._43; temp._44 = this->_44 - rhs._44;

		return temp;
	}
	// 前置減算記号
	Matrix4x4 operator-() const
	{
		return Matrix4x4(-this->_11, -this->_12, -this->_13, -this->_14,
						 -this->_21, -this->_22, -this->_23, -this->_24,
						 -this->_31, -this->_32, -this->_33, -this->_34,
						 -this->_41, -this->_42, -this->_43, -this->_44);
	}
	// 減算代入
	Matrix4x4& operator-=(const Matrix4x4& rhs)
	{
		this->_11 = this->_11 - rhs._11; this->_12 = this->_12 - rhs._12; this->_13 = this->_13 - rhs._13; this->_14 = this->_14 - rhs._14;
		this->_21 = this->_21 - rhs._21; this->_22 = this->_22 - rhs._22; this->_23 = this->_23 - rhs._23; this->_24 = this->_24 - rhs._24;
		this->_31 = this->_31 - rhs._31; this->_32 = this->_32 - rhs._32; this->_33 = this->_33 - rhs._33; this->_34 = this->_34 - rhs._34;
		this->_41 = this->_41 - rhs._41; this->_42 = this->_42 - rhs._42; this->_43 = this->_43 - rhs._43; this->_44 = this->_44 - rhs._44;

		return *this;
	}
	// 積和演算
	Matrix4x4 operator*(const Matrix4x4& rhs) const
	{
		Matrix4x4 temp;

		temp._11 = this->_11 * rhs._11 + this->_12 * rhs._21 + this->_13 * rhs._31 + this->_14 * rhs._41;
		temp._12 = this->_11 * rhs._12 + this->_12 * rhs._22 + this->_13 * rhs._32 + this->_14 * rhs._42;
		temp._13 = this->_11 * rhs._13 + this->_12 * rhs._23 + this->_13 * rhs._33 + this->_14 * rhs._43;
		temp._14 = this->_11 * rhs._14 + this->_12 * rhs._24 + this->_13 * rhs._34 + this->_14 * rhs._44;
		
		temp._21 = this->_21 * rhs._11 + this->_22 * rhs._21 + this->_23 * rhs._31 + this->_24 * rhs._41;
		temp._22 = this->_21 * rhs._12 + this->_22 * rhs._22 + this->_23 * rhs._32 + this->_24 * rhs._42;
		temp._23 = this->_21 * rhs._13 + this->_22 * rhs._23 + this->_23 * rhs._33 + this->_24 * rhs._43;
		temp._24 = this->_21 * rhs._14 + this->_22 * rhs._24 + this->_23 * rhs._34 + this->_24 * rhs._44;
		
		temp._31 = this->_31 * rhs._11 + this->_32 * rhs._21 + this->_33 * rhs._31 + this->_34 * rhs._41;
		temp._32 = this->_31 * rhs._12 + this->_32 * rhs._22 + this->_33 * rhs._32 + this->_34 * rhs._42;
		temp._33 = this->_31 * rhs._13 + this->_32 * rhs._23 + this->_33 * rhs._33 + this->_34 * rhs._43;
		temp._34 = this->_31 * rhs._14 + this->_32 * rhs._24 + this->_33 * rhs._34 + this->_34 * rhs._44;
		
		temp._41 = this->_41 * rhs._11 + this->_42 * rhs._21 + this->_43 * rhs._31 + this->_44 * rhs._41;
		temp._42 = this->_41 * rhs._12 + this->_42 * rhs._22 + this->_43 * rhs._32 + this->_44 * rhs._42;
		temp._43 = this->_41 * rhs._13 + this->_42 * rhs._23 + this->_43 * rhs._33 + this->_44 * rhs._43;
		temp._44 = this->_41 * rhs._14 + this->_42 * rhs._24 + this->_43 * rhs._34 + this->_44 * rhs._44;

		return temp;
	}
	// 積和演算代入
	Matrix4x4& operator*=(const Matrix4x4& rhs)
	{
		float s11, s12, s13, s14;
		float s21, s22, s23, s24;
		float s31, s32, s33, s34;
		float s41, s42, s43, s44;

		s11 = this->_11 * rhs._11 + this->_12 * rhs._21 + this->_13 * rhs._31 + this->_14 * rhs._41;
		s12 = this->_11 * rhs._12 + this->_12 * rhs._22 + this->_13 * rhs._32 + this->_14 * rhs._42;
		s13 = this->_11 * rhs._13 + this->_12 * rhs._23 + this->_13 * rhs._33 + this->_14 * rhs._43;
		s14 = this->_11 * rhs._14 + this->_12 * rhs._24 + this->_13 * rhs._34 + this->_14 * rhs._44;
	
		s21 = this->_21 * rhs._11 + this->_22 * rhs._21 + this->_23 * rhs._31 + this->_24 * rhs._41;
		s22 = this->_21 * rhs._12 + this->_22 * rhs._22 + this->_23 * rhs._32 + this->_24 * rhs._42;
		s23 = this->_21 * rhs._13 + this->_22 * rhs._23 + this->_23 * rhs._33 + this->_24 * rhs._43;
		s24 = this->_21 * rhs._14 + this->_22 * rhs._24 + this->_23 * rhs._34 + this->_24 * rhs._44;
	
		s31 = this->_31 * rhs._11 + this->_32 * rhs._21 + this->_33 * rhs._31 + this->_34 * rhs._41;
		s32 = this->_31 * rhs._12 + this->_32 * rhs._22 + this->_33 * rhs._32 + this->_34 * rhs._42;
		s33 = this->_31 * rhs._13 + this->_32 * rhs._23 + this->_33 * rhs._33 + this->_34 * rhs._43;
		s34 = this->_31 * rhs._14 + this->_32 * rhs._24 + this->_33 * rhs._34 + this->_34 * rhs._44;
	
		s41 = this->_41 * rhs._11 + this->_42 * rhs._21 + this->_43 * rhs._31 + this->_44 * rhs._41;
		s42 = this->_41 * rhs._12 + this->_42 * rhs._22 + this->_43 * rhs._32 + this->_44 * rhs._42;
		s43 = this->_41 * rhs._13 + this->_42 * rhs._23 + this->_43 * rhs._33 + this->_44 * rhs._43;
		s44 = this->_41 * rhs._14 + this->_42 * rhs._24 + this->_43 * rhs._34 + this->_44 * rhs._44;

		this->_11 = s11; this->_12 = s12; this->_13 = s13; this->_14 = s14;
		this->_21 = s21; this->_22 = s22; this->_23 = s23; this->_24 = s24;
		this->_31 = s31; this->_32 = s32; this->_33 = s33; this->_34 = s34;
		this->_41 = s41; this->_42 = s42; this->_43 = s43; this->_44 = s44;

		return *this;
	}
	// スカラー乗算
	Matrix4x4 operator*(const float& rhs) const
	{
		Matrix4x4 temp;
		
		temp._11 = this->_11 * rhs; temp._12 = this->_12 * rhs; temp._13 = this->_13 * rhs; temp._14 = this->_14 * rhs;
		temp._21 = this->_21 * rhs; temp._22 = this->_22 * rhs; temp._23 = this->_23 * rhs; temp._24 = this->_24 * rhs;
		temp._31 = this->_31 * rhs; temp._32 = this->_32 * rhs; temp._33 = this->_33 * rhs; temp._34 = this->_34 * rhs;
		temp._41 = this->_41 * rhs; temp._42 = this->_42 * rhs; temp._43 = this->_43 * rhs; temp._44 = this->_44 * rhs;

		return temp;
	}
	// スカラー乗算代入
	Matrix4x4& operator*=(const float& rhs)
	{
		this->_11 *= rhs; this->_12 *= rhs; this->_13 *= rhs; this->_14 *= rhs;
		this->_21 *= rhs; this->_22 *= rhs; this->_23 *= rhs; this->_24 *= rhs;
		this->_31 *= rhs; this->_32 *= rhs; this->_33 *= rhs; this->_34 *= rhs;
		this->_41 *= rhs; this->_42 *= rhs; this->_43 *= rhs; this->_44 *= rhs;

		return *this;
	}
	// スカラー除算
	Matrix4x4 operator/(const float& rhs) const
	{
		Matrix4x4 temp;
		
		temp._11 = this->_11 / rhs; temp._12 = this->_12 / rhs; temp._13 = this->_13 / rhs; temp._14 = this->_14 / rhs;
		temp._21 = this->_21 / rhs; temp._22 = this->_22 / rhs; temp._23 = this->_23 / rhs; temp._24 = this->_24 / rhs;
		temp._31 = this->_31 / rhs; temp._32 = this->_32 / rhs; temp._33 = this->_33 / rhs; temp._34 = this->_34 / rhs;
		temp._41 = this->_41 / rhs; temp._42 = this->_42 / rhs; temp._43 = this->_43 / rhs; temp._44 = this->_44 / rhs;

		return temp;
	}
	// スカラー除算代入
	Matrix4x4& operator/=(const float& rhs)
	{
		this->_11 /= rhs; this->_12 /= rhs; this->_13 /= rhs; this->_14 /= rhs;
		this->_21 /= rhs; this->_22 /= rhs; this->_23 /= rhs; this->_24 /= rhs;
		this->_31 /= rhs; this->_32 /= rhs; this->_33 /= rhs; this->_34 /= rhs;
		this->_41 /= rhs; this->_42 /= rhs; this->_43 /= rhs; this->_44 /= rhs;

		return *this;
	}

	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;
};

//*****************************************************************************
// クォータニオンクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//*****************************************************************************
class Quaternion
{
public:

	Quaternion(){}
	Quaternion(float x, float y, float z, float w) :
	x(x), y(y), z(z), w(w){}

	~Quaternion(){}

	// 前置減算
	Quaternion operator-() const
	{
		return Quaternion(-this->x, -this->y, -this->z, -this->w);
	}
	// 乗算
	Quaternion operator*(const Quaternion& rhs) const
	{
		Quaternion temp;
		
		temp.w = this->w * rhs.w - (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z); 
		temp.x = this->w * rhs.x + rhs.w * this->x + this->y * rhs.z - this->z * rhs.y;
		temp.y = this->w * rhs.y + rhs.w * this->y + this->z * rhs.x - this->x * rhs.z;
		temp.z = this->w * rhs.z + rhs.w * this->z + this->x * rhs.y - this->y * rhs.x;

		return temp;
	}
	// 乗算代入
	Quaternion& operator*=(const Quaternion& rhs)
	{
		this->w = this->w * rhs.w - (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z); 
		this->x = this->w * rhs.x + rhs.w * this->x + this->y * rhs.z - this->z * rhs.y;
		this->y = this->w * rhs.y + rhs.w * this->y + this->z * rhs.x - this->x * rhs.z;
		this->z = this->w * rhs.z + rhs.w * this->z + this->x * rhs.y - this->y * rhs.x;

		return *this;
	}

	float x, y, z, w;
};

//*****************************************************************************
// 平面クラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//*****************************************************************************
class Plane
{
public:

	Plane(){}
	Plane(float a, float b, float c, float d) :
	a(a), b(b), c(c), d(d){}

	// 平面を定義する要素
	// 平面の方程式 ax + by + cz + d = 0
	float a, b, c, d;
};

//*****************************************************************************
// 座標軸で揃えられた矩形クラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
class AARect
{
public:

	AARect() : left(FLT_MAX), top(FLT_MAX), right(FLT_MIN), bottom(FLT_MIN){}

	AARect(float left, float top, float right, float bottom) :
	left(left), top(top), right(right), bottom(bottom){}

	// 矩形の中心点を返す
	Vector2 center(void) const { return Vector2((left + right) * 0.5f, (top + bottom) * 0.5f); }

	// 矩形の横幅を返す
	float width(void) const { return (right - left); }
	// 矩形の縦幅を返す
	float height(void) const { return (bottom - top); }

	float left, top, right, bottom;
};

//*****************************************************************************
// 座標軸で揃えられたバウンディングボックス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
class AABB
{
public:

	AABB() : Min(FLT_MAX, FLT_MAX, FLT_MAX), Max(FLT_MIN, FLT_MIN, FLT_MIN){}

	AABB(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) :
	Min(minX, minY, minZ), Max(maxX, maxY, maxZ){}

	AABB(Vector3 min, Vector3 max) : Min(min), Max(max){}

	~AABB(){}

	// ボックスの中心点を返す
	Vector3 center(void) const { return Vector3((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f, (Min.z + Max.z) * 0.5f); }

	// ボックスの各辺の長さを返す
	Vector3 size(void) const { return (Max - Min); }
	// X軸方向の長さを返す
	float width(void) const { return (Max.x - Min.x); }
	// Y軸方向の長さを返す
	float height(void) const { return (Max.y - Min.y); }
	// Z軸方向の長さを返す
	float depth(void) const { return (Max.z - Min.z); }

	// 指定したインデックス(0 ~ 7)からAABBの頂点を取得
	// 左手系と考え
	// Z軸を負から正の方向へ見た場合
	// (5)1----2(6)
	//    |    |
	//    |    |
	// (4)0----3(7)
	// という番号付けにする(即席で平面を作りたいとき以外あまり気にする必要はないかも)
	Vector3 corner(int nIndex) const
	{
		Vector3 temp(FLT_MAX, FLT_MAX, FLT_MAX);

		// インデックスが不正な値をさしていないか検査
		if(nIndex < 0 || nIndex >= 8)
		{
			// どうしようもない値を返す
			return temp;
		}

		// インデックスによって返す値を決める
		switch(nIndex)
		{
		case 0:
			{
				return Min;
			}
			break;
			
		case 1:
			{
				temp.x = Min.x; temp.y = Max.y; temp.z = Min.z;
			}
			break;

		case 2:
			{
				temp.x = Max.x; temp.y = Max.y; temp.z = Min.z;
			}
			break;

		case 3:
			{
				temp.x = Max.x; temp.y = Min.y; temp.z = Min.z;
			}
			break;

		case 4:
			{
				temp.x = Min.x; temp.y = Min.y; temp.z = Max.z;
			}
			break;

		case 5:
			{
				temp.x = Min.x; temp.y = Max.y; temp.z = Max.z;
			}
			break;

		case 6:
			{
				return Max;
			}
			break;
			
		case 7:
			{
				temp.x = Max.x; temp.y = Min.y; temp.z = Max.z;
			}
			break;

		default:
			break;
		}

		return temp;
	}

	// 頂点を追加(必要な分だけ拡張する)
	void add(const Vector3& pos)
	{
		if(Min.x > pos.x){ Min.x = pos.x; }
		if(Min.y > pos.y){ Min.y = pos.y; }
		if(Min.z > pos.z){ Min.z = pos.z; }
		if(Max.x < pos.x){ Max.x = pos.x; }
		if(Max.y < pos.y){ Max.y = pos.y; }
		if(Max.z < pos.z){ Max.z = pos.z; }
	}

	// AABBを追加(必要な分だけ拡張する)
	void add(const AABB& aabb)
	{
		if(Min.x > aabb.Min.x){ Min.x = aabb.Min.x; }
		if(Min.y > aabb.Min.y){ Min.y = aabb.Min.y; }
		if(Min.z > aabb.Min.z){ Min.z = aabb.Min.z; }
		if(Max.x < aabb.Max.x){ Max.x = aabb.Max.x; }
		if(Max.y < aabb.Max.y){ Max.y = aabb.Max.y; }
		if(Max.z < aabb.Max.z){ Max.z = aabb.Max.z; }
	}

	// ボックス最小値
	Vector3 Min;
	// ボックス最大値
	Vector3 Max;
};

/*****************************************************************************/
// x86系のプロセッサだった場合
#ifdef _M_IX86

//=============================================================================
// 超高速平方根計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
double inline __declspec (naked) __fastcall sqrtFast(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
}

//=============================================================================
// 超高速平方根計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float inline __declspec (naked) __fastcall sqrtFast(float n)
{
	_asm fld dword ptr [esp+4]
	_asm fsqrt
	_asm ret 4
}

//=============================================================================
// 超高速コサイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
double inline __declspec (naked) __fastcall cosFast(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fcos
	_asm ret 8
}

//=============================================================================
// 超高速コサイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float inline __declspec (naked) __fastcall cosFast(float n)
{
	_asm fld dword ptr [esp+4]
	_asm fcos
	_asm ret 4
}

//=============================================================================
// 超高速サイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
double inline __declspec (naked) __fastcall sinFast(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsin
	_asm ret 8
}

//=============================================================================
// 超高速サイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float inline __declspec (naked) __fastcall sinFast(float n)
{
	_asm fld dword ptr [esp+4]
	_asm fsin
	_asm ret 4
}

//=============================================================================
// 超高速タンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
double inline __declspec (naked) __fastcall tanFast(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fptan
	_asm fdivp ST(1), ST(0) 
	_asm ret 8
}

//=============================================================================
// 超高速タンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float inline __declspec (naked) __fastcall tanFast(float n)
{
	_asm fld dword ptr [esp+4]
	_asm fptan
	_asm fdivp ST(1), ST(0) ; //st1に正接が保存されてるのでst0の1.0で割ってスタックのトップに持ってくるよ
	_asm ret 4
}

//=============================================================================
// アークコサイン関数
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
double inline __declspec (naked) __fastcall acosFast(double n)
{
	_asm
	{
		fld qword ptr [esp+4]
		fmul st(0), st(0);		// 二乗
		fld1
		fsub st(0), st(1);		// 1 - 二乗
		fsqrt
		fld qword ptr [esp+4]
		fpatan
		ret 8
	}
}

//=============================================================================
// アークコサイン関数
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
float inline __declspec (naked) __fastcall acosFast(float n)
{
	_asm
	{
		fld dword ptr [esp+4]
		fmul st(0), st(0);		// 二乗
		fld1
		fsub st(0), st(1);		// 1 - 二乗
		fsqrt
		fld dword ptr [esp+4]
		fpatan
		ret 4
	}
}

//=============================================================================
// アークサイン関数
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
double inline __declspec (naked) __fastcall asinFast(double n)
{
	_asm
	{
		fld qword ptr [esp+4]
		fmul st(0), st(0);		// 二乗
		fld1
		fsub st(0), st(1);		// 1 - 二乗
		fsqrt
		fld qword ptr [esp+4]
		fxch
		fpatan
		ret 8
	}
}

//=============================================================================
// アークサイン関数
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
float inline __declspec (naked) __fastcall asinFast(float n)
{
	_asm
	{
		fld dword ptr [esp+4]
		fmul st(0), st(0);		// 二乗
		fld1
		fsub st(0), st(1);		// 1 - 二乗
		fsqrt
		fld dword ptr [esp+4]
		fxch
		fpatan
		ret 4
	}
}

//=============================================================================
// 超高速アークタンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
double inline __declspec (naked) __fastcall atanFast(double n)
{
	_asm
	{
		fld qword ptr [esp+4]
		fld1
		fpatan
		ret 8
	}
}

//=============================================================================
// 超高速アークタンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
float inline __declspec (naked) __fastcall atanFast(float n)
{
	_asm
	{
		fld dword ptr [esp+4]
		fld1
		fpatan
		ret 4
	}
}

//=============================================================================
// 超高速アークタンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
double inline _declspec (naked) __fastcall atan2Fast(double y, double x)
{
	_asm
	{
		fld qword ptr [esp+4]
		fld qword ptr [esp+12]
		fpatan
		ret 16
	}
}

//=============================================================================
// 超高速アークタンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
float inline _declspec (naked) __fastcall atan2Fast(float y, float x)
{
	_asm
	{
		fld dword ptr [esp+4]
		fld dword ptr [esp+8]
		fpatan
		ret 8
	}
}

#else	// それ以外のプロセッサの時
#include <math.h>
//=============================================================================
// 超高速平方根計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline double sqrtFast(double n)
{
	return sqrt(n);
}

//=============================================================================
// 超高速平方根計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline float sqrtFast(float n)
{
	return sqrtf(n);
}

//=============================================================================
// 超高速コサイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline double cosFast(double n)
{
	return cos(n);
}

//=============================================================================
// 超高速コサイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline float cosFast(float n)
{
	return cosf(n);
}

//=============================================================================
// 超高速サイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline double sinFast(double n)
{
	return sin(n);
}

//=============================================================================
// 超高速サイン計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline float sinFast(float n)
{
	return sinf(n);
}

//=============================================================================
// 超高速タンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline double tanFast(double n)
{
	return tan(n);
}

//=============================================================================
// 超高速タンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float tanFast(float n)
{
	return tanf(n);
}

//=============================================================================
// 超高速アークタンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline double atanFast(double y, double x)
{
	return atan2(y,x);
}

//=============================================================================
// 超高速アークタンジェント計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline float atanFast(float y, float x)
{
	return atan2f(y,x);
}

#endif

//*****************************************************************************
// 独自定義ベクトルマクロ定義
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
// ゼロベクトル
#define KB_VEC_ZERO		(Vector3(0.0f, 0.0f, 0.0f))

//=============================================================================
// 2Dベクトル内積
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/27
//=============================================================================
inline void Vector2Dot(float* pOut, const Vector2& vec0, const Vector2& vec1)
{
	*pOut = vec0.x * vec1.x + vec0.y * vec1.y;
}

//=============================================================================
// 2Dベクトル外積
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/27
//=============================================================================
inline void Vector2Cross(float* pOut, const Vector2& vec0, const Vector2& vec1)
{
	*pOut = vec0.x * vec1.y - vec0.y * vec1.x;
}

//=============================================================================
// ベクトル加算
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3Add(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
{
	pOut->x = vec0.x + vec1.x;
	pOut->y = vec0.y + vec1.y;
	pOut->z = vec0.z + vec1.z;
}

//=============================================================================
// ベクトル減算
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3Sub(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
{
	pOut->x = vec0.x - vec1.x;
	pOut->y = vec0.y - vec1.y;
	pOut->z = vec0.z - vec1.z;
}

//=============================================================================
// ベクトル正規化
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3Normalize(Vector3* pOut, const Vector3& vec0)
{
	float mag = (sqrtFast(vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z));
	// ゼロチェック
	if(mag <= 0.0f)
	{
		// 何もせずに返す
		return;
	}

	float OneOverMag = 1.0f / mag;

	pOut->x = vec0.x * OneOverMag;
	pOut->y = vec0.y * OneOverMag;
	pOut->z = vec0.z * OneOverMag;
}

//=============================================================================
// ベクトル内積計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3Dot(float* pOut, const Vector3& vec0, const Vector3& vec1)
{
	*pOut = vec0.x * vec1.x
		  + vec0.y * vec1.y
		  + vec0.z * vec1.z;
}

//=============================================================================
// ベクトル正規化と内積計算
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3NormalizeDot(float* pOut, const Vector3& vec0, const Vector3& vec1)
{
	float mag0 = (sqrtFast(vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z));
	float mag1 = (sqrtFast(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z));
	// ゼロ除算チェック
	if(mag0 <= 0 || mag1 <= 0)
	{
		// 何もしない
		return;
	}

	float OneOverMag0 = 1.0f / mag0;
	float OneOverMag1 = 1.0f / mag1;

	*pOut = vec0.x * OneOverMag0 * vec1.x * OneOverMag1
		  + vec0.y * OneOverMag0 * vec1.y * OneOverMag1
		  + vec0.z * OneOverMag0 * vec1.z * OneOverMag1;
}

//=============================================================================
// ベクトル外積計算(vec0からvec1回りに計算する)
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3Cross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
{
	pOut->x = vec0.y * vec1.z - vec0.z * vec1.y;
	pOut->y = vec0.z * vec1.x - vec0.x * vec1.z;
	pOut->z = vec0.x * vec1.y - vec0.y * vec1.x;
}

//=============================================================================
// ベクトル正規化と外積計算(vec0からvec1回りに計算する)
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3NormalizeCross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
{
	// 外積計算
	pOut->x = vec0.y * vec1.z - vec0.z * vec1.y;
	pOut->y = vec0.z * vec1.x - vec0.x * vec1.z;
	pOut->z = vec0.x * vec1.y - vec0.y * vec1.x;

	float mag = (sqrtFast(pOut->x * pOut->x + pOut->y * pOut->y + pOut->z * pOut->z));
	// ゼロチェック
	if(mag <= 0.0f)
	{
		// 何もせずに返す
		return;
	}

	float OneOverMag = 1.0f / mag;

	// 正規化
	pOut->x = pOut->x * OneOverMag;
	pOut->y = pOut->y * OneOverMag;
	pOut->z = pOut->z * OneOverMag;
}

//=============================================================================
// ベクトルの行列変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
inline void Vector3Transform(Vector4 *pOut, const Vector3& vec, const Matrix4x4& mtx)
{
	float x, y, z, w;
	x = vec.x * mtx._11 + vec.y * mtx._21 + vec.z * mtx._31 + mtx._41;
	y = vec.x * mtx._12 + vec.y * mtx._22 + vec.z * mtx._32 + mtx._42;
	z = vec.x * mtx._13 + vec.y * mtx._23 + vec.z * mtx._33 + mtx._43;
	w = vec.x * mtx._14 + vec.y * mtx._24 + vec.z * mtx._34 + mtx._44;
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
	pOut->w = w;
}

//=============================================================================
// 3D座標をw = 1に射影する変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
inline void Vector3TransformCoord(Vector3 *pOut, const Vector3& pos, const Matrix4x4& mtx)
{
	if(mtx._44 == 0.0f)
	{
		// 無限遠点
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;
		return;
	}
	float OneOverW = 1.0f / mtx._44;
	float x, y, z;
	x = (pos.x * mtx._11 + pos.y * mtx._21 + pos.z * mtx._31 + mtx._41) * OneOverW;
	y = (pos.x * mtx._12 + pos.y * mtx._22 + pos.z * mtx._32 + mtx._42) * OneOverW;
	z = (pos.x * mtx._13 + pos.y * mtx._23 + pos.z * mtx._33 + mtx._43) * OneOverW;
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
}

//=============================================================================
// 法線の変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
inline void Vector3TransformNormal(Vector3 *pOut, const Vector3& nor, const Matrix4x4& mtx)
{
	float x, y, z;
	x = nor.x * mtx._11 + nor.y * mtx._21 + nor.z * mtx._31;
	y = nor.x * mtx._12 + nor.y * mtx._22 + nor.z * mtx._32;
	z = nor.x * mtx._13 + nor.y * mtx._23 + nor.z * mtx._33;
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
}

//=============================================================================
// 壁擦りベクトル算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline void Vector3ScratchWall(Vector3 *pOut, const Vector3& in, const Vector3& normal)
{
	// inの逆ベクトルと法線の内積を取る
	float MinusInDotNormal = -(in.x * normal.x + in.y * normal.y + in.z * normal.z);

	// 壁擦りベクトル設定
	pOut->x = in.x + MinusInDotNormal * normal.x;
	pOut->y = in.y + MinusInDotNormal * normal.y;
	pOut->z = in.z + MinusInDotNormal * normal.z;
}

//=============================================================================
// 反射ベクトル算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline void Vector3Reflection(Vector3 *pOut, const Vector3& in, const Vector3& normal)
{
	// inの逆ベクトルと法線の内積を取る
	float MinusInDotNormal = -(in.x * normal.x + in.y * normal.y + in.z * normal.z);

	// 反射ベクトル設定
	float x, y, z;
	x = in.x + MinusInDotNormal * 2.0f * normal.x;
	y = in.y + MinusInDotNormal * 2.0f * normal.y;
	z = in.z + MinusInDotNormal * 2.0f * normal.z;
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
}

//=============================================================================
// 行列加算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void Matrix4x4Add(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
{
	pOut->_11 = m1._11 + m2._11; pOut->_12 = m1._12 + m2._12; pOut->_13 = m1._13 + m2._13; pOut->_14 = m1._14 + m2._14;
	pOut->_21 = m1._21 + m2._21; pOut->_22 = m1._22 + m2._22; pOut->_23 = m1._23 + m2._23; pOut->_24 = m1._24 + m2._24;
	pOut->_31 = m1._31 + m2._31; pOut->_32 = m1._32 + m2._32; pOut->_33 = m1._33 + m2._33; pOut->_34 = m1._34 + m2._34;
	pOut->_41 = m1._41 + m2._41; pOut->_42 = m1._42 + m2._42; pOut->_43 = m1._43 + m2._43; pOut->_44 = m1._44 + m2._44;
}

//=============================================================================
// 行列減算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void Matrix4x4Sub(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
{
	pOut->_11 = m1._11 - m2._11; pOut->_12 = m1._12 - m2._12; pOut->_13 = m1._13 - m2._13; pOut->_14 = m1._14 - m2._14;
	pOut->_21 = m1._21 - m2._21; pOut->_22 = m1._22 - m2._22; pOut->_23 = m1._23 - m2._23; pOut->_24 = m1._24 - m2._24;
	pOut->_31 = m1._31 - m2._31; pOut->_32 = m1._32 - m2._32; pOut->_33 = m1._33 - m2._33; pOut->_34 = m1._34 - m2._34;
	pOut->_41 = m1._41 - m2._41; pOut->_42 = m1._42 - m2._42; pOut->_43 = m1._43 - m2._43; pOut->_44 = m1._44 - m2._44;
}

//=============================================================================
// 行列乗算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void Matrix4x4Multiply(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
{
	float i11, i12, i13, i14,
		  i21, i22, i23, i24,
		  i31, i32, i33, i34,
		  i41, i42, i43, i44;

	i11 = m1._11 * m2._11 + m1._12 * m2._21 + m1._13 * m2._31 + m1._14 * m2._41;
	i12 = m1._11 * m2._12 + m1._12 * m2._22 + m1._13 * m2._32 + m1._14 * m2._42;
	i13 = m1._11 * m2._13 + m1._12 * m2._23 + m1._13 * m2._33 + m1._14 * m2._43;
	i14 = m1._11 * m2._14 + m1._12 * m2._24 + m1._13 * m2._34 + m1._14 * m2._44;
	
	i21 = m1._21 * m2._11 + m1._22 * m2._21 + m1._23 * m2._31 + m1._24 * m2._41;
	i22 = m1._21 * m2._12 + m1._22 * m2._22 + m1._23 * m2._32 + m1._24 * m2._42;
	i23 = m1._21 * m2._13 + m1._22 * m2._23 + m1._23 * m2._33 + m1._24 * m2._43;
	i24 = m1._21 * m2._14 + m1._22 * m2._24 + m1._23 * m2._34 + m1._24 * m2._44;
	
	i31 = m1._31 * m2._11 + m1._32 * m2._21 + m1._33 * m2._31 + m1._34 * m2._41;
	i32 = m1._31 * m2._12 + m1._32 * m2._22 + m1._33 * m2._32 + m1._34 * m2._42;
	i33 = m1._31 * m2._13 + m1._32 * m2._23 + m1._33 * m2._33 + m1._34 * m2._43;
	i34 = m1._31 * m2._14 + m1._32 * m2._24 + m1._33 * m2._34 + m1._34 * m2._44;
	
	i41 = m1._41 * m2._11 + m1._42 * m2._21 + m1._43 * m2._31 + m1._44 * m2._41;
	i42 = m1._41 * m2._12 + m1._42 * m2._22 + m1._43 * m2._32 + m1._44 * m2._42;
	i43 = m1._41 * m2._13 + m1._42 * m2._23 + m1._43 * m2._33 + m1._44 * m2._43;
	i44 = m1._41 * m2._14 + m1._42 * m2._24 + m1._43 * m2._34 + m1._44 * m2._44;

	pOut->_11 = i11; pOut->_12 = i12; pOut->_13 = i13; pOut->_14 = i14;
	pOut->_21 = i21; pOut->_22 = i22; pOut->_23 = i23; pOut->_24 = i24;
	pOut->_31 = i31; pOut->_32 = i32; pOut->_33 = i33; pOut->_34 = i34;
	pOut->_41 = i41; pOut->_42 = i42; pOut->_43 = i43; pOut->_44 = i44;
}

//=============================================================================
// 行列初期化
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Matrix4x4Identity(Matrix4x4 *pOut)
{
	pOut->_11 = pOut->_22 = pOut->_33 = pOut->_44 = 1.0f;
	pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = 0.0f;
}

//=============================================================================
// 行列転置
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Matrix4x4Transpose(Matrix4x4 *pOut, const Matrix4x4& mtxTrns)
{
	pOut->_11 = mtxTrns._11;
	pOut->_22 = mtxTrns._22;
	pOut->_33 = mtxTrns._33;
	pOut->_44 = mtxTrns._44;
	
	float i12, i13, i14,
		  i21, i23, i24,
		  i31, i32, i34,
		  i41, i42, i43;

	i12 = mtxTrns._21;
	i13 = mtxTrns._31;
	i14 = mtxTrns._41;
	i21 = mtxTrns._12;
	i23 = mtxTrns._32;
	i24 = mtxTrns._42;
	i31 = mtxTrns._13;
	i32 = mtxTrns._23;
	i34 = mtxTrns._43;
	i41 = mtxTrns._14;
	i42 = mtxTrns._24;
	i43 = mtxTrns._34;

	pOut->_12 = i12;
	pOut->_13 = i13;
	pOut->_14 = i14;
	pOut->_21 = i21;
	pOut->_23 = i23;
	pOut->_24 = i24;
	pOut->_31 = i31;
	pOut->_32 = i32;
	pOut->_34 = i34;
	pOut->_41 = i41;
	pOut->_42 = i42;
	pOut->_43 = i43;
}

//=============================================================================
// 行列式算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void Matrix4x4Determinant(float *pOut, const Matrix4x4& mtx)
{
	float i11 = mtx._11 * (
		mtx._33 * (mtx._22 * mtx._44 - mtx._24 * mtx._42) +
		mtx._34 * (mtx._23 * mtx._42 - mtx._22 * mtx._43) +
		mtx._32 * (mtx._24 * mtx._43 - mtx._23 * mtx._44));
	float i12 = mtx._12 * -(
		mtx._33 * (mtx._21 * mtx._44 - mtx._24 * mtx._41) +
		mtx._34 * (mtx._23 * mtx._41 - mtx._21 * mtx._43) +
		mtx._31 * (mtx._24 * mtx._43 - mtx._23 * mtx._44));
	float i13 = mtx._13 * (
		mtx._32 * (mtx._21 * mtx._44 - mtx._24 * mtx._41) +
		mtx._34 * (mtx._22 * mtx._41 - mtx._21 * mtx._42) +
		mtx._31 * (mtx._24 * mtx._42 - mtx._22 * mtx._44));
	float i14 = mtx._14 * -(
		mtx._32 * (mtx._21 * mtx._43 - mtx._23 * mtx._41) +
		mtx._33 * (mtx._22 * mtx._41 - mtx._21 * mtx._42) +
		mtx._31 * (mtx._23 * mtx._42 - mtx._22 * mtx._43));
	*pOut = i11 + i12 + i13 + i14;
}

//=============================================================================
// 逆行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void Matrix4x4Inverse(Matrix4x4 *pOut, const Matrix4x4& mtx)
{
	// 行列式取得
	float det;
	Matrix4x4Determinant(&det, mtx);
	// 行列式の値が非常に小さいとき、なにもしない
	if(det <= 0.000005f && det >= -0.000005f)
	{
		return;
	}

	// 行列式の逆数
	float invDet = 1.0f / det;
	// 余因子算出
	float i11 = 
		mtx._22 * mtx._33 * mtx._44 - mtx._24 * mtx._33 * mtx._42 +
		mtx._23 * mtx._34 * mtx._42 - mtx._22 * mtx._34 * mtx._43 +
		mtx._24 * mtx._32 * mtx._43 - mtx._23 * mtx._32 * mtx._44;
	float i12 = -(
		mtx._23 * mtx._34 * mtx._41 - mtx._21 * mtx._34 * mtx._43 +
		mtx._24 * mtx._31 * mtx._43 - mtx._23 * mtx._31 * mtx._44 +
		mtx._21 * mtx._33 * mtx._44 - mtx._24 * mtx._33 * mtx._41);
	float i13 =
		mtx._24 * mtx._31 * mtx._42 - mtx._22 * mtx._31 * mtx._44 +
		mtx._21 * mtx._32 * mtx._44 - mtx._24 * mtx._32 * mtx._41 +
		mtx._22 * mtx._34 * mtx._41 - mtx._21 * mtx._34 * mtx._42;
	float i14 = -(
		mtx._21 * mtx._32 * mtx._43 - mtx._23 * mtx._32 * mtx._41 +
		mtx._22 * mtx._33 * mtx._41 - mtx._21 * mtx._33 * mtx._42 +
		mtx._23 * mtx._31 * mtx._42 - mtx._22 * mtx._31 * mtx._43);
	float i21 = -(
		mtx._32 * mtx._43 * mtx._14 - mtx._34 * mtx._43 * mtx._12 +
		mtx._33 * mtx._44 * mtx._12 - mtx._32 * mtx._44 * mtx._13 +
		mtx._34 * mtx._42 * mtx._13 - mtx._33 * mtx._42 * mtx._14);
	float i22 = 
		mtx._33 * mtx._44 * mtx._11 - mtx._31 * mtx._44 * mtx._13 +
		mtx._34 * mtx._41 * mtx._13 - mtx._33 * mtx._41 * mtx._14 +
		mtx._31 * mtx._43 * mtx._14 - mtx._34 * mtx._43 * mtx._11;
	float i23 = -(
		mtx._34 * mtx._41 * mtx._12 - mtx._32 * mtx._41 * mtx._14 +
		mtx._31 * mtx._42 * mtx._14 - mtx._34 * mtx._42 * mtx._11 +
		mtx._32 * mtx._44 * mtx._11 - mtx._31 * mtx._44 * mtx._12);
	float i24 = 
		mtx._31 * mtx._42 * mtx._13 - mtx._33 * mtx._42 * mtx._11 +
		mtx._32 * mtx._43 * mtx._11 - mtx._31 * mtx._43 * mtx._12 +
		mtx._33 * mtx._41 * mtx._12 - mtx._32 * mtx._41 * mtx._13;
	float i31 = 
		mtx._42 * mtx._13 * mtx._24 - mtx._44 * mtx._13 * mtx._22 +
		mtx._43 * mtx._14 * mtx._22 - mtx._42 * mtx._14 * mtx._23 +
		mtx._44 * mtx._12 * mtx._23 - mtx._43 * mtx._12 * mtx._24;
	float i32 = -(
		mtx._43 * mtx._14 * mtx._21 - mtx._41 * mtx._14 * mtx._23 +
		mtx._44 * mtx._11 * mtx._23 - mtx._43 * mtx._11 * mtx._24 +
		mtx._41 * mtx._13 * mtx._24 - mtx._44 * mtx._13 * mtx._21);
	float i33 =
		mtx._44 * mtx._11 * mtx._22 - mtx._42 * mtx._11 * mtx._24 +
		mtx._41 * mtx._12 * mtx._24 - mtx._44 * mtx._12 * mtx._21 +
		mtx._42 * mtx._14 * mtx._21 - mtx._41 * mtx._14 * mtx._22;
	float i34 = -(
		mtx._41 * mtx._12 * mtx._23 - mtx._43 * mtx._12 * mtx._21 +
		mtx._42 * mtx._13 * mtx._21 - mtx._41 * mtx._13 * mtx._22 +
		mtx._43 * mtx._11 * mtx._22 - mtx._42 * mtx._11 * mtx._23);
	float i41 = -(	   
		mtx._12 * mtx._23 * mtx._34 - mtx._14 * mtx._23 * mtx._32 +
		mtx._13 * mtx._24 * mtx._32 - mtx._12 * mtx._24 * mtx._33 +
		mtx._14 * mtx._22 * mtx._33 - mtx._13 * mtx._22 * mtx._34);
	float i42 = 	   			 		   			 		   
		mtx._13 * mtx._24 * mtx._31 - mtx._11 * mtx._24 * mtx._33 +
		mtx._14 * mtx._21 * mtx._33 - mtx._13 * mtx._21 * mtx._34 +
		mtx._11 * mtx._23 * mtx._34 - mtx._14 * mtx._23 * mtx._31;
	float i43 = -(
		mtx._14 * mtx._21 * mtx._32 - mtx._12 * mtx._21 * mtx._34 +
		mtx._11 * mtx._22 * mtx._34 - mtx._14 * mtx._22 * mtx._31 +
		mtx._12 * mtx._24 * mtx._31 - mtx._11 * mtx._24 * mtx._32);
	float i44 = 
		mtx._11 * mtx._22 * mtx._33 - mtx._13 * mtx._22 * mtx._31 +
		mtx._12 * mtx._23 * mtx._31 - mtx._11 * mtx._23 * mtx._32 +
		mtx._13 * mtx._21 * mtx._32 - mtx._12 * mtx._21 * mtx._33;

	// 逆行列設定
	pOut->_11 = i11 * invDet;
	pOut->_12 = i21 * invDet;
	pOut->_13 = i31 * invDet;
	pOut->_14 = i41 * invDet;
	pOut->_21 = i12 * invDet;
	pOut->_22 = i22 * invDet;
	pOut->_23 = i32 * invDet;
	pOut->_24 = i42 * invDet;
	pOut->_31 = i13 * invDet;
	pOut->_32 = i23 * invDet;
	pOut->_33 = i33 * invDet;
	pOut->_34 = i43 * invDet;
	pOut->_41 = i14 * invDet;
	pOut->_42 = i24 * invDet;
	pOut->_43 = i34 * invDet;
	pOut->_44 = i44 * invDet;
}

//=============================================================================
// スケール行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/8
//=============================================================================
inline void Matrix4x4Scaling(Matrix4x4 *pOut, const float& sx, const float &sy, const float& sz)
{
	pOut->_11 *= sx; pOut->_12 *= sx; pOut->_13 *= sx;
	pOut->_21 *= sy; pOut->_22 *= sy; pOut->_23 *= sy;
	pOut->_31 *= sz; pOut->_32 *= sz; pOut->_33 *= sz;
}

//=============================================================================
// YawPitchRoll回転行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/8
//=============================================================================
inline void Matrix4x4YawPitchRoll(Matrix4x4 *pOut, const float& pitch, const float& yaw, const float& roll)
{
	float CosP = cosFast(pitch);
	float CosY = cosFast(yaw);
	float CosR = cosFast(roll);
	float SinP = sinFast(pitch);
	float SinY = sinFast(yaw);
	float SinR = sinFast(roll);

	pOut->_11 = CosY * CosR - SinP * SinY * SinR;
	pOut->_12 = CosY * SinR + SinP * SinY * CosR;
	pOut->_13 = -CosP * SinY;
	pOut->_21 = -CosP * SinR;
	pOut->_22 = CosP * CosR;
	pOut->_23 = SinP;
	pOut->_31 = SinY * CosR + CosY * SinP * SinR;
	pOut->_32 = SinY * SinR - CosY * SinP * CosR;
	pOut->_33 = CosY * CosP;
}

//=============================================================================
// 平行移動行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/8
//=============================================================================
inline void Matrix4x4Translation(Matrix4x4 *pOut, const float& tx, const float& ty, const float& tz)
{
	pOut->_41 = tx;
	pOut->_42 = ty;
	pOut->_43 = tz;
}

//=============================================================================
// 任意軸回転行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//=============================================================================
inline void Matrix4x4RotationArbitraryAxis(Matrix4x4 *pOut, const Vector3& axis, const float& angle)
{
	float AxisXMulAxisY = axis.x * axis.y;
	float AxisXMulAxisZ = axis.x * axis.z;
	float AxisYMulAxisZ = axis.y * axis.z;
	float cosAngle = cosFast(angle);
	float OneMinusCosAngle = 1 - cosAngle;
	float sinAngle = sinFast(angle);
	float AxisXMulSinAngle = axis.x * sinAngle;
	float AxisYMulSinAngle = axis.y * sinAngle;
	float AxisZMulSinAngle = axis.z * sinAngle;

	pOut->_11 = axis.x * axis.x * OneMinusCosAngle +          cosAngle;
	pOut->_12 = AxisXMulAxisY   * OneMinusCosAngle +  AxisZMulSinAngle;
	pOut->_13 = AxisXMulAxisZ   * OneMinusCosAngle -  AxisYMulSinAngle;
	pOut->_21 = AxisXMulAxisY   * OneMinusCosAngle -  AxisZMulSinAngle;
	pOut->_22 = axis.y * axis.y * OneMinusCosAngle +          cosAngle;
	pOut->_23 = AxisYMulAxisZ   * OneMinusCosAngle +  AxisXMulSinAngle;
	pOut->_31 = AxisXMulAxisZ   * OneMinusCosAngle +  AxisYMulSinAngle;
	pOut->_32 = AxisYMulAxisZ   * OneMinusCosAngle -  AxisXMulSinAngle;
	pOut->_33 = axis.z * axis.z * OneMinusCosAngle +          cosAngle;

	pOut->_14 = pOut->_24 = pOut->_34 =
	pOut->_41 = pOut->_42 = pOut->_43 = 0.0f;
	pOut->_44 = 1.0f;
}

//=============================================================================
// 行列からオイラー角に変換(yaw, pitch, roll順)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
inline void Matrix4x4ToEulerAngle(Vector3 *pOut, const Matrix4x4& mtx)
{
	float sinPitch = mtx._23;
	// asinが不正な値にならないようにする
	if(sinPitch <= -1.0f)
	{
		pOut->x = -static_cast<float>(KB_PI) * 0.5f;
	}
	else if(sinPitch >= 1.0f)
	{
		pOut->x = static_cast<float>(KB_PI) * 0.5f;
	}
	else
	{
		pOut->x = asinFast(sinPitch);
	}

	// ジンバルロックを考慮
	if(fabs(sinPitch) > 0.99999f)
	{
		// cos(Pitch)を0と仮定して計算
		// ロールかヘディングを0に設定してどちらかを計算
		pOut->z = 0.0f;
		pOut->y = atan2Fast(mtx._31, mtx._11);
	}
	else
	{
		pOut->y = atan2Fast(-mtx._13, mtx._33);
		pOut->z = atan2Fast(-mtx._21, mtx._22);
	}
}

//=============================================================================
// 行列からクォータニオンに変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/21
//=============================================================================
inline void Matrix4x4ToQuaternion(Quaternion* pOut, const Matrix4x4& mtx)
{
	// 結果を安定させるため、wxyzのいずれかの値の絶対値の最大のものを取る
	// 行列の対角を操作したものを使用
	// すごい名前だが、モノを正確に表す
	float FourWSquaredMinusOne =  mtx._11 + mtx._22 + mtx._33;
	float FourXSquaredMinusOne =  mtx._11 - mtx._22 - mtx._33;
	float FourYSquaredMinusOne = -mtx._11 + mtx._22 - mtx._33;
	float FourZSquaredMinusOne = -mtx._11 - mtx._22 + mtx._33;

	// 選択された処理に分岐する
	// Index
	// w:0 x:1 y:2 z:3
	int BiggestIndex = 0;
	// 一番大きい値を選択
	float BiggestNumber = FourWSquaredMinusOne;
	if(BiggestNumber < FourXSquaredMinusOne)
	{
		BiggestIndex = 1;
		BiggestNumber = FourXSquaredMinusOne;
	}
	else if(BiggestNumber < FourYSquaredMinusOne)
	{
		BiggestIndex = 2;
		BiggestNumber = FourYSquaredMinusOne;
	}
	else if(BiggestNumber < FourZSquaredMinusOne)
	{
		BiggestIndex = 3;
		BiggestNumber = FourZSquaredMinusOne;
	}

	// 最大値
	float BiggestValue = sqrtFast(BiggestNumber + 1) * 0.5f;
	// 行列の各要素にかけて値を算出するクォータニオンの値を算出する
	float mult = 0.25f / BiggestValue;
	// 場合によって計算方法を変える
	switch(BiggestIndex)
	{
		// 一番大きい値がW
	case 0:
		{
			pOut->w = BiggestValue;
			pOut->x = (mtx._23 - mtx._32) * mult;
			pOut->y = (mtx._31 - mtx._13) * mult;
			pOut->z = (mtx._12 - mtx._21) * mult;
		}
		break;
		
		// 一番大きい値がX
	case 1:
		{
			pOut->x = BiggestValue;
			pOut->w = (mtx._23 - mtx._32) * mult;
			pOut->y = (mtx._12 + mtx._21) * mult;
			pOut->z = (mtx._31 + mtx._13) * mult;
		}
		break;
		
		// 一番大きい値がY
	case 2:
		{
			pOut->y = BiggestValue;
			pOut->w = (mtx._31 - mtx._13) * mult;
			pOut->x = (mtx._12 + mtx._21) * mult;
			pOut->z = (mtx._23 + mtx._32) * mult;
		}
		break;
		
		// 一番大きい値がZ
	case 3:
		{
			pOut->z = BiggestValue;
			pOut->w = (mtx._12 - mtx._21) * mult;
			pOut->x = (mtx._31 + mtx._13) * mult;
			pOut->y = (mtx._23 + mtx._32) * mult;
		}
		break;
	}
}

//=============================================================================
// 行列を拡大、回転、平行移動成分に分解
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/18
//=============================================================================
inline void Matrix4x4Decompose(Vector3* pTrans, Quaternion* pRot, Vector3* pScale, const Matrix4x4& mtx)
{
	// 平行移動成分
	pTrans->x = mtx._41;
	pTrans->y = mtx._42;
	pTrans->z = mtx._43;

	// 拡縮成分
	float sx = sqrtFast(mtx._11 * mtx._11 + mtx._12 * mtx._12 + mtx._13 * mtx._13);
	float sy = sqrtFast(mtx._21 * mtx._21 + mtx._22 * mtx._22 + mtx._23 * mtx._23);
	float sz = sqrtFast(mtx._31 * mtx._31 + mtx._32 * mtx._32 + mtx._33 * mtx._33);
	pScale->x = sx;
	pScale->y = sy;
	pScale->z = sz;

	// 回転(軸)成分
	Matrix4x4ToQuaternion(pRot, mtx);
}

//=============================================================================
// クォータニオン乗算
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionMultiply(Quaternion *pOut, const Quaternion& q1, const Quaternion& q2)
{
	float w, x, y, z;
	w = q1.w * q2.w - (q1.x * q2.x + q1.y * q2.y + q1.z * q2.z); 
	x = q1.w * q2.x + q2.w * q1.x + q1.y * q2.z - q1.z * q2.y;
	y = q1.w * q2.y + q2.w * q1.y + q1.z * q2.x - q1.x * q2.z;
	z = q1.w * q2.z + q2.w * q1.z + q1.x * q2.y - q1.y * q2.x;
	pOut->w = w;
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
}

//=============================================================================
// クォータニオン内積
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionDot(float* pOut, const Quaternion& q1, const Quaternion& q2)
{
	*pOut = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

//=============================================================================
// 恒等クォータニオン作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionIdentity(Quaternion *pOut)
{
	pOut->x = pOut->y = pOut->z = 0;
	pOut->w = 1.0f;
}

//=============================================================================
// クォータニオン正規化
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionNormalize(Quaternion *pOut, const Quaternion& q)
{
	float mag = sqrtFast(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if(mag <= 0.0f)
	{
		return;
	}
	float invMag = 1.0f / mag;
	pOut->x = q.x * invMag;
	pOut->y = q.y * invMag;
	pOut->z = q.z * invMag;
	pOut->w = q.w * invMag;
}

//=============================================================================
// 共役クォータニオン作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionConjugate(Quaternion *pOut, const Quaternion& q)
{
	pOut->x = -q.x;
	pOut->y = -q.y;
	pOut->z = -q.z;
	pOut->w = q.w;
}

//=============================================================================
// 逆クォータニオン(共役して正規化されたクォータニオン)作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionInverse(Quaternion *pOut, const Quaternion& q)
{
	float mag = sqrtFast(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
	if(mag <= 0.0f)
	{
		return;
	}
	float invMag = 1.0f / mag;
	pOut->x = -q.x * invMag;
	pOut->y = -q.y * invMag;
	pOut->z = -q.z * invMag;
	pOut->w = q.w * invMag;
}

//=============================================================================
// 指定した軸でクォータニオンを設定
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionRotationAxis(Quaternion *pOut, const Vector3& axis, float angle)
{
	pOut->x = axis.x * sinFast(angle * 0.5f);
	pOut->y = axis.y * sinFast(angle * 0.5f);
	pOut->z = axis.z * sinFast(angle * 0.5f);
	pOut->w = cosFast(angle * 0.5f);
}

//=============================================================================
// 指定した2つの正規化されたクォータニオンの球面線形補間
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionSlerp(Quaternion *pOut, const Quaternion& q0, const Quaternion& q1, float t)
{
	// ベクトルの線形結合を利用
	// クォータニオンの間の角度を算出
	// クォータニオンの軸の内積
	float cosTheta = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;

	// 内積(cos)が負のとき、一方を逆にして、最短距離を取るようにする
	Quaternion temp;
	if(cosTheta < 0.0f)
	{
		temp.w = -q1.w;
		temp.x = -q1.x;
		temp.y = -q1.y;
		temp.z = -q1.z;
		cosTheta = -cosTheta;
	}
	else
	{
		temp.w = q1.w;
		temp.x = q1.x;
		temp.y = q1.y;
		temp.z = q1.z;
	}

	// ベクトルを利用した球面線形補間
	float k0, k1;

	// 二つのクォータニオンが密接していた場合
	if(cosTheta >= 0.9999f)
	{
		// ただの線形補間にする
		k0 = 1 - t;
		k1 = t;
	}
	else
	{
		// sinを算出
		float sinTheta = sqrtFast(1.0f - cosTheta * cosTheta);

		// sinとcosから角度を算出
		float theta = atan2Fast(sinTheta, cosTheta);

		// 分母の逆数を計算しておく
		float OneOverSinTheta = 1.0f / sinTheta;

		// クォータニオン補間係数算出
		k0 = sinFast((1 - t) * theta) * OneOverSinTheta;
		k1 = sinFast(t * theta) * OneOverSinTheta;
	}

	// 補間したクォータニオン算出
	pOut->w = k0 * q0.w + k1 * q1.w;
	pOut->x = k0 * q0.x + k1 * q1.x;
	pOut->y = k0 * q0.y + k1 * q1.y;
	pOut->z = k0 * q0.z + k1 * q1.z;
}

//=============================================================================
// オイラー角からクォータニオンへの変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
inline void EulerAngleToQuaternion(Quaternion *pOut, const Vector3& rot)
{
	float pitchOverTwo = rot.x * 0.5f;
	float yawOverTwo   = rot.y * 0.5f;
	float rollOverTwo  = rot.z * 0.5f;

	float cosPitchOverTwo = cosFast(pitchOverTwo);
	float cosYawOverTwo   = cosFast(yawOverTwo);
	float cosRollOverTwo  = cosFast(rollOverTwo);
	float sinPitchOverTwo = sinFast(pitchOverTwo);
	float sinYawOverTwo   = sinFast(yawOverTwo);
	float sinRollOverTwo  = sinFast(rollOverTwo);

	pOut->w = cosYawOverTwo * cosPitchOverTwo * cosRollOverTwo + sinYawOverTwo * sinPitchOverTwo * sinRollOverTwo;
	pOut->x = cosYawOverTwo * sinPitchOverTwo * cosRollOverTwo + sinYawOverTwo * cosPitchOverTwo * sinRollOverTwo;
	pOut->y = sinYawOverTwo * cosPitchOverTwo * cosRollOverTwo - cosYawOverTwo * sinPitchOverTwo * sinRollOverTwo;
	pOut->z = cosYawOverTwo * cosPitchOverTwo * sinRollOverTwo - sinYawOverTwo * sinPitchOverTwo * cosRollOverTwo;
}

//=============================================================================
// クォータニオンからオイラー角に変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
inline void QuaternionToEulerAngle(Vector3 *pOut, const Quaternion& q)
{
	// 行列の要素に変換してからオイラー角に変換する
	float sinPitch = -2.0f * (q.y * q.z - q.w * q.x);

	// ジンバルロックを考慮
	if(fabs(sinPitch) > 0.99999f)
	{
		// 真上か真下に固定
		pOut->x = static_cast<float>(KB_PI) * 0.5f;

		// とりあえずロールを0に設定
		pOut->y = atan2Fast(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
		pOut->z = 0.0f;
	}
	else
	{
		// 普通に角度を計算する
		pOut->x = asinFast(sinPitch);
		pOut->y = atan2Fast(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		pOut->z = atan2Fast(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}
}

//=============================================================================
// クォータニオンから行列に変換
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
inline void QuaternionToMatrix4x4(Matrix4x4 *pOut, const Quaternion& q)
{
	float XxX = q.x * q.x;
	float YxY = q.y * q.y;
	float ZxZ = q.z * q.z;
	float XxY = q.x * q.y;
	float XxZ = q.x * q.z;
	float YxZ = q.y * q.z;
	float WxX = q.w * q.x;
	float WxY = q.w * q.y;
	float WxZ = q.w * q.z;

	pOut->_11 = 1.0f - 2.0f * (YxY + ZxZ);
	pOut->_12 =        2.0f * (XxY + WxZ);
	pOut->_13 =        2.0f * (XxZ - WxY);
	pOut->_21 =        2.0f * (XxY - WxZ);
	pOut->_22 = 1.0f - 2.0f * (XxX + ZxZ);
	pOut->_23 =        2.0f * (YxZ + WxX);
	pOut->_31 =        2.0f * (XxZ + WxY);
	pOut->_32 =        2.0f * (YxZ - WxX);
	pOut->_33 = 1.0f - 2.0f * (XxX + YxY);

	pOut->_14 = pOut->_24 = pOut->_34 = 
	pOut->_41 = pOut->_42 = pOut->_43 = 0.0f;
	pOut->_44 = 1.0f;
}

//=============================================================================
// 指定した座標を任意軸で回転
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/29
//=============================================================================
inline void Vector3RotationAxis(Vector3* pOut, const Vector3& pos, const Vector3& axis, const float& angle)
{
	Quaternion src, rotQ, rotQconj, temp, dest;

	// 座標をクォータニオンに変換
	src.x = pos.x;
	src.y = pos.y;
	src.z = pos.z;
	src.w = 0.0f;

	// 回転クォータニオン作成
	QuaternionRotationAxis(&rotQ, axis, angle);
	// 共役作成
	rotQconj.x = -rotQ.x;
	rotQconj.y = -rotQ.y;
	rotQconj.z = -rotQ.z;
	rotQconj.w = rotQ.w;

	// (q^-1)src
	QuaternionMultiply(&temp, rotQconj, src);
	// (q^-1)src(q)
	QuaternionMultiply(&dest, temp, rotQ);

	// destのxyz成分がそのまま座標になっている。便利
	pOut->x = dest.x;
	pOut->y = dest.y;
	pOut->z = dest.z;
}

//=============================================================================
// 平面を正規化する
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//=============================================================================
inline void PlaneNormalize(Plane *pOut, const Plane& pl)
{
	float mag = sqrtFast(pl.a * pl.a + pl.b * pl.b + pl.c * pl.c);

	if(mag <= 0.0f){ return; }

	float OneOverMag = 1.0f / mag;

	pOut->a = pl.a * OneOverMag;
	pOut->b = pl.b * OneOverMag;
	pOut->c = pl.c * OneOverMag;
	pOut->d = pl.d * OneOverMag;
}

//=============================================================================
// 平面と点の境界判定
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//=============================================================================
inline void PlaneDotVector3(float *pOut, const Plane& pl, const Vector3& point)
{
	*pOut = pl.a * point.x + pl.b * point.y + pl.c * point.z + pl.d;
}

//=============================================================================
// 点と法線から平面を算出する
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//=============================================================================
inline void PlaneFromPointNormal(Plane *pOut, const Vector3& p, const Vector3& nor)
{
	// 平面の原点との距離を求める
	pOut->d = -(p.x * nor.x + p.y * nor.y + p.z * nor.z);

	// 各要素を設定
	pOut->a = nor.x;
	pOut->b = nor.y;
	pOut->c = nor.z;
}

//=============================================================================
// 3点から平面を算出する(p1 - p0 > p2 - p0 回り)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//=============================================================================
inline void PlaneFromPoints(Plane *pOut, const Vector3& p0, const Vector3& p1, const Vector3& p2)
{
	float x0 = p1.x - p0.x;
	float y0 = p1.y - p0.y;
	float z0 = p1.z - p0.z;
	float x1 = p2.x - p0.x;
	float y1 = p2.y - p0.y;
	float z1 = p2.z - p0.z;
	// 法線を求める
	pOut->a = y0 * z1 - z0 * y1;
	pOut->b = z0 * x1 - x0 * z1;
	pOut->c = x0 * y1 - y0 * x1;
	// 原点と面の距離
	pOut->d = -(pOut->a * p0.x + pOut->b * p0.y + pOut->c * p0.z);

	// 平面正規化
	float mag = sqrtFast(pOut->a * pOut->a + pOut->b * pOut->b + pOut->c * pOut->c);

	if(mag <= 0.0f){ return; }

	float OneOverMag = 1.0f / mag;

	pOut->a = pOut->a * OneOverMag;
	pOut->b = pOut->b * OneOverMag;
	pOut->c = pOut->c * OneOverMag;
	pOut->d = pOut->d * OneOverMag;
}

//=============================================================================
// 平面の回転
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline void PlaneRotation(Plane *pOut, const Plane& pl, const Matrix4x4& rot)
{
}

//=============================================================================
// 平面と光線の交差した座標
// Author : Ryo Kbayashi
// LastUpdate : 2014/5/12
//
// ret		: bool true:当たり false:はずれ
//=============================================================================
inline bool PlaneRayIntersect(Vector3 *pOut, const Plane& pl, const Vector3& pos, const Vector3& ray)
{
	// 式で表すと
	// (pos + ray * k) DOT pl.normal = -pl.d
	// これを k について解く
	// pOutに入る値は pos + ray * k となる

	// 光線と平面の法線の内積を取る
	float RayDotPlaneNormal = ray.x * pl.a + ray.y * pl.b + ray.z * pl.c;
	// 算出する値k
	float k;
	// 内積が限りなくゼロに近いとき
	if(RayDotPlaneNormal >= -0.000005f && RayDotPlaneNormal <= 0.000005f)
	{
		// 交差した場所を無限(float最大値)
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;

		// 光線の始点が平面上にあるとき、当たり
		if((pos.x * pl.a + pos.y * pl.b + pos.z * pl.c + pl.d) == 0.0f)
		{
			return true;
		}
	}
	else
	{
		// 上記の式を展開
		k = (-pl.d - (pos.x * pl.a + pos.y * pl.b + pos.z * pl.c)) / RayDotPlaneNormal;

		// 交差点を算出
		pOut->x = pos.x + ray.x * k;
		pOut->y = pos.y + ray.y * k;
		pOut->z = pos.z + ray.z * k;

		// kがプラス以上のとき、rayの向いている方向に面があるので、当たり
		if(k >= 0)
		{
			return true;
		}
	}

	// はずれ
	return false;
}

//=============================================================================
// 平面と線分の交差した座標
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline bool PlaneLineSegmentIntersect(Vector3 *pOut, const Plane& pln, const Vector3& p0, const Vector3& p1)
{
	// 平面と線分の交差は
	// (start + (end - start) * k) DOT pln.normal = -pln.d となる
	// これを k について解く

	// p0とp1が面の表か裏のどちらにあるか調べる
	float Point0FrontBack, Point1FrontBack;
	PlaneDotVector3(&Point0FrontBack, pln, p0);
	PlaneDotVector3(&Point1FrontBack, pln, p1);
	// p0とp1が面上に存在するフラグ
	bool Point0IsOnFace = (Point0FrontBack >= -0.000005f && Point0FrontBack <= 0.000005f);
	bool Point1IsOnFace = (Point1FrontBack >= -0.000005f && Point1FrontBack <= 0.000005f);
	
	// 線分ベクトル
	float SegX = p1.x - p0.x;
	float SegY = p1.y - p0.y;
	float SegZ = p1.z - p0.z;
	// 線分ベクトルの長さを取る
	float SegMag = sqrtFast(SegX * SegX + SegY * SegY + SegZ * SegZ);

	// p0とp1がほぼ一致していた場合
	if(SegMag >= -0.000005f && SegMag <= 0.000005f)
	{
		// 点が面上に存在した場合
		if(Point0IsOnFace){ *pOut = p0; return true; }
		// 面上に存在しない場合
		// 交差した場所を無限(float最大値)
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;
		// はずれ
		return false;
	}

	// 線分ベクトルの始点
	Vector3 StartPoint = p0;
	// 線分ベクトルと面の法線の内積を取る
	float SegDotPlaneNormal = SegX * pln.a + SegY * pln.b + SegZ * pln.c;

	// 線分と面がほぼ平行な時
	if(SegDotPlaneNormal >= -0.000005f && SegDotPlaneNormal <= 0.000005f)
	{
		// 交差した場所を無限(float最大値)
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;

		// p0とp1が面上に存在するフラグ
		bool Point0IsOnFace = (Point0FrontBack >= -0.000005f && Point0FrontBack <= 0.000005f);
		bool Point1IsOnFace = (Point1FrontBack >= -0.000005f && Point1FrontBack <= 0.000005f);

		// 線分の端のどちらか平面上にあるとき、当たり
		// p0とp1が両方とも面上にある
		if(Point0IsOnFace &&
			Point1IsOnFace)
		{
			return true;
		}
		// p0が平面上にある
		else if(Point0IsOnFace)
		{
			*pOut = p0;
			return true;
		}
		// p1が平面上にある
		else if(Point1IsOnFace)
		{
			*pOut = p1;
			return true;
		}
	}
	else
	{
		// 線分ベクトルと面の法線の内積がプラスだったとき
		// ベクトルが面と同じ方向を向いてるので、反対にして面と向き合うようにする
		if(SegDotPlaneNormal > 0.0f)
		{
			// 内積の結果を逆にする
			SegDotPlaneNormal = -SegDotPlaneNormal;
			// 線分ベクトルを逆向きにする
			SegX = -SegX;
			SegY = -SegY;
			SegZ = -SegZ;
			// 線分ベクトルの始点を変える
			StartPoint = p1;
		}
		// k について解く
		float StartPointDotNormal = (StartPoint.x * pln.a + StartPoint.y * pln.b + StartPoint.z * pln.c);
		float k = (-pln.d - StartPointDotNormal) / SegDotPlaneNormal;

		// k が 0.0以上、1.0以下のとき線分の間に面が存在するのであたり
		if(k >= 0.0f && k <= 1.0f)
		{
			// 交差した座標設定
			pOut->x = StartPoint.x + SegX * k;
			pOut->y = StartPoint.y + SegY * k;
			pOut->z = StartPoint.z + SegZ * k;
			// 当たり
			return true;
		}
		// k が 0.0より小さく、1.0より大きいとき線分の間に面が存在しないのではずれ
		else
		{
			// 交差した場所を無限(float最大値)
			pOut->x = FLT_MAX;
			pOut->y = FLT_MAX;
			pOut->z = FLT_MAX;
		}
	}

	// はずれ
	return false;
}

//=============================================================================
// ワールド行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/23
//=============================================================================
inline void SetWorldMatrix(Matrix4x4 *pOut, const Vector3 &trans, const Vector3 &rot, const Vector3 &scl)
{
	// 変数宣言
	float CosX = cosFast(rot.x);
	float SinX = sinFast(rot.x);
	float CosY = cosFast(rot.y);
	float SinY = sinFast(rot.y);
	float CosZ = cosFast(rot.z);
	float SinZ = sinFast(rot.z);

	// 行列要素設定
	pOut->_11 = (CosY * CosZ - SinY * SinX * SinZ) * scl.x;
	pOut->_12 = (CosY * SinZ + SinY * SinX * CosZ) * scl.x;
	pOut->_13 = (-SinY * CosX) * scl.x;

	pOut->_21 = (-CosX * SinZ) * scl.y;
	pOut->_22 = (CosX * CosZ) * scl.y;
	pOut->_23 = SinX * scl.y;

	pOut->_31 = (SinY * CosZ + CosY * SinX * SinZ) * scl.z;
	pOut->_32 = (SinY * SinZ - CosY * SinX * CosZ) * scl.z;
	pOut->_33 = (CosY * CosX) * scl.z;

	pOut->_41 = trans.x;
	pOut->_42 = trans.y;
	pOut->_43 = trans.z;

	pOut->_14 = pOut->_24 = pOut->_34 = 0.0f;
	pOut->_44 = 1.0f;
}

//=============================================================================
// ワールド逆行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void SetWorldInverseMatrix(Matrix4x4 *pOut, const Matrix4x4& mtx)
{
	// 行列式を算出
	float det;
	Matrix4x4Determinant(&det, mtx);
	// 行列式の値が非常に小さいとき、なにもしない
	if((det <= 0.000005f) && (det >= -0.000005f))
	{
		return;
	}

	// 行列式の逆数
	float invDet = 1.0f / det;
	// 余因子を算出
	float i11 = mtx._22 * mtx._33 - mtx._23 * mtx._32;
	float i12 = mtx._23 * mtx._31 - mtx._21 * mtx._33;
	float i13 = mtx._21 * mtx._32 - mtx._22 * mtx._31;
	float i21 = mtx._32 * mtx._13 - mtx._33 * mtx._12;
	float i22 = mtx._33 * mtx._11 - mtx._31 * mtx._13;
	float i23 = mtx._31 * mtx._12 - mtx._32 * mtx._11;
	float i31 = mtx._12 * mtx._23 - mtx._13 * mtx._22;
	float i32 = mtx._13 * mtx._21 - mtx._11 * mtx._23;
	float i33 = mtx._11 * mtx._22 - mtx._12 * mtx._21;

	// 行列に値を設定
	pOut->_11 = i11 * invDet;
	pOut->_12 = i21 * invDet;
	pOut->_13 = i31 * invDet;
	pOut->_21 = i12 * invDet;
	pOut->_22 = i22 * invDet;
	pOut->_23 = i32 * invDet;
	pOut->_31 = i13 * invDet;
	pOut->_32 = i23 * invDet;
	pOut->_33 = i33 * invDet;

	// 行列式の値が0以下の時
	pOut->_14 = pOut->_24 = pOut->_34 = 0.0f;
	pOut->_41 = -mtx._41;
	pOut->_42 = -mtx._42;
	pOut->_43 = -mtx._43;
	pOut->_44 = 1.0f;
}

//=============================================================================
// ビュー行列作成(左手系)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/25
//=============================================================================
inline void SetViewMatrixLH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
{
	// 注視ベクトル設定
	Vector3 normRay;	// 注視ベクトル
	normRay.x = ray.x - pos.x;
	normRay.y = ray.y - pos.y;
	normRay.z = ray.z - pos.z;
	// 注視ベクトルを正規化
	Vector3Normalize(&normRay, normRay);

	// 右方向ベクトルを算出、正規化
	Vector3 normRight;	// 右方向ベクトル
	Vector3NormalizeCross(&normRight, up, normRay);

	// 上方向ベクトルを設定
	Vector3	normUp;
	Vector3Cross(&normUp, normRay, normRight);
	
	// 現在の座標の逆位置を求める
	Vector3 invPos;
	invPos.x = -(pos.x * normRight.x + pos.y * normRight.y + pos.z * normRight.z);
	invPos.y = -(pos.x * normUp.x	+ pos.y * normUp.y	+ pos.z * normUp.z);
	invPos.z = -(pos.x * normRay.x	+ pos.y * normRay.y	+ pos.z * normRay.z);
	
	// 行列に値を設定
	pOut->_11 = normRight.x;
	pOut->_21 = normRight.y;
	pOut->_31 = normRight.z;
	pOut->_12 = normUp.x;
	pOut->_22 = normUp.y;
	pOut->_32 = normUp.z;
	pOut->_13 = normRay.x;
	pOut->_23 = normRay.y;
	pOut->_33 = normRay.z;
	pOut->_41 = invPos.x;
	pOut->_42 = invPos.y;
	pOut->_43 = invPos.z;
	pOut->_14 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_34 = 0.0f;
	pOut->_44 = 1.0f;
}

//=============================================================================
// ビュー行列作成(右手系)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/23
//=============================================================================
inline void SetViewMatrixRH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
{
	// 注視ベクトル設定
	Vector3 normRay;	// 注視ベクトル
	normRay.x = pos.x - ray.x;
	normRay.y = pos.y - ray.y;
	normRay.z = pos.z - ray.z;
	// 注視ベクトルを正規化
	Vector3Normalize(&normRay, normRay);

	// 右方向ベクトルを算出、正規化
	Vector3 normRight;	// 右方向ベクトル
	Vector3NormalizeCross(&normRight, up, normRay);

	// 上方向ベクトルを設定
	Vector3	normUp;
	Vector3Cross(&normUp, normRay, normRight);
	
	// 現在の座標の逆位置を求める
	Vector3 invPos;
	invPos.x = -(pos.x * normRight.x + pos.y * normRight.y + pos.z * normRight.z);
	invPos.y = -(pos.x * normUp.x	+ pos.y * normUp.y	+ pos.z * normUp.z);
	invPos.z = -(pos.x * normRay.x	+ pos.y * normRay.y	+ pos.z * normRay.z);
	
	// 行列に値を設定
	pOut->_11 = normRight.x;
	pOut->_21 = normRight.y;
	pOut->_31 = normRight.z;
	pOut->_12 = normUp.x;
	pOut->_22 = normUp.y;
	pOut->_32 = normUp.z;
	pOut->_13 = normRay.x;
	pOut->_23 = normRay.y;
	pOut->_33 = normRay.z;
	pOut->_41 = invPos.x;
	pOut->_42 = invPos.y;
	pOut->_43 = invPos.z;
	pOut->_14 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_34 = 0.0f;
	pOut->_44 = 1.0f;
}

//=============================================================================
// 3軸からビュー行列を設定
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/29
//=============================================================================
inline void SetViewMatrixFromAxis(Matrix4x4* pOut, const Vector3& pos, const Vector3& right, const Vector3& up, const Vector3& front)
{
	// 現在の座標の逆位置を求める
	Vector3 invPos;
	invPos.x = -(pos.x * right.x	+ pos.y * right.y	+ pos.z * right.z);
	invPos.y = -(pos.x * up.x		+ pos.y * up.y		+ pos.z * up.z);
	invPos.z = -(pos.x * front.x	+ pos.y * front.y	+ pos.z * front.z);
	
	// 行列に値を設定
	pOut->_11 = right.x;
	pOut->_21 = right.y;
	pOut->_31 = right.z;
	pOut->_12 = up.x;
	pOut->_22 = up.y;
	pOut->_32 = up.z;
	pOut->_13 = front.x;
	pOut->_23 = front.y;
	pOut->_33 = front.z;
	pOut->_41 = invPos.x;
	pOut->_42 = invPos.y;
	pOut->_43 = invPos.z;
	pOut->_14 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_34 = 0.0f;
	pOut->_44 = 1.0f;
}

//=============================================================================
// 射影行列作成(DirectX)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void SetProjectionMatrixLH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
{
	float div = tanFast(FoV * 0.5f);
	float FarMinusNear = farSurface - nearSurface;
	// ゼロチェック
	if((div >= -0.00005f && div <= 0.00005f) || FarMinusNear <= 0.0f || aspect <= 0.f)
	{
		// 何もせずに返す
		return;
	}

	// 行列に値を設定
	pOut->_11 = 1.0f / (aspect * div);
	pOut->_12 = 0.0f;
	pOut->_13 = 0.0f;
	pOut->_14 = 0.0f;
	pOut->_21 = 0.0f;
	pOut->_22 = 1.0f / div;
	pOut->_23 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_31 = 0.0f;
	pOut->_32 = 0.0f;
	pOut->_33 = farSurface / FarMinusNear;
	pOut->_34 = 1.0f;
	pOut->_41 = 0.0f;
	pOut->_42 = 0.0f;
	pOut->_43 = -(farSurface * nearSurface) / FarMinusNear;
	pOut->_44 = 0.0f;
}

//=============================================================================
// 射影行列作成(OpenGL)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void SetProjectionMatrixRH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
{
	float div = tanFast(FoV * 0.5f);
	float FarMinusNear = farSurface - nearSurface;
	// ゼロチェック
	if((div >= -0.00005f && div <= 0.00005f) || FarMinusNear <= 0.0f || aspect <= 0.f)
	{
		// 何もせずに返す
		return;
	}

	// 行列に値を設定
	pOut->_11 = 1.0f / (aspect * div);
	pOut->_12 = 0.0f;
	pOut->_13 = 0.0f;
	pOut->_14 = 0.0f;
	pOut->_21 = 0.0f;
	pOut->_22 = 1.0f / div;
	pOut->_23 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_31 = 0.0f;
	pOut->_32 = 0.0f;
	pOut->_33 = -(farSurface + nearSurface) / FarMinusNear;
	pOut->_34 = -1.0f;
	pOut->_41 = 0.0f;
	pOut->_42 = 0.0f;
	pOut->_43 = -2 * (farSurface * nearSurface) / FarMinusNear;
	pOut->_44 = 0.0f;
}

//=============================================================================
// 平行投影行列作成(OpenGL)
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/15
//=============================================================================
inline void SetOrthoMatrixRH(Matrix4x4 *pOut, float fLeft, float fTop, float fRight, float fBottom, float fNear, float fFar)
{
	float OneOverRightMinusLeft = 1.0f / (fRight - fLeft);
	float OneOverTopMinusBottom = 1.0f / (fTop - fBottom);
	float OneOverFarMinusNear	= 1.0f / (fFar - fNear);

	pOut->_11 = 2.0f  * OneOverRightMinusLeft;
	pOut->_22 = 2.0f  * OneOverTopMinusBottom;
	pOut->_33 = -1.0f * OneOverFarMinusNear;

	pOut->_41 = -((fRight + fLeft) * OneOverRightMinusLeft);
	pOut->_42 = -((fTop + fBottom) * OneOverTopMinusBottom);
	pOut->_43 = fNear * OneOverFarMinusNear;

	pOut->_12 = pOut->_13 = pOut->_14 =
	pOut->_21 = pOut->_23 = pOut->_24 =
	pOut->_31 = pOut->_32 = pOut->_34 = 0.0f;

	pOut->_44 = 1.0f;
}

//=============================================================================
// ビューポート行列作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/28
//=============================================================================
inline void SetViewport(Matrix4x4 *pOut, float x, float y, float fWidth, float fHeight, float nearSurface, float farSurface)
{
	float fHalfWidth = fWidth * 0.5f;
	float fHalfHeight = fHeight * 0.5f;

	pOut->_11 = fHalfWidth; pOut->_12 = 0; pOut->_13 = 0; pOut->_14 = 0;
	pOut->_21 = 0; pOut->_22 = -fHalfHeight;pOut->_23 = 0;pOut->_24 = 0;
	pOut->_31 = 0; pOut->_32 = 0; pOut->_33 = farSurface - nearSurface; pOut->_34 = 0;
	pOut->_41 = x + fHalfWidth;
	pOut->_42 = y + fHalfHeight;
	pOut->_43 = nearSurface;
	pOut->_44 = 1.0f;
}

//=============================================================================
// スクリーン座標をワールド座標に変換し、ワールド座標と光線を出力(左手系)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
// ret		: void
// arg1		: Vector3* ワールド座標
// arg2		: Vector3* スクリーン座標から視錐台の奥を見る正規化された光線
// arg3		: float スクリーン上のx座標
// arg4		: float スクリーン上のy座標
// arg5		: float スクリーン始点x座標オフセット
// arg6		: float スクリーン始点y座標オフセット
// arg7		: float バックバッファの横幅
// arg8		: float バックバッファの縦幅
// arg9		: const Matrix4x4& 射影行列
// arg10	: const Matrix4x4& ビュー逆行列
//=============================================================================
inline void ScreenToWorldPositionLH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)
{
	// スクリーン座標をビュポートと射影の逆行列で変換する
	float x = (sx * 2.0f / fBackBufferWidth - 1) / proj._11;
	float y = (-sy * 2.0f / fBackBufferHeight + 1) / proj._22;

	// 原点
	Vector3 WorldPos(0.0f, 0.0f, 0.0f);
	// ビュー空間の奥に伸びる光線
	Vector3 ray(x, y, 1.0f);	// 奥はプラス

	// ワールド座標空間に変換
	Vector3TransformCoord(pWorldPos, WorldPos, invView);
	// 光線を変換
	Vector3TransformNormal(pRay, ray, invView);
	// 光線を正規化
	Vector3Normalize(pRay, *pRay);
}

//=============================================================================
// スクリーン座標をワールド座標に変換し、ワールド座標と光線を出力(右手系)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
// ret		: void
// arg1		: Vector3* ワールド座標
// arg2		: Vector3* スクリーン座標から視錐台の奥を見る正規化された光線
// arg3		: float スクリーン上のx座標
// arg4		: float スクリーン上のy座標
// arg5		: float スクリーン始点x座標オフセット
// arg6		: float スクリーン始点y座標オフセット
// arg7		: float バックバッファの横幅
// arg8		: float バックバッファの縦幅
// arg9		: const Matrix4x4& 射影行列
// arg10	: const Matrix4x4& ビュー逆行列
//=============================================================================
inline void ScreenToWorldPositionRH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)
{
	// スクリーン座標をビュポートと射影の逆行列で変換する
	float x = (sx * 2.0f / fBackBufferWidth - 1) / proj._11;
	float y = (-sy * 2.0f / fBackBufferHeight + 1) / proj._22;

	// 原点
	Vector3 WorldPos(0.0f, 0.0f, 0.0f);
	// ビュー空間の奥に伸びる光線
	Vector3 ray(x, y, -1.0f);	// 奥はマイナス

	// ワールド座標空間に変換
	Vector3TransformCoord(pWorldPos, WorldPos, invView);
	// 光線を変換
	Vector3TransformNormal(pRay, ray, invView);
	// 光線を正規化
	Vector3Normalize(pRay, *pRay);
}

//=============================================================================
// 指定した二つの値の線形補間を算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<typename T>
inline void ComputeLerp(T* pOut, const T& p0, const T& p1, float t)
{
	// 補間フレーム値を丸める
	if(t > 1.0f)
	{
		t = 1.0f;
	}
	else if(t < 0.0f)
	{
		t = 0.0f;
	}
	*pOut = (p0 + (p1 - p0) * t);
}

//=============================================================================
// 原点を中心にした角速度を算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/26
//=============================================================================
inline void ComputeAngularVelocity(Vector3* pOut, const Vector3& pos,const Vector3& vec)
{
	// 距離の二乗を算出
	float fSquaredDistance = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z;
	
	// 距離が非常に近いとき
	if(fSquaredDistance <= 0.000005f)
	{
		// 角速度を0にする
		pOut->x = 0.0f;
		pOut->y = 0.0f;
		pOut->z = 0.0f;
		return;
	}
	
	// 角速度(距離 × 移動量 / 距離二乗)を算出
	// 距離と移動量の外積をとる
	Vector3Cross(pOut, pos, vec);

	float OneOverSquaredDistance = 1.0f / fSquaredDistance;

	pOut->x *= OneOverSquaredDistance;
	pOut->y *= OneOverSquaredDistance;
	pOut->z *= OneOverSquaredDistance;
}

//=============================================================================
// 中心を指定した角速度を算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/26
//=============================================================================
inline void ComputeAngularVelocity(Vector3* pOut, const Vector3& center, const Vector3& pos, const Vector3& vec)
{
	// 距離の二乗を算出
	Vector3 CenterToPos(pos.x - center.x, pos.y - center.y, pos.z - center.z);
	float fSquaredDistance = CenterToPos.x * CenterToPos.x + CenterToPos.y * CenterToPos.y + CenterToPos.z * CenterToPos.z;
	
	// 距離が非常に近いとき
	if(fSquaredDistance <= 0.000005f)
	{
		// 角速度を0にする
		pOut->x = 0.0f;
		pOut->y = 0.0f;
		pOut->z = 0.0f;
		return;
	}
	
	// 角速度(距離 × 移動量 / 距離二乗)を算出
	// 距離と移動量の外積をとる
	Vector3Cross(pOut, CenterToPos, vec);

	float OneOverSquaredDistance = 1.0f / fSquaredDistance;

	pOut->x *= OneOverSquaredDistance;
	pOut->y *= OneOverSquaredDistance;
	pOut->z *= OneOverSquaredDistance;
}

//=============================================================================
// 二つのベクトルから、一方の反射ベクトルを算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/29
//=============================================================================
inline bool ComputeCollideLineToLineXZ(
	Vector3* pCollidePoint,
	float* pRate,	// 侵入したときのベクトルの比率
	Vector3* pReflectVec,
	const Vector3& pos0st,
	const Vector3& pos0ed,
	const Vector3& pos1st,
	const Vector3& pos1ed)
{
	// 各ベクトル算出
	Vector3 vec0 = pos0ed - pos0st;
	Vector3 vec1 = pos1ed - pos1st;
	Vector3 vec2 = pos0st - pos1st;

	// vec0とvec1の外積を取る(符号付面積Sv0v1)
	float SV0V1 = vec0.z * vec1.x - vec0.x * vec1.z;

	// ベクトルが一致している、またはどちらかがゼロベクトル
	if(SV0V1 == 0.0f)
	{
		return false;
	}

	// vec1とvec2の外積で算出される面積を出す(符号付面積sv1v2)
	float sv1v2 = vec1.z * vec2.x - vec1.x * vec2.z;

	// sv1v2とSV0V1の符号付面積の比を出す
	float fRatioOfSV1V2OverSV0V1 = sv1v2 / SV0V1;

	// 交差地点が始点と終点の内側にあるか
	if(fRatioOfSV1V2OverSV0V1 >= 0.0f && 
	   fRatioOfSV1V2OverSV0V1 <= 1.0f)
	{
		// vec0とvec2の外積で産出される面積を出す(符号付面積sv0v2)
		float sv0v2 = vec0.z * vec2.x - vec0.x * vec2.z;

		// sv0v2とSV0V1符号付面積比を出す
		float fRatioOfSV0V2OverSV0V1 = sv0v2 / SV0V1;

		// 交差地点が始点と終点の内側にあるか
		if(fRatioOfSV0V2OverSV0V1 >= 0.0f &&
		   fRatioOfSV0V2OverSV0V1 <= 1.0f)
		{
			// 交差した

			// 交点を求める
			if(pCollidePoint)
			{
				*pCollidePoint = vec0 * fRatioOfSV1V2OverSV0V1 + pos0st;
			}

			// 当たった場所のvec0内の比を求める
			if(pRate)
			{
				*pRate = fRatioOfSV0V2OverSV0V1;
			}

			// 反射ベクトルを求める
			if(pReflectVec)
			{
				float dotVec0Vec1 = vec0.x * vec1.x + vec0.z * vec1.z;
				
				// ベクトルの長さを求める
				float mag0 = sqrtFast(vec0.x * vec0.x + vec0.z * vec0.z);
				float mag1 = sqrtFast(vec1.x * vec1.x + vec1.z * vec1.z);

				// vec0とvec1の間の角を算出
				float fAngle = -acosf(dotVec0Vec1 / (mag0 * mag1));

				// 反射ベクトル
				Vector3 newVector(
					 cosFast(fAngle) * vec0.x + sinFast(fAngle) * vec0.z,
					0.0f,
					-sinFast(fAngle) * vec0.x + cosFast(fAngle) * vec0.z);
				Vector3Normalize(pReflectVec, newVector);
			}

			return true;
		}
	}

	return false;
}

//=============================================================================
// 二つのベクトルから、一方の壁擦りベクトルを算出
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/18
//=============================================================================
inline bool ComputeCollideLineToLineXZScratch(
	Vector3* pCollidePoint,
	float* pRate,	// 侵入したときのベクトルの比率
	Vector3* pScratchVec,
	const Vector3& pos0st,
	const Vector3& pos0ed,
	const Vector3& pos1st,
	const Vector3& pos1ed)
{
	// 各ベクトル算出
	Vector3 vec0 = pos0ed - pos0st;
	Vector3 vec1 = pos1ed - pos1st;
	Vector3 vec2 = pos0st - pos1st;

	// vec0とvec1の外積を取る(符号付面積Sv0v1)
	float SV0V1 = vec0.z * vec1.x - vec0.x * vec1.z;

	// ベクトルが一致している、またはどちらかがゼロベクトル
	if(SV0V1 == 0.0f)
	{
		return false;
	}

	// vec1とvec2の外積で算出される面積を出す(符号付面積sv1v2)
	float sv1v2 = vec1.z * vec2.x - vec1.x * vec2.z;

	// sv1v2とSV0V1の符号付面積の比を出す
	float fRatioOfSV1V2OverSV0V1 = sv1v2 / SV0V1;

	// 交差地点が始点と終点の内側にあるか
	if(fRatioOfSV1V2OverSV0V1 >= 0.0f && 
	   fRatioOfSV1V2OverSV0V1 <= 1.0f)
	{
		// vec0とvec2の外積で産出される面積を出す(符号付面積sv0v2)
		float sv0v2 = vec0.z * vec2.x - vec0.x * vec2.z;

		// sv0v2とSV0V1符号付面積比を出す
		float fRatioOfSV0V2OverSV0V1 = sv0v2 / SV0V1;

		// 交差地点が始点と終点の内側にあるか
		if(fRatioOfSV0V2OverSV0V1 >= 0.0f &&
		   fRatioOfSV0V2OverSV0V1 <= 1.0f)
		{
			// 交差した

			// 交点を求める
			if(pCollidePoint)
			{
				*pCollidePoint = vec0 * fRatioOfSV1V2OverSV0V1 + pos0st;
			}

			// 当たった場所のvec0内の比を求める
			if(pRate)
			{
				*pRate = fRatioOfSV0V2OverSV0V1;
			}

			// 壁擦りベクトルを求める
			if(pScratchVec)
			{
				float dotVec0Vec1 = vec0.x * vec1.x + vec0.z * vec1.z;

				Vector3 newVector(0.0f, 0.0f, 0.0f);
				if(dotVec0Vec1 > 0.0f)
				{
					newVector = vec0;
					Vector3Normalize(pScratchVec, newVector);
				}
				else if(dotVec0Vec1 < 0.0f)
				{
					newVector = -vec0;
					Vector3Normalize(pScratchVec, newVector);
				}
				else
				{
					*pScratchVec = newVector;
				}
			}

			return true;
		}
	}

	return false;
}

#endif	// __KB_MATH_H__

// EOF