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
#include "math.h"
#include "basic/basic.h"

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
class CGraphicsDevice;
class CRenderstate;
class CRenderstateManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject2DManager : public CBasic
{
public:
	// コンストラクタ
	CObject2DManager(CGraphicsDevice* pGraphicsDevice,CRenderstateManager* pRenderstateManager);

	// デストラクタ
	~CObject2DManager(void);

	// 初期化
	bool Init(void);

	// 終了
	void Uninit(void);

	// 描画処理
	void Draw(void);

	// 格納
	int Add(CObject2D* pObject2D,int nListType = LIST_TYPE_LOAD);

	// 変更
	void Change(void);

	// 変更フラグ
	void RaiseChangeFlag(void);

	//-----------------------------------------------------
	// 描画リストに保存

	void Draw(const int& nObjectNumber,const VECTOR2& Pos);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,float fRot,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture);

	void Draw(const int& nObjectNumber,const VECTOR2& Pos,const float& fRot,const VECTOR2& Scale,const MATRIX4x4& Matrix,CTexture* pTexture,CRenderstate* pRenderstate);

private:

	enum LIST_TYPE
	{
		LIST_TYPE_USE = 0,
		LIST_TYPE_LOAD,
		LIST_TYPE_MAX,
	};

	// オブジェクトリスト
	CObject2DList* m_apObject2DList[LIST_TYPE_MAX];

	// 変更フラグ
	bool m_bChangeFlag;

	// バッファリスト
	CObject2DBuffer* m_pBuffer;

	// グラフィックデバイス
	CGraphicsDevice* m_pGraphicsDevice;

	// レンダーステートマネージャー
	CRenderstateManager* m_pRenderstateManager;
};

#endif	// _OBJECT_2D_MANAGER_H_

//---------------------------------- EOF --------------------------------------
