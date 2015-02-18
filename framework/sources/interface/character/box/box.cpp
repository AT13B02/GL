//*****************************************************************************
//
// ���N���X
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "box.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

#include "../character_manager.h"

#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBox::CBox(CInterfaceManager* interface_manager)
{
	//�C���^�[�t�F�[�X�}�l�[�W���[�̕ۑ�
	interface_manager_ = interface_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBox::~CBox(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CBox::Init(void)
{
	// �I�u�W�F�N�g���f���̐���
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");

	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);
	
	//�l������
	position_ = VECTOR3(0.0f,0.0f,0.0f);
	rotation_ = VECTOR3(0.0f,0.0f,0.0f);
	scale_    = VECTOR3(1.0f,1.0f,1.0f);

	// �����蔻�菉����
	collision_.add(-25.0f,  0.0f, -25.0f);
	collision_.add( 25.0f, 50.0f,  25.0f);

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CBox::Update(void)
{
}

//=============================================================================
// �I������
//=============================================================================
void CBox::Uninit(void)
{
}

//=============================================================================
//�`��
//=============================================================================
void CBox::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// �`��
	object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"yukidaruma");
}

//=============================================================================
// ���W�ݒ�
//=============================================================================
void CBox::position(const VECTOR3& position)
{
	position_._x = position._x;
	position_._y = position._y;
	position_._z = position._z;
}

//=============================================================================
// ���W�ݒ�
//=============================================================================
void CBox::position(const f32 x, const f32 y, const f32 z)
{
	position_._x = x;
	position_._y = y;
	position_._z = z;
}

//=============================================================================
// ���W�擾
//=============================================================================
const VECTOR3& CBox::position()
{
	return position_;
}

//=============================================================================
// �����蔻��擾
//=============================================================================
const AABB& CBox::collision()
{
	return collision_;
}

// EOF