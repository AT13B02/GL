//=============================================================================
//
// カメラクラス [CCamera.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
//=============================================================================
#pragma once
#ifndef __KBR_CAMERA_H__
#define __KBR_CAMERA_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "OpenGL.h"
#include "kbMath.h"

/**************************************************************************//**
* @brief 
* カメラパラメータ構造体
*
* カメラに関するパラメータ
******************************************************************************/
struct CAMERA_PARAM
{
	Vector3		pos;	//!< @brief カメラ座標
	Vector3		ray;	//!< @brief カメラ注視点座標
	Vector3		up;		//!< @brief カメラ上方向ベクトル

	float			fAoV;	//!< @brief カメラ視野角
	
	float			fAspectRatio;	//!< @brief アスペクト比

	float			fNear;	//!< @brief ニアクリップ面
	float			fFar;	//!< @brief ファークリップ面

	static const float DEFAULT_ASPECT_RATIO;	//!< @brief デフォルトアスペクト比定数
};

//*****************************************************************************
// カメラクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//*****************************************************************************
class CCamera
{
public:
	/**
	* @brief	コンストラクタ
	* @author	Ryo Kobayashi
	* @param[in] pos カメラの初期座標
	*/
	CCamera();
	
	/**
	* @brief	デストラクタ
	* @author	Ryo Kobayashi
	*/
	~CCamera();

	/**
	* @brief	カメラをセットアップ
	* @author	Ryo Kobayashi
	* @return	void
	*/
	void Setup(void);

	/**
	* @brief		カメラの座標を設定
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] pos カメラに設定したい座標
	*/
	void SetPosition(const Vector3& pos);
	
	/**
	* @brief		カメラの座標を取得
	* @author		Ryo Kobayashi
	* @return		カメラ座標
	*/
	const Vector3& GetPosition(void);
	
	/**
	* @brief		カメラの注視点座標を設定
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] ray カメラに設定したい注視点座標
	*/
	void SetRay(const Vector3& ray);

	/**
	* @brief		カメラの上方向ベクトルの設定
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] up カメラに設定したい上方向ベクトル
	*/
	void SetUpVector(const Vector3& up);
	
	/**
	* @brief		カメラの画角
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] fAoV カメラに設定したい画角
	*/
	void SetAoV(const float& fAoV);
	
	/**
	* @brief		カメラのアスペクト比設定
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] fAspectRatio カメラに設定したいアスペクト比
	*/
	void SetAspectRatio(const float& fAspectRatio);
	
	/**
	* @brief		カメラのクリップ面設定
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] fNear 近クリップ面
	* @param[in] fFar 遠クリップ面
	*/
	void SetClipPlane(const float& fNear, const float& fFar);
	
	/**
	* @brief		カメラパラメータ設定
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] param 設定したいカメラパラメータ
	*/
	void SetCameraParam(const CAMERA_PARAM& param);

	/**
	* @brief		カメラパラメータ取得
	* @author		Ryo Kobayashi
	* @return		カメラの画角
	*/
	const CAMERA_PARAM& GetCameraParam(void);
	
	/**
	* @brief		カメラビュー行列取得
	* @author		Ryo Kobayashi
	* @return		カメラのビュー行列
	*/
	const Matrix4x4& GetViewMatrix(void);
	
	/**
	* @brief		カメラビュー逆行列取得
	* @author		Ryo Kobayashi
	* @return		カメラのビュー逆行列
	*/
	const Matrix4x4& GetInvViewMatrix(void);
	
	/**
	* @brief		カメラ射影行列取得
	* @author		Ryo Kobayashi
	* @return		カメラの射影行列
	*/
	const Matrix4x4& GetProjMatrix(void);
	
	/**
	* @brief		視野行列と射影行列をかけた行列を返す
	* @author		Ryo Kobayashi
	* @return		視野行列と射影行列をかけた行列
	*/
	const Matrix4x4& GetViewProjMatrix(void);
	
	/**
	* @brief		オルソー行列を返す
	* @author		Ryo Kobayashi
	* @return		オルソー行列
	*/
	const Matrix4x4& GetOrtho(void);

	void left(const float fLeft){ m_fLeft = fLeft; }
	void right(const float fRight){ m_fRight = fRight; }
	void top(const float fTop){ m_fTop = fTop; }
	void bottom(const float fBottom){ m_fBottom = fBottom; }

private:

	Matrix4x4		m_matView;		//!< @brief ビュー行列
	Matrix4x4		m_matInvView;	//!< @brief ビュー逆行列
	Matrix4x4		m_matProj;		//!< @brief 射影行列
	Matrix4x4		m_matViewProj;	//!< @brief ビュー射影行列
	Matrix4x4		m_matOrtho;		//!< @brief オルソー行列

	float m_fLeft;	//!< @brief 左
	float m_fTop;	//!< @brief 上
	float m_fRight;	//!< @brief 右
	float m_fBottom;//!< @brief 下

	CAMERA_PARAM	m_param;	//!< @brief カメラパラメータ
};

#endif	// __KBR_CAMERA_H__

// EOF