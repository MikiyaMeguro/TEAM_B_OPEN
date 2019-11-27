//=============================================================================
//
// リザルト処理 [result.cpp]
// Author : 目黒未来也
//
//=============================================================================
#include "result.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "time.h"
#include "camera.h"
#include "SelectMenu.h"
#include "CameraManager.h"
#include "camera.h"
#include "meshField.h"
#include "sceneX.h"
#include "number.h"
//============================================================================
//	マクロ定義
//============================================================================
#define POS_1ST (D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POS_2ND (D3DXVECTOR3(50.0f,20.0f,0.0f))
#define POS_3RD (D3DXVECTOR3(-10.0f,20.0f,0.0f))
#define POS_4TH (D3DXVECTOR3(-40.0f,0.0f,0.0f))

#define NUMBERPOS_1ST (D3DXVECTOR3(150.0f,100.0f,0.0f))
#define NUMBERPOS_2ND (D3DXVECTOR3(150.0f,200.0f,0.0f))
#define NUMBERPOS_3RD (D3DXVECTOR3(150.0f,300.0f,0.0f))
#define NUMBERPOS_4TH (D3DXVECTOR3(150.0f,400.0f,0.0f))

#define PODIUMPOS_1ST (D3DXVECTOR3(20.0f, 0.0f, 0.0f))
#define PODIUMPOS_2ND (D3DXVECTOR3(50.0f, 0.0f, 0.0f))
#define PODIUMPOS_3RD (D3DXVECTOR3(-10.0f, 0.0f, 0.0f))
#define PODIUMPOS_4TH (D3DXVECTOR3(40.0f,0.0f,0.0f))


#define TIMER_SPACE			(40.0f)							// 数字と数字の間のサイズ(ゲーム時間)

//============================================================================
//静的メンバ変数宣言
//============================================================================
CPlayer *CResult::m_pPlayer[MAX_PLAYER] = {};
CResult::CharaSet CResult::m_ResultChara[MAX_PLAYER] = {};
CMeshField *CResult::m_pMeshField = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CResult::CResult()
{
	m_pSeletMenu = NULL;
	m_bMenu = false;
	m_bMenuCreate = false;
}

//=============================================================================
//デストラクタ
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CResult::Init(void)
{
	int nCntWinScore = 0;				//勝利カウント
	int nCntRankNum[4] = { 0,0,0,0 };	//順位ごとに何人いるか

	float fPosX = 20;	//表彰台初期位置
	float fNext = 30;	//表彰台の間の幅

#if 1
	m_ResultChara[0].nPoint = 0;
	m_ResultChara[1].nPoint = 10;
	m_ResultChara[2].nPoint = 20;
	m_ResultChara[3].nPoint = 0;

#endif
	//順位決め
	//ソート処理 大きい順
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (nCnt != nCntPlayer && m_ResultChara[nCntPlayer].nPoint >= m_ResultChara[nCnt].nPoint)
			{//他と比べて自分が大きい時勝利カウントを増やす
				nCntWinScore++;
			}
		}
		//何回勝ったかで順位決め
		switch (nCntWinScore)
		{
		case 0:
			m_ResultChara[nCntPlayer].nNumRank = 4;
			nCntRankNum[3]++;
			break;
		case 1:
			m_ResultChara[nCntPlayer].nNumRank = 3;
			nCntRankNum[2]++;
			break;
		case 2:
			m_ResultChara[nCntPlayer].nNumRank = 2;
			nCntRankNum[1]++;
			break;
		case 3:
			m_ResultChara[nCntPlayer].nNumRank = 1;
			nCntRankNum[0]++;
			break;
		default:
			break;
		}
		//勝利数を初期化
		nCntWinScore = 0;
	}


#if 1
	//メッシュフィールド生成
	m_pMeshField = NULL;
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			m_pPlayer[nCntPlayer] = CPlayer::Create();
		}
	}

	//表彰台生成
	for (int nCnt = 0; nCnt < nCntRankNum[0]; nCnt++)
	{//順位の数だけ
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM1, 1);
		if(nCnt == 1)
		{	//3位の場所へ変える
			fPosX = 20;
			fNext *= -1;
		}
		//位置をずらす
		fPosX += fNext;
	}

	fPosX = 50;
	for (int nCnt = 0; nCnt < nCntRankNum[1]; nCnt++)
	{//順位の数だけ
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM2, 1);
		if (nCnt == 0)
		{	//3位の場所へ変える
			fPosX = 20;
			fNext *= -1;
		}
		//位置をずらす
		fPosX += fNext;
	}

	fPosX = -10;
	fNext = -30;
	for (int nCnt = 0; nCnt < nCntRankNum[2]; nCnt++)
	{//順位の数だけ
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM3, 1);
		//位置をずらす
		fPosX += fNext;
	}

	D3DXVECTOR3 RankPos;
	int nCntRankPos[4] = { 0,0,0,0 };	//順位ごとに何人いるか

	fPosX = 20;
	fNext = 30;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	//初期位置設定
		switch (m_ResultChara[nCntPlayer].nNumRank)
		{
		case 1:
			if (nCntRankPos[0] == 0)
			{
				fPosX = 20;
			}
			if (nCntRankPos[0] == 1)
			{
				fPosX = 50;
			}
			if (nCntRankPos[0] == 2)
			{
				fPosX = -10;
			}
			if (nCntRankPos[0] == 3)
			{
				fPosX = -40;
			}
			RankPos = D3DXVECTOR3(fPosX, 30.0f, 0.0f);
			nCntRankPos[0]++;
			break;
		case 2:
			if (nCntRankPos[1] == 0)
			{
				fPosX = 50;
			}
			if (nCntRankPos[1] == 1)
			{
				fPosX = -10;
			}
			if (nCntRankPos[1] == 2)
			{
				fPosX = -40;
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[1]++;
			break;
		case 3:
			if (nCntRankPos[2] == 0)
			{
				fPosX = -10;
			}
			if (nCntRankPos[2] == 1)
			{
				fPosX = -40;
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[2]++;
			break;
		case 4:
			RankPos = POS_4TH;
			break;
		}

		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->Set(RankPos, CCharaBase::MOVETYPE_RANKING_CHARA, nCntPlayer, m_ResultChara[nCntPlayer].type);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);
		}
	}


	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	//初期位置設定
		switch (nCntPlayer)
		{
		case 0:
			RankPos = NUMBERPOS_1ST;
			break;
		case 1:
			RankPos = NUMBERPOS_2ND;
			break;
		case 2:
			RankPos = NUMBERPOS_3RD;
			break;
		case 3:
			RankPos = NUMBERPOS_4TH;
			break;
		}

		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			// タイマー初期設定
			m_apNumber[nCntPlayer][nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// ３桁まで
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
				m_apNumber[nCntPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f), D3DXVECTOR2((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y));
				m_apNumber[nCntPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCntTime == 2)
			{	// 3桁目
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
			}
		}
	}

	//数字のテクスチャ設定
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		TexPoint(nCntPlayer, m_ResultChara[nCntPlayer].nPoint);
	}

#endif
	//カメラの設定
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("RESULT_CAMERA",CCamera::TYPE_SPECTOR,D3DXVECTOR3(20.0f, 40.0f, 110.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 135.0f);
	pCameraManager->SetCameraViewPort("RESULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("RESULT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	}

	//メニューを生成
	//m_pSeletMenu = NULL;
	//m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(740, 100.0f, 0), 120, 180, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CResult::Uninit(void)
{
	//メニューの破棄
	if (m_pSeletMenu != NULL)
	{
		m_pSeletMenu->Uninit();
		m_pSeletMenu = NULL;
	}

	//メッシュフィールドの破棄
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	//ナンバーの破棄
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				m_apNumber[nCntPlayer][nCntTime]->Uninit();
				m_apNumber[nCntPlayer][nCntTime] = NULL;
			}
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{	// プレイヤーの破棄
			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}
	//全ての終了処理
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CResult::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	if (pFade->GetFade() == CFade::FADE_NONE)
	{

		//フレームをずらす
		if (m_bMenuCreate == true)
		{
			if (m_bMenu == true)
			{
				m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(530.0f, SCREEN_HEIGHT / 2, 0), 220, 320, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);
				m_pSeletMenu->SetModeSelectBool(true);
				m_bMenu = false;
			}
			// 以降の更新処理を飛ばす
			return;
		}

		//任意のキーENTER
		if (CCommand::GetCommand("DECISION"))
		{
			if (m_bMenuCreate == false)
			{
				if (m_bMenu == false)
				{
					m_bMenu = true;
					m_bMenuCreate = true;
				}
			}
		}
	}
#ifdef _DEBUG
	CDebugProc::Print("c", "リザルト");

#endif
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CResult::Draw(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				m_apNumber[nCntPlayer][nCntTime]->Draw();
			}
		}
	}
}

//=============================================================================
// キャラクター情報を設定
//=============================================================================
void CResult::SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, int nPoint)
{
	m_ResultChara[nNumPlayer].type = type;
	m_ResultChara[nNumPlayer].nPoint = nPoint;
}

//=============================================================================
// テクスチャを設定
//=============================================================================
void CResult::TexPoint(int nPlayer, int nPoint)
{

	for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
	{// テクスチャに反映

		if (m_apNumber[nPlayer][nCntTime] != NULL)
		{
			if (nCntTime < 2)
			{
				m_apNumber[nPlayer][nCntTime]->SetNumber(nPoint);
				nPoint /= 10;
			}
			else if (nCntTime == 2)
			{
				m_apNumber[nPlayer][nCntTime]->SetNumber(nPoint);
				nPoint /= 10;
			}
		}
	}
}
