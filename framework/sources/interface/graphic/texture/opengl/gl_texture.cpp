//*****************************************************************************
//
// OpenGL�e�N�X�`���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <stdio.h>
// basic
#include "basic/application.h"

#ifdef _USING_OPENGL_
// graphic
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/device/opengl/opengl.h"
#include "interface/graphic/texture/opengl/gl_texture.h"

// common
#include "common/file/file.h"
#include "common/image/image.h"
#include "common/image/tga.h"
#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CGLTexture::CGLTexture(CDeviceHolder* device_holder) : CTexture(device_holder)
{
	// �e�N�X�`����ǂݍ��݂��Ă��Ȃ���Ԃɂ���
	m_nTexture = 0;

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGLTexture::~CGLTexture(void)
{
}

//=============================================================================
// ���[�h����
//=============================================================================
bool CGLTexture::Init(void)
{
	return true;
}

//=============================================================================
// �I������
//=============================================================================
void CGLTexture::Uninit(void)
{
	glDeleteTextures(1,&m_nTexture);

	CTexture::Uninit();
}

//=============================================================================
// ���[�h����
//=============================================================================
bool CGLTexture::Load(const char* pFilename)
{
	EXTENSION Extension;

	if(m_nTexture != 0)
	{
		// ���łɓǂݍ��݂��Ă���
		return false;
	}

	// �t�@�C�����̐ݒ�
	SetFilename(pFilename);

	// �g���q�̔���
	Extension = GetExtension(pFilename);

	// �g���q�œǂݍ��ݕ��@��ύX
	switch(Extension)
	{
	// TGA�t�@�C��
	case EXTENSION_TGA:
		// TGA�̃��[�h
		m_nTexture = LoadTga(pFilename);
		break;

	// PNG�t�@�C��
	case EXTENSION_PNG:
		m_nTexture = LoadPng(pFilename);
		break;
	// TXO�t�@�C��
	case EXTENSION_TXO:
		m_nTexture = LoadTxo(pFilename);
		break;
	// �Ή����Ă��Ȃ��t�@�C��
	default:
		return false;
	}

	// �e�N�X�`���̃o�C���h
	glBindTexture(GL_TEXTURE_2D,m_nTexture);

	// �A���C�����g�̐ݒ�
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);

	// �����������s�[�g����
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);

	// �c���������s�[�g����
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	// ���`��Ԃ���
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	// �e�N�X�`���̑I��j��
	glBindTexture(GL_TEXTURE_2D,0);
	
	return true;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
bool CGLTexture::Set(void)
{
	glBindTexture(GL_TEXTURE_2D,m_nTexture);

	if(glIsTexture(m_nTexture))
	{
		int a = 0;
	}
	return true;
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CGLTexture::Unset(void)
{
	glBindTexture(GL_TEXTURE_2D,0);
}

//=============================================================================
// TGA�t�@�C���ǂݍ��ݏ���
//=============================================================================
unsigned int CGLTexture::LoadTga(const char* pFilename)
{
	unsigned int nTexture = 0;		// �e�N�X�`���l�[��
	unsigned short nWidth;			// �摜�̉���
	unsigned short nHeight;			// �摜�̏c��
	unsigned char *pImage;			// �C���[�W�f�[�^
	IMAGE Image;

	if(!LoadTGATexture(pFilename,&Image,true))
	{
		return 0;
	}

	pImage = ConvertCharFromImage(Image);

	nWidth = Image._width;
	nHeight = Image._height;

	SAFE_DELETE_ARRAY(Image._color);

	// �e�N�X�`������
	glGenTextures(1,&nTexture);

	// �e�N�X�`���̑I��
	glBindTexture(GL_TEXTURE_2D,nTexture);

	// �e�N�X�`���̃��[�h
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,nWidth,nHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pImage);

	// �C���[�W�̔j��
	delete[] pImage;

	if(glIsTexture(nTexture))
	{
		int a = 0;
	}

	return nTexture;

}

//=============================================================================
// TXO�t�@�C���̃��[�h
//=============================================================================
unsigned int CGLTexture::LoadTxo(const char* pFilename)
{
	unsigned int nTexture = 0;		// �e�N�X�`���l�[��
	unsigned short nWidth;			// �摜�̉���
	unsigned short nHeight;			// �摜�̏c��
	unsigned char *pImage;			// �C���[�W�f�[�^
	
	// �e�N�X�`���f�[�^�ǂݍ���
	// �t�@�C���|�C���^
	FILE *file = nullptr;
	// �t�@�C���I�[�v��
	fopen_s(&file, pFilename, "rb");
	if(!file)
	{
		return FALSE;
	}

	// ���ǂݍ���
	fread(&nWidth, sizeof(unsigned short), 1, file);
	fread(&nHeight, sizeof(unsigned short), 1, file);
	// �o�b�t�@����
	unsigned bufferSize = nWidth * nHeight * 4;
	pImage = new unsigned char[bufferSize];
	fread(pImage, bufferSize, 1, file);

	// �t�@�C���N���[�Y
	fclose(file);

	// �e�N�X�`������
	glGenTextures(1,&nTexture);

	// �e�N�X�`���̑I��
	glBindTexture(GL_TEXTURE_2D,nTexture);

	// �e�N�X�`���̃��[�h
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,nWidth,nHeight,0,GL_RGBA,GL_UNSIGNED_BYTE,pImage);

	// �C���[�W�̔j��
	delete[] pImage;

	if(glIsTexture(nTexture))
	{
		int a = 0;
	}

	return nTexture;
}

//=============================================================================
// TGA�t�@�C���ǂݍ��ݏ���
//=============================================================================
unsigned int CGLTexture::LoadPng(const char* pFilename)
{
	return 0;
}

//=============================================================================
// �g���q���ʏ���
//=============================================================================
CGLTexture::EXTENSION CGLTexture::GetExtension(const char* pFilename)
{
	char* pExtension;
	CGLTexture::EXTENSION Ret = EXTENSION_NONE;

	GetExtensionName(&pExtension,pFilename);

	// TGA�����f
	if(!strcmp(pExtension,"tga"))
	{
		Ret = EXTENSION_TGA;
	}
	else if(!strcmp(pExtension,"png"))
	{
		Ret = EXTENSION_PNG;
	}
	else if(!strcmp(pExtension,"txo"))
	{
		Ret = EXTENSION_TXO;
	}

	SAFE_DELETE_ARRAY(pExtension);

	return Ret;
}

#endif // _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
