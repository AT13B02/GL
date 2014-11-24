//*****************************************************************************
//
// �I�u�W�F�N�g�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/basic.h"
#include "basic/main_window.h"

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
class CTextureManager;
class CModelManager;
class CRenderstateManager;
class CCameraManager;
class CLightManager;
class CObject2DManager;
class CObject3DManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObjectManager : public CBasic
{
public:
	// �R���X�g���N�^
	CObjectManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CModelManager* model_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager);

	// �f�X�g���N�^
	virtual ~CObjectManager(void);

	// ����������
	bool Init(void);

	// �`�揈��
	void Draw(void);

	// �I������
	void Uninit(void);

	// �I�u�W�F�N�g2D�}�l�[�W���[�̎擾
	CObject2DManager* object_2d_manager(void){return object_2d_manager_;}

	// �I�u�W�F�N�g3D�}�l�[�W���[�̎擾
	CObject3DManager* object_3d_manager(void){return object_3d_manager_;}
	CCameraManager* camera_manager(void){return camera_manager_;}

private:
	// �f�o�C�X�z���_�[
	CDeviceHolder* device_holder_;

	// �e�N�X�`���}�l�[�W���[
	CTextureManager* texture_manager_;

	// ���f���}�l�[�W���[
	CModelManager* model_manager_;

	// �����_�[�X�e�[�g�}�l�[�W���[
	CRenderstateManager* renderstate_manager_;

	// �J�����}�l�[�W���[
	CCameraManager* camera_manager_;

	// ���C�g�}�l�[�W���[
	CLightManager* light_manager_;

	// �I�u�W�F�N�g2D�}�l�[�W���[
	CObject2DManager* object_2d_manager_;

	// �I�u�W�F�N�g3D�}�l�[�W���[
	CObject3DManager* object_3d_manager_;
};

#endif	// _OBJECT_MANAGER_H_

//---------------------------------- EOF --------------------------------------
