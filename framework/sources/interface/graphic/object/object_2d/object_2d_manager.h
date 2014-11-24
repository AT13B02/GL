//*****************************************************************************
//
// �I�u�W�F�N�g2D�}�l�[�W���[�N���X [object_2d_manager.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/09/13(Sat)
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _OBJECT_2D_MANAGER_H_
#define _OBJECT_2D_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "math.h"
#include "basic/basic.h"

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
class CObject2DList;
class CObject2DBuffer;
class CTexture;
class CGraphicsDevice;
class CRenderstate;
class CRenderstateManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2DManager : public CBasic
{
public:
	// �R���X�g���N�^
	CObject2DManager(CGraphicsDevice* pGraphicsDevice,CRenderstateManager* pRenderstateManager);

	// �f�X�g���N�^
	~CObject2DManager(void);

	// ������
	bool Init(void);

	// �I��
	void Uninit(void);

	// �`�揈��
	void Draw(void);

	// �i�[
	int Add(CObject2D* pObject2D,int nListType = LIST_TYPE_LOAD);

	// �ύX
	void Change(void);

	// �ύX�t���O
	void RaiseChangeFlag(void);

	//-----------------------------------------------------
	// �`�惊�X�g�ɕۑ�

	void Draw(const int& nObjectNumber,const VECTOR2& Pos);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,float fRot,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture,CRenderstate* pRenderstate);

private:

	enum LIST_TYPE
	{
		LIST_TYPE_USE = 0,
		LIST_TYPE_LOAD,
		LIST_TYPE_MAX,
	};

	// �I�u�W�F�N�g���X�g
	CObject2DList* m_apObject2DList[LIST_TYPE_MAX];

	// �ύX�t���O
	bool m_bChangeFlag;

	// �o�b�t�@���X�g
	CObject2DBuffer* m_pBuffer;

	// �O���t�B�b�N�f�o�C�X
	CGraphicsDevice* m_pGraphicsDevice;

	// �����_�[�X�e�[�g�}�l�[�W���[
	CRenderstateManager* m_pRenderstateManager;
};

#endif	// _OBJECT_2D_MANAGER_H_

//---------------------------------- EOF --------------------------------------
