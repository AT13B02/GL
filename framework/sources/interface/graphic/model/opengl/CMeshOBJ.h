//=============================================================================
//
// OBJクラス [CMeshOBJ.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/19
//
//=============================================================================
#pragma once
#ifndef __KBR_MESHOBJ_H__
#define __KBR_MESHOBJ_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include "common/math/math.h"

//*****************************************************************************
// マテリアル
//*****************************************************************************
struct Material
{
	VECTOR4 Diffuse;
	VECTOR4 Ambient;
	VECTOR4 Specular;
	VECTOR4 Emissive;
	f32 SpecPower;
};

//*****************************************************************************
// メッシュマテリアル
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
struct MeshMaterial
{
	Material mat;
	s8 TexFileName[MAX_PATH];
};

// 前方参照
class CVBO;
class CIndexBuffer;
struct MeshAttribute;

//*****************************************************************************
// OBJメッシュクラス
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
class CMeshOBJ
{
public:

	CMeshOBJ();

	~CMeshOBJ();

	// 生成処理
	static HRESULT Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial, CMeshOBJ** ppOBJ);

	// 開放処理
	void Release(void);

	// 描画処理
	void DrawSubset(u32 uIndex);

private:

	// 生成処理
	HRESULT Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial);

private:

	// 頂点数
	u32				m_uNumVertex;
	// 頂点バッファ
	CVBO				*m_pVtxBuff;
	CVBO				*m_pTexCoordBuff;
	CVBO				*m_pNormalBuff;
	
	// インデックス数
	u32				m_uNumIndex;
	// インデックスバッファ
	CIndexBuffer		*m_pIdxBuff;

	// サブセット数
	u32				m_uNumSubset;
	// アトリビュート
	MeshAttribute		*m_pAttribute;

	// マテリアル数
	u32				m_uNumMaterial;
	// マテリアル
	MeshMaterial		*m_pMaterial;
};

typedef CMeshOBJ *LPCMESHOBJ;

#endif	// __KBR_MESHOBJ_H__

// EOF