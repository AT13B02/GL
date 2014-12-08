//=============================================================================
//
// デバッグ処理 [Debug.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/10
//
//=============================================================================
#pragma once
#ifndef __KBR_DEBUG_H__
#define __KBR_DEBUG_H__

#ifdef _DEBUG

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <stdio.h>

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define malloc(s) _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define calloc(c, s) _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define realloc(p, s) _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _realloc(p, c, s) _realloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define _expand(p, s) _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)

// 引数が0のとき、警告
#define _Assert(expr)\
	{\
		if(!(expr))\
		{\
			char assertExp[512];\
			char path[256];\
			GetModuleFileName(NULL, path, sizeof(path));\
			sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n", path, __FILE__, __LINE__, __FUNCTION__);\
			int nRet = MessageBox(NULL, assertExp, "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);\
			if(nRet == IDABORT){ PostQuitMessage(0); }\
			else if(nRet == IDRETRY){ __asm int 3 }\
		}\
	}
// 引数が0のとき、警告と文字列
#define _AssertExpr(expr, str)\
	{\
		if(!(expr))\
		{\
			char assertExp[512];\
			char path[256];\
			GetModuleFileName(NULL, path, sizeof(path));\
			sprintf_s(assertExp, 512, "Program Failed\n\nProgram : %s\nFile : %s\nLine : %d\nFunction : %s\n\n%s", path, __FILE__, __LINE__, __FUNCTION__, str);\
			int nRet = MessageBox(NULL, assertExp, "Error", MB_ABORTRETRYIGNORE | MB_ICONERROR);\
			if(nRet == IDABORT){ PostQuitMessage(0); }\
			else if(nRet == IDRETRY){ __asm int 3 }\
		}\
	}

// ファイル名のみの文字列に変換
#define _FILE_NAME_ strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__

// 指定した文字(列)を出力
#define OutDbgPrint(str, ...) \
	{\
		/* コピー先文字列 */\
		char c[256];\
		sprintf_s(c, 256, str, __VA_ARGS__);\
		/* 指定された文字列表示 */\
		OutputDebugString(c);\
	}

// ファイル名、関数名、行数付出力
#define OutDbgWithFFL(str, ...) \
	{\
		char fileFuncLine[256];\
		sprintf_s(fileFuncLine, 256, "FILE :%s / FUNC :%s() / LINE :%d\n", _FILE_NAME_, __FUNCTION__, __LINE__);\
		/* ファイル名、関数名、行数出力 */\
		OutputDebugString(fileFuncLine);\
		/* コピー先文字列 */\
		char c[256];\
		sprintf_s(c, 256, str"\n", __VA_ARGS__);\
		/* 指定された文字列表示 */\
		OutputDebugString(c);\
	}

#else

#define OutDbgPrint(str, ...) /* 空実装 */
#define OutDbgWithFFL(str, ...)
#define _Assert(expr) expr /* めんどくさがって中身で処理する場合があるから普通に展開する */
#define _AssertExpr(expr, str) expr

#endif
#endif