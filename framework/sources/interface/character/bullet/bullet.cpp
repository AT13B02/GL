//*****************************************************************************
//
// �o���b�g�N���X
//
// Author		: Kazuma Ooigawa
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

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBullet::CBullet( CInterfaceManager* interface_manager )
{
	interface_manager_ = interface_manager;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBullet::~CBullet( void )
{
}
//=============================================================================
// ��������
//=============================================================================
void CBullet::CreateBullet( VECTOR3 _pos , VECTOR3 _rot )
{
	pos = _pos;
	rot = _rot;
	speed = 0.5f;
	Init();
}
//=============================================================================
// ����������
//=============================================================================
bool CBullet::Init( void )
{
	// �I�u�W�F�N�g�r���{�[�h�̐���
	CBillboard* object_bill = new CBillboard( interface_manager_->graphic_manager()->device_holder());
	object_bill->set_size( VECTOR2( 10 , 10 ) );
	object_bill->Set();
	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList( object_bill );


	return true;
}
//=============================================================================
// �X�V����
//=============================================================================
void CBullet::Update( void )
{
	pos._y += sinf( rot._x )*speed;
	pos._x += sinf( rot._y )*speed;
	pos._z += cosf( rot._y )*speed;
}
//=============================================================================
// �`�揈��
//=============================================================================
void CBullet::Draw( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	// �`��
	object_3d_manager->Draw(object_key_,pos,rot,VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000");
}
//=============================================================================
// �I������
//=============================================================================
void CBullet::Uninit( void )
{
	//billboard->Release();
}

//---------------------------------- EOF --------------------------------------
