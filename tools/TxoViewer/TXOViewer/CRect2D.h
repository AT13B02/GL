//=============================================================================
//
// �����ɕ`����2D�|���S���N���X [CRect2D.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/4
//
//=============================================================================
#pragma once
#ifndef __KBR_CRECT_2D_H__
#define __KBR_CRECT_2D_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "OpenGL.h"
#include "kbMath.h"

// 2D�p���_
struct VERTEX_2D
{
	Vector3 pos;
	Vector4 color;
	Vector2 tex;
};

//*****************************************************************************
// �����ɕ`����2D�|���S���N���X
// Author : Ryo Kobayashi
//*****************************************************************************
class CRect2D
{
public:

	// 2D�`��
	static void DrawPrimitive(GLenum drawType, void* pBuffer, unsigned nNumVertex);
};

#endif	// __KBR_CRECT_2D_H__

// EOF