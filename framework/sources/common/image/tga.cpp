//*****************************************************************************
//
// tga�t�@�C���֘A
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "tga.h"
#include <stdio.h>

//*****************************************************************************
// warning����
//*****************************************************************************
#pragma warning (disable : 4005)
#pragma warning (disable : 4996)

//*****************************************************************************
// �}�N����`
//*****************************************************************************
bool LoadTGAHeader(FILE* file,TGAHEADERFORMAT* tga_header_format);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// TGA�t�@�C���ǂݍ��ݏ���
//=============================================================================
bool LoadTGATexture(const s8* filename,IMAGE* out_image,bool convert_flag)
{
	COLOR4F* color;				// �F���
	TGAHEADERFORMAT tga_header_format;		// �w�b�_���
	int color_size = 0;				// �F���
	IMAGE image;
	IMAGE work;
	FILE* file = NULL;;

	file = fopen(filename,"rb");

	if(file == NULL)
	{
		return false;
	}

	// �w�b�_���̃��[�h
	LoadTGAHeader(file,&tga_header_format);

	// �F��񂪂���Ƃ���܂Ŕ��
	fseek(file,18,SEEK_SET);

	// �F��񐔂��擾
	color_size = tga_header_format._image_width * tga_header_format._image_height;

	// RGBA
	if(tga_header_format._bit_per_pixel == 32)
	{
		// �F�����쐬
		color = new COLOR4F[color_size];

		for(int i = 0;i < color_size;i++)
		{
			u8 work = 0;

			// B
			fread(&work,1,1,file);

			color[i]._blue = ((float)((int)(work))) / 255.0f;

			// G
			fread(&work,1,1,file);

			color[i]._green = ((float)((int)(work))) / 255.0f;

			// R
			fread(&work,1,1,file);

			color[i]._red = ((float)(((int)(work)))) / 255.0f;

			// A
			fread(&work,1,1,file);

			color[i]._alpha = ((float)((int)(work))) / 255.0f;

		}
	}
	// RGB
	else if(tga_header_format._bit_per_pixel == 24)
	{
		// �F�����쐬
		color = new COLOR4F[color_size];

		for(int i = 0;i < color_size;i++)
		{
			u8 work = 0;

			// B
			fread(&work,1,1,file);

			color[i]._blue = (float)((int)(work)) / 255.0f;

			// G
			fread(&work,1,1,file);

			color[i]._green = (float)((int)(work)) / 255.0f;

			// R
			fread(&work,1,1,file);

			color[i]._red = (float)((int)(work)) / 255.0f;

			// A
			color[i]._alpha = 1.0f;
		}
	}
	else
	{
		return false;
	}

	// �C���[�W�̉������i�[
	image._width = tga_header_format._image_width;

	// �C���[�W�̏c�����i�[
	image._height = tga_header_format._image_height;

	// �F�����i�[
	image._color = color;

	// �ϊ��t���O���m�F
	if(convert_flag)
	{
		if(tga_header_format._discnpter & 0x10)
		{
			// ���E�ϊ�
			FlipHorizontalImage(&work,image);
			delete[] image._color;
			image._color = work._color;
		}

		if(!(tga_header_format._discnpter & 0x20))
		{
			// �㉺�ϊ�
			FlipVerticalImage(&work,image);
			delete[] image._color;
			image._color = work._color;
		}
	}

	*out_image = image;

	return true;
}

//=============================================================================
// TGA�t�@�C���̃w�b�_�ǂݍ��ݏ���
//=============================================================================
bool LoadTGAHeader(FILE* file,TGAHEADERFORMAT* tga_header_format)
{
	// �t�@�C���̐擪�Ɉړ�
	fseek(file,0,SEEK_SET);

	// ID�̓ǂݍ���
	fread(&tga_header_format->_id,1,1,file);

	// �J���[�}�b�v�̓ǂݍ���
	fread(&tga_header_format->_color_map_type,1,1,file);

	// �C���[�W�^�C�v�̓ǂݍ���
	fread(&tga_header_format->_image_type,1,1,file);

	// �J���[�}�b�v�C���f�b�N�X�̓ǂݍ���
	fread(&tga_header_format->_color_map_index,2,1,file);

	// �J���[�}�b�v�����O�X�̓ǂݍ���
	fread(&tga_header_format->_color_map_length,2,1,file);
	fread(&tga_header_format->_color_map_size,1,1,file);
	fread(&tga_header_format->_image_orign_x,2,1,file);
	fread(&tga_header_format->_image_orign_y,2,1,file);
	fread(&tga_header_format->_image_width,2,1,file);
	fread(&tga_header_format->_image_height,2,1,file);
	fread(&tga_header_format->_bit_per_pixel,1,1,file);
	fread(&tga_header_format->_discnpter,1,1,file);

	return true;
}

//-----------------------------------EOF---------------------------------------
