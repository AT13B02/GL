//*****************************************************************************
//
// リストデータ処理 [list_data.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/03/18(Tue)
// Version		: 1.00
// Update Date	: 2014/03/18(Tue)
//
//*****************************************************************************

/**
*	リストデータクラス\n
*	リストの内部データクラス
*/

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _LIST_DATA_H_
#define _LIST_DATA_H_

//*****************************************************************************
// インクルード
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LIST_GUARD_ID	(-1)

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
// リストの内部データクラス
template <class T> class CListData
{
public:
	// コンストラクタ
	CListData(void);

	// データの取り出し
	T Pop(void);

	// データの格納
	void Push(T Data);

	// データの破棄
	void Release(void);

	// 識別IDを設定
	void SetId(int nId);

	// 識別IDを取得
	int GetId(void);

	// 使用フラグの取得
	bool GetUseFlag(void);

	bool GetDeathFlag(void){return m_bDeathFlag;}

	void RaiseDeathFlag(void){m_bDeathFlag = true;}

	// 次のポインタの取得
	CListData* GetNext(void);

	// 次のポインタの設定
	void SetNext(CListData<T>* pNext);

	// 前のポインタの取得
	CListData<T>* GetPreview(void);

	// 前のポインタの設定
	void SetPreview(CListData<T>* pPreview);
private:
	// 識別ID
	int m_nId;

	// 使用フラグ
	bool m_bUseFlag;

	// 死亡フラグ
	bool m_bDeathFlag;

	// データ
	T m_Data;

	// 次のデータのポインタ
	CListData<T>* m_pNext;

	// 前のデータのポインタ
	CListData<T>* m_pPrev;
};


template <class T> CListData<T>::CListData(void)
{
	m_nId = LIST_GUARD_ID;

	m_bUseFlag = false;

	m_bDeathFlag = false;
}

// データの取り出し処理
template <class T> T CListData<T>::Pop(void)
{
	return m_Data;
}

// データの格納処理
template <class T> void CListData<T>::Push(T Data)
{
	m_bUseFlag = true;
	m_Data = Data;
}

// データの破棄
template <class T> void CListData<T>::Release(void)
{
	m_bUseFlag = false;
	delete this;
}

// 識別IDの設定
template <class T> void CListData<T>::SetId(int nId)
{
	m_nId = nId;
}

// 識別IDの取得
template <class T> int CListData<T>::GetId(void)
{
	return m_nId;
}

// 使用フラグの取得
template <class T> bool CListData<T>::GetUseFlag(void)
{
	return m_bUseFlag;
}

// 次のポインタの取得
template <class T> CListData<T>* CListData<T>::GetNext(void)
{
	return m_pNext;
}

// 次のポインタの設定
template <class T> void CListData<T>::SetNext(CListData<T>* pNext)
{
	m_pNext = pNext;
}

// 前のポインタの取得
template <class T> CListData<T>* CListData<T>::GetPreview(void)
{
	return m_pPrev;
}

// 前のポインタの設定
template <class T> void CListData<T>::SetPreview(CListData<T>* pPreview)
{
	m_pPrev = pPreview;
}

#endif // _LIST_DATA_H_

//---------------------------------- EOF --------------------------------------
