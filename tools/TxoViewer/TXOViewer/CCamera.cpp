//=============================================================================
//
// カメラ処理 [CCamera.cpp]
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CCamera.h"
#include "main.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
#ifdef ASPECT16_9	// アスペクト比16:9
const float CAMERA_PARAM::DEFAULT_ASPECT_RATIO = 16.0f / 9.0f;
#else	// それ以外のときの基本アスペクト比
const float CAMERA_PARAM::DEFAULT_ASPECT_RATIO = 4.0f / 3.0f;
#endif

//=============================================================================
// コンストラクタ
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//=============================================================================
CCamera::CCamera()
{
	// カメラパラメータ設定
	// 座標
	m_param.pos				= Vector3(0.0f, 0.0f, 0.0f);
	// 注視点座標
	m_param.ray				= Vector3(0.0f, 0.0f, 1.0f);
	// 上方向ベクトル
	m_param.up				= Vector3(0.0f, 1.0f, 0.0f);
	// 画角
	m_param.fAoV			= KB_PI / 4.0f;
	// アスペクト比
	m_param.fAspectRatio	= CAMERA_PARAM::DEFAULT_ASPECT_RATIO;
	// ニアクリップ面
	m_param.fNear			= 10.f;
	// ファークリップ面
	m_param.fFar			= 2000.f;

	// 左
	m_fLeft = 0.0f;
	// 上
	m_fTop = 0.0f;
	// 右
	m_fRight = 960.0f;
	// 下
	m_fBottom = 540.0f;
}

//=============================================================================
// デストラクタ
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// カメラをセットアップ
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//=============================================================================
void CCamera::Setup(void)
{
	// 射影行列初期化
	Matrix4x4Identity(&m_matProj);
	// 右手系で視野を設定
	// 射影行列(視野角、アスペクト比、ニア面、ファー面)
	SetProjectionMatrixRH(&m_matProj,
								m_param.fAoV,
								m_param.fAspectRatio,
								m_param.fNear,
								m_param.fFar);

	// ビュー行列初期化
	Matrix4x4Identity(&m_matView);
	// 右手系でビュー設定
	SetViewMatrixRH(&m_matView,
						m_param.pos,
						m_param.ray,
						m_param.up);

	// ビュー逆行列設定
	Matrix4x4Inverse(&m_matInvView, m_matView);

	// 視野射影行列
	Matrix4x4Multiply(&m_matViewProj, m_matView, m_matProj);

	// オルソー行列
	SetOrthoMatrixRH(
		&m_matOrtho,
		m_fLeft, m_fTop, m_fRight, m_fBottom, 0.0f, 1.0f);
}

//=============================================================================
// カメラの座標を設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラの座標
//=============================================================================
void CCamera::SetPosition(const Vector3& pos)
{
	m_param.pos.x = pos.x;
	m_param.pos.y = pos.y;
	m_param.pos.z = pos.z;
}

//=============================================================================
// カメラの座標を設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラの座標
//=============================================================================
const Vector3& CCamera::GetPosition(void)
{
	return m_param.pos;
}

//=============================================================================
// カメラの注視点座標を設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラの注視点座標
//=============================================================================
void CCamera::SetRay(const Vector3& ray)
{
	m_param.ray.x = ray.x;
	m_param.ray.y = ray.y;
	m_param.ray.z = ray.z;
}

//=============================================================================
// カメラの上方向ベクトルの設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラの上方向ベクトル
//=============================================================================
void CCamera::SetUpVector(const Vector3& up)
{
	m_param.up.x = up.x;
	m_param.up.y = up.y;
	m_param.up.z = up.z;
}

//=============================================================================
// カメラの画角設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラの画角
//=============================================================================
void CCamera::SetAoV(const float& fAoV)
{
	m_param.fAoV = fAoV;
}

//=============================================================================
// カメラのアスペクト比設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラのアスペクト比
//=============================================================================
void CCamera::SetAspectRatio(const float& fAspectRatio)
{
	m_param.fAspectRatio = fAspectRatio;
}

//=============================================================================
// カメラのクリップ面設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラのニアクリップ面
// arg2		: カメラのファークリップ面
//=============================================================================
void CCamera::SetClipPlane(const float& fNear, const float& fFar)
{
	m_param.fNear = fNear;
	m_param.fFar = fFar;
}

//=============================================================================
// カメラパラメータ設定
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: void
// arg1		: カメラパラメータ
//=============================================================================
void CCamera::SetCameraParam(const CAMERA_PARAM& param)
{
	m_param = param;
}

//=============================================================================
// カメラのパラメータ取得
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: カメラのパラメータ
// arg		: void
//=============================================================================
const CAMERA_PARAM& CCamera::GetCameraParam(void)
{
	return m_param;
}

//=============================================================================
// カメラのビュー行列取得
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: カメラのビュー行列
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetViewMatrix(void)
{
	return m_matView;
}

//=============================================================================
// カメラのビュー逆行列取得
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: カメラのビュー逆行列
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetInvViewMatrix(void)
{
	return m_matInvView;
}

//=============================================================================
// カメラの射影行列取得
// Author : Ryo Kobayashi
// LastUpdate	: 2014/5/16
//
// ret		: カメラの射影行列
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetProjMatrix(void)
{
	return m_matProj;
}

//=============================================================================
// 視野行列と射影行列をかけた行列を返す
// Author : Ryo Kobayashi
// LastUpdate	: 2014/6/9
//
// ret		: 視野行列と射影行列をかけた行列
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetViewProjMatrix(void)
{
	return m_matViewProj;
}

//=============================================================================
// 視野行列と射影行列をかけた行列を返す
// Author : Ryo Kobayashi
// LastUpdate	: 2014/12/8
//
// ret		: オルソー行列
// arg		: void
//=============================================================================
const Matrix4x4& CCamera::GetOrtho(void)
{
	return m_matOrtho;
}

// EOF