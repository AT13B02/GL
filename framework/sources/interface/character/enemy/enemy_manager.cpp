//*****************************************************************************
//
// エネミーマネージャークラス [enemy_manager.cpp]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/04/21(Mon)
// Version		: 1.00
// Update Date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "enemy_manager.h"
#include "common.h"

#include "object_manager.h"
#include "object_2d_manager.h"

#include "enemy_test.h"
#include "enemy_test3d.h"

#include "list.h"
#include "texture_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyManager::CEnemyManager(CObjectManager* pObjectManager)
{
	m_pObjectManager = pObjectManager;

	// エネミーリストを生成
	m_pEnemyList = new CList<CEnemy*>();
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyManager::~CEnemyManager(void)
{
	CEnemy* pEnemy = NULL;

	for(int i = 0;i < CEnemy::ENEMY_TYPE_MAX;i++)
	{
		// 
		SAFE_DELETE(m_aObjectNumber[i]);
	}

	// リストを先頭に
	m_pEnemyList->Begin();

	// リストが終了するまで続ける
	while(m_pEnemyList->Current() != NULL)
	{
		// エネミーを取り出す
		pEnemy = m_pEnemyList->Pop();

		// NULLチェック
		if(pEnemy != NULL)
		{
			// リストから外す
			m_pEnemyList->RaiseDeathFlag();

			// エネミーの開放
			SAFE_RELEASE(pEnemy);
		}

		// 次のリストへ
		m_pEnemyList->Next();
	}

	// エネミーリストを破棄
	SAFE_RELEASE(m_pEnemyList);
}

//=============================================================================
// 初期化処理
//=============================================================================
bool CEnemyManager::Init(void)
{
	CEnemy* pEnemy = NULL;
	int* nNumbers = NULL;
	CTextureManager* pTextureManager = m_pObjectManager->GetTextureManager();

	// オブジェクトを生成
	for(int i = 0;i < CEnemy::ENEMY_TYPE_MAX;i++)
	{
		// エネミーの生成
		pEnemy = CreateEnemy((CEnemy::ENEMY_TYPE)(i),false);

		if(pEnemy != NULL)
		{
			// エネミーに対してオブジェクトの生成を依頼
			pEnemy->CreateObject(&nNumbers);

			m_aObjectNumber[i] = nNumbers;
		}
		else
		{
			m_aObjectNumber[i] = NULL;
		}

		// エネミーの破棄
		SAFE_RELEASE(pEnemy);
	}

	return true;
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyManager::Update(void)
{
	CEnemy* pEnemy = NULL;

	// リストを先頭に
	m_pEnemyList->Begin();

	// リストが終了するまで続ける
	while(m_pEnemyList->Current() != NULL)
	{
		// エネミーを取り出す
		pEnemy = m_pEnemyList->Pop();

		// NULLチェック
		if(pEnemy != NULL)
		{
			pEnemy->Update();
		}

		// 次のリストへ
		m_pEnemyList->Next();
	}
}

//=============================================================================
// 死亡フラグを確認して破棄処理
//=============================================================================
void CEnemyManager::KillRaiseDeathFlag(void)
{
	CEnemy* pEnemy = NULL;

	// リストを先頭に
	m_pEnemyList->Begin();

	// リストが終了するまで続ける
	while(m_pEnemyList->Current() != NULL)
	{
		// エネミーを取り出す
		pEnemy = m_pEnemyList->Pop();

		// NULLチェック
		if(pEnemy != NULL)
		{
			// 死亡フラグを確認
			if(pEnemy->GetDeathFlag())
			{
				// リストから外す
				m_pEnemyList->RaiseDeathFlag();
				// エネミーの開放
				SAFE_RELEASE(pEnemy);
			}
		}

		// 次のリストへ
		m_pEnemyList->Next();
	}

	// 死亡フラグを立っているのをリストから消す
	m_pEnemyList->KillRaiseDeathFlag();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyManager::Draw(void)
{
	CEnemy* pEnemy = NULL;

	// リストを先頭に
	m_pEnemyList->Begin();

	// リストが終了するまで続ける
	while(m_pEnemyList->Current() != NULL)
	{
		// エネミーを取り出す
		pEnemy = m_pEnemyList->Pop();

		// NULLチェック
		if(pEnemy != NULL)
		{
			pEnemy->Draw();
		}

		// 次のリストへ
		m_pEnemyList->Next();
	}
}

//=============================================================================
// エネミーの生成
//=============================================================================
CEnemy* CEnemyManager::CreateEnemy(CEnemy::ENEMY_TYPE EnemyType,bool bListFlag)
{
	CEnemy* pEnemy = NULL;

	switch (EnemyType)
	{
		// テスト
		case (CEnemy::ENEMY_TYPE_TEST):
		{
			pEnemy = new CEnemyTest(m_pObjectManager,m_aObjectNumber[CEnemy::ENEMY_TYPE_TEST]);
			break;
		}
		// テスト
		case (CEnemy::ENEMY_TYPE_TEST3D):
		{
			pEnemy = new CEnemyTest3D(m_pObjectManager,m_aObjectNumber[CEnemy::ENEMY_TYPE_TEST3D]);
			break;
		}
		default:
		{
			break;
		}
	}

	// エネミーの生成をしていたら
	if(pEnemy != NULL)
	{
		// リスト結合フラグがオンの時
		if(bListFlag)
		{
			// リストに登録
			m_pEnemyList->Push(pEnemy);
		}
	}

	return pEnemy;
}

//---------------------------------- EOF --------------------------------------
