//*****************************************************************************
//
// �o���b�g�N���X
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "bullet.h"
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
const f32 CBullet::DEFAULT_RADIUS = 5.0f;
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet(void)
{
}

//=============================================================================
// ��������
//=============================================================================
void CBullet::SetParameter(const VECTOR3& position,const VECTOR3& vector,const f32& speed , const s32& player_id )
{
	position_ = position;
	vector_ = vector;
	speed_ = speed;
	player_id_ = player_id;
}

//=============================================================================
// ����������
//=============================================================================
bool CBullet::Init(void)
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	CBillboard* object_bill = new CBillboard(interface_manager_->graphic_manager()->device_holder());
	object_bill->set_size(VECTOR2(10.0f,10.0f));
	object_bill->Set();

	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_bill);
	radius_ = DEFAULT_RADIUS;
	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update(void)
{
	position_ += vector_ * speed_;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw(void)
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
void CBullet::Uninit( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	object_3d_manager->EraseList( object_key_ );

}
//=============================================================================
// �e��������
//=============================================================================
void CBullet::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
