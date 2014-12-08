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

// interface
#include "../interface_manager.h"

// input
#include "../input/input_manager.h"

// common
#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CAttitudeController::CAttitudeController(CInterfaceManager* interface_manager) : interface_manager_(interface_manager)
{
	basic_vector_ = VECTOR3(0.0f,0.0f,1.0f);

	basic_vector_.Normalize();

	axis_ = VECTOR3(0.0f,1.0f,0.0f);

	axis_.Normalize();
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

	if(input_manager->CheckPress(INPUT_EVENT_U))
	{
		rotation_ += MTH_DEGREE * 1.0f;
	}

	if(input_manager->CheckPress(INPUT_EVENT_O))
	{
		rotation_ -= MTH_DEGREE * 1.0f;
	}

	// �O���x�N�g�������߂�
	front_vector_ = basic_vector_.RotationAxis(axis_,rotation_);
	front_vector_.Normalize();
}

//---------------------------------- EOF --------------------------------------
