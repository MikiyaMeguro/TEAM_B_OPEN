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
#include "sceneBillboard.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// Xの中心座標
#define TIMER_SPACE1P2P		(18.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_SPACE3P4P		(22.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_WIDTH1P2P		(40.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_WIDTH3P4P		(30.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_HEIGHT1P2P	(20.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_HEIGHT3P4P	(15.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_POSITION_Y	(40.0f)							// タイマーのY座標(ゲーム時間)
#define GAME_TIME			(130)							// ゲーム開始時の時間
#define GAME_TIME_MAX		(9)								// ゲームの時間最大数
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 70.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define TIME_POS_2P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50.0f, 440.0f, 0.0f))	// 制限時間の位置(2Pだけの場合)
#define TIME_POS_3P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, 440.0f, 0.0f))	// 制限時間の位置(3Pだけの場合)
#define TIME_POS_4P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 160.0f, 380.0f, 0.0f))	// 制限時間の位置(4Pだけの場合)
#define WAIT_TIME_END		(180)							// 待ち時間

#define COUNTDOWN_SCALE		(3.5f)							// 待ち時間
#define DEFAULT_SIZE		(D3DXVECTOR3(10.0f, 15.0f, 0.0f))	// デフォルトサイズ
#define DEFAULT_SIZE1P2P	(D3DXVECTOR3(12.0f, 20.0f, 0.0f))	// デフォルトサイズ
#define DEFAULT_SIZE3P4P	(D3DXVECTOR3(12.0f, 20.0f, 0.0f))	// デフォルトサイズ
#define SCALE_CHANGE_TIME	(10)								// スケール変化の時間
#define SCALE_UI			(100)								// UIの大きさ
#define SCALE_UI_WIDTH		(200)								// UIの大きさ
#define FEVER_COLOR			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
//=============================================================================
//	静的メンバ変数
//=============================================================================
int						CTime::m_nTime = 0;
int						CTime::m_nTimeCount = 0;
bool					CTime::m_bCountFlag = true;			//時間をカウントするか
int						CTime::m_nTimeOld = 0;
int						CTime::m_nStageChange = 1;
int						CTime::m_nTimeOne = 3;
bool					CTime::m_bFever = false;
int						CTime::m_nStageNum = 0;
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
#if 0
			if (nNumPlayer == 1) { pTime->m_pos = TIME_POS_1P; }
			if (nNumPlayer == 2 && m_nTimeNumCount == 0) { pTime->m_pos = TIME_POS_1P; }
			else if (nNumPlayer == 2 && m_nTimeNumCount == 1) { pTime->m_pos = TIME_POS_2P; }
			if (nNumPlayer == 3) { pTime->m_pos = TIME_POS_3P; }
			if (nNumPlayer == 4) { pTime->m_pos = TIME_POS_4P; }
#endif
			pTime->m_pos = D3DXVECTOR3(20.0f, 80.0f, 0.0f);

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
	m_bChangeStage = false;
	m_fWarningCol = 0.0f;
	m_bWarning = false;
	m_bScaleFlag = false;
	m_nCntScale = 0;
	m_nFeverTime = 0;
	m_bFever = 0;
	m_nStageNum = 0;
	m_nCntUIRepeat = 0;
	m_bStopUI = false;
	m_pFeverBillBoard = NULL;
	m_nUIScaleCounter = 0;
	m_fUIScale = 0;
	m_fUIAddScale = 0;

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
	m_fUIAddScale = 1.0f;

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// タイマー初期設定
			m_apNumber[nCntTime] = new CBillNumber;
			float Space = 0.0f;
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				Space = TIMER_SPACE1P2P;
			}
			else
			{
				Space = TIMER_SPACE3P4P;
			}


			if (nCntTime < 2)
			{	// ３桁まで
				m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - Space * nCntTime), m_pos.y, m_pos.z));
				m_apNumber[nCntTime]->SetPos(D3DXVECTOR3((m_pos.x - Space * nCntTime), m_pos.y, m_pos.z));
			}
			else if (nCntTime == 2)
			{	// 3桁目
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(((m_pos.x - 10.0f) - Space * nCntTime), m_pos.y, m_pos.z));
				m_apNumber[nCntTime]->SetPos(D3DXVECTOR3(((m_pos.x - 10.0f) - Space * nCntTime), m_pos.y, m_pos.z));
			}
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE1P2P);
			}
			else
			{
				m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE3P4P);
			}
		}
		// 数字のテクスチャ設定
		TexTime(nTexData, m_nTimeOne);
	}

	// Timeのロゴ
	if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
	{
		m_pLogo = CSceneBillBoard::Create(D3DXVECTOR3(10.0f, 105.0f, 0.0f), TIMER_WIDTH1P2P, TIMER_HEIGHT1P2P, "TIME");
		m_pLogo->SetBillboard(D3DXVECTOR3(10.0f, 115.0f, 0.0f), TIMER_HEIGHT1P2P, TIMER_WIDTH1P2P);
	}
	else
	{
		m_pLogo = CSceneBillBoard::Create(D3DXVECTOR3(-5.0f, 105.0f, 0.0f), TIMER_WIDTH3P4P, TIMER_HEIGHT3P4P, "TIME");
		m_pLogo->SetBillboard(D3DXVECTOR3(-5.0f, 120.0f, 0.0f), TIMER_HEIGHT3P4P, TIMER_WIDTH3P4P);
	}
	m_pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	//ビルボード設定
	if (m_pColon == NULL)
	{
		if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
		{
			m_pColon = CSceneBillBoard::Create(D3DXVECTOR3(-10.0f, 88.0f, 0.0f), 5.0f, 10.0f, "COLON");
		}
		else
		{
			m_pColon = CSceneBillBoard::Create(D3DXVECTOR3(-17.0f, 86.0f, 0.0f), 7.0f, 10.0f, "COLON");
		}
		m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_pFeverBillBoard == NULL)
	{
		m_pFeverBillBoard = CSceneBillBoard::Create(D3DXVECTOR3(0.0f, 500.0f, 0.0f), 40.0f, 40.0f, "FEVERUI2");
		m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
	}

	//カウントダウン生成
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
		m_pFeverUI[nCnt] = NULL;
	}

	if (m_nNumPlayer == 1)
	{
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+50, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		//フィーバーの位置設定
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, SCREEN_HEIGHT / 2 - 100, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
	}
	else if (m_nNumPlayer == 2)
	{
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		//フィーバーの位置設定
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
		m_pFeverUI[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[1]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[1]->SetCol(FEVER_COLOR);

	}
	else if (m_nNumPlayer == 3)
	{
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
		//フィーバーの位置設定
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
		m_pFeverUI[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[1]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[1]->SetCol(FEVER_COLOR);
	}
	if (m_nNumPlayer == 4)
	{
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(940.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[3]->SetWidthHeight(m_fWidth, m_fHeight);
		//フィーバーの位置設定
		m_pFeverUI[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[0]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[0]->SetCol(FEVER_COLOR);
		m_pFeverUI[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, m_pos.z), "FEVERUI2");
		m_pFeverUI[1]->SetWidthHeight(SCALE_UI_WIDTH, SCALE_UI);
		m_pFeverUI[1]->SetCol(FEVER_COLOR);
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	// プレイヤーを取得
		m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(true);
		}
	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTime::Uninit(void)
{
	m_nStageNum = 0;
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

	if (m_pFeverBillBoard != NULL)
	{
		m_pFeverBillBoard->Uninit();
		m_pFeverBillBoard = NULL;
	}

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pFeverUI[nCnt] != NULL)
		{
			m_pFeverUI[nCnt]->Uninit();
			m_pFeverUI[nCnt] = NULL;
		}
	}


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
		if (m_bCountFlag == true)
		{
			m_nTimeCount++;
			TimeManagement();	// 時間の管理
		}

		//フィーバータイム
		if (m_nTimeCount == 60 * 150)
		{
			m_bFever = true;
			m_pLogo->BindTexture("FEVERUI2");
		}

		if (m_bFever == true)
		{
			m_nFeverTime++;
			if (m_nFeverTime == 60 * 30)
			{
				m_bStopUI = false;
				m_bFever = false;
				m_nFeverTime = 0;
				m_nCntUIRepeat = 0;
				m_fUIAddScale = 1.0f;
				m_nUIScaleCounter = 0;
				m_fUIScale = 0;

				if (m_nNumPlayer == 1)
				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, SCREEN_HEIGHT / 2, 0.0f));
				}
				if (m_nNumPlayer == 2)
				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, 0.0f));
					m_pFeverUI[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, 0.0f));
				}
				if (m_nNumPlayer == 3)

				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, 0.0f));
					m_pFeverUI[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, 0.0f));
				}
				if (m_nNumPlayer == 4)
				{
					m_pFeverUI[0]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 180.0f, 0.0f));
					m_pFeverUI[1]->SetPosition(D3DXVECTOR3(SCREEN_WIDTH + SCALE_UI_WIDTH, 550.0f, 0.0f));
				}

				if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
				{
					m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 105.0f, 0.0f), TIMER_HEIGHT1P2P, TIMER_WIDTH1P2P);
				}
				else
				{
					m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 120.0f, 0.0f), TIMER_HEIGHT3P4P, TIMER_WIDTH3P4P);
				}


				m_pLogo->BindTexture("TIME");
				m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
		}

		//フィーバータイムのUI位置更新
		if (m_bFever == true)
		{
			for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
			{
				if (m_pFeverUI[nCntPlayer] != NULL)
				{
					D3DXVECTOR3 UIPos = m_pFeverUI[nCntPlayer]->GetPosition();
					if (m_bStopUI == false)
					{
						UIPos.x -= 5;
					}
					m_pFeverUI[nCntPlayer]->SetPosition(UIPos);
					if (UIPos.x < -SCALE_UI_WIDTH)
					{
						if (nCntPlayer == 0)
						{
							m_nCntUIRepeat++;
						}
						UIPos.x = SCREEN_WIDTH + SCALE_UI_WIDTH;
						m_pFeverUI[nCntPlayer]->SetPosition(UIPos);
						if (m_nCntUIRepeat == 2)
						{
							m_bStopUI = true;
						}
					}
				}
			}
			//ビルボード拡大縮小
			if (m_bStopUI == true)
			{
				m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
			else if (m_bStopUI == false)
			{
				m_pFeverBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));
			}
			m_nUIScaleCounter++;
			m_fUIScale += m_fUIAddScale;
			m_pFeverBillBoard->SetBillboard(D3DXVECTOR3(0.0f, 120.0f, 0.0f), 40.0f + m_fUIScale, 40.0f + m_fUIScale);

			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 105.0f, 0.0f), TIMER_HEIGHT1P2P + (m_fUIScale / 2), TIMER_WIDTH1P2P + (m_fUIScale / 2));
			}
			else
			{
				m_pLogo->SetBillboard(D3DXVECTOR3(5.0f, 120.0f, 0.0f), TIMER_HEIGHT3P4P + (m_fUIScale / 2), TIMER_WIDTH3P4P + (m_fUIScale / 2));
			}


			for (int nCntPlayer = 0; nCntPlayer < 2; nCntPlayer++)
			{
				if (m_pFeverUI[nCntPlayer] != NULL)
				{
					m_pFeverUI[nCntPlayer]->SetWidthHeight(SCALE_UI_WIDTH + m_fUIScale, SCALE_UI + m_fUIScale);
				}
			}

			if (m_nUIScaleCounter == 30)
			{
				m_fUIAddScale *= -1;
				m_nUIScaleCounter = 0;
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
					CResult::SetRanking(nCntPlayer, CGame::GetPlayer(nCntPlayer)->GetID(), CGame::GetPlayerType(nCntPlayer), CGame::GetPlayer(nCntPlayer)->GetMovetype(), CGame::GetPoint(nCntPlayer)->GetPoint());
				}

				CFade::SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
			}
		}

		if (m_bChangeStage == true)
		{	// ステージ変化の色変化
			ChangeStage();
		}

		ScaleNumber();	// サイズの切替
	}

	CountDown();	// カウントダウン処理

	//ステージ生成完了タイマー
	if (CGame::GetbStageSet() == true)
	{
		m_StageCounter++;
		if (m_StageCounter > 120)
		{
			CManager::GetGame()->SetCreateWord();
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
	if (m_pFeverBillBoard != NULL)
	{
		if (m_bFever == true)
		{
			m_pFeverBillBoard->Draw();
		}
	}
}

//=============================================================================
// カウントダウン
//=============================================================================
void CTime::CountDown(void)
{
	//カウントダウン
	if (m_bEndCntDown == false)
	{
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
		if (m_fScale > COUNTDOWN_SCALE * 75)
		{
			m_fScale = COUNTDOWN_SCALE * 75;
			if (m_nType < 1)
			{
				m_bCntDown = true;
				m_nType += 1;
				m_fScale = 0;
				m_Col.a = 1.0f;
			}
			else if (m_nType == 1)
			{
				m_bEndCntDown = true;
				m_Col.a = 0.0f;
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{	// プレイヤーを取得
					m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
					if (m_pPlayer[nCntPlayer] != NULL)
					{
						m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(false);
					}
				}
			}

			for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
			{
				if (m_pScene2D[nCnt] != NULL)
				{
					switch (m_nType)
					{
					case 0:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN0");
						break;
					case 1:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN1");
						m_pScene2D[nCnt]->SetWidthHeight(m_fWidth + 100, m_fHeight + 100);
						break;
					default:
						break;
					}
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
			if (m_bChangeStage == false)
			{
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
	{	// 60秒ごとにステージが変わる
		m_bStageCreate = true;
		CGame::bStageSet(true);
		int nStageNum = (m_nStageChange / 60);
		m_nStageNum = (m_nStageChange / 60);
		CManager::GetGame()->SetStage(CGame::GetNumStage(),nStageNum);
	}

	if (m_nTime == 10 && m_nTimeOne != 0)
	{	// 警告の時間
		m_bChangeStage = true;
	}


	//リピートモードの時は早く
	int nFlameSecond = 60;
#ifdef _DEBUG
	if (CManager::GetRepeat() == true)
	{
		nFlameSecond = 1;
	}
#endif
	if (m_nTimeCount % nFlameSecond == 0)
	{// 1秒ごとに減算(制限時間)
		m_nTime--;
		m_nStageChange++;
		m_bStageCreate = false;

		if (m_nTime < 0) { m_nTime = 59; m_nTimeOne -= 1; 	DefaultCol();}
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// ステージ切替時の演出
//=============================================================================
void CTime::ChangeStage(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// テクスチャに反映
		if (m_apNumber[nCntTime] != NULL)
		{
			// 色の設定
			if (m_bWarning == false)
			{
				m_fWarningCol -= 0.01f;
				if (m_fWarningCol < 0.2f) { m_fWarningCol = 0.2f;  m_bWarning = true; }
			}
			else if (m_bWarning == true)
			{
				m_fWarningCol += 0.01f;
				if (m_fWarningCol > 1.0f) { m_fWarningCol = 1.0f;  m_bWarning = false; }
			}
			m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, m_fWarningCol, 0.0f, 1.0f));
			if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, m_fWarningCol, 0.0f, 1.0f)); }
		}
	}
}

//=============================================================================
// 色を元に戻す
//=============================================================================
void CTime::DefaultCol(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// テクスチャに反映
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
		}
	}

	m_bChangeStage = false;
}

//=============================================================================
// ステージタイムの拡大縮小処理
//=============================================================================
void CTime::ScaleNumber(void)
{
	if (m_bChangeStage == false)
	{	// ステージ切り替えの警告フラグがfalseならサイズを戻す
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{
			if (m_apNumber[nCntTime] != NULL && m_apNumber[nCntTime]->GetSize() != DEFAULT_SIZE)
			{
				if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
				{
					m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE1P2P);
				}
				else
				{
					m_apNumber[nCntTime]->SetSize(DEFAULT_SIZE3P4P);
				}
			}
		}
		m_nCntScale = 0;
		return;
	}

	m_nCntScale++;	// 加算
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			// サイズの取得
			D3DXVECTOR3 size = m_apNumber[nCntTime]->GetSize();
			float fSizeChange = 0.5f;

			// フラグがfalseなら縮小
			if (m_bScaleFlag == false)
			{
				size.x += fSizeChange / 2;
				size.y += fSizeChange;

				if ((m_nCntScale % SCALE_CHANGE_TIME) == 0) { m_bScaleFlag = true; }
			}
			// フラグがtrueなら拡大
			else if (m_bScaleFlag == true)
			{
				size.x -= fSizeChange / 2;
				size.y -= fSizeChange;

				if ((m_nCntScale % SCALE_CHANGE_TIME) == 0) {
					m_bScaleFlag = false; }
			}

			// サイズの設定
			m_apNumber[nCntTime]->SetSize(size);
		}
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

	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD6))
	{	// 制限時間加算
		m_nTimeCount--;
		m_nStageChange--;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD4))
	{	// 制限時間加算
		m_nTimeCount++;
		m_nStageChange++;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// リザルト画面へ
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}