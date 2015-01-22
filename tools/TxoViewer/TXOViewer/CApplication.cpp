//=============================================================================
//
// �A�v���P�[�V�����N���X [CApplication.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CApplication.h"
#include "CWindowManager.h"
#include "CRenderer.h"
#include "CManager.h"
#include "CHardwareTimer.h"
#include "Debug.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CApplication::CApplication()
	:	m_pWindowManager(nullptr),
	m_pRenderer(nullptr),
	m_pManager(nullptr),
	m_pArg(nullptr)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CApplication::~CApplication()
{
}

//=============================================================================
// �A�v���P�[�V�����X�^�[�g
//=============================================================================
int CApplication::Run(const char* pArg)
{
	CApplication* pApp;
	bool bFlase = false;
	bFlase = Create(pArg, &pApp);
	if(nullptr == pApp)
	{
		return -1;
	}
	else if(false == bFlase)
	{
		pApp->Release();
		return -1;
	}
	
	MSG Msg;					// ���b�Z�[�W�\����
	Msg.message = WM_NULL;		// �k���N���A

	CWindow* pWindow = pApp->m_pWindowManager->GetWindow(0);

	// �E�B���h�E�\��
	pWindow->ShowWindow();
	
	// �^�C�}�[
	CHardwareTimer timer;
	timer.SetupTimer();

	bool bLoopFlag = true;
	while(bLoopFlag)
	{
		// �I��
		if(CWindow::MESSAGE_TERMINATE == pWindow->ProcMessage(Msg))
		{
			bLoopFlag = false;
		}
		// �X�V
		else if(timer.Update())
		{
#ifdef _DEBUG
			char aCap[256];

			sprintf_s(aCap, 255, "%f", timer.GetFPS());

			// �E�B���h�E�̃L���v�V������FPS
			pWindow->SetCaption(aCap);
#endif
			pApp->Update();
		}
	}

	// �A�v���P�[�V�����J��
	pApp->Release();
	
	// �^�C�}�[�I��
	timer.EndTimer();

	// ���b�Z�[�W��Ԃ�
	return (int)Msg.wParam;
}

//=============================================================================
// ����
//=============================================================================
bool CApplication::Create(const char* pArg, CApplication** ppApplication)
{
	(*ppApplication) = new CApplication();
	
	if(nullptr == (*ppApplication))
	{
		_AssertExpr(0, "�A�v���P�[�V�����̐����Ɏ��s");
		return false;
	}

	return (*ppApplication)->Initialize(pArg);
}

//=============================================================================
// ������
//=============================================================================
bool CApplication::Initialize(const char* pArg)
{
	m_pArg = pArg;

	if(false == CWindowManager::Create(&m_pWindowManager))
	{
		return false;
	}
	m_pWindowManager->Add("TxoViewer", "kbr_txo_viewer", 512, 512);

	// �����_������
	if(FAILED(CRenderer::Create(
		m_pWindowManager->GetWindowHandle(0),
		FALSE,
		m_pWindowManager->GetWindowWidth(0),
		m_pWindowManager->GetWindowHeight(0),
		&m_pRenderer)))
	{
		return false;
	}

	// �}�l�[�W������
	if(FAILED(CManager::Create(
		GetModuleHandle(NULL),
		this,
		&m_pManager)))
	{
		return false;
	}

	return true;
}

//=============================================================================
// �J��
//=============================================================================
void CApplication::Release()
{
	m_pManager->Release();
	m_pRenderer->Release();
	m_pWindowManager->Release();

	delete this;
}

//=============================================================================
// �X�V
//=============================================================================
void CApplication::Update()
{
	// �}�l�[�W���[�X�V
	m_pManager->Update();
	// �}�l�[�W���[�`��
	m_pManager->Draw();
}

// EOF