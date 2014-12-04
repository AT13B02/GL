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
#include "interface/character/player/player.h"
#include "interface/character/character_manager.h"

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
	// �L�����N�^�[�}�l�[�W���[�̐����A������
	CCharacterManager *character_manager = interface_manager_->character_manager();
	character_manager->Init();

	// �v���C���[�̐���
	CPlayer *player = new CPlayer(interface_manager_);
	//�v���C���[������
	player->Init();
	//���X�g�֐ݒ�
	character_manager->player_manager()->Push( player );

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
	interface_manager_->character_manager()->Update();

	// �T�[�o�[�Ƀf�[�^���M
}

//=============================================================================
// �`��
//=============================================================================
void CSceneGame::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CCharacterManager *character_manager = interface_manager_->character_manager();

	// �`��
	character_manager->Draw();
	//object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000",NULL);
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
	CCameraManager* camera_manager = object_manager->camera_manager();
	CModelManager* model_manager = graphic_manager->model_manager();
	CCharacterManager *character_manager = interface_manager_->character_manager();



	// �}�b�v�̐���

	// �J�����̐���

	// ���C�g�̐���

	// �ȉ��e�X�g�v���O����

	//CRectangle3D* billboard = new CRectangle3D(device_holder);

	//billboard->set_size(VECTOR2(10,10));

	//billboard->Set();

	// �Q�[���̃e�N�X�`���̃��[�h
	texture_manager->Load("resources/texture/game");

	// �I�u�W�F�N�g�̐���
	//test_object_key_ = object_3d_manager->AddList(billboard);

	// �Q�[���̃��f���̃��[�h
	model_manager->Load("resources/model/game");

	// �I�u�W�F�N�g���f���̐���
/*	CObjectModel* object_model = new CObjectModel(device_holder,"ship");

	// �I�u�W�F�N�g���X�g�ɒǉ�
	test_object_key_ = object_3d_manager->AddList(object_model);

*/
	// �J�����̎擾
	test_camera_ = camera_manager->GetCamera(camera_manager->CreateCamera());
}

//---------------------------------- EOF --------------------------------------
