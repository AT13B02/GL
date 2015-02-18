//=============================================================================
//
// マネージャ [CManager.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "CManager.h"
#include "CApplication.h"
#include "CRenderer.h"
#include "CWindowManager.h"

#include "CRect2D.h"
#include "CTextureGL.h"
#include "CCamera.h"

#include "kbMath.h"
#include "Debug.h"

//=============================================================================
// コンストラクタ
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/15
//=============================================================================
CManager::CManager()
	: m_pApplication(nullptr),
	m_pRenderer(nullptr),
	m_pWindowManager(nullptr),
	m_pTexture(nullptr)
{
}

//=============================================================================
// マネージャ作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
HRESULT CManager::Create(HINSTANCE hInstance, CApplication* pApplication, CManager** ppManager)
{
	// マネージャ生成
	(*ppManager) = new CManager();

	HRESULT hr = (*ppManager)->Init(hInstance, pApplication);

	return hr;
}

//=============================================================================
// マネージャ作成
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Release(void)
{
	Uninit();

	delete this;
}

//=============================================================================
// 初期化
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, CApplication* pApplication)
{
	// アプリケーションクラス設定
	_AssertExpr(pApplication, "アプリケーションが生成されていない");
	m_pApplication = pApplication;

	// レンダラ設定
	m_pRenderer = m_pApplication->GetRenderer();
	// ウィンドウマネージャ設定
	m_pWindowManager = m_pApplication->GetWindowManager();

	// テクスチャ取得
	if('\0' == (pApplication->GetArgument())[0])
	{
		MessageBox(NULL, "テクスチャファイルが指定されていません", "", MB_OK);
		return E_FAIL;
	}
	CTextureGL::LoadFromFile(pApplication->GetArgument(), &m_pTexture);
	
	return S_OK;
}

//=============================================================================
// 開放
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Uninit(void)
{
	// テクスチャ開放
	SafeRelease(m_pTexture);
}

//=============================================================================
// 更新
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Update(void)
{
}

//=============================================================================
// 描画
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/9
//=============================================================================
void CManager::Draw(void)
{
	// カメラ設定
	CCamera camera;
	camera.left(0);
	camera.right(m_pRenderer->GetBackBufferWidth());
	camera.top(0);
	camera.bottom(m_pRenderer->GetBackBufferHeight());
	camera.Setup();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	//glMultMatrixf((GLfloat*)&camera.GetOrtho());
	glOrtho(0, m_pRenderer->GetBackBufferWidth(), m_pRenderer->GetBackBufferHeight(), 0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(0, 0, m_pRenderer->GetBackBufferWidth(), m_pRenderer->GetBackBufferHeight());

	// 描画開始
	m_pRenderer->BeginDraw();
	
	// ライティングオフ
	glDisable(GL_LIGHTING);

	// テクスチャ適用
	m_pTexture->SetTex2D();
	float left = 0;
	float top = 0;
	float right		= (float)m_pRenderer->GetBackBufferWidth();
	float bottom	= (float)m_pRenderer->GetBackBufferHeight();
	float fTexS = 0.0f;
	float fTexT = 0.0f;
	Vector4 color(1.0f, 1.0f, 1.0f, 1.0f);
	VERTEX_2D aVtx[] =
	{
		{
			Vector3(right, top, 0.0f),
			color,
			Vector2(fTexS + 1.0f, fTexT)
		},
		{
			Vector3(left, top, 0.0f),
			color,
			Vector2(fTexS, fTexT)
		},
		{
			Vector3(right, bottom, 0.0f),
			color,
			Vector2(fTexS + 1.0f, fTexT + 1.0f)
		},
		{
			Vector3(left, bottom, 0.0f),
			color,
			Vector2(fTexS, fTexT + 1.0f)
		},
	};
	// テクスチャオン
	glEnable(GL_TEXTURE_2D);
	// 描画
	CRect2D::DrawPrimitive(GL_TRIANGLE_STRIP, (void*)aVtx, 4);
	// テクスチャ無効化
	glDisable(GL_TEXTURE_2D);
	
	// ライティングオン
	glEnable(GL_LIGHTING);
	
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	// 描画終了
	m_pRenderer->EndDraw();
}

// EOF