//*****************************************************************************
//
// OpenGL3D頂点クラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/application.h"

#ifdef _USING_OPENGL_
// graphic
#include "interface/graphic/vertex/opengl/gl_vertex_3d.h"
#include "interface/graphic/device/device_holder.h"
#include "interface/graphic/device/opengl/opengl.h"

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
CGLVertex3D::CGLVertex3D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number) : CVertex3D(device_holder,position_number,normal_number,color_number,texcoord_number)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGLVertex3D::~CGLVertex3D(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CGLVertex3D::Draw(const MATRIX4x4& matrix)
{
	glEnable(GL_TEXTURE_2D);

	// ビューの設定開始
	glMatrixMode(GL_MODELVIEW);

	// ビュー行列を退避
	glPushMatrix();

	// マトリックスの設定
	glMultMatrixf((f32*)&matrix);

	// ポリゴン描画の開始(図形の描画形式を設定)
	glBegin(GL_TRIANGLE_STRIP);

	if(use_index_)
	{
		for(int i = 0;i < index_number_;i++)
		{
			// 色の設定
			glColor4f(vertex_3d_._color[vertex_3d_index_._color[i]]._red,vertex_3d_._color[vertex_3d_index_._color[i]]._green,vertex_3d_._color[vertex_3d_index_._color[i]]._blue,vertex_3d_._color[vertex_3d_index_._color[i]]._alpha);

			// テクスチャ座標
			glTexCoord2f(vertex_3d_._texcoord[vertex_3d_index_._texcoord[i]]._x,vertex_3d_._texcoord[vertex_3d_index_._texcoord[i]]._y);

			// 法線
			glNormal3f(vertex_3d_._normal[vertex_3d_index_._normal[i]]._x,vertex_3d_._normal[vertex_3d_index_._normal[i]]._y,vertex_3d_._normal[vertex_3d_index_._normal[i]]._z);

			// 頂点座標
			glVertex3f(vertex_3d_._position[vertex_3d_index_._position[i]]._x,vertex_3d_._position[vertex_3d_index_._position[i]]._y,vertex_3d_._position[vertex_3d_index_._position[i]]._z);
		}
	}
	else
	{
		for(int i = 0;i < primitive_number_ + 2;i++)
		{
			// 色の設定
			glColor4f(vertex_3d_._color[i]._red,vertex_3d_._color[i]._green,vertex_3d_._color[i]._blue,vertex_3d_._color[i]._alpha);

			// テクスチャ座標
			glTexCoord2f(vertex_3d_._texcoord[i]._x,vertex_3d_._texcoord[i]._y);

			// 法線
			glNormal3f(vertex_3d_._normal[i]._x,vertex_3d_._normal[i]._y,vertex_3d_._normal[i]._z);

			// 頂点座標
			glVertex3f(vertex_3d_._position[i]._x,vertex_3d_._position[i]._y,vertex_3d_._position[i]._z);
		}
	}
	// ポリゴン描画の終了
	glEnd();

	// ワールド行列の破棄
	glPopMatrix();
}

//=============================================================================
// 解除処理
//=============================================================================
void CGLVertex3D::Unlock(void)
{

}

#endif	// _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
