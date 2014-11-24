//*****************************************************************************
//
// リストクラス [list.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/18(Fri)
// Version		: 1.00
// Update Date	: 2014/04/18(Fri)
//
//*****************************************************************************

/**
*	リストクラス
*
*	リストを作成するテンプレートクラス
*	一部比較演算子が使えないと出来ない処理がある
*/

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _LIST_H_
#define _LIST_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "list_data.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#ifndef NULL
#define NULL (0)
#endif
//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// クラス定義
//*****************************************************************************
// テーブルリストクラス
template <class T> class CList
{
public:
	/**
	* @breif  コンストラクタ\n
	* @breif  指定されたサイズ分のテーブルリストを作成する\n
	* @param  void
	*/
	CList(void);

	/**
	* @breif  デストラクタ\n
	* @breif  Release関数を使いデータを破棄する\n
	* @param  void
	*/
	virtual ~CList(void);

	/**
	* @breif  リストの開放処理\n
	* @breif  リストの要素全て破棄する\n
	* @breif  デストラクタでも呼ばれる\n
	* @param  void
	* @return void
	*/
	void Release(void);

	/**
	* @breif  データの取り出し処理\n
	* @breif  現在指しているデータを取り出す\n
	* @breif  データが存在しなかった場合は0を返し、エラー通知を行う\n
	* @param  void
	* @return <T> データ
	*/
	T Pop(void);

	void Push(T Data);

	CListData<T>* Current(void){return m_pCur;}

	/**
	* @breif  データの破棄処理\n
	* @breif  現在指している場所のデータを破棄する\n
	* @breif  現在指している場所を破棄したデータの前のデータにする\n
	* @breif  前のデータがなかった場合次のデータにする\n
	* @breif  次のデータもなかった場合NULLにする\n
	* @param  void
	* @return void
	*/
	void Erase(void);

	// 中身を空にする
	void Refresh(void);

	void RaiseDeathFlag(void){m_pCur->RaiseDeathFlag();}

	void KillRaiseDeathFlag(void);

	/**
	* @breif  前のリストに移動処理\n
	* @breif  前のリストに移動する\n
	* @breif  リストがなかった時は移動しない\n
	* @param  void
	* @return void
	*/
	void Preview(void);

	/**
	* @breif  次のリストに移動処理\n
	* @breif  次のリストに移動する\n
	* @breif  次のリストがなかった時は移動しない\n
	* @param  void
	* @return void
	*/
	void Next(void);

	/**
	* @breif  先頭リストか確認処理\n
	* @breif  先頭リストかどうかを返す\n
	* @breif  先頭リストだった場合はtrue\n
	* @breif  違う場合はfalse\n
	* @param  void
	* @return bool 判定結果
	*/
	bool CheckBegin(void);

	/**
	* @breif  最終リストか確認処理\n
	* @breif  最終リストかどうかを返す\n
	* @breif  最終リストだった場合はtrue\n
	* @breif  違う場合はfalse\n
	* @param  void
	* @return bool 判定結果
	*/
	bool CheckEnd(void);

	/**
	* @breif  先頭リストに移動処理\n
	* @breif  先頭リストに移動する\n
	* @breif  リストがなかった時は何もしない\n
	* @param  void
	* @return void
	*/
	void Begin(void);

	/**
	* @breif  最終リストに移動処理\n
	* @breif  最終リストに移動する\n
	* @breif  リストがなかった時は何もしない\n
	* @param  void
	* @return void
	*/
	void End(void);

	/**
	* @breif  昇順ソート処理\n
	* @breif  昇順にソートする処理\n
	* @breif  比較演算子を使いソートする\n
	* @breif  比較演算子が使えないとコンパイルエラーになるので注意!!\n
	* @param  void
	* @return void
	*/
	//TODO 昇順ソート
	void SortAscendingOrder(void);

	/**
	* @breif  降順ソート処理\n
	* @breif  降順にソートする処理\n
	* @breif  比較演算子を使いソートする\n
	* @breif  比較演算子が使えないとコンパイルエラーになるので注意!!\n
	* @param  void
	* @return void
	*/
	//TODO 降順ソート
	void SortDescendingOrder(void);

private:

	// リストの先頭
	CListData<T>* m_pTop;

	// リストの末尾
	CListData<T>* m_pEnd;

	// 今現在指しているリスト
	CListData<T>* m_pCur;

	// リストに結合
	void LinkList(CListData<T>* pData);

	// リストから外す
	void UnlinkList(CListData<T>* pData);
};

//=============================================================================
// コンストラクタ
//=============================================================================
template <class T> CList<T>::CList(void)
{
	m_pCur = NULL;
	m_pTop = NULL;
	m_pEnd = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
template <class T> CList<T>::~CList(void)
{
}

//=============================================================================
// データの取り出し
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
// 前のリストに移動処理
//=============================================================================
template <class T> void CList<T>::Preview(void)
{
	if(m_pCur != NULL)
	{
		// 次のリストに移動
		m_pCur = m_pCur->GetPreview();
	}
}

//=============================================================================
// 次のリストに移動処理
//=============================================================================
template <class T> void CList<T>::Next(void)
{
	if(m_pCur != NULL)
	{
		// 次のリストに移動
		m_pCur = m_pCur->GetNext();
	}
}

//=============================================================================
// 開放処理
//=============================================================================
template <class T> void CList<T>::Release(void)
{
	Refresh();

	delete this;
}

//=============================================================================
// 中身を空にする処理
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
// 先頭リストに移動処理
//=============================================================================
template <class T> void CList<T>::Begin(void)
{
	// 先頭リスト
	m_pCur = m_pTop;
}

//=============================================================================
// 最終リストに移動処理
//=============================================================================
template <class T> void CList<T>::End(void)
{
	// 最終リスト
	m_pCur = m_pCur;
}

//=============================================================================
// リストの先頭かチェック
//=============================================================================
template <class T> bool CList<T>::CheckBegin(void)
{
	return m_pCurrent == m_pUseList->GetNext();
}

//=============================================================================
// リストの最後かチェック
//=============================================================================
template <class T> bool CList<T>::CheckEnd(void)
{
	return m_pCur == m_pEnd[m_nLayer]->GetPreview();
}

//=============================================================================
// リストに接続処理
//=============================================================================
template <class T> void CList<T>::LinkList(CListData<T>* pData)
{
	// 前のデータを設定
	pData->SetPreview(m_pEnd);

	// 次のデータはNULL
	pData->SetNext(NULL);

	// リストが存在しない
	if(m_pTop == NULL)
	{
		// トップに保存
		m_pTop = pData;

		m_pCur = pData;
	}
	else
	{
		// 末尾の次に追加
		m_pEnd->SetNext(pData);
	}

	// 末尾の変更
	m_pEnd = pData;
}

//=============================================================================
// リストから外す処理
//=============================================================================
template <class T> void CList<T>::UnlinkList(CListData<T>* pData)
{
	CListData<T>* pNext;
	CListData<T>* pPrev;

	// データが存在したら
	if(pData != NULL)
	{
		// 次のポインタを取得
		pNext = pData->GetNext();

		// 前のポインタを取得
		pPrev = pData->GetPreview();

		// 次のデータが存在する
		if(pNext != NULL)
		{
			// 次のデータの前のデータに削除するデータの前のデータを格納
			pNext->SetPreview(pPrev);
		}
		else
		{
			m_pEnd = pPrev;
		}

		// 前のデータが存在する
		if(pPrev != NULL)
		{
			// 前のデータの次のデータに削除するデータの次のデータを格納
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
