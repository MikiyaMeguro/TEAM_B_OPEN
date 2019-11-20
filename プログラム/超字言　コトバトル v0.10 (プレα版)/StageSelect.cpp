//=============================================================================
//
// ステージセレクト処理 [StageSelect.cpp]
// Author : 目黒 未来也/後閑 茜
//
//=============================================================================
#include "StageSelect.h"
#include "manager.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "SetObject.h"
#include <time.h>

//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)
#define SIZE_Y (SCREEN_HEIGHT/2)
#define DEFAULT_SIZE (150.0f)									//ポリゴンサイズの基本の大きさ
#define DEFAULT_POS (D3DXVECTOR3(SIZE_X,SIZE_Y,0.0f))			//初期化位置
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))				//初期化位置
#define STAGESELCHOICE_POS	(D3DXVECTOR3(300.0f,300.0f,0.0f))	//選択肢ポリゴンの位置
#define STAGESELCHOICE_INTERVAL (350.0f)						//選択肢ポリゴン同士の間隔

//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CStageSelect::m_apScene2D[MAX_STAGESELECT_TEX] = {};
CScene2D *CStageSelect::m_apSelect2D[MAX_STAGESELECT] = {};
int CStageSelect::m_nSelect = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CStageSelect::CStageSelect()
{
	m_nCntScrool = 0;
	m_nSelect = 0;
	m_state = SELECTSTATE_SELECT_MACHINE;
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		m_SelectPos[nCnt] = DEFAULT_POS;
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// ステージセレクトの初期化処理
//=============================================================================
void CStageSelect::Init(void)
{
	/*2Dポリゴンの初期設定*/
	InitPolygon();
}

//=============================================================================
// ステージセレクトの終了処理
//=============================================================================
void CStageSelect::Uninit(void)
{
	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// ステージセレクトの更新処理
//=============================================================================
void CStageSelect::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//任意のキーENTER
	if (CCommand::GetCommand("DECISION"))
	{
		pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
	}
	/* 選択処理 */
	if (CCommand::GetCommand("RIGHT"))
	{//右
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
		m_nSelect= (m_nSelect + 1) % MAX_STAGESELECT;
	}
	else if (CCommand::GetCommand("LEFT"))
	{//左
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 2) % MAX_STAGESELECT;
	}

	//選択番号を状態変数に反映し、状態にあわせて処理を行う
	m_state = (SELECTSTATE)m_nSelect;
	SelectState(m_state);

	/* 帯のテクスチャスクロール */
	ScrollMenu(STAGESELECTTYPE_BAND_R, 0.005f);
	ScrollMenu(STAGESELECTTYPE_BAND_L, -0.005f);

#ifdef _DEBUG
	CDebugProc::Print("c", "ステージセレクト");
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);

#endif
}

//=============================================================================
// ステージセレクトの描画処理
//=============================================================================
void CStageSelect::Draw(void)
{

}
//=============================================================================
// ポリゴンの初期設定
//=============================================================================
void CStageSelect::InitPolygon(void)
{
	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{
		/* 生成と座標とテクスチャ */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(STAGESELCHOICE_POS.x + (STAGESELCHOICE_INTERVAL*nCnt),
			STAGESELCHOICE_POS.y,
			STAGESELCHOICE_POS.z), "STAGESEL_ICON");
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f+(1.0f/ MAX_STAGESELECT)*nCnt, 0.0f), D3DXVECTOR2((1.0f / MAX_STAGESELECT) + (1.0f / MAX_STAGESELECT)*nCnt, 1.0f));
		/* サイズ設定 */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);

		/* 選択肢の初期位置を記憶する */
		m_SelectPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();
	}

	//背景
	m_apScene2D[STAGESELECTTYPE_BG] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAYERNUMSEL_BG", 1);
	m_apScene2D[STAGESELECTTYPE_BG]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);
	m_apScene2D[STAGESELECTTYPE_BG]->SetbDraw(false);

	//モード名帯（左）
	m_apScene2D[STAGESELECTTYPE_BAND_L] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "STAGESEL_BAND", 4);
	m_apScene2D[STAGESELECTTYPE_BAND_L]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//モード名帯（右）
	m_apScene2D[STAGESELECTTYPE_BAND_R] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "STAGESEL_BAND", 4);
	m_apScene2D[STAGESELECTTYPE_BAND_R]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

}
//=============================================================================
// 横の文字スクロール処理
//=============================================================================
void CStageSelect::ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;
	if (m_apScene2D[type] != NULL)
	{
		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)),
			D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}
//=============================================================================
// 選択状態の管理
//=============================================================================
void CStageSelect::SelectState(CStageSelect::SELECTSTATE state)
{
	switch (state)
	{
	case SELECTSTATE_SELECT_MACHINE:	//機械
		m_apSelect2D[0]->SetPosition(m_SelectPos[1]);
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
		m_apSelect2D[1]->SetPosition(m_SelectPos[2]);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[2]->SetPosition(m_SelectPos[0]);
		m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		break;

	case SELECTSTATE_SELECT_WEATHER:	//天候
		m_apSelect2D[0]->SetPosition(m_SelectPos[0]);
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[1]->SetPosition(m_SelectPos[1]);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
		m_apSelect2D[2]->SetPosition(m_SelectPos[2]);
		m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		break;

	case SELECTSTATE_SELECT_TERRAIN:	//地形
		m_apSelect2D[0]->SetPosition(m_SelectPos[2]);
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[1]->SetPosition(m_SelectPos[0]);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[2]->SetPosition(m_SelectPos[1]);
		m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
		break;
	}
}