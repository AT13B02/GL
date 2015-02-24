//*****************************************************************************
//
// ライフマネージャークラス [life_2d_manager.h]
//
// Author		: ooigawa Kazuma
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _LIFE_2D_MANAGER_H_
#define _LIFE_2D_MANAGER_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <windows.h>
#include <string>
#include <map>

// basic
#include "basic/basic.h"


// character_manager
#include "life_2d.h"
#include "interface/character/character_manager_interface.h"

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
class CLife2D;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLife2DManager : public CCharacterManagerInterface<CLife2D*>
{
public:
	//コンストラクタ
	CLife2DManager();

	//デストラクタ
	~CLife2DManager();

	// 初期化処理
	bool Init(void);

	static CLife2D* Create( CInterfaceManager* interface_manager , VECTOR2 position , s32 max_life , s32 max_length );

private:
};
#endif //_LIFE_2D_MANAGER_H_
//---------------------------------- EOF --------------------------------------
