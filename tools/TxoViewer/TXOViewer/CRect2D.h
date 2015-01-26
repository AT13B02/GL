//=============================================================================
//
// すぐに描ける2Dポリゴンクラス [CRect2D.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/4
//
//=============================================================================
#pragma once
#ifndef __KBR_CRECT_2D_H__
#define __KBR_CRECT_2D_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "OpenGL.h"
#include "kbMath.h"

// 2D用頂点
struct VERTEX_2D
{
	Vector3 pos;
	Vector4 color;
	Vector2 tex;
};

//*****************************************************************************
// すぐに描ける2Dポリゴンクラス
// Author : Ryo Kobayashi
//*****************************************************************************
class CRect2D
{
public:

	// 2D描画
	static void DrawPrimitive(GLenum drawType, void* pBuffer, unsigned nNumVertex);
};

#endif	// __KBR_CRECT_2D_H__

// EOF