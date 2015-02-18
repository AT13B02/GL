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
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glext.h"

#pragma comment (lib, "winmm.lib")	// ���ꂪ������time~�֐����g���Ȃ�
#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "GLU32.lib")

//*****************************************************************************
// OpenGLExt�\����
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
// �J���p�֐�
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
// �v���g�^�C�v�֐�
//*****************************************************************************
// OpenGLEXT������
BOOL InitOpenGLExt(void);
// �o�b�t�@����
void glGenBuffers(GLsizei n, GLuint *buffers);
// �o�b�t�@�o�C���h
void glBindBuffer(GLenum target, GLuint buffer);
// VRAM��Ƀf�[�^����
void glBufferData(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
// VRAM��Ƀf�[�^���o
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid *data);
// �o�b�t�@�j��
void glDeleteBuffers(GLsizei n, const GLuint *buffers);

#endif	// __KBR_OPEN_GL_H__

// EOF