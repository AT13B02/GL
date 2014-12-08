//*****************************************************************************
//
// Fade2D�N���X
//
// Author		: Tomohiro Kouno
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _FADE_2D_H_
#define _FADE_2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
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
class CTexture;
class CGraphicsDevice;
class CRectangle2D;
class CInterfaceManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CFade2D : public CBasic
{
public:

	// �R���X�g���N�^
	CFade2D(CInterfaceManager* interface_manager);

	// �f�X�g���N�^
	virtual ~CFade2D(void);

	enum FADE_TYPE
	{
		FADE_TYPE_NONE,
		FADE_TYPE_IN,
		FADE_TYPE_IN_END,
		FADE_TYPE_OUT,
		FADE_TYPE_OUT_END,
	};

	// ����������
	bool Init(void);

	// �X�V����
	void Update(void);

	// �`�揈��
	void Draw(void);

	// �I������
	void Uninit(void);

	// �t�F�[�h�C��
	void FadeIn(f32 time = 0.01f){speed_ = time;fadetype_ = FADE_TYPE_IN;}

	// �t�F�[�h�A�E�g
	void FadeOut(f32 time =  0.01f){speed_ = time;fadetype_ = FADE_TYPE_OUT;}

	//�t�F�[�h�`�F�b�N
	bool IsFadeIn(void){return fadetype_ == FADE_TYPE_IN;}
	bool IsFadeOut(void){return fadetype_ == FADE_TYPE_OUT;}
	bool IsFadeInEnd(void){return fadetype_ == FADE_TYPE_IN_END;}
	bool IsFadeOutEnd(void){return fadetype_ == FADE_TYPE_OUT_END;}

protected:
	// ���_���
	CRectangle2D* rectangle_2d_;
	u32 rectangle_2d_key_;
	FADE_TYPE fadetype_;
	f32 alpha_;
	f32 speed_;

	// �C���^�[�t�F�[�X�}�l�[�W���[
	CInterfaceManager* interface_manager_;
private:

};

#endif	// _RECTANGLE_2D_H_

//---------------------------------- EOF --------------------------------------
