//*****************************************************************************
//
// �o���b�g�N���X
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _BULLET_H_
#define _BULLET_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "common/math/math.h"
#include "../character_interface.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CInterfaceManager;
class CBillboard;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CBullet : public CCharacterInterface
{
public:
	// �R���X�g���N�^
	CBullet(CInterfaceManager* interface_manager);

	// �f�X�g���N�^
	~CBullet(void);

	// ������
	bool Init(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �I��
	void Uninit(void);

	// �p�����[�^�̐ݒ�
	void SetParameter(const VECTOR3& position,const VECTOR3& vector,const f32& speed , const s32& player_id );

	//�ʒu�擾
	VECTOR3 position( void ){ return position_; }

	//�����擾
	VECTOR3 vector( void ){ return vector_; }

	//���a�擾
	f32 radius( void ){ return radius_;}

	//�e���擾
	f32 speed( void ){ return speed_;}

	//�v���C���[ID�擾
	s32 player_id( void ){ return player_id_;}

	//�ʒu�Z�b�g
	void set_position( const VECTOR3& pos ){ position_ = pos ;}

	//�����Z�b�g
	void set_vector( const VECTOR3& vec ){ vector_ = vec ;}

	//�e����
	void Erase( void );
private:
	static const f32 DEFAULT_RADIUS;
	u32 object_key_;
	VECTOR3 position_;
	VECTOR3 vector_;
	f32 speed_;
	f32 radius_;
	s32 player_id_;
	CInterfaceManager* interface_manager_;
};
#endif //_BULLET_H_
//---------------------------------- EOF --------------------------------------
