//*****************************************************************************
//
// ���X�g�f�[�^���� [list_data.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/03/18(Tue)
// Version		: 1.00
// Update Date	: 2014/03/18(Tue)
//
//*****************************************************************************

/**
*	���X�g�f�[�^�N���X\n
*	���X�g�̓����f�[�^�N���X
*/

//*****************************************************************************
// ��d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _LIST_DATA_H_
#define _LIST_DATA_H_

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LIST_GUARD_ID	(-1)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �N���X��`
//*****************************************************************************
// ���X�g�̓����f�[�^�N���X
template <class T> class CListData
{
public:
	// �R���X�g���N�^
	CListData(void);

	// �f�[�^�̎��o��
	T Pop(void);

	// �f�[�^�̊i�[
	void Push(T Data);

	// �f�[�^�̔j��
	void Release(void);

	// ����ID��ݒ�
	void SetId(int nId);

	// ����ID���擾
	int GetId(void);

	// �g�p�t���O�̎擾
	bool GetUseFlag(void);

	bool GetDeathFlag(void){return m_bDeathFlag;}

	void RaiseDeathFlag(void){m_bDeathFlag = true;}

	// ���̃|�C���^�̎擾
	CListData* GetNext(void);

	// ���̃|�C���^�̐ݒ�
	void SetNext(CListData<T>* pNext);

	// �O�̃|�C���^�̎擾
	CListData<T>* GetPreview(void);

	// �O�̃|�C���^�̐ݒ�
	void SetPreview(CListData<T>* pPreview);
private:
	// ����ID
	int m_nId;

	// �g�p�t���O
	bool m_bUseFlag;

	// ���S�t���O
	bool m_bDeathFlag;

	// �f�[�^
	T m_Data;

	// ���̃f�[�^�̃|�C���^
	CListData<T>* m_pNext;

	// �O�̃f�[�^�̃|�C���^
	CListData<T>* m_pPrev;
};


template <class T> CListData<T>::CListData(void)
{
	m_nId = LIST_GUARD_ID;

	m_bUseFlag = false;

	m_bDeathFlag = false;
}

// �f�[�^�̎��o������
template <class T> T CListData<T>::Pop(void)
{
	return m_Data;
}

// �f�[�^�̊i�[����
template <class T> void CListData<T>::Push(T Data)
{
	m_bUseFlag = true;
	m_Data = Data;
}

// �f�[�^�̔j��
template <class T> void CListData<T>::Release(void)
{
	m_bUseFlag = false;
	delete this;
}

// ����ID�̐ݒ�
template <class T> void CListData<T>::SetId(int nId)
{
	m_nId = nId;
}

// ����ID�̎擾
template <class T> int CListData<T>::GetId(void)
{
	return m_nId;
}

// �g�p�t���O�̎擾
template <class T> bool CListData<T>::GetUseFlag(void)
{
	return m_bUseFlag;
}

// ���̃|�C���^�̎擾
template <class T> CListData<T>* CListData<T>::GetNext(void)
{
	return m_pNext;
}

// ���̃|�C���^�̐ݒ�
template <class T> void CListData<T>::SetNext(CListData<T>* pNext)
{
	m_pNext = pNext;
}

// �O�̃|�C���^�̎擾
template <class T> CListData<T>* CListData<T>::GetPreview(void)
{
	return m_pPrev;
}

// �O�̃|�C���^�̐ݒ�
template <class T> void CListData<T>::SetPreview(CListData<T>* pPreview)
{
	m_pPrev = pPreview;
}

#endif // _LIST_DATA_H_

//---------------------------------- EOF --------------------------------------
