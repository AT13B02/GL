//*****************************************************************************
//
// 3D頂点クラス
//
// Author		: Tomohiro Kouno
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	2D頂点クラス
*
*	// 使い方
*	Create関数でインスタンスの生成を行う
*	Init関数で初期化
*	Lock関数で頂点情報の格納開始し、頂点バッファのポインタを取得
*	Unlock関数で頂点情報の格納終了(頂点バッファの格納をここでやるので、これを呼ばないと反映されない)
*	Draw関数で描画
*
*/
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _VERTEX_2D_H_
#define _VERTEX_2D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"

// common
#include "common/image/color/color4f.h"
#include "common/math/math.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CVertex2D : public CBasic
{
public:
	typedef struct _VERTEX_2D
	{
		VECTOR2* _position;
		COLOR4F* _color;
		VECTOR2* _texcoord;
	}VERTEX_2D;

	typedef struct _VERTEX_2D_INDEX
	{
		u32* _position;
		u32* _color;
		u32* _texcoord;
	}VERTEX_2D_INDEX;

	// 作成処理
	static CVertex2D* Create(CDeviceHolder* device_holder,const u32& vertex_2d_number);

	// 作成処理
	static CVertex2D* Create(CDeviceHolder* device_holder,const u32& position_number,const u32& color_number,const u32& texcoord_number);

	// デストラクタ
	virtual ~CVertex2D(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(const MATRIX4x4& matrix);

	// 描画処理
	virtual void Draw(const MATRIX4x4& matrix,const u32& offset,const u32 length) = 0;

	// 終了処理
	virtual void Uninit(void);

	// インデックスの作成
	void CreateIndex(const s32& index_number);

	// ロック処理
	void Lock(VERTEX_2D** vertex_2d,VERTEX_2D_INDEX** vertex_2d_index);

	// 解除処理
	virtual void Unlock(void) = 0;

protected:
	// コンストラクタ
	CVertex2D(CDeviceHolder* device_holder,const u32& position_number,const u32& color_number,const u32& texcoord_number);

	CDeviceHolder* device_holder_;
	VERTEX_2D vertex_2d_;
	u32 position_number_;
	u32 normal_number_;
	u32 color_number_;
	u32 texcoord_number_;
	u32 primitive_number_;
	u32 index_number_;
	VERTEX_2D_INDEX vertex_2d_index_;
	bool use_index_;
private:

};

#endif	// _VERTEX_2D_H_

//---------------------------------- EOF --------------------------------------
