//=============================================================================
//
// OBJ�N���X [CMeshOBJ.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/19
//
//=============================================================================
#pragma once
#ifndef __KBR_MESHOBJ_H__
#define __KBR_MESHOBJ_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include "common/math/math.h"

//*****************************************************************************
// �}�e���A��
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
// ���b�V���}�e���A��
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
struct MeshMaterial
{
	Material mat;
	s8 TexFileName[MAX_PATH];
};

// �O���Q��
class CVBO;
class CIndexBuffer;
struct MeshAttribute;

//*****************************************************************************
// OBJ���b�V���N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/28
//*****************************************************************************
class CMeshOBJ
{
public:

	CMeshOBJ();

	~CMeshOBJ();

	// ��������
	static HRESULT Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial, CMeshOBJ** ppOBJ);

	// �J������
	void Release(void);

	// �`�揈��
	void DrawSubset(u32 uIndex);

private:

	// ��������
	HRESULT Create(const s8* pFileName, u32* pNumSubset, MeshMaterial** ppMaterial);

private:

	// ���_��
	u32				m_uNumVertex;
	// ���_�o�b�t�@
	CVBO				*m_pVtxBuff;
	CVBO				*m_pTexCoordBuff;
	CVBO				*m_pNormalBuff;
	
	// �C���f�b�N�X��
	u32				m_uNumIndex;
	// �C���f�b�N�X�o�b�t�@
	CIndexBuffer		*m_pIdxBuff;

	// �T�u�Z�b�g��
	u32				m_uNumSubset;
	// �A�g���r���[�g
	MeshAttribute		*m_pAttribute;

	// �}�e���A����
	u32				m_uNumMaterial;
	// �}�e���A��
	MeshMaterial		*m_pMaterial;
};

typedef CMeshOBJ *LPCMESHOBJ;

#endif	// __KBR_MESHOBJ_H__

// EOF