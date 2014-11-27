//*****************************************************************************
//
// 3D頂点クラス
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
#include "interface/graphic/vertex/vertex_3d.h"
#ifdef _USING_DIRECTX_
#include "interface/graphic/vertex/directx/dx_vertex_3d.h"
#endif
#ifdef _USING_OPENGL_
#include "interface/graphic/vertex/opengl/gl_vertex_3d.h"
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
CVertex3D::CVertex3D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number)
{
	device_holder_ = device_holder;

	position_number_ = position_number;
	normal_number_   = normal_number;
	color_number_    = color_number;
	texcoord_number_ = texcoord_number;

	vertex_3d_._position = new VECTOR3[position_number];
	vertex_3d_._normal   = new VECTOR3[normal_number];
	vertex_3d_._color    = new COLOR4F[color_number];
	vertex_3d_._texcoord = new VECTOR2[texcoord_number];

	vertex_3d_index_._normal   = NULL;
	vertex_3d_index_._position = NULL;
	vertex_3d_index_._color    = NULL;
	vertex_3d_index_._texcoord = NULL;

	index_number_ = 0;
	primitive_number_ = position_number - 2;

	use_index_ = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CVertex3D::~CVertex3D(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CVertex3D::Init(void)
{
	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CVertex3D::Uninit(void)
{
	SAFE_DELETE_ARRAY(vertex_3d_._position);
	SAFE_DELETE_ARRAY(vertex_3d_._normal);
	SAFE_DELETE_ARRAY(vertex_3d_._color);
	SAFE_DELETE_ARRAY(vertex_3d_._texcoord);

	SAFE_DELETE_ARRAY(vertex_3d_index_._normal);
	SAFE_DELETE_ARRAY(vertex_3d_index_._position);
	SAFE_DELETE_ARRAY(vertex_3d_index_._color);
	SAFE_DELETE_ARRAY(vertex_3d_index_._texcoord);

	position_number_ = 0;
	normal_number_   = 0;
	color_number_    = 0;
	texcoord_number_ = 0;
}

//=============================================================================
// 作成処理
//=============================================================================
CVertex3D* CVertex3D::Create(CDeviceHolder* device_holder,const u32& vertex_number)
{
	return Create(device_holder,vertex_number,vertex_number,vertex_number,vertex_number);
}

//=============================================================================
// 作成処理
//=============================================================================
CVertex3D* CVertex3D::Create(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number)
{
	CVertex3D* pVertex3D = NULL;

#ifdef _USING_DIRECTX_
	pVertex3D = new CDXVertex3D(device_holder,position_number,normal_number,color_number,texcoord_number);
#endif

#ifdef _USING_OPENGL_
	pVertex3D = new CGLVertex3D(device_holder,position_number,normal_number,color_number,texcoord_number);
#endif

	return pVertex3D;
}

//=============================================================================
// インデックスの作成
//=============================================================================
void CVertex3D::CreateIndex(const int& index_number)
{
	vertex_3d_index_._normal = new u32[index_number];
	vertex_3d_index_._position = new u32[index_number];
	vertex_3d_index_._color = new u32[index_number];
	vertex_3d_index_._texcoord = new u32[index_number];

	index_number_ = index_number;

	use_index_ = true;
}

//=============================================================================
// ロック処理
//=============================================================================
void CVertex3D::Lock(VERTEX_3D** vertex_3d,VERTEX_3D_INDEX** vertex_3d_index)
{
	if(vertex_3d != NULL)
	{
		*vertex_3d = &vertex_3d_;
	}

	if(vertex_3d_index != NULL)
	{
		*vertex_3d_index = &vertex_3d_index_;
	}
}

//---------------------------------- EOF --------------------------------------
