//*****************************************************************************
//
// 姿勢制御クラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
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
// コンストラクタ
//=============================================================================
CAttitudeController::CAttitudeController(CInterfaceManager* interface_manager) : interface_manager_(interface_manager)
{
	basic_vector_ = VECTOR3(0.0f,0.0f,1.0f);

	basic_vector_.Normalize();

	axis_ = VECTOR3(0.0f,1.0f,0.0f);

	axis_.Normalize();
}

//=============================================================================
// デストラクタ
//=============================================================================
CAttitudeController::~CAttitudeController(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CAttitudeController::Init(void)
{
	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CAttitudeController::Uninit(void)
{
}

//=============================================================================
// 更新
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

	// 前方ベクトルを求める
	front_vector_ = basic_vector_.RotationAxis(axis_,rotation_);
	front_vector_.Normalize();
}

//---------------------------------- EOF --------------------------------------
