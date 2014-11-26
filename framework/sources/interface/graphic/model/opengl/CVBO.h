//=============================================================================
//
// 頂点バッファオブジェクト [CVBO.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//
//=============================================================================
#pragma once
#ifndef __KBR_VBO_H__
#define __KBR_VBO_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "OpenGL.h"

//*****************************************************************************
// 頂点バッファオブジェクトクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//*****************************************************************************
class CVBO
{
public:

	CVBO(){}

	~CVBO(){}
	
	// バッファ作成
	static BOOL CreateBuffer(
		unsigned int uBufferSize,
		unsigned int uDimension,
		GLenum ArrayType,
		CVBO **ppVBO);
	
	//=============================================================================
	// 配列宣言を無効化
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/5/8
	//=============================================================================
	void InvalidateArrayValue(void)
	{
		// 配列宣言を無効化
		glDisableClientState(this->m_uArrayType);
		// 頂点バインドを解除
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// 配列宣言を有効化
	void ValidateArrayValue(void);

	// バッファの先頭へのポインタを取得
	BOOL GetBufferPointer(void** pBuffTop);

	// バッファ開放
	void Release(void);

private:

	// バッファインデックス
	GLuint	m_uIdx;
	
	// 頂点バッファ
	char* pVtxBuff;
	// 配列の種類
	unsigned short m_uArrayType;
	// バッファサイズ
	unsigned int m_uBufferSize;
	// 要素の次元
	unsigned int m_uDimension;
};

#endif	// __KBR_VBO_H__

// EOF