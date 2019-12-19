//=============================================================================
//
// タイトル処理 [title.cpp]
// Author : 目黒 未来也/Akane Gokan
//
//=============================================================================
#include "title.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "time.h"
#include "scene3D.h"
#include "scene2D.h"
#include "sceneX.h"
#include "sceneBillboard.h"
#include "SetObject.h"
#include "PlayerNumSelect.h"
//============================================================================
//	マクロ定義
//============================================================================

//============================================================================
//静的メンバ変数宣言
//============================================================================

//=============================================================================
//	コンストラクタ
//=============================================================================
CTitle::CTitle()
{
}

//=============================================================================
//デストラクタ
//=============================================================================
CTitle::~CTitle()
{

}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
void CTitle::Init(void)
{
	//メンバ変数初期化
	m_bProductionSkip = false;					//演出スキップされていない
	m_FlashSkip = false;						//フラッシュスキップされていない
	m_ProductionState = PRODUCTIONSTATE_NONE;	//演出状態の初期化
	m_FlashSate = FLASHSTATE_NONE;				//フラッシュ状態の初期化

	/*火花*/
	m_fChangeSparkMove = 3.5f;
	m_fSparkX = 0.0f;

	/*フラッシュ系*/
	m_fCntFade = 0.0f;
	m_fAlpha = 0.0f;
	m_nCntFadeTime = 0;

	/*プレスボタン*/
	m_nCntFlashPress = 0;
	m_fPressAlpha = 1.0f;
	m_bPressMode = false;

	/* タイトルロゴ */
	m_fTitleScal = 100;
	/* シーン2Dの初期設定 */
	InitpScene2D();

	/* シーン2Dの初期設定処理 */
	SetScene2D();

#ifdef _DEBUG
	nCntFadeTime = 0;
#endif
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTitle::Uninit(void)
{
	// Scene2Dの破棄
	UninitpScene2D();

	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTitle::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	CSound *pSound = CManager::GetSound();		//	音の取得

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	//CXInputJoyPad *pXInput = NULL;
	//pXInput = CManager::GetXInput();

	/* 演出処理関数呼び出し */
	Production();
	Flash();

	//任意のキーENTER
	if (m_bProductionSkip == true)
	{//演出スキップ済み
		SparkProduction();	//火花移動処理
		if (m_FlashSkip == true)
		{// フラッシュ演出スキップ済み
			if (CCommand::GetCommand("DECISION"))
			{//エンター押下
				m_bPressMode = true;
				pSound->PlaySound(CSound::SOUND_LABEL_SE_TITLE);
				pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
			}
		}
	}

	if (m_bProductionSkip == false)
	{//演出未スキップ
		if (m_FlashSkip == false)
		{// フラッシュ演出未スキップ
			if (CCommand::GetCommand("DECISION"))
			{//エンター押下
				m_ProductionState = PRODUCTIONSTATE_FLASH;	//フラッシュを開始
				m_bProductionSkip = true;
			}
		}
	}
	else if (m_bProductionSkip == true)
	{//演出スキップ済み
		if (m_FlashSkip == false)
		{// フラッシュ演出未スキップ
			if (CCommand::GetCommand("DECISION"))
			{//エンター押下
				m_FlashSate = FLASHSTATE_FINISH;
			}
		}
	}


#ifdef _DEBUG
	CDebugProc::Print("c", "タイトル");

	if (CManager::GetRepeat() == true)
	{
		nCntFadeTime++;
		if (nCntFadeTime > 600)
		{
			pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
		}
	}
#endif
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTitle::Draw(void)
{

}
//=============================================================================
// ポインタの初期化処理
//=============================================================================
void CTitle::InitpScene2D(void)
{

	/* ポインタの初期化 */
	for (int nCnt = 0; nCnt < MAX_TITLEPOLYGON; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt] = NULL;
		}
	}
}
//=============================================================================
// 2Dポリゴンの終了処理
//=============================================================================
void  CTitle::UninitpScene2D(void)
{
	/* ポインタの初期化 */
	for (int nCnt = 0; nCnt < MAX_TITLEPOLYGON; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

}
//=============================================================================
// 2Dポリゴンの初期設定
//=============================================================================
void CTitle::SetScene2D(void)
{
	if (m_pScene2D[POLYGONTYPE_BALANCEBOY] == NULL)
	{//人間_バランス男子
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_BALANCEBOY] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_BALANCEBOY]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f); //サイズ
		m_pScene2D[POLYGONTYPE_BALANCEBOY]->SetPos(D3DXVECTOR3(130.0f, SCREEN_HEIGHT + SCREEN_HEIGHT - 300.0f, 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_BALANCEBOY]->SetAnimation(POLYGONTYPE_BALANCEBOY, 0.25f, 1.0f);			//アニメーション
	}
	if (m_pScene2D[POLYGONTYPE_REACHGIRL] == NULL)
	{//人間_リーチ女子
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_REACHGIRL] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_REACHGIRL]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f); //サイズ
		m_pScene2D[POLYGONTYPE_REACHGIRL]->SetPos(D3DXVECTOR3(460.0f, 0.0f - SCREEN_HEIGHT + 300.0f, 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_REACHGIRL]->SetAnimation(POLYGONTYPE_REACHGIRL, 0.25f, 1.0f);			//アニメーション
	}
	if (m_pScene2D[POLYGONTYPE_POWORBOY] == NULL)
	{//人間_パワー男子
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_POWORBOY] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_POWORBOY]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f); //サイズ
		m_pScene2D[POLYGONTYPE_POWORBOY]->SetPos(D3DXVECTOR3(790.0f, SCREEN_HEIGHT + SCREEN_HEIGHT - 300.0f , 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_POWORBOY]->SetAnimation(POLYGONTYPE_POWORBOY, 0.25f, 1.0f);			//アニメーション
	}
	if (m_pScene2D[POLYGONTYPE_SPEEDGIRL] == NULL)
	{//人間_スピード女子
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_SPEEDGIRL] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HUMAN");
		m_pScene2D[POLYGONTYPE_SPEEDGIRL]->SetWidthHeight(BG_HUMAN_SIZE_W, 510.0f);	//サイズ
		m_pScene2D[POLYGONTYPE_SPEEDGIRL]->SetPos(D3DXVECTOR3(1120.0f, 0.0f - SCREEN_HEIGHT + 300.0f, 0.0f), 0.0f, 1.0f, COL_DEFAULT);
		m_pScene2D[POLYGONTYPE_SPEEDGIRL]->SetAnimation(POLYGONTYPE_SPEEDGIRL, 0.25f, 1.0f);			//アニメーション
	}
	if (m_pScene2D[POLYGONTYPE_KOTOMON] == NULL)
	{//コトモン
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_KOTOMON] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2+50.0f, SCREEN_HEIGHT / 2-20.0f, 0.0f), "TITLE_KOTOMON");
		m_pScene2D[POLYGONTYPE_KOTOMON]->SetWidthHeight(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 180.0f);	//サイズ
		m_pScene2D[POLYGONTYPE_KOTOMON]->SetCol(COL_DEFAULT_TRANSPARENT);
	}
	if (m_pScene2D[POLYGONTYPE_SPARK] == NULL)
	{//火花
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_SPARK] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_HIBANA");
		m_pScene2D[POLYGONTYPE_SPARK]->SetWidthHeight(250.0f, 250.0f);	//サイズ
		m_pScene2D[POLYGONTYPE_SPARK]->SetCol(COL_DEFAULT_TRANSPARENT);

	}
	if (m_pScene2D[POLYGONTYPE_ROGO_MAIN] == NULL)
	{//タイトルロゴ：コトバトル
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_ROGO_MAIN] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "TITLE_ROGO_M");
		m_pScene2D[POLYGONTYPE_ROGO_MAIN]->SetWidthHeight(550.0f, 200.0f);	//サイズ
		m_pScene2D[POLYGONTYPE_ROGO_MAIN]->SetCol(COL_DEFAULT_TRANSPARENT);
	}
	if (m_pScene2D[POLYGONTYPE_ROGO_SUB] == NULL)
	{//タイトルロゴ：超字言
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_ROGO_SUB] = CScene2D::Create(D3DXVECTOR3(400.0f, 250.0f, 0.0f), "TITLE_ROGO_S");
		m_pScene2D[POLYGONTYPE_ROGO_SUB]->SetWidthHeight(250.0f, 70.0f);	//サイズ
		m_pScene2D[POLYGONTYPE_ROGO_SUB]->SetCol(COL_DEFAULT_TRANSPARENT);
	}
	if (m_pScene2D[POLYGONTYPE_FLASH] == NULL)
	{//フラッシュ用
		/* 各種設定 */
		m_pScene2D[POLYGONTYPE_FLASH] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), " ");
		m_pScene2D[POLYGONTYPE_FLASH]->SetWidthHeight(SCREEN_WIDTH - 350.0f, SCREEN_HEIGHT - 200.0f);	//サイズ
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT_TRANSPARENT);								//色
	}
	if (m_pScene2D[POLYGONTYPE_PRESSBUTTON] == NULL)
	{//プレスボタン
	 /* 各種設定 */
		m_pScene2D[POLYGONTYPE_PRESSBUTTON] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT-100.0f, 0.0f), "PRESS");
		m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetWidthHeight(SCREEN_WIDTH/3 , SCREEN_HEIGHT/10);	//サイズ
		m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetCol(COL_DEFAULT);								//色
	}

	// 演出開始状態に変更
	m_ProductionState = PRODUCTIONSTATE_START;
}
//=============================================================================
// 演出処理
//=============================================================================
void CTitle::Production(void)
{
	switch (m_ProductionState)
	{
	case PRODUCTIONSTATE_NONE:
		/* 演出がない状態 */
		break;

	case PRODUCTIONSTATE_START:
		/* 演出の開始 */
		m_ProductionState = PRODUCTIONSTATE_MOVE_B;
		break;

	case PRODUCTIONSTATE_MOVE_B:
		/* バランス男子移動 */
		if (MoveBGCharactor(POLYGONTYPE_BALANCEBOY) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_MOVE_R;
		}
		break;

	case PRODUCTIONSTATE_MOVE_R:
		/* リーチ女子移動 */
		if (MoveBGCharactor(POLYGONTYPE_REACHGIRL) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_MOVE_P;
		}
		break;

	case PRODUCTIONSTATE_MOVE_P:
		/* パワー男子移動 */
		if (MoveBGCharactor(POLYGONTYPE_POWORBOY) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_MOVE_S;
		}
		break;

	case PRODUCTIONSTATE_MOVE_S:
		/* スピード女子移動 */
		if (MoveBGCharactor(POLYGONTYPE_SPEEDGIRL) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_TITLE_SUB;
		}
		break;

	case PRODUCTIONSTATE_TITLE_SUB:
		/* サブタイトル */
		if (TitleScaling(POLYGONTYPE_ROGO_SUB) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_TITLE_MAIN;
		}
		break;

	case PRODUCTIONSTATE_TITLE_MAIN:
		/* メインタイトル */
		if (TitleScaling(POLYGONTYPE_ROGO_MAIN) == true)
		{
			m_ProductionState = PRODUCTIONSTATE_FLASH;
		}
		break;

	case PRODUCTIONSTATE_FLASH:
		/* フラッシュ開始とポリゴンをフラッシュ終了後の色へ変更 */
		HumanProductionPos();

		m_FlashSate = FLASHSTATE_START;
		m_ProductionState = PRODUCTIONSTATE_FINISH;
		break;

	case PRODUCTIONSTATE_FINISH:
		/* 演出全工程が終わった */
		m_bProductionSkip = true;					//演出をスキップ状態
		m_ProductionState = PRODUCTIONSTATE_NONE;	//演出がない状態に戻す
		break;
	}
	Flash();
	PressProduction();
}
//=============================================================================
// 演出処理
//=============================================================================
void CTitle::Flash(void)
{
	switch (m_FlashSate)
	{
	case FLASHSTATE_NONE:
		break;

	case FLASHSTATE_START:
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT);
		m_fCntFade = 1.0f;
		m_nCntFadeTime++;

		if (m_nCntFadeTime >= 30)
		{//0.5秒白画面になったら
			m_FlashSate = FLASHSTATE_FADEOUT;
		}
		break;

	case FLASHSTATE_FADEOUT:
		if (m_fAlpha < 0.0f)
		{//透明度が0以下
			m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT_TRANSPARENT);
			m_FlashSate = FLASHSTATE_FINISH;
			m_ProductionState = PRODUCTIONSTATE_FINISH;
		}
		else
		{
			m_fCntFade = m_fCntFade - 0.008f;
			m_fAlpha = m_fCntFade;
		}
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fAlpha));
		break;

	case FLASHSTATE_FINISH:
		m_pScene2D[POLYGONTYPE_FLASH]->SetCol(COL_DEFAULT_TRANSPARENT);
		m_FlashSkip = true;
		m_FlashSate = FLASHSTATE_NONE;
		break;
	}
}
//=============================================================================
// 背景移動処理
//=============================================================================
bool CTitle::MoveBGCharactor(int Num)
{
	bool bMove = false;
	float fMoveY = -20.0f;	//移動させる用(偶数前提)
	D3DXVECTOR3 Pos = m_pScene2D[Num]->GetPosition();

	if (Num % 2 != 0)
	{//偶数じゃなかったら移動方向の変更
		fMoveY *= -1.0f;
	}

	/* テクスチャの移動 */
	Pos.y += fMoveY;
	m_pScene2D[Num]->SetPos(Pos, 0.0f, 1.0f, COL_DEFAULT);

	if (Num % 2 == 0)
	{//偶数の場合
		if (Pos.y <= SCREEN_HEIGHT / 2)
		{
			bMove = true;
		}
	}
	else if (Num % 2 != 0)
	{//偶数じゃない場合
		if (Pos.y >= SCREEN_HEIGHT / 2)
		{
			bMove = true;
		}
	}
	return bMove;
}
//=============================================================================
// タイトルロゴの拡縮処理
//=============================================================================
bool CTitle::TitleScaling(int Num)
{
	bool bTitleScaling = false;

	if (Num % 2 == 0)
	{//偶数（メイン）
		m_pScene2D[Num]->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TITLEROGO_CORRECTION, 0.0f), 0.0f, m_fTitleScal, COL_DEFAULT);
		m_fTitleScal -= 8.0f;

		if (m_fTitleScal <= 1.0f)
		{
			bTitleScaling = true;
			m_fTitleScal = 0.0f;
		}
	}
	else
	{//奇数（サブ）
		m_pScene2D[Num]->SetPos(D3DXVECTOR3(400.0f, 250.0f - TITLEROGO_CORRECTION, 0.0f), 0.0f, m_fTitleScal, COL_DEFAULT);
		m_fTitleScal -= 5.0f;
		if (m_fTitleScal <= 1.0f)
		{
			bTitleScaling = true;
			m_fTitleScal = 200.0f;
		}
	}

	return bTitleScaling;
}
//=============================================================================
// スキップした時の位置変更処理
//=============================================================================
void CTitle::HumanProductionPos(void)
{
	/* バランス男子 */
	m_pScene2D[POLYGONTYPE_BALANCEBOY]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_BALANCEBOY]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* リーチ女子 */
	m_pScene2D[POLYGONTYPE_REACHGIRL]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_REACHGIRL]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* パワー男子 */
	m_pScene2D[POLYGONTYPE_POWORBOY]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_POWORBOY]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* スピード女子 */
	m_pScene2D[POLYGONTYPE_SPEEDGIRL]
		->SetPos(D3DXVECTOR3(m_pScene2D[POLYGONTYPE_SPEEDGIRL]->GetPosition().x, POS_DEFOLT.y, POS_DEFOLT.z), 0.0f, 0.0f, COL_PRODUCTION_HUMAN);
	/* メインタイトル */
	m_pScene2D[POLYGONTYPE_ROGO_MAIN]
		->SetPos(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - TITLEROGO_CORRECTION, 0.0f),0.0f,0.0f,COL_DEFAULT);
	m_pScene2D[POLYGONTYPE_ROGO_MAIN]->SetCol(COL_DEFAULT);
	/* サブタイトル */
	m_pScene2D[POLYGONTYPE_ROGO_SUB]
		->SetPos(D3DXVECTOR3(400.0f, 250.0f - TITLEROGO_CORRECTION, 0.0f), 0.0f, 0.0f, COL_DEFAULT);
	m_pScene2D[POLYGONTYPE_ROGO_SUB]->SetCol(COL_DEFAULT);

	/* コトモン */
	m_pScene2D[POLYGONTYPE_KOTOMON]->SetCol(COL_DEFAULT);

	/* 火花 */
	m_pScene2D[POLYGONTYPE_SPARK]->SetCol(COL_DEFAULT);

}
//=============================================================================
// 火花の演出処理
//=============================================================================
void CTitle::SparkProduction(void)
{
	D3DXVECTOR3 SparkPos = m_pScene2D[POLYGONTYPE_SPARK]->GetPosition();

	if (m_fSparkX >= 5.0f|| m_fSparkX <= -5.0f)
	{
		m_fChangeSparkMove *= -1.0f;
	}

	//移動量を加算
	m_fSparkX += m_fChangeSparkMove;
	SparkPos.x += m_fSparkX;

	m_pScene2D[POLYGONTYPE_SPARK]->SetPos(SparkPos, 0.0f, 0.0f, COL_DEFAULT);
}
//=============================================================================
// プレスボタンの演出処理
//=============================================================================
void CTitle::PressProduction(void)
{
	m_nCntFlashPress++;
	if (m_bPressMode == false)
	{
		if (m_nCntFlashPress >= 30)
		{
			m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetCol(D3DXCOLOR(COL_DEFAULT.r, COL_DEFAULT.g, COL_DEFAULT.b, m_fPressAlpha));
			m_fPressAlpha *= -1.0f;
			m_nCntFlashPress = 0;
		}
	}
	else
	{
		if (m_nCntFlashPress >= 3)
		{
			m_pScene2D[POLYGONTYPE_PRESSBUTTON]->SetCol(D3DXCOLOR(COL_DEFAULT.r, COL_DEFAULT.g, COL_DEFAULT.b, m_fPressAlpha));
			m_fPressAlpha *= -1.0f;
			m_nCntFlashPress = 0;
		}
	}
}