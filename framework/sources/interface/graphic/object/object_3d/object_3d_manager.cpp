//*****************************************************************************
//
// �I�u�W�F�N�g3D�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_list.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"
#include "interface/graphic/object/object_3d/object_3d_buffer.h"
#include "interface/graphic/object/object_3d/element/object_3d.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/renderstate/state/renderstate.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/light/light_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/device/device_holder.h"

// common
#include "common/common.h"

//*****************************************************************************
// �}�N����`
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
CObject3DManager::CObject3DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CModelManager* model_manager,CCameraManager* camera_manager,CLightManager* light_manager)
{
	// �O���t�B�b�N�f�o�C�X�̐ݒ�
	device_holder_ = device_holder;

	// �����_�[�X�e�[�g�}�l�[�W���[�̐ݒ�
	renderstate_manager_ = renderstate_manager;

	// �e�N�X�`���}�l�[�W���̐ݒ�
	texture_manager_ = texture_manager;

	// �J�����}�l�[�W���[�̐ݒ�
	camera_manager_ = camera_manager;

	// ���f���}�l�[�W���[�̐ݒ�
	model_manager_ = model_manager;

	// ���C�g�}�l�[�W���[�̐ݒ�
	light_manager_ = light_manager;

	// �I�u�W�F�N�g���X�g�̐���
	object_3d_list_ = new CObject3DList();

	// �I�u�W�F�N�g�o�b�t�@�̐���
	object_3d_buffer_ = new CObject3DBuffer();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject3DManager::~CObject3DManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CObject3DManager::Init(void)
{
	INIT(object_3d_list_);
	INIT(object_3d_buffer_);
	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject3DManager::Draw(void)
{
	CCamera* camera = NULL;

	// �����_�[�X�e�[�g�̐ݒ�
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_3D)->Set();

	for(int i = 0;i < camera_manager_->number_count();i++)
	{
		// �J�����̐ݒ�Ɛݒ肵���J�����̎擾
		camera = camera_manager_->SetCamera(i);

		// ���C�g�̐ݒ�
		light_manager_->Set();

		// �o�b�t�@�̕`�揈��
		object_3d_buffer_->Draw(camera,texture_manager_,model_manager_);
	}

	// ���C�g�̉���
	light_manager_->Unset();

	// TODO �o�b�t�@�̔j�� �X���b�h�𕪂�����Ȃ��Ȃ�
	object_3d_buffer_->Refresh();

	// �����_�[�X�e�[�g�̉���
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_3D)->Unset();
}

//=============================================================================
// �I������
//=============================================================================
void CObject3DManager::Uninit(void)
{
	// �I�u�W�F�N�g���X�g�̊J��
	SAFE_RELEASE(object_3d_list_);

	// �o�b�t�@�̊J��
	SAFE_RELEASE(object_3d_buffer_);
}

//=============================================================================
// �I�u�W�F�N�g�ǉ�����
//=============================================================================
u32 CObject3DManager::AddList(CObject3D* object_3d)
{
	return object_3d_list_->AddList(object_3d);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject3DManager::Draw(const u32& object_key,const VECTOR3& position,const VECTOR3& rotation,const VECTOR3& scale,MATRIX4x4 matrix,const std::string& texture_name,CRenderstate* renderstate)
{
	CObject3DData* object_3d_data = NULL;
	CObject3D* object_3d = object_3d_list_->GetListData(object_key);

	// �I�u�W�F�N�g�ԍ��̊m�F
	if(object_3d == NULL)
	{
		return;
	}

	// �o�b�t�@�̐���
	object_3d_data = new CObject3DData();

	// �o�b�t�@�ԍ��̐ݒ�
	object_3d_data->set_object_3d(object_3d);

	// ���W�̐ݒ�
	object_3d_data->set_position(position);

	// ��]�p�̐ݒ�
	object_3d_data->set_rotation(rotation);

	// �X�P�[���̐ݒ�
	object_3d_data->set_scale(scale);

	// �}�g���b�N�X�̐ݒ�
	object_3d_data->set_matrix(matrix);

	// �e�N�X�`���̐ݒ�
	object_3d_data->set_texture_name(texture_name);

	// �����_�[�X�e�[�g�̐ݒ�
	object_3d_data->set_renderstate(renderstate);

	// �o�b�t�@���X�g�ɒǉ�
	object_3d_buffer_->AddList(object_3d_data);
}

//---------------------------------- EOF --------------------------------------
