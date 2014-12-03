//*****************************************************************************
//
// �Q�[���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// scene
#include "scene/title/scene_title.h"
#include "scene/factory/scene_factory.h"

// interface
#include "interface/interface_manager.h"

// input
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"
#include "interface/input/input_alias.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/object/object_3d/element/object_model.h"


#include "interface/graphic/object/object_3d/element/rectangle_3d.h"

#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"


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
CSceneGame::CSceneGame(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_GAME)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneGame::~CSceneGame(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CSceneGame::Init(void)
{
	// �L�����N�^�[�̏�����

	// �}�b�v�̏�����

	// �J�����̏�����

	// �l�b�g���[�N�̏�����

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CSceneGame::Update(void)
{
	// �l�b�g���[�N��M�f�[�^�̊m�F

	// �L�����N�^�[�̍X�V

	// �T�[�o�[�Ƀf�[�^���M
}

//=============================================================================
// �`��
//=============================================================================
void CSceneGame::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	
	object_2d_manager->Draw(object_2d_key_,VECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"field000",NULL);
}

//=============================================================================
// �I������
//=============================================================================
void CSceneGame::Uninit(void)
{
}

//=============================================================================
// �����̃t�@�N�g���[�̐���
//=============================================================================
CSceneFactory* CSceneGame::MakeFactory(void)
{
	// �Q�[���t�@�N�g���[�̐���
	return new CGameFactory();
}

//=============================================================================
// ���[�h����
//=============================================================================
void CSceneGame::Load(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CDeviceHolder* device_holder = graphic_manager->device_holder();
	CTextureManager* texture_manager = graphic_manager->texture_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	CCameraManager* camera_manager = object_manager->camera_manager();
	CModelManager* model_manager = graphic_manager->model_manager();

	// �v���C���[�̐���

	// �}�b�v�̐���

	// �J�����̐���

	// ���C�g�̐���

	// �ȉ��e�X�g�v���O����
	CRectangle2D* pRect2D = new CRectangle2D(device_holder);
	pRect2D->set_size(VECTOR2(1000,1000));
	pRect2D->Set();

	// �Q�[���̃e�N�X�`���̃��[�h
	texture_manager->Load("resources/texture/game");

	object_2d_key_ = object_2d_manager->AddList(pRect2D);

	// �Q�[���̃��f���̃��[�h
	model_manager->Load("resources/model/game");
}

//---------------------------------- EOF --------------------------------------
