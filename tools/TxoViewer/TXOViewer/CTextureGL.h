//=============================================================================
//
// �e�N�X�`���N���X [CTextureGL.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================
#pragma once
#ifndef __KBR_TEXTURE_GL_H__
#define __KBR_TEXTURE_GL_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "OpenGL.h"

//*****************************************************************************
// �e�N�X�`���N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//*****************************************************************************
class CTextureGL
{
public:

	CTextureGL();

	~CTextureGL();
	
	// �e�N�X�`�����[�h
	static BOOL LoadFromFile(const char* pFileName, CTextureGL** ppTexture);

	// �e�N�X�`���o�b�t�@�ւ̃|�C���^���擾
	unsigned char* GetBufferPointer(void);

	// �e�N�X�`���J��
	void Release(void);

	// �e�N�X�`���ݒ�
	void SetTex2D(void);

private:
	
	// �e�N�X�`�����[�h
	BOOL LoadFromFile(const char* pFileName);

private:

	// �e�N�X�`�����ʔԍ�
	unsigned int m_uIndex;
	// �e�N�X�`���o�b�t�@
	unsigned char* m_pTex;

	// �e�N�X�`������
	unsigned short m_uWidth;
	// �e�N�X�`���c��
	unsigned short m_uHeight;
};

typedef CTextureGL* LPCTEXTUREGL;

#endif	// __KBR_TEXTURE_GL_H__

// EOF