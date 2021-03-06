//*****************************************************************************
//
// オブジェクト2Dバッファクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _OBJECT_2D_BUFFER_H_
#define _OBJECT_2D_BUFFER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// stl
#include <list>

// basic
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
class CObject2DData;
class CCamera;
class CModelManager;
class CTextureManager;
class CRenderstateManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject2DBuffer : public CBasic
{
public:
	// コンストラクタ
	CObject2DBuffer(void);

	// デストラクタ
	~CObject2DBuffer(void);

	// 初期化
	bool Init(void);

	// 描画
	void Draw(CCamera* camera,CTextureManager* texture_manager,CRenderstateManager* renderstate_manager);

	// 終了
	void Uninit(void);

	// 追加
	void AddList(CObject2DData* pObjectData);

	// リフレッシュ
	void Refresh(void);

private:
	// バッファリスト
	std::list<CObject2DData*> object_2d_data_list_;
};

#endif	// _OBJECT_2D_BUFFER_H_

//---------------------------------- EOF --------------------------------------
