//=============================================================================
//
// �A�v���P�[�V�����N���X [CApplication.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/5
//
//=============================================================================
#pragma once
#ifndef __KBR_CAPPLICATION_H__
#define __KBR_CAPPLICATION_H__

// �O���Q��
class CWindowManager;
class CRenderer;
class CManager;

//*****************************************************************************
// �A�v���P�[�V�����N���X
// Author : Ryo Kobayashi
//*****************************************************************************
class CApplication
{
public:

	CApplication();

	~CApplication();

	// �A�v���P�[�V�����X�^�[�g
	static int Run(const char* pArg);

	// �E�B���h�E�}�l�[�W���擾
	CWindowManager* GetWindowManager(){ return m_pWindowManager; }

	// �����_���擾
	CRenderer* GetRenderer(){ return m_pRenderer; }

	// �}�l�[�W���擾
	CManager* GetManager(){ return m_pManager; }

	// �A�v���P�[�V���������擾
	const char* GetArgument(){ return m_pArg; }

private:

	// ����
	static bool Create(const char* pArg, CApplication** ppApplication);

	// ������
	bool Initialize(const char* pArg);

	// �J��
	void Release();

	// �X�V
	void Update();

private:

	// �E�B���h�E
	CWindowManager* m_pWindowManager;

	// �����_��
	CRenderer* m_pRenderer;

	// �}�l�[�W��
	CManager* m_pManager;

	// ����
	const char* m_pArg;
};

#endif	// __KBR_CAPPLICATION_H__

// EOF