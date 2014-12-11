//*****************************************************************************
//
// ���b�V���t�B�[���h�N���X
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "basic/application.h"

// graphic
#include "interface/graphic/vertex/vertex_3d.h"
#include "interface/graphic/object/object_3d/element/meshfield.h"
#include "interface/graphic/object/object_3d/object_3d_data.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/texture/texture.h"

// common
#include "common/common.h"

// general
#include "general/procedural/perlin_noise.h"

#include <time.h>

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �萔��`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMeshfield::CMeshfield(CDeviceHolder* device_holder)
	:	CObject3D(device_holder,OBJECT_3D_TYPE_RECTANGLE),
		number_grid_x_(1), number_grid_z_(1),
		length_grid_x_(1.0f), length_grid_z_(1.0f),
		number_vertex_x_(number_grid_x_ + 1), number_vertex_z_(number_grid_z_ + 1),
		p_height_map_(nullptr),
		p_face_normal_map_(nullptr),
		position_(0.0f, 0.0f),
		number_index_(4),
		p_vertex_3d_(nullptr),
		m_fMaxHeight(500.0f)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshfield::~CMeshfield(void)
{
}

//=============================================================================
// ������
//=============================================================================
bool CMeshfield::Init(void)
{
	return true;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshfield::Draw(CObject3DData* object_3d_data)
{
	MATRIX4x4 matrix;
	CTextureManager* texture_manager = object_3d_data->texture_manager();
	CTexture* texture = texture_manager->Get(object_3d_data->texture_name().c_str());

	matrix = GetWorldMatrix(object_3d_data);

	CObject3D::Draw(matrix,p_vertex_3d_,texture,object_3d_data->renderstate_manager(),object_3d_data->renderstate_list());
}

//=============================================================================
// �I��
//=============================================================================
void CMeshfield::Uninit (void)
{
	SAFE_RELEASE(p_vertex_3d_);

	SAFE_DELETE_ARRAY(p_height_map_);
	SAFE_DELETE_ARRAY(p_face_normal_map_);
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CMeshfield::Set(void)
{
	// �n�C�g�}�b�v����
	CreateHeightMap();
	
	// ���_����
	CreateVertexAndIndex();
}

//=============================================================================
// �O���b�h�������ݒ�
//=============================================================================
void CMeshfield::set_grid_number(const u32& grid_x, const u32& grid_z)
{
	number_grid_x_ = grid_x;
	number_grid_z_ = grid_z;

	number_vertex_x_ = grid_x + 1;
	number_vertex_z_ = grid_z + 1;
}

//=============================================================================
// �O���b�h���ݒ�
//=============================================================================
void CMeshfield::set_grid_length(const f32& length_x, const f32& length_z)
{
	length_grid_x_ = length_x;
	length_grid_z_ = length_z;
}

//=============================================================================
// �����擾
//=============================================================================
f32 CMeshfield::get_height(const VECTOR3& in_position, VECTOR3* p_out_normal)
{
	// �ȉ��̍��W�n�ɕϊ�����
	//     (0,0) ---------- (Width,0) ---x
	//         |			|
	//         |			|
	//         |			|
	//         |			|
	//         |			|
	// (0,Depth) ---------- (Width,Depth)
	//         |
	//         z
	f32 x =   in_position._x + number_grid_x_ * length_grid_x_ * 0.5f;
	f32 z =   in_position._z + number_grid_z_ * length_grid_z_ * 0.5f;

	// p0����p1�ւ̓x����
	f32 s;
	// p0����p2�ւ̓x����
	f32 t;
	
	// �I�u�W�F�N�g�̕ϊ����W���o��
	f32 fObjectX;
	f32 fObjectZ;
	
	// �ʃC���f�b�N�X(�l�p�`��)
	s32 nFaceX;
	s32 nFaceZ;
	
	// ���E����
	if(x < 0.0f)
	{
		fObjectX = 0.0f;
		nFaceX = 0;
	}
	else if(x >= number_grid_x_ * length_grid_x_)
	{
		fObjectX = (f32)number_grid_x_;
		nFaceX = number_grid_x_ - 1;
	}
	else
	{
		fObjectX = x / length_grid_x_;
		nFaceX = (s32)(x / length_grid_x_);
	}
	if(z < 0.0f)
	{
		fObjectZ = 0.0f;
		nFaceZ = 0;
	}
	else if(z >= number_grid_z_ * length_grid_z_)
	{
		fObjectZ = (f32)number_grid_z_;
		nFaceZ = number_grid_z_ - 1;
	}
	else
	{
		fObjectZ = z / length_grid_z_;
		nFaceZ = (s32)(z / length_grid_z_);
	}
	
	// p0����p1�ւ̓x����
	s = fObjectX - nFaceX;
	// p0����p2�ւ̓x����
	t = fObjectZ - nFaceZ;
	
	f32 fOffsetX = -(number_grid_x_ * length_grid_x_) * 0.5f;
	f32 fOffsetZ = -(number_grid_z_ * length_grid_z_) * 0.5f;
	f32 fHeight;
	
	VECTOR3 tempNormal;
	if(s + t < 1.0f)
	{
		// ���̎O�p�`
		VECTOR3 p0(// ����
			nFaceX * length_grid_x_ + fOffsetX,
			p_height_map_[nFaceZ * number_vertex_x_ + nFaceX],
			nFaceZ * length_grid_z_ + fOffsetZ);

		// �@���ݒ�
		if(nullptr != p_out_normal)
		{
			tempNormal = *p_out_normal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		else
		{
			tempNormal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		
		// �I�u�W�F�N�gy���W�ݒ�
		if(tempNormal._y < 0.00005f)
		{
			// �E�㍂��
			float p1 = p_height_map_[nFaceZ * number_vertex_x_ + nFaceX + 1];
			// ��������
			float p2 = p_height_map_[(nFaceZ + 1) * number_vertex_x_ + nFaceX];
			// p0 -> p1 �����x�N�g��
			//float h0 = p1 - p0.y;
			// p0 -> p2 �����x�N�g��
			//float h1 = p2 - p0.y;
			fHeight = p0._y + (p1 - p0._y) * s + (p2 - p0._y) * t;
		}
		else
		{
			// ���ς̕��������Z�o
			fHeight = p0._y - (tempNormal._x * (in_position._x - p0._x) + tempNormal._z * (in_position._z - p0._z)) / tempNormal._y;
		}
	}
	else
	{
		// �E�̎O�p�`
		VECTOR3 p3(// �E��
			(nFaceX + 1) * length_grid_x_ + fOffsetX,
			p_height_map_[(nFaceZ + 1) * number_vertex_x_ + nFaceX + 1],
			(nFaceZ + 1) * length_grid_z_ + fOffsetZ);
	
		// �@���ݒ�
		if(nullptr != p_out_normal)
		{
			tempNormal = *p_out_normal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		else
		{
			tempNormal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		
		// �I�u�W�F�N�gy���W�ݒ�
		if(tempNormal._y < 0.00005f)
		{
			// ��������
			float p2 = p_height_map_[(nFaceZ + 1) * number_vertex_x_ + nFaceX];
			// �E�㍂��
			float p1 = p_height_map_[nFaceZ * number_vertex_x_ + nFaceX + 1];
			// p3 -> p2 �����x�N�g��
			//float h1 = p2 - p0.y;
			// p3 -> p1 �����x�N�g��
			//float h0 = p1 - p0.y;
			fHeight = p3._y + (p2 - p3._y) * (1 - s) + (p1 - p3._y) * (1 - t);
		}
		else
		{
			// ���ς̕��������Z�o
			fHeight = p3._y - (tempNormal._x * (in_position._x - p3._x) + tempNormal._z * (in_position._z - p3._z)) / tempNormal._y;
		}
	}

	// ������Ԃ�
	return fHeight;
}

//=============================================================================
// �n�C�g�}�b�v����
//=============================================================================
void CMeshfield::CreateHeightMap()
{
	if(nullptr != p_height_map_)
	{
		SAFE_DELETE_ARRAY(p_height_map_);
	}

	// ����
	p_height_map_ = new f32[number_vertex_x_ * number_vertex_z_];

	PerlinNoise noise;
	//noise.SetSeed(time((time_t*)NULL));
	noise.SetSeed(0);
	noise.SetPersistence(0.7f);
	u32 idx = 0;
	f32 min_height = FLT_MAX;
	for(u32 z = 0; z < number_vertex_z_; z++)
	{
		for(u32 x = 0; x < number_vertex_x_; x++)
		{
			p_height_map_[idx] = m_fMaxHeight * (noise.GetNoise((float)x, (float)z) * 0.5f + 0.5f);
			if(min_height > p_height_map_[idx])
			{
				min_height = p_height_map_[idx];
			}
			idx++;
		}
	}
	// ��ԒႢ�ꏊ��0�ɍ��킹��
	for(u32 i = 0; i < number_vertex_z_ * number_vertex_x_; i++)
	{
		p_height_map_[i] -= min_height;
	}
}

//=============================================================================
// ���_�ƃC���f�b�N�X�𐶐�
//=============================================================================
void CMeshfield::CreateVertexAndIndex()
{
	if(nullptr != p_vertex_3d_)
	{
		SAFE_RELEASE(p_vertex_3d_);
	}

	p_vertex_3d_ = CVertex3D::Create(device_holder_, number_vertex_x_ * number_vertex_z_);
	p_vertex_3d_->CreateIndex(2 * (number_grid_z_ * (number_grid_x_ + 2) - 1));// (x + 1) * 2 * z + (z - 1) * 2 ���܂Ƃ߂�
	
	CVertex3D::VERTEX_3D* pVertex3D = nullptr;
	CVertex3D::VERTEX_3D_INDEX* pIndex = nullptr;
	
	// ���_�A�C���f�b�N�X���b�N
	p_vertex_3d_->Lock(&pVertex3D, &pIndex);
	
	// ���_�̒l�ݒ�
	SetVertex(
		pVertex3D->_position,
		pVertex3D->_color,
		pVertex3D->_texcoord);
	
	// �@���}�b�v�ݒ�
	CreateNormalMap(pVertex3D->_position);

	// �@���ݒ�
	SetNormal(pVertex3D->_normal);

	// �C���f�b�N�X�ݒ�
	SetIndex(pIndex->_position);
	SetIndex(pIndex->_normal);
	SetIndex(pIndex->_color);
	SetIndex(pIndex->_texcoord);

	// ���_�����A�����b�N
	p_vertex_3d_->Unlock();
}

//=============================================================================
// ���_�̒l�ݒ�
//=============================================================================
void CMeshfield::SetVertex(VECTOR3* p_position, COLOR4F* p_color, VECTOR2* p_texcoord)
{
	u32 idx = 0;
	for(u32 z = 0; z < number_vertex_z_; z++)
	{
		for(u32 x = 0; x < number_vertex_x_; x++)
		{
			p_position[idx]._x	= (f32)(x * length_grid_x_ - number_grid_x_ * length_grid_x_ * 0.5f);
			p_position[idx]._z	= (f32)(z * length_grid_z_ - number_grid_z_ * length_grid_z_ * 0.5f);

			p_position[idx]._y	= p_height_map_[idx];
			
			p_color[idx]._red	= 1.0f;
			p_color[idx]._green	= 1.0f;
			p_color[idx]._blue	= 1.0f;
			p_color[idx]._alpha	= 1.0f;

			p_texcoord[idx]	= VECTOR2((f32)x, (f32)z);

			// �C���f�b�N�X�C���N�������g
			idx++;
		}
	}
}

//=============================================================================
// �@���}�b�v����
//=============================================================================
void CMeshfield::CreateNormalMap(VECTOR3* p_position)
{
	if(nullptr != p_face_normal_map_)
	{
		SAFE_DELETE_ARRAY(p_face_normal_map_);
	}

	p_face_normal_map_ = new VECTOR3[number_grid_x_ * number_grid_z_ * 2];

	// �ʖ@���}�b�v�쐬
	VECTOR3 v0;
	VECTOR3 v1;
	VECTOR3 nor;
	for(u32 z = 0; z < number_grid_z_; z++)
	{
		for(u32 x = 0; x < number_grid_x_; x++)
		{
			// ���_�C���f�b�N�X
			u32 uVtxIndex = z * (number_grid_x_ + 1) + x;
			// �ʖ@���C���f�b�N�X
			u32 uFaceIndex = 2 * (z * number_grid_x_ + x);
			
			// �ʂ���1
			// �O�ϗp�x�N�g���Z�o
			v0 = p_position[uVtxIndex + number_grid_x_ + 1] - p_position[uVtxIndex];
			v1 = p_position[uVtxIndex + 1] - p_position[uVtxIndex];
			// �O�όv�Z
			nor = v0.CrossProduct(v1);
			// �@�����K��
			nor.Normalize();
			// �@���}�b�v�ݒ�
			p_face_normal_map_[uFaceIndex] = nor;

			// �ʂ���2
			// �O�ϗp�x�N�g���Z�o
			v0 = p_position[uVtxIndex + number_grid_x_ + 1] - p_position[uVtxIndex + 1];
			v1 = p_position[uVtxIndex + number_grid_x_ + 2] - p_position[uVtxIndex + 1];
			// �O�όv�Z
			nor = v0.CrossProduct(v1);
			// �@�����K��
			nor.Normalize();
			// �@���}�b�v�ݒ�
			p_face_normal_map_[uFaceIndex + 1] = nor;
		}
	}
}

//=============================================================================
// �@���ݒ�
//=============================================================================
void CMeshfield::SetNormal(VECTOR3* p_normal)
{
	// �ʖ@������
	DWORD number_face_normal = number_grid_x_ * number_grid_z_ * 2;

	// �@���ݒ�
	VECTOR3 nor;
	for(u32 z = 0; z < number_vertex_z_; z++)
	{
		for(u32 x = 0; x < number_vertex_x_; x++)
		{
			// ���_�C���f�b�N�X
			u32 uVtxIndex = z * number_vertex_x_ + x;
			// �ʃC���f�b�N�X
			u32 uFaceIndex;

			// ��[
			if(z == 0)
			{
				// �����
				if(x == 0)
				{
					nor = p_face_normal_map_[0];
				}
				// �E���
				else if(x == number_grid_x_)
				{
					nor = p_face_normal_map_[(number_grid_x_ - 1) * 2] + p_face_normal_map_[(number_grid_x_ - 1) * 2 + 1];
				}
				// ���̑���[
				else
				{
					uFaceIndex = (x - 1) * 2;
					nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + 1] + p_face_normal_map_[uFaceIndex + 2];
				}
			}
			// ���[
			else if(z == number_grid_z_)
			{
				// ������
				if(x == 0)
				{
					nor = p_face_normal_map_[number_grid_x_ * 2 * (number_grid_z_ - 1)] + p_face_normal_map_[number_grid_x_ * 2 * (number_grid_z_ - 1) + 1];
				}
				// �E����
				else if(x == number_grid_x_)
				{
					nor = p_face_normal_map_[number_face_normal - 1];
				}
				// ���̑����[
				else
				{
					uFaceIndex = (x - 1) * 2 + (number_grid_z_ - 1) * (number_grid_x_ * 2) + 1;
					nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + 1] + p_face_normal_map_[uFaceIndex + 2];
				}
			}
			// ���[
			else if(x == 0)
			{
				uFaceIndex = (z - 1) * number_grid_x_ * 2;
				nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + 1] + p_face_normal_map_[uFaceIndex + number_grid_x_ * 2];
			}
			// �E�[
			else if(x == number_grid_x_)
			{
				uFaceIndex = (z - 1) * number_grid_x_ * 2 + (number_grid_x_ * 2 - 1);
				nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + number_grid_x_ * 2 - 1] + p_face_normal_map_[uFaceIndex + number_grid_x_ * 2];
			}
			// ����
			else
			{
				uFaceIndex = (z - 1) * number_grid_x_ * 2 + x * 2 - 1;
				u32 nNextRowFaceIndex = uFaceIndex + number_grid_x_ * 2 - 1;
				// �g�p����ʖ@���� 6 ��
				nor = p_face_normal_map_[uFaceIndex] +
					  p_face_normal_map_[uFaceIndex + 1] +
					  p_face_normal_map_[uFaceIndex + 2] +
					  p_face_normal_map_[nNextRowFaceIndex] +
					  p_face_normal_map_[nNextRowFaceIndex + 1] +
					  p_face_normal_map_[nNextRowFaceIndex + 2];
			}
			
			// �@���ݒ�
			nor.Normalize();
			p_normal[uVtxIndex] = nor;
		}
	}
}

//=============================================================================
// �C���f�b�N�X�ݒ�
//=============================================================================
void CMeshfield::SetIndex(u32* p_index)
{
	// �C���f�b�N�X�ݒ�
	for(u32 z = 0; z < number_grid_z_; z++)
	{
		// ��ԍ��ォ��n�߂�
		p_index[0] = z * number_vertex_x_;
		for(u32 x = 0; x < number_grid_x_; x++)
		{
			p_index[x * 2 + 1]	= (z + 1) * number_vertex_x_ + x;
			p_index[x * 2 + 2]	= z * number_vertex_x_ + (x + 1);
		}
		p_index[number_grid_x_ * 2 + 1] = (z + 1) * (number_grid_x_ + 1) + number_grid_x_;

		if(z != (number_grid_z_ - 1))
		{
			p_index[number_grid_x_ * 2 + 2] = (z + 1) * (number_grid_x_ + 1) + number_grid_x_;
			p_index[number_grid_x_ * 2 + 3] = (z + 1) * (number_grid_x_ + 1);
		}
		// �A�h���X�̃C���N�������g
		p_index += (number_grid_x_ * 2 + 4);
	}
}

//---------------------------------- EOF --------------------------------------
