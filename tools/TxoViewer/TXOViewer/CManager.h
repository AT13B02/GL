//=============================================================================
//
// �}�l�[�W�� [CManager.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//
//=============================================================================
#pragma once
#ifndef __KBR_MANAGER_H__
#define __KBR_MANAGER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>

// �O���Q��
class CApplication;
class CRenderer;
class CWindowManager;
class CTextureGL;

//*****************************************************************************
// �}�l�[�W���N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/9
//*****************************************************************************
class CManager
{
public:

	CManager();

	~CManager(){}

	// �}�l�[�W���쐬
	static HRESULT Create(HINSTANCE hInstance, CApplication* pApplication, CManager** ppManager);

	// �J��
	void Release(void);

	// ������
	HRESULT Init(HINSTANCE hInstance,
				CApplication* pApplication);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

private:
	
	// �J��
	void Uninit(void);

	// �C���[�W�o��
	void DrawRenderedImage();

private:

	// �A�v���P�[�V����
	CApplication* m_pApplication;

	// �����_��
	CRenderer* m_pRenderer;

	// �E�B���h�E�}�l�[�W��
	CWindowManager* m_pWindowManager;
	
	// �O���[�o���ϐ�
	CTextureGL *m_pTexture;

};

#endif	// __KBR_MANAGER_H__

// EOF