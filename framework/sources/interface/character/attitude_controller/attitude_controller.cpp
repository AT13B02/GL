//*****************************************************************************
//
// �p������N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// character
#include "attitude_controller.h"
#include "../character_interface.h"

// interface
#include "interface/interface_manager.h"

// input
#include "interface/input/input_manager.h"

// common
#include "common/common.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
const f32 CAM_ROT_MAX=0.00625f;
const f32 CAM_ROT_MIN=-0.62f;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAttitudeController::CAttitudeController(CInterfaceManager* interface_manager) : interface_manager_(interface_manager)
{
	basic_vector_ = VECTOR3(0.0f,0.0f,1.0f);

	basic_vector_.Normalize();

	axis_ = VECTOR3(0.0f,1.0f,0.0f);

	axis_.Normalize();

	rotation_ = VECTOR3(0.0f,0.0f,0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CAttitudeController::~CAttitudeController(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CAttitudeController::Init(void)
{
	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CAttitudeController::Uninit(void)
{
}

//=============================================================================
// �X�V
//=============================================================================
void CAttitudeController::Update(void)
{
	CInputManager* input_manager = interface_manager_->input_manager();

	//����ɂ��J��������]������
	if(input_manager->CheckPress(INPUT_EVENT_RIGHT))
	{
		rotation_._y += MTH_DEGREE * 1.0f;
	}

	if(input_manager->CheckPress(INPUT_EVENT_LEFT))
	{
		rotation_._y -= MTH_DEGREE * 1.0f;
	}

	if(input_manager->CheckPress(INPUT_EVENT_DOWN))
	{
		rotation_._x -= MTH_DEGREE * 1.0f;
	}

	if(input_manager->CheckPress(INPUT_EVENT_UP))
	{
		rotation_._x += MTH_DEGREE * 1.0f;
	}


	//�J�����̓����ɐ�����������
	if(rotation_._x>=CAM_ROT_MAX)
	{
		rotation_._x=CAM_ROT_MAX;
	}

	if(rotation_._x<=CAM_ROT_MIN)
	{
		rotation_._x=CAM_ROT_MIN;
	}
	// �O���x�N�g�������߂�
	front_vector_ = basic_vector_.RotationAxis(VECTOR3(1.0f,0.0f,0.0f),rotation_._x);
	front_vector_.Normalize();
	front_vector_ = front_vector_.RotationAxis(VECTOR3(0.0f,1.0f,0.0f),rotation_._y);
	front_vector_.Normalize();

	// �E�x�N�g��
	right_vector_ = front_vector_.CrossProduct(VECTOR3(0.0f,1.0f,0.0f));
	right_vector_.Normalize();

	for(auto it = character_container_.begin();it != character_container_.end();++it)
	{
		(*it)->set_front_vector(front_vector_);
		(*it)->set_right_vector(right_vector_);
	}
}

//=============================================================================
// �ǉ�����
//=============================================================================
void CAttitudeController::Push(CCharacterInterface* character_interface)
{
	character_container_.push_back(character_interface);
}

//---------------------------------- EOF --------------------------------------
