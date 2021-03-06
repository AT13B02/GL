//*****************************************************************************
//
// アイコン(2D)マネージャー
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************
#include "icon_2d_manager.h"
#include "icon_2d.h"
//=============================================================================
// コンストラクタ
//=============================================================================
CIcon2DManager::CIcon2DManager( void )
{
}
//=============================================================================
// デストラクタ
//=============================================================================
CIcon2DManager::~CIcon2DManager( void )
{
}
//=============================================================================
// 初期化
//=============================================================================
bool CIcon2DManager::Init( void )
{
	return true;
}
//=============================================================================
// 生成
//=============================================================================
CIcon2D* CIcon2DManager::Create( CInterfaceManager* interface_manager , int player_id , f32 scale )
{
	CIcon2D* p = new CIcon2D( interface_manager , player_id , scale );
	p->Init();
	return p;
}
//---------------------------------- EOF --------------------------------------
