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
	void Draw(CObject3DData* object_3d_data);

	// �I������
	void Uninit(void);

	// ���_���̐ݒ�
	void Set(void);

	// �O���b�h�������ݒ�
	void set_number_grid(const u32& grid_x, const u32& grid_z){number_grid_x_ = grid_x;number_grid_z_ = grid_z;number_vertex_x_ = grid_x + 1;number_vertex_z_ = grid_z + 1;}

	// �O���b�h���ݒ�
	void set_length_grid(const f32& length_x,const f32& length_z){length_grid_x_ = length_x;length_grid_z_ = length_z;}

	// height����
	void set_height_seed(const s32& height_seed){height_seed_ = height_seed;}

	// �����擾
	f32 GetHeight(const VECTOR3& in_position, VECTOR3* p_out_normal) const;

	// �t�B�[���hX���W�ő�l
	const f32& max_x(void) const {return max_x_;}

	// �t�B�[���hX���W�ŏ��l
	const f32& min_x(void) const {return min_x_;}

	// �t�B�[���hZ���W�ő�l
	const f32& max_z(void) const {return max_z_;}

	// �t�B�[���hZ���W�ŏ��l
	const f32& min_z(void) const {return min_z_;}

protected:

private:
	// �n�C�g�}�b�v����
	void CreateHeightMap(void);

	// ���_�ƃC���f�b�N�X�𐶐�
	void CreateVertexAndIndex(void);

	// ���_�̒l�ݒ�
	void SetVertex(VECTOR3* p_out_position,COLOR4F* p_out_color,VECTOR2* p_out_texcoord);
	
	// �@���}�b�v����
	void CreateNormalMap(const VECTOR3* p_position);

	// �@���ݒ�
	void SetNormal(VECTOR3* p_normal);

	// �C���f�b�N�X�ݒ�
	void SetIndex(u32* p_out_index);

	// �t�B�[���h�̎l����ݒ�
	void SetFieldRect(void);

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
	s32 height_seed_;

	// �n�C�g�}�b�v
	f32* p_height_map_;

	// �ʖ@���}�b�v
	VECTOR3* p_face_normal_map_;

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
