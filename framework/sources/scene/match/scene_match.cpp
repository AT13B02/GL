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
#include "scene/match/scene_match.h"
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
const float CSceneMatch::PLAYER_DISP_OFFSET_X = 600.0f;
const float CSceneMatch::PLAYER_DISP_OFFSET_Y = 70.0f;
const float CSceneMatch::PLAYER_DISP_START_Y =180.0f;
const VECTOR2 CSceneMatch::HOST_DECITION_DEFAULT_POS(600.0f,600.0f);
const VECTOR2 CSceneMatch::LOGO_DEFAULT_POS(600.0f,60.0f);

const char* CSceneMatch::p_texture_names[TEXTURE_TYPE_MAX] = 
{
	"field001",//logo
	"field001",//player
	"field001",//player
	"field001",//player
	"field001",//player
	"field001",//host
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneMatch::CSceneMatch(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	test_object_key_ = -1;
	test_2d_key_ = -1;

	host_decision_key_ = -1;

	for(int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{ 
		player_Disp_2d_key_[nPlayer] = -1;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneMatch::~CSceneMatch(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CSceneMatch::Init(void)
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
void CSceneMatch::Update(void)
{
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
	{
		set_next_scene(new CGameFactory());
	}
}

//=============================================================================
// �`��
//=============================================================================
void CSceneMatch::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// �`��
	//object_3d_manager->Draw(test_object_key_,VECTOR3(),VECTOR3(90,0,0),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"");
	//object_2d_manager->Draw(test_2d_key_,VECTOR2(),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"");
	object_2d_manager->Draw(host_decision_key_,HOST_DECITION_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_HOST_DECISION]);
	object_2d_manager->Draw(logo_key_,LOGO_DEFAULT_POS,0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[TEXTURE_TYPE_LOGO]);

	for(int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		object_2d_manager->Draw(player_Disp_2d_key_[nPlayer],VECTOR2(PLAYER_DISP_OFFSET_X,nPlayer * PLAYER_DISP_OFFSET_Y +CSceneMatch::PLAYER_DISP_START_Y),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),p_texture_names[1+nPlayer]);
	}
}

//=============================================================================
// �I��
//=============================================================================
void CSceneMatch::Uninit(void)
{
}

//=============================================================================
// ���[�h
//=============================================================================
void CSceneMatch::Load(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CDeviceHolder* device_holder = graphic_manager->device_holder();
	CTextureManager* texture_manager = graphic_manager->texture_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	texture_manager->Load("resources/texture/game");

	CRectangle3D* billboard = new CRectangle3D(device_holder);

	billboard->set_size(VECTOR2(200,200));
	
	billboard->Set();

	// �^�C�g���t�H���_�̃��[�h
	texture_manager->Load("resources/texture/title");

	// �I�u�W�F�N�g�̐���
	test_object_key_ = object_3d_manager->AddList(billboard);


	CRectangle2D* p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(200,200));
	p_rect2D->Set();
	test_2d_key_ = object_2d_manager->AddList(p_rect2D);

	for(int nPlayer = 0; nPlayer < PLAYER_MAX; nPlayer++)
	{
		CRectangle2D* p_rect2D = new CRectangle2D(device_holder);
		p_rect2D->set_size(VECTOR2(512,64));
		p_rect2D->Set();
		player_Disp_2d_key_[nPlayer] = object_2d_manager->AddList(p_rect2D);
	}

	//host board loading
	p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(128,128));
	p_rect2D->Set();
	host_decision_key_ = object_2d_manager->AddList(p_rect2D);

	//logo text loading
	p_rect2D = new CRectangle2D(device_holder);
	p_rect2D->set_size(VECTOR2(512,128));
	p_rect2D->Set();
	logo_key_ = object_2d_manager->AddList(p_rect2D);
	
}

//=============================================================================
// �����̃t�@�N�g���[�̐���
//=============================================================================
CSceneFactory* CSceneMatch::MakeFactory(void)
{
	return new CMatchFactory();
}

//---------------------------------- EOF --------------------------------------
