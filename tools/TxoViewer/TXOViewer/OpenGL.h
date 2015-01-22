//=============================================================================
//
// OpenGL [OpenGL.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
//=============================================================================
#pragma once
#ifndef __KBR_OPEN_GL_H__
#define __KBR_OPEN_GL_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glext.h"

#pragma comment (lib, "winmm.lib")	// これが無いとtime~関数が使えない
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

//*****************************************************************************
// OpenGLExt構造体
//*****************************************************************************
struct OpenGLExt
{
	PFNGLGENBUFFERSPROC glGenBuffers;
	PFNGLBINDBUFFERPROC glBindBuffer;
	PFNGLBUFFERDATAPROC glBufferData;
	PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	PFNGLBUFFERSUBDATAPROC glBufferSubData;
};

//*****************************************************************************
// 開放用関数
//*****************************************************************************
template<typename T>
void SafeRelease(T*& obj)
{
	if(obj)
	{
		obj->Release();
		obj = nullptr;
	}
}

//*****************************************************************************
// プロトタイプ関数
//*****************************************************************************
// OpenGLEXT初期化
BOOL InitOpenGLExt(void);
// バッファ生成
void glGenBuffers(GLsizei n, GLuint *buffers);
// バッファバインド
void glBindBuffer(GLenum target, GLuint buffer);
// VRAM上にデータ生成
void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
// VRAM上にデータ送出
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
// バッファ破棄
void glDeleteBuffers(GLsizei n, const GLuint *buffers);

#endif	// __KBR_OPEN_GL_H__

// EOF