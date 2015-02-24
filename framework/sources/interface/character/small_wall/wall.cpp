//*****************************************************************************
//
// �ǃN���X
// Author		: ooigawa kazuma
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "wall.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"

#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/input/input_manager.h"

#include "../character_manager.h"

#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWall::CWall( CInterfaceManager* interface_manager , WALL_KIND wall_kind)
{
	//�C���^�[�t�F�[�X�}�l�[�W���[�̕ۑ�
	interface_manager_ = interface_manager;
	wall_kind_ = wall_kind;
	CObjectModel* object_model ;
	switch( wall_kind_ )
	{
	case WALL_KIND_BIG:
		// �I�u�W�F�N�g���f���̐���
		object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"big_wall");
		break;
	case WALL_KIND_SMALL:
		// �I�u�W�F�N�g���f���̐���
		object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"small_wall");
		break;
	}
	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWall::~CWall( void )
{
}
//=============================================================================
// ������
//=============================================================================
bool CWall::Init( void )
{
	//�ϐ�������
	position_	= VECTOR3( 0.0f , 0.0f , 0.0f );
	rotation_	= VECTOR3( 0.0f , 0.0f , 0.0f );
	scale_		= VECTOR3( 1.0f , 1.0f , 1.0f );

	return true;
}
//=============================================================================
// �X�V
//=============================================================================
void CWall::Update( void )
{
}
//=============================================================================
// �`�揈��
//=============================================================================
void CWall::Draw( void )
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	switch( wall_kind_ )
	{
	case WALL_KIND_BIG:
		// �`��
		object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"big_wall");
		break;
	case WALL_KIND_SMALL:
		// �`��
		object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"small_wall");
		break;
	}

}