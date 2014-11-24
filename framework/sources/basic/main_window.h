//*****************************************************************************
//
// ���C���E�B���h�E����
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <windows.h>
#include "basic.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct _WINDOW_DATA
{
	HWND _hwnd;
	HINSTANCE _hinstance;
	WNDCLASSEX _wndclassex;
	u32 _width;
	u32 _height;
}WINDOW_DATA;

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CThread;
class CWindowData;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CMainWindow : public CBasic
{
public:
	// �R���X�g���N�^
	CMainWindow(HINSTANCE hinstance);

	// �f�X�g���N�^
	~CMainWindow(void);

	// ����������
	bool Init(void);

	// �I������
	void Uninit(void);

	// ���b�Z�[�W�̊m�F
	bool CheckMessage(void);

	// ���b�Z�[�W���[�v�t���O�̊m�F
	bool message_loop_flag(void){return message_loop_flag_;}

	// �E�B���h�E�n���h���̎擾
	HWND hwnd(void){return hwnd_;}

	// �C���X�^���X�̎擾
	HINSTANCE hinstance(void){return hinstance_;}

	// �E�B���h�E�f�[�^�̎擾
	WINDOW_DATA* window_data(void){return &window_data_;}

private:
	static const u32 DEFAULT_WIDTH;
	static const u32 DEFAULT_HEIGHT;
	static const s8* CLASS_NAME;
	static const s8* CAPTION_NAME;

	HWND hwnd_;
	HINSTANCE hinstance_;
	WNDCLASSEX wndclassex_;
	bool volatile message_loop_flag_;

	WINDOW_DATA window_data_;

	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

	static void Message(CMainWindow* main_window);

};

#endif // _MAIN_WINDOW_H_

//-----------------------------------EOF---------------------------------------
