//=============================================================================
//
// ���_�o�b�t�@���� [CVBO.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CVBO.h"
#include "Debug.h"

//=============================================================================
// �o�b�t�@�쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//
// ret			: BOOL TRUE:���� FALSE:���s
// arg1			: unsigned int ���_�o�b�t�@�T�C�Y
// arg2			: unsigned int ��v�f�̎���(Vector3 -> float[3]��)
// arg2			: GLenum �z��^�C�v
// arg3			: CVBO** ���_�o�b�t�@�N���X�ւ̃|�C���^
//=============================================================================
BOOL CVBO::CreateBuffer(
	unsigned int uBufferSize,
	unsigned int uDimension,
	GLenum ArrayType,
	CVBO **ppVBO)
{
	// ���_�o�b�t�@�N���X�쐬
	(*ppVBO) = new CVBO();
	_AssertExpr((*ppVBO), "���_�o�b�t�@�I�u�W�F�N�g�N���X�������s");
	// �쐬���s
	if((*ppVBO) == NULL)
	{
		return FALSE;
	}

	// ���_�o�b�t�@�m��
	(*ppVBO)->pVtxBuff = new char[uBufferSize];
	_AssertExpr((*ppVBO)->pVtxBuff, "���_�o�b�t�@�������s");
	// �m�ێ��s
	if((*ppVBO)->pVtxBuff == NULL)
	{
		return FALSE;
	}

	// �z��̎�ނ�ݒ�
	(*ppVBO)->m_uArrayType = ArrayType;

	// �o�b�t�@�T�C�Y
	(*ppVBO)->m_uBufferSize = uBufferSize;

	// �v�f���ݒ�
	(*ppVBO)->m_uDimension = uDimension;
	
	// �o�b�t�@����
	glGenBuffers(1, &(*ppVBO)->m_uIdx);
	// �o�b�t�@�o�C���h
	glBindBuffer(GL_ARRAY_BUFFER, (*ppVBO)->m_uIdx);
	// �o�b�t�@�m��
	glBufferData(GL_ARRAY_BUFFER, (*ppVBO)->m_uBufferSize, 0, GL_DYNAMIC_DRAW);
	// �o�C���h����
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return TRUE;
}

//=============================================================================
// �z��錾��L����
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
void CVBO::ValidateArrayValue(void)
{
	// �z��錾��L����
	glEnableClientState(this->m_uArrayType);

	// �o�b�t�@�o�C���h
	glBindBuffer(GL_ARRAY_BUFFER, m_uIdx);
	// �f�[�^���o
	glBufferSubData(GL_ARRAY_BUFFER, 0, m_uBufferSize, pVtxBuff);

	// �o�b�t�@�̐擪����̃I�t�Z�b�g��ݒ�
	switch(this->m_uArrayType)
	{
		// ���_
	case GL_VERTEX_ARRAY:
		glVertexPointer(this->m_uDimension, GL_FLOAT, 0, 0);
		break;
		// �F
	case GL_COLOR_ARRAY:
		glColorPointer(this->m_uDimension, GL_FLOAT, 0, 0);
		break;
		// �@��
	case GL_NORMAL_ARRAY:
		glNormalPointer(GL_FLOAT, 0, 0);
		break;
		// �e�N�X�`�����W
	case GL_TEXTURE_COORD_ARRAY:
		glTexCoordPointer(this->m_uDimension, GL_FLOAT, 0, 0);
		break;
	default:
		_AssertExpr(0, "�w�肳�ꂽ�z��^�C�v�͑��݂��܂���");
	}
}

//=============================================================================
// �o�b�t�@�̐擪�ւ̃|�C���^���擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
BOOL CVBO::GetBufferPointer(void** pBuffTop)
{
	// �o�b�t�@���m�ۂ���Ă��Ȃ�
	if(this->pVtxBuff == NULL)
	{
		return FALSE;
	}
	(*pBuffTop) = this->pVtxBuff;
	
	return TRUE;
}

//=============================================================================
// �o�b�t�@�J��
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//=============================================================================
void CVBO::Release(void)
{
	if(this->pVtxBuff)
	{
		delete[] this->pVtxBuff;
		this->pVtxBuff = NULL;
	}

	// �o�b�t�@�j��
	glDeleteBuffers(1, &m_uIdx);

	delete this;
}

// EOF