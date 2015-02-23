//*****************************************************************************
//
// �v���C���[�N���X
//
// Author		: Chiharu Kamiyama
//				: Kenji Kabutomori
//
//*****************************************************************************


//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

//*****************************************************************************
// warning����
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/basic.h"
#include "common/math/vector/vector3.h"

//character
#include "player_manager.h"
#include "interface/character/character_interface.h"


//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
static const int kDefaultDamage = 10;

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CPlayer : public CCharacterInterface
{
public:
	// �R���X�g���N�^
	CPlayer(CInterfaceManager* interface_manager);

	// �f�X�g���N�^
	~CPlayer(void);

	// ����������
	bool Init(void);

	// �X�V����
	void Update(void);

	// �I������
	void Uninit(void);

	// �`�揈��
	void Draw(void);

	// �|�W�V�����̎擾
	const VECTOR3& position(void) const {return position_;}

	// �|�W�V�����̐ݒ�
	void set_position(const VECTOR3& position){position_ = position;}

	// �p�x�̎擾
	const VECTOR3& rotation(void) const {return rotation_;}

	// �p�x�̐ݒ�
	void set_rotation(const VECTOR3& rotation){rotation_ = rotation;}

	// id�̎擾
	int player_id(void);
	
	// ���S�t���O�A�N�Z�T
	bool death_flag(void){return death_flag_;};
	void SetDeathFlag(bool flag);

	// HP�A�N�Z�T
	void set_hp(s16 hp){hp_ = hp;};
	s16 hp(void){return hp_;};

	// �_���[�W�֐�
	void Damage(int damage);
	
	// �v���C���[�ړ������擾
	const VECTOR3& get_move_vector();

	// �v���C���[�ړ��X�s�[�h�擾
	const f32 get_move_speed();

protected:
	// �C���^�[�t�F�[�X�}�l�[�W���[�̃|�C���^
	CInterfaceManager* interface_manager_;

	// �I�u�W�F�N�g�L�[
	u32 object_key_;

	// �e��l
	VECTOR3 position_;
	VECTOR3 rotation_;
	VECTOR3 scale_;
	VECTOR3 move_vector_;
	s16		hp_;

private:
	// �X�s�[�h
	static const f32 SPEED;
	static const f32 SPEED_DEST;
	static const f32 ROTATION_DEST;
	static const f32 BULLET_LAUNCH_HEIGHT_OFFSET;
	//�ړ��ڕW�l�ϐ�
	VECTOR3 rotation_dest_;
	bool update_;

	bool death_flag_;
};

//---------------------------------- EOF --------------------------------------

#endif // _PLAYER_H_