//*****************************************************************************
//
// エネミーテストクラス [enemy_test.cpp]
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
#include "enemy_test.h"

#include "object_manager.h"
#include "object_2d_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 定数定義
//*****************************************************************************
const VECTOR2 CEnemyTest::DEFAULT_SIZE = VECTOR2(100.0f,100.0f);
const int CEnemyTest::OBJECT_MAX = 1;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyTest::CEnemyTest(CObjectManager* pObjectManager,int* pNumbers) : CEnemy(ENEMY_TYPE_TEST)
{
	// オブジェクトマネージャーの登録
	m_pObjectManager = pObjectManager;

	// 座標の初期化
	m_Pos = VECTOR2(DEFAULT_SCREEN_WIDTH * 0.5f,DEFAULT_SCREEN_HEIGHT * 0.5f);

	// オブジェクト番号の保存
	m_pNumber = pNumbers;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyTest::~CEnemyTest(void)
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
int CEnemyTest::CreateObject(int** pOutNumbers)
{
	CObject2DManager* pObject2DManager;

	*pOutNumbers = new int[OBJECT_MAX];

	pObject2DManager = m_pObjectManager->GetObject2DManager();

	for(int i = 0;i < OBJECT_MAX;i++)
	{
		//*pOutNumbers[i] = pObject2DManager->Create(DEFAULT_SIZE);
	}

	return OBJECT_MAX;
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyTest::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyTest::Draw(void)
{
	CObject2DManager* pObject2DManager;

	// 
	pObject2DManager = m_pObjectManager->GetObject2DManager();

	pObject2DManager->Draw(*m_pNumber,m_Pos);
}

//=============================================================================
// 破棄処理
//=============================================================================
void CEnemyTest::Release(void)
{
	CEnemy::Release();
}

//---------------------------------- EOF --------------------------------------
