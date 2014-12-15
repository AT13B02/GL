//=============================================================================
//
// �e�N�X�`���N���X [CTextureGL.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "CTextureGL.h"
#include "TextureLoader.h"
#include "Debug.h"

//=============================================================================
// �R���X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureGL::CTextureGL() :
m_uIndex(0),
m_pTex(NULL),
m_uWidth(0),
m_uHeight(0)
{
}

//=============================================================================
// �f�X�g���N�^
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
CTextureGL::~CTextureGL()
{
}

//=============================================================================
// �e�N�X�`�����[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureGL::LoadFromFile(const char* pFileName, CTextureGL** ppTexture)
{
	// �e�N�X�`������
	(*ppTexture) = new CTextureGL();

	if(!(*ppTexture)->LoadFromFile(pFileName))
	{
		return FALSE;
	}

	return TRUE;
}

//=============================================================================
// �e�N�X�`���o�b�t�@�ւ̃|�C���^���擾
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
unsigned char* CTextureGL::GetBufferPointer(void)
{
	return m_pTex;
}

//=============================================================================
// �e�N�X�`�����[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
BOOL CTextureGL::LoadFromFile(const char* pFileName)
{
	LoadTexture(pFileName, &m_pTex, &m_uWidth, &m_uHeight);

	// �ǂݍ��ݎ��s��
	if(!m_pTex)
	{
		_asm int 3;
		return FALSE;
	}
	
	// �e�N�X�`������
	glGenTextures(1, &m_uIndex);
	// �Q�ƃe�N�X�`���ݒ�
	glBindTexture(GL_TEXTURE_2D, m_uIndex);

	// 1�s�N�Z���ɑ΂��鏈��(UNPACK_ALIGNMENT), 1�o�C�g
	// 4�o�C�g�A���C�������g������ƍ����ɂȂ�
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	// S������(��)�������b�v���@
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	// T������(�c)�������b�v���@
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// �g�厞��ԕ��@
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// �k������ԕ��@
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// �e�N�X�`���K�p
	glTexImage2D(
		GL_TEXTURE_2D,	// �e�N�X�`���`��(�Œ�)
		0,				// �~�b�v�}�b�v���x��(0���Ɩ���)
		GL_RGBA,		// �e�N�X�`���t�H�[�}�b�g(�݂��܂��)
		m_uWidth,		// �e�N�X�`������
		m_uHeight,		// �e�N�X�`���c��
		0,				// �e�N�X�`������̃{�[�_�[(�Ȃ񂩂̌��ʂŎg�������H)
		GL_RGBA,		// �e�N�X�`���������u���b�N�t�H�[�}�b�g(��̃t�H�[�}�b�g�Ɠ���)
		GL_UNSIGNED_BYTE,// �e�N�X�`��1����(R,A,etc.)�̌^
		m_pTex);		// �e�N�X�`���Q�Ɛ�
	
	// �e�N�X�`���Q�Ɛ�J��
	glBindTexture(GL_TEXTURE_2D, 0);

	return TRUE;
}

//=============================================================================
// �e�N�X�`���J��
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
void CTextureGL::Release(void)
{
	// VRAM��̃e�N�X�`�����J��
	glDeleteTextures(1, &m_uIndex);
	// �e�N�X�`���f���[�g
	DeleteTexture(&m_pTex);
	delete this;
}

//=============================================================================
// �e�N�X�`���ݒ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/16
//=============================================================================
void CTextureGL::SetTex2D(void)
{
	glBindTexture(GL_TEXTURE_2D, m_uIndex);
}

// EOF