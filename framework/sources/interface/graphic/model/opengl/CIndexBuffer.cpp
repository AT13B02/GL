//=============================================================================
//
// �C���f�b�N�X�o�b�t�@���� [CIndexBuffer.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/13
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CIndexBuffer.h"
#include "Debug.h"

//=============================================================================
// �o�b�t�@�쐬
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//
// ret			: BOOL TRUE:���� FALSE:���s
// arg1			: unsigned int ���_�o�b�t�@�T�C�Y
// arg3			: CIndexBuffer** ���_�o�b�t�@�N���X�ւ̃|�C���^
//=============================================================================
BOOL CIndexBuffer::CreateBuffer(
	unsigned int uBufferSize,
	CIndexBuffer **ppIdx)
{
	// ���_�o�b�t�@�N���X�쐬
	(*ppIdx) = new CIndexBuffer();
	_AssertExpr((*ppIdx), "�C���f�b�N�X�o�b�t�@�N���X�������s");
	// �쐬���s
	if((*ppIdx) == NULL)
	{
		return FALSE;
	}

	// ���_�o�b�t�@�m��
	(*ppIdx)->m_pIdxBuff = new unsigned char[uBufferSize];
	_AssertExpr((*ppIdx)->m_pIdxBuff, "�C���f�b�N�X�o�b�t�@�������s");
	// �m�ێ��s
	if((*ppIdx)->m_pIdxBuff == NULL)
	{
		return FALSE;
	}

	// �o�b�t�@�T�C�Y
	(*ppIdx)->m_uBufferSize = uBufferSize;

	return TRUE;
}

//=============================================================================
// �r�f�I��������ɍ쐬�����C���f�b�N�X�o�b�t�@�𐶐�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
void CIndexBuffer::GenBuffer(void)
{
	// �o�b�t�@����
	glGenBuffers(1, &m_uIdx);
	// �o�b�t�@�o�C���h
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uIdx);
	// �o�b�t�@�m��
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_uBufferSize, m_pIdxBuff, GL_STATIC_DRAW);
	// �o�C���h����
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
	
//=============================================================================
// �o�b�t�@�o�C���h
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/14
//=============================================================================
void CIndexBuffer::BindBuffer(void)
{
	// �o�b�t�@�o�C���h
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uIdx);
}

//=============================================================================
// �o�b�t�@�̐擪�ւ̃|�C���^���擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/8
//=============================================================================
BOOL CIndexBuffer::GetBufferPointer(void** pBuffTop)
{
	// �o�b�t�@���m�ۂ���Ă��Ȃ�
	if(this->m_pIdxBuff == NULL)
	{
		return FALSE;
	}
	(*pBuffTop) = this->m_pIdxBuff;
	
	return TRUE;
}

//=============================================================================
// �o�b�t�@�J��
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/29
//=============================================================================
void CIndexBuffer::Release(void)
{
	if(this->m_pIdxBuff)
	{
		delete[] this->m_pIdxBuff;
		this->m_pIdxBuff = NULL;
	}

	// �o�b�t�@�j��
	glDeleteBuffers(1, &m_uIdx);

	delete this;
}

// EOF