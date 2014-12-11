//*****************************************************************************
//
// フィールドクラス
//
// Author		: Ryo Kobayashi
//
//*****************************************************************************
#pragma once
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
// graphic
#include "interface/graphic/object/object_3d/element/object_3d.h"

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
class CVertex3D;
struct COLOR4F;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CMeshfield : public CObject3D
{
public:
	// コンストラクタ
	CMeshfield(CDeviceHolder* device_holder);

	// デストラクタ
	virtual ~CMeshfield(void);

	// 初期化処理
	bool Init(void);

	// 描画処理
	void Draw(CObject3DData* pObject3DData);

	// 終了処理
	void Uninit(void);

	// 頂点情報の設定
	virtual void Set(void);

	// グリッド分割数設定
	void set_grid_number(const u32& grid_x, const u32& grid_z);

	// グリッド幅設定
	void set_grid_length(const f32& length_x, const f32& length_z);

	// 高さ取得
	f32 get_height(const VECTOR3& in_position, VECTOR3* p_out_normal);
protected:

private:
	// ハイトマップ生成
	void CreateHeightMap();

	// 頂点とインデックスを生成
	void CreateVertexAndIndex();

	// 頂点の値設定
	void SetVertex(VECTOR3* p_position, COLOR4F* p_color, VECTOR2* p_texcoord);
	
	// 法線マップ生成
	void CreateNormalMap(VECTOR3* p_position);

	// 法線設定
	void SetNormal(VECTOR3* p_normal);

	// インデックス設定
	void SetIndex(u32* p_index);

private:
	// グリッド数
	u32 number_grid_x_;
	u32 number_grid_z_;

	// グリッド幅
	f32 length_grid_x_;
	f32 length_grid_z_;

	// 頂点数
	u32 number_vertex_x_;
	u32 number_vertex_z_;

	// ハイトマップ
	f32 *p_height_map_;

	// 面法線マップ
	VECTOR3 *p_face_normal_map_;

	// 頂点座標
	VECTOR2 position_;

	// インデックス数
	u32 number_index_;

	// 頂点情報
	CVertex3D* p_vertex_3d_;

	// 最大の高さ
	f32 m_fMaxHeight;
};

#endif	// _OBJECT_3D_H_

//---------------------------------- EOF --------------------------------------
