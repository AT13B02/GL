//*****************************************************************************
//
// ���C�t�N���X
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _LIFE_H_
#define _LIFE_H_

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
class CLife : public CCharacterInterface
{
public:
	// �R���X�g���N�^
	CLife(CInterfaceManager* interface_manager , s32 max_life , s32 max_length );

	// �f�X�g���N�^
	~CLife(void);

	// ������
	bool Init(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �I��
	void Uninit(void);

	// �p�����[�^�̐ݒ�
	void SetParameter(const VECTOR3& position , const s32& player_id );

	//�ʒu�擾
	VECTOR3 position( void ){ return position_; }

	//�v���C���[ID�擾
	s32 player_id( void ){ return player_id_;}

	//���C�t�擾
	s32 life( void ){ return life_;}

	//�ʒu�Z�b�g
	void set_position( const VECTOR3& pos ){ position_ = pos ;}

	//���C�t�Z�b�g
	void set_life( const s32 life ){ life_ = life;}

	//����
	void Erase( void );
private:
	u32 object_key_;
	VECTOR3 position_;
	u32 max_life_;
	s32 life_;
	u32 max_length_;
	s32 length_;
	s32 player_id_;
	CBillboard* object_bill_;
	CInterfaceManager* interface_manager_;
};
#endif //_LIFE_H_
//---------------------------------- EOF --------------------------------------