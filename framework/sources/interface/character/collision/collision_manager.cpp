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

#include "../field/field.h"
#include "../field/field_manager.h"

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
	JudgePlayerAndBullet();
	JudgeFieldIn();
	JudgeFieldOn();

}

//=============================================================================
// �v���C���[�ƒe�̓����蔻�菈��
//=============================================================================
void CCollisionManager::JudgePlayerAndBullet(void)
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
			if(JudgeSphereCross((*player_it)->pos(),10,(*bullet_it)->position(),10))
			{
				//���U���g�ֈړ�

			}
		}
	}
}

//=============================================================================
// �t�B�[���h���ɂ��邩�ǂ�������
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

	// �t�B�[���h
	for(auto field_it = field_list.begin();field_it != field_list.end();++field_it)
	{
		FieldXmax=(*field_it)->get_max_x();
		FieldZmax=(*field_it)->get_max_z();
		FieldXmin=(*field_it)->get_min_x();
		FieldZmin=(*field_it)->get_min_z();

		// �v���C���[
		for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
		{
			pos=(*player_it)->pos();
			// �����蔻��
			if(pos._x>=FieldXmax)
			{
				//�t�B�[���h�O�ɂ��鎞�̏���
				pos._x=FieldXmax;
				(*player_it)->set_pos(pos);

			}
			// �����蔻��
			if(pos._z>=FieldZmax)
			{
				//�t�B�[���h�O�ɂ��鎞�̏���
				pos._z=FieldZmax;
				(*player_it)->set_pos(pos);
			}

			// �����蔻��
			if(pos._x<=FieldXmin)
			{
				//�t�B�[���h�O�ɂ��鎞�̏���
				pos._x=FieldXmin;
				(*player_it)->set_pos(pos);
			}

			// �����蔻��
			if(pos._z<=FieldZmin)
			{
				//�t�B�[���h�O�ɂ��鎞�̏���
				pos._z=FieldZmin;
				(*player_it)->set_pos(pos);
			}
		}

		//�e
		for(auto bullet_it = bullet_list.begin();bullet_it != bullet_list.end();++bullet_it)
		{
			pos=(*bullet_it)->position();
			// �����蔻��
			if(pos._x>=FieldXmax||pos._z>=FieldZmax||pos._x<=FieldXmin||pos._z<=FieldZmin)
			{
				//�t�B�[���h�O�ɂ��鎞�̏���

			}
		}
	}
}

//=============================================================================
// �n�ʂ̏�ɋ��邩�ǂ�������
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

	//�t�B�[���h
	for(auto field_it = field_list.begin();field_it != field_list.end();++field_it)
	{
		// �v���C���[
		for(auto player_it = player_list.begin();player_it != player_list.end();++player_it)
		{
			pos=(*player_it)->pos();
			height=(*field_it)->get_height(pos,&up);
			// �����蔻��
			//if(pos._y<=height)
			{
				pos._y=height;
				(*player_it)->set_pos(pos);
			}

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
