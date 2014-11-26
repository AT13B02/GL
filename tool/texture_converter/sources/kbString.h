//=============================================================================
//
// ������N���X [kbString.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/22
//
//=============================================================================
#pragma once
#ifndef __KBR_STRING_H__
#define __KBR_STRING_H__

// ���O���
namespace kb
{
	//******************************************************************************
	// ������N���X
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
			int nNumChar = 0;	// ������
			while(pStr[nNumChar] != '\0')
			{
				nNumChar++;
			}

			pString = new char[nNumChar + 1];

			for(int nLoop = 0; nLoop < nNumChar; nLoop++)
			{
				pString[nLoop] = pStr[nLoop];
			}
			pString[nNumChar] = '\0';	// �I�[�k������
			nLength = nNumChar;
		}
		CString(const char* pStr, const unsigned int& uSize)
		{
			unsigned int nNumChar = 0;	// ������
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
			pString[nNumChar] = '\0';	// �I�[�k������
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
		// ������Ԃ�
		//=============================================================================
		const int& GetLength() const
		{
			return nLength;
		}
		
		//=============================================================================
		// ������̐擪�ւ̃|�C���^��Ԃ�
		//=============================================================================
		const char* GetStr() const
		{
			return pString;
		}
		
		//=============================================================================
		// �w�肵���g�[�N���̕����ւ̃|�C���^��Ԃ�(������)
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
		// �w�肵���g�[�N���̕����ւ̃|�C���^��Ԃ�(�E����)
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
		// �w�肵���g�[�N���̃C���f�b�N�X��Ԃ�(������)
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
		// �w�肵���g�[�N���̃C���f�b�N�X��Ԃ�(�E����)
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
		// �w�肵���g�[�N���̑�����Ԃ�
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

		// ���Z�q�I�[�o�[���[�h
		//=============================================================================
		// ����������ɒǉ� += (CString)
		//=============================================================================
		CString& operator+=(const CString& str)
		{
			int nNewLength = nLength + str.GetLength();	// �E�̕�����̕������ǉ�

			char* NewString = new char[nNewLength + 1];

			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				NewString[nLoop] = pString[nLoop];
			}
			for(int nLoop = nLength, nRhsLoop = 0; nLoop < nNewLength; nLoop++, nRhsLoop++)
			{
				NewString[nLoop] = str[nRhsLoop];
			}
			NewString[nNewLength] = '\0';	// �I�[�����ǉ�

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		//=============================================================================
		// ����������ɒǉ� += (const char*)
		//=============================================================================
		CString& operator+=(const char* str)
		{
			int nNewLength = nLength;
			int nRhsLength = 0;
			
			while(str[nRhsLength] != '\0')
			{
				nRhsLength++;
			}
			nNewLength += nRhsLength;	// �E�̕�����̕������ǉ�

			char* NewString = new char[nNewLength + 1];
			
			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				NewString[nLoop] = pString[nLoop];
			}
			for(int nLoop = nLength, nRhsLoop = 0; nLoop < nNewLength; nLoop++, nRhsLoop++)
			{
				NewString[nLoop] = str[nRhsLoop];
			}
			NewString[nNewLength] = '\0';	// �I�[�����ǉ�

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		
		//=============================================================================
		// �������� = (CString)
		//=============================================================================
		CString& operator=(const CString& str)
		{
			int nNewLength = str.GetLength();	// �E�̕�����̕�����

			char* NewString = new char[nNewLength + 1];

			for(int nLoop = 0; nLoop < nNewLength; nLoop++)
			{
				NewString[nLoop] = str[nLoop];
			}
			NewString[nNewLength] = '\0';	// �I�[�����ǉ�

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		//=============================================================================
		// �������� = (const char*)
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
			NewString[nNewLength] = '\0';	// �I�[�����ǉ�

			delete [] pString;
			nLength = nNewLength;
			pString = NewString;

			return *this;
		}
		
		//=============================================================================
		// �������r < (CString)
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
		// �������r < (const char*)
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
		// �������r > (CString)
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
		// �������r > (const char*)
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
		// �������r <= (CString)
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
		// �������r <= (const char*)
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
		// �������r >= (CString)
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
		// �������r >= (const char*)
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
		// �������r == (CString)
		//=============================================================================
		bool operator==(const CString& str)
		{
			if(nLength != str.GetLength())
			{
				// ���������������Ⴄ
				return false;
			}

			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] != str[nLoop])
				{
					// ��ł��Ⴆ�ΏI���
					return false;
				}
			}

			// �����I��
			return true;
		}
		//=============================================================================
		// �������r == (const char*)
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
				// ���������������Ⴄ
				return false;
			}
			
			for(int nLoop = 0; nLoop < nLength; nLoop++)
			{
				if(pString[nLoop] != str[nLoop])
				{
					// ��ł��Ⴆ�ΏI���
					return false;
				}
			}

			// �����I��
			return true;
		}
		
		//=============================================================================
		// �������r != (CString)
		//=============================================================================
		bool operator!=(const CString& str)
		{
			if(nLength != str.GetLength())
			{
				// �������Ⴄ�̂�OK
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
					// ��ł��Ⴆ��OK
					return true;
				}
			}

			// �����I��������_��
			return false;
		}
		//=============================================================================
		// �������r != (const char*)
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
					// ��ł��Ⴆ��OK
					return true;
				}
			}

			return false;
		}

		//=============================================================================
		// �w�肵���C���f�b�N�X�̕�����Ԃ�
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