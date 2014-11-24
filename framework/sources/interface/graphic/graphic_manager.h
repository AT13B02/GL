//*****************************************************************************
//
// グラフィックマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _GRAPHIC_MANAGER_H_
#define _GRAPHIC_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
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
class CObjectManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CGraphicManager : public CBasic
{
public:
	// コンストラクタ
	CGraphicManager(WINDOW_DATA* window_data);

	// デストラクタ
	virtual ~CGraphicManager(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(void);

	// 終了処理
	void Uninit(void);

	// ロード開始
	void BeginLoad(void);

	// ロード終了
	void EndLoad(void);

	// デバイスホルダーの取得
	CDeviceHolder* device_holder(void){return device_holder_;}

	// オブジェクトマネージャーの取得
	CObjectManager* object_manager(void){return object_manager_;}

	// テクスチャマネージャーの取得
	CTextureManager* texture_manager(void){return texture_manager_;}

	// モデルマネージャーの取得
	CModelManager* model_manager(void){return model_manager_;}

	// カメラマネージャーの取得
	CCameraManager* camera_manager(void){return camera_manager_;}

	// ライトマネージャーの取得
	CLightManager* light_manager(void){return light_manager_;}

	// レンダーステートマネージャーの取得
	CRenderstateManager* renderstate_manager(void){return renderstate_manager_;}
protected:

private:
	// デバイスホルダーの取得
	CDeviceHolder* device_holder_;

	// オブジェクトマネージャー
	CObjectManager* object_manager_;

	// テクスチャマネージャー
	CTextureManager* texture_manager_;

	// モデルマネージャー
	CModelManager* model_manager_;

	// カメラマネージャー
	CCameraManager* camera_manager_;

	// ライトマネージャー
	CLightManager* light_manager_;

	// レンダーステートマネージャー
	CRenderstateManager* renderstate_manager_;
};

#endif	// _GRAPHIC_MANAGER_H_

//---------------------------------- EOF --------------------------------------
