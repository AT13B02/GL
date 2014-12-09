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
	void SetParameter(const VECTOR3& position,const VECTOR3& vector,const f32& speed);

private:
	u32 object_key_;
	VECTOR3 position_;
	VECTOR3 vector_;
	f32 speed_;
	CInterfaceManager* interface_manager_;

};
#endif //_BULLET_H_
//---------------------------------- EOF --------------------------------------