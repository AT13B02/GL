//*****************************************************************************
//
// �I�u�W�F�N�g3D�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _OBJECT_3D_MANAGER_H_
#define _OBJECT_3D_MANAGER_H_

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
class CObject3D;
class CObject3DList;
class CObject3DBuffer;

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
class CObject3DManager : public CBasic
{
public:
	// �R���X�g���N�^
	CObject3DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CModelManager* model_manager,CCameraManager* camera_manager,CLightManager* light_manager);

	// �f�X�g���N�^
	~CObject3DManager(void);

	// ����������
	bool Init(void);

	// �`�揈��
	void Draw(void);

	// �I������
	void Uninit(void);

	// ���X�g�ɒǉ�
	u32 AddList(CObject3D* object_3d);

	// ���f���}�l�[�W���[�̎擾
	CModelManager* GetModelManager(void){return model_manager_;}

	//-----------------------------------------------------
	// �`�惊�X�g�ɕۑ�

	void Draw(const u32& object_key,const VECTOR3& position,const VECTOR3& rotation,const VECTOR3& scale,MATRIX4x4 matrix,const std::string& texture_name,CRenderstate* renderstate);

	//--------------------------------------------------------

protected:

private:
	// �I�u�W�F�N�g���X�g
	CObject3DList* object_3d_list_;

	// �o�b�t�@���X�g
	CObject3DBuffer* object_3d_buffer_;

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

	// ���f���}�l�[�W���[
	CModelManager* model_manager_;
};

#endif	// _OBJECT_3D_MANAGER_H_

//---------------------------------- EOF --------------------------------------
