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
	m_StageCounter = 0;

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{	// タイマー初期設定
			m_apNumber[nCntTime] = new CNumber;
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
				//m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - Space * nCntTime), m_pos.y, m_pos.z),1);
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}
			else if (nCntTime == 2)
			{	// 3桁目
				//m_apNumber[nCntTime]->Init(D3DXVECTOR3(((m_pos.x - 10.0f) - Space * nCntTime), m_pos.y, m_pos.z),2);
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				//m_apNumber[nCntTime]->SetSize(D3DXVECTOR2(TIMER_WIDTH1P2P, TIMER_HEIGHT1P2P), D3DXVECTOR2((m_pos.x - 10.0f) - Space * nCntTime, m_pos.y));
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}
			else
			{
				m_apNumber[nCntTime]->SetSize(D3DXVECTOR2(100, 100), D3DXVECTOR2(100.0f, 200.0f));
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
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+50, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
	}
	else if (m_nNumPlayer == 2)
	{
		//カウントダウンの位置設定
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
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
void CTutoTime::Uninit(void)
{
	m_nStageNum = 0;
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{	// タイマーの破棄
			if (m_apNumber[nCntTime] != NULL)
			{
				m_apNumber[nCntTime]->Uninit();
				m_apNumber[nCntTime] = NULL;
			}
		}
	}

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
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

	if ((GameMode == CManager::MODE_GAME) && m_bEndCntDown == true || (GameMode == CManager::MODE_TUTORIAL) && m_bEndCntDown == true)
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

		if (m_nTime == 0 && m_nTimeOne == 0 && GameMode == CManager::MODE_GAME)
		{
			// ゲーム終了
			m_nWaitTime++;	// 待ち時間の加算
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				CFade::SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
			}
		}
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
void CTutoTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}
}

//=============================================================================
// カウントダウン
//=============================================================================
void CTutoTime::CountDown(void)
{
	CSound *pSound = CManager::GetSound();		//	音の取得

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
				//テクスチャ替え
				m_bCntDown = true;
				m_nType += 1;
				m_fScale = 0;
				m_Col.a = 1.0f;

				pSound->SetVolume(CSound::SOUND_LABEL_SE_GAMESTART01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_GAMESTART01);
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
						//スタート表示
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
void CTutoTime::TexTime(int nTexData, int nTimeOne)
{
	nTexData = m_nTime;

	//for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
	//{// テクスチャに反映

	//	if (m_apNumber[nCntTime] != NULL)
	//	{
	//		if (nCntTime < 2)
	//		{
	//			m_apNumber[nCntTime]->SetNumber(nTexData);
	//			nTexData /= 10;
	//		}
	//		else if (nCntTime == 2)
	//		{
	//			m_apNumber[nCntTime]->SetNumber(nTimeOne);
	//			nTexData /= 10;
	//		}
	//	}
	//}
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
		if (m_nTime < 0) { m_nTime = 59; m_nTimeOne -= 1; 	DefaultCol();}
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
	for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
	{// テクスチャに反映
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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