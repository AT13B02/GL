//*****************************************************************************
//
// カウントダウンクラス
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

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
class CInterfaceManager;
class CRectangle2D;


//*****************************************************************************
// クラス定義
//*****************************************************************************
class CCountDown : public CBasic
{
public:
	// コンストラクタ
	CCountDown(CInterfaceManager* interface_manager);

	// デストラクタ
	virtual ~CCountDown(void);

	// 初期化
	bool Init(void);

	// 更新
	void Update(void);

	// 描画
	void Draw(void);

	// 終了
	void Uninit(void);

	// ロード
	void Load(void);

	bool countdown_comp( void ){ return countdown_comp_; }



protected:
	static const f32 ADD_TEXTURE_UV;
	static const f32 ADD_SCALSE;
	static const f32 WIDTH;
	static const f32 HEIGHT;


private:
	CInterfaceManager *interface_manager_;
	CRectangle2D *countdown_polygon;
	u32 countdown_polygon_key_;
	f32 alpha_;
	f32 scl_;
	f32 right_;
	f32 left_;
	f32 top_;
	f32 bottom_;

	bool countdown_comp_;



};

#endif	// _COUNTDOWN_H_

//---------------------------------- EOF --------------------------------------
