//=============================================================================
//
// �����_�����O�N���X [CRenderer.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/8
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CRenderer.h"
#include "Debug.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
	:	m_hWnd(0),
		m_hdc(0),
		m_glRC(0),
		m_uBackBufferWidth(0),
		m_uBackBufferHeight(0),
		m_Clear_Red(0.1f),
		m_Clear_Green(0.1f),
		m_Clear_Blue(0.1f)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// ��������
//=============================================================================
HRESULT CRenderer::Create(HWND hWnd, BOOL bWindow, unsigned uBackBufferWidth, unsigned uBackBufferHeight, CRenderer** ppRender)
{
	(*ppRender) = new CRenderer();
	_Assert((*ppRender));

	return (*ppRender)->Init(hWnd, bWindow, uBackBufferWidth, uBackBufferHeight);
}

//=============================================================================
// ������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow, unsigned uBackBufferWidth, unsigned uBackBufferHeight)
{
	// �s�N�Z���t�H�[�}�b�g������
	// pixel format descriptor
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | // �E�B���h�E�ɏ���
		PFD_SUPPORT_OPENGL | // OpenGL
		PFD_DOUBLEBUFFER,	// �_�u���o�b�t�@
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, // �[�x�o�b�t�@�r�b�g��
		8, // �X�e���V���o�b�t�@�r�b�g��
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	// �搶�����������
	/*
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | // �E�B���h�E�ɏ���
		PFD_SUPPORT_OPENGL | // OpenGL
		PFD_DOUBLEBUFFER,	// �_�u���o�b�t�@
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		24, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32, // �[�x�o�b�t�@�r�b�g��
		0, // �X�e���V���o�b�t�@�r�b�g��
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	*/

	// �o�b�N�o�b�t�@�T�C�Y�ݒ�
	m_uBackBufferWidth = uBackBufferWidth;
	m_uBackBufferHeight = uBackBufferHeight;

	// �f�o�C�X�R���e�L�X�g�擾
	m_hdc = GetDC(hWnd);
	int format = ChoosePixelFormat(m_hdc, &pfd);
	if (format == 0)
	{
		return E_FAIL; // �Y������s�N�Z���t�H�[�}�b�g������
	}

	// OpenGL���g���f�o�C�X�R���e�L�X�g�Ɏw��̃s�N�Z���t�H�[�}�b�g���Z�b�g
	if (!SetPixelFormat(m_hdc, format, &pfd))
	{
		return E_FAIL; // DC�փt�H�[�}�b�g��ݒ肷��̂Ɏ��s
	}

	// OpenGL�p��context���쐬
	m_glRC = wglCreateContext(m_hdc);

	// �쐬���ꂽ�R���e�L�X�g���J�����g�i���ݎg�p���̃R���e�L�X�g�j���H
	if (!wglMakeCurrent(m_hdc, m_glRC))	// �R���e�L�X�g�̐؂�ւ����ł���
	{
		return E_FAIL;
	}

	// �E�B���h�E�n���h���ݒ�
	m_hWnd = hWnd;
	
	// OpenGLExt������
	if(!InitOpenGLExt())
	{
		_AssertExpr(0, "OpenGLExt�̏������Ɏ��s");
		return E_FAIL;
	}
	
	// ���ʂ��J�����O
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// �[�x�e�X�g�L����
	glEnable(GL_DEPTH_TEST);
	// ���C�e�B���O�L����
	glEnable(GL_LIGHTING);
	// �A���t�@�e�X�g�L����
	glEnable(GL_ALPHA_TEST);
	// �u�����h�L����
	glEnable(GL_BLEND);
	// �A���t�@�����ݒ�
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// ���Z����
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	// ��Z����(�|���S���̐F�Ɗ|�����킹)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	return S_OK;
}

//=============================================================================
// �J��
//=============================================================================
void CRenderer::Release(void)
{
	// �J�����g�R���e�L�X�g(�����_�����O�R���e�L�X�g�H)�𖳌��ɂ���
	wglMakeCurrent(NULL, NULL);

	// �J�����g�R���e�L�X�g���폜
	wglDeleteContext(m_glRC);

	// �f�o�C�X�R���e�L�X�g���
	ReleaseDC(m_hWnd, m_hdc);

	delete this;
}

//=============================================================================
// �`��J�n
//=============================================================================
void CRenderer::BeginDraw()
{
	// �`���ݒ�
	BOOL res = wglMakeCurrent(m_hdc, m_glRC);

	// ��ʂ̃N���A
	// (�o�b�N�o�b�t�@, �[�x�o�b�t�@)
	glClearColor(m_Clear_Red, m_Clear_Green, m_Clear_Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//=============================================================================
// �`��I��
//=============================================================================
void CRenderer::EndDraw()
{
	// �N���C�A���g�A�T�[�o�[�Ԃ̃R�}���h�������s
	// �X�^���h�A�����ł͂��܂�Ӗ��͖���
	glFlush();

	// �o�b�t�@����
	SwapBuffers(m_hdc);
}

// EOF