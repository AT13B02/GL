//*****************************************************************************
//
// �O���t�B�b�N�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/camera/camera_manager.h"
//#include "interface/graphic/light/light_manager.h"

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
CGraphicManager::CGraphicManager(WINDOW_DATA* window_data)
{
	// �f�o�C�X�z���_�[�̐���
	device_holder_ = new CDeviceHolder(window_data);

	// �����_�[�X�e�[�g�}�l�[�W���[�̐���
	renderstate_manager_ = new CRenderstateManager(device_holder_);

	// �e�N�X�`���}�l�[�W���[�̐���
	texture_manager_ = new CTextureManager(device_holder_);

	// ���f���}�l�[�W���[�̐���
	model_manager_ = new CModelManager(device_holder_);

	// �J�����}�l�[�W���[�̐���
	camera_manager_ = new CCameraManager(device_holder_);

	// ���C�g�}�l�[�W���[�̐���
	light_manager_ = NULL;

	// �I�u�W�F�N�g�}�l�[�W���[�̐���
	object_manager_ = new CObjectManager(device_holder_,texture_manager_,model_manager_,renderstate_manager_,camera_manager_,light_manager_);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGraphicManager::~CGraphicManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CGraphicManager::Init(void)
{
	// �O���t�B�b�N�f�o�C�X�̏�����
	INIT(device_holder_);

	// �e�N�X�`���}�l�[�W���[�̏�����
	INIT(texture_manager_);

	// �����_�[�X�e�[�g�}�l�[�W���[�̏�����
	INIT(renderstate_manager_);

	// �I�u�W�F�N�g�}�l�[�W���[�̏�����
	INIT(object_manager_);

	// ���f���}�l�[�W���[�̏�����
	INIT(model_manager_);

	// �J�����}�l�[�W���[�̏�����
	INIT(camera_manager_);

	// ���C�g�}�l�[�W���[�̏�����
	//INIT(light_manager_);

	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGraphicManager::Draw(void)
{
	// �`��J�n
	device_holder_->BeginDraw();

	// �`��
	object_manager_->Draw();

	// �`��I��
	device_holder_->EndDraw();
}

//=============================================================================
// �I������
//=============================================================================
void CGraphicManager::Uninit(void)
{
	// �I�u�W�F�N�g�}�l�[�W���[�̊J��
	SAFE_RELEASE(object_manager_);

	// �J�����}�l�[�W���[�̊J��
	SAFE_RELEASE(camera_manager_);

	// ���C�g�}�l�[�W���[�̊J��
	//SAFE_RELEASE(light_manager_);

	// ���f���}�l�[�W���[�̊J��
	SAFE_RELEASE(model_manager_);

	// �����_�[�X�e�[�g�}�l�[�W���[�̊J��
	SAFE_RELEASE(renderstate_manager_);

	// �e�N�X�`���}�l�[�W���[�̊J��
	SAFE_RELEASE(texture_manager_);

	// �f�o�C�X�z���_�[�̊J��
	SAFE_RELEASE(device_holder_);
}

//=============================================================================
// ���[�h�J�n
//=============================================================================
void CGraphicManager::BeginLoad(void)
{
	device_holder_->BeginLoad();
}

//=============================================================================
// ���[�h�I��
//=============================================================================
void CGraphicManager::EndLoad(void)
{
	device_holder_->EndLoad();
}

//---------------------------------- EOF --------------------------------------
