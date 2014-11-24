//*****************************************************************************
//
// 3D頂点クラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	3D頂点クラス
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

#ifndef _VERTEX_3D_H_
#define _VERTEX_3D_H_

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
class CVertex3D : public CBasic
{
public:
	typedef struct _VERTEX_3D
	{
		VECTOR3* _position;
		VECTOR3* _normal;
		COLOR4F* _color;
		VECTOR2* _texcoord;
	}VERTEX_3D;

	typedef struct _VERTEX_3D_INDEX
	{
		u32* _position;
		u32* _normal;
		u32* _color;
		u32* _texcoord;
	}VERTEX_3D_INDEX;

	// 作成処理
	static CVertex3D* Create(CDeviceHolder* device_holder,const u32& vertex_3d_number);

	// 作成処理
	static CVertex3D* Create(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number);

	// デストラクタ
	virtual ~CVertex3D(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	virtual void Draw(const MATRIX4x4& matrix) = 0;

	// 終了処理
	virtual void Uninit(void);

	// ロック処理
	void Lock(VERTEX_3D** vertex_3d,VERTEX_3D_INDEX** vertex_3d_index);

	// 解除処理
	virtual void Unlock(void) = 0;

protected:
	// コンストラクタ
	CVertex3D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number);

	CDeviceHolder* device_holder_;
	VERTEX_3D vertex_3d_;
	u32 position_number_;
	u32 normal_number_;
	u32 color_number_;
	u32 texcoord_number_;
	u32 primitive_number_;
	u32 index_number_;
	VERTEX_3D_INDEX* vertex_3d_index_;

private:

};

#endif	// _VERTEX_3D_H_

//---------------------------------- EOF --------------------------------------
