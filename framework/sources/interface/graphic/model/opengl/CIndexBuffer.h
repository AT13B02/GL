//=============================================================================
//
// �C���f�b�N�X�o�b�t�@���� [CIndexBuffer.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//
//=============================================================================
#pragma once
#ifndef __KBR_INDEXBUFFER_H__
#define __KBR_INDEXBUFFER_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "OpenGL.h"

//*****************************************************************************
// �C���f�b�N�X�o�b�t�@�N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//*****************************************************************************
class CIndexBuffer
{
public:
	CIndexBuffer() : m_uIdx(0), m_pIdxBuff(NULL){}

	~CIndexBuffer(){}

	// �o�b�t�@�쐬
	static BOOL CreateBuffer(
		unsigned int uBufferSize,
		CIndexBuffer **ppIdx);

	// �r�f�I��������ɍ쐬�����C���f�b�N�X�o�b�t�@�𐶐�
	void GenBuffer(void);
	
	// �o�b�t�@�o�C���h
	void BindBuffer(void);
	
	//=============================================================================
	// �o�b�t�@�o�C���h����
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/5/13
	//=============================================================================
	void UnbindBuffer(void)
	{
		// �o�b�t�@�o�C���h����
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// �o�b�t�@�̐擪�ւ̃|�C���^���擾
	BOOL GetBufferPointer(void** pBuffTop);

	// �o�b�t�@�J��
	void Release(void);

private:

	// �o�b�t�@�C���f�b�N�X
	unsigned int m_uIdx;

	// ���_�o�b�t�@
	unsigned char* m_pIdxBuff;
	// �o�b�t�@�T�C�Y
	unsigned int m_uBufferSize;
};

typedef CIndexBuffer* LPCINDEXBUFFER;

#endif	// __KBR_INDEXBUFFER_H__

// EOF