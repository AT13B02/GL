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
#include "interface/input/input_manager.h"

#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const f32 CPlayer::SPEED = 0.5f;
const f32 CPlayer::SPEED_DEST = 0.3f;
const f32 CPlayer::ROTATION_DEST = 0.3f;



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

	
	//移動目標値変数
	VECTOR3 pos_dest_ = VECTOR3( 0.0f, 0.0f, 0.0f );
	VECTOR3 rot_dest_ = VECTOR3( 0.0f, 0.0f, 0.0f );

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	//カメラの角度を持ってくる
	f32 camera_rot_y = 0.0f;

	//カメラの前ベクトルと右ベクトル持ってくる
	VECTOR3 camera_flont_vec = VECTOR3( 0.0f, 1.0f, 0.0f );
	VECTOR3 camera_right_vec = VECTOR3( 1.0f, 0.0f, 0.0f );



	//右移動
	if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_D ) )
	{
		//右斜め後ろ
		if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_S ) )
		{
			//カメラの角度を持ってくる
			rot_._y = camera_rot_y + MTH_PI/2;
			//移動
			pos_dest_ = pos_ + ((camera_right_vec + camera_flont_vec  ) / 2) * SPEED;
		}
		//右斜め前
		else if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_W ) )
		{
			//カメラの角度を持ってくる
			rot_._y = camera_rot_y + MTH_PI *3; 
			//移動
			pos_dest_ = pos_ + ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;
		}
		else
		{
			//カメラの角度を持ってくる
			rot_._y = camera_rot_y + MTH_PI/2; 
			//移動
			pos_dest_ = pos_ + ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;

		}
	}
	//左移動
	if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_A ) )
	{		
		//右斜め後ろ
		if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_S ) )
		{
			//カメラの角度を持ってくる
			rot_dest_._y = camera_rot_y - MTH_PI/4;
			//移動
			pos_dest_ = pos_ + ((camera_right_vec + camera_flont_vec  ) / 2) * SPEED;
		}
		//右斜め前
		else if( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_W) )
		{
			//カメラの角度を持ってくる
			rot_dest_._y = camera_rot_y - MTH_PI/4 * 5; 
			//移動
			pos_dest_ = pos_dest_ + ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;
		}
		else
		{
			//カメラの角度を持ってくる
			rot_dest_._y = camera_rot_y - MTH_PI/2; 
			//移動
			pos_dest_ = pos_ - ((camera_right_vec + -camera_flont_vec  ) / 2) * SPEED;

		}
	}
	
	//奥移動
	if(( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_W )))
	{
		pos_dest_ = pos_ - camera_flont_vec * SPEED;
		rot_dest_._y = camera_rot_y + MTH_PI;
	}

	//手前移動
	if(( interface_manager_->input_manager()->CheckPress( INPUT_EVENT_S )))
	
	{
		pos_dest_ = pos_ + camera_flont_vec * SPEED;
		rot_dest_._y = camera_rot_y;
	}


	pos_._x += ( pos_dest_._x - pos_._x ) * SPEED_DEST;
	pos_._z += ( pos_dest_._z - pos_._z ) * SPEED_DEST;

	rot_._y += ( rot_dest_._y - rot_._y ) * ROTATION_DEST;

	DEBUG_TOOL.debug_console()->Print("Player Pos  : %.1f, %.1f, %.1f\n", pos_._x, pos_._y, pos_._z);
	DEBUG_TOOL.debug_console()->Print("Player Rot  : %.1f, %.1f, %.1f\n", rot_._x, rot_._y, rot_._z);

}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,pos_,rot_,scale_,MATRIX4x4(),"");
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
}

//---------------------------------- EOF --------------------------------------
