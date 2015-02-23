//*****************************************************************************
//
// WindowsSocketsクラス [windows_sockets.h]
//
// Author		: 兜森 健史
// Date			: 2014/05/07(Wed)
// Version		: 1.00
// Modified by	: 兜森 健史
// Update date	: 2014/05/14(Wed)
//
//*****************************************************************************

//*****************************************************************************
// 二重定義防止
//*****************************************************************************
#pragma once

#ifndef _WINDOWS_SOCKET_H_
#define _WINDOWS_SOCKET_H_

//*****************************************************************************
// インクルード
//*****************************************************************************
#include "../../basic/basic.h"
#include <winsock.h>
#include "../../common/math/vector/vector3.h"
#include "network_data.h"
//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib,"wsock32.lib")

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
class CNetworkData;
class CNetworkDataBuffer;

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CWindowsSockets : public CBasic
{
public:
	// コンストラクタ
	CWindowsSockets(const char* pIpAddress);

	// デストラクタ
	virtual ~CWindowsSockets(void);

	// 初期化処理
	bool Init(void);

	// 終了処理
	void Uninit(void);

	// プレイヤーIDリクエスト
	void RequestID(void);

	// バッファのポインタセット
	void SetNetworkDataBufferPointer(CNetworkDataBuffer* buffer_pointer){m_DataBuffer = buffer_pointer;};

	// 準備完了を他のプレイヤーに通知
	void SendDataPrepare(int my_id);

	// ゲーム開始通知を送る
	void SendGameStart(void);

	// リザルトに切り替え通知
	void SendDataGoToResultScene(void);

	// データの送信
	void SendDataCharcter(VECTOR3* position, VECTOR3* rotation, int animation_id, int hp);	// プレイヤー
	void SendDataBullet(VECTOR3* position, VECTOR3* front_vector, float speed);		// 弾

	void SendDataMyself(char* pData,int nSize);

	// データの受信
	int ReceiveData(NETWORK_DATA* pOutData, sockaddr_in* from_addres);

	// 準備完了確認
	void CheckAllPlayerPrepare(int my_id);

	// 死亡フラグ送信
	void SendDeathFlag(int my_id);

protected:

private:
	SOCKET m_Socket;
	char m_pIpAddress[256];
	struct sockaddr_in m_Sendaddr;
	struct sockaddr_in m_Recieveaddr;
	CNetworkDataBuffer* m_DataBuffer;

	// マルチキャストアドレス

	// 送信先アドレス

	// 送信時のポート番号

	// 受信時のポート番号
};

#endif	// _WINDOWS_SOCKET_H_

//---------------------------------- EOF --------------------------------------
