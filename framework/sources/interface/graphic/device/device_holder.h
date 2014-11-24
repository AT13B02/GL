//*****************************************************************************
//
// �f�o�C�X�z���_�[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
/**
*
*	�`��f�o�C�X���쐬�A�폜�A�ێ�����N���X
*
*/
//*****************************************************************************

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _DEVICE_HOLDER_H_
#define _DEVICE_HOLDER_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
// basic
#include "basic/basic.h"
#include "basic/application.h"
#include "basic/main_window.h"

// graphic
#include "interface/graphic/device/graphic_device.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �O���錾
//*****************************************************************************
#ifdef _USING_DIRECTX_
class CDirectx;
#endif // _USING_DIRECTX_
#ifdef _USING_OPENGL_
class COpengl;
#endif // _USING_OPENGL_

//*****************************************************************************
// �N���X��`
//*****************************************************************************
class CDeviceHolder : public CBasic
{
public:
	// �R���X�g���N�^
	CDeviceHolder(WINDOW_DATA* window_data);

	// �f�X�g���N�^
	virtual ~CDeviceHolder(void);

	// ������
	bool Init(void);

	// �I��
	void Uninit(void);

	// �`��J�n
	void BeginDraw(void);

	// �`��I��
	void EndDraw(void);

	// ���[�h�̊J�n
	void BeginLoad(void);

	// ���[�h�̏I��
	void EndLoad(void);

	// �X�N���[���V���b�g
	void ScreenShot(void);

	// �X�N���[���V���b�g
	void ScreenShot(const s8* pFilename);

	// �N���[���̐���
	//CDeviceHolder* MakeClone(void);

	// �f�o�C�X�̕`�惂�[�h�̐ݒ�
	void SetDrawMode(const CGraphicDevice::DEVICE_MODE& device_mode);

	// �f�o�C�X�̕`�惂�[�h�̐ݒ�
	void SetLoadMode(const CGraphicDevice::DEVICE_MODE& device_mode);

	// TODO �f�o�C�X�̍Ď擾(������)
	void ResetDevice(void);

#ifdef _USING_DIRECTX_
	CDirectX* device(void){return device_;}
#endif // _USING_DIRECTX_
#ifdef _USING_OPENGL_
	COpengl* device(void){return device_;}
#endif // _USING_OPENGL_

private:
	// �R���X�g���N�^
	CDeviceHolder(void);

#ifdef _USING_DIRECTX_
	CDirectX* device_;
#endif // _USING_DIRECTX_
#ifdef _USING_OPENGL_
	COpengl* device_;
#endif // _USING_OPENGL_
	WINDOW_DATA* window_data_;
};

#endif // _GRAPHICS_API_H_

//---------------------------------- EOF --------------------------------------
