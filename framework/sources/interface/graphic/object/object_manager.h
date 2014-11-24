//*****************************************************************************
//
// オブジェクトマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/basic.h"
#include "basic/main_window.h"

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
class CTextureManager;
class CModelManager;
class CRenderstateManager;
class CCameraManager;
class CLightManager;
class CObject2DManager;
class CObject3DManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObjectManager : public CBasic
{
public:
	// コンストラクタ
	CObjectManager(CDeviceHolder* device_holder,CTextureManager* texture_manager,CModelManager* model_manager,CRenderstateManager* renderstate_manager,CCameraManager* camera_manager,CLightManager* light_manager);

	// デストラクタ
	virtual ~CObjectManager(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(void);

	// 終了処理
	void Uninit(void);

	// オブジェクト2Dマネージャーの取得
	CObject2DManager* object_2d_manager(void){return object_2d_manager_;}

	// オブジェクト3Dマネージャーの取得
	CObject3DManager* object_3d_manager(void){return object_3d_manager_;}
	CCameraManager* camera_manager(void){return camera_manager_;}

private:
	// デバイスホルダー
	CDeviceHolder* device_holder_;

	// テクスチャマネージャー
	CTextureManager* texture_manager_;

	// モデルマネージャー
	CModelManager* model_manager_;

	// レンダーステートマネージャー
	CRenderstateManager* renderstate_manager_;

	// カメラマネージャー
	CCameraManager* camera_manager_;

	// ライトマネージャー
	CLightManager* light_manager_;

	// オブジェクト2Dマネージャー
	CObject2DManager* object_2d_manager_;

	// オブジェクト3Dマネージャー
	CObject3DManager* object_3d_manager_;
};

#endif	// _OBJECT_MANAGER_H_

//---------------------------------- EOF --------------------------------------
