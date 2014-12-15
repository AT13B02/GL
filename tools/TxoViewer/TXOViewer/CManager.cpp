//=============================================================================
//
// �}�l�[�W�� [CManager.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CManager.h"
#include "CApplication.h"
#include "CRenderer.h"
#include "CWindowManager.h"

#include "CRect2D.h"
#include "CTextureGL.h"
#include "CCamera.h"

#include "kbMath.h"
#include "Debug.h"

//=============================================================================
// �R���X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/15
//=============================================================================
CManager::CManager()
	: m_pApplication(nullptr),
	m_pRenderer(nullptr),
	m_pWindowManager(nullptr),
	m_pTexture(nullptr)
{
}

//=============================================================================
// �}�l�[�W���쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
HRESULT CManager::Create(HINSTANCE hInstance, CApplication* pApplication, CManager** ppManager)
{
	// �}�l�[�W������
	(*ppManager) = new CManager();

	HRESULT hr = (*ppManager)->Init(hInstance, pApplication);

	return hr;
}

//=============================================================================
// �}�l�[�W���쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Release(void)
{
	Uninit();

	delete this;
}

//=============================================================================
// ������
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, CApplication* pApplication)
{
	// �A�v���P�[�V�����N���X�ݒ�
	_AssertExpr(pApplication, "�A�v���P�[�V��������������Ă��Ȃ�");
	m_pApplication = pApplication;

	// �����_���ݒ�
	m_pRenderer = m_pApplication->GetRenderer();
	// �E�B���h�E�}�l�[�W���ݒ�
	m_pWindowManager = m_pApplication->GetWindowManager();

	// �e�N�X�`���擾
	if('\0' == (pApplication->GetArgument())[0])
	{
		MessageBox(NULL, "�e�N�X�`���t�@�C�����w�肳��Ă��܂���", "", MB_OK);
		return E_FAIL;
	}
	CTextureGL::LoadFromFile(pApplication->GetArgument(), &m_pTexture);
	
	return S_OK;
}

//=============================================================================
// �J��
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Uninit(void)
{
	// �e�N�X�`���J��
	SafeRelease(m_pTexture);
}

//=============================================================================
// �X�V
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Update(void)
{
}

//=============================================================================
// �`��
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Draw(void)
{
	// �J�����ݒ�
	CCamera camera;
	camera.left(0);
	camera.right(m_pRenderer->GetBackBufferWidth());
	camera.top(0);
	camera.bottom(m_pRenderer->GetBackBufferHeight());
	camera.Setup();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glMultMatrixf((GLfloat*)&camera.GetOrtho());
	glOrtho(0, m_pRenderer->GetBackBufferWidth(), m_pRenderer->GetBackBufferHeight(), 0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(0, 0, m_pRenderer->GetBackBufferWidth(), m_pRenderer->GetBackBufferHeight());

	// �`��J�n
	m_pRenderer->BeginDraw();
	
	// ���C�e�B���O�I�t
	glDisable(GL_LIGHTING);

	// �e�N�X�`���K�p
	m_pTexture->SetTex2D();
	float left = 0;
	float top = 0;
	float right		= (float)m_pRenderer->GetBackBufferWidth();
	float bottom	= (float)m_pRenderer->GetBackBufferHeight();
	float fTexS = 0.0f;
	float fTexT = 0.0f;
	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f);
	VERTEX_2D aVtx[] =
	{
		{
			Vector3(right, top, 0.0f),
			color,
			Vector2(fTexS + 1.0f, fTexT)
		},
		{
			Vector3(left, top, 0.0f),
			color,
			Vector2(fTexS, fTexT)
		},
		{
			Vector3(right, bottom, 0.0f),
			color,
			Vector2(fTexS + 1.0f, fTexT + 1.0f)
		},
		{
			Vector3(left, bottom, 0.0f),
			color,
			Vector2(fTexS, fTexT + 1.0f)
		},
	};
	// �e�N�X�`���I��
	glEnable(GL_TEXTURE_2D);
	// �`��
	CRect2D::DrawPrimitive(GL_TRIANGLE_STRIP, (void*)aVtx, 4);
	// �e�N�X�`��������
	glDisable(GL_TEXTURE_2D);
	
	// ���C�e�B���O�I��
	glEnable(GL_LIGHTING);
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// �`��I��
	m_pRenderer->EndDraw();
}

// EOF