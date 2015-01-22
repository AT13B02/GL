//=============================================================================
//
// �����_�����O�N���X [CRenderer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/18
//
//=============================================================================
#pragma once
#ifndef __KBR_RENDERER_GL_H__
#define __KBR_RENDERER_GL_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include "OpenGL.h"
#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ErrorMessage(msg) MessageBox(NULL, msg, "ERROR", MB_OK | MB_ICONSTOP | MB_TASKMODAL);

//*****************************************************************************
// �O���Q��
//*****************************************************************************
class CRenderTexture;

//*****************************************************************************
// �����_�����O�N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/8
//*****************************************************************************
class CRenderer
{
public:

	CRenderer();

	~CRenderer();

	// ��������
	static HRESULT Create(
		HWND hWnd, 
		BOOL bWindow, 
		unsigned uBackBufferWidth, 
		unsigned uBackBufferHeight, 
		CRenderer** ppRender);

	// �J��
	void Release();

	// �`��J�n
	void BeginDraw();
	// �`��I��
	void EndDraw();

	// �o�b�N�o�b�t�@�T�C�Y�擾
	const unsigned& GetBackBufferWidth(){ return m_uBackBufferWidth; }
	const unsigned& GetBackBufferHeight(){ return m_uBackBufferHeight; }

private:

	// ������
	HRESULT Init(HWND hWnd, BOOL bWindow, unsigned uBackBufferWidth, unsigned uBackBufferHeight);

private:
	
	// �E�B���h�E�n���h��
	HWND		m_hWnd;
	// �f�o�C�X�R���e�L�X�g
	HDC			m_hdc;
	// OpenGL�R���e�L�X�g
	HGLRC		m_glRC;

	// �o�b�N�o�b�t�@����
	unsigned m_uBackBufferWidth;
	// �o�b�N�o�b�t�@�c��
	unsigned m_uBackBufferHeight;

	// �N���A�J���[
	float m_Clear_Red;
	float m_Clear_Green;
	float m_Clear_Blue;
};

#endif	// __KBR_RENDERER_GL_H__

// EOF