//*****************************************************************************
//
// 2D頂点クラス
//
// Author		: Tomohiro Kouno
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/application.h"

// graphic
#include "interface/graphic/vertex/vertex_2d.h"
#ifdef _USING_DIRECTX_
#include "interface/graphic/vertex/directx/dx_vertex_2d.h"
#endif
#ifdef _USING_OPENGL_
#include "interface/graphic/vertex/opengl/gl_vertex_2d.h"
#endif

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
CVertex2D::CVertex2D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number)
{
	device_holder_ = device_holder;

	position_number_ = position_number;
	normal_number_   = normal_number;
	color_number_    = color_number;
	texcoord_number_ = texcoord_number;

	vertex_2d_._position = new VECTOR2[position_number];
	//vertex_2d_._normal   = new VECTOR3[normal_number];
	vertex_2d_._color    = new COLOR4F[color_number];
	vertex_2d_._texcoord = new VECTOR2[texcoord_number];

	//vertex_2d_index_._normal   = NULL;
	vertex_2d_index_._position = NULL;
	vertex_2d_index_._color    = NULL;
	vertex_2d_index_._texcoord = NULL;

	index_number_ = 0;
	primitive_number_ = position_number - 2;

	use_index_ = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CVertex2D::~CVertex2D(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CVertex2D::Init(void)
{
	return true;
}

//=============================================================================
// 描画処理
//=============================================================================
//void CVertex2D::Draw(const MATRIX4x4& matrix)
//{
//	Draw(matrix,0,primitive_number_ + 2);
//}

//=============================================================================
// 終了処理
//=============================================================================
void CVertex2D::Uninit(void)
{
	SAFE_DELETE_ARRAY(vertex_2d_._position);
	//SAFE_DELETE_ARRAY(vertex_2d_._normal);
	SAFE_DELETE_ARRAY(vertex_2d_._color);
	SAFE_DELETE_ARRAY(vertex_2d_._texcoord);

	//SAFE_DELETE_ARRAY(vertex_2d_index_._normal);
	SAFE_DELETE_ARRAY(vertex_2d_index_._position);
	SAFE_DELETE_ARRAY(vertex_2d_index_._color);
	SAFE_DELETE_ARRAY(vertex_2d_index_._texcoord);

	position_number_ = 0;
	normal_number_   = 0;
	color_number_    = 0;
	texcoord_number_ = 0;
}

//=============================================================================
// 作成処理
//=============================================================================
CVertex2D* CVertex2D::Create(CDeviceHolder* device_holder,const u32& vertex_number)
{
	return Create(device_holder,vertex_number,vertex_number,vertex_number,vertex_number);
}

//=============================================================================
// 作成処理
//=============================================================================
CVertex2D* CVertex2D::Create(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number)
{
	CVertex2D* pVertex2D = NULL;

#ifdef _USING_DIRECTX_
	pVertex2D = new CDXVertex2D(device_holder,position_number,normal_number,color_number,texcoord_number);
#endif

#ifdef _USING_OPENGL_
	pVertex2D = new CGLVertex2D(device_holder,position_number,normal_number,color_number,texcoord_number);
#endif

	return pVertex2D;
}

//=============================================================================
// インデックスの作成
//=============================================================================
void CVertex2D::CreateIndex(const int& index_number)
{
	//vertex_2d_index_._normal = new u32[index_number];
	vertex_2d_index_._position = new u32[index_number];
	vertex_2d_index_._color = new u32[index_number];
	vertex_2d_index_._texcoord = new u32[index_number];

	index_number_ = index_number;

	primitive_number_ = index_number;

	use_index_ = true;
}

//=============================================================================
// ロック処理
//=============================================================================
void CVertex2D::Lock(VERTEX_2D** vertex_2d,VERTEX_2D_INDEX** vertex_2d_index)
{
	if(vertex_2d != NULL)
	{
		*vertex_2d = &vertex_2d_;
	}

	if(vertex_2d_index != NULL)
	{
		*vertex_2d_index = &vertex_2d_index_;
	}
}

//---------------------------------- EOF --------------------------------------
