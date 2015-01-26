//=============================================================================
//
// エントリーポイント [main.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/8
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <Windows.h>

#include "main.h"

#include "CApplication.h"

#include "Debug.h"

//=============================================================================
// エントリーポイント
// Author : Ryo Kobayashi
// LastUpdate : 2014/12/8
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	// メッセージを返す
	return CApplication::Run(lpCmdLine);
}

// EOF