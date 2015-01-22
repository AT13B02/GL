//=============================================================================
//
// �e�N�X�`�����[�h���� [TextureLoader.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================
#pragma once
#ifndef __KBR_TEXTURE_LOADER_H__
#define __KBR_TEXTURE_LOADER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>

//*****************************************************************************
// �v���g�^�C�v�֐�
//*****************************************************************************
// �e�N�X�`�����[�h����
BOOL LoadTexture(const char* pTexName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// ���[�h�����e�N�X�`���̊J��
void DeleteTexture(unsigned char** ppTex);

#endif	// __KBR_TEXTURE_LOADER_H__

// EOF