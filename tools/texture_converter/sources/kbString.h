//=============================================================================
//
// 文字列クラス [kbString.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/22
//
//=============================================================================
#pragma once
#ifndef __KBR_STRING_H__
#define __KBR_STRING_H__

// 名前空間
namespace kb
{
	//******************************************************************************
	// 文字列クラス
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/6/22
	//******************************************************************************
	class CString
	{
	public:

		CString() : pString(0), nLength(0)
		{
			pString = new char[nLength];
		}
		CString(const char* pStr)
		{
			int nNumChar = 0;	// 文字数
			while(pStr[nNumChar] != '\0')
			{
				nNumChar++;
			}

			pString = new char[nNumChar + 1];

			for(int nLoop = 0; nLoop < nNumChar; nLoop++)
			{
				pString[nLoop] = pStr[nLoop];
			}
			pString[nNumChar] = '\0';	// 終端ヌル文字
			nLength = nNumChar;
		}
		CString(const char* pStr, const unsigned int& uSize)
		{
			unsigned int nNumChar = 0;	// 文字数
			while(pStr[nNumChar] != '\0')
			{
				nNumChar++;
			}

			if(nNumChar >= uSize)
			{
				nNumChar = uSize;
			}

			pString = new char[nNumChar + 1];

			for(int nLoop = 0; nLoop < (int)nNumChar; nLoop++)
			{
				pString[nLoop] = pStr[nLoop];
			}
			pString[nNumChar] = '\0';	// 終端ヌル文字
			nLength = (int)nNumChar;
		}

		~CString()
		{
			if(pString)
			{
				delete [] pString;
			}
		}
		
		//=============================================================================
		// 長さを返す
		//=============================================================================
		const int& GetLength() const
		{
			return nLength;
		}
		
		//=============================================================================
		// 文字列の先頭へのポインタを返す
		//=============================================================================
		const char* GetStr() const
		{
			return pString;
		}
		
		//=============================================================================
		// 指定したトークンの文字へのポインタを返す(左から)
		//=============================================================================
		char* SearchTokenPtrL(const char& tok) const
		{
			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] == tok)
				{
					return &pString[nLoop];
				}
			}

			return 0;
		}
		//=============================================================================
		// 指定したトークンの文字へのポインタを返す(右から)
		//=============================================================================
		char* SearchTokenPtrR(const char& tok) const
		{
			for(int nLoop = nLength - 1; nLoop >= 0; nLoop--)
			{
				if(pString[nLoop] == tok)
				{
					return &pString[nLoop];
				}
			}

			return 0;
		}
		
		//=============================================================================
		// 指定したトークンのインデックスを返す(左から)
		//=============================================================================
		int SearchTokenIndexL(const char& tok) const
		{
			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] == tok)
				{
					return nLoop;
				}
			}

			return -1;
		}
		//=============================================================================
		// 指定したトークンのインデックスを返す(右から)
		//=============================================================================
		int SearchTokenIndexR(const char& tok) const
		{
			for(int nLoop = nLength - 1; nLoop >= 0; nLoop--)
			{
				if(pString[nLoop] == tok)
				{
					return nLoop;
				}
			}

			return -1;
		}

		//=============================================================================
		// 指定したトークンの総数を返す
		//=============================================================================
		int GetTokenNum(const char& tok) const
		{
			int nNumTok = 0;

			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] == tok)
				{
					nNumTok++;
				}
			}

			return nNumTok;
		}

		// 演算子オーバーロード
		//=============================================================================
		// 文字列を後ろに追加 += (CString)
		//=============================================================================
		CString& operator+=(const CString& str)
		{
			int nNewLength = nLength + str.GetLength();	// 右の文字列の文字数追加

			char* NewString = new char[nNewLength + 1];

			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				NewString[nLoop] = pString[nLoop];
			}
			for(int nLoop = nLength, nRhsLoop = 0; nLoop < nNewLength; nLoop++, nRhsLoop++)
			{
				NewString[nLoop] = str[nRhsLoop];
			}
			NewString[nNewLength] = '\0';	// 終端文字追加

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		//=============================================================================
		// 文字列を後ろに追加 += (const char*)
		//=============================================================================
		CString& operator+=(const char* str)
		{
			int nNewLength = nLength;
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			nNewLength += nRhsLength;	// 右の文字列の文字数追加

			char* NewString = new char[nNewLength + 1];
			
			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				NewString[nLoop] = pString[nLoop];
			}
			for(int nLoop = nLength, nRhsLoop = 0; nLoop < nNewLength; nLoop++, nRhsLoop++)
			{
				NewString[nLoop] = str[nRhsLoop];
			}
			NewString[nNewLength] = '\0';	// 終端文字追加

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		
		//=============================================================================
		// 文字列代入 = (CString)
		//=============================================================================
		CString& operator=(const CString& str)
		{
			int nNewLength = str.GetLength();	// 右の文字列の文字数

			char* NewString = new char[nNewLength + 1];

			for(int nLoop = 0; nLoop < nNewLength; nLoop++)
			{
				NewString[nLoop] = str[nLoop];
			}
			NewString[nNewLength] = '\0';	// 終端文字追加

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		//=============================================================================
		// 文字列代入 = (const char*)
		//=============================================================================
		CString& operator=(const char* str)
		{
			int nNewLength = 0;
			
			if('\0' == str)
			{
				delete pString;
				nLength = 0;
				pString = new char[1];
				pString[0] = '\0';
				return *this;
			}

			while(str[nNewLength] != '\0')
			{
				nNewLength++;
			}

			char* NewString = new char[nNewLength + 1];
			
			for(int nLoop = 0; nLoop < nNewLength; nLoop++)
			{
				NewString[nLoop] = str[nLoop];
			}
			NewString[nNewLength] = '\0';	// 終端文字追加

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		
		//=============================================================================
		// 文字列比較 < (CString)
		//=============================================================================
		bool operator<(const CString& str)
		{
			if(nLength < str.GetLength())
			{
				return true;
			}

			return false;
		}
		//=============================================================================
		// 文字列比較 < (const char*)
		//=============================================================================
		bool operator<(const char* str)
		{
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			
			if(nLength < nRhsLength)
			{
				return true;
			}

			return false;
		}
		
		//=============================================================================
		// 文字列比較 > (CString)
		//=============================================================================
		bool operator>(const CString& str)
		{
			if(nLength > str.GetLength())
			{
				return true;
			}

			return false;
		}
		//=============================================================================
		// 文字列比較 > (const char*)
		//=============================================================================
		bool operator>(const char* str)
		{
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			
			if(nLength > nRhsLength)
			{
				return true;
			}

			return false;
		}
		
		//=============================================================================
		// 文字列比較 <= (CString)
		//=============================================================================
		bool operator<=(const CString& str)
		{
			if(nLength <= str.GetLength())
			{
				return true;
			}

			return false;
		}
		//=============================================================================
		// 文字列比較 <= (const char*)
		//=============================================================================
		bool operator<=(const char* str)
		{
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			
			if(nLength <= nRhsLength)
			{
				return true;
			}

			return false;
		}
		
		//=============================================================================
		// 文字列比較 >= (CString)
		//=============================================================================
		bool operator>=(const CString& str)
		{
			if(nLength >= str.GetLength())
			{
				return true;
			}

			return false;
		}
		//=============================================================================
		// 文字列比較 >= (const char*)
		//=============================================================================
		bool operator>=(const char* str)
		{
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			
			if(nLength >= nRhsLength)
			{
				return true;
			}

			return false;
		}
		
		//=============================================================================
		// 文字列比較 == (CString)
		//=============================================================================
		bool operator==(const CString& str)
		{
			if(nLength != str.GetLength())
			{
				// そもそも長さが違う
				return false;
			}

			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] != str[nLoop])
				{
					// 一つでも違えば終わり
					return false;
				}
			}

			// 無事終了
			return true;
		}
		//=============================================================================
		// 文字列比較 == (const char*)
		//=============================================================================
		bool operator==(const char* str)
		{
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			
			if(nLength != nRhsLength)
			{
				// そもそも長さが違う
				return false;
			}
			
			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] != str[nLoop])
				{
					// 一つでも違えば終わり
					return false;
				}
			}

			// 無事終了
			return true;
		}
		
		//=============================================================================
		// 文字列比較 != (CString)
		//=============================================================================
		bool operator!=(const CString& str)
		{
			if(nLength != str.GetLength())
			{
				// 長さが違うのでOK
				return true;
			}

			int nMaxLength;
			if(nLength <= str.GetLength())
			{
				nMaxLength = nLength;
			}
			else
			{
				nMaxLength = str.GetLength();
			}

			for(int nLoop = 0; nLoop < nMaxLength; nLoop++)
			{
				if(pString[nLoop] != str[nLoop])
				{
					// 一つでも違えばOK
					return true;
				}
			}

			// 無事終了したらダメ
			return false;
		}
		//=============================================================================
		// 文字列比較 != (const char*)
		//=============================================================================
		bool operator!=(const char* str)
		{
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			
			if(nLength != nRhsLength)
			{
				return true;
			}
			
			int nMaxLength;
			if(nLength <= nRhsLength)
			{
				nMaxLength = nLength;
			}
			else
			{
				nMaxLength = nRhsLength;
			}

			for(int nLoop = 0; nLoop < nMaxLength; nLoop++)
			{
				if(pString[nLoop] != str[nLoop])
				{
					// 一つでも違えばOK
					return true;
				}
			}

			return false;
		}

		//=============================================================================
		// 指定したインデックスの文字を返す
		//=============================================================================
		char& operator[](const int& nIndex) const
		{
			if((unsigned int)nIndex >= (unsigned int)nLength)
			{
				__asm int 3
			}
			return pString[nIndex];
		}

	private:

		char* pString;

		int nLength;
	};
};

#endif	// __KBR_STRING_H__

// EOF