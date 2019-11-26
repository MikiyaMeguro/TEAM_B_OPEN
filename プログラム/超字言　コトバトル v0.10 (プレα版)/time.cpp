//=============================================================================
//
// タイマー処理 [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"
#include "charactor.h"
#include "result.h"
#include "point.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// Xの中心座標
#define TIMER_SPACE			(30.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_POSITION_Y	(70.0f)							// タイマーのY座標(ゲーム時間)
#define GAME_TIME			(130)							// ゲーム開始時の時間
#define GAME_TIME_MAX		(9)							// ゲームの時間最大数
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 70.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define TIME_POS_2P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 440.0f, 0.0f))	// 制限時間の位置(2Pだけの場合)
#define TIME_POS_3P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 140.0f, 440.0f, 0.0f))	// 制限時間の位置(3Pだけの場合)
#define TIME_POS_4P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 380.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define WAIT_TIME_END		(180)							// 待ち時間

#define COUNTDOWN_SCALE		(4.0f)							// 待ち時間

//=============================================================================
//	静的メンバ変数
//=============================================================================
int						CTime::m_nTime = 0;
int						CTime::m_nTimeNumCount = 0;
int						CTime::m_nTimeCount = 0;
bool					CTime::m_bCountFlag = true;			//時間をカウントするか
int						CTime::m_nTimeOld = 0;
int						CTime::m_nStageChange = 1;
int						CTime::m_nTimeOne = 3;
//=============================================================================
// 生成処理
//=============================================================================
CTime *CTime::Create(int nNumPlayer)
{
	CTime *pTime = NULL;

	//NULLチェック
	if (pTime == NULL)
	{//動的確保
		pTime = new CTime;

		//NULLチェック
		if (pTime != NULL)
		{
			//位置の設定
			if (nNumPlayer == 1) { pTime->m_pos = TIME_POS_1P; }
			if (nNumPlayer == 2 && m_nTimeNumCount == 0) { pTime->m_pos = TIME_POS_1P; }
			else if (nNumPlayer == 2 && m_nTimeNumCount == 1) { pTime->m_pos = TIME_POS_2P; }
			if (nNumPlayer == 3) { pTime->m_pos = TIME_POS_3P; }
			if (nNumPlayer == 4) { pTime->m_pos = TIME_POS_4P; }
			pTime->m_nNumPlayer = nNumPlayer;

			//初期化処理
			pTime->Init();
		}
	}

	return pTime;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CTime::CTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
	m_nTimeNum = 3;
	m_nWaitTime = 0;
	m_pColon = NULL;
	m_bStart = false;
	m_bStageCreate = false;
	m_nStageChange = 1;
	m_StageCounter = 0;
	//値の初期化
	m_bCntDown = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nColorFlash = 0;
	m_nType = 0;
	m_fWidth = 100;
	m_fHeight = 100;
	m_bEndCntDown = false;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = NULL;			// プレイヤーを取得
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CTime::~CTime() {}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTime::Init(void)
{
	int nTexData = 0;
	m_nTime = 0;
	m_nTimeOld = GAME_TIME - 30;
	m_nTimeNum = PowerCalculation(m_nTime, 0);
	m_nTimeOne = 3;
	m_StageCounter = 0;
	// 後ろの背景
	if (m_nNumPlayer == 1 || m_nNumPlayer == 2 && m_nTimeNumCount == 0)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_nNumPlayer == 2 && m_nTimeNumCount == 1)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 420.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_nNumPlayer == 3)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 420.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_nNumPlayer == 4)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 370.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// タイマー初期設定
			m_apNumber[nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// ３桁まで
				m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntTime), m_pos.y, m_pos.z), 0);
			}
			else if (nCntTime == 2)
			{	// 3桁目
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(((m_pos.x - 20.0f) - TIMER_SPACE * nCntTime), m_pos.y, m_pos.z), 0);
			}
		}
		// 数字のテクスチャ設定
		TexTime(nTexData, m_nTimeOne);
	}

	//カウントダウン生成
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (m_nNumPlayer == 1)
	{
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_pos.z), "COUNTDOWN2");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
	}

	if (m_nNumPlayer == 1 || m_nNumPlayer == 2 && m_nTimeNumCount == 0)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 18.0f, 70.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Timeのロゴ
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 35.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

		if (m_nNumPlayer == 2) { m_nTimeNumCount++; }
	}
	else if (m_nNumPlayer == 2 && m_nTimeNumCount == 1)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 18.0f, 440.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 180.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 540.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);

		// Timeのロゴ
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 405.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		m_bStart = true;
	}
	else if (m_nNumPlayer == 3)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 82.0f, 440.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 180.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 180.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 540.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);

		// Timeのロゴ
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 405.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	if (m_nNumPlayer == 4)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 18.0f, 380.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 180.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 180.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 540.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(940.0f, 540.0f, m_pos.z), "COUNTDOWN2");
		m_pScene2D[3]->SetWidthHeight(m_fWidth, m_fHeight);

		// Timeのロゴ
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	// プレイヤーを取得
		m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
		m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(true);
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// タイマーの破棄
			if (m_apNumber[nCntTime] != NULL)
			{
				m_apNumber[nCntTime]->Uninit();
				m_apNumber[nCntTime] = NULL;
			}
		}
	}

	if (m_pColon != NULL)
	{
		m_pColon->Uninit();
		m_pColon = NULL;
	}

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}
	m_nTimeNumCount = 0;

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTime::Update(void)
{

	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// デバック用

	if ((GameMode == CManager::MODE_GAME) && m_bEndCntDown == true || (GameMode == CManager::MODE_TUTORIAL) && m_bEndCntDown == true)
	{//制限時間
	 //ゲーム
		if (m_bStart == false)
		{
			if (m_bCountFlag == true)
			{
				m_nTimeCount++;
				TimeManagement();	// 時間の管理
			}
		}

		int nTexData = 0;
		// 数字のテクスチャ設定
		TexTime(nTexData, m_nTimeOne);

		if (m_nTime == 0 && m_nTimeOne == 0 && GameMode == CManager::MODE_GAME)
		{
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{	// プレイヤーを行動できないように
				m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(true);
				m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
				m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);

				if (m_pScene2D[nCntPlayer] != NULL)
				{
					m_pScene2D[nCntPlayer]->BindTexture("GAME_END");
					m_pScene2D[nCntPlayer]->SetCol(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
					m_pScene2D[nCntPlayer]->SetWidthHeight(m_fWidth + 200, m_fHeight);
					m_pScene2D[nCntPlayer]->SetScale(200.0f);
				}
			}

			// ゲーム終了
			m_nWaitTime++;	// 待ち時間の加算
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				for (int nCntPlayer = 0; nCntPlayer < 4; nCntPlayer++)
				{
					CResult::SetRanking(nCntPlayer, CGame::GetPlayerType(nCntPlayer), CGame::GetPoint(nCntPlayer)->GetPoint());
				}

				CFade::SetFade(CManager::MODE_RESULT, CFade::FADE_OUT);
			}
		}
	}

	//カウントダウン
	if (m_bEndCntDown == false)
	{
		if (m_bCntDown == true && m_nType < 4)
		{
			for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
			{
				if (m_pScene2D[nCnt] != NULL)
				{
					switch (m_nType)
					{
					case 0:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN2");
						break;
					case 1:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN1");
						break;
					case 2:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN0");
						break;
					case 3:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN3");
						m_pScene2D[nCnt]->SetWidthHeight(m_fWidth + 100, m_fHeight + 100);

						break;
					default:
						break;
					}
				}
			}
			m_bCntDown = false;
		}

		//大きさ変化
		m_fScale += COUNTDOWN_SCALE;
		//透明度上げ
		if (m_fScale > 200 && m_fScale <= 250)
		{
			//カウンター加算
			if (m_bCntDown == false)
			{
				m_Col.a -= 0.1f;
			}
		}
		//大きさ最大
		if (m_fScale > COUNTDOWN_SCALE * 60)
		{
			m_fScale = COUNTDOWN_SCALE * 60;
			if (m_nType < 3)
			{
				m_bCntDown = true;
				m_nType += 1;
				m_fScale = 0;
				m_Col.a = 1.0f;
			}
			else if (m_nType == 3)
			{
				m_bEndCntDown = true;
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{	// プレイヤーを取得
					m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
					m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(false);
				}
			}
		}
		//色・大きさ更新
		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			if (m_pScene2D[nCnt] != NULL)
			{
				m_pScene2D[nCnt]->SetCol(m_Col);
				m_pScene2D[nCnt]->SetScale(m_fScale);
			}
		}
	}

	//ステージ生成完了タイマー
	if (CGame::GetbStageSet() == true)
	{
		m_StageCounter++;
		if (m_StageCounter > 120)
		{
			m_StageCounter = 0;
			CGame::bStageSet(false);
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}

	if (m_pColon != NULL)
	{
		m_pColon->Draw();
	}
}

//=============================================================================
// タイマーのTexture管理
//=============================================================================
void CTime::TexTime(int nTexData, int nTimeOne)
{
	nTexData = m_nTime;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// テクスチャに反映

		if (m_apNumber[nCntTime] != NULL)
		{
			if (nCntTime < 2)
			{
				m_apNumber[nCntTime]->SetNumber(nTexData);
				nTexData /= 10;
			}
			else if (nCntTime == 2)
			{
				m_apNumber[nCntTime]->SetNumber(nTimeOne);
				nTexData /= 10;
			}
			// 色の設定
			if (m_nTime <= 10 && m_nTimeOne == 0)
			{ // 10秒以下 色を赤に
				m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)); }
			}
			else
			{
				m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
			}
		}
	}
}
//=============================================================================
// タイム加算処理
//=============================================================================
void CTime::AddTime(int nTime)
{
	if (m_nTime > 0)
	{
		m_nTimeOne += nTime;
	}

	if (GAME_TIME_MAX < m_nTimeOne) { m_nTimeOne = GAME_TIME_MAX; }
}
//=============================================================================
// べき乗の計算
//=============================================================================
int CTime::PowerCalculation(int nData, int nOperation)
{
	int nNum = 1;
	int nPower = (int)std::pow(POWER_X, nNum);
	int nDataNum = nData;
	while ((nDataNum / nPower) != 0)
	{
		nNum++;
		nPower = (int)std::pow(POWER_X, nNum);		// べき乗する(二乗や三乗など)
		if (nOperation == 0)
		{	// 制限時間
			if (nNum >= TIME_MAX) { nNum = TIME_MAX; }
		}
	}
	return nNum;
}

//=============================================================================
// 時間の管理
//=============================================================================
void CTime::TimeManagement(void)
{
	if (m_nTime == 0 && m_nTimeOne == 0) {m_nTime = 0; return; }

	if ((m_nStageChange % 60) == 0 && m_bStageCreate == false)
	{	// 30秒ごとにステージが変わる
		m_bStageCreate = true;
		CGame::bStageSet(true);
		int nStageNum = (m_nStageChange / 60);
		CManager::GetGame()->SetStage(CGame::GetNumStage(),nStageNum);
	}

	if (m_nTimeCount % 60 == 0)
	{// 1秒ごとに減算(制限時間)
		m_nTime--;
		m_nStageChange++;
		m_bStageCreate = false;

		if (m_nTime < 0) { m_nTime = 59; m_nTimeOne -= 1; }
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// デバック用
//=============================================================================
void CTime::DebugKey(void)
{
	// デバック用
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD0))
	{	// 制限時間加算
		AddTime(1);
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// リザルト画面へ
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}