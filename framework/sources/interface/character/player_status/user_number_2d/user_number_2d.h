//*****************************************************************************
//
// ���[�U�[�i���o�[(2D)�N���X
//
// Author		: Kazuma Ooigawa
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _USER_NUMBER_2D_H_
#define _USER_NUMBER_2D_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "common/math/math.h"
#include "../../character_interface.h"

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
class CRectangle2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CUserNumber2D : public CCharacterInterface
{
public:
	// �R���X�g���N�^
	CUserNumber2D(CInterfaceManager* interface_manager , s32 max_length );

	// �f�X�g���N�^
	~CUserNumber2D(void);

	// ������
	bool Init(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �I��
	void Uninit(void);

	// �p�����[�^�̐ݒ�
	void SetParameter(const VECTOR2& position , const s32& player_id );

	//�ʒu�擾
	VECTOR2 position( void ){ return position_; }

	//�v���C���[ID�擾
	s32 player_id( void ){ return player_id_;}

	//���C�t�擾
	s32 user_number( void ){ return user_number_;}

	//�ʒu�Z�b�g
	void set_position( const VECTOR2& pos ){ position_ = pos ;}

	//���[�U�[�i���o�[�Z�b�g
	void set_user_number( const s32 user_number ){ user_number_ = user_number;}

	//����
	void Erase( void );
private:
	u32 object_key_;
	VECTOR2 position_;
	u32 max_user_number_;
	s32 user_number_;
	u32 max_length_;
	s32 length_;
	s32 player_id_;
	CRectangle2D* rectangle_2d_;
	CInterfaceManager* interface_manager_;
};
#endif //_USER_NUMBER_2D_H_
//---------------------------------- EOF --------------------------------------