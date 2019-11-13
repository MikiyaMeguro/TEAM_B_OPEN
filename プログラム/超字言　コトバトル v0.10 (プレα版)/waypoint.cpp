//=============================================================================
//
// 経路情報のビルボード処理 [waypoint.cpp]
// Author :　目黒 未来也
//
//=============================================================================
#include "waypoint.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "InputKeyboard.h"
#include "PlayerNumSelect.h"
#include "debugProc.h"

#include "sceneX.h"
#include "object.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CWaypoint::CWaypoint() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	nNumWayPoint = 0;
}

//--------------------------------------------
// デストラクタ
//--------------------------------------------
CWaypoint::~CWaypoint()
{
}

//--------------------------------------------
// 生成
//--------------------------------------------
CWaypoint *CWaypoint::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag)
{
	CWaypoint *pWaypoint = NULL;

	if (pWaypoint == NULL)
	{
		pWaypoint = new CWaypoint;

		if (pWaypoint != NULL)
		{
			//値の代入
			pWaypoint->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWaypoint->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			//設定
			pWaypoint->Init(pos);
			pWaypoint->BindTexture(Tag);
		}
	}

	return pWaypoint;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWaypoint::Init(D3DXVECTOR3 pos)
{
	//CSceneBillBoard::Init(pos);
	D3DXVECTOR3 InitPos(0, 0, 0);
	D3DXVECTOR3 SetPos(0, 0, 0);

	//初期化
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		WayPoint[nCntWayPoint].pWayPoint = NULL;
		WayPoint[nCntWayPoint].WayPointPos = D3DXVECTOR3(0, 0, 0);
		WayPoint[nCntWayPoint].bInPlayer = 0;
		WayPoint[nCntWayPoint].nWayPointNum = 9;
		WayPoint[nCntWayPoint].bInPlayer = false;
		WayPoint[nCntWayPoint].bBlock = false;
	}
	//生成
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		SetPos = D3DXVECTOR3(-350.0f + InitPos.x, pos.y + InitPos.y, -350.0f + InitPos.z);

		WayPoint[nCntWayPoint].WayPointPos = SetPos;
		WayPoint[nCntWayPoint].pWayPoint = CSceneBillBoard::Create(SetPos, 0, 0, "NUMBER");
		WayPoint[nCntWayPoint].pWayPoint->Init(SetPos);
		WayPoint[nCntWayPoint].pWayPoint->SetBillboard(SetPos, m_size.x, m_size.y);
		WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
		//X方向にずらす
		InitPos.x += 80;

		if (nCntWayPoint % SPLIT_WAYPOINT == SPLIT_WAYPOINT -1)
		{
			//X方向を戻す
			InitPos.x = 0;
			//Z方向にずらす
			InitPos.z += 80;
		}
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWaypoint::Uninit(void)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].pWayPoint != NULL)
		{
			WayPoint[nCntWayPoint].pWayPoint->Uninit();
			WayPoint[nCntWayPoint].pWayPoint = NULL;
		}
	}
	CSceneBillBoard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWaypoint::Update(void)
{
	int nNowNumber = 0;		//今いるマスの番号
	int nAdjacent = 0;		//隣接しているマスは何マス分離れているか
	bool bLand = false;		//誰かがマスに乗っている
	int nNum2Cnt = 0;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
		WayPoint[nCntWayPoint].nWayPointNum = 9;
	}

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].bInPlayer == true)
		{	//今いるマスの番号を代入
			nNowNumber = nCntWayPoint;
			WayPoint[nCntWayPoint].nWayPointNum = 0;
			WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
			bLand = true;
		}
	}

	//今いるマスから何マス分離れているか
	for (int nCntSplit = 1; nCntSplit < SPLIT_WAYPOINT + 3; nCntSplit++)
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			//周囲8マス
#if 1
			if (nNowNumber - 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
				|| nNowNumber + 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT + 1 == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT) % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT - 1 == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT + 1 == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT) % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT - 1 == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true)
			{//隣接するマス
				WayPoint[nCntWayPoint].nWayPointNum = 1;
				WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
			}

			if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true)
			{//隣接マスから離れている

				if ((nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
				{//右横　余りが出ないマスは折り返しているマスなので見ないようにする
					WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if ((nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
				{//左横 余りが分割数-1のマスは折り返しているマスなので見ないようにする
					WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if ((nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//前 分割数分引いたときに0以下の時は入らない
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if ((nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//後ろ 最大数以上の時は入らない
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}

				if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT - 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
				{	//右前	例(5*5で中央にいる場合)　12 - 8 == 分割数 + 1 && 0以上 && 折り返していない
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT + 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT -1)
				{	//左前	例(5*5で中央にいる場合)　12 - 6 == 分割数 - 1 && 0以上 && 折り返していない
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT + 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
				{	//右後	例(5*5で中央にいる場合)　18 - 12 == 分割数 + 1 && 25以内 && 折り返していない
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT - 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1)
				{	//左後	例(5*5で中央にいる場合)　16 - 12 == 分割数 - 1 && 25以内 && 折り返していない
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}

			}


#endif
			//周囲４マス
#if 0
			//どこかのマスに乗ったとき
			if (nNowNumber - 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
				|| nNowNumber + 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT && bLand == true)
			{//隣接するマス
				WayPoint[nCntWayPoint].nWayPointNum = 1;
				WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
			}

			if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true)
			{//隣接マスから離れている
			 //条件文の決め方
			 //自分から１マス離れたマスの右左前後を見て離れているマスを見つける
				if (nCntWayPoint + 1 && (nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
				{//右横　余りが出ないマスは折り返しているマスなので見ないようにする
					WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - 1 && (nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
				{//左横 余りが分割数-1のマスは折り返しているマスなので見ないようにする
					WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - SPLIT_WAYPOINT && (nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//前 分割数分引いたときに0以下の時は入らない
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint + SPLIT_WAYPOINT && (nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//後ろ 最大数以上の時は入らない
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
			}
#endif
		}
	}

	//ブロックに当たっている
	CollisionObj();

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_B))
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
			WayPoint[nCntWayPoint].nWayPointNum = 9;
		}
	}

#ifdef _DEBUG

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].nWayPointNum == 1)
		{
		//	CDebugProc::Print("cfcfcf", "2のマスの位置 : X ", WayPoint[nCntWayPoint].WayPointPos.x, " Y ", WayPoint[nCntWayPoint].WayPointPos.y, " Z ", WayPoint[nCntWayPoint].WayPointPos.z);
			nNum2Cnt++;
		}
	}

///	CDebugProc::Print("cn", "２のマスの数 :", nNum2Cnt);
#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void CWaypoint::Draw(void)
{
	//CSceneBillBoard::Draw();
}

//=============================================================================
// 移動処理
//=============================================================================
D3DXVECTOR3 CWaypoint::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == false)
	{
		if (pos.y > 30.0f)
		{	// 位置が指定した場所より大きい場合
			m_bMoveFlag = true;
		}
	}
	else if (m_bMoveFlag == true)
	{
		if (pos.y < 0.0f + m_size.y)
		{	// 位置が指定した場所より小さい場合
			m_bMoveFlag = false;
		}
	}

	return pos;
}

//=============================================================================
// 拡大縮小の処理
//=============================================================================
void CWaypoint::ScaleSize(void)
{
	if (m_bScaleFlag == false)
	{	// 拡大する
		m_size.x += 0.2f;
		m_size.y += 0.2f;
		if (m_size.x > 15.0f && m_size.y > 15.0f)
		{	// 縮小するフラグへ
			m_bScaleFlag = true;
		}
	}
	else if (m_bScaleFlag == true)
	{	// 縮小する
		m_size.x -= 0.2f;
		m_size.y -= 0.2f;
		if (m_size.x < m_sizeOld.x && m_size.y < m_sizeOld.y)
		{	// 拡大するフラグへ
			m_bScaleFlag = false;
		}
	}
}

//=============================================================================
// 範囲内の処理
//=============================================================================
void CWaypoint::InRange(D3DXVECTOR3 pos)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (pos.z <= WayPoint[nCntWayPoint].WayPointPos.z + WAYPOINT_HIT && pos.z >= WayPoint[nCntWayPoint].WayPointPos.z - WAYPOINT_HIT)
		{// zの範囲の中
			if (pos.x <= WayPoint[nCntWayPoint].WayPointPos.x + WAYPOINT_HIT && pos.x >= WayPoint[nCntWayPoint].WayPointPos.x - WAYPOINT_HIT)
			{// xの範囲の中
				//プレイヤーが乗っている
				WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
				WayPoint[nCntWayPoint].bInPlayer = true;
				WayPoint[nCntWayPoint].nWayPointNum = 0;
			}
			else
			{
				WayPoint[nCntWayPoint].bInPlayer = false;
			}
		}
		else
		{
			WayPoint[nCntWayPoint].bInPlayer = false;
		}
	}
}

//=============================================================================
// 移動可能な位置を返す処理
//=============================================================================
D3DXVECTOR3 &CWaypoint::ReturnPointMove(void)
{
	//int nCnt = 0;
	nNumWayPoint = 0;

	for (int nCntWP = 0; nCntWP < 8; nCntWP++)
	{
		//m_pWayPointPos[nCntWP] = NULL;
		m_pWayPointPos[nCntWP] = D3DXVECTOR3(0, 0, 0);
	}

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].nWayPointNum == 1)
		{
			m_pWayPointPos[nNumWayPoint] = WayPoint[nCntWayPoint].WayPointPos;
			nNumWayPoint++;
		}
	}
	return m_pWayPointPos[0];
}

//=============================================================================
// 移動可能な数を返す処理
//=============================================================================
int CWaypoint::CntWayPoint(void)
{
	return nNumWayPoint;
}

//=============================================================================
// オブジェクト判定処理
//=============================================================================
void CWaypoint::CollisionObj(void)
{
	CScene *pScene = NULL;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		// 先頭のオブジェクトを取得
		pScene = CScene::GetTop(SCENEX_PRIORITY);

		while (pScene != NULL)
		{// 優先順位が3のオブジェクトを1つ1つ確かめる
		 // 処理の最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
			{// 死亡フラグが立っていないもの
			 // オブジェクトの種類を確かめる
				CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneXへキャスト(型の変更)
				if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
				{
					bool  bLand = pSceneX->CollisionIN(WayPoint[nCntWayPoint].WayPointPos, D3DXVECTOR3(40, 0, 40));
					CObject *pSceneObj = ((CObject*)pSceneX);

					//オブジェクトに当たった
					if (bLand == true)
					{
						WayPoint[nCntWayPoint].bBlock = true;
						WayPoint[nCntWayPoint].nWayPointNum = 9;
					}
				}
			}
			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}
}
