//*****************************************************************************
//
// Fade2Dクラス
//
// Author		: Tomohiro Kouno
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _FADE_2D_H_
#define _FADE_2D_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
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
class CTexture;
class CGraphicsDevice;
class CRectangle2D;
class CInterfaceManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CFade2D : public CBasic
{
public:

	// コンストラクタ
	CFade2D(CInterfaceManager* interface_manager);

	// デストラクタ
	virtual ~CFade2D(void);

	enum FADE_TYPE
	{
		FADE_TYPE_NONE,
		FADE_TYPE_IN,
		FADE_TYPE_IN_END,
		FADE_TYPE_OUT,
		FADE_TYPE_OUT_END,
	};

	// 初期化処理
	bool Init(void);

	// 更新処理
	void Update(void);

	// 描画処理
	void Draw(void);

	// 終了処理
	void Uninit(void);

	// フェードイン
	void FadeIn(f32 time = 0.01f){speed_ = time;fadetype_ = FADE_TYPE_IN;}

	// フェードアウト
	void FadeOut(f32 time =  0.01f){speed_ = time;fadetype_ = FADE_TYPE_OUT;}

	//フェードチェック
	bool IsFadeIn(void){return fadetype_ == FADE_TYPE_IN;}
	bool IsFadeOut(void){return fadetype_ == FADE_TYPE_OUT;}
	bool IsFadeInEnd(void){return fadetype_ == FADE_TYPE_IN_END;}
	bool IsFadeOutEnd(void){return fadetype_ == FADE_TYPE_OUT_END;}

protected:
	// 頂点情報
	CRectangle2D* rectangle_2d_;
	u32 rectangle_2d_key_;
	FADE_TYPE fadetype_;
	f32 alpha_;
	f32 speed_;

	// インターフェースマネージャー
	CInterfaceManager* interface_manager_;
private:

};

#endif	// _RECTANGLE_2D_H_

//---------------------------------- EOF --------------------------------------
