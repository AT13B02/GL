//*****************************************************************************
//
// オブジェクト3Dマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _OBJECT_3D_MANAGER_H_
#define _OBJECT_3D_MANAGER_H_

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
class CObject3D;
class CObject3DList;
class CObject3DBuffer;

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
class CObject3DManager : public CBasic
{
public:
	// コンストラクタ
	CObject3DManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager,CModelManager* model_manager,CCameraManager* camera_manager,CLightManager* light_manager);

	// デストラクタ
	~CObject3DManager(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(void);

	// 終了処理
	void Uninit(void);

	// リストに追加
	u32 AddList(CObject3D* object_3d);

	// モデルマネージャーの取得
	CModelManager* GetModelManager(void){return model_manager_;}

	//-----------------------------------------------------
	// 描画リストに保存

	void Draw(const u32& object_key,const VECTOR3& position,const VECTOR3& rotation,const VECTOR3& scale,MATRIX4x4 matrix,const std::string& texture_name,CRenderstate* renderstate);

	//--------------------------------------------------------

protected:

private:
	// オブジェクトリスト
	CObject3DList* object_3d_list_;

	// バッファリスト
	CObject3DBuffer* object_3d_buffer_;

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

	// モデルマネージャー
	CModelManager* model_manager_;
};

#endif	// _OBJECT_3D_MANAGER_H_

//---------------------------------- EOF --------------------------------------
