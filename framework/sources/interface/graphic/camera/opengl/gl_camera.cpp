//*****************************************************************************
//
// OpenGLカメラクラス
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
#include "interface/graphic/device/opengl/opengl.h"
#include "interface/graphic/camera/opengl/gl_camera.h"
#include "interface/graphic/device/device_holder.h"

// common
#include "common/math/math.h"
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
CGLCamera::CGLCamera(CDeviceHolder* device_holder) : CCamera(device_holder)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CGLCamera::~CGLCamera(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CGLCamera::Init(void)
{
	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CGLCamera::Uninit(void)
{

}

//=============================================================================
// 設定処理
//=============================================================================
void CGLCamera::Set(void)
{
	// ライトのオフ
	glDisable(GL_LIGHTING);

	// プロジェクション行列の設定開始
	glMatrixMode(GL_PROJECTION);

	// 単位行列の設定
	glLoadIdentity();

	// プロジェクション行列の生成
	projection_matrix_.SetPerspectiveFovRH(perspective_degree_,perspective_aspect_,perspective_near_,perspective_far_);

	// プロジェクション行列の設定
	//gluPerspective(60.0,(double)DEFAULT_SCREEN_WIDTH / (double)DEFAULT_SCREEN_HEIGHT,1.0,100.0);

	// プロジェクション行列の設定
	glMultMatrixf((f32*)&projection_matrix_);

	// ビューの設定開始(カメラ)
	glMatrixMode(GL_MODELVIEW);

	// 単位行列の設定
	glLoadIdentity();

	// ビュー行列の作成
	view_matrix_.SetLookAtRH(eye_,look_at_,up_);

	// ビュー行列の設定
	//glMultMatrixf((f32*)&view_matrix_);

	// ビュー行列の設定
	gluLookAt((double)eye_._x,(double)eye_._y,(double)eye_._z,look_at_._x,look_at_._y,look_at_._z,up_._x,up_._y,up_._z);

	// カメラの行列を取得
	glGetFloatv(GL_MODELVIEW_MATRIX,(f32*)&view_matrix_);

	// カメラの逆行列を取得
	inverse_matrix_ = view_matrix_.GetInverse();
}

#endif

//---------------------------------- EOF --------------------------------------
