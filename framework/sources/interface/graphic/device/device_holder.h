//*****************************************************************************
//
// デバイスホルダークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	描画デバイスを作成、削除、保持するクラス
*
*/
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _DEVICE_HOLDER_H_
#define _DEVICE_HOLDER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"
#include "basic/application.h"
#include "basic/main_window.h"

// graphic
#include "interface/graphic/device/graphic_device.h"

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
// 前方宣言
//*****************************************************************************
#ifdef _USING_DIRECTX_
class CDirectx;
#endif // _USING_DIRECTX_
#ifdef _USING_OPENGL_
class COpengl;
#endif // _USING_OPENGL_

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CDeviceHolder : public CBasic
{
public:
	// コンストラクタ
	CDeviceHolder(WINDOW_DATA* window_data);

	// デストラクタ
	virtual ~CDeviceHolder(void);

	// 初期化
	bool Init(void);

	// 終了
	void Uninit(void);

	// 描画開始
	void BeginDraw(void);

	// 描画終了
	void EndDraw(void);

	// ロードの開始
	void BeginLoad(void);

	// ロードの終了
	void EndLoad(void);

	// スクリーンショット
	void ScreenShot(void);

	// スクリーンショット
	void ScreenShot(const s8* pFilename);

	// クローンの生成
	//CDeviceHolder* MakeClone(void);

	// デバイスの描画モードの設定
	void SetDrawMode(const CGraphicDevice::DEVICE_MODE& device_mode);

	// デバイスの描画モードの設定
	void SetLoadMode(const CGraphicDevice::DEVICE_MODE& device_mode);

	// TODO デバイスの再取得(未実装)
	void ResetDevice(void);

#ifdef _USING_DIRECTX_
	CDirectX* device(void){return device_;}
#endif // _USING_DIRECTX_
#ifdef _USING_OPENGL_
	COpengl* device(void){return device_;}
#endif // _USING_OPENGL_

private:
	// コンストラクタ
	CDeviceHolder(void);

#ifdef _USING_DIRECTX_
	CDirectX* device_;
#endif // _USING_DIRECTX_
#ifdef _USING_OPENGL_
	COpengl* device_;
#endif // _USING_OPENGL_
	WINDOW_DATA* window_data_;
};

#endif // _GRAPHICS_API_H_

//---------------------------------- EOF --------------------------------------
