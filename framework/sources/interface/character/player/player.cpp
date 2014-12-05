//*****************************************************************************
//
// �v���C���[�N���X
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "player.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPlayer::CPlayer(CInterfaceManager* interface_manager)
{
	//�C���^�[�t�F�[�X�}�l�[�W���[�̕ۑ�
	interface_manager_ = interface_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CPlayer::Init(void)
{
	// �I�u�W�F�N�g���f���̐���
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"ship");
	// �I�u�W�F�N�g���X�g�ɒǉ�
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList( object_model );

	//�l������
	pos_   = VECTOR3( 0.0f, 0.0f, 0.0f );
	rot_   = VECTOR3( 0.0f, 0.0f, 0.0f );
	scale_ = VECTOR3( 1.0f, 1.0f, 1.0f );

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayer::Update(void)
{
	//pos._x += 0.1f;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �`��
	interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->
		Draw(object_key_,pos_,rot_,scale_,MATRIX4x4(), "field000");
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
}

//---------------------------------- EOF --------------------------------------
