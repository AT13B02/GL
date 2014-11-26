//=============================================================================
//
// インデックスバッファ処理 [CIndexBuffer.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CIndexBuffer.h"
#include "Debug.h"

//=============================================================================
// バッファ作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//
// ret			: BOOL TRUE:成功 FALSE:失敗
// arg1			: unsigned int 頂点バッファサイズ
// arg3			: CIndexBuffer** 頂点バッファクラスへのポインタ
//=============================================================================
BOOL CIndexBuffer::CreateBuffer(
	unsigned int uBufferSize,
	CIndexBuffer **ppIdx)
{
	// 頂点バッファクラス作成
	(*ppIdx) = new CIndexBuffer();
	_AssertExpr((*ppIdx), "インデックスバッファクラス生成失敗");
	// 作成失敗
	if((*ppIdx) == NULL)
	{
		return FALSE;
	}

	// 頂点バッファ確保
	(*ppIdx)->m_pIdxBuff = new unsigned char[uBufferSize];
	_AssertExpr((*ppIdx)->m_pIdxBuff, "インデックスバッファ生成失敗");
	// 確保失敗
	if((*ppIdx)->m_pIdxBuff == NULL)
	{
		return FALSE;
	}

	// バッファサイズ
	(*ppIdx)->m_uBufferSize = uBufferSize;

	return TRUE;
}

//=============================================================================
// ビデオメモリ上に作成したインデックスバッファを生成
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
void CIndexBuffer::GenBuffer(void)
{
	// バッファ生成
	glGenBuffers(1, &m_uIdx);
	// バッファバインド
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uIdx);
	// バッファ確保
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_uBufferSize, m_pIdxBuff, GL_STATIC_DRAW);
	// バインド解除
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	
//=============================================================================
// バッファバインド
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//=============================================================================
void CIndexBuffer::BindBuffer(void)
{
	// バッファバインド
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uIdx);
}

//=============================================================================
// バッファの先頭へのポインタを取得
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
BOOL CIndexBuffer::GetBufferPointer(void** pBuffTop)
{
	// バッファが確保されていない
	if(this->m_pIdxBuff == NULL)
	{
		return FALSE;
	}
	(*pBuffTop) = this->m_pIdxBuff;
	
	return TRUE;
}

//=============================================================================
// バッファ開放
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//=============================================================================
void CIndexBuffer::Release(void)
{
	if(this->m_pIdxBuff)
	{
		delete[] this->m_pIdxBuff;
		this->m_pIdxBuff = NULL;
	}

	// バッファ破棄
	glDeleteBuffers(1, &m_uIdx);

	delete this;
}

// EOF