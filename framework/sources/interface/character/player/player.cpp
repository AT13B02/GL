//*****************************************************************************
//
// プレイヤークラス
//
// Author		: Chiharu Kamiyama
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "player.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(CInterfaceManager* interface_manager)
{
	//インターフェースマネージャーの保存
	interface_manager_ = interface_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CPlayer::Init(void)
{
	// オブジェクトモデルの生成
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"ship");
	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList( object_model );

	//値初期化
	pos_   = VECTOR3( 0.0f, 0.0f, 0.0f );
	rot_   = VECTOR3( 0.0f, 0.0f, 0.0f );
	scale_ = VECTOR3( 1.0f, 1.0f, 1.0f );

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	//pos._x += 0.1f;
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// 描画
	interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->
		Draw(object_key_,pos_,rot_,scale_,MATRIX4x4(), "field000");
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
}

//---------------------------------- EOF --------------------------------------
