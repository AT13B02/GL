//=============================================================================
//
// �E�B���h�E�}�l�[�W���N���X [CWindowManager.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CWindowManager.h"
#include "CWindow.h"
#include <fstream>
#include "Debug.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWindowManager::CWindowManager()
	:	m_uNumWindow(0),
		m_ppWindow(0)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWindowManager::~CWindowManager()
{
}

//=============================================================================
// ����
//=============================================================================
bool CWindowManager::Create(CWindowManager** ppManager)
{
	(*ppManager) = new CWindowManager();

	if(nullptr == (*ppManager))
	{
		_Assert((*ppManager));
		return false;
	}

	return true;
}

//=============================================================================
// �J��
//=============================================================================
void CWindowManager::Release()
{
	for(int i = 0; i < m_uNumWindow; i++)
	{
		m_ppWindow[i]->Release();
		m_ppWindow[i] = nullptr;
	}
	
	delete[] m_ppWindow;
	m_ppWindow = nullptr;
	m_uNumWindow = 0;

	delete this;
}

//=============================================================================
// �E�B���h�E��ǉ�
//=============================================================================
const int CWindowManager::Add(const char* pFileName)
{
	// �V�����E�B���h�E�z������
	CWindow** ppNewWindow = new CWindow*[m_uNumWindow + 1];
	
	if(nullptr != m_ppWindow)
	{
		for(int i = 0; i < m_uNumWindow; i++)
		{
			ppNewWindow[i] = m_ppWindow[i];
		}

		delete[] m_ppWindow;
		m_ppWindow = nullptr;
	}

	m_ppWindow = ppNewWindow;
	m_uNumWindow = m_uNumWindow + 1;

	// �E�B���h�E����
	return CreateNewWindow(pFileName);
}

//=============================================================================
// �V�����E�B���h�E�̐���
// Author : Ryo Kobayashi
// Last Update : 2014/6/8
//=============================================================================
const int CWindowManager::Add(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight)
{
	// �V�����E�B���h�E�z������
	CWindow** ppNewWindow = new CWindow*[m_uNumWindow + 1];
	
	if(nullptr != m_ppWindow)
	{
		for(int i = 0; i < m_uNumWindow; i++)
		{
			ppNewWindow[i] = m_ppWindow[i];
		}

		delete[] m_ppWindow;
		m_ppWindow = nullptr;
	}

	m_ppWindow = ppNewWindow;
	m_uNumWindow = m_uNumWindow + 1;

	// �E�B���h�E����
	return CreateNewWindow(pCaption, pClassName, uWidth, uHeight);
}

//=============================================================================
// ���b�Z�[�W����
//=============================================================================
CWindow::Message CWindowManager::ProcMessage(const unsigned uIndex, MSG& msg)
{
	return m_ppWindow[uIndex]->ProcMessage(msg);
}

//=============================================================================
// �E�B���h�E�n���h���擾
//=============================================================================
const HWND& CWindowManager::GetWindowHandle(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->GetWindowHandle();
}

//=============================================================================
// �E�B���h�E�����擾
//=============================================================================
const DWORD& CWindowManager::GetWindowWidth(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->GetWindowWidth();
}

//=============================================================================
// �E�B���h�E�c���擾
//=============================================================================
const DWORD& CWindowManager::GetWindowHeight(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->GetWindowHeight();
}

//=============================================================================
// �L���v�V�����ݒ�
//=============================================================================
void CWindowManager::SetCaption(const unsigned uIndex,const char* pCaption)
{
	return m_ppWindow[uIndex]->SetCaption(pCaption);
}

//=============================================================================
// �E�B���h�E�\��
//=============================================================================
void CWindowManager::ShowWindow(const unsigned uIndex)
{
	return m_ppWindow[uIndex]->ShowWindow();
}

//=============================================================================
// �E�B���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK CWindowManager::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// ���b�Z�[�W�ɂ���ĕ���
	switch(uMsg)
	{
		// �E�B���h�E�j��
	case WM_DESTROY:
		// �I�����b�Z�[�W���o
		PostQuitMessage(0);
		break;

		// �L�[����
	case WM_KEYDOWN:
		// �L�[���͏���
		KeyInputProc(hWnd, wParam);
		break;
		
		// �E�B���h�E�T�C�Y�ύX��
	case WM_SIZE:
		break;
		
	default:
		break;
	}

	// �W�������ɓ�����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//=============================================================================
// �V�����E�B���h�E�̐���
// Author : Ryo Kobayashi
// Last Update : 2014/6/8
//=============================================================================
const int CWindowManager::CreateNewWindow(const char* pFileName)
{
	int nNewWindowIndex = (int)m_uNumWindow - 1;

	unsigned uWindowWidth = 800;
	unsigned uWindowHeight = 600;
	char aCaption[256] = "WINDOW";
	char aClassName[256] = "WINDOW_CLASS";

	std::ifstream ifs(pFileName);

	if(ifs.is_open())
	{
		ifs >> uWindowWidth;
		ifs.ignore(10, '\n');
		ifs >> uWindowHeight;
		ifs.ignore(10, '\n');
		ifs >> aCaption;
		ifs.ignore(10, '\n');
		ifs >> aClassName;
		ifs.ignore(10, '\n');
	}

	// ����
	if(FAILED(CWindow::Create(uWindowWidth, uWindowHeight, aCaption, aClassName, WndProc, &m_ppWindow[nNewWindowIndex])))
	{
		return -1;
	}

	return m_uNumWindow;
}

//=============================================================================
// �V�����E�B���h�E����
// Author : Ryo Kobayashi
// Last Update : 2014/12/15
//=============================================================================
const int CWindowManager::CreateNewWindow(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight)
{
	int nNewWindowIndex = (int)m_uNumWindow - 1;

	if(!pCaption)
	{
		pCaption = "WINDOW";
	}
	if(!pClassName)
	{
		pClassName = "WINDOW_CLASS";
	}

	// ����
	if(FAILED(CWindow::Create(uWidth, uHeight, pCaption, pClassName, WndProc, &m_ppWindow[nNewWindowIndex])))
	{
		return -1;
	}

	return m_uNumWindow;
}

//=============================================================================
// �L�[���͏���
// Author : Ryo Kobayashi
// Last Update : 2014/6/8
//=============================================================================
void CWindowManager::KeyInputProc(HWND hWnd, WPARAM wParam)
{
	switch(wParam)
	{
		// �G�X�P�[�v�������ꂽ�Ƃ�
	case VK_ESCAPE:
		if(IDYES == MessageBox(NULL, "�I�����܂����H", "", MB_YESNO))
		{
			DestroyWindow(hWnd);	// �e�E�B���h�E�̃n���h�����擾
		}
		break;
	}
}

// EOF