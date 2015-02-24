//=============================================================================
//
// パーリンノイズ
// Author : Ryo Kobayashi
//
//=============================================================================
#pragma once
#ifndef _PERLINNOISE_H_
#define _PERLINNOISE_H_

//*****************************************************************************
// パーリンノイズクラス
//*****************************************************************************
class PerlinNoise
{
public:
	// ノイズ補間方法
	enum InterpolationType
	{
		LINEAR_INTERPOLATION,  // 線形補間
		COSINE_INTERPOLATION,  // コサイン補間
		MAX_INTERPOLATION,
	};

	PerlinNoise();

	~PerlinNoise();

	// ノイズを重ねる数設定
	// 通常は6。処理の重さによっては4なども
	void SetOctaves(s32 oct);

	// 周波数設定
	// 高いほどノイズが細かくなる
	// 低いほどノイズが粗くなる
	void SetFrequency(f32 freq);

	// Persistence設定
	// 高いほど隣接したノイズと値が遠くなる
	// 低いほど隣接したノイズと値が近くなる
	void SetPersistence(f32 per);

	// 補間方法設定
	void SetInterpolationType(InterpolationType type);

	// シード値設定
	void SetSeed(s32 seed);

	// ノイズ取得
	f32 GetNoise(f32 n) const;
	f32 GetNoise(f32 x, f32 y) const;

private:

	// ノイズ補間
	f32 InterpolateNoise(f32 n) const;
	f32 InterpolateNoise(f32 x, f32 y) const;

	// フィルタをかけたノイズ
	f32 FilteredNoise(s32 n) const;
	f32 FilteredNoise(s32 x, s32 y) const;

	// 線形補間
	f32 InterpolationLinear(f32 f0, f32 f1, f32 d) const;
	// コサイン補間
	f32 InterpolationCosine(f32 f0, f32 f1, f32 d) const;

	// ノイズジェネレータ
	// -1.0 ^ 1.0の浮動小数を返す
	f32 RawPerlinNoise(s32 n) const;
	f32 RawPerlinNoise(s32 x, s32 y) const;

private:
	// オクターブ数
	s32 octaves_;

	// 周波数
	f32 frequency_;

	// 高さ
	f32 persistence_;

	// ノイズ補間方法
	InterpolationType interpolation_type_;

	// 補間方法テーブル
	static f32(PerlinNoise::*InterpolationTable[MAX_INTERPOLATION])(
		f32 /* 補間始点値 */,
		f32 /* 補間終点値*/,
		f32 /* 補間係数(0~1) */) const;

	// シード
	static s32 seed_;
};

#endif	// VG_GENERAL_PROCEDURAL_PERLINNOISE_H_

// EOF