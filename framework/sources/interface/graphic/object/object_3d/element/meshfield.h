//*****************************************************************************
//
// �t�B�[���h�N���X
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************
#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/element/object_3d.h"

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
class CVertex3D;
struct COLOR4F;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMeshfield : public CObject3D
{
public:
	// �R���X�g���N�^
	CMeshfield(CDeviceHolder* device_holder);

	// �f�X�g���N�^
	virtual ~CMeshfield(void);

	// ����������
	bool Init(void);

	// �`�揈��
	void Draw(CObject3DData* pObject3DData);

	// �I������
	void Uninit(void);

	// ���_���̐ݒ�
	virtual void Set(void);

	// �O���b�h�������ݒ�
	void set_grid_number(const u32& grid_x, const u32& grid_z);

	// �O���b�h���ݒ�
	void set_grid_length(const f32& length_x, const f32& length_z);

	// height����
	void set_height_seed(const s32& seed);

	// �����擾
	f32 get_height(const VECTOR3& in_position, VECTOR3* p_out_normal);
	
	// �t�B�[���hX���W�ő�l
	f32 get_max_x(void);
	// �t�B�[���hX���W�ŏ��l
	f32 get_min_x(void);
	
	// �t�B�[���hZ���W�ő�l
	f32 get_max_z(void);
	// �t�B�[���hZ���W�ŏ��l
	f32 get_min_z(void);

protected:

private:
	// �n�C�g�}�b�v����
	void CreateHeightMap();

	// ���_�ƃC���f�b�N�X�𐶐�
	void CreateVertexAndIndex();

	// ���_�̒l�ݒ�
	void SetVertex(VECTOR3* p_position, COLOR4F* p_color, VECTOR2* p_texcoord);
	
	// �@���}�b�v����
	void CreateNormalMap(VECTOR3* p_position);

	// �@���ݒ�
	void SetNormal(VECTOR3* p_normal);

	// �C���f�b�N�X�ݒ�
	void SetIndex(u32* p_index);

	// �t�B�[���h�̎l����ݒ�
	void SetFieldRect();

private:
	// �O���b�h��
	u32 number_grid_x_;
	u32 number_grid_z_;

	// �O���b�h��
	f32 length_grid_x_;
	f32 length_grid_z_;

	// ���_��
	u32 number_vertex_x_;
	u32 number_vertex_z_;

	// �V�[�h
	s32 seed_;

	// �n�C�g�}�b�v
	f32 *p_height_map_;

	// �ʖ@���}�b�v
	VECTOR3 *p_face_normal_map_;

	// �l���̍��W
	f32 max_x_;
	f32 min_x_;
	f32 max_z_;
	f32 min_z_;

	// ���_���W
	VECTOR2 position_;

	// �C���f�b�N�X��
	u32 number_index_;

	// ���_���
	CVertex3D* p_vertex_3d_;

	// �ő�̍���
	f32 m_fMaxHeight;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
