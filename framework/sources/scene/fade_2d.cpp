//*****************************************************************************
//
// Fade2Dクラス
//
// Author		: Tomohiro Kouno
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "basic/application.h"

// interface
#include "interface/interface_manager.h"

// graphic
#include "interface/graphic/graphic_manager.h"
#include "interface/graphic/vertex/vertex_2d.h"
#include "interface/graphic/object/object_2d/element/rectangle_2d.h"
#include "interface/graphic/object/object_2d/object_2d_data.h"
#include "interface/graphic/texture/texture_manager.h"
#include "interface/graphic/texture/texture.h"
#include "interface/graphic/object/object_manager.h"
#include "interface/graphic/object/object_2d/object_2d_manager.h"

#include "fade_2d.h"

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
CFade2D::CFade2D(CInterfaceManager* interface_manager):
rectangle_2d_(nullptr),
rectangle_2d_key_(NULL),
fadetype_(FADE_TYPE_OUT_END),
alpha_(1.0f),
speed_(0.01f)
{
	
	rectangle_2d_ =new  CRectangle2D(interface_manager->graphic_manager()->device_holder());
	rectangle_2d_->set_size(VECTOR2((f32)DEFAULT_SCREEN_WIDTH,(f32)DEFAULT_SCREEN_HEIGHT));
	rectangle_2d_->set_point(CRectangle2D::POINT_LEFT_UP);
	rectangle_2d_->Set();

	interface_manager_ = interface_manager;
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	rectangle_2d_key_ = object_2d_manager->AddList(rectangle_2d_);
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade2D::~CFade2D(void)
{
}

//=============================================================================
// 初期化
//=============================================================================
bool CFade2D::Init(void)
{
	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CFade2D::Update(void)
{
	//フェード状態に従いαを遷移
	if(fadetype_ == FADE_TYPE_IN)
	{
		alpha_ -= speed_;
	}
	else if(fadetype_ == FADE_TYPE_OUT)
	{
		alpha_ += speed_;
	}

	//限界値に達したらフェード終了状態を設定
	if(alpha_ <= 0.0f && fadetype_ == FADE_TYPE_IN)
	{
		fadetype_ = FADE_TYPE_IN_END;
	}
	else if(alpha_ >= 1.0f && fadetype_ == FADE_TYPE_OUT)
	{
		fadetype_ = FADE_TYPE_OUT_END;
	}

	//フェードポリゴンに色情報を適用
	rectangle_2d_->set_color(COLOR4F(1.0f,1.0f,1.0f,alpha_));
	rectangle_2d_->Set();
}

//=============================================================================
// 描画処理
//=============================================================================
void CFade2D::Draw(void)
{
	CGraphicManager* graphic_manager = interface_manager_->graphic_manager();
	CObjectManager* object_manager = graphic_manager->object_manager();
	CObject2DManager* object_2d_manager = object_manager->object_2d_manager();
	object_2d_manager->Draw(rectangle_2d_key_,VECTOR2(0,0),0.0f,VECTOR2(1.0f,1.0f),MATRIX4x4(),"field000");
}

//=============================================================================
// 終了
//=============================================================================
void CFade2D::Uninit (void)
{
	
}
//---------------------------------- EOF --------------------------------------
