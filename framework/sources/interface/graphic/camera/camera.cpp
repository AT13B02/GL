//*****************************************************************************
//
// カメラクラス
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
#ifdef _USING_OPENGL_
#include "interface/graphic/camera/opengl/gl_camera.h"
#endif
#ifdef _USING_DIRECTX_
#include "interface/graphic/camera/directx/dx_camera.h"
#endif
#include "interface/graphic/camera/camera.h"

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
CCamera::CCamera(CDeviceHolder* device_holder)
{
	device_holder_ = device_holder;

	eye_     = VECTOR3( 0.0f, 0.0f,10.0f);
	look_at_ = VECTOR3( 0.0f, 0.0f, 0.0f);
	up_      = VECTOR3( 0.0f, 1.0f, 0.0f);

	// 視点と注視点の距離を求める
	length_ = sqrtf(((eye_._x - look_at_._x) * (eye_._x - look_at_._x)) + 
					((eye_._y - look_at_._y) * (eye_._y - look_at_._y)) + 
					((eye_._z - look_at_._z) * (eye_._z - look_at_._z)));

	// 視点と注視点の角度を求める
	rotation_._y = atan2f(look_at_._z - eye_._z,look_at_._x - eye_._x);
	rotation_._x = atan2f(look_at_._x - eye_._y,look_at_._z - eye_._z);
	rotation_._z = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CCamera::~CCamera(void)
{
}

//=============================================================================
// 作成処理
//=============================================================================
CCamera* CCamera::Create(CDeviceHolder* device_holder)
{
	CCamera* camera = NULL;

#ifdef _USING_DIRECTX_
	camera = new CDXCamera(device_holder);
#endif

#ifdef _USING_OPENGL_
	camera = new CGLCamera(device_holder);
#endif

	return camera;
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CCamera::Init(void)
{
	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CCamera::Update(void)
{
}

//=============================================================================
// 視点の設定処理
//=============================================================================
void CCamera::SetEye(const VECTOR3& eye)
{
	eye_ = eye;

	// 視点と注視点の距離を求める
	length_ = sqrtf(((eye_._x - look_at_._x) * (eye_._x - look_at_._x)) + 
				    ((eye_._y - look_at_._y) * (eye_._y - look_at_._y)) + 
				    ((eye_._z - look_at_._z) * (eye_._z - look_at_._z)));

	// 視点と注視点の角度を求める
	rotation_._y = atan2f(look_at_._z - eye_._z,look_at_._x - eye_._x);
	rotation_._x = atan2f(look_at_._x - eye_._y,look_at_._z - eye_._z);
	rotation_._z = 0.0f;
}

//=============================================================================
// 注視点の設定処理
//=============================================================================
void CCamera::SetLookAt(const VECTOR3& look_at)
{
	look_at_ = look_at;

	// 視点と注視点の距離を求める
	length_ = sqrtf(((eye_._x - look_at_._x) * (eye_._x - look_at_._x)) + 
				    ((eye_._y - look_at_._y) * (eye_._y - look_at_._y)) + 
				    ((eye_._z - look_at_._z) * (eye_._z - look_at_._z)));

	// 視点と注視点の角度を求める
	rotation_._y = atan2f(look_at_._z - eye_._z,look_at_._x - eye_._x);
	rotation_._x = atan2f(look_at_._x - eye_._y,look_at_._z - eye_._z);
	rotation_._z = 0.0f;
}

//=============================================================================
// 視点から回転角の設定処理
//=============================================================================
void CCamera::SetRotationEye(const VECTOR3& rotation)
{
	rotation_ = rotation;
}

//=============================================================================
// 注視点から回転角の設定処理
//=============================================================================
void CCamera::SetRotationLookAt(const VECTOR3& rotation)
{
}

//=============================================================================
// パースペクティブの設定処理
//=============================================================================
void CCamera::SetPerspective(const f32& perspective_degree,const f32& perspective_aspect,const f32& perspective_near,const f32& perspective_far)
{
	perspective_degree_ = perspective_degree;
	perspective_aspect_ = perspective_aspect;
	perspective_near_ = perspective_near;
	perspective_far_ = perspective_far;
}

//=============================================================================
// ローテーションの正規化処理
//=============================================================================
VECTOR3 CCamera::NormalizeRotation(const VECTOR3& rotation)
{
	VECTOR3 out_rotation;

	if(rotation._y > (f32)(180.0f * MTH_DEGREE))
	{
		out_rotation._y = 2 * MTH_PI - rotation._y;
	}

	if(rotation._y < (f32)(-180.0f * MTH_DEGREE))
	{
		out_rotation._y = 2 * -MTH_PI + rotation._y;
	}

	return out_rotation;
}

//---------------------------------- EOF --------------------------------------
