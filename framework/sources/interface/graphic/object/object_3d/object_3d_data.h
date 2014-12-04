//*****************************************************************************
//
// オブジェクト3Dデータクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _OBJECT_3D_DATA_H_
#define _OBJECT_3D_DATA_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// stl
#include <string>
#include <list>

// basic
#include "basic/basic.h"

// common
#include "common/math/math.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CObject3D;
class CRenderstate;
class CCamera;
class CModelManager;
class CTextureManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CObject3DData : public CBasic
{
public:
	// コンストラクタ
	CObject3DData(void);

	// デストラクタ
	~CObject3DData(void);

	// 初期化
	bool Init(void);

	// 描画処理
	void Draw(void);

	// 初期化
	void Uninit(void);

	//-----------------------------------------------------
	// アクセサ

	void set_position(const VECTOR3& position){position_ = position;}
	void set_rotation(const VECTOR3& rotation){rotation_ = rotation;}
	void set_scale(const VECTOR3& scale){scale_ = scale;}
	void set_matrix(const MATRIX4x4& matrix){matrix_ = matrix;}
	void set_object_3d(CObject3D* object_3d){object_3d_ = object_3d;}
	void set_texture_name(const std::string& texture_name){texture_name_ = texture_name;}
	void set_renderstate(std::list<u32> renderstate_list){renderstate_list_ = renderstate_list;}
	void set_camera(CCamera* camera){camera_ = camera;}
	void set_model_manager(CModelManager* model_manager){model_manager_ = model_manager;}
	void set_texture_manager(CTextureManager* texture_manager){texture_manager_ = texture_manager;}

	const VECTOR3& position(void){return position_;}
	const VECTOR3& rotation(void){return rotation_;}
	const VECTOR3& scale(void){return scale_;}
	const MATRIX4x4& matrix(void){return matrix_;}
	CObject3D* object_3d(void){return object_3d_;}
	std::string& texture_name(void){return texture_name_;}
	std::list<u32>& renderstate_list(void){return renderstate_list_;}
	CCamera* camera(void){return camera_;}
	CModelManager* model_manager(void){return model_manager_;}
	CTextureManager* texture_manager(void){return texture_manager_;}

private:
	VECTOR3 position_;
	VECTOR3 rotation_;
	VECTOR3 scale_;
	MATRIX4x4 matrix_;
	CObject3D* object_3d_;
	std::string texture_name_;
	std::list<u32> renderstate_list_;
	CCamera* camera_;
	CModelManager* model_manager_;
	CTextureManager* texture_manager_;
};

#endif	// _OBJECT_3D_DATA_H_

//---------------------------------- EOF --------------------------------------
