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
#include "scene/game/scene_game.h"
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
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/model/model_manager.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/light/light_manager.h"
#include "interface/graphic/light/light.h"
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/object/object_3d/element/meshfield.h"

// character
#include "interface/character/character_manager.h"
#include "interface/character/player/player_manager.h"
#include "interface/character/player/player.h"
#include "interface/character/camera/character_camera.h"
#include "interface/character/camera/character_camera_manager.h"
#include "interface/character/bullet/bullet_manager.h"
#include "interface/character/bullet/bullet.h"

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

	// ��M�f�[�^�����ɍX�V(��������W�̒���)

	// �����蔻��

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
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// TODO �`��e�X�g
	object_3d_manager->Draw(test_meshfield_key_,VECTOR3(0.0f,0.0f,0.0f),VECTOR3(0.0f,0.0f,0.0f),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"field000");
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
	CLightManager* light_manager = graphic_manager->light_manager();
	CCharacterManager* character_manager = interface_manager_->character_manager();
	CPlayerManager* player_manager = character_manager->player_manager();
	CCharacterCameraManager* character_camera_manager = character_manager->character_camera_manager();
	CBulletManager* bullet_manager = character_manager->bullet_manager();
	// �Q�[���̃e�N�X�`���̃��[�h
	texture_manager->Load("resources/texture/game");

	// �Q�[���̃��f���̃��[�h
	model_manager->Load("resources/model/game");

	// ���C�g�̐ݒ�
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(1.0f,0.0f,0.0f).Normalize());
	light_manager->Add(light);

	// �v���C���[�̐���
	CPlayer* player = new CPlayer(interface_manager_);
	player->Init();
	player_manager->Push(player);

	// �o���b�g�̐���
	CBullet* bullet = new CBullet( interface_manager_ );
	bullet->CreateBullet( VECTOR3(0,0,0) , VECTOR3(0,0,0) );
	bullet_manager->Push(bullet);

	// �J�����̐���
	CCharacterCamera* camera = new CCharacterCamera(interface_manager_);
	camera->Init();
	character_camera_manager->Push(camera);





	// TODO �ȉ��e�X�g�v���O����

	// ���b�V���t�B�[���h
	CMeshfield* mesh_field = new CMeshfield(device_holder);
	mesh_field->Init();
	mesh_field->set_grid_number(10,10);
	mesh_field->set_grid_length(100.0f,100.0f);
	mesh_field->Set();
	test_meshfield_key_ = object_3d_manager->AddList(mesh_field);
}

//---------------------------------- EOF --------------------------------------
