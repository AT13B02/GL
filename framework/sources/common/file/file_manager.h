//*****************************************************************************
//
// �t�@�C���}�l�[�W���[�N���X
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// ���d��`�h�~
//*****************************************************************************
#pragma once

#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

//*****************************************************************************
// warning����
//*****************************************************************************

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <windows.h>
#include <string>
#include <map>

// basic
#include "basic/basic.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �N���X�̑O���Q��
//*****************************************************************************
class CFile;
class CGraphicsDevice;

//*****************************************************************************
// �N���X��`
//*****************************************************************************
template <class T> class CFileManager : public CBasic
{
public:
	// �R���X�g���N�^
	CFileManager(void);

	// �f�X�g���N�^
	~CFileManager(void);

	// ����������
	bool Init(void);

	// �I������
	void Uninit(void);

	// �ύX����
	void Change(void);

	// �ύX�t���O�𗧂Ă�
	void RaiseChangeFlag(void);

	// ���[�h(�t�H���_���S�Ă����[�h)
	void Load(const char* foldername);

	// �擾����
	T Get(const char* filename);

	// �t�@�C���̃��[�h
	void LoadFile(std::string filename);

protected:
	// �t�@�C�����X�g
	std::map<std::string,T> file_list_;

	// �ύX�t���O
	bool change_flag_;

private:
	// ���X�g�̔j��
	void ReleaseList(std::map<std::string,T>* list);

	// �t�@�C�����쐬
	virtual T Create(std::string filename) = 0;

	// �f�[�^�̍폜
	virtual void ReleaseData(T data) = 0;
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
template <class T> CFileManager<T>::CFileManager(void)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
template <class T> CFileManager<T>::~CFileManager(void)
{
}

//=============================================================================
// ����������
//=============================================================================
template <class T> bool CFileManager<T>::Init(void)
{
	return true;
}

//=============================================================================
// �I������
//=============================================================================
template <class T> void CFileManager<T>::Uninit(void)
{
	ReleaseList(&file_list_);
}

//=============================================================================
// �ύX����
//=============================================================================
template <class T> void CFileManager<T>::Change(void)
{
	if(change_flag)
	{
		MAP_FWD(std::string,T)* list = file_list_[LIST_TYPE_USE];

		file_list_[LIST_TYPE_USE] = file_list_[LIST_TYPE_LOAD];

		file_list_[LIST_TYPE_LOAD] = list;

		ReleaseList(list);

		change_flag_ = false;
	}
}

//=============================================================================
// �J������
//=============================================================================
template <class T> void CFileManager<T>::RaiseChangeFlag(void)
{
	change_flag = true;
}

//=============================================================================
// ���[�h����
//=============================================================================
template <class T> void CFileManager<T>::Load(const char* folder_name)
{
	WIN32_FIND_DATA ffd;
	char dir[MAX_PATH];
	std::string path;
	int len = 0;
	HANDLE handle;
	char file_path[MAX_PATH] = {0};

	GetCurrentDirectory(MAX_PATH,dir);

	path.clear();

	path = dir;

	len = strlen(dir);

	dir[len + 0] = '\\';
	dir[len + 1] = '*';
	dir[len + 2] = NULL;

	strcpy(dir,folder_name);
	strcat(dir,"\\*");

	// �n���h�����擾����
	handle = FindFirstFileEx(dir,FindExInfoStandard, &ffd,FindExSearchNameMatch,NULL,0);

	// �n���h���̎擾���s
	if(handle == INVALID_HANDLE_VALUE)
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
			strcpy(file_path,folder_name);
			strcat(file_path,"/");
			strcat(file_path,ffd.cFileName);

			LoadFile(file_path);
		}
	// ���̃t�@�C������������
	} while ( FindNextFile( handle, &ffd ) );

	// �n���h�������
	FindClose( handle );
}

//=============================================================================
// �擾����
//=============================================================================
template <class T> T CFileManager<T>::Get(const char* filename)
{
	std::map<std::string,T>::iterator p;

	p = file_list_.find(std::string(filename));

	// ������Ȃ�����
	if(p == file_list_.end())
	{
		return NULL;
	}

	return p->second;
}

//=============================================================================
// ���[�h����
//=============================================================================
template <class T> void CFileManager<T>::LoadFile(std::string filename)
{
	// �h�b�g�̈ʒu������
	int dot = filename.rfind('.');
	int slash = filename.rfind('/');

	if(slash == std::string::npos)
	{
		slash = 0;
	}
	else
	{
		slash += 1;
	}

	if(dot == std::string::npos)
	{
		dot = filename.size();
	}

	std::string key = filename.substr(slash,dot - slash);

	// ���łɓo�^����Ă��邩���m�F
	if(file_list_.end() != file_list_.find(key))
	{
		return;
	}

	// �t�@�C���̍쐬
	T file = Create(filename);

	// �t�@�C���̓o�^
	file_list_.insert(std::pair<std::string,T>(key,file));
}

//=============================================================================
// ���X�g�̊J������
//=============================================================================
template <class T> void CFileManager<T>::ReleaseList(std::map<std::string,T>* list)
{
	for(auto it = list->begin();it != list->end();++it)
	{
		ReleaseData(it->second);
	}
	list->clear();
}

#endif	// _FILE_MANAGER_H_

//---------------------------------- EOF --------------------------------------
