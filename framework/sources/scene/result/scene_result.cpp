//*****************************************************************************
//
// �^�C�g���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// scene
#include "scene/result/scene_result.h"
#include "scene/factory/scene_factory.h"

// input
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"
#include "interface/input/input_alias.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"

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
CSceneResult::CSceneResult(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	test_object_key_ = -1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneResult::~CSceneResult(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CSceneResult::Init(void)
{
	if(!CScene::Init())
	{
		return false;
	}

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CSceneResult::Update(void)
{
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
	{
		set_next_scene(new CTitleFactory());
	}
}

//=============================================================================
// �`��
//=============================================================================
void CSceneResult::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// �`��
	object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"");
}

//=============================================================================
// �I��
//=============================================================================
void CSceneResult::Uninit(void)
{
}

//=============================================================================
// ���[�h
//=============================================================================
void CSceneResult::Load(void)
{
	CGraphicManager* graphic_manager	= interface_manager_->graphic_manager();
	CDeviceHolder* device_holder		= graphic_manager->device_holder();
	CTextureManager* texture_manager	= graphic_manager->texture_manager();
	CObjectManager* object_manager		= graphic_manager->object_manager();
	CObject3DManager* object_3d_manager	= object_manager->object_3d_manager();

	CRectangle3D* billboard = new CRectangle3D(device_holder);
	billboard->set_size(VECTOR2(200,200));
	billboard->Set();

	// �^�C�g���t�H���_�̃��[�h
	texture_manager->Load("resources/texture/title");

	// �I�u�W�F�N�g�̐���
	test_object_key_ = object_3d_manager->AddList(billboard);
}

//=============================================================================
// �����̃t�@�N�g���[�̐���
//=============================================================================
CSceneFactory* CSceneResult::MakeFactory(void)
{
	return new CResultFactory();
}

//---------------------------------- EOF --------------------------------------
