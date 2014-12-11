//*****************************************************************************
//
// メッシュフィールドクラス
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************

//*****************************************************************************
// インクルード
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
// デストラクタ
//=============================================================================
CMeshfield::~CMeshfield(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CMeshfield::Init(void)
{
	return true;
}

//=============================================================================
// 描画処理
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
// 終了
//=============================================================================
void CMeshfield::Uninit (void)
{
	SAFE_RELEASE(p_vertex_3d_);

	SAFE_DELETE_ARRAY(p_height_map_);
	SAFE_DELETE_ARRAY(p_face_normal_map_);
}

//=============================================================================
// 設定処理
//=============================================================================
void CMeshfield::Set(void)
{
	// ハイトマップ生成
	CreateHeightMap();
	
	// 頂点生成
	CreateVertexAndIndex();
}

//=============================================================================
// グリッド分割数設定
//=============================================================================
void CMeshfield::set_grid_number(const u32& grid_x, const u32& grid_z)
{
	number_grid_x_ = grid_x;
	number_grid_z_ = grid_z;

	number_vertex_x_ = grid_x + 1;
	number_vertex_z_ = grid_z + 1;
}

//=============================================================================
// グリッド幅設定
//=============================================================================
void CMeshfield::set_grid_length(const f32& length_x, const f32& length_z)
{
	length_grid_x_ = length_x;
	length_grid_z_ = length_z;
}

//=============================================================================
// 高さ取得
//=============================================================================
f32 CMeshfield::get_height(const VECTOR3& in_position, VECTOR3* p_out_normal)
{
	// 以下の座標系に変換する
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

	// p0からp1への度合い
	f32 s;
	// p0からp2への度合い
	f32 t;
	
	// オブジェクトの変換座標を出す
	f32 fObjectX;
	f32 fObjectZ;
	
	// 面インデックス(四角形面)
	s32 nFaceX;
	s32 nFaceZ;
	
	// 境界判定
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
	
	// p0からp1への度合い
	s = fObjectX - nFaceX;
	// p0からp2への度合い
	t = fObjectZ - nFaceZ;
	
	f32 fOffsetX = -(number_grid_x_ * length_grid_x_) * 0.5f;
	f32 fOffsetZ = -(number_grid_z_ * length_grid_z_) * 0.5f;
	f32 fHeight;
	
	VECTOR3 tempNormal;
	if(s + t < 1.0f)
	{
		// 左の三角形
		VECTOR3 p0(// 左上
			nFaceX * length_grid_x_ + fOffsetX,
			p_height_map_[nFaceZ * number_vertex_x_ + nFaceX],
			nFaceZ * length_grid_z_ + fOffsetZ);

		// 法線設定
		if(nullptr != p_out_normal)
		{
			tempNormal = *p_out_normal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		else
		{
			tempNormal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		
		// オブジェクトy座標設定
		if(tempNormal._y < 0.00005f)
		{
			// 右上高さ
			float p1 = p_height_map_[nFaceZ * number_vertex_x_ + nFaceX + 1];
			// 左下高さ
			float p2 = p_height_map_[(nFaceZ + 1) * number_vertex_x_ + nFaceX];
			// p0 -> p1 高さベクトル
			//float h0 = p1 - p0.y;
			// p0 -> p2 高さベクトル
			//float h1 = p2 - p0.y;
			fHeight = p0._y + (p1 - p0._y) * s + (p2 - p0._y) * t;
		}
		else
		{
			// 内積の方程式より算出
			fHeight = p0._y - (tempNormal._x * (in_position._x - p0._x) + tempNormal._z * (in_position._z - p0._z)) / tempNormal._y;
		}
	}
	else
	{
		// 右の三角形
		VECTOR3 p3(// 右下
			(nFaceX + 1) * length_grid_x_ + fOffsetX,
			p_height_map_[(nFaceZ + 1) * number_vertex_x_ + nFaceX + 1],
			(nFaceZ + 1) * length_grid_z_ + fOffsetZ);
	
		// 法線設定
		if(nullptr != p_out_normal)
		{
			tempNormal = *p_out_normal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		else
		{
			tempNormal = p_face_normal_map_[nFaceZ * number_grid_x_ * 2 + nFaceX * 2];
		}
		
		// オブジェクトy座標設定
		if(tempNormal._y < 0.00005f)
		{
			// 左下高さ
			float p2 = p_height_map_[(nFaceZ + 1) * number_vertex_x_ + nFaceX];
			// 右上高さ
			float p1 = p_height_map_[nFaceZ * number_vertex_x_ + nFaceX + 1];
			// p3 -> p2 高さベクトル
			//float h1 = p2 - p0.y;
			// p3 -> p1 高さベクトル
			//float h0 = p1 - p0.y;
			fHeight = p3._y + (p2 - p3._y) * (1 - s) + (p1 - p3._y) * (1 - t);
		}
		else
		{
			// 内積の方程式より算出
			fHeight = p3._y - (tempNormal._x * (in_position._x - p3._x) + tempNormal._z * (in_position._z - p3._z)) / tempNormal._y;
		}
	}

	// 高さを返す
	return fHeight;
}

//=============================================================================
// ハイトマップ生成
//=============================================================================
void CMeshfield::CreateHeightMap()
{
	if(nullptr != p_height_map_)
	{
		SAFE_DELETE_ARRAY(p_height_map_);
	}

	// 生成
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
	// 一番低い場所を0に合わせる
	for(u32 i = 0; i < number_vertex_z_ * number_vertex_x_; i++)
	{
		p_height_map_[i] -= min_height;
	}
}

//=============================================================================
// 頂点とインデックスを生成
//=============================================================================
void CMeshfield::CreateVertexAndIndex()
{
	if(nullptr != p_vertex_3d_)
	{
		SAFE_RELEASE(p_vertex_3d_);
	}

	p_vertex_3d_ = CVertex3D::Create(device_holder_, number_vertex_x_ * number_vertex_z_);
	p_vertex_3d_->CreateIndex(2 * (number_grid_z_ * (number_grid_x_ + 2) - 1));// (x + 1) * 2 * z + (z - 1) * 2 をまとめた
	
	CVertex3D::VERTEX_3D* pVertex3D = nullptr;
	CVertex3D::VERTEX_3D_INDEX* pIndex = nullptr;
	
	// 頂点、インデックスロック
	p_vertex_3d_->Lock(&pVertex3D, &pIndex);
	
	// 頂点の値設定
	SetVertex(
		pVertex3D->_position,
		pVertex3D->_color,
		pVertex3D->_texcoord);
	
	// 法線マップ設定
	CreateNormalMap(pVertex3D->_position);

	// 法線設定
	SetNormal(pVertex3D->_normal);

	// インデックス設定
	SetIndex(pIndex->_position);
	SetIndex(pIndex->_normal);
	SetIndex(pIndex->_color);
	SetIndex(pIndex->_texcoord);

	// 頂点情報をアンロック
	p_vertex_3d_->Unlock();
}

//=============================================================================
// 頂点の値設定
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

			// インデックスインクリメント
			idx++;
		}
	}
}

//=============================================================================
// 法線マップ生成
//=============================================================================
void CMeshfield::CreateNormalMap(VECTOR3* p_position)
{
	if(nullptr != p_face_normal_map_)
	{
		SAFE_DELETE_ARRAY(p_face_normal_map_);
	}

	p_face_normal_map_ = new VECTOR3[number_grid_x_ * number_grid_z_ * 2];

	// 面法線マップ作成
	VECTOR3 v0;
	VECTOR3 v1;
	VECTOR3 nor;
	for(u32 z = 0; z < number_grid_z_; z++)
	{
		for(u32 x = 0; x < number_grid_x_; x++)
		{
			// 頂点インデックス
			u32 uVtxIndex = z * (number_grid_x_ + 1) + x;
			// 面法線インデックス
			u32 uFaceIndex = 2 * (z * number_grid_x_ + x);
			
			// 面その1
			// 外積用ベクトル算出
			v0 = p_position[uVtxIndex + number_grid_x_ + 1] - p_position[uVtxIndex];
			v1 = p_position[uVtxIndex + 1] - p_position[uVtxIndex];
			// 外積計算
			nor = v0.CrossProduct(v1);
			// 法線正規化
			nor.Normalize();
			// 法線マップ設定
			p_face_normal_map_[uFaceIndex] = nor;

			// 面その2
			// 外積用ベクトル算出
			v0 = p_position[uVtxIndex + number_grid_x_ + 1] - p_position[uVtxIndex + 1];
			v1 = p_position[uVtxIndex + number_grid_x_ + 2] - p_position[uVtxIndex + 1];
			// 外積計算
			nor = v0.CrossProduct(v1);
			// 法線正規化
			nor.Normalize();
			// 法線マップ設定
			p_face_normal_map_[uFaceIndex + 1] = nor;
		}
	}
}

//=============================================================================
// 法線設定
//=============================================================================
void CMeshfield::SetNormal(VECTOR3* p_normal)
{
	// 面法線総数
	DWORD number_face_normal = number_grid_x_ * number_grid_z_ * 2;

	// 法線設定
	VECTOR3 nor;
	for(u32 z = 0; z < number_vertex_z_; z++)
	{
		for(u32 x = 0; x < number_vertex_x_; x++)
		{
			// 頂点インデックス
			u32 uVtxIndex = z * number_vertex_x_ + x;
			// 面インデックス
			u32 uFaceIndex;

			// 上端
			if(z == 0)
			{
				// 左上隅
				if(x == 0)
				{
					nor = p_face_normal_map_[0];
				}
				// 右上隅
				else if(x == number_grid_x_)
				{
					nor = p_face_normal_map_[(number_grid_x_ - 1) * 2] + p_face_normal_map_[(number_grid_x_ - 1) * 2 + 1];
				}
				// その他上端
				else
				{
					uFaceIndex = (x - 1) * 2;
					nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + 1] + p_face_normal_map_[uFaceIndex + 2];
				}
			}
			// 下端
			else if(z == number_grid_z_)
			{
				// 左下隅
				if(x == 0)
				{
					nor = p_face_normal_map_[number_grid_x_ * 2 * (number_grid_z_ - 1)] + p_face_normal_map_[number_grid_x_ * 2 * (number_grid_z_ - 1) + 1];
				}
				// 右下隅
				else if(x == number_grid_x_)
				{
					nor = p_face_normal_map_[number_face_normal - 1];
				}
				// その他下端
				else
				{
					uFaceIndex = (x - 1) * 2 + (number_grid_z_ - 1) * (number_grid_x_ * 2) + 1;
					nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + 1] + p_face_normal_map_[uFaceIndex + 2];
				}
			}
			// 左端
			else if(x == 0)
			{
				uFaceIndex = (z - 1) * number_grid_x_ * 2;
				nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + 1] + p_face_normal_map_[uFaceIndex + number_grid_x_ * 2];
			}
			// 右端
			else if(x == number_grid_x_)
			{
				uFaceIndex = (z - 1) * number_grid_x_ * 2 + (number_grid_x_ * 2 - 1);
				nor = p_face_normal_map_[uFaceIndex] + p_face_normal_map_[uFaceIndex + number_grid_x_ * 2 - 1] + p_face_normal_map_[uFaceIndex + number_grid_x_ * 2];
			}
			// 内側
			else
			{
				uFaceIndex = (z - 1) * number_grid_x_ * 2 + x * 2 - 1;
				u32 nNextRowFaceIndex = uFaceIndex + number_grid_x_ * 2 - 1;
				// 使用する面法線は 6 個
				nor = p_face_normal_map_[uFaceIndex] +
					  p_face_normal_map_[uFaceIndex + 1] +
					  p_face_normal_map_[uFaceIndex + 2] +
					  p_face_normal_map_[nNextRowFaceIndex] +
					  p_face_normal_map_[nNextRowFaceIndex + 1] +
					  p_face_normal_map_[nNextRowFaceIndex + 2];
			}
			
			// 法線設定
			nor.Normalize();
			p_normal[uVtxIndex] = nor;
		}
	}
}

//=============================================================================
// インデックス設定
//=============================================================================
void CMeshfield::SetIndex(u32* p_index)
{
	// インデックス設定
	for(u32 z = 0; z < number_grid_z_; z++)
	{
		// 一番左上から始める
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
		// アドレスのインクリメント
		p_index += (number_grid_x_ * 2 + 4);
	}
}

//---------------------------------- EOF --------------------------------------
