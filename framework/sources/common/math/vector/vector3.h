//*****************************************************************************
//
// 3�����x�N�g���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	3�����x�N�g���N���X
*
*	3�����x�N�g���Ŏg�������������ɏ���
*
*/
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _VECTOR3_H_
#define _VECTOR3_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �萔��`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct VECTOR3
{
public:
	f32 _x;
	f32 _y;
	f32 _z;

	//-----------------------------------------------------
	// �R���X�g���N�^

	/**
	*	�f�t�H���g�R���X�g���N�^
	*
	*	0.0f�ŏ�����
	*
	*	@param	void
	*/
	VECTOR3(void){_x = 0.0f;_y = 0.0f;_z = 0.0f;}

	/**
	*	�R���X�g���N�^
	*
	*	�v�f���w�肵�ď�����
	*
	*	@param	f32 x
	*	@param	f32 y
	*	@param	f32 z
	*/
	VECTOR3(const f32& x,const f32& y,const f32& z){_x = x;_y = y;_z = z;}

	/**
	*	�R�s�[�R���X�g���N�^
	*
	*	�v�f���R�s�[���ď�����
	*
	*	@param	VECTOR3
	*/
	VECTOR3(const VECTOR3& vector){_x = vector._x;_y = vector._y;_z = vector._z;}

	//-----------------------------------------------------
	// �x�N�g���̊֐�

	/**
	*	�P�ʃx�N�g����
	*
	*	�x�N�g����P�ʃx�N�g���ɂ���
	*
	*	@param	void
	*	@return	void
	*/
	void Normalize(void);

	/**
	*	�x�N�g���̑傫���̎擾
	*
	*	�x�N�g���̑傫�����擾����
	*
	*	@param	void
	*	@return	f32 �x�N�g���̑傫��
	*/
	f32 Magnitude(void) const;

	/**
	*	�x�N�g���̓���
	*
	*	�x�N�g���̓��όv�Z���s��
	*	���Z���ʂ͕Ԃ�l
	*
	*	@param	VECTOR3 �x�N�g��
	*	@return	f32 ���ό���
	*/
	f32 DotProduct(const VECTOR3& vector) const;

	/**
	*	�x�N�g���̊O��
	*
	*	�x�N�g���̊O�όv�Z���s��
	*	���Z���ʂ͕Ԃ�l
	*
	*	@param	VECTOR3 �x�N�g��
	*	@return	VECTOR3 �O�ό���
	*/
	VECTOR3 CrossProduct(const VECTOR3& vector) const;

	//-----------------------------------------------------
	// �����ϊ�

	VECTOR3 operator+(void){return *this;}
	VECTOR3 operator-(void){return VECTOR3(-_x,-_y,-_z);}

	//-----------------------------------------------------
	// �X�J���[�Ƃ̌v�Z

	VECTOR3 operator+(const f32& fValue) const;
	VECTOR3 operator-(const f32& fValue) const;
	VECTOR3 operator*(const f32& fValue) const;
	VECTOR3 operator/(const f32& fValue) const;

	VECTOR3& operator+=(const f32& fValue);
	VECTOR3& operator-=(const f32& fValue);
	VECTOR3& operator*=(const f32& fValue);
	VECTOR3& operator/=(const f32& fValue);

	//-----------------------------------------------------
	// �x�N�g���Ƃ̌v�Z

	VECTOR3 operator+(const VECTOR3& vector) const;
	VECTOR3 operator-(const VECTOR3& vector) const;

	VECTOR3& operator+=(const VECTOR3& vector);
	VECTOR3& operator-=(const VECTOR3& vector);

}VECTOR3;

#endif // _VECTOR3_H_

//---------------------------------- EOF --------------------------------------
