//*****************************************************************************
//
// OpenGLクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _OPENGL_H_
#define _OPENGL_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"
#include "basic/main_window.h"

// graphic
#include "interface/graphic/device/graphic_device.h"

// opengl
#include <GL/gl.h>
#include <GL/glu.h>

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"glu32.lib")

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 前方宣言
//*****************************************************************************

//*****************************************************************************
// OpenGLクラス
//*****************************************************************************
class COpengl : public CGraphicDevice
{
public:
	// コンストラクタ
	COpengl(WINDOW_DATA* window_data);

	// デストラクタ
	~COpengl(void);

	// 初期化
	bool Init(void);

	// 終了
	void Uninit(void);

	// 描画開始
	void BeginDraw(void);

	// 描画終了
	void EndDraw(void);

	// ロード開始
	void BeginLoad(void);

	// ロード終了
	void EndLoad(void);

	// TODO スクリーンショット(未実装)
	void ScreenShot(const s8* filename);

	// 描画モードの設定
	void SetDrawMode(const DEVICE_MODE& device_mode);

	// ロードモードの設定
	void SetLoadMode(const DEVICE_MODE& device_mode);
private:
	static const u8 CONTEXT_MAX = 3;

	typedef struct _GL_CONTEXT
	{
		HDC _hdc;
		HGLRC _hglrc;
	}GL_CONTEXT;

	GL_CONTEXT gl_context_[CONTEXT_MAX];
};

#endif // _OPENGL_H_

//---------------------------------- EOF --------------------------------------
