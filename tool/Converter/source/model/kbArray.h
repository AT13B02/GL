//=============================================================================
//
// 配列クラス [kbArray.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/21
//
//=============================================================================
#pragma once
#ifndef __KBR_ARRAY_H__
#define __KBR_ARRAY_H__

// 名前空間
namespace kb
{
	//******************************************************************************
	// 配列クラス
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/6/21
	//******************************************************************************
	template<class T>
	class CArray
	{
	public:

		CArray() : Array(0), nLength(0){}

		CArray(const int& nNum) : nLength(nNum)
		{
			// 指定された数要素を生成
			Array = new T*[nNum];
			for(int nLoop = 0; nLoop < nNum; nLoop++)
			{
				Array[nLoop] = new T;
			}
		}

		~CArray()
		{
			// 要素が存在するとき
			if(Array)
			{
				for(int nLoop = 0; nLoop < nLength; nLoop++)
				{
					delete Array[nLoop];
				}
				delete [] Array;
			}
		}
		
		//=============================================================================
		// サイズ取得
		//=============================================================================
		const int& GetLength() const
		{
			return nLength;
		}
		
		//=============================================================================
		// 配列を確保
		//=============================================================================
		void Allocate(const int& nNum)
		{
			if(nLength)
			{
				// 確保する必要がないので何もしない
				return;
			}
			
			// 指定された数要素を生成
			Array = new T*[nNum];
			for(int nLoop = 0; nLoop < nNum; nLoop++)
			{
				Array[nLoop] = new T;
			}
			nLength = nNum;
		}
		//=============================================================================
		// 配列の再確保
		//=============================================================================
		void ReAllocate(const int& nNum)
		{
			if(!nLength)
			{
				// 配列が確保されていないので確保する
				Allocate(nNum);
				return;
			}

			ResizeInternal(nNum);
		}
		
		//=============================================================================
		// 配列の最後尾に追加
		//=============================================================================
		void Add(const T& Factor)
		{
			ResizeInternal(nLength + 1);
			*Array[nLength - 1] = Factor;
		}
		
		//=============================================================================
		// 配列の要素を削除
		//=============================================================================
		void Remove(const int& nIndex)
		{
			if((DWORD)nIndex >= (DWORD)nLength)
			{
				__asm int 3
			}

			delete Array[nIndex]:
			Array[nIndex] = 0;

			// 配列を詰める
			for(int nLoop = nIndex; nLoop < nLength - 1; nLoop++)
			{
				Array[nLoop] = Array[nLoop + 1];
			}
			// 配列再設定
			ResizePtrInternal(nLength - 1);
		}

		//=============================================================================
		// 配列要素のポインタを取得
		//=============================================================================
		T* GetPtr(const int& nIndex) const
		{
			if((DWORD)nIndex >= (DWORD)nLength)
			{
				__asm int 3
			}
			return Array[nIndex];
		}
		
		//=============================================================================
		// 配列要素のポインタを設定
		// この設定方法の場合、元のポインタの参照が保証されなくなるので、
		// 事前に消しておくか何かしておく
		//=============================================================================
		void SetPtr(const int& nIndex, T* pFactor)
		{
			if((DWORD)nIndex >= (DWORD)nLength)
			{
				__asm int 3
			}
			Array[nIndex] = pFactor;
		}
		
		//=============================================================================
		// 配列要素にアクセス
		//=============================================================================
		T& operator[](const int& nIndex)
		{
			if((DWORD)nIndex >= (DWORD)nLength)
			{
				__asm int 3;
			}
			return *Array[nIndex];
		}
		const T& operator[](const int& nIndex) const
		{
			if((DWORD)nIndex >= (DWORD)nLength)
			{
				__asm int 3;
			}
			return *Array[nIndex];
		}

	private:
		
		//=============================================================================
		// 配列を再確保する
		//=============================================================================
		void ResizeInternal(const int& nNum)
		{
			if(nLength == nNum)
			{
				return;
			}

			T** NewArray = new T*[nNum];
			// 今までの方が長い
			if(nLength > nNum)
			{
				for(int nLoop = 0; nLoop < nNum; nLoop++)
				{
					NewArray[nLoop] = Array[nLoop];
				}
				for(int nLoop = nNum; nLoop < nLength; nLoop++)
				{
					delete Array[nLoop];
				}
			}
			// 新しく設定する方が長い
			else if(nLength < nNum)
			{
				for(int nLoop = 0; nLoop < nLength; nLoop++)
				{
					NewArray[nLoop] = Array[nLoop];
				}
				for(int nLoop = nLength; nLoop < nNum; nLoop++)
				{
					NewArray[nLoop] = new T;
				}
			}
			delete [] Array;
			nLength = nNum;
			Array = NewArray;
		}
		
		//=============================================================================
		// 配列を再確保する(値は破棄しない)
		//=============================================================================
		void ResizePtrInternal(const int& nNum)
		{
			if(nLength == nNum)
			{
				return;
			}

			T** NewArray = new T*[nNum];
			// 今までの方が長い
			if(nLength > nNum)
			{
				for(int nLoop = 0; nLoop < nNum; nLoop++)
				{
					NewArray[nLoop] = Array[nLoop];
				}
			}
			// 新しく設定する方が長い
			else if(nLength < nNum)
			{
				for(int nLoop = 0; nLoop < nLength; nLoop++)
				{
					NewArray[nLoop] = Array[nLoop];
				}
			}
			delete [] Array;
			nLength = nNum;
			Array = NewArray;
		}

		T** Array;
		int nLength;
	};
};

#endif	// __KBR_ARRAY_H__

// EOF