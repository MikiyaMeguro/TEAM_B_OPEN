//=============================================================================
//
// タイマー処理 [tutotime.cpp]
// Author : Meguroo Mikiya
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "tutotime.h"
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
#define GAME_TUTOTIME_MAX		(9)								// ゲームの時間最大数
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
int						CTutoTime::m_nTime = 0;
int						CTutoTime::m_nTimeCount = 0;
bool					CTutoTime::m_bCountFlag = true;			//時間をカウントするか
int						CTutoTime::m_nTimeOld = 0;
int						CTutoTime::m_nTimeOne = 3;
int						CTutoTime::m_nStageNum = 0;
//=============================================================================
// 生成処理
//=============================================================================
CTutoTime *CTutoTime::Create(int nNumPlayer)
{
	CTutoTime *pTime = NULL;

	//NULLチェック
	if (pTime == NULL)
	{//動的確保
		pTime = new CTutoTime;

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
CTutoTime::CTutoTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
	m_nTimeNum = 3;
	m_nWaitTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTutoTime::~CTutoTime() {}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutoTime::Init(void)
{
	int nTexData = 0;
	m_nTime = 0;
	m_nTimeOld = GAME_TIME - 30;
	m_nTimeNum = PowerCalculation(m_nTime, 0);
	m_nTimeOne = 3;
	int nHeight = 0;
	int nWidth = 0;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{
			m_apNumber[nCntTime][nCntPlayer] = NULL;
		}
	}

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
		{
			for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
			{	// タイマー初期設定
				m_apNumber[nCntTime][nCntPlayer] = new CNumber;
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
					m_apNumber[nCntTime][nCntPlayer]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(50, 70), D3DXVECTOR2(410.0f + (68 * nCntTime), 650.0f));
					m_apNumber[nCntTime][nCntPlayer]->SetNumber(0);
					m_apNumber[nCntTime][nCntPlayer]->SetbDraw(true);
				}

				if (m_nNumPlayer == 1)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(50, 70), D3DXVECTOR2(430.0f - (68 * nCntTime), 650.0f));
				}
				else if(m_nNumPlayer == 2)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(50, 70), D3DXVECTOR2(430.0f - (68 * nCntTime), 300.0f + (360 * nCntPlayer)));
				}
				else if (m_nNumPlayer == 3)
				{
					if (nCntPlayer == 1)
					{
						nHeight = 1;
					}
					if (nCntPlayer == 2)
					{
						nWidth = 1;
						nHeight = 0;
					}

					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(25, 35), D3DXVECTOR2(270.0f - (35 * nCntTime) + (650 * nWidth), 320.0f + (360 * nHeight)));
				}
				else if (m_nNumPlayer == 4)
				{
					if (nCntPlayer == 1)
					{
						nHeight = 1;
					}
					if (nCntPlayer == 2)
					{
						nWidth = 1;
						nHeight = 0;
					}
					if (nCntPlayer == 3)
					{
						nWidth = 1;
						nHeight = 1;
					}
					m_apNumber[nCntTime][nCntPlayer]->SetSize(D3DXVECTOR2(25, 35), D3DXVECTOR2(270.0f - (35 * nCntTime) + (650 * nWidth), 320.0f + (360 * nHeight)));
				}
			}
		}
		// 数字のテクスチャ設定
		m_nTime = 30;
		TexTime(nTexData, m_nTimeOne);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutoTime::Uninit(void)
{
	m_nStageNum = 0;
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
		{
			for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
			{	// タイマーの破棄
				if (m_apNumber[nCntTime][nCntPlayer] != NULL)
				{
					m_apNumber[nCntTime][nCntPlayer]->Uninit();
					m_apNumber[nCntTime][nCntPlayer] = NULL;
				}
			}
		}
	}

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutoTime::Update(void)
{
	CSound *pSound = CManager::GetSound();		//	音の取得

	//現在のモードの取得
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// デバック用

	if (GameMode == CManager::MODE_TUTORIAL)
	{//制限時間
	 //ゲーム
		if (m_bCountFlag == true)
		{
			m_nTimeCount++;
			TimeManagement();	// 時間の管理
		}

		int nTexData = 0;
		// 数字のテクスチャ設定
		TexTime(nTexData, m_nTimeOne);

		if (m_nTime == 0 && GameMode == CManager::MODE_TUTORIAL)
		{
			// ゲーム終了
			m_nWaitTime++;	// 待ち時間の加算
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				CFade::SetFade(CManager::MODE_CHARASELECT, CFade::FADE_OUT);
			}
		}
	}

	//CountDown();	// カウントダウン処理

}

//=============================================================================
// 描画処理
//=============================================================================
void CTutoTime::Draw(void)
{
	for (int nCntPlayer = 0; nCntPlayer < m_nNumPlayer; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{
			if (m_apNumber[nCntTime][nCntPlayer] != NULL)
			{
				m_apNumber[nCntTime][nCntPlayer]->Draw();
			}
		}
	}
}

//=============================================================================
// カウントダウン
//=============================================================================
void CTutoTime::CountDown(void)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
}
//=============================================================================
// タイマーのTexture管理
//=============================================================================
void CTutoTime::TexTime(int nTexData, int nTimeOne)
{
	int nTime[4] = { 0,0,0,0 };
	nTexData = m_nTime;

	for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
	{
		nTime[nCntPlayer] = m_nTime;
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{// テクスチャに反映
			if (m_apNumber[nCntTime][nCntPlayer] != NULL)
			{
				if (nCntTime < 2)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetNumber(nTime[nCntPlayer]);
					nTime[nCntPlayer] /= 10;
				}
				else if (nCntTime == 2)
				{
					m_apNumber[nCntTime][nCntPlayer]->SetNumber(nTime[nCntPlayer]);
					nTime[nCntPlayer] /= 10;
				}
			}
		}
	}
}
//=============================================================================
// タイム加算処理
//=============================================================================
void CTutoTime::AddTime(int nTime)
{
	if (m_nTime > 0)
	{
		m_nTimeOne += nTime;
	}

	if (GAME_TUTOTIME_MAX < m_nTimeOne) { m_nTimeOne = GAME_TUTOTIME_MAX; }
}
//=============================================================================
// べき乗の計算
//=============================================================================
int CTutoTime::PowerCalculation(int nData, int nOperation)
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
			if (nNum >= TUTOTIME_MAX) { nNum = TUTOTIME_MAX; }
		}
	}
	return nNum;
}

//=============================================================================
// 時間の管理
//=============================================================================
void CTutoTime::TimeManagement(void)
{
	if (m_nTime == 0 && m_nTimeOne == 0) {m_nTime = 0; return; }

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
		if (m_nTime < 0) { m_nTime = 0; m_nTimeOne -= 1; 	DefaultCol();}
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// ステージ切替時の演出
//=============================================================================
void CTutoTime::ChangeStage(void)
{

}

//=============================================================================
// 色を元に戻す
//=============================================================================
void CTutoTime::DefaultCol(void)
{
	for (int nCntPlayer = 0; nCntPlayer < PLAYER_MAX; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{// テクスチャに反映
			if (m_apNumber[nCntTime][nCntPlayer] != NULL)
			{
				m_apNumber[nCntTime][nCntPlayer]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}

//=============================================================================
// デバック用
//=============================================================================
void CTutoTime::DebugKey(void)
{
	// デバック用
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD0))
	{	// 制限時間加算
		AddTime(1);
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD6))
	{	// 制限時間加算
		m_nTimeCount--;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD4))
	{	// 制限時間加算
		m_nTimeCount++;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// リザルト画面へ
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}