//=============================================================================
//
// �e�N�X�`���N���X [CTextureConverter.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CTextureConverter.h"
#include "TextureLoader.h"
#include "kbString.h"
#include <stdio.h>
#include "Debug.h"

//=============================================================================
// �R���X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureConverter::CTextureConverter() :
m_pBuffer(NULL),
m_uWidth(0),
m_uHeight(0)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureConverter::~CTextureConverter()
{
}

//=============================================================================
// �e�N�X�`�����[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureConverter::Convert(const char* pFileName)
{
	// �e�N�X�`������
	CTextureConverter conv;

	if(!conv.LoadFromFile(pFileName))
	{
		return FALSE;
	}

	return TRUE;
}

//=============================================================================
// �e�N�X�`�����[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureConverter::LoadFromFile(const char* pFileName)
{
	LoadTexture(pFileName, &m_pBuffer, &m_uWidth, &m_uHeight);

	// �ǂݍ��ݎ��s��
	if(!m_pBuffer)
	{
		_asm int 3;
		return FALSE;
	}

	kb::CString fn(pFileName);
	// �t�@�C�����ݒ�
	int id = fn.SearchTokenIndexL('.') + 1;
	char ext[] = "txo";
	int strId = 0;
	while(id + strId < fn.GetLength())
	{
		fn[id + strId] = ext[strId];
		strId++;
	}
	while(strId < sizeof(ext) - 1)
	{
		fn += &ext[strId];
		strId++;
	}
	// �t�@�C���I�[�v��
	FILE* pFile = nullptr;
	fopen_s(&pFile, fn.GetStr(), "wb");
	// ����
	fwrite(&m_uWidth, sizeof(m_uWidth), 1, pFile);
	// �c��
	fwrite(&m_uHeight, sizeof(m_uHeight), 1, pFile);
	// �f�[�^(rgba��4�o�C�g)
	fwrite(m_pBuffer, 4, m_uWidth * m_uHeight, pFile);
	fclose(pFile);

	printf("�ϊ� : %s\n", fn.GetStr());

	delete[] m_pBuffer;
	
	return TRUE;
}

// EOF