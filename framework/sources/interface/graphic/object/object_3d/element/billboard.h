//*****************************************************************************
//
// �r���{�[�h�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/element/object_3d.h"

// common
#include "common/image/color/color4f.h"

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
class CVertex3D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBillboard : public CObject3D
{
public:
	// �R���X�g���N�^
	CBillboard(CDeviceHolder* device_holder);

	// �f�X�g���N�^
	virtual ~CBillboard(void);

	// ����������
	bool Init(void);

	// �`�揈��
	void Draw(CObject3DData* object_3d_data);

	// �I������
	void Uninit(void);

	// ���_���̐ݒ�
	void Set(void);

	// �T�C�Y�̐ݒ�
	void set_size(const VECTOR2& size){size_ = size;}

	// �e�N�X�`�����W�̐ݒ�
	void set_texcoord(const f32& left,const f32& right,const f32& top,const f32& bottom){left_ = left;right_ = right;top_ = top;bottom_ = bottom;}

	// �J���[�̐ݒ�
	void set_color(const COLOR4F& Color){for(int i = 0;i < VERTEX_MAX;i++){color_[i] = Color;}}

	// �J���[�̐ݒ�
	void set_color(const COLOR4F& LeftTop,const COLOR4F& RightTop,const COLOR4F& LeftBottom,const COLOR4F& RightBottom){color_[0] = LeftTop;color_[1] = LeftBottom;color_[2] = RightTop;color_[3] = RightBottom;}

protected:



private:
	static const int VERTEX_MAX = (4);

	// �T�C�Y
	VECTOR2 size_;

	// �F
	COLOR4F color_[VERTEX_MAX];

	// �e�N�X�`�����W
	f32 left_;
	f32 right_;
	f32 top_;
	f32 bottom_;

	// ���_���W
	VECTOR2 position_[VERTEX_MAX];

	// ���_���
	CVertex3D* vertex_3d_;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
