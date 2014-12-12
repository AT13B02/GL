//*****************************************************************************
//
// �Փ˔���N���X
//
// Author		: Yuki Sakamoto
//
//*****************************************************************************


//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <list>

#include "collision_manager.h"
#include "../character_manager.h"

#include "../player/player.h"
#include "../player/player_manager.h"

#include "../bullet/bullet.h"
#include "../bullet/bullet_manager.h"

#include "common/common.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CCollisionManager::CCollisionManager(CCharacterManager* character_manager)
{
	character_manager_ = character_manager;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCollisionManager::~CCollisionManager(void)
{

}

//=============================================================================
// ������
//=============================================================================
bool CCollisionManager::Init(void)
{
	return true;
}

//=============================================================================
// �I������
//=============================================================================
void CCollisionManager::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CCollisionManager::Update(void)
{
	CPlayerManager* player_manager = character_manager_->player_manager();
	CBulletManager* bullet_manager = character_manager_->bullet_manager();
	std::list<CPlayer*> player_list = player_manager->character_list();
	std::list<CBullet*> bullet_list = bullet_manager->character_list();

	// �v���C���[�ƒe�̓����蔻��
	for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
	{
		for(auto bullet_it = bullet_list.begin();bullet_it != bullet_list.end();++bullet_it)
		{
			// �����蔻��

		}
	}
}

//=============================================================================
// ���̂Ƌ��̂̓����蔻�菈��
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
