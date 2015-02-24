//*****************************************************************************
//
// インターフェースマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _INTERFACE_MANAGER_H_
#define _INTERFACE_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/basic.h"
#include "basic/main_window.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CInputManager;
class CSoundManager;
class CGraphicManager;
class CNetworkManager;
class CCharacterManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CInterfaceManager : public CBasic
{
public:
	// コンストラクタ
	CInterfaceManager(WINDOW_DATA* window_data);

	// デストラクタ
	~CInterfaceManager(void);

	// 初期化処理
	bool Init(void);

	// 更新処理
	void Update(void);

	// 描画処理
	void Draw(void);

	// 終了処理
	void Uninit(void);

	// ロード開始
	void BeginLoad(void);

	// ロード終了
	void EndLoad(void);

	// ウィンドウデータの取得
	WINDOW_DATA* window_data(void){return window_data_;}

	// インプットマネージャーの取得
	CInputManager* input_manager(void){return input_manager_;}

	// サウンドマネージャーの取得
	CSoundManager* sound_manager(void){return sound_manager_;}

	// グラフィックマネージャーの取得
	CGraphicManager* graphic_manager(void){return graphic_manager_;}

	// ネットワークマネージャーの取得
	CNetworkManager* network_manager(void){return network_manager_;}

	//キャラクタマネージャーの取得
	CCharacterManager* character_manager( void ){ return character_manager_; }

protected:

private:
	WINDOW_DATA* window_data_;
	CInputManager* input_manager_;
	CSoundManager* sound_manager_;
	CGraphicManager* graphic_manager_;
	CNetworkManager* network_manager_;
	CCharacterManager* character_manager_;
};

#endif // _INTERFACE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
