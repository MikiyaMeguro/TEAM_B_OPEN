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
CWaypoint::CWaypoint() : CScene(2)
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nNumWayPoint = 0;
	m_nNumNowPoint = 0;
	m_FromHit = FROMHIT_NONE;
	m_bStageStart = false;
	m_bStageSetEnd = false;
	for (int nCntWP = 0; nCntWP < 8; nCntWP++)
	{
		m_pWayPointPos[nCntWP] = D3DXVECTOR3(0, 0, 0);
		m_nTargetNum[nCntWP] = 0;
	}
	m_nFlameCnt = 0;
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
			pWaypoint->Init(/*pos*/);
			/*pWaypoint->BindTexture(Tag);*/
		}
	}
	return pWaypoint;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWaypoint::Init(/*D3DXVECTOR3 pos*/)
{
	//CSceneBillBoard::Init(pos);
	D3DXVECTOR3 InitPos(0, 0, 0);
	D3DXVECTOR3 SetPos(0, 0, 0);
	m_PlayerPos = D3DXVECTOR3(0, 0, 0);
	//初期化
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		WayPoint[nCntWayPoint].pWayPoint = NULL;
		WayPoint[nCntWayPoint].WayPointPos = D3DXVECTOR3(0, 0, 0);
		WayPoint[nCntWayPoint].nWayPointNum = 9;
		WayPoint[nCntWayPoint].bInPlayer = false;
		WayPoint[nCntWayPoint].bBlock = false;
		WayPoint[nCntWayPoint].bAdjacent = false;
	}
	//生成
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		SetPos = D3DXVECTOR3(-390.0f + InitPos.x, InitPos.y + InitPos.y, -390.0f + InitPos.z);

		WayPoint[nCntWayPoint].WayPointPos = SetPos;
		//WayPoint[nCntWayPoint].pWayPoint = CSceneBillBoard::Create(SetPos, 0, 0, "NUMBER");
		//WayPoint[nCntWayPoint].pWayPoint->Init(SetPos);
		//WayPoint[nCntWayPoint].pWayPoint->SetBillboard(SetPos, m_size.x, m_size.y);
		//WayPoint[nCntWayPoint].pWayPoint->SetTexture(0, 10, 1, 1);
		//X方向にずらす
		InitPos.x += WAYPOINT_POS_WIDE;

		if (nCntWayPoint % SPLIT_WAYPOINT == SPLIT_WAYPOINT -1)
		{
			//X方向を戻す
			InitPos.x = 0;
			//Z方向にずらす
			InitPos.z += WAYPOINT_POS_WIDE;
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

	/*CSceneBillBoard::Uninit();*/
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWaypoint::Update(void)
{
	int nNowNumber = 0;		//今いるマスの番号
	int nAdjacent = 0;		//隣接しているマスは何マス分離れているか
	bool bLand = false;		//誰かがマスに乗っている

	if (CGame::GetbStageSet() == false)
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			//WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
			WayPoint[nCntWayPoint].nWayPointNum = 9;
		}

		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			if (WayPoint[nCntWayPoint].bInPlayer == true)
			{	//今いるマスの番号を代入
				nNowNumber = nCntWayPoint;
				m_nNumNowPoint = nCntWayPoint;
				WayPoint[nCntWayPoint].nWayPointNum = 0;
				WayPoint[nCntWayPoint].bAdjacent = false;
				if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint != NULL)
				{
					//	WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
				}
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
					if (WayPoint[nCntWayPoint].pWayPoint != NULL)
					{
						//	WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
					}
					WayPoint[nCntWayPoint].bAdjacent = true;
				}

				if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true && WayPoint[nCntWayPoint].bAdjacent != true)
				{//隣接マスから離れている

					if ((nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
					{//右横　余りが出ないマスは折り返しているマスなので見ないようにする
						WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + 1].bAdjacent = false;
					}
					if ((nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
					{//左横 余りが分割数-1のマスは折り返しているマスなので見ないようにする
						WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - 1].bAdjacent = false;
					}
					if ((nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
					{//前 分割数分引いたときに0以下の時は入らない
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT].bAdjacent = false;
					}
					if ((nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
					{//後ろ 最大数以上の時は入らない
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT].bAdjacent = false;
					}

					if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT - 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
					{	//右前	例(5*5で中央にいる場合)　12 - 8 == 分割数 + 1 && 0以上 && 折り返していない
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].bAdjacent = false;
					}
					if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT + 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1)
					{	//左前	例(5*5で中央にいる場合)　12 - 6 == 分割数 - 1 && 0以上 && 折り返していない
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].bAdjacent = false;
					}
					if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT + 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
					{	//右後	例(5*5で中央にいる場合)　18 - 12 == 分割数 + 1 && 25以内 && 折り返していない
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].bAdjacent = false;
					}
					if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT - 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1)
					{	//左後	例(5*5で中央にいる場合)　16 - 12 == 分割数 - 1 && 25以内 && 折り返していない
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
						if (WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].pWayPoint != NULL)
						{
							//	WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
						}
						WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].bAdjacent = false;
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

		if (CGame::GetbStageSet() == true && m_bStageSetEnd == false)
		{	//ステージ切り替わり時に当たり判定更新
			m_bStageSetEnd = true;
		}
		else if (CGame::GetbStageSet() == false && m_bStageSetEnd == true)
		{
			CollisionObj();
			m_bStageSetEnd = false;
		}
		else
		{
			if (m_bStageStart == false)
			{	//開始時に当たり判定更新 最初のみ
				CollisionObj();
				m_bStageStart = true;
			}
		}
	}


	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_B))
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			//WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
			WayPoint[nCntWayPoint].nWayPointNum = 9;
		}
	}

#ifdef _DEBUG
	int nNum2Cnt = 0;

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
	//プレイヤーの位置記憶
	m_PlayerPos = pos;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (pos.z <= WayPoint[nCntWayPoint].WayPointPos.z + WAYPOINT_HIT && pos.z >= WayPoint[nCntWayPoint].WayPointPos.z - WAYPOINT_HIT)
		{// zの範囲の中
			if (pos.x <= WayPoint[nCntWayPoint].WayPointPos.x + WAYPOINT_HIT && pos.x >= WayPoint[nCntWayPoint].WayPointPos.x - WAYPOINT_HIT)
			{// xの範囲の中
				//プレイヤーが乗っている
				//WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
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
	m_nNumWayPoint = 0;

	for (int nCntWP = 0; nCntWP < 8; nCntWP++)
	{
		m_pWayPointPos[nCntWP] = D3DXVECTOR3(0, 0, 0);
		m_nTargetNum[nCntWP] = 0;
	}

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].bAdjacent == true && WayPoint[nCntWayPoint].bBlock == false)
		{	//周囲のマスの位置情報と番号を記憶
			m_pWayPointPos[m_nNumWayPoint] = WayPoint[nCntWayPoint].WayPointPos;
			m_nTargetNum[m_nNumWayPoint] = nCntWayPoint;
			m_nNumWayPoint++;

			if (m_nNumWayPoint == 8)
			{
				break;
			}
		}
	}
	return m_pWayPointPos[0];
}

//=============================================================================
// 移動可能な数を返す処理
//=============================================================================
int CWaypoint::CntWayPoint(void)
{
	return m_nNumWayPoint;
}

//=============================================================================
// オブジェクト判定処理
//=============================================================================
void CWaypoint::CollisionObj(void)
{
	int nCntHitObj = 0; //当たった数をカウント

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
					if (pSceneX->GetCollsionType() != CSceneX::COLLSIONTYPE_FLOORCOLLSION)
					{
						bool  bLand = pSceneX->CollisionIN(WayPoint[nCntWayPoint].WayPointPos, D3DXVECTOR3(WAYPOINT_RADIUS, 0, WAYPOINT_RADIUS));
						//オブジェクトに当たった
						if (bLand == true)
						{
							WayPoint[nCntWayPoint].bBlock = true;
							WayPoint[nCntWayPoint].nWayPointNum = 9;
							//break;
							//WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
						}
					}
				}
			}
			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}


	//オブジェクトと当たっていないウェイポイントを更新
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].bBlock == true)
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
						if (pSceneX->GetCollsionType() != CSceneX::COLLSIONTYPE_FLOORCOLLSION)
						{
							bool  bLand = pSceneX->CollisionIN(WayPoint[nCntWayPoint].WayPointPos, D3DXVECTOR3(WAYPOINT_RADIUS, 0, WAYPOINT_RADIUS));
							CObject *pSceneObj = ((CObject*)pSceneX);
							if (bLand == true)
							{//当たっていない
								nCntHitObj++;
							}
						}
					}
				}
				// 次のシーンに進める
				pScene = pSceneNext;
			}

			if (nCntHitObj == 0)
			{//一度もオブジェクトに当たっていない
				WayPoint[nCntWayPoint].bBlock = false;
			}
		}
	}
}


//=============================================================================
// オブジェクト判定処理
//=============================================================================
CWaypoint::WAYPOINT &CWaypoint::GetWayPoint(void)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		//オブジェクトと当たっている
		if (WayPoint[nCntWayPoint].bBlock == true)
		{

		}
	}

	return WayPoint[0];
}

//=============================================================================
// 行こうとしているマス番号を取得
//=============================================================================
int CWaypoint::GetNumTargetPoint(int nWayPoint)
{
	if (nWayPoint > MAX_WAYPOINT)
	{
		nWayPoint = 0;
	}
	if (nWayPoint < 0)
	{
		nWayPoint = 0;
	}

	return m_nTargetNum[nWayPoint];
}

//=============================================================================
// 隣のマスを目標にする
//=============================================================================
D3DXVECTOR3 CWaypoint::GetNextWayPoint(int nWayPoint)
{
	int nReturnNum = nWayPoint;
	int nRightNum = nWayPoint;
	int nLeftNum = nWayPoint;

	int nParallel = 0;	//平行移動
	int nRouteCnt[2] = { 0,0 };	//何マスで移動できるか
	bool bEndRoute = false;
	bool bRouteSearchEnd[2] = { false ,false };

	m_FromHit = FROMHIT_NONE;

	//行こうとしているマスがブロックだった
	if (WayPoint[nReturnNum].bBlock == true)
	{
		if (m_nNumNowPoint - nWayPoint == SPLIT_WAYPOINT)
		{//手前に移動しようとしている
			nParallel += SPLIT_WAYPOINT;
			m_FromHit = FROMHIT_BACK;
		}
		else if (m_nNumNowPoint - nWayPoint == -SPLIT_WAYPOINT)
		{//奥に移動しようとしている
			nParallel -= SPLIT_WAYPOINT;
			m_FromHit = FROMHIT_FRONT;
		}
		else if (m_nNumNowPoint - nWayPoint == -1)
		{//右に移動しようとしている
			nParallel -= 1;
			m_FromHit = FROMHIT_LEFT;
		}
		else if (m_nNumNowPoint - nWayPoint == 1)
		{//左に移動しようとしている
			nParallel += 1;
			m_FromHit = FROMHIT_RIGHT;
		}
		else if (m_nNumNowPoint - nWayPoint == 0)
		{//今いるマスがブロック
			nParallel += 0;
			m_FromHit = FROMHIT_IN;
		}
	}

	while (bEndRoute == false)
	{
		if (nRightNum >= MAX_WAYPOINT || nLeftNum >= MAX_WAYPOINT
			|| nRightNum < 0 || nLeftNum < 0)
		{
			bEndRoute = true;
			nRightNum = MAX_WAYPOINT / 2;
			nLeftNum = MAX_WAYPOINT / 2;
		}

		switch (m_FromHit)
		{
		case FROMHIT_FRONT:
			//右回りルート
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//目標のマスがブロック 右横　もう一度右横のブロックを見る
				nRightNum = nRightNum + 1;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}

			//左回りルート
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//目標のマスがブロック 左横　もう一度左横のブロックを見る
				nLeftNum = nLeftNum - 1;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//目標のマスがブロックではない 左横　ブロックではないマスの番号を記憶
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//右回り左回りのルートを調べ終わった
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}

			break;
		case FROMHIT_BACK:

			//右回りルート
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//目標のマスがブロック 右横　もう一度右横のブロックを見る
				nRightNum = nRightNum - 1;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//目標のマスがブロック 左横　もう一度左横のブロックを見る
				nLeftNum = nLeftNum + 1;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//目標のマスがブロックではない 左横　ブロックではないマスの番号を記憶
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//右回り左回りのルートを調べ終わった
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}

			break;
		case FROMHIT_RIGHT:
			//右回りルート
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//目標のマスがブロック 右横　もう一度右横のブロックを見る
				nRightNum = nRightNum + SPLIT_WAYPOINT;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}
			//左回りルート
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//目標のマスがブロック 右横　もう一度右横のブロックを見る
				nLeftNum = nLeftNum - SPLIT_WAYPOINT;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//右回り左回りのルートを調べ終わった
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}
			break;
		case FROMHIT_LEFT:
			//右回りルート
			if (WayPoint[nRightNum].bBlock == true && bRouteSearchEnd[0] == false)
			{//目標のマスがブロック 右横　もう一度右横のブロックを見る
				nRightNum = nRightNum - SPLIT_WAYPOINT;
				nRouteCnt[0]++;
			}
			if (WayPoint[nRightNum].bBlock == false && bRouteSearchEnd[0] == false)
			{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
				nRightNum = nRightNum + nParallel;
				bRouteSearchEnd[0] = true;
			}
			//左回りルート
			if (WayPoint[nLeftNum].bBlock == true && bRouteSearchEnd[1] == false)
			{//目標のマスがブロック 右横　もう一度右横のブロックを見る
				nLeftNum = nLeftNum + SPLIT_WAYPOINT;
				nRouteCnt[1]++;
			}
			if (WayPoint[nLeftNum].bBlock == false && bRouteSearchEnd[1] == false)
			{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
				nLeftNum = nLeftNum + nParallel;
				bRouteSearchEnd[1] = true;
			}
			//右回り左回りのルートを調べ終わった
			if (bRouteSearchEnd[0] == true && bRouteSearchEnd[1] == true)
			{
				bEndRoute = true;
			}

			break;
		case FROMHIT_IN:

			if (m_PlayerPos.x > WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z > WayPoint[nReturnNum].WayPointPos.z)
			{//右前
				if (WayPoint[nReturnNum + 1].bBlock == false)
				{//右
					nReturnNum = nReturnNum + 1;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT].bBlock == false)
				{//前
					nReturnNum = nReturnNum - SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT + 1].bBlock == false)
				{//斜め右前
					nReturnNum = nReturnNum - SPLIT_WAYPOINT + 1;
				}
			}
			else if (m_PlayerPos.x < WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z > WayPoint[nReturnNum].WayPointPos.z)
			{//左前
				if (WayPoint[nReturnNum - 1].bBlock == false)
				{//左
					nReturnNum = nReturnNum - 1;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT].bBlock == false)
				{//前
					nReturnNum = nReturnNum - SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum - SPLIT_WAYPOINT - 1].bBlock == false)
				{//斜め左前
					nReturnNum = nReturnNum - SPLIT_WAYPOINT -1;
				}
			}
			else if (m_PlayerPos.x > WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z < WayPoint[nReturnNum].WayPointPos.z)
			{//右後
				if (WayPoint[nReturnNum + 1].bBlock == false)
				{//右
					nReturnNum = nReturnNum + 1;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT].bBlock == false)
				{//後
					nReturnNum = nReturnNum + SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT + 1].bBlock == false)
				{//斜め右後
					nReturnNum = nReturnNum + SPLIT_WAYPOINT + 1;
				}
			}
			else if (m_PlayerPos.x < WayPoint[nReturnNum].WayPointPos.x && m_PlayerPos.z < WayPoint[nReturnNum].WayPointPos.z)
			{//左後
				if (WayPoint[nReturnNum - 1].bBlock == false)
				{//左
					nReturnNum = nReturnNum - 1;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT].bBlock == false)
				{//後
					nReturnNum = nReturnNum + SPLIT_WAYPOINT;
				}
				else if (WayPoint[nReturnNum + SPLIT_WAYPOINT - 1].bBlock == false)
				{//斜め左後
					nReturnNum = nReturnNum + SPLIT_WAYPOINT - 1;
				}
			}
			bEndRoute = true;
			break;
		default:
			bEndRoute = true;
			break;
		}
	}

	//最短ルートのマス
	if (nRouteCnt[0] <= nRouteCnt[1] && m_FromHit != FROMHIT_IN)
	{
		nReturnNum = nRightNum;
	}
	else if (nRouteCnt[0] > nRouteCnt[1] && m_FromHit != FROMHIT_IN)
	{
		nReturnNum = nLeftNum;
	}
	else if (m_FromHit == FROMHIT_IN)
	{
		nReturnNum = nReturnNum;
	}
	else
	{
		nReturnNum = nRightNum;
	}
	return WayPoint[nReturnNum].WayPointPos;
}



#if 0
if (WayPoint[nReturnNum].bBlock == true)
{//目標のマスがブロック 右横　もう一度右横のブロックを見る
	nReturnNum = nReturnNum + 1;
	nRouteCnt++;
}
if (WayPoint[nReturnNum].bBlock == false)
{//目標のマスがブロックではない 右横　ブロックではないマスの番号を記憶
	nReturnNum = nReturnNum - nParallel;
	bEndRoute = true;
	break;
}
#endif