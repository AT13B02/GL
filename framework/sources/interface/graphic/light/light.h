//*****************************************************************************
//
// ���C�g�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/basic.h"

// common
#include "common/math/math.h"
#include "common/image/color/color4f.h"

//*****************************************************************************
// �萔��`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CLight : public CBasic
{
public:
	enum Type
	{
		TYPE_DIRECTIONAL,	// ���s����
		TYPE_POINT,			// �_����
		TYPE_MAX
	};

	// ���C�g�̍ő吔
	static const s32 LIGHT_MAX = 8;

	// �쐬����
	static CLight* Create(CDeviceHolder* device_holder);

	// ����������
	bool Init(void);

	// �J������
	void Uninit(void);

	// ���C�g�̐ݒ�
	virtual void Set(void) = 0;
	// ���C�g�̐ݒ�
	virtual void Unset(void) = 0;

	// ���C�g�ԍ��ݒ�
	void SetLightIndex(const s32& light_index){light_index_ = light_index;}

	// ���C�g�̎�ސݒ�
	void SetType(const Type& light_type){light_type_ = light_type;}

	// �F���̐ݒ�
	// �g�U��
	void SetDiffuse(const COLOR4F& diffuse){diffuse_ = diffuse;}
	// ����
	void SetAmbient(const COLOR4F& ambient){ambient_ = ambient;}
	// ���ʔ��ˌ�
	void SetSpecular(const COLOR4F& specular){specular_ = specular;}
	// ������
	void SetEmissive(const COLOR4F& emissive){emissive_ = emissive;}
	// ���ʔ��˂̋���
	void SetSpecPower(const f32& spec_power){spec_power_ = spec_power;}

	// ���C�g�萔����
	void SetAttenuationConstant(const f32& att_constant){att_constant_ = att_constant;}
	// ���C�g1������
	void SetAttenuationLinear(const f32& att_linear){att_linear_ = att_linear;}
	// ���C�g2������
	void SetAttenuationQuadratic(const f32& att_quadratic){att_quadratic_ = att_quadratic;}

	// ���W
	void SetPosition(const VECTOR3& position){position_._x = position._x; position_._y = position._y; position_._z = position._z;}
	// ���C�g����
	void SetDirection(const VECTOR3& vector){vector_ = vector;vector_.Normalize();}

protected:
	// �R���X�g���N�^
	CLight(CDeviceHolder* device_holder);

	// �f�X�g���N�^
	virtual ~CLight(void);

	// �O���t�B�b�N�f�o�C�X
	CDeviceHolder* device_holder_;
	
	// ���C�g�C���f�b�N�X
	s32 light_index_;

	// ���C�g�̎��
	Type light_type_;

	// �F
	// �g�U��
	COLOR4F diffuse_;
	// ����
	COLOR4F ambient_;
	// ���ʔ��ˌ�
	COLOR4F specular_;
	// ������
	COLOR4F emissive_;
	// ���ʔ��ˋ���
	f32 spec_power_;
	
	// ���̌�����
	// �萔
	f32 att_constant_;
	// 1��
	f32 att_linear_;
	// 2��
	f32 att_quadratic_;

	// ���W
	VECTOR4 position_;
	// �x�N�g��
	VECTOR3 vector_;
private:
};

#endif	// _GL_LIGHT_H_

//---------------------------------- EOF --------------------------------------
