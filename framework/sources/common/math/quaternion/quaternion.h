//*****************************************************************************
//
// クォータニオンクラス
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************
#pragma once
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

//*****************************************************************************
// 前方参照
//*****************************************************************************
struct VECTOR3;

//*****************************************************************************
// 構造体定義
//*****************************************************************************
struct QUATERNION
{
	/**
	*	デフォルトコンストラクタ
	*
	*	軸成分を0.0fで初期化。w=1に初期化
	*
	*	@param	void
	*/
	QUATERNION() :
	_x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f){}

	/**
	*	引数付コンストラクタ
	*
	*	引数で初期化
	*
	*	@param	void
	*/
	QUATERNION(float x, float y, float z, float w) :
	_x(x), _y(y), _z(z), _w(w){}
	
	/**
	*	デストラクタ
	*/
	~QUATERNION(){}
	
	/**
	*	クォータニオン回転軸
	*
	*	引数で初期化
	*
	*	@param	VECTOR3	任意軸
	*	@param	float	回転量
	*/
	QUATERNION RotationAxis(const VECTOR3& axis, const float angle);
	
	/**
	*	クォータニオンから回転量変換
	*
	*	引数で初期化
	*
	*	@param	QUATERNION 回転クォータニオン
	*/
	VECTOR3 YawPitchRollFromQuaternion(const QUATERNION& q);

	//-----------------------------------------------------
	// 符号変換

	QUATERNION operator+(void){return *this;}
	QUATERNION operator-(void){return QUATERNION(-_x,-_y,-_z,-_w);}
	
	//-----------------------------------------------------
	// 乗算

	QUATERNION operator*(const QUATERNION& rhs) const;
	
	//-----------------------------------------------------
	// 乗算代入

	QUATERNION& operator*=(const QUATERNION& rhs);

	union
	{
		struct
		{
			float _x, _y, _z, _w;
		};
		float _q[4];
	};
};

#endif	// _QUATERNION_H_

//---------------------------------- EOF --------------------------------------
