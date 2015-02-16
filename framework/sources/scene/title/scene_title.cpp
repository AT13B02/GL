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
#include "scene/title/scene_title.h"
#include "scene/factory/scene_factory.h"

// input
#include "interface/interface_manager.h"
#include "interface/input/input_manager.h"
#include "interface/input/input_alias.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/element/rectangle_3d.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/light/light_manager.h"
#include "interface/graphic/light/light.h"
#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/model/model_manager.h"

// character
#include "interface/character/character_manager.h"
#include "interface/character/field/field.h"
#include "interface/character/field/field_manager.h"
#include "interface/character/camera/title_camera.h"
#include "interface/character/camera/character_camera_manager.h"

// common
#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TIKATIKA_CHANGE_POINT       (30)

#define TITLE_LOGO_POS_X_INIT       (650)
#define TITLE_LOGO_POS_Y_INIT       (100)
#define TITLE_LOGO_TEX_SIZE_X_INIT  (670)
#define TITLE_LOGO_TEX_SIZE_Y_INIT  (100)
#define TITLE_LOGO_SCL_X_INIT       (1)
#define TITLE_LOGO_SCL_Y_INIT       (1)
#define TITLE_LOGO_TEX_NAME         ("title")

#define TITLE_ENTER_POS_X_INIT      (650)
#define TITLE_ENTER_POS_Y_INIT      (620)
#define TITLE_ENTER_TEX_SIZE_X_INIT (609)
#define TITLE_ENTER_TEX_SIZE_Y_INIT (62)
#define TITLE_ENTER_SCL_X_INIT      (1)
#define TITLE_ENTER_SCL_Y_INIT      (1)
#define TITLE_ENTER_TEX_NAME        ("pleaseEnter")

#define TITLE_CHARA_POS_X_INIT      (0)
#define TITLE_CHARA_POS_Y_INIT      (40)
#define TITLE_CHARA_POS_Z_INIT      (60)
#define TITLE_CHARA_DISTANCE_X_INIT     (15)
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneTitle::CSceneTitle(CInterfaceManager* interface_manager) : CScene(interface_manager,TYPE_TITLE)
{
	logo_object_key_ = -1;
	enter_object_key_ = -1;
	daruma_object_key_ = -1;
	field_object_key_ = -1;

	tikatika_=true;
	center_daruma_height=TITLE_CHARA_POS_Y_INIT;
	is_daruma_up=true;
	tikatika_counter=0;
	jump_cnt=0;
	rot_=0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneTitle::~CSceneTitle(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CSceneTitle::Init(void)
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
void CSceneTitle::Update(void)
{
	//�G���^�[�L�[�������ꂽ��V�[���؂�ւ�
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_RETURN))
	{
		set_next_scene(new CGameFactory());
	}

	//PUSHENTER�̓_�ŏ���
	tikatika_counter++;
	if(tikatika_counter>=TIKATIKA_CHANGE_POINT)
	{
		tikatika_counter=0;
		tikatika_=!tikatika_;
	}

	//�p�x�X�V
	rot_ += 2.0f;
	//�p�x����
	if( rot_ > 180 )
	{
		rot_ = -180.0f;
	}

	//�^�񒆂̂���܂̃W�����v����
	if(is_daruma_up)
	{
		jump_cnt++;
		center_daruma_height+=0.4f;
		if(jump_cnt>=12)
		{
			jump_cnt=0;
			is_daruma_up=!is_daruma_up;
		}
	}

	else
	{
		jump_cnt++;
		center_daruma_height-=0.4f;
		if(jump_cnt>=12)
		{
			jump_cnt=0;
			is_daruma_up=!is_daruma_up;
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CSceneTitle::Draw(void)
{
	//�}�l�[�W���[���擾
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();

	// �`��
	object_3d_manager->Draw(daruma_object_key_ ,VECTOR3((TITLE_CHARA_POS_X_INIT+TITLE_CHARA_DISTANCE_X_INIT*-2),TITLE_CHARA_POS_Y_INIT,TITLE_CHARA_POS_Z_INIT),VECTOR3(0,rot_,0),VECTOR3(1,1,1),MATRIX4x4(),"");
	object_3d_manager->Draw(daruma_object2_key_,VECTOR3((TITLE_CHARA_POS_X_INIT+TITLE_CHARA_DISTANCE_X_INIT*-1),TITLE_CHARA_POS_Y_INIT,TITLE_CHARA_POS_Z_INIT),VECTOR3(0,rot_,0),VECTOR3(1,1,1),MATRIX4x4(),"");
	object_3d_manager->Draw(daruma_object3_key_,VECTOR3((TITLE_CHARA_POS_X_INIT+TITLE_CHARA_DISTANCE_X_INIT* 0),center_daruma_height,TITLE_CHARA_POS_Z_INIT),VECTOR3(0,rot_,0),VECTOR3(1,1,1),MATRIX4x4(),"");
	object_3d_manager->Draw(daruma_object4_key_,VECTOR3((TITLE_CHARA_POS_X_INIT+TITLE_CHARA_DISTANCE_X_INIT* 1),TITLE_CHARA_POS_Y_INIT,TITLE_CHARA_POS_Z_INIT),VECTOR3(0,rot_,0),VECTOR3(1,1,1),MATRIX4x4(),"");
	object_3d_manager->Draw(daruma_object5_key_,VECTOR3((TITLE_CHARA_POS_X_INIT+TITLE_CHARA_DISTANCE_X_INIT* 2),TITLE_CHARA_POS_Y_INIT,TITLE_CHARA_POS_Z_INIT),VECTOR3(0,rot_,0),VECTOR3(1,1,1),MATRIX4x4(),"");

	object_2d_manager->Draw(logo_object_key_,VECTOR2(TITLE_LOGO_POS_X_INIT,TITLE_LOGO_POS_Y_INIT),0,VECTOR2(TITLE_LOGO_SCL_X_INIT,TITLE_LOGO_SCL_Y_INIT),MATRIX4x4(),TITLE_LOGO_TEX_NAME);
	if(tikatika_)
	{
		object_2d_manager->Draw(logo_object_key_,VECTOR2(TITLE_ENTER_POS_X_INIT,TITLE_ENTER_POS_Y_INIT),0,VECTOR2(TITLE_ENTER_SCL_X_INIT,TITLE_ENTER_SCL_Y_INIT),MATRIX4x4(),TITLE_ENTER_TEX_NAME);
	}
}
//=============================================================================
// �I��
//=============================================================================
void CSceneTitle::Uninit(void)
{
	CCharacterManager* character_manager = interface_manager_->character_manager();
	character_manager->Clear();
}

//=============================================================================
// ���[�h
//=============================================================================
void CSceneTitle::Load(void)
{
	//�}�l�[�W���[���擾
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
	CFieldManager* field_manager = character_manager->field_manager();
	CCharacterCameraManager* character_camera_manager = character_manager->character_camera_manager();

	// �^�C�g���t�H���_�̃��[�h
	texture_manager->Load("resources/texture/title");
	// �^�C�g���̃��f���̃��[�h
	model_manager->Load("resources/model/title");

	// ���C�g�̐ݒ�
	CLight* light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(1.0f,0.0f,0.0f).Normalize());
	light_manager->Add(light);

	// ���C�g�̐ݒ�
	light = CLight::Create(device_holder);
	light->Init();
	light->SetType(CLight::TYPE_DIRECTIONAL);
	light->SetDirection(VECTOR3(0.0f,-1.0f,0.0f).Normalize());
	light_manager->Add(light);

	//���S�|���S������
	CRectangle2D* Logo = new CRectangle2D(device_holder);
	Logo->set_size(VECTOR2(TITLE_LOGO_TEX_SIZE_X_INIT,TITLE_LOGO_TEX_SIZE_Y_INIT));
	Logo->Set();
	logo_object_key_ = object_2d_manager->AddList(Logo);

	//�v���[�Y�G���^�[�|���S������
	CRectangle2D* Enter = new CRectangle2D(device_holder);
	Enter->set_size(VECTOR2(TITLE_ENTER_TEX_SIZE_X_INIT,TITLE_ENTER_TEX_SIZE_Y_INIT));
	Enter->Set();
	enter_object_key_ = object_2d_manager->AddList(Enter);

	// �Ⴞ��܃��f���̐���
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	daruma_object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model);
	
	CObjectModel* object_model2 = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	daruma_object2_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model2);
	
	CObjectModel* object_model3 = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	daruma_object3_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model3);
	
	CObjectModel* object_model4 = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	daruma_object4_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model4);

	CObjectModel* object_model5 = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
	daruma_object5_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(object_model5);

	// �t�B�[���h�̐���
	CField* field = new CField(interface_manager_);
	field->Init();
	field_manager->Push(field);

	// �J�����̐���
	CTitleCamera* camera = new CTitleCamera(interface_manager_);
	camera->Init();
	character_camera_manager->Push(camera);
}

//=============================================================================
// �����̃t�@�N�g���[�̐���
//=============================================================================
CSceneFactory* CSceneTitle::MakeFactory(void)
{
	return new CTitleFactory();
}

//---------------------------------- EOF --------------------------------------
