//*****************************************************************************
//
// �V�[���}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// scene
#include "scene/scene.h"
#include "scene/factory/scene_factory.h"
#include "scene/scene_manager.h"
#include "scene/load/scene_load.h"

#include "interface/interface_manager.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/device/device_holder.h"

// sound
#include "interface/sound/sound_manager.h"

// common
#include "common/thread/thread.h"
#include "common/common.h"

//fade
#include "interface/graphic/object/object_2d/element/fade_2d.h"

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
CSceneManager::CSceneManager(CInterfaceManager* interface_manager)
{
	// �V�[���̏�����
	scene_ = NULL;

	// ���[�h�t���O�̏�����
	load_flag_ = false;

	// �X���b�h�̏�����
	thread_ = NULL;

	// �C���^�[�t�F�[�X�}�l�[�W���[�̐ݒ�
	interface_manager_ = interface_manager;

	// ���[�h���p�̃V�[���𐶐�
	load_ = new CSceneLoad(interface_manager);

	// ���̃V�[���̐ݒ�
	next_scene_ = new CTitleFactory();

	// �t�F�[�h
	fade_2d_ = new CFade2D(interface_manager_->graphic_manager()->device_holder(),interface_manager_);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneManager::~CSceneManager(void)
{
	
}

//=============================================================================
// ����������
//=============================================================================
bool CSceneManager::Init(void)
{
	// ���[�h���̃V�[���̃f�[�^�����[�h
	load_->Load();

	return true;
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneManager::Update(void)
{
	// ���[�h���Ă��Ȃ����Ƃ��m�F
	if(!load_flag_)
	{
		if(thread_ != NULL)
		{
			// �X���b�h���I�����Ă�����
			if(thread_->CheckEnd())
			{
				// �X���b�h�N���X�̔j��
				SAFE_RELEASE(thread_);

				// �`�惂�[�h�����C���ɐ؂芷����
				interface_manager_->graphic_manager()->device_holder()->SetDrawMode(CGraphicDevice::DEVICE_MODE_MAIN);
			}
		}

		// �V�[�������݂��Ă��邩�m�F
		if(scene_ != NULL)
		{
			scene_->Update();

			// ���̃V�[�������݂��Ȃ���
			if(next_scene_ == NULL)
			{
				next_scene_ = scene_->next_scene();
			}
		}

		// ���̃V�[�������݂���Ƃ�
		if(next_scene_ != NULL)
		{
			// ���[�h�t���O���I��
			load_flag_ = true;

			// ���[�h�����̏�����
			load_->Init();

			// �X���b�h�̐���
			thread_ = new CThread();

			// �`�惂�[�h�����[�h�ɐ؂芷����
			interface_manager_->graphic_manager()->device_holder()->SetDrawMode(CGraphicDevice::DEVICE_MODE_LOAD);
			interface_manager_->graphic_manager()->device_holder()->BeginDraw();

			// �X���b�h�Ń��[�h�J�n
			thread_->Start(Load,this);
		}
	}
	else
	{
		if(load_ != NULL)
		{
			// ���[�h���̍X�V
			load_->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneManager::Draw(void)
{
	fade_2d_->Draw(nullptr);

	// ���[�h���Ă��Ȃ����Ƃ��m�F
	if(!load_flag_)
	{
		if(scene_ != NULL)
		{
			// �`�揈��
			scene_->Draw();
		}
	}
	else
	{
		if(load_ != NULL)
		{
			load_->Draw();
		}
	}
}

//=============================================================================
// �I������
//=============================================================================
void CSceneManager::Uninit(void)
{
	// �X���b�h�̔j��
	SAFE_DELETE(thread_);

	// �V�[���̔j��
	SAFE_RELEASE(scene_);

	// ���[�h���p�̃V�[���̔j��
	SAFE_RELEASE(load_);

	// ���̃V�[���̔j��
	SAFE_DELETE(next_scene_);

	// �t�F�[�h�̔j��
	SAFE_DELETE(fade_2d_);
}

//=============================================================================
// ���[�h����
//=============================================================================
void CSceneManager::Load(CSceneManager* scene_manager)
{
	// �V�[���}�l�[�W���[�����݂���Ƃ�
	if(scene_manager != NULL)
	{
		// ���݂̃V�[������������
		if(scene_manager->scene_ != NULL)
		{
			// �V�[���������Ƃ�
			if(scene_manager->scene_->scene_type() == scene_manager->next_scene_->scene_type())
			{
				// ������
				scene_manager->scene_->Init();

				// ���[�h�̏I��
				scene_manager->load_flag_ = false;
			}
			else
			{
				// ���݂̃V�[���̊J��
				SAFE_RELEASE(scene_manager->scene_);
			}
		}

		// ���[�h����
		if(scene_manager->load_flag_)
		{
			// �C���^�[�t�F�[�X��ǂݍ��݃��[�h�ɂ���
			scene_manager->interface_manager_->graphic_manager()->device_holder()->SetLoadMode(CGraphicDevice::DEVICE_MODE_MAIN);

			// ���[�h�J�n
			scene_manager->interface_manager_->BeginLoad();

			// �V�[���̐���
			scene_manager->scene_ = scene_manager->next_scene_->Make(scene_manager->interface_manager_);

			// �ǂݍ��ݏ���
			scene_manager->scene_->Load();

			// ����������
			scene_manager->scene_->Init();

			// ���̃V�[����j��
			SAFE_DELETE(scene_manager->next_scene_);

			// �C���^�[�t�F�[�X�̓ǂݍ��݃��[�h���I������
			scene_manager->interface_manager_->EndLoad();
		}
	}

	// ���[�h�̏I��
	scene_manager->load_flag_ = false;
}

//---------------------------------- EOF --------------------------------------
