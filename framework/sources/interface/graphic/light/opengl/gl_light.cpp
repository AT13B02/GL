//*****************************************************************************
//
// ライトクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/application.h"

#ifdef _USING_OPENGL_
// graphic
#include "interface/graphic/light/opengl/gl_light.h"
#include "interface/graphic/device/opengl/opengl.h"

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CGLLight::CGLLight(CDeviceHolder* device_holder) : CLight(device_holder)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGLLight::~CGLLight(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CGLLight::Init(void)
{
	return true;
}

//=============================================================================
// 設定処理
//=============================================================================
void CGLLight::Set(void)
{
	if(light_index_ < 0 || light_index_ >= LIGHT_MAX)
	{
		return;
	}

	s32 light_index = GL_LIGHT0 + light_index_;
	// ライト有効化
	glEnable(light_index);
	switch(light_type_)
	{
		// 平行光源
		case TYPE_DIRECTIONAL:
			{
				VECTOR4 dir;
				dir._x = -vector_._x;
				dir._y = -vector_._y;
				dir._z = -vector_._z;
				dir._w = 0.0f;
				glLightfv(light_index, GL_POSITION, (GLfloat*)&dir);
			}
			break;
			
		// 点光源
		case TYPE_POINT:
			{
				glLightfv(light_index, GL_POSITION, (GLfloat*)&position_);
				glLightf(light_index, GL_CONSTANT_ATTENUATION, att_constant_);
				glLightf(light_index, GL_LINEAR_ATTENUATION, att_linear_);
				glLightf(light_index, GL_QUADRATIC_ATTENUATION, att_quadratic_);
			}
			break;
	}

	glLightfv(light_index, GL_DIFFUSE, (GLfloat*)&diffuse_);
	glLightfv(light_index, GL_AMBIENT, (GLfloat*)&ambient_);
	glLightfv(light_index, GL_SPECULAR, (GLfloat*)&specular_);
	glLightfv(light_index, GL_EMISSION, (GLfloat*)&emissive_);
	glLightf(light_index, GL_SHININESS, spec_power_);
}

//=============================================================================
// ライトの設定を切る
//=============================================================================
void CGLLight::Unset(void)
{
	// ライト無効化
	glDisable(GL_LIGHT0 + light_index_);
}

#endif // _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
