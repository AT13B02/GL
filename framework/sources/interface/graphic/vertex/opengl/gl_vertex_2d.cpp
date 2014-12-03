//*****************************************************************************
//
// OpenGL2D頂点クラス
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
#include "interface/graphic/vertex/opengl/gl_vertex_2d.h"
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
CGLVertex2D::CGLVertex2D(CDeviceHolder* device_holder,const u32& position_number,const u32& normal_number,const u32& color_number,const u32& texcoord_number) : CVertex2D(device_holder,position_number,normal_number,color_number,texcoord_number)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGLVertex2D::~CGLVertex2D(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CGLVertex2D::Draw(const MATRIX4x4& matrix,const u32& offset,const u32 length)
{
	u32 vertex_number = offset + length;

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
		for(u32 i = offset;i < vertex_number;++i)
		{
			// 色の設定
			glColor4f(vertex_2d_._color[vertex_2d_index_._color[i]]._red,vertex_2d_._color[vertex_2d_index_._color[i]]._green,vertex_2d_._color[vertex_2d_index_._color[i]]._blue,vertex_2d_._color[vertex_2d_index_._color[i]]._alpha);

			// テクスチャ座標
			glTexCoord2f(vertex_2d_._texcoord[vertex_2d_index_._texcoord[i]]._x,vertex_2d_._texcoord[vertex_2d_index_._texcoord[i]]._y);

			// 法線
			//glNormal3f(vertex_2d_._normal[vertex_2d_index_._normal[i]]._x,vertex_2d_._normal[vertex_2d_index_._normal[i]]._y,vertex_2d_._normal[vertex_2d_index_._normal[i]]._z);

			// 頂点座標
			//glVertex3f(vertex_2d_._position[vertex_2d_index_._position[i]]._x,vertex_2d_._position[vertex_2d_index_._position[i]]._y,vertex_2d_._position[vertex_2d_index_._position[i]]._z);
			glVertex3f(vertex_2d_._position[vertex_2d_index_._position[i]]._x,vertex_2d_._position[vertex_2d_index_._position[i]]._y,0.0f);
		}
	}
	else
	{
		for(u32 i = 0;i < vertex_number;++i)
		{
			// 色の設定
			glColor4f(vertex_2d_._color[i]._red,vertex_2d_._color[i]._green,vertex_2d_._color[i]._blue,vertex_2d_._color[i]._alpha);

			// テクスチャ座標
			glTexCoord2f(vertex_2d_._texcoord[i]._x,vertex_2d_._texcoord[i]._y);

			// 法線
			//glNormal3f(vertex_2d_._normal[i]._x,vertex_2d_._normal[i]._y,vertex_2d_._normal[i]._z);

			// 頂点座標
			//glVertex3f(vertex_2d_._position[i]._x,vertex_2d_._position[i]._y,vertex_2d_._position[i]._z);
			glVertex3f(vertex_2d_._position[i]._x,vertex_2d_._position[i]._y,0.0f);
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
void CGLVertex2D::Unlock(void)
{

}

#endif	// _USING_OPENGL_

//---------------------------------- EOF --------------------------------------
