//*****************************************************************************
//
// �I�u�W�F�N�g2D�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/object_2d_list.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"
#include "interface/graphic/object/object_2d/object_2d_buffer.h"
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
CObject2DManager::CObject2DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager)
{
	// �O���t�B�b�N�f�o�C�X�̐ݒ�
	device_holder_ = device_holder;

	// �����_�[�X�e�[�g�}�l�[�W���[�̐ݒ�
	renderstate_manager_ = renderstate_manager;

	// �e�N�X�`���}�l�[�W���̐ݒ�
	texture_manager_ = texture_manager;

	// �J�����}�l�[�W���[�̐ݒ�
	camera_manager_ = camera_manager;

	// ���C�g�}�l�[�W���[�̐ݒ�
	light_manager_ = light_manager;

	// �I�u�W�F�N�g���X�g�̐���
	object_2d_list_ = new CObject2DList();

	// �I�u�W�F�N�g�o�b�t�@�̐���
	object_2d_buffer_ = new CObject2DBuffer();
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject2DManager::~CObject2DManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CObject2DManager::Init(void)
{
	INIT(object_2d_list_);
	INIT(object_2d_buffer_);
	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject2DManager::Draw(void)
{
	CCamera* camera = NULL;

	//light Setting

	//RenderState Setting
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_2D)->Set();

	//for(int i = 0;i < camera_manager_->number_count();i++)
	//{
		// �J�����̐ݒ�Ɛݒ肵���J�����̎擾
		//camera = camera_manager_->SetCamera(i);

		// �o�b�t�@�̕`�揈��
		object_2d_buffer_->Draw(camera,texture_manager_);
	//}

	// TODO �o�b�t�@�̔j�� �X���b�h�𕪂�����Ȃ��Ȃ�
	object_2d_buffer_->Refresh();

	//End of RenderState
	renderstate_manager_->renderstate(CRenderstateManager::TYPE_2D)->Unset();
	
}

//=============================================================================
// �I������
//=============================================================================
void CObject2DManager::Uninit(void)
{
	// �I�u�W�F�N�g���X�g�̊J��
	SAFE_RELEASE(object_2d_list_);

	// �o�b�t�@�̊J��
	SAFE_RELEASE(object_2d_buffer_);
}

//=============================================================================
// �I�u�W�F�N�g�ǉ�����
//=============================================================================
u32 CObject2DManager::AddList(CObject2D* object_2d)
{
	return object_2d_list_->AddList(object_2d);
}

//=============================================================================
// �`�惊�X�g�ɕۑ�
//=============================================================================
void CObject2DManager::Draw(const u32& object_key,const VECTOR2& position,const float rotation,const VECTOR2& scale,MATRIX4x4 matrix,const std::string& texture_name)
{
	CObject2DData* object_2d_data = NULL;
	CObject2D* object_2d = object_2d_list_->GetListData(object_key);

	// �I�u�W�F�N�g�ԍ��̊m�F
	if(object_2d == NULL)
	{
		return;
	}

	// �o�b�t�@�̐���
	object_2d_data = new CObject2DData();

	// �o�b�t�@�ԍ��̐ݒ�
	object_2d_data->set_object_2d(object_2d);

	// ���W�̐ݒ�
	object_2d_data->set_position(position);

	// ��]�p�̐ݒ�
	object_2d_data->set_rotation(rotation);

	// �X�P�[���̐ݒ�
	object_2d_data->set_scale(scale);

	// �}�g���b�N�X�̐ݒ�
	object_2d_data->set_matrix(matrix);

	// �e�N�X�`���̐ݒ�
	object_2d_data->set_texture_name(texture_name);

	// �����_�[�X�e�[�g�̐ݒ�
	object_2d_data->set_renderstate(NULL);

	// �o�b�t�@���X�g�ɒǉ�
	object_2d_buffer_->AddList(object_2d_data);
}

//---------------------------------- EOF --------------------------------------
