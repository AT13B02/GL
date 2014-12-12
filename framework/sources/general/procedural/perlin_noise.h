//=============================================================================
//
// �p�[�����m�C�Y
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef _PERLINNOISE_H_
#define _PERLINNOISE_H_

//*****************************************************************************
// �p�[�����m�C�Y�N���X
//*****************************************************************************
class PerlinNoise
{
public:
	// �m�C�Y��ԕ��@
	enum InterpolationType
	{
		LINEAR_INTERPOLATION,  // ���`���
		COSINE_INTERPOLATION,  // �R�T�C�����
		MAX_INTERPOLATION,
	};

	PerlinNoise();

	~PerlinNoise();

	// �m�C�Y���d�˂鐔�ݒ�
	// �ʏ��6�B�����̏d���ɂ���Ă�4�Ȃǂ�
	void SetOctaves(s32 oct);

	// ���g���ݒ�
	// �����قǃm�C�Y���ׂ����Ȃ�
	// �Ⴂ�قǃm�C�Y���e���Ȃ�
	void SetFrequency(f32 freq);

	// Persistence�ݒ�
	// �����قǗאڂ����m�C�Y�ƒl�������Ȃ�
	// �Ⴂ�قǗאڂ����m�C�Y�ƒl���߂��Ȃ�
	void SetPersistence(f32 per);

	// ��ԕ��@�ݒ�
	void SetInterpolationType(InterpolationType type);

	// �V�[�h�l�ݒ�
	void SetSeed(s32 seed);

	// �m�C�Y�擾
	f32 GetNoise(f32 n) const;
	f32 GetNoise(f32 x, f32 y) const;

private:

	// �m�C�Y���
	f32 InterpolateNoise(f32 n) const;
	f32 InterpolateNoise(f32 x, f32 y) const;

	// �t�B���^���������m�C�Y
	f32 FilteredNoise(s32 n) const;
	f32 FilteredNoise(s32 x, s32 y) const;

	// ���`���
	f32 InterpolationLinear(f32 f0, f32 f1, f32 d) const;
	// �R�T�C�����
	f32 InterpolationCosine(f32 f0, f32 f1, f32 d) const;

	// �m�C�Y�W�F�l���[�^
	// -1.0 ^ 1.0�̕���������Ԃ�
	f32 RawPerlinNoise(s32 n) const;
	f32 RawPerlinNoise(s32 x, s32 y) const;

private:
	// �I�N�^�[�u��
	s32 octaves_;

	// ���g��
	f32 frequency_;

	// ����
	f32 persistence_;

	// �m�C�Y��ԕ��@
	InterpolationType interpolation_type_;

	// ��ԕ��@�e�[�u��
	static f32(PerlinNoise::*InterpolationTable[MAX_INTERPOLATION])(
		f32 /* ��Ԏn�_�l */,
		f32 /* ��ԏI�_�l*/,
		f32 /* ��ԌW��(0~1) */) const;

	// �V�[�h
	static s32 seed_;
};

#endif	// VG_GENERAL_PROCEDURAL_PERLINNOISE_H_

// EOF