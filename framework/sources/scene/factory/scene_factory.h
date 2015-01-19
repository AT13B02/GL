//*****************************************************************************
//
// シーンファクトリークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "scene/scene.h"
#include "scene/title/scene_title.h"
#include "scene/match/scene_match.h"
#include "scene/game/scene_game.h"
#include "scene/load/scene_load.h"
#include "scene/result/scene_result.h"

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
class CInterfaceManager;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CSceneFactory
{
public:
	// コンストラクタ
	CSceneFactory(CScene::TYPE scene_type){scene_type_ = scene_type;}

	// デストラクタ
	virtual ~CSceneFactory(void){}

	virtual CScene* Make(CInterfaceManager* interface_manager) = 0;

	CScene::TYPE scene_type(void){return scene_type_;}
protected:

private:
	CScene::TYPE scene_type_;
};

class CTitleFactory : public CSceneFactory
{
public:

	// コンストラクタ
	CTitleFactory(void) : CSceneFactory(CScene::TYPE_TITLE){}

	// デストラクタ
	virtual ~CTitleFactory(void){}

	CScene* Make(CInterfaceManager* interface_manager){return new CSceneTitle(interface_manager);}
protected:

private:
};

class CMatchFactory : public CSceneFactory
{
public:

	// コンストラクタ
	CMatchFactory(void) : CSceneFactory(CScene::TYPE_MATCH){}

	// デストラクタ
	virtual ~CMatchFactory(void){}

	CScene* Make(CInterfaceManager* interface_manager){return new CSceneMatch(interface_manager);}
protected:

private:
};

class CGameFactory : public CSceneFactory
{
public:

	// コンストラクタ
	CGameFactory(void) : CSceneFactory(CScene::TYPE_GAME){}

	// デストラクタ
	virtual ~CGameFactory(void){}

	CScene* Make(CInterfaceManager* interface_manager){return new CSceneGame(interface_manager);}

protected:

private:
};

class CLoadFactory : public CSceneFactory
{
public:

	// コンストラクタ
	CLoadFactory(void) : CSceneFactory(CScene::TYPE_LOAD){}

	// デストラクタ
	virtual ~CLoadFactory(void){}

	CScene* Make(CInterfaceManager* interface_manager){return new CSceneLoad(interface_manager);}

protected:

private:
};

class CResultFactory : public CSceneFactory
{
public:

	// コンストラクタ
	CResultFactory(void) : CSceneFactory(CScene::TYPE_RESULT){}

	// デストラクタ
	virtual ~CResultFactory(void){}

	CScene* Make(CInterfaceManager* interface_manager){return new CSceneResult(interface_manager);}
protected:

private:
};

#endif	// _SCENE_FACTORY_H_

//---------------------------------- EOF --------------------------------------
