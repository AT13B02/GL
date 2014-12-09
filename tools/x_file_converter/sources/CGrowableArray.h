//=============================================================================
//
// �L�т�z�� [CGrowableArray.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/19
//
//=============================================================================
#pragma once
#ifndef __KBR_GROWABLEARRAY_H__
#define __KBR_GROWABLEARRAY_H__

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <Windows.h>
#include <stdlib.h>
#include "Debug.h"

//*****************************************************************************
// �L�т�z��
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/19
//*****************************************************************************
template<class T>
class CGrowableArray
{
public:
	CGrowableArray() : m_pData(NULL), m_uNumData(0), m_uMaxData(0){}
	~CGrowableArray()
	{
		// �S��������
		RemoveAll();
	}

	// �ǂݎ���p�z��A�N�Z�X
	const T& operator[](int nIndex) const
	{
		return GetIdDat(nIndex);
	}
	// �ǂݏ����\�z��A�N�Z�X
	T& operator[](int nIndex)
	{
		return GetIdDat(nIndex);
	}
	// ���E�l�Ńk�����l���𔻒肵�āA�C���f�b�N�X�Ŏw�肳�ꂽ�f�[�^��Ԃ�
	T& GetIdDat(int nIndex) const
	{
		_Assert((nIndex >= 0 && nIndex < static_cast<int>(m_uNumData)));
		return m_pData[nIndex];
	}
	// �C���f�b�N�X���w�肵�Ēl��ݒ�

	// �z��T�C�Y���w�肵���T�C�Y�ɐݒ肵�Ȃ���
	HRESULT SetSize(int nNewSize);
	// �v�f��z��ɉ�����
	HRESULT Add(const T& val);
	// �w�肵���C���f�b�N�X�ɒl��ݒ�
	HRESULT SetAt(int nIndex, const T& val);

	// �f�[�^�擾
	T* GetData(void)
	{
		return m_pData;
	}

	// �f�[�^�S����
	void RemoveAll(void)
	{
		SetSize(0);
	}

	// �f�[�^���擾
	DWORD GetNumData(void)
	{
		return m_uNumData;
	}

private:
	// �f�[�^
	T		*m_pData;
	// �l�������Ă���f�[�^�̗v�f��
	DWORD	m_uNumData;
	// �m�ۂ����f�[�^�̑傫��
	DWORD	m_uMaxData;

	// �����Ŕz��̃T�C�Y��ύX����
	HRESULT SetSizeInternal(int nNewSize);
};

//=============================================================================
// �z��T�C�Y���w�肵���T�C�Y�ɐݒ肵�Ȃ���
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::SetSize(int nNewSize)
{
	int nOldDataNum = m_uNumData;	// �T�C�Y�R�s�[

	// ���݂̃T�C�Y��菬��������ꍇ
	if(nOldDataNum > nNewSize)
	{
		// �z�񂪊m�ۂ���Ă��Ȃ������Ƃ�
		_AssertExpr(m_pData, "�z�񂪊m�ۂ���Ă��܂���");

		// �V�����T�C�Y���猻�݂̃T�C�Y�܂ŁA�z�unew�Ŋm�ۂ��Ă�̂�
		// �����I�Ƀf�X�g���N�^���Ă�ŊJ������
		for(int i = nNewSize; i < nOldDataNum; i++)
		{
			m_pData[i].~T();
		}
	}

	// �o�b�t�@�T�C�Y��V�����T�C�Y�ɍ��킹��
	HRESULT hr = SetSizeInternal(nNewSize);

	// �V�����T�C�Y���O�̃T�C�Y���傫���ꍇ
	if(nOldDataNum < nNewSize)
	{
		// �z�񂪊m�ۂ���Ă��Ȃ������Ƃ�
		_AssertExpr(m_pData, "�z�񂪊m�ۂ���Ă��܂���");
		
		// �O�̃T�C�Y����V�����T�C�Y�܂ŁA�z�unew�Ŋm�ۂ���̂�
		// �����I�ɃR���X�g���N�^���Ă�
		for(int i = nOldDataNum; i < nNewSize; i++)
		{
			new (&m_pData[i]) T;
		}
	}
	
	return hr;
}

//=============================================================================
// �v�f��z��ɉ�����
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::Add(const T& val)
{
	// �z��̃T�C�Y�𑝂₷
	HRESULT hr;
	if(FAILED(hr = SetSizeInternal(m_uNumData + 1)))
	{
		return hr;
	}

	_Assert(m_pData);

	// �z�unew�Ń������m��
	new (&m_pData[m_uNumData]) T;

	// �f�[�^�o�^
	m_pData[m_uNumData] = val;
	m_uNumData++;

	return S_OK;
}

//=============================================================================
// �����Ŕz��̃T�C�Y��ύX����
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::SetSizeInternal(int nNewSize)
{
	// �V�����T�C�Y�̒l���s���������ꍇ
	if(nNewSize < 0 || nNewSize > INT_MAX / sizeof(T))// int�̍ő�l���傫���o�C�g���͊m�ۂł��Ȃ�
	{
		_AssertExpr(0, "�V�����T�C�Y���s���ł�");
		return E_FAIL;
	}

	// �V�����T�C�Y��0���w��
	if(nNewSize == 0)
	{
		// �f�[�^�����݂��Ă����ꍇ
		if(m_pData)
		{
			// �f�[�^�J��
			free(m_pData);
			m_pData = NULL;
		}
		m_uNumData = 0;
		m_uMaxData = 0;
	}
	// �f�[�^�����݂��Ȃ��A�܂��͔z�񂪐L�т�Ƃ�
	else if(m_pData == NULL || nNewSize > (int)m_uMaxData)
	{
		// �L���ł���T�C�Y���w��(�ő�l��0��������K���Ȑ�)
		// �Ƃ肠����2�{�ɂ��Ă����΂���܂薳�ʂɂȂ�Ȃ������H
		int nGrowNum = (m_uMaxData == 0) ? 16 : m_uMaxData;

		// �L���T�C�Y�ƃf�[�^�T�C�Y�̍��v��int���傫�������ꍇ
		if((UINT)nGrowNum + (UINT)m_uMaxData > (UINT)INT_MAX)
		{
			nGrowNum = INT_MAX - m_uMaxData;
		}

		// �V�����T�C�Y�ƌ��݂̓�{�̃T�C�Y�̂ǂ��炪�傫����
		nNewSize = (nNewSize > nGrowNum + (int)m_uMaxData ? nNewSize : nGrowNum + (int)m_uMaxData);

		// �Ƃ肠����unsigned���傫���Ȃ��ĂȂ������ׂ�
		if(sizeof(T) > UINT_MAX / (UINT)nNewSize)
		{
			_AssertExpr(0, "�V�����T�C�Y���傫�����ł�");
			return E_FAIL;
		}

		// �V�������������m��
		T* pDat = (T*)realloc(m_pData, sizeof(T) * nNewSize);
		if(!pDat)
		{
			_AssertExpr(0, "�������̊m�ۂɎ��s");
			return E_FAIL;
		}

		m_pData = pDat;
		m_uMaxData = nNewSize;
	}

	return S_OK;
}

//=============================================================================
// �w�肵���C���f�b�N�X�ɒl��ݒ�
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::SetAt(int nIndex, const T& val)
{
	// �C���f�b�N�X���s���ȗ̈�������Ă��Ȃ���
	if(nIndex < 0 || nIndex >= (int)m_uNumData)
	{
		_AssertExpr(0, "�s���ȗ̈��������");
		return E_FAIL;
	}

	m_pData[nIndex] = val;

	return S_OK;
}

#endif	// __KBR_GROWABLEARRAY_H__

// EOF