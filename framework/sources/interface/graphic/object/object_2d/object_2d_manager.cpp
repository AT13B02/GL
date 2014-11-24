//*****************************************************************************
//
// オブジェクト2Dマネージャークラス [object_2d_manager.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object_2d.h"
#include "object_2d_list.h"
#include "object_2d_data.h"
#include "object_2d_buffer.h"
#include "object_2d_manager.h"

#include "renderstate.h"
#include "renderstate_manager.h"

#include "graphics_device.h"

#include "common.h"

//*****************************************************************************
// マクロ定義
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
CObject2DManager::CObject2DManager(CGraphicsDevice* pGraphicsDevice,CRenderstateManager* pRenderstateManager)
{
	// グラフィックデバイスの設定
	m_pGraphicsDevice = pGraphicsDevice;

	// レンダーステートマネージャーの設定
	m_pRenderstateManager = pRenderstateManager;

	// オブジェクトリストの生成
	for(int i = 0;i < LIST_TYPE_MAX;i++)
	{
		m_apObject2DList[i] = new CObject2DList();
	}

	m_bChangeFlag = false;

	// オブジェクトバッファの生成
	m_pBuffer = new CObject2DBuffer();
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject2DManager::~CObject2DManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CObject2DManager::Init(void)
{
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject2DManager::Draw(void)
{
	m_pRenderstateManager->GetRenderstate(CRenderstateManager::TYPE_2D)->Set();

	m_pBuffer->Draw();

	m_pRenderstateManager->GetRenderstate(CRenderstateManager::TYPE_2D)->Unset();
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject2DManager::Uninit(void)
{
	// オブジェクトリストの開放
	for(int i = 0;i < LIST_TYPE_MAX;i++)
	{
		SAFE_RELEASE(m_apObject2DList[i]);
	}

	// バッファの開放
	SAFE_RELEASE(m_pBuffer);

}

//=============================================================================
// 追加処理
//=============================================================================
int CObject2DManager::Add(CObject2D* pObject2D,int nListType)
{
	if(nListType < 0 || nListType >= LIST_TYPE_MAX)
	{
		return -1;
	}

	return m_apObject2DList[nListType]->Add(pObject2D);
}

//=============================================================================
// 変更処理
//=============================================================================
void CObject2DManager::Change(void)
{
	if(m_bChangeFlag)
	{
		CObject2DList* pObjectList = NULL;
		pObjectList = m_apObject2DList[LIST_TYPE_USE];
		m_apObject2DList[LIST_TYPE_USE] = m_apObject2DList[LIST_TYPE_LOAD];
		m_apObject2DList[LIST_TYPE_LOAD] = pObjectList;
		pObjectList->Refresh();
		m_bChangeFlag = false;
	}
}

//=============================================================================
// 変更処理
//=============================================================================
void CObject2DManager::RaiseChangeFlag(void)
{
	m_bChangeFlag = true;
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos)
{
	Draw(nObjectNumber,Pos,NULL);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,CTexture* pTexture)
{
	Draw(nObjectNumber,Pos,0.0f,pTexture);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,float fRot,CTexture* pTexture)
{
	Draw(nObjectNumber,Pos,fRot,VECTOR2(1.0f,1.0f),pTexture);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,CTexture* pTexture)
{
	MATRIX4x4 Matrix;

	Matrix.SetIdentity();

	Draw(nObjectNumber,Pos,fRot,Scale,Matrix,pTexture);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture)
{
	Draw(nObjectNumber,Pos,fRot,Scale,Matrix,pTexture,NULL);
}

//=============================================================================
// 描画リストに保存
//=============================================================================
void CObject2DManager::Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture,CRenderstate* pRenderstate)
{
	CObject2DData* pData = NULL;
	CObject2D* pObject2D = m_apObject2DList[LIST_TYPE_USE]->GetObject2D(nObjectNumber);

	// オブジェクト番号の確認
	if(pObject2D == NULL)
	{
		return;
	}

	// バッファの生成
	pData = new CObject2DData();

	// バッファ番号の設定
	pData->SetObject(pObject2D);

	// 座標の設定
	pData->SetPosition(Pos);

	// 回転角の設定
	pData->SetRotation(fRot);

	// スケールの設定
	pData->SetScale(Scale);

	// マトリックスの設定
	pData->SetMatrix(Matrix);

	// テクスチャの設定
	pData->SetTexture(pTexture);

	// レンダーステートの設定
	pData->SetRenderstate(pRenderstate);

	// バッファリストに保存
	m_pBuffer->Add(pData);
}

//---------------------------------- EOF --------------------------------------
