//*****************************************************************************
//
// ファイルマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

//*****************************************************************************
// warning消し
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <windows.h>
#include <string>
#include <map>

// basic
#include "basic/basic.h"

//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// クラスの前方参照
//*****************************************************************************
class CFile;
class CGraphicsDevice;

//*****************************************************************************
// クラス定義
//*****************************************************************************
template <class T> class CFileManager : public CBasic
{
public:
	// コンストラクタ
	CFileManager(void);

	// デストラクタ
	~CFileManager(void);

	// 初期化処理
	bool Init(void);

	// 終了処理
	void Uninit(void);

	// 変更処理
	void Change(void);

	// 変更フラグを立てる
	void RaiseChangeFlag(void);

	// ロード(フォルダ内全てをロード)
	void Load(const char* foldername);

	// 取得処理
	T Get(const char* filename);

	// ファイルのロード
	void LoadFile(std::string filename);

protected:
	// ファイルリスト
	std::map<std::string,T> file_list_;

	// 変更フラグ
	bool change_flag_;

private:
	// リストの破棄
	void ReleaseList(std::map<std::string,T>* list);

	// ファイルを作成
	virtual T Create(std::string filename) = 0;

	// データの削除
	virtual void ReleaseData(T data) = 0;
};

//=============================================================================
// コンストラクタ
//=============================================================================
template <class T> CFileManager<T>::CFileManager(void)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
template <class T> CFileManager<T>::~CFileManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
template <class T> bool CFileManager<T>::Init(void)
{
	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
template <class T> void CFileManager<T>::Uninit(void)
{
	ReleaseList(&file_list_);
}

//=============================================================================
// 変更処理
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
// 開放処理
//=============================================================================
template <class T> void CFileManager<T>::RaiseChangeFlag(void)
{
	change_flag = true;
}

//=============================================================================
// ロード処理
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

	// ハンドルを取得する
	handle = FindFirstFileEx(dir,FindExInfoStandard, &ffd,FindExSearchNameMatch,NULL,0);

	// ハンドルの取得失敗
	if(handle == INVALID_HANDLE_VALUE)
	{
		return;
	}

	do
	{
		if(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// ディレクトリの場合
			if(strcmp(ffd.cFileName,".") && strcmp(ffd.cFileName,".."))
			{
			}
		}
		// ファイルの場合
		else
		{
			strcpy(file_path,folder_name);
			strcat(file_path,"/");
			strcat(file_path,ffd.cFileName);

			LoadFile(file_path);
		}
	// 次のファイルを検索する
	} while ( FindNextFile( handle, &ffd ) );

	// ハンドルを閉じる
	FindClose( handle );
}

//=============================================================================
// 取得処理
//=============================================================================
template <class T> T CFileManager<T>::Get(const char* filename)
{
	std::map<std::string,T>::iterator p;

	p = file_list_.find(std::string(filename));

	// 見つからなかった
	if(p == file_list_.end())
	{
		return NULL;
	}

	return p->second;
}

//=============================================================================
// ロード処理
//=============================================================================
template <class T> void CFileManager<T>::LoadFile(std::string filename)
{
	// ドットの位置を検索
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

	// すでに登録されているかを確認
	if(file_list_.end() != file_list_.find(key))
	{
		return;
	}

	// ファイルの作成
	T file = Create(filename);

	// ファイルの登録
	file_list_.insert(std::pair<std::string,T>(key,file));
}

//=============================================================================
// リストの開放処理
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
