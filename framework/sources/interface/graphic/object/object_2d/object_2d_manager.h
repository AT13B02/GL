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
// stl
#include <list>

// basic
#include "basic/basic.h"

// math
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
class CObject2D;
class CObject2DList;
class CObject2DBuffer;

class CTexture;
class CDeviceHolder;

class CRenderstate;
class CRenderstateManager;

class CCameraManager;
class CLightManager;
class CModelManager;
class CTextureManager;


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2DManager : public CBasic
{
public:
	// �R���X�g���N�^
	CObject2DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager);

	// �f�X�g���N�^
	~CObject2DManager(void);

	// ������
	bool Init(void);

	// �`�揈��
	void Draw(void);

	// �I��
	void Uninit(void);


	// ���X�g�ɒǉ�
	u32 AddList(CObject2D* object_2d);

	//-----------------------------------------------------
	// �`�惊�X�g�ɕۑ�
	void Draw(const u32& object_key,const VECTOR2& position,const float rotation,const VECTOR2& scale,MATRIX4x4 matrix,const std::string& texture_name,CRenderstate* renderstate);

private:

	// �I�u�W�F�N�g���X�g
	CObject2DList* object_2d_list_;

	// �o�b�t�@���X�g
	CObject2DBuffer* object_2d_buffer_;

	// �f�o�C�X�z���_�[
	CDeviceHolder* device_holder_;

	// �����_�[�X�e�[�g�}�l�[�W���[
	CRenderstateManager* renderstate_manager_;

	// �e�N�X�`���}�l�[�W���[
	CTextureManager* texture_manager_;

	// �J�����}�l�[�W���[
	CCameraManager* camera_manager_;

	// ���C�g�}�l�[�W���[
	CLightManager* light_manager_;
};

#endif	// _OBJECT_2D_MANAGER_H_

//---------------------------------- EOF --------------------------------------
