//=============================================================================
//
// インデックスバッファ処理 [CIndexBuffer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//
//=============================================================================
#pragma once
#ifndef __KBR_INDEXBUFFER_H__
#define __KBR_INDEXBUFFER_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "OpenGL.h"

//*****************************************************************************
// インデックスバッファクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//*****************************************************************************
class CIndexBuffer
{
public:
	CIndexBuffer() : m_uIdx(0), m_pIdxBuff(NULL){}

	~CIndexBuffer(){}

	// バッファ作成
	static BOOL CreateBuffer(
		unsigned int uBufferSize,
		CIndexBuffer **ppIdx);

	// ビデオメモリ上に作成したインデックスバッファを生成
	void GenBuffer(void);
	
	// バッファバインド
	void BindBuffer(void);
	
	//=============================================================================
	// バッファバインド解除
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/5/13
	//=============================================================================
	void UnbindBuffer(void)
	{
		// バッファバインド解除
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// バッファの先頭へのポインタを取得
	BOOL GetBufferPointer(void** pBuffTop);

	// バッファ開放
	void Release(void);

private:

	// バッファインデックス
	unsigned int m_uIdx;

	// 頂点バッファ
	unsigned char* m_pIdxBuff;
	// バッファサイズ
	unsigned int m_uBufferSize;
};

typedef CIndexBuffer* LPCINDEXBUFFER;

#endif	// __KBR_INDEXBUFFER_H__

// EOF