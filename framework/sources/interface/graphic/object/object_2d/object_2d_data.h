//*****************************************************************************
//
// �I�u�W�F�N�g2D�f�[�^�N���X [object_2d_data.h]
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

#ifndef _OBJECT_2D_DATA_H_
#define _OBJECT_2D_DATA_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "math.h"
#include "basic.h"

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
class CObject2D;
class CTexture;
class CRenderstate;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2DData : public CBasic
{
public:
	// �R���X�g���N�^
	CObject2DData(void);

	// �f�X�g���N�^
	~CObject2DData(void);

	// ������
	bool Init(void);

	// �`�揈��
	void Draw(void);

	// ������
	void Uninit(void);

	//-----------------------------------------------------
	// �A�N�Z�T

	void SetPosition(const VECTOR2& Pos){m_Pos = Pos;}
	void SetRotation(const float& fRot){m_fRot = fRot;}
	void SetScale(const VECTOR2& Scale){m_Scale = Scale;}
	void SetMatrix(const MATRIX4x4& Matrix){m_Matrix = Matrix;}
	void SetObject(CObject2D* pObject2D){m_pObject2D = pObject2D;}
	void SetTexture(CTexture* pTexture){m_pTexture = pTexture;}
	void SetRenderstate(CRenderstate* pRenderstate){m_pRenderstate = pRenderstate;}

	const VECTOR2& GetPosition(void){return m_Pos;}
	const float& GetRotation(void){return m_fRot;}
	const VECTOR2& GetScale(void){return m_Scale;}
	const MATRIX4x4& GetMatrix(void){return m_Matrix;}
	CObject2D* GetObject2D(void){return m_pObject2D;}
	CTexture* GetTexture(void){return m_pTexture;}
	CRenderstate* GetRenderstate(void){return m_pRenderstate;}

private:
	VECTOR2 m_Pos;
	float m_fRot;
	VECTOR2 m_Scale;
	MATRIX4x4 m_Matrix;
	CObject2D* m_pObject2D;
	CTexture* m_pTexture;
	CRenderstate* m_pRenderstate;
};

#endif	// _OBJECT_2D_DATA_H_

//---------------------------------- EOF --------------------------------------
