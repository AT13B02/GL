//=============================================================================
//
// すぐに描ける2Dポリゴンクラス [CRect2D.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/4
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CRect2D.h"
#include "CStaticVBO.h"

//=============================================================================
// 2D描画
//=============================================================================
void CRect2D::DrawPrimitive(GLenum drawType, void* pBuffer, unsigned nNumVertex)
{
	CStaticVBO *pVtxBuff = NULL;
	CStaticVBO *pColorBuff = NULL;
	CStaticVBO *pTexCoordBuff = NULL;
	
	// VBO作成
	// 頂点
	CStaticVBO::CreateBuffer(sizeof(Vector3) * nNumVertex, 3, GL_VERTEX_ARRAY, &pVtxBuff);
	// 色
	CStaticVBO::CreateBuffer(sizeof(Vector4) * nNumVertex, 4, GL_COLOR_ARRAY, &pColorBuff);
	// テクスチャ座標
	CStaticVBO::CreateBuffer(sizeof(Vector2) * nNumVertex, 2, GL_TEXTURE_COORD_ARRAY, &pTexCoordBuff);

	VERTEX_2D *pVtx = (VERTEX_2D*)pBuffer;
	Vector3* pVtxPos;
	Vector4* pColor;
	Vector2* pTexCoord;
	pVtxBuff->GetBufferPointer((void**)&pVtxPos);
	pColorBuff->GetBufferPointer((void**)&pColor);
	pTexCoordBuff->GetBufferPointer((void**)&pTexCoord);

	for(int i = 0; i < (int)nNumVertex; i++)
	{
		pVtxPos[i] = pVtx[i].pos;
		pColor[i] = pVtx[i].color;
		pTexCoord[i] = pVtx[i].tex;
	}
	
	pVtxBuff->GenBuffer();
	pColorBuff->GenBuffer();
	pTexCoordBuff->GenBuffer();
	
	// 深度テスト無効化
	glDisable(GL_DEPTH_TEST);
	
	// 頂点配列有効化
	pVtxBuff->ValidateArrayValue();
	// カラー配列有効化
	pColorBuff->ValidateArrayValue();
	// テクスチャ配列有効化
	pTexCoordBuff->ValidateArrayValue();
	// 描画
	glDrawArrays(drawType, 0, nNumVertex);
	// 配列無効化
	pVtxBuff->InvalidateArrayValue();
	pColorBuff->InvalidateArrayValue();
	pTexCoordBuff->InvalidateArrayValue();
	
	// 深度テスト有効化
	glEnable(GL_DEPTH_TEST);

	pVtxBuff->Release();
	pColorBuff->Release();
	pTexCoordBuff->Release();
}

// EOF