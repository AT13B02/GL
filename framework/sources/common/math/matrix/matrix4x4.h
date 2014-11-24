//*****************************************************************************
//
// 4x4行列クラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	4x4の行列クラス
*
*	行列で使う計算処理もここでやる
*
*/
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _MATRIX4x4_H_
#define _MATRIX4x4_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "common/math/vector/vector3.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct MATRIX4x4
{
public:
	f32 _11;	f32 _12;	f32 _13;	f32 _14;
	f32 _21;	f32 _22;	f32 _23;	f32 _24;
	f32 _31;	f32 _32;	f32 _33;	f32 _34;
	f32 _41;	f32 _42;	f32 _43;	f32 _44;

	//-----------------------------------------------------
	// コンストラクタ

	MATRIX4x4(void)
	{
		_11 = 1.0f;	_12 = 0.0f;	_13 = 0.0f;	_14 = 0.0f;
		_21 = 0.0f;	_22 = 1.0f;	_23 = 0.0f;	_24 = 0.0f;
		_31 = 0.0f;	_32 = 0.0f;	_33 = 1.0f;	_34 = 0.0f;
		_41 = 0.0f;	_42 = 0.0f;	_43 = 0.0f;	_44 = 1.0f;
	}

	MATRIX4x4(f32 in11,	f32 in12,	f32 in13,	f32 in14,
			  f32 in21,	f32 in22,	f32 in23,	f32 in24,
			  f32 in31,	f32 in32,	f32 in33,	f32 in34,
			  f32 in41,	f32 in42,	f32 in43,	f32 in44)
	{
		_11 = in11;	_12 = in12;	_13 = in13;	_14 = in14;
		_21 = in21;	_22 = in22;	_23 = in23;	_24 = in24;
		_31 = in31;	_32 = in32;	_33 = in33;	_34 = in34;
		_41 = in41;	_42 = in42;	_43 = in43;	_44 = in44;
	}

	//-----------------------------------------------------
	// 特別な行列を設定

	// 単位行列
	void SetIdentity(void);

	// 平行移動行列の設定
	void SetTlanslation(const f32& fX, const f32& fY, const f32& fZ);

	// 平行移動行列の設定
	void SetTlanslation(const VECTOR3& Vector);

	// スケール行列の設定
	void SetScaling(const f32& fScaleX, const f32& fScaleY, const f32& fScaleZ);

	// YawPitchRoll回転行列の設定
	void SetYawPitchRoll(const f32& fRotX, const f32& fRotY, const f32& fRotZ);

	// 任意軸回転行列の設定
	void SetRotationArbitraryAxis(const VECTOR3& Axis, const f32& fAngle);

	// パースペクティブ行列の設定
	void SetPerspectiveFovLH(const f32& fDegree,const f32& fAspect,const f32& fNear,const f32& fFar);

	// パースペクティブ行列の設定
	void SetPerspectiveFovRH(const f32& fDegree,const f32& fAspect,const f32& fNear,const f32& fFar);

	// カメラ行列の設定
	void SetLookAtLH(const VECTOR3& Eye,const VECTOR3& LookAt,const VECTOR3& Up);

	// カメラ行列の設定
	void SetLookAtRH(const VECTOR3& Eye,const VECTOR3& LookAt,const VECTOR3& Up);

	//-----------------------------------------------------
	// 行列からの取得

	// 行列式
	f32 GetDeterminant(void);

	// 逆行列
	MATRIX4x4 GetInverse(void);

	// 回転行列の逆行列を取得
	MATRIX4x4 GetInverseRotation(void);

	// 転置行列
	MATRIX4x4 GetTranspose(void);

	// オイラー角の取得
	VECTOR3 GetEulerAngle(void);

	//-----------------------------------------------------
	// 符号計算

	MATRIX4x4 operator+(void) const{ return *this; }
	MATRIX4x4 operator-(void) const{ return MATRIX4x4(-_11,-_12,-_13,-_14,
													  -_21,-_22,-_23,-_24,
													  -_31,-_32,-_33,-_34,
													  -_41,-_42,-_43,-_44);}

	//-----------------------------------------------------
	// 係数との計算

	MATRIX4x4 operator*(const f32& fValue) const;
	MATRIX4x4 operator/(const f32& fValue) const;

	MATRIX4x4& operator*=(const f32& fValue);
	MATRIX4x4& operator/=(const f32& fValue);

	//-----------------------------------------------------
	// 行列同士の計算

	MATRIX4x4 operator+(const MATRIX4x4& Matrix) const;
	MATRIX4x4 operator-(const MATRIX4x4& Matrix) const;
	MATRIX4x4 operator*(const MATRIX4x4& Matrix) const;

	MATRIX4x4& operator+=(const MATRIX4x4& Matrix);
	MATRIX4x4& operator-=(const MATRIX4x4& Matrix);
	MATRIX4x4& operator*=(const MATRIX4x4& Matrix);

	void operator=(const MATRIX4x4& Matrix);

}MATRIX4x4;

#endif// _MATRIX4x4_H_

//---------------------------------- EOF --------------------------------------
