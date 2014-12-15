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

	// ビューの設定
	SetView(VECTOR3(0.0f,0.0f,10.0f),VECTOR3(0.0f,0.0f,0.0f),VECTOR3(0.0f,1.0f,0.0f));

	// デフォルトのパースペクティブの設定
	SetPerspective(60.0f,16.0f / 9.0f,1.0f,1000.0f);
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
	SetPosition(eye,look_at_);
}

//=============================================================================
// 注視点の設定処理
//=============================================================================
void CCamera::SetLookAt(const VECTOR3& look_at)
{
	SetPosition(eye_,look_at);
}

//=============================================================================
// 視点と注視点の設定処理
//=============================================================================
void CCamera::SetPosition(const VECTOR3& eye,const VECTOR3& look_at)
{
	SetView(eye,look_at,up_);
}

//=============================================================================
// 上方向ベクトルの設定
//=============================================================================
void CCamera::SetUp(const VECTOR3& up)
{
	SetView(eye_,look_at_,up);
}

//=============================================================================
// 並行移動
//=============================================================================
void CCamera::SetTranslation(const VECTOR3& translation)
{
	eye_ += translation;
	look_at_ += translation;
}

//=============================================================================
// 視点から注視点設定
//=============================================================================
void CCamera::SetLookAtFromEye(const VECTOR3& eye)
{
	look_at_._x = eye._x + length_ * cosf(rotation_._x * MTH_DEGREE) * cosf(rotation_._y * MTH_DEGREE);
	look_at_._y = eye._y;// - 10.0f;// + length_ * sinf(rotation_._x);
	look_at_._z = eye._z + length_ * cosf(rotation_._x * MTH_DEGREE) * sinf(rotation_._y * MTH_DEGREE);

	SetEye(eye);
}

//=============================================================================
// 視点の回転角の設定処理
//=============================================================================
void CCamera::SetRotationEyeToLookAt(const VECTOR3& rotation)
{
	rotation_ = NormalizeRotation(rotation);

	SetLookAtFromEye(eye_);
}

//=============================================================================
// 注視点の回転角の設定処理
//=============================================================================
void CCamera::SetRotationLookAtToEye(const VECTOR3& rotation)
{
}

//=============================================================================
// パースペクティブの設定処理
//=============================================================================
void CCamera::SetPerspective(const f32& perspective_degree,const f32& perspective_aspect,const f32& perspective_near,const f32& perspective_far)
{
	perspective_degree_ = perspective_degree;
	perspective_aspect_ = perspective_aspect;
	perspective_near_   = perspective_near;
	perspective_far_    = perspective_far;
}

//=============================================================================
// ビューの設定処理
//=============================================================================
void CCamera::SetView(const VECTOR3& eye,const VECTOR3& look_at,const VECTOR3& up)
{
	eye_ = eye;
	look_at_ = look_at;
	up_ = up;

	// 視点と注視点の距離を求める
	length_ = sqrtf(((look_at._x - eye._x) * (look_at._x - eye._x)) + 
				    ((look_at._y - eye._y) * (look_at._y - eye._y)) + 
				    ((look_at._z - eye._z) * (look_at._z - eye._z)));

	// 視点と注視点の角度を求める
	rotation_._y = atan2f(look_at._z - eye._z,look_at._x - eye._x) * MTH_RADIAN;
	rotation_._x = atan2f(look_at_._y - eye_._y,look_at_._z - eye._z) * MTH_RADIAN;
	rotation_._z = 0.0f * MTH_RADIAN;

	// 正規化
	rotation_ = NormalizeRotation(rotation_);

	// 前方ベクトルを求める
	front_vector_ = look_at - eye;
	front_vector_._y = 0.0f;
	front_vector_.Normalize();

	// 右ベクトルを求める
	right_vector_ = front_vector_.CrossProduct(up);
}

//=============================================================================
// ローテーションの正規化処理
//=============================================================================
VECTOR3 CCamera::NormalizeRotation(const VECTOR3& rotation)
{
	VECTOR3 out_rotation = rotation;

	if(rotation._y >= (f32)(180.0f))
	{
		out_rotation._y = -360.0f + rotation._y;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	if(rotation._y <= (f32)(-180.0f))
	{
		out_rotation._y = -360.0f + rotation._y;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	if(rotation._x >= 90.0f)
	{
		//out_rotation._y = rotation._y + 180.0f;
		out_rotation._x = 180.0f - rotation._x;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	if(rotation._x <= -90.0f)
	{
		//out_rotation._y = rotation._y - 180.0f;
		out_rotation._x = 180.0f + rotation._x;
		//out_rotation = NormalizeRotation(out_rotation);
	}

	return out_rotation;
}

//---------------------------------- EOF --------------------------------------
