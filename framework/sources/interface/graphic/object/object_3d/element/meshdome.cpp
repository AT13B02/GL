//*****************************************************************************
//
// メッシュドームクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/application.h"

// graphic
#include "meshdome.h"
#include "../object_3d_data.h"
#include "interface/graphic/vertex/vertex_3d.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/texture/texture.h"

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
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
CMeshdome::CMeshdome(CDeviceHolder* device_holder) :
	CObject3D(device_holder,OBJECT_3D_TYPE_MESHDOME),
	vertex_(nullptr),
	grid_x_number_(0),
	grid_z_number_(0),
	radius_(0.0f)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshdome::~CMeshdome(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CMeshdome::Init(void)
{
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshdome::Draw(CObject3DData* object_3d_data)
{
	MATRIX4x4 matrix;
	CTextureManager* texture_manager = object_3d_data->texture_manager();
	CTexture* texture = texture_manager->Get(object_3d_data->texture_name().c_str());

	matrix = GetWorldMatrix(object_3d_data);

	CObject3D::Draw(matrix,vertex_,texture,object_3d_data->renderstate_manager(),object_3d_data->renderstate_list());
}

//=============================================================================
// 終了
//=============================================================================
void CMeshdome::Uninit (void)
{
	SAFE_RELEASE(vertex_);
}

//=============================================================================
// 設定処理
//=============================================================================
void CMeshdome::Set(void)
{
	CVertex3D::VERTEX_3D* vertex_3d = nullptr;
	CVertex3D::VERTEX_3D_INDEX* vertex_3d_index = nullptr;

	vertex_ = CVertex3D::Create(device_holder_,(grid_x_number_ + 1) * (grid_z_number_ + 1));

	vertex_->CreateIndex((((grid_x_number_ + 1) * 2) * (grid_z_number_ - 0) + ((grid_z_number_ - 1) * 2)));

	f32 rotation_x = (MTH_PI * 2) / grid_x_number_;
	f32 rotation_y = (MTH_PI) / grid_z_number_;

	vertex_->Lock(&vertex_3d,&vertex_3d_index);

	for(u32 i = 0;i <= grid_z_number_;++i)
	{
		f32 radius = radius_ * cosf((f32)MTH_PI / grid_z_number_ / 2 * i);

		for(u32 j = 0;j <= grid_x_number_;++j)
		{
			vertex_3d->_position[i];

			VECTOR3 position = VECTOR3(radius * cosf(rotation_x * j),(radius_ / grid_z_number_) * i,radius * sinf(rotation_x * j));
			VECTOR3 normal = (-position).Normalize();

			vertex_3d->_position[j + i * (grid_x_number_ + 1)] = position;
			vertex_3d->_texcoord[j + i * (grid_x_number_ + 1)] = VECTOR2((1.0f / grid_x_number_) * j,1.0f - sinf(i * MTH_PI / 2 / grid_z_number_));
			vertex_3d->_color[j + i * (grid_x_number_ + 1)]    = COLOR4F(1.0f,1.0f,1.0f,1.0f);
			vertex_3d->_normal[j + i * (grid_x_number_ + 1)]   = normal;
		}
	}

	u32 index_count = 0;

	// インデックスの情報の格納
	for(u32 i = 0;i < grid_z_number_;++i)
	{
		for(u32 j = 0;j <= grid_x_number_;++j)
		{
			vertex_3d_index->_position[index_count + 0] = (i + 1) * (grid_x_number_ + 1) + j;
			vertex_3d_index->_position[index_count + 1] = (i + 0) * (grid_x_number_ + 1) + j;

			index_count += 2;

			if((j == grid_x_number_) && i != (grid_z_number_ - 2))
			{
				vertex_3d_index->_position[index_count + 0] = (i + 0) * (grid_x_number_ + 1) + j;
				vertex_3d_index->_position[index_count + 1] = (i + 2) * (grid_x_number_ + 1) + j;

				index_count += 2;
			}
		}
	}

	vertex_->Unlock();
}

//---------------------------------- EOF --------------------------------------
