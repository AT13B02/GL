//*****************************************************************************
//
// オブジェクト3Dリストクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/object_3d_list.h"
#include "interface/graphic/object/object_3d/element/object_3d.h"

// common
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
CObject3DList::CObject3DList(void)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3DList::~CObject3DList(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CObject3DList::Init(void)
{
	return true;
}

//=============================================================================
// 終了
//=============================================================================
void CObject3DList::Uninit(void)
{
	for(auto it = object_3d_list_.begin();it != object_3d_list_.end();++it)
	{
		SAFE_RELEASE(it->second);
	}

	object_3d_list_.clear();
}

//=============================================================================
// 追加
//=============================================================================
u32 CObject3DList::AddList(CObject3D* object_3d)
{
	u32 key = CreateKey();

	object_3d_list_.insert(std::pair<u32,CObject3D*>(key,object_3d));

	return key;
}

//=============================================================================
// 追加
//=============================================================================
bool CObject3DList::EraseList(u32 object_key)
{
	//auto it = object_3d_list_.find(object_key);

	//SAFE_RELEASE(it->second);

	//object_3d_list_.erase(it);

	return true;
}

//=============================================================================
// オブジェクトの取得
//=============================================================================
CObject3D* CObject3DList::GetListData(const u32& object_key)
{
	CObject3D* object_3d = NULL;

	auto it = object_3d_list_.find(object_key);

	if(it != object_3d_list_.end())
	{
		object_3d = it->second;
	}

	return object_3d;
}

//=============================================================================
// リフレッシュ
//=============================================================================
void CObject3DList::Refresh(void)
{
	for(auto it = object_3d_list_.begin();it != object_3d_list_.end();++it)
	{
		SAFE_RELEASE(it->second);
	}

	object_3d_list_.clear();
}

//=============================================================================
// キーの発行
//=============================================================================
u32 CObject3DList::CreateKey(void)
{
	bool is_find = false;
	u32 key = 0;

	while(!is_find)
	{
		// キーの生成
		key = rand();

		// キーが存在しない
		if(object_3d_list_.find(key) == object_3d_list_.end())
		{
			// キーとして使用
			is_find = true;
		}
	}

	return key;
}

//---------------------------------- EOF --------------------------------------
