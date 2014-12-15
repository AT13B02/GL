//*****************************************************************************
//
// GLモデルクラス
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "gl_model.h"
#include <stdio.h>

// opengl
#include "interface/graphic/device/opengl/opengl.h"

// common
#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CGLModel::CGLModel(CDeviceHolder* device_holder) :
CModel(device_holder)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGLModel::~CGLModel(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CGLModel::Init(void)
{
	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CGLModel::Uninit(void)
{
	SAFE_RELEASE(m_pVtxBuffer);

	SAFE_DELETE_ARRAY(m_pMaterial);
	SAFE_DELETE_ARRAY(m_pMeshAttribute);
}

//=============================================================================
// ロード
//=============================================================================
bool CGLModel::Load(const s8* filename)
{
	FILE *pFile = NULL;

	fopen_s(&pFile, filename, "rb");

	if(!pFile)
	{
		return false;
	}

	// ヘッダ読み込み
	DataHeader dh;
	fread(&dh, sizeof(dh), 1, pFile);

	// 頂点生成
	m_pVtxBuffer = CVertex3D::Create(device_holder_, dh.uVtx);
	// インデックス生成
	m_pVtxBuffer->CreateIndex(dh.uIdx);

	// 頂点読み込み
	CVertex3D::VERTEX_3D *pVtx;
	CVertex3D::VERTEX_3D_INDEX *pIdx;
	m_pVtxBuffer->Lock(&pVtx, &pIdx);
	// 頂点座標
	fread(pVtx->_position, sizeof(VECTOR3), dh.uVtx, pFile);
	// 法線
	fread(pVtx->_normal, sizeof(VECTOR3), dh.uVtx, pFile);
	// 頂点カラー
	for(int i = 0; i < dh.uVtx; i++)
	{
		pVtx->_color[i]._red =	1.0f;
		pVtx->_color[i]._green = 1.0f;
		pVtx->_color[i]._blue = 1.0f;
		pVtx->_color[i]._alpha = 1.0f;
	}
	// テクスチャ座標
	fread(pVtx->_texcoord, sizeof(VECTOR2), dh.uVtx, pFile);
	// インデックス
	fread(pIdx->_position, sizeof(u32), dh.uIdx, pFile);
	memcpy(pIdx->_normal, pIdx->_position, sizeof(u32) * dh.uIdx);
	memcpy(pIdx->_color, pIdx->_position, sizeof(u32) * dh.uIdx);
	memcpy(pIdx->_texcoord, pIdx->_position, sizeof(u32) * dh.uIdx);

	m_pVtxBuffer->Unlock();

	// マテリアル
	m_uNumMaterial = dh.uMat;
	m_pMaterial = new TexMaterial[dh.uMat];
	fread(m_pMaterial, sizeof(TexMaterial), dh.uMat, pFile);
	
	// アトリビュート読み込み
	m_pMeshAttribute = new MeshAttribute[dh.uAtt];
	fread(m_pMeshAttribute, sizeof(MeshAttribute), dh.uAtt, pFile);

	fclose(pFile);

	return true;
}

//=============================================================================
// 描画
//=============================================================================
void CGLModel::Draw(const MATRIX4x4& matrix)
{
	// デフォルトマテリアル取得
	VECTOR4 diffuse;
	glGetMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&diffuse);

	for(u32 uAtt = 0; uAtt < m_uNumMaterial; uAtt++)
	{
		glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&m_pMaterial->mat.Diffuse);
		m_pVtxBuffer->Draw(matrix, m_pMeshAttribute[uAtt].idxStart, m_pMeshAttribute[uAtt].idxNum);
	}

	glMaterialfv(GL_FRONT, GL_DIFFUSE, (GLfloat*)&diffuse);
}

// EOF