//*****************************************************************************
//
// �O���t�B�b�N�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _GRAPHIC_MANAGER_H_
#define _GRAPHIC_MANAGER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
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
class CObjectManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CGraphicManager : public CBasic
{
public:
	// �R���X�g���N�^
	CGraphicManager(WINDOW_DATA* window_data);

	// �f�X�g���N�^
	virtual ~CGraphicManager(void);

	// ����������
	bool Init(void);

	// �`�揈��
	void Draw(void);

	// �I������
	void Uninit(void);

	// ���[�h�J�n
	void BeginLoad(void);

	// ���[�h�I��
	void EndLoad(void);

	// �f�o�C�X�z���_�[�̎擾
	CDeviceHolder* device_holder(void){return device_holder_;}

	// �I�u�W�F�N�g�}�l�[�W���[�̎擾
	CObjectManager* object_manager(void){return object_manager_;}

	// �e�N�X�`���}�l�[�W���[�̎擾
	CTextureManager* texture_manager(void){return texture_manager_;}

	// ���f���}�l�[�W���[�̎擾
	CModelManager* model_manager(void){return model_manager_;}

	// �J�����}�l�[�W���[�̎擾
	CCameraManager* camera_manager(void){return camera_manager_;}

	// ���C�g�}�l�[�W���[�̎擾
	CLightManager* light_manager(void){return light_manager_;}

	// �����_�[�X�e�[�g�}�l�[�W���[�̎擾
	CRenderstateManager* renderstate_manager(void){return renderstate_manager_;}
protected:

private:
	// �f�o�C�X�z���_�[�̎擾
	CDeviceHolder* device_holder_;

	// �I�u�W�F�N�g�}�l�[�W���[
	CObjectManager* object_manager_;

	// �e�N�X�`���}�l�[�W���[
	CTextureManager* texture_manager_;

	// ���f���}�l�[�W���[
	CModelManager* model_manager_;

	// �J�����}�l�[�W���[
	CCameraManager* camera_manager_;

	// ���C�g�}�l�[�W���[
	CLightManager* light_manager_;

	// �����_�[�X�e�[�g�}�l�[�W���[
	CRenderstateManager* renderstate_manager_;
};

#endif	// _GRAPHIC_MANAGER_H_

//---------------------------------- EOF --------------------------------------
