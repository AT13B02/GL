//*****************************************************************************
//
// OpenGLクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "interface/graphic/device/opengl/opengl.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
COpengl::COpengl(WINDOW_DATA* window_data) : CGraphicDevice(window_data)
{
	int format;

	// ピクセルフォーマット初期化
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //Flags
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, //Number of bits for the depthbuffer
		8, //Number of bits for the stencilbuffer
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	for(u8 i = 0;i < CONTEXT_MAX;++i)
	{
		// デバイスコンテキストの取得
		gl_context_[i]._hdc = GetDC(window_data_->_hwnd);

		// ピクセルフォーマットの選択
		format = ChoosePixelFormat(gl_context_[i]._hdc, &pfd);

		// OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
		SetPixelFormat(gl_context_[i]._hdc,format,&pfd);

		// OpenGL contextを作成
		gl_context_[i]._hglrc = wglCreateContext(gl_context_[i]._hdc);
	}

	// アルファテスト有効化
	glEnable(GL_ALPHA_TEST);
	GLboolean alphatest = glIsEnabled(GL_ALPHA_TEST);

	// srcとdestのαブレンドの仕方の設定
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	// discardするアルファの値を設定
	glAlphaFunc(GL_GREATER, 0.0f);
	float alphaRef;
	glGetFloatv(GL_ALPHA_TEST_REF, &alphaRef);
	draw_mode_ = DEVICE_MODE_LOAD;
}

//=============================================================================
// デストラクタ
//=============================================================================
COpengl::~COpengl(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool COpengl::Init(void)
{
	return true;
}

//=============================================================================
// 終了
//=============================================================================
void COpengl::Uninit(void)
{
	// カレントコンテキストを無効にする
	wglMakeCurrent(NULL,NULL);

	for(u8 i = 0;i < CONTEXT_MAX;i++)
	{
		// OpenGLのコンテキスト
		wglDeleteContext(gl_context_[i]._hglrc);

		// デバイスコンテキスト解放
		ReleaseDC(window_data_->_hwnd,gl_context_[i]._hdc);
	}
}

//=============================================================================
// 描画開始
//=============================================================================
void COpengl::BeginDraw(void)
{
	// カレントコンテキストの選択
	if(wglMakeCurrent(gl_context_[0]._hdc,gl_context_[draw_mode_]._hglrc) == FALSE)
	{
		int a = 0;
	}

	// バッファのクリアする色を設定
	glClearColor(0.9f,1.0f,1.0f,0.8f);

	// クリアするものを選択
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

//=============================================================================
// 描画終了
//=============================================================================
void COpengl::EndDraw(void)
{
	wglMakeCurrent(NULL,NULL);

	// バッファに書込
	glFlush();

	// バッファの入れ替え
	SwapBuffers(gl_context_[0]._hdc);
}

//=============================================================================
// ロード開始
//=============================================================================
void COpengl::BeginLoad(void)
{
	// カレントコンテキストの選択
	while((wglMakeCurrent(gl_context_[1]._hdc,gl_context_[load_mode_]._hglrc) == FALSE));
}

//=============================================================================
// ロード終了
//=============================================================================
void COpengl::EndLoad(void)
{
	if(wglMakeCurrent(NULL,NULL) == FALSE)
	{
		int a = 0;
	}
}

//=============================================================================
// スクリーンショット
//=============================================================================
void COpengl::ScreenShot(const s8* filename)
{
}

//=============================================================================
// 描画モードの設定
//=============================================================================
void COpengl::SetDrawMode(const DEVICE_MODE& device_mode)
{
	CGraphicDevice::SetDrawMode(device_mode);

	if(wglMakeCurrent(NULL,NULL) == FALSE)
	{
		//MessageBox(NULL,"ロード失敗するかもに","エラー",MB_OK);
	}
}

//=============================================================================
// ロードモードの設定
//=============================================================================
void COpengl::SetLoadMode(const DEVICE_MODE& device_mode)
{
	CGraphicDevice::SetLoadMode(device_mode);

	wglMakeCurrent(NULL,NULL);
}

//---------------------------------- EOF --------------------------------------
