//=============================================================================
//
// �E�B���h�E�}�l�[�W���N���X [CWindowManager.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================
#pragma once
#ifndef __KBR_CWINDOW_MANAGER_H__
#define __KBR_CWINDOW_MANAGER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CWindow.h"

//*****************************************************************************
// �E�B���h�E�}�l�[�W���N���X
// Author : Ryo Kobayashi
//*****************************************************************************
class CWindowManager
{
public:

	CWindowManager();

	~CWindowManager();

	// ����
	static bool Create(CWindowManager** ppManager);
	
	// �J��
	void Release();

	// �E�B���h�E��ǉ�
	// �ǉ�������ID��Ԃ�
	const int Add(const char* pFileName);
	const int Add(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight);

	// �E�B���h�E�擾
	CWindow* GetWindow(const unsigned uIndex){ return m_ppWindow[uIndex]; }
	
	// ���b�Z�[�W����
	CWindow::Message ProcMessage(const unsigned uIndex, MSG& msg);

	// �E�B���h�E�n���h���擾
	const HWND& GetWindowHandle(const unsigned uIndex);

	// �E�B���h�E�����擾
	const DWORD& GetWindowWidth(const unsigned uIndex);

	// �E�B���h�E�c���擾
	const DWORD& GetWindowHeight(const unsigned uIndex);

	// �L���v�V�����ݒ�
	void SetCaption(const unsigned uIndex,const char* pCaption);

	// �E�B���h�E�\��
	void ShowWindow(const unsigned uIndex);
	
	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:

	// �V�����E�B���h�E�̐���
	const int CreateNewWindow(const char* pFileName);
	const int CreateNewWindow(const char* pCaption, const char* pClassName, const unsigned uWidth, const unsigned uHeight);
	
	// �L�[����
	static void KeyInputProc(HWND hWnd, WPARAM wParam);

private:

	unsigned m_uNumWindow;
	CWindow** m_ppWindow;
};

#endif	// __KBR_CWINDOW_MANAGER_H__

// EOF