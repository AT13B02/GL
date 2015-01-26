//=============================================================================
//
// �Ǝ���`�̐��w���[�e�B���e�B [kbMath.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/15
//
//=============================================================================
#pragma once
#ifndef __KB_MATH_H__
#define __KB_MATH_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <float.h>		// (�{���x)����������`
#include <math.h>		// �Ǝ���`�֐����{�g���l�b�N�ɂȂ�����g��

//*****************************************************************************
// ���̃t�@�C���ɓ����Ă�N���X�Ɗ֐�
/*

Vector2 �N���X
Vector3 �N���X
Vector4 �N���X
Matrix4x4 �N���X
Quaternion �N���X
Plane �N���X
AARect�N���X
AABB �N���X

// �������֐�
double inline __declspec (naked) __fastcall sqrtFast(double n)
float inline __declspec (naked) __fastcall sqrtFast(float n)
// �R�T�C���֐�
double inline __declspec (naked) __fastcall cosFast(double n)
float inline __declspec (naked) __fastcall cosFast(float n)
// �T�C���֐�
double inline __declspec (naked) __fastcall sinFast(double n)
float inline __declspec (naked) __fastcall sinFast(float n)
// �^���W�F���g�֐�
double inline __declspec (naked) __fastcall tanFast(double n)
float inline __declspec (naked) __fastcall tanFast(float n)
// �A�[�N�R�T�C���֐�
double inline __declspec (naked) __fastcall acosFast(double n)
float inline __declspec (naked) __fastcall acosFast(float n)
// �A�[�N�T�C���֐�
double inline __declspec (naked) __fastcall asinFast(double n)
float inline __declspec (naked) __fastcall asinFast(float n)
// �A�[�N�^���W�F���g�֐�
double inline __declspec (naked) __fastcall atanFast(double n)
float inline __declspec (naked) __fastcall atanFast(float n)
// �A�[�N�^���W�F���g�֐�(2����)
double inline __declspec (naked) __fastcall atan2Fast(double y, double x)
float inline __declspec (naked) __fastcall atan2Fast(float y, float x)

// 2D�x�N�g��
// 2D�x�N�g������
void Vector2Dot(float* pOut, const Vector2& vec0, const Vector2& vec1)
// 2D�x�N�g���O��
void Vector2Cross(float* pOut, const Vector2& vec0, const Vector2& vec1)

// 3D�x�N�g��
// �x�N�g�����Z����
void Vector3Add(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// �x�N�g�����Z����
void Vector3Sub(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// �x�N�g���𐳋K������
void Vector3Normalize(Vector3* pOut, const Vector3& vec0)
// �x�N�g���̓��ς��Z�o
void Vector3Dot(float* pOut, const Vector3& vec0, const Vector3& vec1)
// ���K�������x�N�g���̓��ς��Z�o
void Vector3NormalizeDot(float* pOut, const Vector3& vec0, const Vector3& vec1)
// �x�N�g���̊O�ς��Z�o
void Vector3Cross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// ���K�������x�N�g���̊O�ς��Z�o
void Vector3NormalizeCross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
// �x�N�g���̍s��ϊ�
void Vector3Transform(Vector4 *pOut, const Vector3& vec, const Matrix4x4& mtx)
// 3D���W��w = 1�Ɏˉe����ϊ�
void Vector3TransformCoord(Vector3 *pOut, const Vector3& nor, const Matrix4x4& mtx)
// �@���̕ϊ�
void Vector3TransformNormal(Vector3 *pOut, const Vector3& nor, const Matrix4x4& mtx)
// �ǎC��x�N�g���Z�o
void Vector3ScratchWall(Vector3 *pOut, const Vector3& in, const Vector3& normal)
// ���˃x�N�g���Z�o
void Vector3Reflection(Vector3 *pOut, const Vector3& in, const Vector3& normal)

// �s��
// �s����Z
void Matrix4x4Add(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
// �s�񌸎Z
void Matrix4x4Sub(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
// �s���Z
void Matrix4x4Multiply(Matrix4x4 *pOut, const Matrix4x4& m1, const Matrix4x4& m2)
// �s�񏉊���
void Matrix4x4Identity(Matrix4x4 *pOut);
// �]�u�s��쐬
void Matrix4x4Transpose(Matrix4x4 *pOut, const Matrix4x4& mtxTrns)
// �s�񎮎Z�o
void Matrix4x4Determinant(float *pOut, const Matrix4x4& mtx)
// �t�s��쐬
void Matrix4x4Inverse(Matrix4x4 *pOut, const Matrix4x4& mtx)
// �X�P�[���s��쐬
void Matrix4x4Scaling(Matrix4x4 *pOut, const float& sx, const float &sy, const float& sz)
// YawPitchRoll��]�s��쐬
void Matrix4x4YawPitchRoll(Matrix4x4 *pOut, const float& pitch, const float& yaw, const float& roll)
// ���s�ړ��s��쐬
void Matrix4x4Translation(Matrix4x4 *pOut, const float& tx, const float& ty, const float& tz)
// �s����g��A��]�A���s�ړ������ɕ���
void Matrix4x4Decompose(Vector3* pTrans, Quaternion* pRot, Vector3* pScale, const Matrix4x4& mtx)
// �C�ӎ���]�s��쐬
void Matrix4x4RotationArbitraryAxis(Matrix4x4 *pOut, const Vector3& axis, const float& angle)
// �s�񂩂�I�C���[�p�ɕϊ�
void Matrix4x4ToEulerAngle(Vector3 *pOut, const Matrix4x4& mtx)
// �s�񂩂�N�H�[�^�j�I���ɕϊ�
void Matrix4x4ToQuaternion(Quaternion* pOut, const Matrix4x4& mtx)

// �N�H�[�^�j�I��
// �ȉ��Ŏg�p����N�H�[�^�j�I����Z�́A��ʓI�Ȏ��ƈقȂ�B��Z�̒�`��ύX���邱�Ƃɂ��A
// q = bap(ba)-1 �̂悤�ȉE���獶�̏�Z��
// q = (-ab)p(ab) �̍�����E�ւ̏�Z�ւƕς���(���ʂ͓���)
// �N�H�[�^�j�I����Z
void QuaternionMultiply(Quaternion *pOut, const Quaternion& q1, const Quaternion& q2)
// �N�H�[�^�j�I������
void QuaternionDot(float* pOut, const Quaternion& q1, const Quaternion& q2)
// �P���N�H�[�^�j�I���쐬
void QuaternionIdentity(Quaternion *pOut)
// �N�H�[�^�j�I�����K��
void QuaternionNormalize(Quaternion *pOut, const Quoternion& q) 
// �����N�H�[�^�j�I���쐬
void QuaternionConjugate(Quaternion *pOut, const Quaternion& q)
// �t�N�H�[�^�j�I��(�����Ɛ��K�����ꂽ�N�H�[�^�j�I��)�쐬
void QuaternionInverse(Quaternion *pOut, const Quaternion& q)
// �w�肵�����Ɖ�]�ʂŃN�H�[�^�j�I�����쐬
void QuaternionRotationAxis(Quoaternion *pOut, const Vector3& axis, float angle)
// �w�肵��2�̃N�H�[�^�j�I���̋��ʐ��`��Ԃ��ꂽ�N�H�[�^�j�I�����쐬
void QuaternionSlerp(Quaternion *pOut, const Quaternion& q1, const Quaternion& q2, float t)
// �I�C���[�p����N�H�[�^�j�I���ւ̕ϊ�
void EulerAngleToQuaternion(Quaternion *pOut, const Vector3& rot)
// �N�H�[�^�j�I������I�C���[�p�ɕϊ�
void QuaternionToEulerAngle(Vector3 *pOut, const Quaternion& q)
// �N�H�[�^�j�I������s��ɕϊ�
void QuaternionToMatrix4x4(Matrix4x4 *pOut, const Quaternion& q)

// �w�肵�����W��C�ӎ��ŉ�]
void Vector3RotationAxis(Vector3* pOut, const Vector3& pos, const Vector3& axis, const float& angle)

// ����
// ���ʂƓ_�̋��E����
void PlaneDotVector3(float *pOut, const Plane& pl, const Vector3& point)
// �_�Ɩ@�����畽�ʂ��Z�o����
void PlaneFromPointNormal(Plane *pOut, const Vector3& p, const Vector3& nor)
// 3�_���畽�ʂ��Z�o����
void PlaneFromPoints(Plane *pOut, const Vector3& p0, const Vector3& p1, const Vector3& p2)
// ���ʂ𐳋K������
void PlaneNormalize(Plane *pOut, const Plane& pl)
// ���ʂ̉�]
void PlaneRotation(Plane *pOut, const Plane& pl, const Matrix4x4& rot)
// ���ʂƌ����̌����������W
bool PlaneRayIntersect(Vector3 *pOut, const Plane& pl, const Vector3& pos, const Vector3& ray)
// ���ʂƐ����̌����������W
bool PlaneLineSegmentIntersect(Vector3 *pOut, const Plane& pl, const Vector3& p0, const Vector3& p1)

// ���[���h�s��쐬
void SetWorldMatrix(Matrix4x4 *pOut, const Vector3 &trans, const Vector3 &rot, const Vector3 &scl)
// ���[���h�t�s��쐬
void SetWorldInverseMatrix(Matrix4x4 *pOut, const Matrix4x4& mtx)
// �r���[�s��쐬
void SetViewMatrixLH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
void SetViewMatrixRH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
// �O������r���[�s��쐬
void SetViewMatrixFromAxis(Matrix4x4* pOut, const Vector3& pos, const Vector3& right, const Vector3& up, const Vector3& front)
// �ˉe�s��쐬
void SetProjectionMatrixLH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
void SetProjectionMatrixRH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
// ���s���e�s��쐬
void SetOrthoMatrixRH(Matrix4x4 *pOut, float fLeft, float fTop, float fRight, float fBottom, float fNear, float fFar)
// �r���[�|�[�g�s��쐬
void SetViewport(float x, float y, float fWidth, float fHeight, float nearSurface, float farSurface)

// �X�N���[�����W�����[���h���W�ɕϊ����A���[���h���W�ƌ������o��(����n)
void ScreenToWorldPositionLH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)
// �X�N���[�����W�����[���h���W�ɕϊ����A���[���h���W�ƌ������o��(�E��n)
void ScreenToWorldPositionRH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)

// �w�肵����̒l�̐��`��Ԃ��Z�o
template<typename T>
void ComputeLerp(T* pOut, const T& p0, const T& p1, float t)

// ���_�𒆐S�ɂ����p���x���Z�o
void ComputeAngularVelocity(Vector3* pOut, const Vector3& pos,const Vector3& vec)

// ���S���w�肵���p���x���Z�o
void ComputeAngularVelocity(Vector3* pOut, const Vector3& center, const Vector3& pos, const Vector3& vec)

// ��̃x�N�g������A����̔��˃x�N�g�����Z�o
bool ComputeCollideLineToLineXZ(
Vector3* pCollidePoint,
float* pRate,	// �N�������Ƃ��̃x�N�g���̔䗦
Vector3* pReflectVec,
Vector3 pos0st,
Vector3 pos0ed,
Vector3 pos1st,
Vector3 pos1ed)
*/
//*****************************************************************************

//*****************************************************************************
// ���w�ɕ֗�?�ȃ}�N����`
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
// �~����
#define KB_PI			(3.141592653589f)
// �x���@��1�x
#define ONE_DEGREE		(KB_PI / 180.0f)
// 2�̕������̋t��
#define ONE_OVER_RT2	(0.7071067811865475f)

//*****************************************************************************
// 2���x�N�g���N���X
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

	// �I�[�o�[���[�h���Z�q
	// ���Z
	Vector2 operator+(const Vector2& rhs) const
	{
		return Vector2(this->x + rhs.x, this->y + rhs.y);
	}
	// ���Z�L���O�u
	Vector2 operator+(void) const
	{
		return *this;
	}
	// ���Z���
	Vector2& operator+=(const Vector2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}
	// ���Z
	Vector2 operator-(const Vector2& rhs) const
	{
		return Vector2(this->x - rhs.x, this->y - rhs.y);
	}
	// ���Z�L���O�u
	Vector2 operator-(void) const
	{
		return Vector2(-this->x, -this->y);
	}
	// ���Z���
	Vector2& operator-=(const Vector2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}
	// ��Z
	Vector2 operator*(const float& rhs) const
	{
		return Vector2(this->x * rhs, this->y * rhs);
	}
	// ��Z���
	Vector2& operator*=(const float& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;

		return *this;
	}
	// ���Z
	Vector2 operator/(const float& rhs) const
	{
		return Vector2(this->x / rhs, this->y / rhs);
	}
	// ���Z���
	Vector2& operator/=(const float& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;

		return *this;
	}

	// �����o�ϐ�
	float x, y;
};

//*****************************************************************************
// 3���x�N�g���N���X
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

	// �I�[�o�[���[�h���Z�q
	// ���Z
	Vector3 operator+(const Vector3& rhs) const
	{
		return Vector3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}
	// ���Z�L���O�u
	Vector3 operator+(void) const
	{
		return *this;
	}
	// ���Z���
	Vector3& operator+=(const Vector3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;

		return *this;
	}
	// ���Z
	Vector3 operator-(const Vector3& rhs) const
	{
		return Vector3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}
	// ���Z�L���O�u
	Vector3 operator-(void) const
	{
		return Vector3(-this->x, -this->y, -this->z);
	}
	// ���Z���
	Vector3& operator-=(const Vector3& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;

		return *this;
	}
	// ��Z
	Vector3 operator*(const float& rhs) const
	{
		return Vector3(this->x * rhs, this->y * rhs, this->z * rhs);
	}
	// ��Z���
	Vector3& operator*=(const float& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;

		return *this;
	}
	// ���Z
	Vector3 operator/(const float& rhs) const
	{
		return Vector3(this->x / rhs, this->y / rhs, this->z / rhs);
	}
	// ���Z���
	Vector3& operator/=(const float& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;

		return *this;
	}

	// �����o�ϐ�
	float x, y, z;
};

//*****************************************************************************
// 4���x�N�g���N���X
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

	// �I�[�o�[���[�h���Z�q
	// ���Z
	Vector4 operator+(const Vector4& rhs) const
	{
		return Vector4(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z, this->w + rhs.w);
	}
	// ���Z�L���O�u
	Vector4 operator+(void) const
	{
		return *this;
	}
	// ���Z���
	Vector4& operator+=(const Vector4& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		this->w += rhs.w;

		return *this;
	}
	// ���Z
	Vector4 operator-(const Vector4& rhs) const
	{
		return Vector4(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z, this->w - rhs.w);
	}
	// ���Z�L���O�u
	Vector4 operator-(void) const
	{
		return Vector4(-this->x, -this->y, -this->z, -this->w);
	}
	// ���Z���
	Vector4& operator-=(const Vector4& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		this->z -= rhs.z;
		this->w -= rhs.w;

		return *this;
	}
	// ��Z
	Vector4 operator*(const float& rhs) const
	{
		return Vector4(this->x * rhs, this->y * rhs, this->z * rhs, this->w * rhs);
	}
	// ��Z���
	Vector4& operator*=(const float& rhs)
	{
		this->x *= rhs;
		this->y *= rhs;
		this->z *= rhs;
		this->w *= rhs;

		return *this;
	}
	// ���Z
	Vector4 operator/(const float& rhs) const
	{
		return Vector4(this->x / rhs, this->y / rhs, this->z / rhs, this->w / rhs);
	}
	// ���Z���
	Vector4& operator/=(const float& rhs)
	{
		this->x /= rhs;
		this->y /= rhs;
		this->z /= rhs;
		this->w /= rhs;

		return *this;
	}

	// �����o�ϐ�(�������W�ł��F�ł��g����)
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
// 4x4�s��N���X
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

	// �I�[�o�[���[�h���Z�q
	// ���Z
	Matrix4x4 operator+(const Matrix4x4& rhs) const
	{
		Matrix4x4 temp;

		temp._11 = this->_11 + rhs._11; temp._12 = this->_12 + rhs._12; temp._13 = this->_13 + rhs._13; temp._14 = this->_14 + rhs._14;
		temp._21 = this->_21 + rhs._21; temp._22 = this->_22 + rhs._22; temp._23 = this->_23 + rhs._23; temp._24 = this->_24 + rhs._24;
		temp._31 = this->_31 + rhs._31; temp._32 = this->_32 + rhs._32; temp._33 = this->_33 + rhs._33; temp._34 = this->_34 + rhs._34;
		temp._41 = this->_41 + rhs._41; temp._42 = this->_42 + rhs._42; temp._43 = this->_43 + rhs._43; temp._44 = this->_44 + rhs._44;

		return temp;
	}
	// �O�u���Z�L��
	Matrix4x4 operator+() const
	{
		return *this;
	}
	// ���Z���
	Matrix4x4& operator+=(const Matrix4x4& rhs)
	{
		this->_11 = this->_11 + rhs._11; this->_12 = this->_12 + rhs._12; this->_13 = this->_13 + rhs._13; this->_14 = this->_14 + rhs._14;
		this->_21 = this->_21 + rhs._21; this->_22 = this->_22 + rhs._22; this->_23 = this->_23 + rhs._23; this->_24 = this->_24 + rhs._24;
		this->_31 = this->_31 + rhs._31; this->_32 = this->_32 + rhs._32; this->_33 = this->_33 + rhs._33; this->_34 = this->_34 + rhs._34;
		this->_41 = this->_41 + rhs._41; this->_42 = this->_42 + rhs._42; this->_43 = this->_43 + rhs._43; this->_44 = this->_44 + rhs._44;

		return *this;
	}
	// ���Z
	Matrix4x4 operator-(const Matrix4x4& rhs) const
	{
		Matrix4x4 temp;

		temp._11 = this->_11 - rhs._11; temp._12 = this->_12 - rhs._12; temp._13 = this->_13 - rhs._13; temp._14 = this->_14 - rhs._14;
		temp._21 = this->_21 - rhs._21; temp._22 = this->_22 - rhs._22; temp._23 = this->_23 - rhs._23; temp._24 = this->_24 - rhs._24;
		temp._31 = this->_31 - rhs._31; temp._32 = this->_32 - rhs._32; temp._33 = this->_33 - rhs._33; temp._34 = this->_34 - rhs._34;
		temp._41 = this->_41 - rhs._41; temp._42 = this->_42 - rhs._42; temp._43 = this->_43 - rhs._43; temp._44 = this->_44 - rhs._44;

		return temp;
	}
	// �O�u���Z�L��
	Matrix4x4 operator-() const
	{
		return Matrix4x4(-this->_11, -this->_12, -this->_13, -this->_14,
						 -this->_21, -this->_22, -this->_23, -this->_24,
						 -this->_31, -this->_32, -this->_33, -this->_34,
						 -this->_41, -this->_42, -this->_43, -this->_44);
	}
	// ���Z���
	Matrix4x4& operator-=(const Matrix4x4& rhs)
	{
		this->_11 = this->_11 - rhs._11; this->_12 = this->_12 - rhs._12; this->_13 = this->_13 - rhs._13; this->_14 = this->_14 - rhs._14;
		this->_21 = this->_21 - rhs._21; this->_22 = this->_22 - rhs._22; this->_23 = this->_23 - rhs._23; this->_24 = this->_24 - rhs._24;
		this->_31 = this->_31 - rhs._31; this->_32 = this->_32 - rhs._32; this->_33 = this->_33 - rhs._33; this->_34 = this->_34 - rhs._34;
		this->_41 = this->_41 - rhs._41; this->_42 = this->_42 - rhs._42; this->_43 = this->_43 - rhs._43; this->_44 = this->_44 - rhs._44;

		return *this;
	}
	// �Ϙa���Z
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
	// �Ϙa���Z���
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
	// �X�J���[��Z
	Matrix4x4 operator*(const float& rhs) const
	{
		Matrix4x4 temp;
		
		temp._11 = this->_11 * rhs; temp._12 = this->_12 * rhs; temp._13 = this->_13 * rhs; temp._14 = this->_14 * rhs;
		temp._21 = this->_21 * rhs; temp._22 = this->_22 * rhs; temp._23 = this->_23 * rhs; temp._24 = this->_24 * rhs;
		temp._31 = this->_31 * rhs; temp._32 = this->_32 * rhs; temp._33 = this->_33 * rhs; temp._34 = this->_34 * rhs;
		temp._41 = this->_41 * rhs; temp._42 = this->_42 * rhs; temp._43 = this->_43 * rhs; temp._44 = this->_44 * rhs;

		return temp;
	}
	// �X�J���[��Z���
	Matrix4x4& operator*=(const float& rhs)
	{
		this->_11 *= rhs; this->_12 *= rhs; this->_13 *= rhs; this->_14 *= rhs;
		this->_21 *= rhs; this->_22 *= rhs; this->_23 *= rhs; this->_24 *= rhs;
		this->_31 *= rhs; this->_32 *= rhs; this->_33 *= rhs; this->_34 *= rhs;
		this->_41 *= rhs; this->_42 *= rhs; this->_43 *= rhs; this->_44 *= rhs;

		return *this;
	}
	// �X�J���[���Z
	Matrix4x4 operator/(const float& rhs) const
	{
		Matrix4x4 temp;
		
		temp._11 = this->_11 / rhs; temp._12 = this->_12 / rhs; temp._13 = this->_13 / rhs; temp._14 = this->_14 / rhs;
		temp._21 = this->_21 / rhs; temp._22 = this->_22 / rhs; temp._23 = this->_23 / rhs; temp._24 = this->_24 / rhs;
		temp._31 = this->_31 / rhs; temp._32 = this->_32 / rhs; temp._33 = this->_33 / rhs; temp._34 = this->_34 / rhs;
		temp._41 = this->_41 / rhs; temp._42 = this->_42 / rhs; temp._43 = this->_43 / rhs; temp._44 = this->_44 / rhs;

		return temp;
	}
	// �X�J���[���Z���
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
// �N�H�[�^�j�I���N���X
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

	// �O�u���Z
	Quaternion operator-() const
	{
		return Quaternion(-this->x, -this->y, -this->z, -this->w);
	}
	// ��Z
	Quaternion operator*(const Quaternion& rhs) const
	{
		Quaternion temp;
		
		temp.w = this->w * rhs.w - (this->x * rhs.x + this->y * rhs.y + this->z * rhs.z); 
		temp.x = this->w * rhs.x + rhs.w * this->x + this->y * rhs.z - this->z * rhs.y;
		temp.y = this->w * rhs.y + rhs.w * this->y + this->z * rhs.x - this->x * rhs.z;
		temp.z = this->w * rhs.z + rhs.w * this->z + this->x * rhs.y - this->y * rhs.x;

		return temp;
	}
	// ��Z���
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
// ���ʃN���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//*****************************************************************************
class Plane
{
public:

	Plane(){}
	Plane(float a, float b, float c, float d) :
	a(a), b(b), c(c), d(d){}

	// ���ʂ��`����v�f
	// ���ʂ̕����� ax + by + cz + d = 0
	float a, b, c, d;
};

//*****************************************************************************
// ���W���ő�����ꂽ��`�N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
class AARect
{
public:

	AARect() : left(FLT_MAX), top(FLT_MAX), right(FLT_MIN), bottom(FLT_MIN){}

	AARect(float left, float top, float right, float bottom) :
	left(left), top(top), right(right), bottom(bottom){}

	// ��`�̒��S�_��Ԃ�
	Vector2 center(void) const { return Vector2((left + right) * 0.5f, (top + bottom) * 0.5f); }

	// ��`�̉�����Ԃ�
	float width(void) const { return (right - left); }
	// ��`�̏c����Ԃ�
	float height(void) const { return (bottom - top); }

	float left, top, right, bottom;
};

//*****************************************************************************
// ���W���ő�����ꂽ�o�E���f�B���O�{�b�N�X
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

	// �{�b�N�X�̒��S�_��Ԃ�
	Vector3 center(void) const { return Vector3((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f, (Min.z + Max.z) * 0.5f); }

	// �{�b�N�X�̊e�ӂ̒�����Ԃ�
	Vector3 size(void) const { return (Max - Min); }
	// X�������̒�����Ԃ�
	float width(void) const { return (Max.x - Min.x); }
	// Y�������̒�����Ԃ�
	float height(void) const { return (Max.y - Min.y); }
	// Z�������̒�����Ԃ�
	float depth(void) const { return (Max.z - Min.z); }

	// �w�肵���C���f�b�N�X(0 ~ 7)����AABB�̒��_���擾
	// ����n�ƍl��
	// Z���𕉂��琳�̕����֌����ꍇ
	// (5)1----2(6)
	//    |    |
	//    |    |
	// (4)0----3(7)
	// �Ƃ����ԍ��t���ɂ���(���Ȃŕ��ʂ���肽���Ƃ��ȊO���܂�C�ɂ���K�v�͂Ȃ�����)
	Vector3 corner(int nIndex) const
	{
		Vector3 temp(FLT_MAX, FLT_MAX, FLT_MAX);

		// �C���f�b�N�X���s���Ȓl�������Ă��Ȃ�������
		if(nIndex < 0 || nIndex >= 8)
		{
			// �ǂ����悤���Ȃ��l��Ԃ�
			return temp;
		}

		// �C���f�b�N�X�ɂ���ĕԂ��l�����߂�
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

	// ���_��ǉ�(�K�v�ȕ������g������)
	void add(const Vector3& pos)
	{
		if(Min.x > pos.x){ Min.x = pos.x; }
		if(Min.y > pos.y){ Min.y = pos.y; }
		if(Min.z > pos.z){ Min.z = pos.z; }
		if(Max.x < pos.x){ Max.x = pos.x; }
		if(Max.y < pos.y){ Max.y = pos.y; }
		if(Max.z < pos.z){ Max.z = pos.z; }
	}

	// AABB��ǉ�(�K�v�ȕ������g������)
	void add(const AABB& aabb)
	{
		if(Min.x > aabb.Min.x){ Min.x = aabb.Min.x; }
		if(Min.y > aabb.Min.y){ Min.y = aabb.Min.y; }
		if(Min.z > aabb.Min.z){ Min.z = aabb.Min.z; }
		if(Max.x < aabb.Max.x){ Max.x = aabb.Max.x; }
		if(Max.y < aabb.Max.y){ Max.y = aabb.Max.y; }
		if(Max.z < aabb.Max.z){ Max.z = aabb.Max.z; }
	}

	// �{�b�N�X�ŏ��l
	Vector3 Min;
	// �{�b�N�X�ő�l
	Vector3 Max;
};

/*****************************************************************************/
// x86�n�̃v���Z�b�T�������ꍇ
#ifdef _M_IX86

//=============================================================================
// �������������v�Z
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
// �������������v�Z
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
// �������R�T�C���v�Z
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
// �������R�T�C���v�Z
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
// �������T�C���v�Z
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
// �������T�C���v�Z
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
// �������^���W�F���g�v�Z
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
// �������^���W�F���g�v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float inline __declspec (naked) __fastcall tanFast(float n)
{
	_asm fld dword ptr [esp+4]
	_asm fptan
	_asm fdivp ST(1), ST(0) ; //st1�ɐ��ڂ��ۑ�����Ă�̂�st0��1.0�Ŋ����ăX�^�b�N�̃g�b�v�Ɏ����Ă����
	_asm ret 4
}

//=============================================================================
// �A�[�N�R�T�C���֐�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
double inline __declspec (naked) __fastcall acosFast(double n)
{
	_asm
	{
		fld qword ptr [esp+4]
		fmul st(0), st(0);		// ���
		fld1
		fsub st(0), st(1);		// 1 - ���
		fsqrt
		fld qword ptr [esp+4]
		fpatan
		ret 8
	}
}

//=============================================================================
// �A�[�N�R�T�C���֐�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
float inline __declspec (naked) __fastcall acosFast(float n)
{
	_asm
	{
		fld dword ptr [esp+4]
		fmul st(0), st(0);		// ���
		fld1
		fsub st(0), st(1);		// 1 - ���
		fsqrt
		fld dword ptr [esp+4]
		fpatan
		ret 4
	}
}

//=============================================================================
// �A�[�N�T�C���֐�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
double inline __declspec (naked) __fastcall asinFast(double n)
{
	_asm
	{
		fld qword ptr [esp+4]
		fmul st(0), st(0);		// ���
		fld1
		fsub st(0), st(1);		// 1 - ���
		fsqrt
		fld qword ptr [esp+4]
		fxch
		fpatan
		ret 8
	}
}

//=============================================================================
// �A�[�N�T�C���֐�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
float inline __declspec (naked) __fastcall asinFast(float n)
{
	_asm
	{
		fld dword ptr [esp+4]
		fmul st(0), st(0);		// ���
		fld1
		fsub st(0), st(1);		// 1 - ���
		fsqrt
		fld dword ptr [esp+4]
		fxch
		fpatan
		ret 4
	}
}

//=============================================================================
// �������A�[�N�^���W�F���g�v�Z
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
// �������A�[�N�^���W�F���g�v�Z
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
// �������A�[�N�^���W�F���g�v�Z
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
// �������A�[�N�^���W�F���g�v�Z
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

#else	// ����ȊO�̃v���Z�b�T�̎�
#include <math.h>
//=============================================================================
// �������������v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline double sqrtFast(double n)
{
	return sqrt(n);
}

//=============================================================================
// �������������v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline float sqrtFast(float n)
{
	return sqrtf(n);
}

//=============================================================================
// �������R�T�C���v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline double cosFast(double n)
{
	return cos(n);
}

//=============================================================================
// �������R�T�C���v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline float cosFast(float n)
{
	return cosf(n);
}

//=============================================================================
// �������T�C���v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline double sinFast(double n)
{
	return sin(n);
}

//=============================================================================
// �������T�C���v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline float sinFast(float n)
{
	return sinf(n);
}

//=============================================================================
// �������^���W�F���g�v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
inline double tanFast(double n)
{
	return tan(n);
}

//=============================================================================
// �������^���W�F���g�v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/24
//=============================================================================
float tanFast(float n)
{
	return tanf(n);
}

//=============================================================================
// �������A�[�N�^���W�F���g�v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline double atanFast(double y, double x)
{
	return atan2(y,x);
}

//=============================================================================
// �������A�[�N�^���W�F���g�v�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline float atanFast(float y, float x)
{
	return atan2f(y,x);
}

#endif

//*****************************************************************************
// �Ǝ���`�x�N�g���}�N����`
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//*****************************************************************************
// �[���x�N�g��
#define KB_VEC_ZERO		(Vector3(0.0f, 0.0f, 0.0f))

//=============================================================================
// 2D�x�N�g������
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/27
//=============================================================================
inline void Vector2Dot(float* pOut, const Vector2& vec0, const Vector2& vec1)
{
	*pOut = vec0.x * vec1.x + vec0.y * vec1.y;
}

//=============================================================================
// 2D�x�N�g���O��
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/27
//=============================================================================
inline void Vector2Cross(float* pOut, const Vector2& vec0, const Vector2& vec1)
{
	*pOut = vec0.x * vec1.y - vec0.y * vec1.x;
}

//=============================================================================
// �x�N�g�����Z
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
// �x�N�g�����Z
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
// �x�N�g�����K��
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3Normalize(Vector3* pOut, const Vector3& vec0)
{
	float mag = (sqrtFast(vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z));
	// �[���`�F�b�N
	if(mag <= 0.0f)
	{
		// ���������ɕԂ�
		return;
	}

	float OneOverMag = 1.0f / mag;

	pOut->x = vec0.x * OneOverMag;
	pOut->y = vec0.y * OneOverMag;
	pOut->z = vec0.z * OneOverMag;
}

//=============================================================================
// �x�N�g�����όv�Z
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
// �x�N�g�����K���Ɠ��όv�Z
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3NormalizeDot(float* pOut, const Vector3& vec0, const Vector3& vec1)
{
	float mag0 = (sqrtFast(vec0.x * vec0.x + vec0.y * vec0.y + vec0.z * vec0.z));
	float mag1 = (sqrtFast(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z));
	// �[�����Z�`�F�b�N
	if(mag0 <= 0 || mag1 <= 0)
	{
		// �������Ȃ�
		return;
	}

	float OneOverMag0 = 1.0f / mag0;
	float OneOverMag1 = 1.0f / mag1;

	*pOut = vec0.x * OneOverMag0 * vec1.x * OneOverMag1
		  + vec0.y * OneOverMag0 * vec1.y * OneOverMag1
		  + vec0.z * OneOverMag0 * vec1.z * OneOverMag1;
}

//=============================================================================
// �x�N�g���O�όv�Z(vec0����vec1���Ɍv�Z����)
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
// �x�N�g�����K���ƊO�όv�Z(vec0����vec1���Ɍv�Z����)
// Author : Ryo Kobayashi
// LastUpdate : 2014/3/5
//=============================================================================
inline void Vector3NormalizeCross(Vector3* pOut, const Vector3& vec0, const Vector3& vec1)
{
	// �O�όv�Z
	pOut->x = vec0.y * vec1.z - vec0.z * vec1.y;
	pOut->y = vec0.z * vec1.x - vec0.x * vec1.z;
	pOut->z = vec0.x * vec1.y - vec0.y * vec1.x;

	float mag = (sqrtFast(pOut->x * pOut->x + pOut->y * pOut->y + pOut->z * pOut->z));
	// �[���`�F�b�N
	if(mag <= 0.0f)
	{
		// ���������ɕԂ�
		return;
	}

	float OneOverMag = 1.0f / mag;

	// ���K��
	pOut->x = pOut->x * OneOverMag;
	pOut->y = pOut->y * OneOverMag;
	pOut->z = pOut->z * OneOverMag;
}

//=============================================================================
// �x�N�g���̍s��ϊ�
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
// 3D���W��w = 1�Ɏˉe����ϊ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
inline void Vector3TransformCoord(Vector3 *pOut, const Vector3& pos, const Matrix4x4& mtx)
{
	if(mtx._44 == 0.0f)
	{
		// �������_
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
// �@���̕ϊ�
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
// �ǎC��x�N�g���Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline void Vector3ScratchWall(Vector3 *pOut, const Vector3& in, const Vector3& normal)
{
	// in�̋t�x�N�g���Ɩ@���̓��ς����
	float MinusInDotNormal = -(in.x * normal.x + in.y * normal.y + in.z * normal.z);

	// �ǎC��x�N�g���ݒ�
	pOut->x = in.x + MinusInDotNormal * normal.x;
	pOut->y = in.y + MinusInDotNormal * normal.y;
	pOut->z = in.z + MinusInDotNormal * normal.z;
}

//=============================================================================
// ���˃x�N�g���Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline void Vector3Reflection(Vector3 *pOut, const Vector3& in, const Vector3& normal)
{
	// in�̋t�x�N�g���Ɩ@���̓��ς����
	float MinusInDotNormal = -(in.x * normal.x + in.y * normal.y + in.z * normal.z);

	// ���˃x�N�g���ݒ�
	float x, y, z;
	x = in.x + MinusInDotNormal * 2.0f * normal.x;
	y = in.y + MinusInDotNormal * 2.0f * normal.y;
	z = in.z + MinusInDotNormal * 2.0f * normal.z;
	pOut->x = x;
	pOut->y = y;
	pOut->z = z;
}

//=============================================================================
// �s����Z
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
// �s�񌸎Z
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
// �s���Z
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
// �s�񏉊���
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
// �s��]�u
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
// �s�񎮎Z�o
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
// �t�s��쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void Matrix4x4Inverse(Matrix4x4 *pOut, const Matrix4x4& mtx)
{
	// �s�񎮎擾
	float det;
	Matrix4x4Determinant(&det, mtx);
	// �s�񎮂̒l�����ɏ������Ƃ��A�Ȃɂ����Ȃ�
	if(det <= 0.000005f && det >= -0.000005f)
	{
		return;
	}

	// �s�񎮂̋t��
	float invDet = 1.0f / det;
	// �]���q�Z�o
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

	// �t�s��ݒ�
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
// �X�P�[���s��쐬
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
// YawPitchRoll��]�s��쐬
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
// ���s�ړ��s��쐬
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
// �C�ӎ���]�s��쐬
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
// �s�񂩂�I�C���[�p�ɕϊ�(yaw, pitch, roll��)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
inline void Matrix4x4ToEulerAngle(Vector3 *pOut, const Matrix4x4& mtx)
{
	float sinPitch = mtx._23;
	// asin���s���Ȓl�ɂȂ�Ȃ��悤�ɂ���
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

	// �W���o�����b�N���l��
	if(fabs(sinPitch) > 0.99999f)
	{
		// cos(Pitch)��0�Ɖ��肵�Čv�Z
		// ���[�����w�f�B���O��0�ɐݒ肵�Ăǂ��炩���v�Z
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
// �s�񂩂�N�H�[�^�j�I���ɕϊ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/21
//=============================================================================
inline void Matrix4x4ToQuaternion(Quaternion* pOut, const Matrix4x4& mtx)
{
	// ���ʂ����肳���邽�߁Awxyz�̂����ꂩ�̒l�̐�Βl�̍ő�̂��̂����
	// �s��̑Ίp�𑀍삵�����̂��g�p
	// ���������O�����A���m�𐳊m�ɕ\��
	float FourWSquaredMinusOne =  mtx._11 + mtx._22 + mtx._33;
	float FourXSquaredMinusOne =  mtx._11 - mtx._22 - mtx._33;
	float FourYSquaredMinusOne = -mtx._11 + mtx._22 - mtx._33;
	float FourZSquaredMinusOne = -mtx._11 - mtx._22 + mtx._33;

	// �I�����ꂽ�����ɕ��򂷂�
	// Index
	// w:0 x:1 y:2 z:3
	int BiggestIndex = 0;
	// ��ԑ傫���l��I��
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

	// �ő�l
	float BiggestValue = sqrtFast(BiggestNumber + 1) * 0.5f;
	// �s��̊e�v�f�ɂ����Ēl���Z�o����N�H�[�^�j�I���̒l���Z�o����
	float mult = 0.25f / BiggestValue;
	// �ꍇ�ɂ���Čv�Z���@��ς���
	switch(BiggestIndex)
	{
		// ��ԑ傫���l��W
	case 0:
		{
			pOut->w = BiggestValue;
			pOut->x = (mtx._23 - mtx._32) * mult;
			pOut->y = (mtx._31 - mtx._13) * mult;
			pOut->z = (mtx._12 - mtx._21) * mult;
		}
		break;
		
		// ��ԑ傫���l��X
	case 1:
		{
			pOut->x = BiggestValue;
			pOut->w = (mtx._23 - mtx._32) * mult;
			pOut->y = (mtx._12 + mtx._21) * mult;
			pOut->z = (mtx._31 + mtx._13) * mult;
		}
		break;
		
		// ��ԑ傫���l��Y
	case 2:
		{
			pOut->y = BiggestValue;
			pOut->w = (mtx._31 - mtx._13) * mult;
			pOut->x = (mtx._12 + mtx._21) * mult;
			pOut->z = (mtx._23 + mtx._32) * mult;
		}
		break;
		
		// ��ԑ傫���l��Z
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
// �s����g��A��]�A���s�ړ������ɕ���
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/18
//=============================================================================
inline void Matrix4x4Decompose(Vector3* pTrans, Quaternion* pRot, Vector3* pScale, const Matrix4x4& mtx)
{
	// ���s�ړ�����
	pTrans->x = mtx._41;
	pTrans->y = mtx._42;
	pTrans->z = mtx._43;

	// �g�k����
	float sx = sqrtFast(mtx._11 * mtx._11 + mtx._12 * mtx._12 + mtx._13 * mtx._13);
	float sy = sqrtFast(mtx._21 * mtx._21 + mtx._22 * mtx._22 + mtx._23 * mtx._23);
	float sz = sqrtFast(mtx._31 * mtx._31 + mtx._32 * mtx._32 + mtx._33 * mtx._33);
	pScale->x = sx;
	pScale->y = sy;
	pScale->z = sz;

	// ��](��)����
	Matrix4x4ToQuaternion(pRot, mtx);
}

//=============================================================================
// �N�H�[�^�j�I����Z
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
// �N�H�[�^�j�I������
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionDot(float* pOut, const Quaternion& q1, const Quaternion& q2)
{
	*pOut = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
}

//=============================================================================
// �P���N�H�[�^�j�I���쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionIdentity(Quaternion *pOut)
{
	pOut->x = pOut->y = pOut->z = 0;
	pOut->w = 1.0f;
}

//=============================================================================
// �N�H�[�^�j�I�����K��
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
// �����N�H�[�^�j�I���쐬
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
// �t�N�H�[�^�j�I��(�������Đ��K�����ꂽ�N�H�[�^�j�I��)�쐬
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
// �w�肵�����ŃN�H�[�^�j�I����ݒ�
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
// �w�肵��2�̐��K�����ꂽ�N�H�[�^�j�I���̋��ʐ��`���
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void QuaternionSlerp(Quaternion *pOut, const Quaternion& q0, const Quaternion& q1, float t)
{
	// �x�N�g���̐��`�����𗘗p
	// �N�H�[�^�j�I���̊Ԃ̊p�x���Z�o
	// �N�H�[�^�j�I���̎��̓���
	float cosTheta = q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;

	// ����(cos)�����̂Ƃ��A������t�ɂ��āA�ŒZ���������悤�ɂ���
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

	// �x�N�g���𗘗p�������ʐ��`���
	float k0, k1;

	// ��̃N�H�[�^�j�I�������ڂ��Ă����ꍇ
	if(cosTheta >= 0.9999f)
	{
		// �����̐��`��Ԃɂ���
		k0 = 1 - t;
		k1 = t;
	}
	else
	{
		// sin���Z�o
		float sinTheta = sqrtFast(1.0f - cosTheta * cosTheta);

		// sin��cos����p�x���Z�o
		float theta = atan2Fast(sinTheta, cosTheta);

		// ����̋t�����v�Z���Ă���
		float OneOverSinTheta = 1.0f / sinTheta;

		// �N�H�[�^�j�I����ԌW���Z�o
		k0 = sinFast((1 - t) * theta) * OneOverSinTheta;
		k1 = sinFast(t * theta) * OneOverSinTheta;
	}

	// ��Ԃ����N�H�[�^�j�I���Z�o
	pOut->w = k0 * q0.w + k1 * q1.w;
	pOut->x = k0 * q0.x + k1 * q1.x;
	pOut->y = k0 * q0.y + k1 * q1.y;
	pOut->z = k0 * q0.z + k1 * q1.z;
}

//=============================================================================
// �I�C���[�p����N�H�[�^�j�I���ւ̕ϊ�
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
// �N�H�[�^�j�I������I�C���[�p�ɕϊ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/20
//=============================================================================
inline void QuaternionToEulerAngle(Vector3 *pOut, const Quaternion& q)
{
	// �s��̗v�f�ɕϊ����Ă���I�C���[�p�ɕϊ�����
	float sinPitch = -2.0f * (q.y * q.z - q.w * q.x);

	// �W���o�����b�N���l��
	if(fabs(sinPitch) > 0.99999f)
	{
		// �^�ォ�^���ɌŒ�
		pOut->x = static_cast<float>(KB_PI) * 0.5f;

		// �Ƃ肠�������[����0�ɐݒ�
		pOut->y = atan2Fast(-q.x * q.z + q.w * q.y, 0.5f - q.y * q.y - q.z * q.z);
		pOut->z = 0.0f;
	}
	else
	{
		// ���ʂɊp�x���v�Z����
		pOut->x = asinFast(sinPitch);
		pOut->y = atan2Fast(q.x * q.z + q.w * q.y, 0.5f - q.x * q.x - q.y * q.y);
		pOut->z = atan2Fast(q.x * q.y + q.w * q.z, 0.5f - q.x * q.x - q.z * q.z);
	}
}

//=============================================================================
// �N�H�[�^�j�I������s��ɕϊ�
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
// �w�肵�����W��C�ӎ��ŉ�]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/29
//=============================================================================
inline void Vector3RotationAxis(Vector3* pOut, const Vector3& pos, const Vector3& axis, const float& angle)
{
	Quaternion src, rotQ, rotQconj, temp, dest;

	// ���W���N�H�[�^�j�I���ɕϊ�
	src.x = pos.x;
	src.y = pos.y;
	src.z = pos.z;
	src.w = 0.0f;

	// ��]�N�H�[�^�j�I���쐬
	QuaternionRotationAxis(&rotQ, axis, angle);
	// �����쐬
	rotQconj.x = -rotQ.x;
	rotQconj.y = -rotQ.y;
	rotQconj.z = -rotQ.z;
	rotQconj.w = rotQ.w;

	// (q^-1)src
	QuaternionMultiply(&temp, rotQconj, src);
	// (q^-1)src(q)
	QuaternionMultiply(&dest, temp, rotQ);

	// dest��xyz���������̂܂܍��W�ɂȂ��Ă���B�֗�
	pOut->x = dest.x;
	pOut->y = dest.y;
	pOut->z = dest.z;
}

//=============================================================================
// ���ʂ𐳋K������
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
// ���ʂƓ_�̋��E����
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//=============================================================================
inline void PlaneDotVector3(float *pOut, const Plane& pl, const Vector3& point)
{
	*pOut = pl.a * point.x + pl.b * point.y + pl.c * point.z + pl.d;
}

//=============================================================================
// �_�Ɩ@�����畽�ʂ��Z�o����
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/11
//=============================================================================
inline void PlaneFromPointNormal(Plane *pOut, const Vector3& p, const Vector3& nor)
{
	// ���ʂ̌��_�Ƃ̋��������߂�
	pOut->d = -(p.x * nor.x + p.y * nor.y + p.z * nor.z);

	// �e�v�f��ݒ�
	pOut->a = nor.x;
	pOut->b = nor.y;
	pOut->c = nor.z;
}

//=============================================================================
// 3�_���畽�ʂ��Z�o����(p1 - p0 > p2 - p0 ���)
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
	// �@�������߂�
	pOut->a = y0 * z1 - z0 * y1;
	pOut->b = z0 * x1 - x0 * z1;
	pOut->c = x0 * y1 - y0 * x1;
	// ���_�Ɩʂ̋���
	pOut->d = -(pOut->a * p0.x + pOut->b * p0.y + pOut->c * p0.z);

	// ���ʐ��K��
	float mag = sqrtFast(pOut->a * pOut->a + pOut->b * pOut->b + pOut->c * pOut->c);

	if(mag <= 0.0f){ return; }

	float OneOverMag = 1.0f / mag;

	pOut->a = pOut->a * OneOverMag;
	pOut->b = pOut->b * OneOverMag;
	pOut->c = pOut->c * OneOverMag;
	pOut->d = pOut->d * OneOverMag;
}

//=============================================================================
// ���ʂ̉�]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline void PlaneRotation(Plane *pOut, const Plane& pl, const Matrix4x4& rot)
{
}

//=============================================================================
// ���ʂƌ����̌����������W
// Author : Ryo Kbayashi
// LastUpdate : 2014/5/12
//
// ret		: bool true:������ false:�͂���
//=============================================================================
inline bool PlaneRayIntersect(Vector3 *pOut, const Plane& pl, const Vector3& pos, const Vector3& ray)
{
	// ���ŕ\����
	// (pos + ray * k) DOT pl.normal = -pl.d
	// ����� k �ɂ��ĉ���
	// pOut�ɓ���l�� pos + ray * k �ƂȂ�

	// �����ƕ��ʂ̖@���̓��ς����
	float RayDotPlaneNormal = ray.x * pl.a + ray.y * pl.b + ray.z * pl.c;
	// �Z�o����lk
	float k;
	// ���ς�����Ȃ��[���ɋ߂��Ƃ�
	if(RayDotPlaneNormal >= -0.000005f && RayDotPlaneNormal <= 0.000005f)
	{
		// ���������ꏊ�𖳌�(float�ő�l)
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;

		// �����̎n�_�����ʏ�ɂ���Ƃ��A������
		if((pos.x * pl.a + pos.y * pl.b + pos.z * pl.c + pl.d) == 0.0f)
		{
			return true;
		}
	}
	else
	{
		// ��L�̎���W�J
		k = (-pl.d - (pos.x * pl.a + pos.y * pl.b + pos.z * pl.c)) / RayDotPlaneNormal;

		// �����_���Z�o
		pOut->x = pos.x + ray.x * k;
		pOut->y = pos.y + ray.y * k;
		pOut->z = pos.z + ray.z * k;

		// k���v���X�ȏ�̂Ƃ��Aray�̌����Ă�������ɖʂ�����̂ŁA������
		if(k >= 0)
		{
			return true;
		}
	}

	// �͂���
	return false;
}

//=============================================================================
// ���ʂƐ����̌����������W
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//=============================================================================
inline bool PlaneLineSegmentIntersect(Vector3 *pOut, const Plane& pln, const Vector3& p0, const Vector3& p1)
{
	// ���ʂƐ����̌�����
	// (start + (end - start) * k) DOT pln.normal = -pln.d �ƂȂ�
	// ����� k �ɂ��ĉ���

	// p0��p1���ʂ̕\�����̂ǂ���ɂ��邩���ׂ�
	float Point0FrontBack, Point1FrontBack;
	PlaneDotVector3(&Point0FrontBack, pln, p0);
	PlaneDotVector3(&Point1FrontBack, pln, p1);
	// p0��p1���ʏ�ɑ��݂���t���O
	bool Point0IsOnFace = (Point0FrontBack >= -0.000005f && Point0FrontBack <= 0.000005f);
	bool Point1IsOnFace = (Point1FrontBack >= -0.000005f && Point1FrontBack <= 0.000005f);
	
	// �����x�N�g��
	float SegX = p1.x - p0.x;
	float SegY = p1.y - p0.y;
	float SegZ = p1.z - p0.z;
	// �����x�N�g���̒��������
	float SegMag = sqrtFast(SegX * SegX + SegY * SegY + SegZ * SegZ);

	// p0��p1���قڈ�v���Ă����ꍇ
	if(SegMag >= -0.000005f && SegMag <= 0.000005f)
	{
		// �_���ʏ�ɑ��݂����ꍇ
		if(Point0IsOnFace){ *pOut = p0; return true; }
		// �ʏ�ɑ��݂��Ȃ��ꍇ
		// ���������ꏊ�𖳌�(float�ő�l)
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;
		// �͂���
		return false;
	}

	// �����x�N�g���̎n�_
	Vector3 StartPoint = p0;
	// �����x�N�g���Ɩʂ̖@���̓��ς����
	float SegDotPlaneNormal = SegX * pln.a + SegY * pln.b + SegZ * pln.c;

	// �����Ɩʂ��قڕ��s�Ȏ�
	if(SegDotPlaneNormal >= -0.000005f && SegDotPlaneNormal <= 0.000005f)
	{
		// ���������ꏊ�𖳌�(float�ő�l)
		pOut->x = FLT_MAX;
		pOut->y = FLT_MAX;
		pOut->z = FLT_MAX;

		// p0��p1���ʏ�ɑ��݂���t���O
		bool Point0IsOnFace = (Point0FrontBack >= -0.000005f && Point0FrontBack <= 0.000005f);
		bool Point1IsOnFace = (Point1FrontBack >= -0.000005f && Point1FrontBack <= 0.000005f);

		// �����̒[�̂ǂ��炩���ʏ�ɂ���Ƃ��A������
		// p0��p1�������Ƃ��ʏ�ɂ���
		if(Point0IsOnFace &&
			Point1IsOnFace)
		{
			return true;
		}
		// p0�����ʏ�ɂ���
		else if(Point0IsOnFace)
		{
			*pOut = p0;
			return true;
		}
		// p1�����ʏ�ɂ���
		else if(Point1IsOnFace)
		{
			*pOut = p1;
			return true;
		}
	}
	else
	{
		// �����x�N�g���Ɩʂ̖@���̓��ς��v���X�������Ƃ�
		// �x�N�g�����ʂƓ��������������Ă�̂ŁA���΂ɂ��Ėʂƌ��������悤�ɂ���
		if(SegDotPlaneNormal > 0.0f)
		{
			// ���ς̌��ʂ��t�ɂ���
			SegDotPlaneNormal = -SegDotPlaneNormal;
			// �����x�N�g�����t�����ɂ���
			SegX = -SegX;
			SegY = -SegY;
			SegZ = -SegZ;
			// �����x�N�g���̎n�_��ς���
			StartPoint = p1;
		}
		// k �ɂ��ĉ���
		float StartPointDotNormal = (StartPoint.x * pln.a + StartPoint.y * pln.b + StartPoint.z * pln.c);
		float k = (-pln.d - StartPointDotNormal) / SegDotPlaneNormal;

		// k �� 0.0�ȏ�A1.0�ȉ��̂Ƃ������̊Ԃɖʂ����݂���̂ł�����
		if(k >= 0.0f && k <= 1.0f)
		{
			// �����������W�ݒ�
			pOut->x = StartPoint.x + SegX * k;
			pOut->y = StartPoint.y + SegY * k;
			pOut->z = StartPoint.z + SegZ * k;
			// ������
			return true;
		}
		// k �� 0.0��菬�����A1.0���傫���Ƃ������̊Ԃɖʂ����݂��Ȃ��̂ł͂���
		else
		{
			// ���������ꏊ�𖳌�(float�ő�l)
			pOut->x = FLT_MAX;
			pOut->y = FLT_MAX;
			pOut->z = FLT_MAX;
		}
	}

	// �͂���
	return false;
}

//=============================================================================
// ���[���h�s��쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/23
//=============================================================================
inline void SetWorldMatrix(Matrix4x4 *pOut, const Vector3 &trans, const Vector3 &rot, const Vector3 &scl)
{
	// �ϐ��錾
	float CosX = cosFast(rot.x);
	float SinX = sinFast(rot.x);
	float CosY = cosFast(rot.y);
	float SinY = sinFast(rot.y);
	float CosZ = cosFast(rot.z);
	float SinZ = sinFast(rot.z);

	// �s��v�f�ݒ�
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
// ���[���h�t�s��쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void SetWorldInverseMatrix(Matrix4x4 *pOut, const Matrix4x4& mtx)
{
	// �s�񎮂��Z�o
	float det;
	Matrix4x4Determinant(&det, mtx);
	// �s�񎮂̒l�����ɏ������Ƃ��A�Ȃɂ����Ȃ�
	if((det <= 0.000005f) && (det >= -0.000005f))
	{
		return;
	}

	// �s�񎮂̋t��
	float invDet = 1.0f / det;
	// �]���q���Z�o
	float i11 = mtx._22 * mtx._33 - mtx._23 * mtx._32;
	float i12 = mtx._23 * mtx._31 - mtx._21 * mtx._33;
	float i13 = mtx._21 * mtx._32 - mtx._22 * mtx._31;
	float i21 = mtx._32 * mtx._13 - mtx._33 * mtx._12;
	float i22 = mtx._33 * mtx._11 - mtx._31 * mtx._13;
	float i23 = mtx._31 * mtx._12 - mtx._32 * mtx._11;
	float i31 = mtx._12 * mtx._23 - mtx._13 * mtx._22;
	float i32 = mtx._13 * mtx._21 - mtx._11 * mtx._23;
	float i33 = mtx._11 * mtx._22 - mtx._12 * mtx._21;

	// �s��ɒl��ݒ�
	pOut->_11 = i11 * invDet;
	pOut->_12 = i21 * invDet;
	pOut->_13 = i31 * invDet;
	pOut->_21 = i12 * invDet;
	pOut->_22 = i22 * invDet;
	pOut->_23 = i32 * invDet;
	pOut->_31 = i13 * invDet;
	pOut->_32 = i23 * invDet;
	pOut->_33 = i33 * invDet;

	// �s�񎮂̒l��0�ȉ��̎�
	pOut->_14 = pOut->_24 = pOut->_34 = 0.0f;
	pOut->_41 = -mtx._41;
	pOut->_42 = -mtx._42;
	pOut->_43 = -mtx._43;
	pOut->_44 = 1.0f;
}

//=============================================================================
// �r���[�s��쐬(����n)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/25
//=============================================================================
inline void SetViewMatrixLH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
{
	// �����x�N�g���ݒ�
	Vector3 normRay;	// �����x�N�g��
	normRay.x = ray.x - pos.x;
	normRay.y = ray.y - pos.y;
	normRay.z = ray.z - pos.z;
	// �����x�N�g���𐳋K��
	Vector3Normalize(&normRay, normRay);

	// �E�����x�N�g�����Z�o�A���K��
	Vector3 normRight;	// �E�����x�N�g��
	Vector3NormalizeCross(&normRight, up, normRay);

	// ������x�N�g����ݒ�
	Vector3	normUp;
	Vector3Cross(&normUp, normRay, normRight);
	
	// ���݂̍��W�̋t�ʒu�����߂�
	Vector3 invPos;
	invPos.x = -(pos.x * normRight.x + pos.y * normRight.y + pos.z * normRight.z);
	invPos.y = -(pos.x * normUp.x	+ pos.y * normUp.y	+ pos.z * normUp.z);
	invPos.z = -(pos.x * normRay.x	+ pos.y * normRay.y	+ pos.z * normRay.z);
	
	// �s��ɒl��ݒ�
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
// �r���[�s��쐬(�E��n)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/23
//=============================================================================
inline void SetViewMatrixRH(Matrix4x4* pOut, const Vector3& pos, const Vector3& ray, const Vector3& up)
{
	// �����x�N�g���ݒ�
	Vector3 normRay;	// �����x�N�g��
	normRay.x = pos.x - ray.x;
	normRay.y = pos.y - ray.y;
	normRay.z = pos.z - ray.z;
	// �����x�N�g���𐳋K��
	Vector3Normalize(&normRay, normRay);

	// �E�����x�N�g�����Z�o�A���K��
	Vector3 normRight;	// �E�����x�N�g��
	Vector3NormalizeCross(&normRight, up, normRay);

	// ������x�N�g����ݒ�
	Vector3	normUp;
	Vector3Cross(&normUp, normRay, normRight);
	
	// ���݂̍��W�̋t�ʒu�����߂�
	Vector3 invPos;
	invPos.x = -(pos.x * normRight.x + pos.y * normRight.y + pos.z * normRight.z);
	invPos.y = -(pos.x * normUp.x	+ pos.y * normUp.y	+ pos.z * normUp.z);
	invPos.z = -(pos.x * normRay.x	+ pos.y * normRay.y	+ pos.z * normRay.z);
	
	// �s��ɒl��ݒ�
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
// 3������r���[�s���ݒ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/29
//=============================================================================
inline void SetViewMatrixFromAxis(Matrix4x4* pOut, const Vector3& pos, const Vector3& right, const Vector3& up, const Vector3& front)
{
	// ���݂̍��W�̋t�ʒu�����߂�
	Vector3 invPos;
	invPos.x = -(pos.x * right.x	+ pos.y * right.y	+ pos.z * right.z);
	invPos.y = -(pos.x * up.x		+ pos.y * up.y		+ pos.z * up.z);
	invPos.z = -(pos.x * front.x	+ pos.y * front.y	+ pos.z * front.z);
	
	// �s��ɒl��ݒ�
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
// �ˉe�s��쐬(DirectX)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void SetProjectionMatrixLH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
{
	float div = tanFast(FoV * 0.5f);
	float FarMinusNear = farSurface - nearSurface;
	// �[���`�F�b�N
	if((div >= -0.00005f && div <= 0.00005f) || FarMinusNear <= 0.0f || aspect <= 0.f)
	{
		// ���������ɕԂ�
		return;
	}

	// �s��ɒl��ݒ�
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
// �ˉe�s��쐬(OpenGL)
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/27
//=============================================================================
inline void SetProjectionMatrixRH(Matrix4x4* pOut, const float& FoV, const float& aspect, const float& nearSurface, const float& farSurface)
{
	float div = tanFast(FoV * 0.5f);
	float FarMinusNear = farSurface - nearSurface;
	// �[���`�F�b�N
	if((div >= -0.00005f && div <= 0.00005f) || FarMinusNear <= 0.0f || aspect <= 0.f)
	{
		// ���������ɕԂ�
		return;
	}

	// �s��ɒl��ݒ�
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
// ���s���e�s��쐬(OpenGL)
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
// �r���[�|�[�g�s��쐬
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
// �X�N���[�����W�����[���h���W�ɕϊ����A���[���h���W�ƌ������o��(����n)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
// ret		: void
// arg1		: Vector3* ���[���h���W
// arg2		: Vector3* �X�N���[�����W���王����̉������鐳�K�����ꂽ����
// arg3		: float �X�N���[�����x���W
// arg4		: float �X�N���[�����y���W
// arg5		: float �X�N���[���n�_x���W�I�t�Z�b�g
// arg6		: float �X�N���[���n�_y���W�I�t�Z�b�g
// arg7		: float �o�b�N�o�b�t�@�̉���
// arg8		: float �o�b�N�o�b�t�@�̏c��
// arg9		: const Matrix4x4& �ˉe�s��
// arg10	: const Matrix4x4& �r���[�t�s��
//=============================================================================
inline void ScreenToWorldPositionLH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)
{
	// �X�N���[�����W���r���|�[�g�Ǝˉe�̋t�s��ŕϊ�����
	float x = (sx * 2.0f / fBackBufferWidth - 1) / proj._11;
	float y = (-sy * 2.0f / fBackBufferHeight + 1) / proj._22;

	// ���_
	Vector3 WorldPos(0.0f, 0.0f, 0.0f);
	// �r���[��Ԃ̉��ɐL�т����
	Vector3 ray(x, y, 1.0f);	// ���̓v���X

	// ���[���h���W��Ԃɕϊ�
	Vector3TransformCoord(pWorldPos, WorldPos, invView);
	// ������ϊ�
	Vector3TransformNormal(pRay, ray, invView);
	// �����𐳋K��
	Vector3Normalize(pRay, *pRay);
}

//=============================================================================
// �X�N���[�����W�����[���h���W�ɕϊ����A���[���h���W�ƌ������o��(�E��n)
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
// ret		: void
// arg1		: Vector3* ���[���h���W
// arg2		: Vector3* �X�N���[�����W���王����̉������鐳�K�����ꂽ����
// arg3		: float �X�N���[�����x���W
// arg4		: float �X�N���[�����y���W
// arg5		: float �X�N���[���n�_x���W�I�t�Z�b�g
// arg6		: float �X�N���[���n�_y���W�I�t�Z�b�g
// arg7		: float �o�b�N�o�b�t�@�̉���
// arg8		: float �o�b�N�o�b�t�@�̏c��
// arg9		: const Matrix4x4& �ˉe�s��
// arg10	: const Matrix4x4& �r���[�t�s��
//=============================================================================
inline void ScreenToWorldPositionRH(Vector3 *pWorldPos, Vector3 *pRay, float sx, float sy,
						   float fScreenOffsetX, float fScreenOffsetY,
						   float fBackBufferWidth, float fBackBufferHeight,
						   const Matrix4x4& proj, const Matrix4x4& invView)
{
	// �X�N���[�����W���r���|�[�g�Ǝˉe�̋t�s��ŕϊ�����
	float x = (sx * 2.0f / fBackBufferWidth - 1) / proj._11;
	float y = (-sy * 2.0f / fBackBufferHeight + 1) / proj._22;

	// ���_
	Vector3 WorldPos(0.0f, 0.0f, 0.0f);
	// �r���[��Ԃ̉��ɐL�т����
	Vector3 ray(x, y, -1.0f);	// ���̓}�C�i�X

	// ���[���h���W��Ԃɕϊ�
	Vector3TransformCoord(pWorldPos, WorldPos, invView);
	// ������ϊ�
	Vector3TransformNormal(pRay, ray, invView);
	// �����𐳋K��
	Vector3Normalize(pRay, *pRay);
}

//=============================================================================
// �w�肵����̒l�̐��`��Ԃ��Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<typename T>
inline void ComputeLerp(T* pOut, const T& p0, const T& p1, float t)
{
	// ��ԃt���[���l���ۂ߂�
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
// ���_�𒆐S�ɂ����p���x���Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/26
//=============================================================================
inline void ComputeAngularVelocity(Vector3* pOut, const Vector3& pos,const Vector3& vec)
{
	// �����̓����Z�o
	float fSquaredDistance = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z;
	
	// ���������ɋ߂��Ƃ�
	if(fSquaredDistance <= 0.000005f)
	{
		// �p���x��0�ɂ���
		pOut->x = 0.0f;
		pOut->y = 0.0f;
		pOut->z = 0.0f;
		return;
	}
	
	// �p���x(���� �~ �ړ��� / �������)���Z�o
	// �����ƈړ��ʂ̊O�ς��Ƃ�
	Vector3Cross(pOut, pos, vec);

	float OneOverSquaredDistance = 1.0f / fSquaredDistance;

	pOut->x *= OneOverSquaredDistance;
	pOut->y *= OneOverSquaredDistance;
	pOut->z *= OneOverSquaredDistance;
}

//=============================================================================
// ���S���w�肵���p���x���Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/26
//=============================================================================
inline void ComputeAngularVelocity(Vector3* pOut, const Vector3& center, const Vector3& pos, const Vector3& vec)
{
	// �����̓����Z�o
	Vector3 CenterToPos(pos.x - center.x, pos.y - center.y, pos.z - center.z);
	float fSquaredDistance = CenterToPos.x * CenterToPos.x + CenterToPos.y * CenterToPos.y + CenterToPos.z * CenterToPos.z;
	
	// ���������ɋ߂��Ƃ�
	if(fSquaredDistance <= 0.000005f)
	{
		// �p���x��0�ɂ���
		pOut->x = 0.0f;
		pOut->y = 0.0f;
		pOut->z = 0.0f;
		return;
	}
	
	// �p���x(���� �~ �ړ��� / �������)���Z�o
	// �����ƈړ��ʂ̊O�ς��Ƃ�
	Vector3Cross(pOut, CenterToPos, vec);

	float OneOverSquaredDistance = 1.0f / fSquaredDistance;

	pOut->x *= OneOverSquaredDistance;
	pOut->y *= OneOverSquaredDistance;
	pOut->z *= OneOverSquaredDistance;
}

//=============================================================================
// ��̃x�N�g������A����̔��˃x�N�g�����Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/29
//=============================================================================
inline bool ComputeCollideLineToLineXZ(
	Vector3* pCollidePoint,
	float* pRate,	// �N�������Ƃ��̃x�N�g���̔䗦
	Vector3* pReflectVec,
	const Vector3& pos0st,
	const Vector3& pos0ed,
	const Vector3& pos1st,
	const Vector3& pos1ed)
{
	// �e�x�N�g���Z�o
	Vector3 vec0 = pos0ed - pos0st;
	Vector3 vec1 = pos1ed - pos1st;
	Vector3 vec2 = pos0st - pos1st;

	// vec0��vec1�̊O�ς����(�����t�ʐ�Sv0v1)
	float SV0V1 = vec0.z * vec1.x - vec0.x * vec1.z;

	// �x�N�g������v���Ă���A�܂��͂ǂ��炩���[���x�N�g��
	if(SV0V1 == 0.0f)
	{
		return false;
	}

	// vec1��vec2�̊O�ςŎZ�o�����ʐς��o��(�����t�ʐ�sv1v2)
	float sv1v2 = vec1.z * vec2.x - vec1.x * vec2.z;

	// sv1v2��SV0V1�̕����t�ʐς̔���o��
	float fRatioOfSV1V2OverSV0V1 = sv1v2 / SV0V1;

	// �����n�_���n�_�ƏI�_�̓����ɂ��邩
	if(fRatioOfSV1V2OverSV0V1 >= 0.0f && 
	   fRatioOfSV1V2OverSV0V1 <= 1.0f)
	{
		// vec0��vec2�̊O�ςŎY�o�����ʐς��o��(�����t�ʐ�sv0v2)
		float sv0v2 = vec0.z * vec2.x - vec0.x * vec2.z;

		// sv0v2��SV0V1�����t�ʐϔ���o��
		float fRatioOfSV0V2OverSV0V1 = sv0v2 / SV0V1;

		// �����n�_���n�_�ƏI�_�̓����ɂ��邩
		if(fRatioOfSV0V2OverSV0V1 >= 0.0f &&
		   fRatioOfSV0V2OverSV0V1 <= 1.0f)
		{
			// ��������

			// ��_�����߂�
			if(pCollidePoint)
			{
				*pCollidePoint = vec0 * fRatioOfSV1V2OverSV0V1 + pos0st;
			}

			// ���������ꏊ��vec0���̔�����߂�
			if(pRate)
			{
				*pRate = fRatioOfSV0V2OverSV0V1;
			}

			// ���˃x�N�g�������߂�
			if(pReflectVec)
			{
				float dotVec0Vec1 = vec0.x * vec1.x + vec0.z * vec1.z;
				
				// �x�N�g���̒��������߂�
				float mag0 = sqrtFast(vec0.x * vec0.x + vec0.z * vec0.z);
				float mag1 = sqrtFast(vec1.x * vec1.x + vec1.z * vec1.z);

				// vec0��vec1�̊Ԃ̊p���Z�o
				float fAngle = -acosf(dotVec0Vec1 / (mag0 * mag1));

				// ���˃x�N�g��
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
// ��̃x�N�g������A����̕ǎC��x�N�g�����Z�o
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/18
//=============================================================================
inline bool ComputeCollideLineToLineXZScratch(
	Vector3* pCollidePoint,
	float* pRate,	// �N�������Ƃ��̃x�N�g���̔䗦
	Vector3* pScratchVec,
	const Vector3& pos0st,
	const Vector3& pos0ed,
	const Vector3& pos1st,
	const Vector3& pos1ed)
{
	// �e�x�N�g���Z�o
	Vector3 vec0 = pos0ed - pos0st;
	Vector3 vec1 = pos1ed - pos1st;
	Vector3 vec2 = pos0st - pos1st;

	// vec0��vec1�̊O�ς����(�����t�ʐ�Sv0v1)
	float SV0V1 = vec0.z * vec1.x - vec0.x * vec1.z;

	// �x�N�g������v���Ă���A�܂��͂ǂ��炩���[���x�N�g��
	if(SV0V1 == 0.0f)
	{
		return false;
	}

	// vec1��vec2�̊O�ςŎZ�o�����ʐς��o��(�����t�ʐ�sv1v2)
	float sv1v2 = vec1.z * vec2.x - vec1.x * vec2.z;

	// sv1v2��SV0V1�̕����t�ʐς̔���o��
	float fRatioOfSV1V2OverSV0V1 = sv1v2 / SV0V1;

	// �����n�_���n�_�ƏI�_�̓����ɂ��邩
	if(fRatioOfSV1V2OverSV0V1 >= 0.0f && 
	   fRatioOfSV1V2OverSV0V1 <= 1.0f)
	{
		// vec0��vec2�̊O�ςŎY�o�����ʐς��o��(�����t�ʐ�sv0v2)
		float sv0v2 = vec0.z * vec2.x - vec0.x * vec2.z;

		// sv0v2��SV0V1�����t�ʐϔ���o��
		float fRatioOfSV0V2OverSV0V1 = sv0v2 / SV0V1;

		// �����n�_���n�_�ƏI�_�̓����ɂ��邩
		if(fRatioOfSV0V2OverSV0V1 >= 0.0f &&
		   fRatioOfSV0V2OverSV0V1 <= 1.0f)
		{
			// ��������

			// ��_�����߂�
			if(pCollidePoint)
			{
				*pCollidePoint = vec0 * fRatioOfSV1V2OverSV0V1 + pos0st;
			}

			// ���������ꏊ��vec0���̔�����߂�
			if(pRate)
			{
				*pRate = fRatioOfSV0V2OverSV0V1;
			}

			// �ǎC��x�N�g�������߂�
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