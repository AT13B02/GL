//*****************************************************************************
//
// プレイヤークラス
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "player.h"
#include "interface/graphic/model/model.h"
#include "interface/graphic/object/object_3d/element/object_model.h"
#include "interface/interface_manager.h"
#include "interface/sound/sound_manager.h"
#include "interface/sound/sound.h"
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/input/input_manager.h"

#include "../character_manager.h"
#include "../bullet/bullet_manager.h"
#include "../bullet/bullet.h"
#include "../player_status/life_2d/life_2d.h"

//network
#include "../../network/network_manager.h"
#include "../../network/network_client.h"
#include "../../network/network_data_buffer.h"
#include "../../network/windows_sockets.h"

#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
const f32 CPlayer::SPEED = 1.0f;
const f32 CPlayer::SPEED_DEST = 0.3f;
const f32 CPlayer::ROTATION_DEST = 0.3f;
const f32 CPlayer::BULLET_LAUNCH_HEIGHT_OFFSET = 20.0f;
const f32 BULLET_MOVE_SPD=6.f;
const s16 COOLDOWN_TIME = 30;
const s16 CPlayer::MAX_HP = 100;

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(CInterfaceManager* interface_manager)
{
	
	//インターフェースマネージャーの保存
	interface_manager_ = interface_manager;
	death_flag_ = false;
	life_2d_ = NULL;
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
	//値初期化
	position_ = VECTOR3(0.0f,0.0f,0.0f);
	rotation_ = VECTOR3(0.0f,0.0f,0.0f);
	scale_    = VECTOR3(1.0f,1.0f,1.0f);
	
	//移動目標値変数
	VECTOR3 pos_dest_ = VECTOR3(0.0f,0.0f,0.0f );
	VECTOR3 rot_dest_ = VECTOR3(0.0f,0.0f,0.0f );

	//更新しない
	update_ = false;

	hp_ = MAX_HP;
	cooldown_cnt=0;
	is_fire=false;

	position_ = VECTOR3(0,0,0);

	switch(player_id())
	{
		case 0:
			position_ = VECTOR3(-1200.f,0,-1200.f);
		break;

		case 1:
			position_ = VECTOR3(-1200.f,0,1200.f);
		
		break;

		case 2:
			position_ = VECTOR3(1200.f,0,-1200.f);
	
		break;

		case 3:
			position_ = VECTOR3(1200.f,0,1200.f);
	
		break;

		default:
			position_ = VECTOR3(0,0,0);
	
			break;
	}

	return true;
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update(void)
{
	death_flag_ = interface_manager_->network_manager()->GetNetworkClient()->GetNetworkDataBuffer()->GetCharDeathFlag(player_id());

	VECTOR3 front_vector = front_vector_;
	VECTOR3 right_vector = right_vector_;
	VECTOR3 center_vector = front_vector + right_vector;

	front_vector._y = 0.0f;
	front_vector.Normalize();

	right_vector._y = 0.0f;
	right_vector.Normalize();

	move_vector_._x = 0.0f;
	move_vector_._y = 0.0f;
	move_vector_._z = 0.0f;

	// 左上移動
	if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		move_vector_ = (front_vector - right_vector).Normalize();
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 45.0f;
	}
	// 右上移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		move_vector_ = (front_vector + right_vector).Normalize();
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 135.0f;
	}
	// 左下移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		move_vector_ -= (front_vector + right_vector).Normalize();
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 45.0f;
	}
	// 右下移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		move_vector_ -= (front_vector - right_vector).Normalize();
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 135.0f;
	}
	// 右移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		move_vector_ = right_vector;
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 180.0f;
	}
	// 左移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		move_vector_ = -right_vector;
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN;
	}
	// 奥移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W))
	{
		move_vector_ = front_vector;
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 90.0f;
	}
	// 手前移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S))
	{
		move_vector_ = -front_vector;
		//rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 90.0f;
	}

	// 移動量加算
	position_ += move_vector_ * CPlayer::SPEED;

	//キャラクターは常にカメラに背を向ける
	rotation_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 90.0f;

	rotation_dest_._y = GetRotationNormalize(rotation_dest_._y);

	f32 def = rotation_dest_._y - rotation_._y;

	def = GetRotationNormalize(def);
	rotation_._y += def * 0.1f;

	//キー操作により射撃状態を切り替える
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_SPACE))
	{
		is_fire=!is_fire;
	}

	rotation_._y = GetRotationNormalize(rotation_._y);

	//発射可能状態の時
	if(cooldown_cnt>=COOLDOWN_TIME)
	{
		// 弾の発射
		if(is_fire&&death_flag_ == false)
		{
			cooldown_cnt=0;
			VECTOR3 crate_position = position_;
			crate_position._y += BULLET_LAUNCH_HEIGHT_OFFSET;
			VECTOR3 launch_vector(front_vector_);
			const f32 LAUNCH_OFFSET_Y = 0.34f;
			launch_vector._y += LAUNCH_OFFSET_Y;
			//launch_vector = launch_vector.RotationAxis(VECTOR3(0.0f, 1.0f, 0.0f), -(rotation_._y + 180.0f) * MTH_DEGREE);
			launch_vector.Normalize();
			interface_manager_
				->network_manager()
				->GetNetworkClient()
				->GetWinSock()
				->SendDataBullet(&crate_position
								,&launch_vector
								,BULLET_MOVE_SPD);


		}
	}
	//カウントダウンを進める
	else
	{
		cooldown_cnt++;
	}
	//if( life_2d_ != NULL )
	//{
	//	life_2d_->set_life( hp_ );
	//}
	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDataCharcter(&position_,&rotation_,0,hp_);
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
	object_3d_manager->Draw(object_key_,position_,rotation_,scale_,MATRIX4x4(),"");
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{

}

//=============================================================================
// idの取得
//=============================================================================
int CPlayer::player_id(void)
{
	//ネットワークバッファの取得
	int id = (int)interface_manager_->network_manager()->GetNetworkClient()->GetMyID();
	return id;
}

//=============================================================================
// デスフラグセット
//=============================================================================
void CPlayer::SetDeathFlag(bool flag)
{
	death_flag_ = flag;
	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDeathFlag(player_id());
}

//=============================================================================
// プレイヤー移動方向取得
//=============================================================================
const VECTOR3& CPlayer::get_move_vector()
{
	return move_vector_;
}

//=============================================================================
// プレイヤー移動スピード取得
//=============================================================================
const f32 CPlayer::get_move_speed()
{
	return CPlayer::SPEED;
}

//=============================================================================
// ダメージ関数
//=============================================================================
void CPlayer::Damage(int damage)
{
	hp_ -= damage;
	if(hp_ <= 0)
	{
		hp_ = 0;
		SetDeathFlag(true);
	}
}

//---------------------------------- EOF --------------------------------------
