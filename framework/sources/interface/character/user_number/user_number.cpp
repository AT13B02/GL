//*****************************************************************************
//
// ���[�U�[�i���o�[�N���X
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "user_number.h"
//billboard
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CUserNumber::CUserNumber(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CUserNumber::~CUserNumber(void)
{
}

//=============================================================================
// ��������
//=============================================================================
void CUserNumber::SetParameter(const VECTOR3& position , const s32& player_id )
{
	position_ = position;
	player_id_ = player_id;
}

//=============================================================================
// ����������
//=============================================================================
bool CUserNumber::Init(void)
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	CBillboard* object_bill = new CBillboard(interface_manager_->graphic_manager()->device_holder());
	object_bill->set_size(VECTOR2(10.0f,10.0f));
	object_bill->Set();

	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_bill);
	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CUserNumber::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CUserNumber::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// �`��
	object_3d_manager->Draw(object_key_,position_,VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"snowball001");
}

//=============================================================================
// �I������
//=============================================================================
void CUserNumber::Uninit( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	object_3d_manager->EraseList( object_key_ );

}
//=============================================================================
// ��������
//=============================================================================
void CUserNumber::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
