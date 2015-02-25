//*****************************************************************************
//
// �^�C�g���N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _SCENE_MATCH_H_
#define _SCENE_MATCH_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "scene/scene.h"

#include "common/math/vector/vector2.h"
#include "common/math/vector/vector3.h"

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
// �N���X�̑O���錾
//*****************************************************************************
class CSound;
class CRectangle2D;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CSceneMatch : public CScene
{
public:
	// �R���X�g���N�^
	CSceneMatch(CInterfaceManager* interface_manager);

	// �f�X�g���N�^
	virtual ~CSceneMatch(void);

	// ������
	bool Init(void);

	// �X�V
	void Update(void);

	// �`��
	void Draw(void);

	// �I��
	void Uninit(void);

	// ���[�h
	void Load(void);

	// �����̃t�@�N�g���[�̍쐬
	CSceneFactory* MakeFactory(void);

protected:

private:

	typedef enum TEXTURE_TYPE_
	{
		TEXTURE_TYPE_LOGO,
		TEXTURE_TYPE_PLAYER1,
		TEXTURE_TYPE_PLAYER2,
		TEXTURE_TYPE_PLAYER3,
		TEXTURE_TYPE_PLAYER4,
		TEXTURE_TYPE_HOST_DECISION,
		TEXTURE_TYPE_PLAYER1_READY,
		TEXTURE_TYPE_PLAYER2_READY,
		TEXTURE_TYPE_PLAYER3_READY,
		TEXTURE_TYPE_PLAYER4_READY,
		TEXTURE_TYPE_MAX,
	}TEXTURE_TYPE;

	static const char* p_texture_names[TEXTURE_TYPE_MAX];

	static const int PLAYER_MAX = 4;
	static const float PLAYER_DISP_OFFSET_X;
	static const float PLAYER_DISP_OFFSET_Y;
	static const float PLAYER_DISP_START_Y;

	static const float PLAYER_DISP_READY_OFFSET_X;
	static const float PLAYER_DISP_READY_OFFSET_Y;
	static const float PLAYER_DISP_READY_START_Y;

	static const VECTOR2 HOST_DECITION_DEFAULT_POS;
	static const VECTOR2 LOGO_DEFAULT_POS;
	u32 test_object_key_;
	u32 test_2d_key_;


	u32 player_Disp_2d_key_[PLAYER_MAX]; //�v���C���[�}�b�`���O�\��
	u32 player_ready_disp_2d_key_[PLAYER_MAX]; //�v���C���[�}�b�`���O�����\��
	u32 host_decision_key_;				 //�z�X�g������������Ƃ��ɕK�v
	u32 logo_key_;						 //���S�\���ɕK�v

	CRectangle2D* p_rectRedy[PLAYER_MAX];
	CRectangle2D* p_rect_all_ready_logo;

	
	//TODO
	static const u32 FLASH_ALL_TIME = 40;//�_�ł̑S�̎���
	bool draw_flag_;
	u32 flash_timer_;					 //�_�ŗp�^�C�}�[
	VECTOR3 player_Disp_2d_pos_;

	bool flag[ PLAYER_MAX ];

	bool changeFlag;
};

#endif	// _SCENE_TITLE_H_

//---------------------------------- EOF --------------------------------------
