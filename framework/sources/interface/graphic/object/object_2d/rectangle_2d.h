//*****************************************************************************
//
// ��`2D�N���X [object_2d.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _RECTANGLE_2D_H_
#define _RECTANGLE_2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "object_2d.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CTexture;
class CGraphicsDevice;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CRectangle2D : public CObject2D
{
public:
	enum POINT
	{
		POINT_CENTER = 0,
		POINT_LEFT_UP,
		POINT_LEFT_MIDDLE,
		POINT_LEFT_DOWN,
		POINT_RIGHT_UP,
		POINT_RIGHT_MIDDLE,
		POINT_RIGHT_DOWN,
		POINT_MIDDLE_UP,
		POINT_MIDDLE_DOWN,
		POINT_MAX,
	};

	// �쐬����
	static CRectangle2D* Create(CGraphicsDevice* pGraphicsDevice);

	// ���_���̐ݒ�
	virtual void Set(void);

	// �T�C�Y�̐ݒ�
	void SetSize(const VECTOR2& Size){m_Size = Size;}

	// �e�N�X�`�����W�̐ݒ�
	void SetTexcoord(const float& fLeft,const float& fRight,const float& fTop,const float& fBottom){m_fLeft = fLeft;m_fRight = fRight;m_fTop = fTop;m_fBottom = fBottom;}

	// �J���[�̐ݒ�
	void SetColor(const COLOR4F& Color){for(int i = 0;i < VERTEX_MAX;i++){m_Color[i] = Color;}}

	// �J���[�̐ݒ�
	void SetColor(const COLOR4F& LeftTop,const COLOR4F& RightTop,const COLOR4F& LeftBottom,const COLOR4F& RightBottom){m_Color[0] = LeftTop;m_Color[1] = LeftBottom;m_Color[2] = RightTop;m_Color[3] = RightBottom;}

	// ���S�̐ݒ�
	void SetPoint(POINT Point){m_Point = Point;}

protected:
	static const int VERTEX_MAX = (4);

	// �R���X�g���N�^
	CRectangle2D(void);

	// �f�X�g���N�^
	virtual ~CRectangle2D(void);

	// �T�C�Y
	VECTOR2 m_Size;

	// �F
	COLOR4F m_Color[VERTEX_MAX];

	// �e�N�X�`�����W
	float m_fLeft;
	float m_fRight;
	float m_fTop;
	float m_fBottom;

	// ���S�_
	POINT m_Point;

	// ���_���W
	VECTOR2 m_Position[VERTEX_MAX];

private:

};

#endif	// _RECTANGLE_2D_H_

//---------------------------------- EOF --------------------------------------
