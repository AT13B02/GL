//*****************************************************************************
//
// ���X�g�N���X [list.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/18(Fri)
// Version		: 1.00
// Update Date	: 2014/04/18(Fri)
//
//*****************************************************************************

/**
*	���X�g�N���X
*
*	���X�g���쐬����e���v���[�g�N���X
*	�ꕔ��r���Z�q���g���Ȃ��Əo���Ȃ�����������
*/

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _LIST_H_
#define _LIST_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "list_data.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#ifndef NULL
#define NULL (0)
#endif
//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
// �e�[�u�����X�g�N���X
template <class T> class CList
{
public:
	/**
	* @breif  �R���X�g���N�^\n
	* @breif  �w�肳�ꂽ�T�C�Y���̃e�[�u�����X�g���쐬����\n
	* @param  void
	*/
	CList(void);

	/**
	* @breif  �f�X�g���N�^\n
	* @breif  Release�֐����g���f�[�^��j������\n
	* @param  void
	*/
	virtual ~CList(void);

	/**
	* @breif  ���X�g�̊J������\n
	* @breif  ���X�g�̗v�f�S�Ĕj������\n
	* @breif  �f�X�g���N�^�ł��Ă΂��\n
	* @param  void
	* @return void
	*/
	void Release(void);

	/**
	* @breif  �f�[�^�̎��o������\n
	* @breif  ���ݎw���Ă���f�[�^�����o��\n
	* @breif  �f�[�^�����݂��Ȃ������ꍇ��0��Ԃ��A�G���[�ʒm���s��\n
	* @param  void
	* @return <T> �f�[�^
	*/
	T Pop(void);

	void Push(T Data);

	CListData<T>* Current(void){return m_pCur;}

	/**
	* @breif  �f�[�^�̔j������\n
	* @breif  ���ݎw���Ă���ꏊ�̃f�[�^��j������\n
	* @breif  ���ݎw���Ă���ꏊ��j�������f�[�^�̑O�̃f�[�^�ɂ���\n
	* @breif  �O�̃f�[�^���Ȃ������ꍇ���̃f�[�^�ɂ���\n
	* @breif  ���̃f�[�^���Ȃ������ꍇNULL�ɂ���\n
	* @param  void
	* @return void
	*/
	void Erase(void);

	// ���g����ɂ���
	void Refresh(void);

	void RaiseDeathFlag(void){m_pCur->RaiseDeathFlag();}

	void KillRaiseDeathFlag(void);

	/**
	* @breif  �O�̃��X�g�Ɉړ�����\n
	* @breif  �O�̃��X�g�Ɉړ�����\n
	* @breif  ���X�g���Ȃ��������͈ړ����Ȃ�\n
	* @param  void
	* @return void
	*/
	void Preview(void);

	/**
	* @breif  ���̃��X�g�Ɉړ�����\n
	* @breif  ���̃��X�g�Ɉړ�����\n
	* @breif  ���̃��X�g���Ȃ��������͈ړ����Ȃ�\n
	* @param  void
	* @return void
	*/
	void Next(void);

	/**
	* @breif  �擪���X�g���m�F����\n
	* @breif  �擪���X�g���ǂ�����Ԃ�\n
	* @breif  �擪���X�g�������ꍇ��true\n
	* @breif  �Ⴄ�ꍇ��false\n
	* @param  void
	* @return bool ���茋��
	*/
	bool CheckBegin(void);

	/**
	* @breif  �ŏI���X�g���m�F����\n
	* @breif  �ŏI���X�g���ǂ�����Ԃ�\n
	* @breif  �ŏI���X�g�������ꍇ��true\n
	* @breif  �Ⴄ�ꍇ��false\n
	* @param  void
	* @return bool ���茋��
	*/
	bool CheckEnd(void);

	/**
	* @breif  �擪���X�g�Ɉړ�����\n
	* @breif  �擪���X�g�Ɉړ�����\n
	* @breif  ���X�g���Ȃ��������͉������Ȃ�\n
	* @param  void
	* @return void
	*/
	void Begin(void);

	/**
	* @breif  �ŏI���X�g�Ɉړ�����\n
	* @breif  �ŏI���X�g�Ɉړ�����\n
	* @breif  ���X�g���Ȃ��������͉������Ȃ�\n
	* @param  void
	* @return void
	*/
	void End(void);

	/**
	* @breif  �����\�[�g����\n
	* @breif  �����Ƀ\�[�g���鏈��\n
	* @breif  ��r���Z�q���g���\�[�g����\n
	* @breif  ��r���Z�q���g���Ȃ��ƃR���p�C���G���[�ɂȂ�̂Œ���!!\n
	* @param  void
	* @return void
	*/
	//TODO �����\�[�g
	void SortAscendingOrder(void);

	/**
	* @breif  �~���\�[�g����\n
	* @breif  �~���Ƀ\�[�g���鏈��\n
	* @breif  ��r���Z�q���g���\�[�g����\n
	* @breif  ��r���Z�q���g���Ȃ��ƃR���p�C���G���[�ɂȂ�̂Œ���!!\n
	* @param  void
	* @return void
	*/
	//TODO �~���\�[�g
	void SortDescendingOrder(void);

private:

	// ���X�g�̐擪
	CListData<T>* m_pTop;

	// ���X�g�̖���
	CListData<T>* m_pEnd;

	// �����ݎw���Ă��郊�X�g
	CListData<T>* m_pCur;

	// ���X�g�Ɍ���
	void LinkList(CListData<T>* pData);

	// ���X�g����O��
	void UnlinkList(CListData<T>* pData);
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
template <class T> CList<T>::CList(void)
{
	m_pCur = NULL;
	m_pTop = NULL;
	m_pEnd = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
template <class T> CList<T>::~CList(void)
{
}

//=============================================================================
// �f�[�^�̎��o��
//=============================================================================
template <class T> T CList<T>::Pop(void)
{
	if(m_pCur != NULL)
	{
		return m_pCur->Pop();
	}

	return (T)0;
}

template <class T> void CList<T>::Push(T Data)
{
	CListData<T>* pData;

	pData = new CListData<T>;

	pData->Push(Data);

	LinkList(pData);
}

//=============================================================================
// �O�̃��X�g�Ɉړ�����
//=============================================================================
template <class T> void CList<T>::Preview(void)
{
	if(m_pCur != NULL)
	{
		// ���̃��X�g�Ɉړ�
		m_pCur = m_pCur->GetPreview();
	}
}

//=============================================================================
// ���̃��X�g�Ɉړ�����
//=============================================================================
template <class T> void CList<T>::Next(void)
{
	if(m_pCur != NULL)
	{
		// ���̃��X�g�Ɉړ�
		m_pCur = m_pCur->GetNext();
	}
}

//=============================================================================
// �J������
//=============================================================================
template <class T> void CList<T>::Release(void)
{
	Refresh();

	delete this;
}

//=============================================================================
// ���g����ɂ��鏈��
//=============================================================================
template <class T> void CList<T>::Refresh(void)
{
	CListData<T>* pWork;
	CListData<T>* pNext;

	pWork = m_pTop;

	while(pWork != NULL)
	{
		pNext = pWork->GetNext();

		pWork->RaiseDeathFlag();

		pWork = pNext;
	}

	// 
	KillRaiseDeathFlag();

}

//=============================================================================
// �擪���X�g�Ɉړ�����
//=============================================================================
template <class T> void CList<T>::Begin(void)
{
	// �擪���X�g
	m_pCur = m_pTop;
}

//=============================================================================
// �ŏI���X�g�Ɉړ�����
//=============================================================================
template <class T> void CList<T>::End(void)
{
	// �ŏI���X�g
	m_pCur = m_pCur;
}

//=============================================================================
// ���X�g�̐擪���`�F�b�N
//=============================================================================
template <class T> bool CList<T>::CheckBegin(void)
{
	return m_pCurrent == m_pUseList->GetNext();
}

//=============================================================================
// ���X�g�̍Ōォ�`�F�b�N
//=============================================================================
template <class T> bool CList<T>::CheckEnd(void)
{
	return m_pCur == m_pEnd[m_nLayer]->GetPreview();
}

//=============================================================================
// ���X�g�ɐڑ�����
//=============================================================================
template <class T> void CList<T>::LinkList(CListData<T>* pData)
{
	// �O�̃f�[�^��ݒ�
	pData->SetPreview(m_pEnd);

	// ���̃f�[�^��NULL
	pData->SetNext(NULL);

	// ���X�g�����݂��Ȃ�
	if(m_pTop == NULL)
	{
		// �g�b�v�ɕۑ�
		m_pTop = pData;

		m_pCur = pData;
	}
	else
	{
		// �����̎��ɒǉ�
		m_pEnd->SetNext(pData);
	}

	// �����̕ύX
	m_pEnd = pData;
}

//=============================================================================
// ���X�g����O������
//=============================================================================
template <class T> void CList<T>::UnlinkList(CListData<T>* pData)
{
	CListData<T>* pNext;
	CListData<T>* pPrev;

	// �f�[�^�����݂�����
	if(pData != NULL)
	{
		// ���̃|�C���^���擾
		pNext = pData->GetNext();

		// �O�̃|�C���^���擾
		pPrev = pData->GetPreview();

		// ���̃f�[�^�����݂���
		if(pNext != NULL)
		{
			// ���̃f�[�^�̑O�̃f�[�^�ɍ폜����f�[�^�̑O�̃f�[�^���i�[
			pNext->SetPreview(pPrev);
		}
		else
		{
			m_pEnd = pPrev;
		}

		// �O�̃f�[�^�����݂���
		if(pPrev != NULL)
		{
			// �O�̃f�[�^�̎��̃f�[�^�ɍ폜����f�[�^�̎��̃f�[�^���i�[
			pPrev->SetNext(pNext);
		}
		else
		{
			m_pTop = pNext;
		}
	}
}


template <class T> void CList<T>::KillRaiseDeathFlag(void)
{
	CListData<T>* pWork;
	CListData<T>* pNext;

	pWork = m_pTop;

	while(pWork != NULL)
	{
		pNext = pWork->GetNext();
		if(pWork->GetDeathFlag())
		{
			UnlinkList(pWork);
			pWork->Release();
		}
		pWork = pNext;
	}
}
#endif // _LIST_H_

//---------------------------------- EOF --------------------------------------
