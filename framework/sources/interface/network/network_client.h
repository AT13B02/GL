//*****************************************************************************
//
// ネットワーククライアントクラス [network_client.h]
//
// Author		: KENJI KABUTOMORI
// Date			: 2014/09/17(Wed)
// Version		: 1.00
// Update Date	: 2014/09/17(Wed)
//
//*****************************************************************************

//*****************************************************************************
// 多重定義防止
//*****************************************************************************
#pragma once

#ifndef _NETWORK_CLIENT_H_
#define _NETWORK_CLIENT_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "../../basic/basic.h"
#include <winsock.h>
#include "network_data.h"

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
// クラスの前方参照
//*****************************************************************************
class CThread;
class CWindowsSockets;
class CNetworkDataBuffer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CNetworkClient : public CBasic
{
public:
	// コンストラクタ
	CNetworkClient(void);

	// デストラクタ
	virtual ~CNetworkClient(void);

	// 初期化処理
	bool Init(void);

	// 終了処理
	void Uninit(void);

	// ネットワークデータバッファ
	CNetworkDataBuffer* GetNetworkDataBuffer(void){return m_pNetworkDataBuffer;}

	CWindowsSockets* GetWinSock(void){return m_pWinsock;};

	// 全員準備完了してるかのフラグアクセサ
	bool GetEndAllPlayerPrepareFlag(void){return m_bAllPlayerPrepare;};
	void SetEndAllPlayerPrepareFlag(bool flag){m_bAllPlayerPrepare = flag;};

	// ゲームスタートのフラグアクセサ
	bool GetStartGameFlag(void){return m_bStartGame;};
	void SetStartGameFlag(bool flag){m_bStartGame = flag;};

protected:

private:
	CThread*			m_pThread;
	bool volatile		m_bLoopFlag;
	CWindowsSockets*	m_pWinsock;
	CNetworkDataBuffer* m_pNetworkDataBuffer;
	static s8			m_myID;
	bool				m_bAllPlayerPrepare;
	bool				m_bStartGame;

	// 受信スレッド処理
	static unsigned __stdcall ReceiveThread(CNetworkClient* pNetworkClient);
};

#endif	// _NETWORK_CLIENT_H_

//---------------------------------- EOF --------------------------------------
