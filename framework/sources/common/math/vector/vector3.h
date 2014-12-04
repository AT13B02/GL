//*****************************************************************************
//
// 3次元ベクトルクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	3次元ベクトルクラス
*
*	3次元ベクトルで使う処理もここに書く
*
*/
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

//*****************************************************************************
// インクルード
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct VECTOR3
{
public:
	f32 _x;
	f32 _y;
	f32 _z;

	//-----------------------------------------------------
	// コンストラクタ

	/**
	*	デフォルトコンストラクタ
	*
	*	0.0fで初期化
	*
	*	@param	void
	*/
	VECTOR3(void){_x = 0.0f;_y = 0.0f;_z = 0.0f;}

	/**
	*	コンストラクタ
	*
	*	要素を指定して初期化
	*
	*	@param	f32 x
	*	@param	f32 y
	*	@param	f32 z
	*/
	VECTOR3(const f32& x,const f32& y,const f32& z){_x = x;_y = y;_z = z;}

	/**
	*	コピーコンストラクタ
	*
	*	要素をコピーして初期化
	*
	*	@param	VECTOR3
	*/
	VECTOR3(const VECTOR3& vector){_x = vector._x;_y = vector._y;_z = vector._z;}

	//-----------------------------------------------------
	// ベクトルの関数

	/**
	*	単位ベクトル化
	*
	*	ベクトルを単位ベクトルにする
	*
	*	@param	void
	*	@return	void
	*/
	const VECTOR3& Normalize(void);

	/**
	*	ベクトルの大きさの取得
	*
	*	ベクトルの大きさを取得する
	*
	*	@param	void
	*	@return	f32 ベクトルの大きさ
	*/
	f32 Magnitude(void) const;

	/**
	*	ベクトルの内積
	*
	*	ベクトルの内積計算を行う
	*	演算結果は返り値
	*
	*	@param	VECTOR3 ベクトル
	*	@return	f32 内積結果
	*/
	f32 DotProduct(const VECTOR3& vector) const;

	/**
	*	ベクトルの外積
	*
	*	ベクトルの外積計算を行う
	*	演算結果は返り値
	*
	*	@param	VECTOR3 ベクトル
	*	@return	VECTOR3 外積結果
	*/
	VECTOR3 CrossProduct(const VECTOR3& vector) const;

	//-----------------------------------------------------
	// 符号変換

	VECTOR3 operator+(void){return *this;}
	VECTOR3 operator-(void){return VECTOR3(-_x,-_y,-_z);}

	//-----------------------------------------------------
	// スカラーとの計算

	VECTOR3 operator+(const f32& fValue) const;
	VECTOR3 operator-(const f32& fValue) const;
	VECTOR3 operator*(const f32& fValue) const;
	VECTOR3 operator/(const f32& fValue) const;

	VECTOR3& operator+=(const f32& fValue);
	VECTOR3& operator-=(const f32& fValue);
	VECTOR3& operator*=(const f32& fValue);
	VECTOR3& operator/=(const f32& fValue);

	//-----------------------------------------------------
	// ベクトルとの計算

	VECTOR3 operator+(const VECTOR3& vector) const;
	VECTOR3 operator-(const VECTOR3& vector) const;

	VECTOR3& operator+=(const VECTOR3& vector);
	VECTOR3& operator-=(const VECTOR3& vector);

}VECTOR3;

#endif // _VECTOR3_H_

//---------------------------------- EOF --------------------------------------
