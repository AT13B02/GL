//*****************************************************************************
//
// ライトクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _LIGHT_H_
#define _LIGHT_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/basic.h"

// common
#include "common/math/math.h"
#include "common/image/color/color4f.h"

//*****************************************************************************
// 定数定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CDeviceHolder;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CLight : public CBasic
{
public:
	enum Type
	{
		TYPE_DIRECTIONAL,	// 平行光源
		TYPE_POINT,			// 点光源
		TYPE_MAX
	};

	// ライトの最大数
	static const s32 LIGHT_MAX = 8;

	// 作成処理
	static CLight* Create(CDeviceHolder* device_holder);

	// 初期化処理
	bool Init(void);

	// 開放処理
	void Uninit(void);

	// ライトの設定
	virtual void Set(void) = 0;
	// ライトの設定
	virtual void Unset(void) = 0;

	// ライト番号設定
	void SetLightIndex(const s32& light_index){light_index_ = light_index;}

	// ライトの種類設定
	void SetType(const Type& light_type){light_type_ = light_type;}

	// 色情報の設定
	// 拡散光
	void SetDiffuse(const COLOR4F& diffuse){diffuse_ = diffuse;}
	// 環境光
	void SetAmbient(const COLOR4F& ambient){ambient_ = ambient;}
	// 鏡面反射光
	void SetSpecular(const COLOR4F& specular){specular_ = specular;}
	// 自発光
	void SetEmissive(const COLOR4F& emissive){emissive_ = emissive;}
	// 鏡面反射の強さ
	void SetSpecPower(const f32& spec_power){spec_power_ = spec_power;}

	// ライト定数減衰
	void SetAttenuationConstant(const f32& att_constant){att_constant_ = att_constant;}
	// ライト1次減衰
	void SetAttenuationLinear(const f32& att_linear){att_linear_ = att_linear;}
	// ライト2次減衰
	void SetAttenuationQuadratic(const f32& att_quadratic){att_quadratic_ = att_quadratic;}

	// 座標
	void SetPosition(const VECTOR3& position){position_._x = position._x; position_._y = position._y; position_._z = position._z;}
	// ライト向き
	void SetDirection(const VECTOR3& vector){vector_ = vector;vector_.Normalize();}

protected:
	// コンストラクタ
	CLight(CDeviceHolder* device_holder);

	// デストラクタ
	virtual ~CLight(void);

	// グラフィックデバイス
	CDeviceHolder* device_holder_;
	
	// ライトインデックス
	s32 light_index_;

	// ライトの種類
	Type light_type_;

	// 色
	// 拡散光
	COLOR4F diffuse_;
	// 環境光
	COLOR4F ambient_;
	// 鏡面反射光
	COLOR4F specular_;
	// 自発光
	COLOR4F emissive_;
	// 鏡面反射強さ
	f32 spec_power_;
	
	// 光の減衰量
	// 定数
	f32 att_constant_;
	// 1次
	f32 att_linear_;
	// 2次
	f32 att_quadratic_;

	// 座標
	VECTOR4 position_;
	// ベクトル
	VECTOR3 vector_;
private:
};

#endif	// _GL_LIGHT_H_

//---------------------------------- EOF --------------------------------------
