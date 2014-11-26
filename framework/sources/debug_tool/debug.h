//*****************************************************************************
//
// デバッグ関連
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _DEBUG_H_
#define _DEBUG_H_

//*****************************************************************************
// warning消し
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "debug_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#ifdef _DEBUG
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)

#endif // _DEBUG

#ifdef _DEBUG
#define ERROR_EXIT(ErrorMessage) \
{ \
	int line = __LINE__;\
	const char *file = __FILE__;\
	char msg[_MAX_FNAME + _MAX_EXT + 256];\
	char drive[_MAX_DRIVE];\
	char dir[_MAX_DIR];\
	char fname[_MAX_FNAME];\
	char ext[_MAX_EXT];\
	_splitpath(file,drive,dir,fname,ext);\
	sprintf(msg,ErrorMessage"\r\n"\
	"ファイル : %s%s\r\n"\
	"行番号 : %d",fname,ext,line);\
	MessageBox(NULL,msg,"Error",MB_OK | MB_ICONEXCLAMATION);\
}
#else
#define ERROR_EXIT(ErrorMessage) {}
#endif // _DEBUG

#endif // _DEBUG_H_

//---------------------------------- EOF --------------------------------------
