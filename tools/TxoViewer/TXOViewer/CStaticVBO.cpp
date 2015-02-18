//=============================================================================
//
// 静的な頂点バッファオブジェクト [CStaticVBO.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CStaticVBO.h"
#include "Debug.h"

//=============================================================================
// バッファ作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//
// ret			: BOOL TRUE:成功 FALSE:失敗
// arg1			: unsigned int 頂点バッファサイズ
// arg2			: unsigned int 一要素の次元(Vector3 -> float[3]つ)
// arg2			: GLenum 配列タイプ
// arg3			: CStaticVBO** 頂点バッファクラスへのポインタ
//=============================================================================
BOOL CStaticVBO::CreateBuffer(
	unsigned int uBufferSize,
	unsigned int uDimension,
	GLenum ArrayType,
	CStaticVBO **ppVBO)
{
	// 頂点バッファクラス作成
	(*ppVBO) = new CStaticVBO();
	_AssertExpr((*ppVBO), "頂点バッファオブジェクトクラス生成失敗");
	// 作成失敗
	if((*ppVBO) == NULL)
	{
		return FALSE;
	}

	// 頂点バッファ確保
	(*ppVBO)->pVtxBuff = new char[uBufferSize];
	_AssertExpr((*ppVBO)->pVtxBuff, "頂点バッファ生成失敗");
	// 確保失敗
	if((*ppVBO)->pVtxBuff == NULL)
	{
		return FALSE;
	}

	// 配列の種類を設定
	(*ppVBO)->m_uArrayType = ArrayType;

	// バッファサイズ
	(*ppVBO)->m_uBufferSize = uBufferSize;

	// 要素数設定
	(*ppVBO)->m_uDimension = uDimension;
	
	return TRUE;
}

//=============================================================================
// ビデオメモリ上に作成したインデックスバッファを生成
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//=============================================================================
void CStaticVBO::GenBuffer(void)
{
	// バッファ生成
	glGenBuffers(1, &m_uIdx);
	// バッファバインド
	glBindBuffer(GL_ARRAY_BUFFER, m_uIdx);
	// バッファ確保
	glBufferData(GL_ARRAY_BUFFER, m_uBufferSize, pVtxBuff, GL_STATIC_DRAW);
	// バインド解除
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
	
//=============================================================================
// 配列宣言を有効化
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//=============================================================================
void CStaticVBO::ValidateArrayValue(void)
{
	// 配列宣言を有効化
	glEnableClientState(this->m_uArrayType);

	// バッファバインド
	glBindBuffer(GL_ARRAY_BUFFER, m_uIdx);

	// バッファの先頭からのオフセットを設定
	switch(this->m_uArrayType)
	{
		// 頂点
	case GL_VERTEX_ARRAY:
		glVertexPointer(this->m_uDimension, GL_FLOAT, 0, 0);
		break;
		// 色
	case GL_COLOR_ARRAY:
		glColorPointer(this->m_uDimension, GL_FLOAT, 0, 0);
		break;
		// 法線
	case GL_NORMAL_ARRAY:
		glNormalPointer(GL_FLOAT, 0, 0);
		break;
		// テクスチャ座標
	case GL_TEXTURE_COORD_ARRAY:
		glTexCoordPointer(this->m_uDimension, GL_FLOAT, 0, 0);
		break;
	default:
		_AssertExpr(0, "指定された配列タイプは存在しません");
	}
}

//=============================================================================
// バッファの先頭へのポインタを取得
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//=============================================================================
BOOL CStaticVBO::GetBufferPointer(void** pBuffTop)
{
	// バッファが確保されていない
	if(this->pVtxBuff == NULL)
	{
		return FALSE;
	}
	(*pBuffTop) = this->pVtxBuff;
	
	return TRUE;
}

//=============================================================================
// バッファ開放
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//=============================================================================
void CStaticVBO::Release(void)
{
	if(this->pVtxBuff)
	{
		delete[] this->pVtxBuff;
		this->pVtxBuff = NULL;
	}

	// バッファ破棄
	glDeleteBuffers(1, &m_uIdx);

	delete this;
}

// EOF