//*****************************************************************************
//
// �����N���X
//
// Author		: Kazuma Ooigawa
//				: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

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
class CExplosion : public CCharacterInterface
{
public:
	// �R���X�g���N�^
	CExplosion(CInterfaceManager* interface_manager);

	// �f�X�g���N�^
	~CExplosion(void);

	// ������
	bool Init(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �I��
	void Uninit(void);

	// �p�����[�^�̐ݒ�
	void SetParameter(const VECTOR3& position, const s16 u_division_num, const s16 v_division_num, const s16 animation_change_count  );

	//�ʒu�擾
	VECTOR3 position( void ){ return position_; }

	//�ʒu�Z�b�g
	void set_position( const VECTOR3& pos ){ position_ = pos ;}

	//�e����
	void Erase( void );

private:
	static const f32 DEFAULT_RADIUS;
	u32 object_key_;
	VECTOR3 position_;
	f32 radius_;

	CBillboard *billboard_;					//�r���{�[�h
	s16 u_division_num_;						//������
	s16 v_division_num_;						//������

	s16 u_division_count;						//����
	s16 v_division_count;						//����

	s16 animation_change_count_;			//�A�j���[�V�����ύX�J�E���g
	s16 animation_count_;					//�J�E���^

	//�e�N�X�`��
	f32 left_; 
	f32 right_;
	f32 top_;
	f32 bottom_;

	CInterfaceManager* interface_manager_;
};
#endif //_BULLET_H_
//---------------------------------- EOF --------------------------------------
