//=============================================================================
//
// �p�[�����m�C�Y [PerlinNoise.h]
// Author : Ryo Kobayashi
//
//=============================================================================

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include "perlin_noise.h"
#include <math.h>

//*****************************************************************************
// �֐��e�[�u��
//*****************************************************************************
// ��ԏ����e�[�u��
f32 (PerlinNoise::*PerlinNoise::InterpolationTable[MAX_INTERPOLATION])(f32, f32, f32) =
{
  &InterpolationLinear,
  &InterpolationCosine
};

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************
// �����V�[�h
s32 PerlinNoise::seed_ = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
PerlinNoise::PerlinNoise() :
  octaves_(6),
  frequency_(0.008f),
  persistence_(0.5f),
  interpolation_type_(COSINE_INTERPOLATION)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
PerlinNoise::~PerlinNoise()
{

}

//=============================================================================
// �I�N�^�[�u���ݒ�
//=============================================================================
void PerlinNoise::SetOctaves(s32 oct)
{
  octaves_ = oct;
}

//=============================================================================
// ���g���ݒ�
//=============================================================================
void PerlinNoise::SetFrequency(f32 freq)
{
  frequency_ = freq;
}

//=============================================================================
// Persistence�ݒ�
//=============================================================================
void PerlinNoise::SetPersistence(f32 per)
{
  persistence_ = per;
}

//=============================================================================
// ��ԕ��@�ݒ�
//=============================================================================
void PerlinNoise::SetInterpolationType(InterpolationType type)
{
  interpolation_type_ = type;
}

//=============================================================================
// �V�[�h�l�ݒ�
//=============================================================================
void PerlinNoise::SetSeed(s32 seed)
{
  this->seed_ = seed;
}

//=============================================================================
// �m�C�Y�擾
//=============================================================================
f32 PerlinNoise::GetNoise(f32 n) const
{
  f32 sum = 0;
  f32 amplitude = 1;
  f32 tempFreq = frequency_;

  for(s32 i = 0; i < octaves_; i++)
  {
    sum += InterpolateNoise(n * tempFreq) * amplitude;

    // ���g��2�{
    tempFreq *= 2;
    // �g�̍���
    amplitude *= persistence_;
  }

  return sum;
}

//=============================================================================
// �m�C�Y�擾
//=============================================================================
f32 PerlinNoise::GetNoise(f32 x, f32 y) const
{
  f32 sum = 0;
  f32 amplitude = 1;
  f32 tempFreq = frequency_;

  for(s32 i = 0; i < octaves_; i++)
  {
    sum += InterpolateNoise(x * tempFreq, y * tempFreq) * amplitude;

    // ���g��2�{
    tempFreq *= 2;
    // �g�̍���
    amplitude *= persistence_;
  }

  return sum;
}

//=============================================================================
// �m�C�Y���
//=============================================================================
f32 PerlinNoise::InterpolateNoise(f32 n) const
{
  s32 intN = (s32)n;
  f32 fractionN = n - intN;

  f32 f0, f1;

  f0 = FilteredNoise(intN);
  f1 = FilteredNoise(intN + 1);

  return (this->*InterpolationTable[interpolation_type_])(f0, f1, fractionN);
}

//=============================================================================
// �m�C�Y���
//=============================================================================
f32 PerlinNoise::InterpolateNoise(f32 x, f32 y) const
{
  s32 intX = (s32)x;
  f32 fractionX = x - intX;

  s32 intY = (s32)y;
  f32 fractionY = y - intY;

  f32 f0, f1;

  f0 = (this->*InterpolationTable[interpolation_type_])(
    FilteredNoise(intX, intY),
    FilteredNoise(intX + 1, intY),
    fractionX);
  f1 = (this->*InterpolationTable[interpolation_type_])(
    FilteredNoise(intX, intY + 1),
    FilteredNoise(intX + 1, intY + 1),
    fractionX);

  return (this->*InterpolationTable[interpolation_type_])(f0, f1, fractionY);
}

//=============================================================================
// �m�C�Y�t�B���^
//=============================================================================
f32 PerlinNoise::FilteredNoise(s32 n) const
{
  return (RawPerlinNoise(n) / 2 + (RawPerlinNoise(n - 1) + RawPerlinNoise(n + 1)) / 4);
}

//=============================================================================
// �m�C�Y�t�B���^
//=============================================================================
f32 PerlinNoise::FilteredNoise(s32 x, s32 y) const
{
  // 3x3�K�E�V�A���t�B���^
  f32 n = RawPerlinNoise(x, y) / 4;
  n += (RawPerlinNoise(x - 1, y) +
    RawPerlinNoise(x, y - 1) +
    RawPerlinNoise(x + 1, y) +
    RawPerlinNoise(x, y + 1)) / 8;
  n += (RawPerlinNoise(x - 1, y - 1) +
    RawPerlinNoise(x + 1, y - 1) +
    RawPerlinNoise(x - 1, y + 1) +
    RawPerlinNoise(x + 1, y + 1)) / 16;

  return n;
}

//=============================================================================
// �l�̕��(���`)
//=============================================================================
f32 PerlinNoise::InterpolationLinear(f32 f0, f32 f1, f32 d) const
{
  // ���`���
  return (f0 * (1.0f - d) + f1 * d);
}

//=============================================================================
// �l�̕��(�R�T�C��)
//=============================================================================
f32 PerlinNoise::InterpolationCosine(f32 f0, f32 f1, f32 d) const
{
  // �R�T�C�����
  f32 rad = d * 3.1415926535f;
  d = (1.0f - cosf(rad)) * 0.5f;	// 0 ~ 1
  return (f0 * (1.0f - d) + f1 * d);
}

//=============================================================================
// �m�C�Y�W�F�l���[�^	
// -1.0 ^ 1.0�̕���������Ԃ�
//=============================================================================
f32 PerlinNoise::RawPerlinNoise(s32 n) const
{
  n += seed_;

  n = (n << 13) ^ n;

  s32 noise = (n * (n * n * 15731 + 122033) + 1376312589) & 0x7fffffff;

  return 1.0f - ((f32)noise / 1073741824.0f);
}

//=============================================================================
// �m�C�Y�W�F�l���[�^	
// -1.0 ^ 1.0�̕���������Ԃ�
//=============================================================================
f32 PerlinNoise::RawPerlinNoise(s32 x, s32 y) const
{
  s32 n = seed_ + x + y * 2677;

  n = (n << 13) ^ n;

  s32 noise = (n * (n * n * 15731 + 122033) + 1376312589) & 0x7fffffff;

  return 1.0f - ((f32)noise / 1073741824.0f);
}

// EOF