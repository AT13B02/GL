//*****************************************************************************
//
// キャラクタマネージャークラス
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************

#include "character_manager.h"
#include "player/player_manager.h"

#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCharacterManager::CCharacterManager()
{
	player_manager_ = new CPlayerManager;

}

//=============================================================================
// デストラクタ
//=============================================================================
CCharacterManager::~CCharacterManager()
{


}


//=============================================================================
// 初期化
//=============================================================================
bool CCharacterManager::Init(void)
{
	
	player_manager_->Init();

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CCharacterManager::Update(void)
{
	player_manager_->Update();
}

//=============================================================================
// 描画
//=============================================================================
void CCharacterManager::Draw(void)
{
	player_manager_->Draw();

}

//=============================================================================
// 終了
//=============================================================================
void CCharacterManager::Uninit( void )
{
	SAFE_RELEASE( player_manager_ );
}


//---------------------------------- EOF --------------------------------------
