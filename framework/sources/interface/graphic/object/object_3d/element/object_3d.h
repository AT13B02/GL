//*****************************************************************************
//
// オブジェクト3Dクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _OBJECT_3D_H_
#define _OBJECT_3D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/object/object.h"

// common
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
class CDeviceHolder;
class CObject3DData;
class CModel;
class CVertex3D;
class CTexture;
class CRenderstate;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject3D : public CObject
{
public:
	enum OBJECT_3D_TYPE
	{
		OBJECT_3D_TYPE_RECTANGLE = 0,
		OBJECT_3D_TYPE_BILLBOARD,
		OBJECT_3D_TYPE_OBJECT_MODEL,
		OBJECT_3D_TYPE_MAX
	};

	// コンストラクタ
	CObject3D(CDeviceHolder* device_holder,OBJECT_3D_TYPE type);

	// デストラクタ
	virtual ~CObject3D(void);

	// 描画処理
	virtual void Draw(CObject3DData* pObject3DData) = 0;

	// 描画処理
	void Draw(const MATRIX4x4& Matrix,CVertex3D* pVertex3D,CTexture* pTexture,CRenderstate* pRenderstate);

	// 描画処理
	void Draw(const MATRIX4x4& matrix,CModel* model,CRenderstate* renderstate);

	// 設定処理
	virtual void Set(void) = 0;

protected:
	MATRIX4x4 GetWorldMatrix(CObject3DData* pObject3DData);
	CDeviceHolder* device_holder_;

private:
	OBJECT_3D_TYPE object_3d_type_;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
