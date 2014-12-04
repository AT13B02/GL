//*****************************************************************************
//
// �����_�[�X�e�[�g���C�g�I�t�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/application.h"

#include "interface/graphic/renderstate/state/renderstate_light_off.h"
#ifdef _USING_OPENGL_
#include "interface/graphic/renderstate/state/opengl/gl_renderstate_light_off.h"
#endif

#ifdef _USING_DIRECTX_
#include "interface/graphic/renderstate/state/directx/dx_renderstate_2d.h"
#endif

// common
#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
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
CRenderstateLightOff::CRenderstateLightOff(CDeviceHolder* device_holder) : CRenderstate(device_holder)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderstateLightOff::~CRenderstateLightOff(void)
{
}

//=============================================================================
// �쐬����
//=============================================================================
CRenderstateLightOff* CRenderstateLightOff::Create(CDeviceHolder* device_holder)
{
	CRenderstateLightOff* renderstate_light_off = NULL;

#ifdef _USING_OPENGL_
	renderstate_light_off = new CGLRenderstateLightOff(device_holder);
#endif

#ifdef _USING_DIRECTX_
	renderstate_2d = new CGLRenderstateLightOff(device_holder);
#endif

	return renderstate_light_off;
}

//---------------------------------- EOF --------------------------------------
