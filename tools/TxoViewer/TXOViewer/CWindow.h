//=============================================================================
//
// �E�B���h�E�N���X [CWindow.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/2
//
//=============================================================================
#pragma once
#ifndef __KBR_CWINDOW_H__
#define __KBR_CWINDOW_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <string>

//*****************************************************************************
// �E�B���h�E�N���X
// Author : Ryo Kobayashi
//*****************************************************************************
class CWindow
{
public:

	enum Message
	{
		MESSAGE_OK,			// ���b�Z�[�W���������ꂽ
		MESSAGE_TERMINATE	// �I�����b�Z�[�W������
	};

	CWindow();

	~CWindow();

	// ��������
	static HRESULT Create(DWORD uWidth, DWORD uHeight, const char* pCaption, const char* pClassName, WNDPROC pWndProc, CWindow** ppWindow);

	// �J��
	void Release();

	// ���b�Z�[�W����
	Message ProcMessage(MSG& msg);

	// �E�B���h�E�n���h���擾
	const HWND& GetWindowHandle();

	// �E�B���h�E�����擾
	const DWORD& GetWindowWidth();

	// �E�B���h�E�c���擾
	const DWORD& GetWindowHeight();

	// �L���v�V�����ݒ�
	void SetCaption(const char* pCaption);

	// �E�B���h�E�\��
	void ShowWindow();

private:

	// ������������
	HRESULT Create(DWORD uWidth, DWORD uHeight, const char* pCaption, const char* pClassName, WNDPROC pWndProc);

private:

	// �E�B���h�E�n���h��
	HWND m_hWnd;

	// �E�B���h�E����
	DWORD m_uWindowWidth;
	// �E�B���h�E�c��
	DWORD m_uWindowHeight;

	// �E�B���h�E�N���X��
	std::string m_strClassName;

	// �E�B���h�E�L���v�V����
	std::string m_strCaption;
	
	// �E�B���h�E�X�^�C��
	static const int GAME_WINDOW;
};

#endif	// __KBR_CWINDOW_H__

// EOF