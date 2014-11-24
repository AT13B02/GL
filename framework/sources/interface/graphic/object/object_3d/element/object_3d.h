//*****************************************************************************
//
// �I�u�W�F�N�g3D�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

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
class CDeviceHolder;
class CObject3DData;
class CModel;
class CVertex3D;
class CTexture;
class CRenderstate;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject3D : public CObject
{
public:
	enum OBJECT_3D_TYPE
	{
		OBJECT_3D_TYPE_RECTANGLE = 0,
		OBJECT_3D_TYPE_BILLBOARD,
		OBJECT_3D_TYPE_OBJECT_MODEL,
		OBJECT_3D_TYPE_MAX
	};

	// �R���X�g���N�^
	CObject3D(CDeviceHolder* device_holder,OBJECT_3D_TYPE type);

	// �f�X�g���N�^
	virtual ~CObject3D(void);

	// �`�揈��
	virtual void Draw(CObject3DData* pObject3DData) = 0;

	// �`�揈��
	void Draw(const MATRIX4x4& Matrix,CVertex3D* pVertex3D,CTexture* pTexture,CRenderstate* pRenderstate);

	// �`�揈��
	void Draw(const MATRIX4x4& matrix,CModel* model,CRenderstate* renderstate);

	// �ݒ菈��
	virtual void Set(void) = 0;

protected:
	MATRIX4x4 GetWorldMatrix(CObject3DData* pObject3DData);
	CDeviceHolder* device_holder_;

private:
	OBJECT_3D_TYPE object_3d_type_;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
