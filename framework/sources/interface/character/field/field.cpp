//*****************************************************************************
//
// �t�B�[���h�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "field.h"
#include "interface/graphic/object/object_3d/element/meshfield.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

#include "../character_manager.h"
#include "../bullet/bullet_manager.h"
#include "../bullet/bullet.h"

#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CField::CField(CInterfaceManager* interface_manager)
{
	// �C���^�[�t�F�[�X�}�l�[�W���[�̕ۑ�
	interface_manager_ = interface_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CField::~CField(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CField::Init(void)
{
	// �I�u�W�F�N�g���f���̐���
	meshfield_ = new CMeshfield(interface_manager_->graphic_manager()->device_holder());
	meshfield_->Init();
	meshfield_->set_grid_length(50.0f,50.0f);
	meshfield_->set_grid_number(10,10);
	meshfield_->Set();

	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(meshfield_);

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CField::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CField::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// �`��
	object_3d_manager->Draw(object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000");
}

//=============================================================================
// �I������
//=============================================================================
void CField::Uninit(void)
{
}

//=============================================================================
// �����擾
//=============================================================================
f32 CField::get_height(const VECTOR3& in_position, VECTOR3* p_out_normal)
{
	return meshfield_->get_height(in_position, p_out_normal);
}

//---------------------------------- EOF --------------------------------------
