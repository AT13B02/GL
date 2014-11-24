//*****************************************************************************
//
// �I�u�W�F�N�g�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/light/light_manager.h"
//#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/renderstate/state/renderstate.h"
//#include "interface/graphic/texture/texture_manager.h"
//#include "interface/graphic/camera/camera_manager.h"

// common
#include "common/common.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObjectManager::CObjectManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CModelManager* model_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager)
{
	// �f�o�C�X�z���_�[�̐ݒ�
	device_holder_ = device_holder;

	// �e�N�X�`���}�l�[�W���[�̐ݒ�
	texture_manager_ = texture_manager;

	// ���f���}�l�[�W���[�̐ݒ�
	model_manager_ = model_manager;

	// �����_�[�X�e�[�g�}�l�[�W���[�̐ݒ�
	renderstate_manager_ = renderstate_manager;

	// �J�����}�l�[�W���[�̐���
	camera_manager_ = camera_manager;

	// ���C�g�}�l�[�W���[�̐���
	light_manager_ = light_manager_;

	// �I�u�W�F�N�g2D�}�l�[�W���[�̐���
	//object_2d_manager_ = new CObject2DManager(graphic_device_,renderstate_manager);

	// �I�u�W�F�N�g3D�}�l�[�W���[�̐���
	object_3d_manager_ = new CObject3DManager(device_holder_,texture_manager_,renderstate_manager_,model_manager_,camera_manager_,light_manager_);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObjectManager::~CObjectManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CObjectManager::Init(void)
{
	// �e�N�X�`���}�l�[�W���[�̏�����
	//INIT(texture_manager_);

	// �����_�[�X�e�[�g�}�l�[�W���[�̏�����
	//INIT(renderstate_manager_);

	// �I�u�W�F�N�g2D�}�l�[�W���[�̏�����
	//INIT(object_2d_manager_);

	// �I�u�W�F�N�g3D�}�l�[�W���[�̏�����
	//INIT(object_3d_manager_);

	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObjectManager::Draw(void)
{
	CRenderstate* renderstate_all = NULL;

	if(renderstate_manager_ != NULL)
	{
		renderstate_all = renderstate_manager_->renderstate(CRenderstateManager::TYPE_ALL);
	}

	if(renderstate_all != NULL)
	{
		renderstate_all->Set();
	}

	if(object_3d_manager_ != NULL)
	{
		// �I�u�W�F�N�g3D�̕`��
		object_3d_manager_->Draw();
	}

	// �I�u�W�F�N�g2D�̕`��
	//object_2d_manager_->Draw();

	// �����_�[�X�e�[�g�̉���
	if(renderstate_all != NULL)
	{
		// �����_�[�X�e�[�g�̉���
		renderstate_all->Unset();
	}

}

//=============================================================================
// �I������
//=============================================================================
void CObjectManager::Uninit(void)
{
	// �I�u�W�F�N�g3D�}�l�[�W���[�̊J��
	SAFE_RELEASE(object_3d_manager_);

	// �I�u�W�F�N�g2D�}�l�[�W���[�̊J��
	//SAFE_RELEASE(object_3d_manager_);

	// �J�����}�l�[�W���[�̊J��
	SAFE_RELEASE(camera_manager_);

	// ���C�g�}�l�[�W���[�̊J��
	//SAFE_RELEASE(light_manager_);
}

//---------------------------------- EOF --------------------------------------
