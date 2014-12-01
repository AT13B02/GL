//*****************************************************************************
//
// オブジェクト2Dリストクラス [object_2d_list.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "object_2d_list.h"
#include "object_2d.h"

#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CObject2DList::CObject2DList(void)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CObject2DList::~CObject2DList(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CObject2DList::Init(void)
{
	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CObject2DList::Uninit(void)
{
	for(auto it = object_2d_list_.begin();it != object_2d_list_.end();++it)
	{
		SAFE_RELEASE(it->second);
	}

	object_2d_list_.clear();
}

//=============================================================================
// 追加
//=============================================================================
u32 CObject2DList::AddList(CObject2D* object_2d)
{
	u32 key = CreateKey();

	object_2d_list_.insert(std::pair<u32,CObject2D*>(key,object_2d));

	return key;
}

//=============================================================================
// オブジェクトの取得
//=============================================================================
CObject2D* CObject2DList::GetListData(const u32& object_key)
{
	CObject2D* object_2d = NULL;

	auto it = object_2d_list_.find(object_key);

	if(it != object_2d_list_.end())
	{
		object_2d = it->second;
	}

	return object_2d;
}

//=============================================================================
// リフレッシュ
//=============================================================================
void CObject2DList::Refresh(void)
{
	for(auto it = object_2d_list_.begin();it != object_2d_list_.end();++it)
	{
		SAFE_RELEASE(it->second);
	}

	object_2d_list_.clear();
}


//=============================================================================
// キーの発行
//=============================================================================
u32 CObject2DList::CreateKey(void)
{
	bool is_find = false;
	u32 key = 0;

	while(!is_find)
	{
		// キーの生成
		key = rand();

		// キーが存在しない
		if(object_2d_list_.find(key) == object_2d_list_.end())
		{
			// キーとして使用
			is_find = true;
		}
	}

	return key;
}
//---------------------------------- EOF --------------------------------------
