//*****************************************************************************
//
// ファイルマネージャークラス
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// インクルード
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
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

/*
//=============================================================================
// デフォルトコンストラクタ
//=============================================================================
CFileManager::CFileManager(void)
{
	// テクスチャリストの生成
	for(int i = 0;i < LIST_TYPE_MAX;i++)
	{
		m_pFileList[i] = new std::map<std::string,CFile*>;
	}

	// 変更フラグ
	m_bChangeFlag = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CFileManager::~CFileManager(void)
{
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CFileManager::Init(void)
{
	return true;
}

//=============================================================================
// 終了処理
//=============================================================================
void CFileManager::Uninit(void)
{
}

//=============================================================================
// 変更処理
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
// 開放処理
//=============================================================================
void CFileManager::RaiseChangeFlag(void)
{
	m_bChangeFlag = true;
}

//=============================================================================
// ロード処理
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

	// ハンドルを取得する
	h = FindFirstFileEx(Dir,FindExInfoStandard, &ffd,FindExSearchNameMatch,NULL,0);

	// ハンドルの取得失敗
	if(h == INVALID_HANDLE_VALUE)
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
			strcpy(aFilePath,pFoldename);
			strcat(aFilePath,"/");
			strcat(aFilePath,ffd.cFileName);

			Load(aFilePath);
		}
	// 次のファイルを検索する
	} while ( FindNextFile( h, &ffd ) );

	// ハンドルを閉じる
	FindClose( h );
}

//=============================================================================
// 変更処理
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
// テクスチャの取得処理
//=============================================================================
CFile* CFileManager::Get(const char* pFilename)
{
	std::map<std::string,CFile*>::iterator p = m_pFileList[LIST_TYPE_USE]->find(std::string(pFilename));

	// 見つからなかった
	if(p == m_pFileList[LIST_TYPE_USE]->end())
	{
		return NULL;
	}

	return p->second;
}

//=============================================================================
// ロード処理
//=============================================================================
void CFileManager::LoadFile(const char* pFilename)
{
	int nLength;
	char aFilename[MAX_PATH];
	//CTexture* pTexture;
	int nCount = 0;
	bool bDot = false;
	int nStart = 0;

	// ファイル名の長さの取得
	nLength = strlen(pFilename);

	// '.'を見つけて'/'まで
	for(int i = 0;i < nLength;i++)
	{
		// .を見つけた後
		if(bDot)
		{
			// '/'があったら終了
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

	// ファイル名を設定
	for(int i = 0;i < nCount;i++)
	{
		aFilename[i] = pFilename[nStart + i];
	}

	aFilename[nCount] = NULL;

	std::string theKey(aFilename);

	// すでに登録されているかを確認
	if(m_pFileList[LIST_TYPE_LOAD]->end() != m_pFileList[LIST_TYPE_LOAD]->find(theKey))
	{
		return;
	}

	// 
	CFile* pFile = Create(pFilename);

	// テクスチャを作成
	//pTexture = new CTexture(m_pGraphicsDevice,pFilename);

	// ファイル
	//m_pFileList[LIST_TYPE_LOAD]->insert(std::pair<std::string,CFile*>(theKey,pTexture));
}
*/
//---------------------------------- EOF --------------------------------------
