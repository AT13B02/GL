//*****************************************************************************
//
// �L�����N�^�[�}�l�[�W���[�C���^�[�t�F�[�X�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _CHARACTER_MANAGER_INTERFACE_H_
#define _CHARACTER_MANAGER_INTERFACE_H_

//*****************************************************************************
// warning����
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <string>
#include <map>

// basic
#include "basic/basic.h"

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
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CInterfaceManager;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
template <class T> class CCharacterManagerInterface : public CBasic
{
public:
	// �R���X�g���N�^
	CCharacterManagerInterface(void);

	// �f�X�g���N�^
	virtual ~CCharacterManagerInterface(void);

	// ����������
	virtual bool Init(void) = 0;

	// �X�V����
	virtual void Update(void);

	// �I������
	virtual void Uninit(void);

	// �L�����N�^�[�̒ǉ�
	void Push(T character);

	// �L�����N�^�[���X�g�̎擾
	const std::list<T>& character_list(void){return character_list_;}

protected:
	std::list<T> character_list_;

private:

};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
template <class T> CCharacterManagerInterface::CCharacterManagerInterface(void)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
template <class T> CCharacterManagerInterface::~CCharacterManagerInterface(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
template <class T> void CCharacterManagerInterface<T>::Update(void)
{
	for(auto it = character_list_.begin();it != character_list_.end();++it)
	{
		(*it)->Update();
	}
}

//=============================================================================
// �I������
//=============================================================================
template <class T> void CCharacterManagerInterface<T>::Uninit(void)
{
	for(auto it = character_list_.begin();it != character_list_.end();++it)
	{
		(*it)->Uninit();
	}

	character_list_.clear();
}

//=============================================================================
// �ǉ�����
//=============================================================================
template <class T> void CCharacterManagerInterface<T>::Push(T character)
{
	character_list_.push_back(character);
}

#endif	// _CHARACTER_MANAGER_INTERFACE_H_

//---------------------------------- EOF --------------------------------------