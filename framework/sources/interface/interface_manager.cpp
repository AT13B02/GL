//*****************************************************************************
//
// インターフェースマネージャークラス [interface_manager.cpp]
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "interface/interface_manager.h"

// input
#include "interface/input/input_manager.h"

// graphic
#include "interface/graphic/graphic_manager.h"

// character
#include "interface/character/character_manager.h"

// sound
//#include "interface/sound/sound_manager.h"

// network
#include "interface/network/network_manager.h"

#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CInterfaceManager::CInterfaceManager(WINDOW_DATA* window_data)
{
	window_data_ = window_data;

	input_manager_ = new CInputManager(window_data);
	graphic_manager_ = new CGraphicManager(window_data);
	sound_manager_ = NULL;//new CSoundManager();
	network_manager_ = new CNetworkManager();
	character_manager_ = new CCharacterManager();
}

//=============================================================================
// デストラクタ
//=============================================================================
CInterfaceManager::~CInterfaceManager(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CInterfaceManager::Init(void)
{
	// インプットマネージャーの初期化
	INIT(input_manager_);

	// グラフィックマネージャーの初期化
	INIT(graphic_manager_);

	// サウンドマネージャーの初期化
	//INIT(sound_manager_);

	// ネットワークマネージャーの初期化
	INIT(network_manager_);

	//キャラクタマネージャーの初期化
	INIT(character_manager_);

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CInterfaceManager::Update(void)
{
	// インプットマネージャーの更新
	input_manager_->Update();

	// キャラクターマネージャーの更新
	character_manager_->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CInterfaceManager::Draw(void)
{
	// キャラクターの描画
	character_manager_->Draw();

	// グラフィックマネージャーの描画
	graphic_manager_->Draw();
}

//=============================================================================
// 終了
//=============================================================================
void CInterfaceManager::Uninit(void)
{
	
	//キャラクタマネージャの解放
	SAFE_RELEASE(character_manager_);

	// インプットマネージャーの開放
	SAFE_RELEASE(input_manager_);

	// グラフィックマネージャーの開放
	SAFE_RELEASE(graphic_manager_);

	// サウンドマネージャーの開放
	//SAFE_RELEASE(sound_manager_);

	// ネットワークマネージャーの開放
	SAFE_RELEASE(network_manager_);

}

//=============================================================================
// ロード開始
//=============================================================================
void CInterfaceManager::BeginLoad(void)
{
	graphic_manager_->BeginLoad();
}

//=============================================================================
// ロード終了
//=============================================================================
void CInterfaceManager::EndLoad(void)
{
	graphic_manager_->EndLoad();
}

//-----------------------------------EOF---------------------------------------
