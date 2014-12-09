//*****************************************************************************
//
// �N�H�[�^�j�I���N���X
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************
#pragma once
#ifndef _QUATERNION_H_
#define _QUATERNION_H_

//*****************************************************************************
// �O���Q��
//*****************************************************************************
struct VECTOR3;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
struct QUATERNION
{
	/**
	*	�f�t�H���g�R���X�g���N�^
	*
	*	��������0.0f�ŏ������Bw=1�ɏ�����
	*
	*	@param	void
	*/
	QUATERNION() :
	_x(0.0f), _y(0.0f), _z(0.0f), _w(1.0f){}

	/**
	*	�����t�R���X�g���N�^
	*
	*	�����ŏ�����
	*
	*	@param	void
	*/
	QUATERNION(float x, float y, float z, float w) :
	_x(x), _y(y), _z(z), _w(w){}
	
	/**
	*	�f�X�g���N�^
	*/
	~QUATERNION(){}
	
	/**
	*	�N�H�[�^�j�I����]��
	*
	*	�����ŏ�����
	*
	*	@param	VECTOR3	�C�ӎ�
	*	@param	float	��]��
	*/
	QUATERNION RotationAxis(const VECTOR3& axis, const float angle);
	
	/**
	*	�N�H�[�^�j�I�������]�ʕϊ�
	*
	*	�����ŏ�����
	*
	*	@param	QUATERNION ��]�N�H�[�^�j�I��
	*/
	VECTOR3 YawPitchRollFromQuaternion(const QUATERNION& q);

	//-----------------------------------------------------
	// �����ϊ�

	QUATERNION operator+(void){return *this;}
	QUATERNION operator-(void){return QUATERNION(-_x,-_y,-_z,-_w);}
	
	//-----------------------------------------------------
	// ��Z

	QUATERNION operator*(const QUATERNION& rhs) const;
	
	//-----------------------------------------------------
	// ��Z���

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
