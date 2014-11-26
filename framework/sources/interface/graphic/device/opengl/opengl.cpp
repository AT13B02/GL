//*****************************************************************************
//
// OpenGL�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "interface/graphic/device/opengl/opengl.h"

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
COpengl::COpengl(WINDOW_DATA* window_data) : CGraphicDevice(window_data)
{
	int format;

	// �s�N�Z���t�H�[�}�b�g������
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, //Number of bits for the depthbuffer
		8, //Number of bits for the stencilbuffer
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	for(u8 i = 0;i < CONTEXT_MAX;++i)
	{
		// �f�o�C�X�R���e�L�X�g�̎擾
		gl_context_[i]._hdc = GetDC(window_data_->_hwnd);

		// �s�N�Z���t�H�[�}�b�g�̑I��
		format = ChoosePixelFormat(gl_context_[i]._hdc, &pfd);

		// OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
		SetPixelFormat(gl_context_[i]._hdc,format,&pfd);

		// OpenGL context���쐬
		gl_context_[i]._hglrc = wglCreateContext(gl_context_[i]._hdc);
	}

	draw_mode_ = DEVICE_MODE_LOAD;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
COpengl::~COpengl(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool COpengl::Init(void)
{
	return true;
}

//=============================================================================
// �I��
//=============================================================================
void COpengl::Uninit(void)
{
	// �J�����g�R���e�L�X�g�𖳌��ɂ���
	wglMakeCurrent(NULL,NULL);

	for(u8 i = 0;i < CONTEXT_MAX;i++)
	{
		// OpenGL�̃R���e�L�X�g
		wglDeleteContext(gl_context_[i]._hglrc);

		// �f�o�C�X�R���e�L�X�g���
		ReleaseDC(window_data_->_hwnd,gl_context_[i]._hdc);
	}
}

//=============================================================================
// �`��J�n
//=============================================================================
void COpengl::BeginDraw(void)
{
	// �J�����g�R���e�L�X�g�̑I��
	if(wglMakeCurrent(gl_context_[0]._hdc,gl_context_[draw_mode_]._hglrc) == FALSE)
	{
		int a = 0;
	}

	// �o�b�t�@�̃N���A����F��ݒ�
	glClearColor(0.8f,0.8f,1.0f,0.8f);

	// �N���A������̂�I��
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//=============================================================================
// �`��I��
//=============================================================================
void COpengl::EndDraw(void)
{
	wglMakeCurrent(NULL,NULL);

	// �o�b�t�@�ɏ���
	glFlush();

	// �o�b�t�@�̓���ւ�
	SwapBuffers(gl_context_[0]._hdc);
}

//=============================================================================
// ���[�h�J�n
//=============================================================================
void COpengl::BeginLoad(void)
{
	// �J�����g�R���e�L�X�g�̑I��
	while((wglMakeCurrent(gl_context_[1]._hdc,gl_context_[load_mode_]._hglrc) == FALSE));
}

//=============================================================================
// ���[�h�I��
//=============================================================================
void COpengl::EndLoad(void)
{
	if(wglMakeCurrent(NULL,NULL) == FALSE)
	{
		int a = 0;
	}
}

//=============================================================================
// �X�N���[���V���b�g
//=============================================================================
void COpengl::ScreenShot(const s8* filename)
{
}

//=============================================================================
// �`�惂�[�h�̐ݒ�
//=============================================================================
void COpengl::SetDrawMode(const DEVICE_MODE& device_mode)
{
	CGraphicDevice::SetDrawMode(device_mode);

	if(wglMakeCurrent(NULL,NULL) == FALSE)
	{
		//MessageBox(NULL,"���[�h���s���邩����","�G���[",MB_OK);
	}
}

//=============================================================================
// ���[�h���[�h�̐ݒ�
//=============================================================================
void COpengl::SetLoadMode(const DEVICE_MODE& device_mode)
{
	CGraphicDevice::SetLoadMode(device_mode);

	wglMakeCurrent(NULL,NULL);
}

//---------------------------------- EOF --------------------------------------