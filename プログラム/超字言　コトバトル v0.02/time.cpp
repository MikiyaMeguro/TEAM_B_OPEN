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

//=============================================================================
// マクロ定義
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// Xの中心座標
#define TIMER_SPACE			(30.0f)							// 数字と数字の間のサイズ(ゲーム時間)
#define TIMER_POSITION_Y	(70.0f)							// タイマーのY座標(ゲーム時間)
#define GAME_TIME			(130)							// ゲーム開始時の時間
#define GAME_TIME_MAX		(960)							// ゲームの時間最大数
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 70.0f, 0.0f))	// 制限時間の位置(1Pだけの場合)
#define WAIT_TIME_END		(180)							// 待ち時間
//=============================================================================
//	静的メンバ変数
//=============================================================================
int						CTime::m_nTime = 0;
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
			//if (nNumPlayer == 1 || nNumPlayer == 0)
			{
				pTime->m_pos = TIME_POS_1P;
			}
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
	m_nTimeNum = 1;
	m_nWaitTime = 0;
	m_pColon = NULL;
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
	m_nTime = GAME_TIME;
	m_nTimeNum = PowerCalculation(m_nTime, 0);

	// 後ろの背景
	CScene2D *pBg= CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), "BG_FREAME", 5);
	pBg->SetWidthHeight(80.0f, 60.0f);
	pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

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
		TexTime(nTexData);
	}

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

	if ((GameMode == CManager::MODE_GAME) || (GameMode == CManager::MODE_TUTORIAL))
	{//制限時間
	 //ゲーム
		m_nTimeCount++;

		TimeManagement();	// 時間の管理

		int nTexData = 0;
		// 数字のテクスチャ設定
		TexTime(nTexData);

		if (m_nTime == 0 && GameMode == CManager::MODE_GAME)
		{	// ゲーム終了
			m_nWaitTime++;	// 待ち時間の加算
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				CFade::SetFade(CManager::MODE_RESULT, CFade::FADE_OUT);
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < m_nTimeNum; nCntTime++)
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
void CTime::TexTime(int nTexData)
{
	nTexData = m_nTime;

	for (int nCntTime = 0; nCntTime < m_nTimeNum; nCntTime++)
	{// テクスチャに反映

		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->SetNumber(nTexData);

			nTexData /= 10;
			// 色の設定
			if (m_nTime <= 10)
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
		m_nTime += nTime;
	}

	if (GAME_TIME_MAX < m_nTime) { m_nTime = GAME_TIME_MAX; }
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
	if (m_nTimeCount % 60 == 0)
	{// 1秒ごとに減算(制限時間)
		m_nTime--;
		if ((m_nTime % 100) == 0) { m_nTime -= 41; }
		if (m_nTime < 0) { m_nTime = 0; }
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
		AddTime(100);
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// リザルト画面へ
		m_nTime = 0;
	}
}