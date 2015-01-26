//=============================================================================
//
// �J�����N���X [CCamera.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
//=============================================================================
#pragma once
#ifndef __KBR_CAMERA_H__
#define __KBR_CAMERA_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "OpenGL.h"
#include "kbMath.h"

/**************************************************************************//**
* @brief 
* �J�����p�����[�^�\����
*
* �J�����Ɋւ���p�����[�^
******************************************************************************/
struct CAMERA_PARAM
{
	Vector3		pos;	//!< @brief �J�������W
	Vector3		ray;	//!< @brief �J���������_���W
	Vector3		up;		//!< @brief �J����������x�N�g��

	float			fAoV;	//!< @brief �J��������p
	
	float			fAspectRatio;	//!< @brief �A�X�y�N�g��

	float			fNear;	//!< @brief �j�A�N���b�v��
	float			fFar;	//!< @brief �t�@�[�N���b�v��

	static const float DEFAULT_ASPECT_RATIO;	//!< @brief �f�t�H���g�A�X�y�N�g��萔
};

//*****************************************************************************
// �J�����N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//*****************************************************************************
class CCamera
{
public:
	/**
	* @brief	�R���X�g���N�^
	* @author	Ryo Kobayashi
	* @param[in] pos �J�����̏������W
	*/
	CCamera();
	
	/**
	* @brief	�f�X�g���N�^
	* @author	Ryo Kobayashi
	*/
	~CCamera();

	/**
	* @brief	�J�������Z�b�g�A�b�v
	* @author	Ryo Kobayashi
	* @return	void
	*/
	void Setup(void);

	/**
	* @brief		�J�����̍��W��ݒ�
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] pos �J�����ɐݒ肵�������W
	*/
	void SetPosition(const Vector3& pos);
	
	/**
	* @brief		�J�����̍��W���擾
	* @author		Ryo Kobayashi
	* @return		�J�������W
	*/
	const Vector3& GetPosition(void);
	
	/**
	* @brief		�J�����̒����_���W��ݒ�
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] ray �J�����ɐݒ肵���������_���W
	*/
	void SetRay(const Vector3& ray);

	/**
	* @brief		�J�����̏�����x�N�g���̐ݒ�
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] up �J�����ɐݒ肵����������x�N�g��
	*/
	void SetUpVector(const Vector3& up);
	
	/**
	* @brief		�J�����̉�p
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] fAoV �J�����ɐݒ肵������p
	*/
	void SetAoV(const float& fAoV);
	
	/**
	* @brief		�J�����̃A�X�y�N�g��ݒ�
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] fAspectRatio �J�����ɐݒ肵�����A�X�y�N�g��
	*/
	void SetAspectRatio(const float& fAspectRatio);
	
	/**
	* @brief		�J�����̃N���b�v�ʐݒ�
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] fNear �߃N���b�v��
	* @param[in] fFar ���N���b�v��
	*/
	void SetClipPlane(const float& fNear, const float& fFar);
	
	/**
	* @brief		�J�����p�����[�^�ݒ�
	* @author		Ryo Kobayashi
	* @return		void
	* @param[in] param �ݒ肵�����J�����p�����[�^
	*/
	void SetCameraParam(const CAMERA_PARAM& param);

	/**
	* @brief		�J�����p�����[�^�擾
	* @author		Ryo Kobayashi
	* @return		�J�����̉�p
	*/
	const CAMERA_PARAM& GetCameraParam(void);
	
	/**
	* @brief		�J�����r���[�s��擾
	* @author		Ryo Kobayashi
	* @return		�J�����̃r���[�s��
	*/
	const Matrix4x4& GetViewMatrix(void);
	
	/**
	* @brief		�J�����r���[�t�s��擾
	* @author		Ryo Kobayashi
	* @return		�J�����̃r���[�t�s��
	*/
	const Matrix4x4& GetInvViewMatrix(void);
	
	/**
	* @brief		�J�����ˉe�s��擾
	* @author		Ryo Kobayashi
	* @return		�J�����̎ˉe�s��
	*/
	const Matrix4x4& GetProjMatrix(void);
	
	/**
	* @brief		����s��Ǝˉe�s����������s���Ԃ�
	* @author		Ryo Kobayashi
	* @return		����s��Ǝˉe�s����������s��
	*/
	const Matrix4x4& GetViewProjMatrix(void);
	
	/**
	* @brief		�I���\�[�s���Ԃ�
	* @author		Ryo Kobayashi
	* @return		�I���\�[�s��
	*/
	const Matrix4x4& GetOrtho(void);

	void left(const float fLeft){ m_fLeft = fLeft; }
	void right(const float fRight){ m_fRight = fRight; }
	void top(const float fTop){ m_fTop = fTop; }
	void bottom(const float fBottom){ m_fBottom = fBottom; }

private:

	Matrix4x4		m_matView;		//!< @brief �r���[�s��
	Matrix4x4		m_matInvView;	//!< @brief �r���[�t�s��
	Matrix4x4		m_matProj;		//!< @brief �ˉe�s��
	Matrix4x4		m_matViewProj;	//!< @brief �r���[�ˉe�s��
	Matrix4x4		m_matOrtho;		//!< @brief �I���\�[�s��

	float m_fLeft;	//!< @brief ��
	float m_fTop;	//!< @brief ��
	float m_fRight;	//!< @brief �E
	float m_fBottom;//!< @brief ��

	CAMERA_PARAM	m_param;	//!< @brief �J�����p�����[�^
};

#endif	// __KBR_CAMERA_H__

// EOF