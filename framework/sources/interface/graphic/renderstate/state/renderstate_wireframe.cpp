//*****************************************************************************
//
// �����_�[�X�e�[�g���C���[�t���[���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/application.h"

#include "interface/graphic/renderstate/state/renderstate_wireframe.h"
#ifdef _USING_OPENGL_
#include "interface/graphic/renderstate/state/opengl/gl_renderstate_wireframe.h"
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
CRenderstateWireframe::CRenderstateWireframe(CDeviceHolder* device_holder) : CRenderstate(device_holder)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderstateWireframe::~CRenderstateWireframe(void)
{
}

//=============================================================================
// �쐬����
//=============================================================================
CRenderstateWireframe* CRenderstateWireframe::Create(CDeviceHolder* device_holder)
{
	CRenderstateWireframe* renderstate_wireframe = NULL;

#ifdef _USING_OPENGL_
	renderstate_wireframe = new CGLRenderstateWireframe(device_holder);
#endif

#ifdef _USING_DIRECTX_
	renderstate_2d = new CGLRenderstateWireframe(device_holder);
#endif

	return renderstate_wireframe;
}

//---------------------------------- EOF --------------------------------------
