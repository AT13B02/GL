//*****************************************************************************
//
// �����_�[�X�e�[�g�}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/renderstate/renderstate_manager.h"
#include "interface/graphic/renderstate/state/renderstate_2d.h"
#include "interface/graphic/renderstate/state/renderstate_3d.h"
#include "interface/graphic/renderstate/state/renderstate_all.h"
#include "interface/graphic/renderstate/state/renderstate_light_off.h"
#include "interface/graphic/renderstate/state/renderstate_wireframe.h"

// common
#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderstateManager::CRenderstateManager(CDeviceHolder* device_holder)
{
	device_holder_ = device_holder;

	for(int i = 0;i < TYPE_MAX;i++)
	{
		renderstate_[i] = NULL;
	}

	renderstate_[TYPE_ALL] = CRenderstateAll::Create(device_holder);
	renderstate_[TYPE_2D] = CRenderstate2D::Create(device_holder);
	renderstate_[TYPE_3D] = CRenderstate3D::Create(device_holder);
	renderstate_[TYPE_LIGHT_OFF] = CRenderstateLightOff::Create(device_holder);
	renderstate_[TYPE_WIREFRAME] = CRenderstateWireframe::Create(device_holder);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderstateManager::~CRenderstateManager(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CRenderstateManager::Init(void)
{
	return true;
}

//=============================================================================
// �I��
//=============================================================================
void CRenderstateManager::Uninit(void)
{
	for(int i = 0;i < TYPE_MAX;i++)
	{
		SAFE_RELEASE(renderstate_[i]);
	}
}

//=============================================================================
// �����_�[�X�e�[�g�̎擾
//=============================================================================
CRenderstate* CRenderstateManager::renderstate(const TYPE& type)
{
	CRenderstate* renderstate = NULL;

	if((type < TYPE_MAX) && (type >= 0))
	{
		renderstate = renderstate_[type];
	}

	return renderstate;
}

//-----------------------------------EOF---------------------------------------
