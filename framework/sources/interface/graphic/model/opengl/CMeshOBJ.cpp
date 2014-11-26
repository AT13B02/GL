//=============================================================================
//
// OBJクラス [CMeshOBJ.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CMeshOBJ.h"
#include "CVBO.h"
#include "CIndexBuffer.h"
#include <stdio.h>

//*****************************************************************************
// アトリビュート
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
struct MeshAttribute
{
	u32 idxStart;	// 開始インデックス
	u32 idxNum;	// インデックス数
	u32 vtxStart;	// 開始頂点番号
	u32 vtxNum;	// 頂点数
	u32 faceNum;	// プリミティブ数
};

// データヘッダ
struct XOHeader
{
	u32 uVtx;
	u32 uIdx;
	u32 uMat;
	u32 uAtt;
};

//=============================================================================
// コンストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
CMeshOBJ::CMeshOBJ() :
m_uNumVertex(0),
m_pVtxBuff(NULL),
m_pTexCoordBuff(NULL),
m_pNormalBuff(NULL),
m_uNumIndex(0),
m_pIdxBuff(NULL),
m_uNumSubset(0),
m_pAttribute(NULL),
m_uNumMaterial(0),
m_pMaterial(NULL)
{
}

//=============================================================================
// デストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
CMeshOBJ::~CMeshOBJ()
{
}

//=============================================================================
// 生成処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
HRESULT CMeshOBJ::Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial, CMeshOBJ** ppOBJ)
{
	HRESULT hr;

	// メッシュ生成
	(*ppOBJ) = new CMeshOBJ();

	// メッシュ生成処理
	hr = (*ppOBJ)->Create(pFileName, pNumSubset, ppMaterial);

	return hr;
}

//=============================================================================
// 開放処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
void CMeshOBJ::Release(void)
{
	// 頂点開放
	m_pVtxBuff->Release();
	m_pTexCoordBuff->Release();
	m_pNormalBuff->Release();

	// インデックス開放
	m_pIdxBuff->Release();
	
	// サブセット開放
	if(m_pAttribute)
	{
		delete [] m_pAttribute;
	}

	if(m_pMaterial)
	{
		delete [] m_pMaterial;
	}

	// 自己解放
	delete this;
}

//=============================================================================
// 描画処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
void CMeshOBJ::DrawSubset(u32 uIndex)
{
	// 頂点配列有効化
	m_pVtxBuff->ValidateArrayValue();
	// 法線配列有効化
	m_pNormalBuff->ValidateArrayValue();
	// テクスチャ配列有効化
	m_pTexCoordBuff->ValidateArrayValue();

	// インデックスバインド
	m_pIdxBuff->BindBuffer();

	// 描画
	u32 uOffsetIdx = m_pAttribute[uIndex].idxStart * sizeof(u32);
	glDrawElements(GL_TRIANGLE_STRIP, m_pAttribute[uIndex].idxNum, GL_UNSIGNED_INT, (void*)uOffsetIdx);

	// 配列無効化
	m_pVtxBuff->InvalidateArrayValue();
	m_pNormalBuff->InvalidateArrayValue();
	m_pTexCoordBuff->InvalidateArrayValue();

	// インデックスバインド解除
	m_pIdxBuff->UnbindBuffer();
}

//=============================================================================
// 生成処理
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//=============================================================================
HRESULT CMeshOBJ::Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial)
{
	// メッシュファイル読み込み
	FILE *pFile;

	// ファイルオープン
	pFile = fopen(pFileName, "rb");
	if(!pFile)
	{
		return E_FAIL;
	}

	// ヘッダ
	XOHeader xo;
	// ヘッダ読み込み
	fread(&xo, sizeof(xo), 1, pFile);

	// 頂点数コピー
	m_uNumVertex = xo.uVtx;

	// 頂点データ生成
	// 座標
	CVBO::CreateBuffer(m_uNumVertex * sizeof(VECTOR3), 3, GL_VERTEX_ARRAY, &m_pVtxBuff);
	// テクスチャ座標
	CVBO::CreateBuffer(m_uNumVertex * sizeof(VECTOR2), 2, GL_TEXTURE_COORD_ARRAY, &m_pTexCoordBuff);
	// 法線
	CVBO::CreateBuffer(m_uNumVertex * sizeof(VECTOR3), 3, GL_NORMAL_ARRAY, &m_pNormalBuff);

	// 頂点バッファアクセスポインタ
	VECTOR3 *pVtx = NULL;
	VECTOR2 *pTexCoord = NULL;
	VECTOR3 *pNormal = NULL;

	// 頂点座標アクセス
	m_pVtxBuff->GetBufferPointer((void**)&pVtx);
	// 頂点座標データ読み込み
	fread(pVtx, m_uNumVertex * sizeof(VECTOR3), 1, pFile);
	// 法線アクセス
	m_pNormalBuff->GetBufferPointer((void**)&pNormal);
	// 法線データ読み込み
	fread(pNormal, m_uNumVertex * sizeof(VECTOR3), 1, pFile);
	// テクスチャ座標アクセス
	m_pTexCoordBuff->GetBufferPointer((void**)&pTexCoord);
	// テクスチャ座標データ読み込み
	fread(pTexCoord, m_uNumVertex * sizeof(VECTOR2), 1, pFile);

	// インデックスデータ生成
	m_uNumIndex = xo.uIdx;
	CIndexBuffer::CreateBuffer(m_uNumIndex * sizeof(u32), &m_pIdxBuff);
	// インデックスデータ読み込み
	u32 *pIdx = NULL;
	m_pIdxBuff->GetBufferPointer((void**)&pIdx);
	fread(pIdx, m_uNumIndex * sizeof(u32), 1, pFile);

	// VRAM上にバッファ生成
	m_pIdxBuff->GenBuffer();
	
	m_uNumMaterial = xo.uMat;
	// マテリアル生成
	m_pMaterial = new MeshMaterial[m_uNumMaterial];
	// マテリアル読み込み
	fread(m_pMaterial, m_uNumMaterial * sizeof(MeshMaterial), 1, pFile);
	// マテリアル設定
	(*ppMaterial) = m_pMaterial;
	
	m_uNumSubset = xo.uAtt;
	// サブセット数コピー
	*pNumSubset = m_uNumSubset;
	// サブセット数だけアトリビュート生成
	m_pAttribute = new MeshAttribute[m_uNumSubset];
	// ファイル読み込み
	fread(m_pAttribute, m_uNumSubset * sizeof(MeshAttribute), 1, pFile);
	
	// ファイルクローズ
	fclose(pFile);

	return S_OK;
}

// EOF