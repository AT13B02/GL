//=============================================================================
//
// OpenGL [OpenGL.cpp]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//
//=============================================================================

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include "OpenGL.h"
#include "Debug.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
// OpenGLExt
OpenGLExt g_OpenGLExt;

//=============================================================================
// OpenGLEXT初期化
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//=============================================================================
BOOL InitOpenGLExt(void)
{
	g_OpenGLExt.glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	_AssertExpr(g_OpenGLExt.glGenBuffers, "glGenBuffers");
	g_OpenGLExt.glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	_AssertExpr(g_OpenGLExt.glBindBuffer, "glBindBuffer");
	g_OpenGLExt.glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	_AssertExpr(g_OpenGLExt.glBufferData, "glBufferData");
	g_OpenGLExt.glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	_AssertExpr(g_OpenGLExt.glDeleteBuffers, "glDeleteBuffers");
	g_OpenGLExt.glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	_AssertExpr(g_OpenGLExt.glBufferSubData, "glBufferSubData");

	return TRUE;
}

//=============================================================================
// バッファ生成
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//=============================================================================
void glGenBuffers(GLsizei n, GLuint *buffers)
{
	g_OpenGLExt.glGenBuffers(n, buffers);
}

//=============================================================================
// バッファバインド
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//=============================================================================
void glBindBuffer(GLenum target, GLuint buffer)
{
	g_OpenGLExt.glBindBuffer(target, buffer);
}

//=============================================================================
// VRAM上にデータ生成
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//=============================================================================
void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage)
{
	g_OpenGLExt.glBufferData(target, size, data, usage);
}

//=============================================================================
// VRAM上にデータ送出
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//=============================================================================
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data)
{
	g_OpenGLExt.glBufferSubData(target, offset, size, data);
}

//=============================================================================
// バッファ破棄
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/16
//=============================================================================
void glDeleteBuffers(GLsizei n, const GLuint *buffers)
{
	g_OpenGLExt.glDeleteBuffers(n, buffers);
}

// EOF