//*****************************************************************************
//
// バレットクラス
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************
#include "explosion.h"
//billboard
#include "interface/graphic/object/object_3d/element/billboard.h"
#include "interface/interface_manager.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************
const f32 CExplosion::DEFAULT_RADIUS = 20.0f;

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion(CInterfaceManager* interface_manager)
{
	interface_manager_ = interface_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion(void)
{
}

//=============================================================================
// 生成処理
//=============================================================================
void CExplosion::SetParameter(const VECTOR3& position, const s16 u_division_num, const s16 v_division_num, const s16 animation_change_count)
{
	position_ = position;
	u_division_num_ = u_division_num;
	v_division_num_ = v_division_num;
	animation_change_count_ = animation_change_count;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CExplosion::Init(void)
{
	// オブジェクトビルボードの生成
	billboard_ = new CBillboard(interface_manager_->graphic_manager()->device_holder());
	billboard_->set_size(VECTOR2(50.0f,50.0f));

	//テクスチャ設定
	left_   = 0.0f;
	right_  = 1.0f / u_division_num_;
	top_    = 0.0f;
	bottom_ = 1.0f / v_division_num_;

	billboard_->set_texcoord( left_, right_, top_, bottom_ );

	//セット
	billboard_->Set();

	// オブジェクトリストに追加
	object_key_ = interface_manager_->graphic_manager()->object_manager()->object_3d_manager()->AddList(billboard_);
	radius_ = DEFAULT_RADIUS;

	animation_count_ = 0;
	u_division_count = 0;
	v_division_count = 0;

	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	//アニメーション変更カウントになったらテクスチャ変更??
	if( animation_count_ % animation_change_count_ == 0 )
	{
 		u_division_count++;

		if( ( u_division_count >= u_division_num_ ) && ( v_division_count < v_division_num_ ) )
		{
			u_division_count = 0;
			v_division_count++;

			left_ = 0.0f;
			right_ = 1.0f / u_division_num_;

			top_ = bottom_;
			bottom_ = bottom_ + ( 1.0f / v_division_num_ );
		}
		else if(( u_division_count >= u_division_num_ ) &&( v_division_count >= v_division_num_ ))
		{
			Erase();
		}
		else
		{
			left_ = right_;
			right_ = right_ + ( 1.0f / u_division_num_ );

		}

		billboard_->set_texcoord( left_, right_, top_,  bottom_);
		billboard_->Set();

	}

	//カウント増加
	animation_change_count_++;
}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,position_,VECTOR3(),VECTOR3(1.0f,1.0f,1.0f),MATRIX4x4(),"explosion");
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit( void )
{


}
//=============================================================================
// 弾消去処理
//=============================================================================
void CExplosion::Erase( void )
{
	is_death_ = true;
}
//---------------------------------- EOF --------------------------------------
