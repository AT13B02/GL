//*****************************************************************************
//
// オブジェクト2Dマネージャークラス [object_2d_manager.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/09/13(Sat)
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _OBJECT_2D_MANAGER_H_
#define _OBJECT_2D_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// stl
#include <list>

// basic
#include "basic/basic.h"

// math
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
class CObject2D;
class CObject2DList;
class CObject2DBuffer;

class CTexture;
class CDeviceHolder;

class CRenderstate;
class CRenderstateManager;

class CCameraManager;
class CLightManager;
class CModelManager;
class CTextureManager;


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject2DManager : public CBasic
{
public:
	// コンストラクタ
	CObject2DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager);

	// デストラクタ
	~CObject2DManager(void);

	// 初期化
	bool Init(void);

	// 描画処理
	void Draw(void);

	// 終了
	void Uninit(void);


	// リストに追加
	u32 AddList(CObject2D* object_2d);

	//-----------------------------------------------------
	// 描画リストに保存
	void Draw(const u32& object_key,const VECTOR2& position,const float rotation,const VECTOR2& scale,MATRIX4x4 matrix,const std::string& texture_name,CRenderstate* renderstate);

private:

	// オブジェクトリスト
	CObject2DList* object_2d_list_;

	// バッファリスト
	CObject2DBuffer* object_2d_buffer_;

	// デバイスホルダー
	CDeviceHolder* device_holder_;

	// レンダーステートマネージャー
	CRenderstateManager* renderstate_manager_;

	// テクスチャマネージャー
	CTextureManager* texture_manager_;

	// カメラマネージャー
	CCameraManager* camera_manager_;

	// ライトマネージャー
	CLightManager* light_manager_;
};

#endif	// _OBJECT_2D_MANAGER_H_

//---------------------------------- EOF --------------------------------------
