//=============================================================================
//
// �e�N�X�`�����[�h���� [TextureLoader.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/22
//
// 2014/4/22 TGA�t�H�[�}�b�g��ǉ�
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "TextureLoader.h"
#include "Debug.h"
#include <stdio.h>

//*****************************************************************************
// �萔��`
//*****************************************************************************
// �e�N�X�`���C���[�W�t�H�[�}�b�g
enum IMAGE_FORMAT
{
	BMP = 0,	// �r�b�g�}�b�v
	TGA,		// TGA
	JPG,		// JPEG
	PNG,		// PNG
	TXO		// �Ǝ���`TXO�t�@�C��
};

//*****************************************************************************
// TGA�w�b�_��`
//*****************************************************************************
struct TGAHeader
{
	BYTE thFiled;		// �t�B�[���h��
	BYTE thColorMap;	// �J���[�}�b�v(0:�Ȃ�, 1:����)
	BYTE thImageFormat;	// �摜�`��(2:�t���J���[, 10:�t���J���[���������O�X���k)
	unsigned short thColorMapEntry;
	unsigned short thColorMapLength;
	BYTE thColorMapEntrySize;
	short thX;			// X���W(���Ɏg�����s��)
	short thY;			// Y���W(���Ɏg�����s��)
	unsigned short thWidth;	// �摜����
	unsigned short thHeight;// �摜�c��
	BYTE thColorDepth;	// �F�[�x
	BYTE thAttribute;	// 0~3:���� 4,5:�i�[���(�Ƃ���0���g���₷��)
};

//*****************************************************************************
// PNG�w�b�_��`
//*****************************************************************************
struct PNG_IHDR
{
	int ihLength;		// �`�����N�f�[�^�T�C�Y
	int ihChunkType;	// �`�����N�f�[�^�^�C�v
	int ihWidth;		// �f�[�^����
	int ihHeight;	// �f�[�^�c��
	BYTE ihDepth;		// �r�b�g�[�x
	BYTE ihColorType;		// �J���[�^�C�v
	BYTE ihCompressionMethod;// �f�[�^���k��@
	BYTE ihFilteringMethod;	// �t�B���^��@
	BYTE ihInterraceMethod;	// �C���^�[���[�X��@
	int ihCRC;			// ChunkType��ChunkData����Ɍv�Z����鉽��
};

//*****************************************************************************
// �v���g�^�C�v�֐�
//*****************************************************************************
// �摜�t�H�[�}�b�g�`�F�b�N
int CheckFormat(char* pFormatName);
// �r�b�g�}�b�v�`�F�b�N
BOOL IsBitmap(char* pFormatName);
// TGA�`�F�b�N
BOOL IsTGA(char* pFormatName);
// JPEG�`�F�b�N
BOOL IsJPEG(char* pFormatName);
// PNG�`�F�b�N
BOOL IsPNG(char* pFormatName);
// TXO�`�F�b�N
BOOL IsTXO(char* pFormatName);

// �r�b�g�}�b�v���[�h
BOOL LoadBitmapFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// TGA���[�h
BOOL LoadTGAFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// JPEG���[�h
BOOL LoadJPEGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// PNG���[�h
BOOL LoadPNGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);
// TXO���[�h
BOOL LoadTXOFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight);

//*****************************************************************************
// �֐��|�C���^
//*****************************************************************************
// ���[�_�e�[�u��
BOOL (*TexLoader[])(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight) =
{
	LoadBitmapFromFile,	// Bitmap
	LoadTGAFromFile,	// TGA
	LoadJPEGFromFile,	// JPEG
	LoadPNGFromFile,	// PNG
	LoadTXOFromFile	// TXO
};

//=============================================================================
// �e�N�X�`�����[�h����
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: BOOL		���� : TRUE
//						���s : FALSE
// arg1		: char*		�e�N�X�`����
// arg2		: char**	�e�N�X�`���f�[�^�ւ̃|�C���^
// arg3		: unsigned short*	�e�N�X�`�������ւ̃|�C���^
// arg4		: unsigned short*	�e�N�X�`���c���ւ̃|�C���^
//=============================================================================
BOOL LoadTexture(const char* pTexName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	// �摜�t�H�[�}�b�g
	int nFormat = -1;

	// �e�N�X�`�������
	for(int i = 0; pTexName[i] != '\0'; i++)
	{
		// �g���q�̃h�b�g(.)�𔭌�
		if(pTexName[i] == '.')
		{
			// ��ɑ����g���q�𒲂ׂ�
			nFormat = CheckFormat((char*)&pTexName[i + 1]);
			// ���[�v�𔲂���
			break;
		}
	}

	// �Y������t�H�[�}�b�g�����݂��Ȃ�����
	if(nFormat == -1)
	{
		// �G���[��Ԃ�
		return FALSE;
	}

	// �g���q����ǂݍ��ݕ��@��ω�������
	if(!(*TexLoader[nFormat])(pTexName, ppTex, pWidth, pHeight))
	{
		// �e�N�X�`���̓ǂݍ��݂Ɏ��s
		_AssertExpr(0, "�e�N�X�`���̓ǂݍ��݂Ɏ��s");
		return FALSE;
	}

	// �ǂݍ��ݐ���
	return TRUE;
}

//=============================================================================
// �e�N�X�`���J������
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: void
// arg1		: char*		�e�N�X�`����
// arg2		: char**	�e�N�X�`���f�[�^�ւ̃|�C���^
//=============================================================================
void DeleteTexture(unsigned char** ppTex)
{
	// �e�N�X�`���f�[�^�J��
	delete[] (*ppTex);
}

//============================================================================
// �摜�t�H�[�}�b�g�`�F�b�N
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : �Y�������t�H�[�}�b�g�萔��Ԃ�
//						���s : -1��Ԃ�
// arg1		: char*		�t�H�[�}�b�g��
//=============================================================================
int CheckFormat(char* pFormatName)
{
	// Bitmap�������ꍇ
	if(IsBitmap(pFormatName))
	{
		// Bitmap�t�H�[�}�b�g�萔��Ԃ�
		return BMP;
	}
	// TGA�������ꍇ
	if(IsTGA(pFormatName))
	{
		// Bitmap�t�H�[�}�b�g�萔��Ԃ�
		return TGA;
	}
	// JPEG�������ꍇ
	else if(IsJPEG(pFormatName))
	{
		// JPEG�t�H�[�}�b�g�萔��Ԃ�
		return JPG;
	}
	// PNG�������ꍇ
	else if(IsPNG(pFormatName))
	{
		// PNG�t�H�[�}�b�g�萔��Ԃ�
		return PNG;
	}
	// TXO�������ꍇ
	else if(IsTXO(pFormatName))
	{
		return TXO;
	}
	// �ǂ�ɂ��Y�����Ȃ��ꍇ
	else
	{
		_AssertExpr(0, "�\�����Ȃ��t�@�C���t�H�[�}�b�g���w�肳��܂���");
	}

	// �G���[��Ԃ�
	return -1;
}

//============================================================================
// �r�b�g�}�b�v�`�F�b�N
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : �Y�������t�H�[�}�b�g�萔��Ԃ�
//						���s : -1��Ԃ�
// arg1		: char*		�t�H�[�}�b�g��
//=============================================================================
BOOL IsBitmap(char* pFormatName)
{
	// �t�H�[�}�b�g������v
	if( pFormatName[0] == 'b' &&
		pFormatName[1] == 'm' &&
		pFormatName[2] == 'p' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// ��v���Ȃ������Ƃ�
	return FALSE;
}

//============================================================================
// TGA�`�F�b�N
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/22
//
// ret		: int		���� : �Y�������t�H�[�}�b�g�萔��Ԃ�
//						���s : -1��Ԃ�
// arg1		: char*		�t�H�[�}�b�g��
//=============================================================================
BOOL IsTGA(char* pFormatName)
{
	// �t�H�[�}�b�g������v
	if( pFormatName[0] == 't' &&
		pFormatName[1] == 'g' &&
		pFormatName[2] == 'a' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// ��v���Ȃ������Ƃ�
	return FALSE;
}

//============================================================================
// JPEG�`�F�b�N
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : �Y�������t�H�[�}�b�g�萔��Ԃ�
//						���s : -1��Ԃ�
// arg1		: char*		�t�H�[�}�b�g��
//=============================================================================
BOOL IsJPEG(char* pFormatName)
{
	// �t�H�[�}�b�g������v
	if( pFormatName[0] == 'j' &&
		pFormatName[1] == 'p' &&
		pFormatName[2] == 'g' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// ��v���Ȃ������Ƃ�
	return FALSE;
}

//============================================================================
// PNG�`�F�b�N
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : �Y�������t�H�[�}�b�g�萔��Ԃ�
//						���s : -1��Ԃ�
// arg1		: char*		�t�H�[�}�b�g��
//=============================================================================
BOOL IsPNG(char* pFormatName)
{
	// �t�H�[�}�b�g������v
	if( pFormatName[0] == 'p' &&
		pFormatName[1] == 'n' &&
		pFormatName[2] == 'g' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// ��v���Ȃ������Ƃ�
	return FALSE;
}

//============================================================================
// TXO�`�F�b�N
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//
// ret		: int		���� : �Y�������t�H�[�}�b�g�萔��Ԃ�
//						���s : -1��Ԃ�
// arg1		: char*		�t�H�[�}�b�g��
//=============================================================================
BOOL IsTXO(char* pFormatName)
{
	// �t�H�[�}�b�g������v
	if( pFormatName[0] == 't' &&
		pFormatName[1] == 'x' &&
		pFormatName[2] == 'o' &&
		pFormatName[3] == '\0')
	{
		return TRUE;
	}

	// ��v���Ȃ������Ƃ�
	return FALSE;
}

//============================================================================
// �r�b�g�}�b�v���[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : TRUE
//						���s : FALSE
// arg1		: char*		�t�@�C����
// arg2		: char**	�e�N�X�`���|�C���^
//=============================================================================
BOOL LoadBitmapFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	// �r�b�g�}�b�v�t�@�C���w�b�_
	BITMAPFILEHEADER bmfh;
	// �r�b�g�}�b�v�C���t�H�w�b�_
	BITMAPINFOHEADER bmih;

	// �t�@�C���|�C���^
	FILE *pFile = NULL;

	// �t�@�C���I�[�v��
	pFile = fopen(pFileName, "rb");

	// �t�@�C�����k��
	if(!pFile)
	{
		_AssertExpr(pFile, "BMP�t�@�C�����J���܂���");
		return FALSE;
	}

	// �t�@�C���w�b�_�ǂݍ���
	fread(&bmfh, sizeof(BITMAPFILEHEADER), 1, pFile);
	// �C���t�H�w�b�_�ǂݍ���
	fread(&bmih, sizeof(BITMAPINFOHEADER), 1, pFile);

	// �摜�T�C�Y�擾
	int nImgWidth = bmih.biWidth;
	int nImgHeight = bmih.biHeight;

	// �T�C�Y�R�s�[
	*pWidth = nImgWidth;
	*pHeight = nImgHeight;

	// 1���C��������̃o�C�g��
	int nLine = nImgWidth * 4;	// rgba��4�o�C�g���Ă����O��

	// �o�b�t�@�m��
	(*ppTex) = new unsigned char[nImgHeight * nLine];
	_AssertExpr((*ppTex), "BMP�e�N�X�`���p�o�b�t�@�̊m�ۂɎ��s");

	// �摜�f�[�^�ǂݍ���
	char b = 0;
	char g = 0;
	char r = 0;
	for(int y = nImgHeight - 1; y >= 0; y--)
	{
		for(int x = 0; x < nLine; x += 4)
		{
			fread(&b, 1, 1, pFile);
			fread(&g, 1, 1, pFile);
			fread(&r, 1, 1, pFile);
			ppTex[0][y * nLine + x    ] = r;
			ppTex[0][y * nLine + x + 1] = g;
			ppTex[0][y * nLine + x + 2] = b;
			ppTex[0][y * nLine + x + 3] = 0xff;
		}
	}

	// �t�@�C���N���[�Y
	fclose(pFile);

	return TRUE;
}

//============================================================================
// TGA���[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/22
//
// ret		: int		���� : TRUE
//						���s : FALSE
// arg1		: char*		�t�@�C����
// arg2		: char**	�e�N�X�`���|�C���^
//=============================================================================
BOOL LoadTGAFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	// TGA�t�@�C���w�b�_
	TGAHeader tga;
	// �t�@�C���|�C���^
	FILE *pFile;

	// �t�@�C���I�[�v��
	pFile = fopen(pFileName, "rb");

	// �t�@�C�����J���Ȃ������Ƃ�
	if(!pFile)
	{
		return FALSE;
	}

	// �w�b�_��񒆂̐擪12�o�C�g���R�s�[
	fread(&tga, 12, 1, pFile);

	// �c���Ɖ����̎擾
	fread(&tga.thWidth, 2, 1, pFile);
	fread(&tga.thHeight, 2, 1, pFile);
	*pWidth = tga.thWidth;
	*pHeight = tga.thHeight;

	// �w�b�_�̍Ō�̕�����ǂݍ���
	fread(&tga.thColorDepth, 1, 1, pFile);
	fread(&tga.thAttribute, 1, 1, pFile);
	
	// 1���C��������̃o�C�g��
	int nLine = tga.thWidth * 4;	// rgba��4�o�C�g���Ă����O��

	// �o�b�t�@�m��
	(*ppTex) = new unsigned char[tga.thHeight * nLine];
	_AssertExpr((*ppTex), "TGA�e�N�X�`���p�o�b�t�@�̊m�ۂɎ��s");
	
	// ���[�v�����ϐ�
	int nLoopIncrement = 1;
	// �ŏ��A�ő�
	int nStart = 0;
	int nEnd = tga.thHeight;

	// �ォ�牺�ɓǂݍ���
	if(tga.thAttribute & 0x20)
	{
		nLoopIncrement = 1;
		nStart = 0;
		nEnd = tga.thHeight;
	}
	// �������ɓǂݍ���
	else
	{
		nLoopIncrement = -1;
		nStart = tga.thHeight - 1;
		nEnd = -1;
	}

	// �摜�f�[�^�ǂݍ���
	// �F�[�x��24�r�b�g�̂Ƃ�
	if(tga.thColorDepth == 24)
	{
		struct bgr
		{
			BYTE b, g, r;
		};
		bgr bgrColor;

		// ���[�v����
		for(int y = nStart; y != nEnd; y += nLoopIncrement)
		{
			for(int x = 0; x < nLine; x += 4)
			{
				fread(&bgrColor, sizeof(bgr), 1, pFile);
				ppTex[0][y * nLine + x    ] = bgrColor.r;
				ppTex[0][y * nLine + x + 1] = bgrColor.g;
				ppTex[0][y * nLine + x + 2] = bgrColor.b;
				ppTex[0][y * nLine + x + 3] = 0xFF;
			}
		}
	}
	// �F�[�x��32�r�b�g�̂Ƃ�
	else if(tga.thColorDepth == 32)
	{
		struct bgra
		{
			BYTE b, g, r, a;
		};
		bgra color;

		for(int y = nStart; y != nEnd; y += nLoopIncrement)
		{
			for(int x = 0; x < nLine; x += 4)
			{
				fread(&color, sizeof(bgra), 1, pFile);
				ppTex[0][y * nLine + x    ] = color.r;
				ppTex[0][y * nLine + x + 1] = color.g;
				ppTex[0][y * nLine + x + 2] = color.b;
				ppTex[0][y * nLine + x + 3] = color.a;
			}
		}
	}
	else
	{
		_AssertExpr(0, "�L���ȐF�[�x�ł͂���܂���");
		return FALSE;
	}

	// �t�@�C���N���[�Y
	fclose(pFile);

	return TRUE;
}

//============================================================================
// JPEG���[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : TRUE
//						���s : FALSE
// arg1		: char*		�t�@�C����
// arg2		: char**	�e�N�X�`���|�C���^
//=============================================================================
BOOL LoadJPEGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	return TRUE;
}

//============================================================================
// PNG���[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/4/21
//
// ret		: int		���� : TRUE
//						���s : FALSE
// arg1		: char*		�t�@�C����
// arg2		: char**	�e�N�X�`���|�C���^
//=============================================================================
BOOL LoadPNGFromFile(const char *pFileName, unsigned char** ppTex, unsigned short* pWidth, unsigned short* pHeight)
{
	_AssertExpr(0, "PNG�t�@�C���̓T�|�[�g����Ă��܂���");
	// PNG�t�@�C���̃o�C�g�I�[�_�[�̓r�b�O�G���f�B�A��
	PNG_IHDR png;

	// �t�@�C���|�C���^
	FILE *pFile;
	// �t�@�C���I�[�v��
	pFile = fopen(pFileName, "rb");
	if(!pFile)
	{
		return FALSE;
	}

	// �V�O�l�`���ǂݍ���
	BYTE sig[8];
	fread(sig, 8, 1, pFile);

	// �w�b�_�ǂݍ���
	fread(&png, 16, 1, pFile);
	fread(&png.ihDepth, 1, 1, pFile);
	fread(&png.ihColorType, 1, 1, pFile);
	fread(&png.ihCompressionMethod, 1, 1, pFile);
	fread(&png.ihFilteringMethod, 1, 1, pFile);
	fread(&png.ihInterraceMethod, 1, 1, pFile);
	fread(&png.ihCRC, 4, 1, pFile);
	png.ihLength = (png.ihLength >> 24) + (((png.ihLength >> 16) & 0xff) << 8) + (((png.ihLength >> 8) & 0xff) << 16) + ((png.ihLength & 0xff) << 24);
	png.ihChunkType = (png.ihChunkType >> 24) + (((png.ihChunkType >> 16) & 0xff) << 8) + (((png.ihChunkType >> 8) & 0xff) << 16) + ((png.ihChunkType & 0xff) << 24);
	png.ihWidth = (png.ihWidth >> 24) + (((png.ihWidth >> 16) & 0xff) << 8) + (((png.ihWidth >> 8) & 0xff) << 16) + ((png.ihWidth & 0xff) << 24);
	png.ihHeight = (png.ihHeight >> 24) + (((png.ihHeight >> 16) & 0xff) << 8) + (((png.ihHeight >> 8) & 0xff) << 16) + ((png.ihHeight & 0xff) << 24);
	png.ihCRC = (png.ihCRC >> 24) + (((png.ihCRC >> 16) & 0xff) << 8) + (((png.ihCRC >> 8) & 0xff) << 16) + ((png.ihCRC & 0xff) << 24);
	
	// �摜�T�C�Y�ݒ�
	*pWidth = png.ihWidth;
	*pHeight = png.ihHeight;

	// �C���[�W�f�[�^�T�C�Y
	int imgDatSize;
	// �C���[�W�f�[�^�`�����N�^�C�v
	int imgChunkType;
	fread(&imgDatSize, 4, 1, pFile);
	fread(&imgChunkType, 4, 1, pFile);
	imgDatSize = (imgDatSize >> 24) + (((imgDatSize >> 16) & 0xff) << 8) + (((imgDatSize >> 8) & 0xff) << 16) + ((imgDatSize & 0xff) << 24);
	imgChunkType = (imgChunkType >> 24) + (((imgChunkType >> 16) & 0xff) << 8) + (((imgChunkType >> 8) & 0xff) << 16) + ((imgChunkType & 0xff) << 24);

	// 1���C��������̃o�C�g��
	int nLine = png.ihWidth * 4;	// rgba��4�o�C�g���Ă����O��

	// �o�b�t�@�m��
	(*ppTex) = new unsigned char[png.ihHeight * nLine];

	// �J���[�^�C�v�ɂ���ēǂݍ��ޑ傫����ς���
	// RGB
	if(png.ihColorType == 2)
	{
		struct rgb
		{
			BYTE r, g, b;
		};
		rgb color;
		for(int y = 0; y < png.ihHeight; y++)
		{
			for(int x = 0; x < nLine; x += 4)
			{
				fread(&color, 3, 1, pFile);
				ppTex[0][y * nLine + x    ] = color.r;
				ppTex[0][y * nLine + x + 1] = color.g;
				ppTex[0][y * nLine + x + 2] = color.b;
				ppTex[0][y * nLine + x + 3] = 0xff;
			}
		}
	}
	// RGBA
	else if(png.ihColorType == 6)
	{
		fread(*ppTex, nLine * png.ihHeight, 1, pFile);
	}
	else
	{
		return FALSE;
	}

	// �t�@�C���N���[�Y
	fclose(pFile);

	return TRUE;
}

//============================================================================
// TXO���[�h
// Author : Ryo Kobayashi
// LastUpdate : 2014/11/18
//
// ret		: int		���� : TRUE
//						���s : FALSE
// arg1		: char*		�t�@�C����
// arg2		: char**	�e�N�X�`���|�C���^
//=============================================================================
BOOL LoadTXOFromFile(const char *filename_pointer, unsigned char** texture_double_pointer, unsigned short* width_pointer, unsigned short* height_pointer)
{
	// �t�@�C���|�C���^
	FILE *file = nullptr;
	// �t�@�C���I�[�v��
	fopen_s(&file, filename_pointer, "rb");
	if(!file)
	{
		return FALSE;
	}

	// ���ǂݍ���
	fread(width_pointer, sizeof(unsigned short), 1, file);
	fread(height_pointer, sizeof(unsigned short), 1, file);
	// �o�b�t�@����
	unsigned bufferSize = (*width_pointer) * (*height_pointer) * 4;
	(*texture_double_pointer) = new unsigned char[bufferSize];
	fread((*texture_double_pointer), bufferSize, 1, file);

	fclose(file);

	return TRUE;
}

// EOF