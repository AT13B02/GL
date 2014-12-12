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
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_3d/object_3d_manager.h"
#include "interface/input/input_manager.h"

#include "../character_manager.h"
#include "../bullet/bullet_manager.h"
#include "../bullet/bullet.h"

//network
#include "../../network/network_manager.h"
#include "../../network/network_client.h"
#include "../../network/network_data_buffer.h"
#include "../../network/windows_sockets.h"

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
	CObjectModel* object_model = new CObjectModel( interface_manager_->graphic_manager()->device_holder(),"yukidaruma");
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
	VECTOR3 front_vector = front_vector_;
	VECTOR3 right_vector = right_vector_;
	VECTOR3 center_vector = front_vector + right_vector;

	front_vector._y = 0.0f;
	front_vector.Normalize();

	right_vector._y = 0.0f;
	right_vector.Normalize();

	// 左上移動
	if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		pos_ += (front_vector - right_vector).Normalize() * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 45.0f;
	}
	// 右上移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		pos_ += (front_vector + right_vector).Normalize() * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 135.0f;
	}
	// 左下移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		pos_ -= (front_vector + right_vector).Normalize() * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 45.0f;
	}
	// 右下移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S) && interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		pos_ -= (front_vector - right_vector).Normalize() * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 135.0f;
	}
	// 右移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_D))
	{
		pos_ += right_vector * 1.0f;
 		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 180.0f;
	}
	// 左移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_A))
	{
		pos_ -= right_vector * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN;
	}
	// 奥移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_W))
	{
		pos_ += front_vector * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN - 90.0f;
	}
	// 手前移動
	else if(interface_manager_->input_manager()->CheckPress(INPUT_EVENT_S))
	{
		pos_ -= front_vector * 1.0f;
		rot_dest_._y = -atan2f(front_vector_._z,front_vector_._x) * MTH_RADIAN + 90.0f;
	}

	rot_dest_._y = GetRotationNormalize(rot_dest_._y);

	f32 def = rot_dest_._y - rot_._y;

	def = GetRotationNormalize(def);
	rot_._y += def * 0.1f;

	rot_._y = GetRotationNormalize(rot_._y);

	// 弾の発射
	if(interface_manager_->input_manager()->CheckTrigger(INPUT_EVENT_SPACE))
	{
		CBulletManager* bullet_manager = interface_manager_->character_manager()->bullet_manager();
		CBullet* bullet = new CBullet(interface_manager_);

		bullet->Init();
		bullet->SetParameter(pos_,front_vector.RotationAxis(VECTOR3(0.0f,1.0f,0.0f),-(rot_._y + 180.0f) * MTH_DEGREE),1.0f,0);
		bullet_manager->Push(bullet);
	}

	interface_manager_->network_manager()->GetNetworkClient()->GetWinSock()->SendDataCharcter(&pos_,&rot_,0);
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	/*
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject3DManager* object_3d_manager = object_manager->object_3d_manager();

	// 描画
	object_3d_manager->Draw(object_key_,pos_,rot_,scale_,MATRIX4x4(),"");

	*/
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
}

//---------------------------------- EOF --------------------------------------
