//*****************************************************************************
//
// 衝突判定クラス
//
// Author		: Yuki Sakamoto
//
//*****************************************************************************


//*****************************************************************************
// インクルード
//*****************************************************************************
#include <list>

#include "collision_manager.h"
#include "../character_manager.h"

#include "../player/player.h"
#include "../player/player_manager.h"

#include "../bullet/bullet.h"
#include "../bullet/bullet_manager.h"

#include "../field/field.h"
#include "../field/field_manager.h"

#include "common/common.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CCollisionManager::CCollisionManager(CCharacterManager* character_manager)
{
	character_manager_ = character_manager;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCollisionManager::~CCollisionManager(void)
{

}

//=============================================================================
// 初期化
//=============================================================================
bool CCollisionManager::Init(void)
{
	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCollisionManager::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CCollisionManager::Update(void)
{
	JudgePlayerAndBullet();
	JudgeFieldIn();
	JudgeFieldOn();

}

//=============================================================================
// プレイヤーと弾の当たり判定処理
//=============================================================================
void CCollisionManager::JudgePlayerAndBullet(void)
{
	CPlayerManager* player_manager = character_manager_->player_manager();
	CBulletManager* bullet_manager = character_manager_->bullet_manager();
	std::list<CPlayer*> player_list = player_manager->character_list();
	std::list<CBullet*> bullet_list = bullet_manager->character_list();

	// プレイヤーと弾の当たり判定
	for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
	{
		for(auto bullet_it = bullet_list.begin();bullet_it != bullet_list.end();++bullet_it)
		{
			// 当たり判定
			if(JudgeSphereCross((*player_it)->pos(),10,(*bullet_it)->position(),10))
			{
				//リザルトへ移動

			}
		}
	}
}

//=============================================================================
// フィールド内にいるかどうか判定
//=============================================================================
void CCollisionManager::JudgeFieldIn(void)
{
	CPlayerManager* player_manager = character_manager_->player_manager();
	CBulletManager* bullet_manager = character_manager_->bullet_manager();
	CFieldManager* field_manager = character_manager_->field_manager();
	std::list<CPlayer*> player_list = player_manager->character_list();
	std::list<CBullet*> bullet_list = bullet_manager->character_list();
	std::list<CField*> field_list = field_manager->character_list();

	f32 FieldXmax;
	f32 FieldZmax;
	f32 FieldXmin;
	f32 FieldZmin;

	VECTOR3 pos;

	// フィールド
	for(auto field_it = field_list.begin();field_it != field_list.end();++field_it)
	{
		FieldXmax=(*field_it)->get_max_x();
		FieldZmax=(*field_it)->get_max_z();
		FieldXmin=(*field_it)->get_min_x();
		FieldZmin=(*field_it)->get_min_z();

		// プレイヤー
		for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
		{
			pos=(*player_it)->pos();
			// 当たり判定
			if(pos._x>=FieldXmax)
			{
				//フィールド外にいる時の処理
				pos._x=FieldXmax;
				(*player_it)->set_pos(pos);

			}
			// 当たり判定
			if(pos._z>=FieldZmax)
			{
				//フィールド外にいる時の処理
				pos._z=FieldZmax;
				(*player_it)->set_pos(pos);
			}

			// 当たり判定
			if(pos._x<=FieldXmin)
			{
				//フィールド外にいる時の処理
				pos._x=FieldXmin;
				(*player_it)->set_pos(pos);
			}

			// 当たり判定
			if(pos._z<=FieldZmin)
			{
				//フィールド外にいる時の処理
				pos._z=FieldZmin;
				(*player_it)->set_pos(pos);
			}
		}

		//弾
		for(auto bullet_it = bullet_list.begin();bullet_it != bullet_list.end();++bullet_it)
		{
			pos=(*bullet_it)->position();
			// 当たり判定
			if(pos._x>=FieldXmax||pos._z>=FieldZmax||pos._x<=FieldXmin||pos._z<=FieldZmin)
			{
				//フィールド外にいる時の処理

			}
		}
	}
}

//=============================================================================
// 地面の上に居るかどうか判定
//=============================================================================
void CCollisionManager::JudgeFieldOn(void)
{
	CPlayerManager* player_manager = character_manager_->player_manager();
	std::list<CPlayer*> player_list = player_manager->character_list();
	CFieldManager* field_manager = character_manager_->field_manager();
	std::list<CField*> field_list = field_manager->character_list();

	VECTOR3 pos,up;
	f32 height;
	up._x=0;
	up._y=1;
	up._z=0;

	//フィールド
	for(auto field_it = field_list.begin();field_it != field_list.end();++field_it)
	{
		// プレイヤー
		for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
		{
			pos=(*player_it)->pos();
			height=(*field_it)->get_height(pos,&up);
			// 当たり判定
			//if(pos._y<=height)
			{
				pos._y=height;
				(*player_it)->set_pos(pos);
			}

		}
	}

}

//=============================================================================
// 球体と球体の当たり判定処理
//=============================================================================
bool CCollisionManager::JudgeSphereCross(VECTOR3 p1,float r1,VECTOR3 p2,float r2)
{
	if((p2._x-p1._x)*(p2._x-p1._x)+(p2._y-p1._y)*(p2._y-p1._y)+(p2._z-p1._z)*(p2._z-p1._z)<=(r1+r2)*(r1+r2))
	{
		return true;
	}

	return false;
}

//---------------------------------- EOF --------------------------------------
