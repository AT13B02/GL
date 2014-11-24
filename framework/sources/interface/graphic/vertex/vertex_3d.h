//*****************************************************************************
//
// 3D���_�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	3D���_�N���X
*
*	// �g����
*	Create�֐��ŃC���X�^���X�̐������s��
*	Init�֐��ŏ�����
*	Lock�֐��Œ��_���̊i�[�J�n���A���_�o�b�t�@�̃|�C���^���擾
*	Unlock�֐��Œ��_���̊i�[�I��(���_�o�b�t�@�̊i�[�������ł��̂ŁA������Ă΂Ȃ��Ɣ��f����Ȃ�)
*	Draw�֐��ŕ`��
*
*/
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _VERTEX_3D_H_
#define _VERTEX_3D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/basic.h"

// common
#include "common/image/color/color4f.h"
#include "common/math/math.h"

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
class CDeviceHolder;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CVertex3D : public CBasic
{
public:
	typedef struct _VERTEX_3D
	{
		VECTOR3* _position;
		VECTOR3* _normal;
		COLOR4F* _color;
		VECTOR2* _texcoord;
	}VERTEX_3D;

	typedef struct _VERTEX_3D_INDEX
	{
		u32* _position;
		u32* _normal;
		u32* _color;
		u32* _texcoord;
	}VERTEX_3D_INDEX;

	// �쐬����
	static CVertex3D* Create(CDeviceHolder* device_holder,const u32& vertex_3d_number);

	// �쐬����
	static CVertex3D* Create(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number);

	// �f�X�g���N�^
	virtual ~CVertex3D(void);

	// ����������
	bool Init(void);

	// �`�揈��
	virtual void Draw(const MATRIX4x4& matrix) = 0;

	// �I������
	virtual void Uninit(void);

	// ���b�N����
	void Lock(VERTEX_3D** vertex_3d,VERTEX_3D_INDEX** vertex_3d_index);

	// ��������
	virtual void Unlock(void) = 0;

protected:
	// �R���X�g���N�^
	CVertex3D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number);

	CDeviceHolder* device_holder_;
	VERTEX_3D vertex_3d_;
	u32 position_number_;
	u32 normal_number_;
	u32 color_number_;
	u32 texcoord_number_;
	u32 primitive_number_;
	u32 index_number_;
	VERTEX_3D_INDEX* vertex_3d_index_;

private:

};

#endif	// _VERTEX_3D_H_

//---------------------------------- EOF --------------------------------------
