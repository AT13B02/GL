//*****************************************************************************
//
// カメラクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"

// common
#include "common/math/math.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCamera : public CBasic
{
public:
	// 作成処理
	static CCamera* Create(CDeviceHolder* device_holder);

	// 初期化処理
	bool Init(void);

	// 更新処理
	void Update(void);

	// カメラの設定
	virtual void Set(void) = 0;

	// カメラの行列を取得
	MATRIX4x4& view_matrix(void){return view_matrix_;}

	// カメラの逆行列を取得
	MATRIX4x4& inverse_matrix(void){return inverse_matrix_;}

	// 視点の設定
	void SetEye(const VECTOR3& eye);

	// 注視点の設定
	void SetLookAt(const VECTOR3& look_at);

	// 視点からのローテーションの設定
	void SetRotationEye(const VECTOR3& rotation);

	// 注視点からのローテーションの設定
	void SetRotationLookAt(const VECTOR3& rotation);

	// パースペクティブの設定
	void SetPerspective(const f32& perspective_degree,const f32& perspective_aspect,const f32& perspective_near,const f32& perspective_far);

protected:
	// コンストラクタ
	CCamera(CDeviceHolder* device_holder);

	// デストラクタ
	virtual ~CCamera(void);

	// グラフィックデバイス
	CDeviceHolder* device_holder_;

	// 視点
	VECTOR3 eye_;

	// 注視点
	VECTOR3 look_at_;

	// 上方向ベクトル
	VECTOR3 up_;

	// 視点と注視点の距離
	f32 length_;

	// 視点と注視点の角度
	VECTOR3 rotation_;

	// パースペクティブ角度
	f32 perspective_degree_;

	// パースペクティブアスペクト比
	f32 perspective_aspect_;

	// パースペクティブニア値
	f32 perspective_near_;

	// パースペクティブファー値
	f32 perspective_far_;

	// プロジェクション行列
	MATRIX4x4 projection_matrix_;

	// ビューマトリクス
	MATRIX4x4 view_matrix_;

	// カメラの逆行列
	MATRIX4x4 inverse_matrix_;

private:
	// ローテーションの正規化
	VECTOR3 NormalizeRotation(const VECTOR3& rotation);
};

#endif	// _GL_CAMERA_H_

//---------------------------------- EOF --------------------------------------
