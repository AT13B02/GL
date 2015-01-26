//=============================================================================
//
// レンダリングクラス [CRenderer.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/8
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CRenderer.h"
#include "Debug.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CRenderer::CRenderer()
	:	m_hWnd(0),
		m_hdc(0),
		m_glRC(0),
		m_uBackBufferWidth(0),
		m_uBackBufferHeight(0),
		m_Clear_Red(0.1f),
		m_Clear_Green(0.1f),
		m_Clear_Blue(0.1f)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 生成処理
//=============================================================================
HRESULT CRenderer::Create(HWND hWnd, BOOL bWindow, unsigned uBackBufferWidth, unsigned uBackBufferHeight, CRenderer** ppRender)
{
	(*ppRender) = new CRenderer();
	_Assert((*ppRender));

	return (*ppRender)->Init(hWnd, bWindow, uBackBufferWidth, uBackBufferHeight);
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow, unsigned uBackBufferWidth, unsigned uBackBufferHeight)
{
	// ピクセルフォーマット初期化
	// pixel format descriptor
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | // ウィンドウに書く
		PFD_SUPPORT_OPENGL | // OpenGL
		PFD_DOUBLEBUFFER,	// ダブルバッファ
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		32, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24, // 深度バッファビット数
		8, // ステンシルバッファビット数
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	// 先生が書いたやつ
	/*
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | // ウィンドウに書く
		PFD_SUPPORT_OPENGL | // OpenGL
		PFD_DOUBLEBUFFER,	// ダブルバッファ
		PFD_TYPE_RGBA, //The kind of framebuffer. RGBA or palette.
		24, //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32, // 深度バッファビット数
		0, // ステンシルバッファビット数
		0, //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	*/

	// バックバッファサイズ設定
	m_uBackBufferWidth = uBackBufferWidth;
	m_uBackBufferHeight = uBackBufferHeight;

	// デバイスコンテキスト取得
	m_hdc = GetDC(hWnd);
	int format = ChoosePixelFormat(m_hdc, &pfd);
	if (format == 0)
	{
		return E_FAIL; // 該当するピクセルフォーマットが無い
	}

	// OpenGLが使うデバイスコンテキストに指定のピクセルフォーマットをセット
	if (!SetPixelFormat(m_hdc, format, &pfd))
	{
		return E_FAIL; // DCへフォーマットを設定するのに失敗
	}

	// OpenGL用のcontextを作成
	m_glRC = wglCreateContext(m_hdc);

	// 作成されたコンテキストがカレント（現在使用中のコンテキスト）か？
	if (!wglMakeCurrent(m_hdc, m_glRC))	// コンテキストの切り替えができる
	{
		return E_FAIL;
	}

	// ウィンドウハンドル設定
	m_hWnd = hWnd;
	
	// OpenGLExt初期化
	if(!InitOpenGLExt())
	{
		_AssertExpr(0, "OpenGLExtの初期化に失敗");
		return E_FAIL;
	}
	
	// 裏面をカリング
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// 深度テスト有効化
	glEnable(GL_DEPTH_TEST);
	// ライティング有効化
	glEnable(GL_LIGHTING);
	// アルファテスト有効化
	glEnable(GL_ALPHA_TEST);
	// ブレンド有効化
	glEnable(GL_BLEND);
	// アルファ合成設定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// 加算合成
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	// 乗算合成(ポリゴンの色と掛け合わせ)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	return S_OK;
}

//=============================================================================
// 開放
//=============================================================================
void CRenderer::Release(void)
{
	// カレントコンテキスト(レンダリングコンテキスト？)を無効にする
	wglMakeCurrent(NULL, NULL);

	// カレントコンテキストを削除
	wglDeleteContext(m_glRC);

	// デバイスコンテキスト解放
	ReleaseDC(m_hWnd, m_hdc);

	delete this;
}

//=============================================================================
// 描画開始
//=============================================================================
void CRenderer::BeginDraw()
{
	// 描画先設定
	BOOL res = wglMakeCurrent(m_hdc, m_glRC);

	// 画面のクリア
	// (バックバッファ, 深度バッファ)
	glClearColor(m_Clear_Red, m_Clear_Green, m_Clear_Blue, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

//=============================================================================
// 描画終了
//=============================================================================
void CRenderer::EndDraw()
{
	// クライアント、サーバー間のコマンド強制実行
	// スタンドアロンではあまり意味は無い
	glFlush();

	// バッファ交換
	SwapBuffers(m_hdc);
}

// EOF