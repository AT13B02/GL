//*****************************************************************************
//
// レンダーステートワイヤーフレームクラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
// basic
#include "basic/application.h"

#include "interface/graphic/renderstate/state/renderstate_wireframe.h"
#ifdef _USING_OPENGL_
#include "interface/graphic/renderstate/state/opengl/gl_renderstate_wireframe.h"
#endif

#ifdef _USING_DIRECTX_
#include "interface/graphic/renderstate/state/directx/dx_renderstate_2d.h"
#endif

// common
#include "common/common.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
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
CRenderstateWireframe::CRenderstateWireframe(CDeviceHolder* device_holder) : CRenderstate(device_holder)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderstateWireframe::~CRenderstateWireframe(void)
{
}

//=============================================================================
// 作成処理
//=============================================================================
CRenderstateWireframe* CRenderstateWireframe::Create(CDeviceHolder* device_holder)
{
	CRenderstateWireframe* renderstate_wireframe = NULL;

#ifdef _USING_OPENGL_
	renderstate_wireframe = new CGLRenderstateWireframe(device_holder);
#endif

#ifdef _USING_DIRECTX_
	renderstate_2d = new CGLRenderstateWireframe(device_holder);
#endif

	return renderstate_wireframe;
}

//---------------------------------- EOF --------------------------------------
