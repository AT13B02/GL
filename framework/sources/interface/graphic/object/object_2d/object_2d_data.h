//*****************************************************************************
//
// �I�u�W�F�N�g2D�f�[�^�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _OBJECT_2D_DATA_H_
#define _OBJECT_2D_DATA_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// stl
#include <string>

// basic
#include "basic/basic.h"

// common
#include "common/math/math.h"

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

class CObject2D;
class CTexture;
class CRenderstate;
class CCamera;
class CModelManager;
class CTextureManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CObject2DData : public CBasic
{
public:
	// �R���X�g���N�^
	CObject2DData(void);

	// �f�X�g���N�^
	~CObject2DData(void);

	// ������
	bool Init(void);

	// �`�揈��
	void Draw(void);

	// ������
	void Uninit(void);

	//-----------------------------------------------------
	// �A�N�Z�T
	void set_position(const VECTOR2& position){position_ = position;}
	void set_rotation(const float rotation){rotation_ = rotation;}
	void set_scale(const VECTOR2& scale){scale_ = scale;}
	void set_matrix(const MATRIX4x4& matrix){matrix_ = matrix;}
	void set_object_2d(CObject2D* object_2d){object_2d_ = object_2d;}
	void set_texture_name(const std::string& texture_name){texture_name_ = texture_name;}
	void set_renderstate(CRenderstate* renderstate){renderstate_ = renderstate;}
	void set_camera(CCamera* camera){camera_ = camera;}
	void set_texture_manager(CTextureManager* texture_manager){texture_manager_ = texture_manager;}

	const VECTOR2& position(void){return position_;}
	const float& rotation(void){return rotation_;}
	const VECTOR2& scale(void){return scale_;}
	const MATRIX4x4& matrix(void){return matrix_;}
	CObject2D* object_2d(void){return object_2d_;}
	std::string& texture_name(void){return texture_name_;}
	CRenderstate* renderstate(void){return renderstate_;}
	CCamera* camera(void){return camera_;}
	CTextureManager* texture_manager(void){return texture_manager_;}

private:
	VECTOR2 position_;
	float rotation_;
	VECTOR2 scale_;
	MATRIX4x4 matrix_;
	CObject2D* object_2d_;
	std::string texture_name_;
	CRenderstate* renderstate_;
	CCamera* camera_;
	CTextureManager* texture_manager_;
};

#endif	// _OBJECT_2D_DATA_H_

//---------------------------------- EOF --------------------------------------
