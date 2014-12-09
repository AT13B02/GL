//=============================================================================
//
// 伸びる配列 [CGrowableArray.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/19
//
//=============================================================================
#pragma once
#ifndef __KBR_GROWABLEARRAY_H__
#define __KBR_GROWABLEARRAY_H__

//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <Windows.h>
#include <stdlib.h>
#include "Debug.h"

//*****************************************************************************
// 伸びる配列
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
		// 全消去処理
		RemoveAll();
	}

	// 読み取り専用配列アクセス
	const T& operator[](int nIndex) const
	{
		return GetIdDat(nIndex);
	}
	// 読み書き可能配列アクセス
	T& operator[](int nIndex)
	{
		return GetIdDat(nIndex);
	}
	// 境界値でヌルか値かを判定して、インデックスで指定されたデータを返す
	T& GetIdDat(int nIndex) const
	{
		_Assert((nIndex >= 0 && nIndex < static_cast<int>(m_uNumData)));
		return m_pData[nIndex];
	}
	// インデックスを指定して値を設定

	// 配列サイズを指定したサイズに設定しなおす
	HRESULT SetSize(int nNewSize);
	// 要素を配列に加える
	HRESULT Add(const T& val);
	// 指定したインデックスに値を設定
	HRESULT SetAt(int nIndex, const T& val);

	// データ取得
	T* GetData(void)
	{
		return m_pData;
	}

	// データ全消去
	void RemoveAll(void)
	{
		SetSize(0);
	}

	// データ数取得
	DWORD GetNumData(void)
	{
		return m_uNumData;
	}

private:
	// データ
	T		*m_pData;
	// 値が入っているデータの要素数
	DWORD	m_uNumData;
	// 確保したデータの大きさ
	DWORD	m_uMaxData;

	// 内部で配列のサイズを変更する
	HRESULT SetSizeInternal(int nNewSize);
};

//=============================================================================
// 配列サイズを指定したサイズに設定しなおす
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::SetSize(int nNewSize)
{
	int nOldDataNum = m_uNumData;	// サイズコピー

	// 現在のサイズより小さくする場合
	if(nOldDataNum > nNewSize)
	{
		// 配列が確保されていなかったとき
		_AssertExpr(m_pData, "配列が確保されていません");

		// 新しいサイズから現在のサイズまで、配置newで確保してるので
		// 明示的にデストラクタを呼んで開放する
		for(int i = nNewSize; i < nOldDataNum; i++)
		{
			m_pData[i].~T();
		}
	}

	// バッファサイズを新しいサイズに合わせる
	HRESULT hr = SetSizeInternal(nNewSize);

	// 新しいサイズが前のサイズより大きい場合
	if(nOldDataNum < nNewSize)
	{
		// 配列が確保されていなかったとき
		_AssertExpr(m_pData, "配列が確保されていません");
		
		// 前のサイズから新しいサイズまで、配置newで確保するので
		// 明示的にコンストラクタを呼ぶ
		for(int i = nOldDataNum; i < nNewSize; i++)
		{
			new (&m_pData[i]) T;
		}
	}
	
	return hr;
}

//=============================================================================
// 要素を配列に加える
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::Add(const T& val)
{
	// 配列のサイズを増やす
	HRESULT hr;
	if(FAILED(hr = SetSizeInternal(m_uNumData + 1)))
	{
		return hr;
	}

	_Assert(m_pData);

	// 配置newでメモリ確保
	new (&m_pData[m_uNumData]) T;

	// データ登録
	m_pData[m_uNumData] = val;
	m_uNumData++;

	return S_OK;
}

//=============================================================================
// 内部で配列のサイズを変更する
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::SetSizeInternal(int nNewSize)
{
	// 新しいサイズの値が不正だった場合
	if(nNewSize < 0 || nNewSize > INT_MAX / sizeof(T))// intの最大値より大きいバイト数は確保できない
	{
		_AssertExpr(0, "新しいサイズが不正です");
		return E_FAIL;
	}

	// 新しいサイズに0が指定
	if(nNewSize == 0)
	{
		// データが存在していた場合
		if(m_pData)
		{
			// データ開放
			free(m_pData);
			m_pData = NULL;
		}
		m_uNumData = 0;
		m_uMaxData = 0;
	}
	// データが存在しない、または配列が伸びるとき
	else if(m_pData == NULL || nNewSize > (int)m_uMaxData)
	{
		// 伸長できるサイズを指定(最大値が0だったら適当な数)
		// とりあえず2倍にしておけばあんまり無駄にならないかも？
		int nGrowNum = (m_uMaxData == 0) ? 16 : m_uMaxData;

		// 伸長サイズとデータサイズの合計がintより大きかった場合
		if((UINT)nGrowNum + (UINT)m_uMaxData > (UINT)INT_MAX)
		{
			nGrowNum = INT_MAX - m_uMaxData;
		}

		// 新しいサイズと現在の二倍のサイズのどちらが大きいか
		nNewSize = (nNewSize > nGrowNum + (int)m_uMaxData ? nNewSize : nGrowNum + (int)m_uMaxData);

		// とりあえずunsignedより大きくなってないか調べる
		if(sizeof(T) > UINT_MAX / (UINT)nNewSize)
		{
			_AssertExpr(0, "新しいサイズが大きすぎです");
			return E_FAIL;
		}

		// 新しくメモリを確保
		T* pDat = (T*)realloc(m_pData, sizeof(T) * nNewSize);
		if(!pDat)
		{
			_AssertExpr(0, "メモリの確保に失敗");
			return E_FAIL;
		}

		m_pData = pDat;
		m_uMaxData = nNewSize;
	}

	return S_OK;
}

//=============================================================================
// 指定したインデックスに値を設定
// Author : Ryo Kobayashi
// LastUpdate : 2014/5/24
//=============================================================================
template<class T> HRESULT CGrowableArray<T>::SetAt(int nIndex, const T& val)
{
	// インデックスが不正な領域をさしていないか
	if(nIndex < 0 || nIndex >= (int)m_uNumData)
	{
		_AssertExpr(0, "不正な領域をさした");
		return E_FAIL;
	}

	m_pData[nIndex] = val;

	return S_OK;
}

#endif	// __KBR_GROWABLEARRAY_H__

// EOF