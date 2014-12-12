//*****************************************************************************
//
// �L�����N�^�[�J�����N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "interface/character/camera/player_camera.h"
#include "interface/character/player/player.h"

#include "interface/graphic/camera/camera.h"
#include "interface/graphic/camera/camera_manager.h"
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/graphic_manager.h"

#include "interface/input/input_manager.h"
#include "interface/input/input_manager.h"

#include "interface/interface_manager.h"

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
CPlayerCamera::CPlayerCamera(CInterfaceManager* interface_manager,CPlayer* player) : CCharacterCamera(interface_manager)
{
	move_speed_ = 0;

	camera_key_ = 0;

	player_ = player;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayerCamera::~CPlayerCamera(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CPlayerCamera::Init(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	WINDOW_DATA* window_data = interface_manager_->window_data();
	CCameraManager* camera_manager = graphic_manager->camera_manager();
	camera_key_ = camera_manager->CreateCamera();
	CCamera* camera = camera_manager->GetCamera(camera_key_);

	// ���������s
	if(!camera->Init())
	{
		// ������J�������폜
		camera_manager->EraseCamera(camera_key_);
		return false;
	}

	// �������W�̐ݒ�
	camera->SetPosition(VECTOR3(0.0f,10.0f,100.0f),VECTOR3(0.0f,0.0f,0.0f));

	// �p�[�X�y�N�e�B�u�̐ݒ�
	camera->SetPerspective(60.0f,((f32)(window_data->_width) / window_data->_height),1.0f,10000.0f);

	move_speed_ = 1.0f;

	length_ = 50.0f;

	return true;
}

//=============================================================================
// �X�V
//=============================================================================
void CPlayerCamera::Update(void)
{
	CInputManager* input_manager = interface_manager_->input_manager();
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CCameraManager* camera_manager = graphic_manager->camera_manager();
	CCamera* camera = camera_manager->GetCamera(camera_key_);

	VECTOR3 look_at = player_->position();
	VECTOR3 eye;

	eye = look_at - (front_vector_ * length_);

	camera->SetPosition(eye,look_at);
}

//=============================================================================
// �I��
//=============================================================================
void CPlayerCamera::Uninit(void)
{
}

//---------------------------------- EOF --------------------------------------
