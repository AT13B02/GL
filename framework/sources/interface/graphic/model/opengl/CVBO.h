//=============================================================================
//
// ���_�o�b�t�@�I�u�W�F�N�g [CVBO.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//
//=============================================================================
#pragma once
#ifndef __KBR_VBO_H__
#define __KBR_VBO_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "OpenGL.h"

//*****************************************************************************
// ���_�o�b�t�@�I�u�W�F�N�g�N���X
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/12
//*****************************************************************************
class CVBO
{
public:

	CVBO(){}

	~CVBO(){}
	
	// �o�b�t�@�쐬
	static BOOL CreateBuffer(
		unsigned int uBufferSize,
		unsigned int uDimension,
		GLenum ArrayType,
		CVBO **ppVBO);
	
	//=============================================================================
	// �z��錾�𖳌���
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/5/8
	//=============================================================================
	void InvalidateArrayValue(void)
	{
		// �z��錾�𖳌���
		glDisableClientState(this->m_uArrayType);
		// ���_�o�C���h������
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// �z��錾��L����
	void ValidateArrayValue(void);

	// �o�b�t�@�̐擪�ւ̃|�C���^���擾
	BOOL GetBufferPointer(void** pBuffTop);

	// �o�b�t�@�J��
	void Release(void);

private:

	// �o�b�t�@�C���f�b�N�X
	GLuint	m_uIdx;
	
	// ���_�o�b�t�@
	char* pVtxBuff;
	// �z��̎��
	unsigned short m_uArrayType;
	// �o�b�t�@�T�C�Y
	unsigned int m_uBufferSize;
	// �v�f�̎���
	unsigned int m_uDimension;
};

#endif	// __KBR_VBO_H__

// EOF