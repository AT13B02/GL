//*****************************************************************************
//
// �C���[�W�f�[�^�֘A
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "common/image/image.h"

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
// ���E���]����
//=============================================================================
void FlipVerticalImage(IMAGE* out_image,const IMAGE& in_image)
{
	s32 width = 0;
	s32 height = 0;

	// �T�C�Y�̎擾
	width = in_image._width;
	height = in_image._height;

	out_image->_width = width;
	out_image->_height = height;
	out_image->_color = new COLOR4F[width * height];

	for(s32 i = 0;i < height;++i)
	{
		for(s32 j = 0;j < width;++j)
		{
			out_image->_color[i * width + j] = in_image._color[(height - i - 1) * width + j];
		}
	}
}

//=============================================================================
// ���E���]����
//=============================================================================
void FlipHorizontalImage(IMAGE* out_image,const IMAGE& in_image)
{
	s32 width;
	s32 height;

	// �T�C�Y�̎擾
	width = in_image._width;
	height = in_image._height;

	out_image->_width = width;
	out_image->_height = height;
	out_image->_color = new COLOR4F[width * height];

	for(s32 i = 0;i < height;++i)
	{
		for(s32 j = 0;j < width;++j)
		{
			out_image->_color[i * width + j] = in_image._color[i * width + (width - j - 1)];
		}
	}
}

//=============================================================================
// IMAGE����unsigned char�֕ϊ�����
//=============================================================================
u8* ConvertCharFromImage(const IMAGE& image)
{
	s32 image_size;
	u8* out;

	image_size = image._width * image._height;

	out = new u8[image_size * 4];

	for(s32 i = 0;i < image_size;i++)
	{
		(out)[i * 4 + 0] = (s8)((s32)(image._color[i]._red   * 255));
		(out)[i * 4 + 1] = (s8)((s32)(image._color[i]._green * 255));
		(out)[i * 4 + 2] = (s8)((s32)(image._color[i]._blue  * 255));
		(out)[i * 4 + 3] = (s8)((s32)(image._color[i]._alpha) * 255);
	}

	return out;
}

//-----------------------------------EOF---------------------------------------
