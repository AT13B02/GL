//*****************************************************************************
//
// ゲームクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _SCENE_GAME_H_
#define _SCENE_GAME_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "scene/scene.h"

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
// TODO テスト用
class CCharacterCamera;
// ネットワークコマンダー
class CNetworkCommandAssistant;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSceneGame : public CScene
{
public:
	// コンストラクタ
	CSceneGame(CInterfaceManager* interface_manager);

	// デストラクタ
	virtual ~CSceneGame(void);

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

	// ファクトリの生成
	CSceneFactory* MakeFactory(void);

protected:

private:


	// TODO テスト用メンバー変数
	u32 test_meshfield_key_;
	u32 test_meshdome_key_;
	CNetworkCommandAssistant *network_command_assistant_;
};

#endif	// _SCENE_GAME_H_

//---------------------------------- EOF --------------------------------------
