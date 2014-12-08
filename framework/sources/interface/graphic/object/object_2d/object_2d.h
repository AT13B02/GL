//*****************************************************************************
//
// �I�u�W�F�N�g2D�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _OBJECT_2D_H_
#define _OBJECT_2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/object/object.h"

// common
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
class CObject2DData;
class CDeviceHolder;
class CModel;
class CVertex2D;
class CTexture;
class CRenderstate;


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2D : public CObject
{
public:
	enum OBJECT_2D_TYPE
	{
		OBJECT_2D_TYPE_RECTANGLE = 0,
		OBJECT_2D_TYPE_BILLBOARD,
		OBJECT_2D_TYPE_OBJECT_MODEL,
		OBJECT_2D_TYPE_MAX
	};

	// �R���X�g���N�^
	explicit CObject2D(CDeviceHolder* device_holder,OBJECT_2D_TYPE type);

	// �f�X�g���N�^
	virtual ~CObject2D(void);

	// �`�揈��
	virtual void Draw(CObject2DData* object_2d_data){}

	// 2D�|���S���̕`�揈��
	void Draw(const MATRIX4x4& matrix,CVertex2D* vertex_2d,CTexture* texture,CRenderstate* renderstate);

	// �ݒ菈��
	virtual void Set(void) = 0;

protected:
	CDeviceHolder* device_holder_;
	MATRIX4x4 GetWorldMatrix(CObject2DData* object_2d_data);

private:
	OBJECT_2D_TYPE object_2d_type_;
};

#endif	// _OBJECT_2D_H_

//---------------------------------- EOF --------------------------------------
