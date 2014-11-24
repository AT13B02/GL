//*****************************************************************************
//
// �t�@�C���}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include "file_manager.h"

// 
#include <windows.h>
#include <string.h>

// stl
#include <map>
#include <iterator>

#include "common/common.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

/*
//=============================================================================
// �f�t�H���g�R���X�g���N�^
//=============================================================================
CFileManager::CFileManager(void)
{
	// �e�N�X�`�����X�g�̐���
	for(int i = 0;i < LIST_TYPE_MAX;i++)
	{
		m_pFileList[i] = new std::map<std::string,CFile*>;
	}

	// �ύX�t���O
	m_bChangeFlag = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFileManager::~CFileManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
bool CFileManager::Init(void)
{
	return true;
}

//=============================================================================
// �I������
//=============================================================================
void CFileManager::Uninit(void)
{
}

//=============================================================================
// �ύX����
//=============================================================================
void CFileManager::Change(void)
{
	if(m_bChangeFlag)
	{
		MAP_FWD(std::string,CFile*)* pList = m_pFileList[LIST_TYPE_USE];

		m_pFileList[LIST_TYPE_USE] = m_pFileList[LIST_TYPE_LOAD];

		m_pFileList[LIST_TYPE_LOAD] = pList;

		ReleaseList(pList);

		m_bChangeFlag = false;
	}
}

//=============================================================================
// �J������
//=============================================================================
void CFileManager::RaiseChangeFlag(void)
{
	m_bChangeFlag = true;
}

//=============================================================================
// ���[�h����
//=============================================================================
void CFileManager::Load(const char* pFoldename)
{
	WIN32_FIND_DATA ffd;
	char Dir[MAX_PATH];
	std::string Path;
	int nLen = 0;
	HANDLE h;
	char aFilePath[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH,Dir);

	Path.clear();

	Path = Dir;

	nLen = strlen(Dir);

	Dir[nLen + 0] = '\\';
	Dir[nLen + 1] = '*';
	Dir[nLen + 2] = NULL;

	strcpy(Dir,pFoldename);
	strcat(Dir,"\\*");

	// �n���h�����擾����
	h = FindFirstFileEx(Dir,FindExInfoStandard, &ffd,FindExSearchNameMatch,NULL,0);

	// �n���h���̎擾���s
	if(h == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// �f�B���N�g���̏ꍇ
			if(strcmp(ffd.cFileName,".") && strcmp(ffd.cFileName,".."))
			{
			}
		}
		// �t�@�C���̏ꍇ
		else
		{
			strcpy(aFilePath,pFoldename);
			strcat(aFilePath,"/");
			strcat(aFilePath,ffd.cFileName);

			Load(aFilePath);
		}
	// ���̃t�@�C������������
	} while ( FindNextFile( h, &ffd ) );

	// �n���h�������
	FindClose( h );
}

//=============================================================================
// �ύX����
//=============================================================================
void CFileManager::ReleaseList(MAP_FWD(std::string,CFile*)* pList)
{
	for(auto it = pList->begin();it != pList->end();)
	{
		//SAFE_RELEASE(it->second);
		it = pList->erase(it);
	}
}

//=============================================================================
// �e�N�X�`���̎擾����
//=============================================================================
CFile* CFileManager::Get(const char* pFilename)
{
	std::map<std::string,CFile*>::iterator p = m_pFileList[LIST_TYPE_USE]->find(std::string(pFilename));

	// ������Ȃ�����
	if(p == m_pFileList[LIST_TYPE_USE]->end())
	{
		return NULL;
	}

	return p->second;
}

//=============================================================================
// ���[�h����
//=============================================================================
void CFileManager::LoadFile(const char* pFilename)
{
	int nLength;
	char aFilename[MAX_PATH];
	//CTexture* pTexture;
	int nCount = 0;
	bool bDot = false;
	int nStart = 0;

	// �t�@�C�����̒����̎擾
	nLength = strlen(pFilename);

	// '.'��������'/'�܂�
	for(int i = 0;i < nLength;i++)
	{
		// .����������
		if(bDot)
		{
			// '/'����������I��
			if(pFilename[nLength - i - 1] == '/')
			{
				nStart = nLength - i;
				break;
			}
			nCount++;
		}
		else if(pFilename[nLength - i - 1] == '.')
		{
			bDot = true;
		}
	}

	// �t�@�C������ݒ�
	for(int i = 0;i < nCount;i++)
	{
		aFilename[i] = pFilename[nStart + i];
	}

	aFilename[nCount] = NULL;

	std::string theKey(aFilename);

	// ���łɓo�^����Ă��邩���m�F
	if(m_pFileList[LIST_TYPE_LOAD]->end() != m_pFileList[LIST_TYPE_LOAD]->find(theKey))
	{
		return;
	}

	// 
	CFile* pFile = Create(pFilename);

	// �e�N�X�`�����쐬
	//pTexture = new CTexture(m_pGraphicsDevice,pFilename);

	// �t�@�C��
	//m_pFileList[LIST_TYPE_LOAD]->insert(std::pair<std::string,CFile*>(theKey,pTexture));
}
*/
//---------------------------------- EOF --------------------------------------
