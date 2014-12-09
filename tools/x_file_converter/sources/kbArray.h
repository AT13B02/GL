//=============================================================================
//
// �z��N���X [kbArray.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/21
//
//=============================================================================
#pragma once
#ifndef __KBR_ARRAY_H__
#define __KBR_ARRAY_H__

// ���O���
namespace kb
{
	//******************************************************************************
	// �z��N���X
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
			// �w�肳�ꂽ���v�f�𐶐�
			Array = new T*[nNum];
			for(int nLoop = 0; nLoop < nNum; nLoop++)
			{
				Array[nLoop] = new T;
			}
		}

		~CArray()
		{
			// �v�f�����݂���Ƃ�
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
		// �T�C�Y�擾
		//=============================================================================
		const int& GetLength() const
		{
			return nLength;
		}
		
		//=============================================================================
		// �z����m��
		//=============================================================================
		void Allocate(const int& nNum)
		{
			if(nLength)
			{
				// �m�ۂ���K�v���Ȃ��̂ŉ������Ȃ�
				return;
			}
			
			// �w�肳�ꂽ���v�f�𐶐�
			Array = new T*[nNum];
			for(int nLoop = 0; nLoop < nNum; nLoop++)
			{
				Array[nLoop] = new T;
			}
			nLength = nNum;
		}
		//=============================================================================
		// �z��̍Ċm��
		//=============================================================================
		void ReAllocate(const int& nNum)
		{
			if(!nLength)
			{
				// �z�񂪊m�ۂ���Ă��Ȃ��̂Ŋm�ۂ���
				Allocate(nNum);
				return;
			}

			ResizeInternal(nNum);
		}
		
		//=============================================================================
		// �z��̍Ō���ɒǉ�
		//=============================================================================
		void Add(const T& Factor)
		{
			ResizeInternal(nLength + 1);
			*Array[nLength - 1] = Factor;
		}
		
		//=============================================================================
		// �z��̗v�f���폜
		//=============================================================================
		void Remove(const int& nIndex)
		{
			if((DWORD)nIndex >= (DWORD)nLength)
			{
				__asm int 3
			}

			delete Array[nIndex]:
			Array[nIndex] = 0;

			// �z����l�߂�
			for(int nLoop = nIndex; nLoop < nLength - 1; nLoop++)
			{
				Array[nLoop] = Array[nLoop + 1];
			}
			// �z��Đݒ�
			ResizePtrInternal(nLength - 1);
		}

		//=============================================================================
		// �z��v�f�̃|�C���^���擾
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
		// �z��v�f�̃|�C���^��ݒ�
		// ���̐ݒ���@�̏ꍇ�A���̃|�C���^�̎Q�Ƃ��ۏ؂���Ȃ��Ȃ�̂ŁA
		// ���O�ɏ����Ă������������Ă���
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
		// �z��v�f�ɃA�N�Z�X
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
		// �z����Ċm�ۂ���
		//=============================================================================
		void ResizeInternal(const int& nNum)
		{
			if(nLength == nNum)
			{
				return;
			}

			T** NewArray = new T*[nNum];
			// ���܂ł̕�������
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
			// �V�����ݒ肷���������
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
		// �z����Ċm�ۂ���(�l�͔j�����Ȃ�)
		//=============================================================================
		void ResizePtrInternal(const int& nNum)
		{
			if(nLength == nNum)
			{
				return;
			}

			T** NewArray = new T*[nNum];
			// ���܂ł̕�������
			if(nLength > nNum)
			{
				for(int nLoop = 0; nLoop < nNum; nLoop++)
				{
					NewArray[nLoop] = Array[nLoop];
				}
			}
			// �V�����ݒ肷���������
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