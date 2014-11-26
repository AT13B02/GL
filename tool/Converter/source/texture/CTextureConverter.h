//=============================================================================
//
// �e�N�X�`���ϊ��N���X [CTextureConverter.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//
//=============================================================================
#pragma once
#ifndef __KBR_TEXTURE_GL_H__
#define __KBR_TEXTURE_GL_H__

#include <Windows.h>

//*****************************************************************************
// �e�N�X�`���ϊ��N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//*****************************************************************************
class CTextureConverter
{
public:

	CTextureConverter();

	~CTextureConverter();
	
	// �e�N�X�`���ϊ�
	BOOL Convert(const char* pFileName);

private:
	
	// �e�N�X�`�����[�h
	BOOL LoadFromFile(const char* pFileName);

private:

	// �e�N�X�`���o�b�t�@
	unsigned char* m_pBuffer;

	// �e�N�X�`������
	unsigned short m_uWidth;
	// �e�N�X�`���c��
	unsigned short m_uHeight;
};

#endif	// __KBR_TEXTURE_GL_H__

// EOF