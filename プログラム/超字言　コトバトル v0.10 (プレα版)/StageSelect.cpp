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
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))				//初期化回転
#define DEFAULT_COL (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))			//初期化色
#define STAGESELCHOICE_POS	(D3DXVECTOR3(300.0f,300.0f,0.0f))	//選択肢ポリゴンの位置
#define STAGESELCHOICE_INTERVAL (350.0f)						//選択肢ポリゴン同士の間隔
#define STAGESEL_DIFF (0.3f)									//移動の変化量
//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CStageSelect::m_apScene2D[MAX_STAGESELECT_TEX] = {};
CScene2D *CStageSelect::m_apSelect2D[MAX_STAGESELECT] = {};
int	CStageSelect::m_nSelect = 0;
//=============================================================================
//	コンストラクタ
//=============================================================================
CStageSelect::CStageSelect()
{
	m_nCntScrool = 0;
	m_type = SELECTTYPE_SELECT_MACHINE;
	m_MoveIconState = SELECTICON_STATE_NONE;
	m_bRep = false;

	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		m_SelectPos[nCnt] = DEFAULT_POS;
		m_IconCol[nCnt] = DEFAULT_COL;
		m_fWidth[nCnt] = 0.0f;
		m_fHeight[nCnt] = 0.0f;
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
		m_nSelect = (m_nSelect + 1) % MAX_STAGESELECT;
		m_MoveIconState = SELECTICON_STATE_MOVE_R;
	}
	else if (CCommand::GetCommand("LEFT"))
	{//左
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (MAX_STAGESELECT - 1)) % MAX_STAGESELECT;
		m_MoveIconState = SELECTICON_STATE_MOVE_L;
	}

	//選択番号を状態変数に反映し、状態にあわせて処理を行う
	ProductionIcon(m_MoveIconState, m_type);
	if (m_MoveIconState == SELECTICON_STATE_NONE)
	{//移動が完了したら
		m_type = (SELECTTYPE)m_nSelect;
		Selecttype(m_type);
	}

	/* 帯のテクスチャスクロール */
	ScrollMenu(STAGESELECTTYPE_BAND_R, 0.005f);
	ScrollMenu(STAGESELECTTYPE_BAND_L, -0.005f);

#ifdef _DEBUG
	CDebugProc::Print("c", "ステージセレクト");
	CDebugProc::Print("cn", "m_MoveIconState:", m_MoveIconState);
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
	D3DXVECTOR3 Replacement = DEFAULT_POS;

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{
		/* 生成と座標とテクスチャ */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(STAGESELCHOICE_POS.x + (STAGESELCHOICE_INTERVAL*nCnt),
			STAGESELCHOICE_POS.y,
			STAGESELCHOICE_POS.z), "STAGESEL_ICON");
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f+(1.0f/ MAX_STAGESELECT)*nCnt, 0.0f), D3DXVECTOR2((1.0f / MAX_STAGESELECT) + (1.0f / MAX_STAGESELECT)*nCnt, 1.0f));
		
		/* 選択肢の初期位置を記憶する */
		m_SelectPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();

	}
	m_IconCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_IconCol[1] = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);
	m_IconCol[2] = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);

	/* 初期位置から見て真ん中が0になるように設定 */
	Replacement = m_SelectPos[1];
	m_SelectPos[1] = m_SelectPos[2];
	m_SelectPos[2] = m_SelectPos[0];
	m_SelectPos[0] = Replacement;

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{/* 位置を再設定 */
		m_apSelect2D[nCnt]->SetPosition(m_SelectPos[nCnt]);
		m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
	}

	/* サイズ設定 */
	m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
	m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
	m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{/* サイズを取得 */
		m_fWidth[nCnt] = m_apSelect2D[nCnt]->GetSize(0);
		m_fHeight[nCnt] = m_apSelect2D[nCnt]->GetSize(1);
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
void CStageSelect::Selecttype(CStageSelect::SELECTTYPE TYPE)
{
	switch (TYPE)
	{
	case SELECTTYPE_SELECT_MACHINE:	//機械		
		break;

	case SELECTTYPE_SELECT_WEATHER:	//天候
		break;

	case SELECTTYPE_SELECT_TERRAIN:	//地形
		break;
	}
}
//=============================================================================
// 選択肢の移動演出
//=============================================================================
void CStageSelect::ProductionIcon(SELECTICONSTATE &state, SELECTTYPE type)
{
	float fDiffpos[MAX_STAGE] = { 0.0f ,0.0f ,0.0f };											//位置差
	D3DXVECTOR2 fDiffScal[MAX_STAGE] = { D3DXVECTOR2(0.0f, 0.0f) ,D3DXVECTOR2(0.0f, 0.0f) };	//拡縮差
	float fmove[MAX_STAGE] = { 0.0f ,0.0f ,0.0f };												//移動量
	D3DXVECTOR2 fScal[MAX_STAGE] = { D3DXVECTOR2(0.0f, 0.0f) ,D3DXVECTOR2(0.0f, 0.0f) };		//拡縮量

	switch (state)
	{
	case SELECTICON_STATE_NONE:
		break;

	case SELECTICON_STATE_MOVE_R:
		if (m_bRep == false)
		{
			Replacement(state);
			m_bRep = true;
		}
		for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
		{
			fDiffpos[nCnt] = m_SelectPos[nCnt].x - m_apSelect2D[nCnt]->GetPosition().x;
			fDiffScal[nCnt] = D3DXVECTOR2(m_fWidth[nCnt] - m_apSelect2D[nCnt]->GetSize(0), m_fHeight[nCnt] - m_apSelect2D[nCnt]->GetSize(1));
			if (fDiffpos[nCnt] <= 0.0f)
			{
				fDiffpos[nCnt] *= -1.0f;
			}
			if (fScal[nCnt].x <= 0.0f)
			{
				fScal[nCnt].x *= -1.0f;
			}
			if (fScal[nCnt].y <= 0.0f)
			{
				fScal[nCnt].y *= -1.0f;
			}
			fmove[nCnt] = fDiffpos[nCnt] - (fDiffpos[nCnt] * STAGESEL_DIFF);
			fScal[nCnt] = D3DXVECTOR2(fDiffScal[nCnt].x - (fDiffScal[nCnt].x*STAGESEL_DIFF), fDiffScal[nCnt].y - (fDiffScal[nCnt].y*STAGESEL_DIFF));

			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(m_SelectPos[nCnt].x + fmove[nCnt], m_SelectPos[nCnt].y, m_SelectPos[nCnt].z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fWidth[nCnt] - fScal[nCnt].x, m_fHeight[nCnt] - fScal[nCnt].y);
			m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
		}

		if (fDiffpos[0] <= 1.0f&&fDiffpos[1] <= 1.0f&& fDiffpos[2] <= 1.0f)
		{//差がなくなったら移動完了
			state = SELECTICON_STATE_STOP;
		}
		break;

	case SELECTICON_STATE_MOVE_L:
		if (m_bRep == false)
		{
			Replacement(state);
			m_bRep = true;
		}

		if (m_bRep == false)
		{
			Replacement(state);
			m_bRep = true;
		}
		for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
		{
			fDiffpos[nCnt] = m_SelectPos[nCnt].x - m_apSelect2D[nCnt]->GetPosition().x;
			fDiffScal[nCnt] = D3DXVECTOR2(m_fWidth[nCnt] - m_apSelect2D[nCnt]->GetSize(0), m_fHeight[nCnt] - m_apSelect2D[nCnt]->GetSize(1));
			if (fDiffpos[nCnt] <= 0.0f)
			{
				fDiffpos[nCnt] *= -1.0f;
			}
			if (fScal[nCnt].x <= 0.0f)
			{
				fScal[nCnt].x *= -1.0f;
			}
			if (fScal[nCnt].y <= 0.0f)
			{
				fScal[nCnt].y *= -1.0f;
			}
			fmove[nCnt] = fDiffpos[nCnt] - (fDiffpos[nCnt] * STAGESEL_DIFF);
			fScal[nCnt] = D3DXVECTOR2(fDiffScal[nCnt].x - (fDiffScal[nCnt].x*STAGESEL_DIFF), fDiffScal[nCnt].y - (fDiffScal[nCnt].y*STAGESEL_DIFF));

			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(m_SelectPos[nCnt].x - fmove[nCnt], m_SelectPos[nCnt].y, m_SelectPos[nCnt].z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fWidth[nCnt] - fScal[nCnt].x, m_fHeight[nCnt] - fScal[nCnt].y);
			m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
		}

		if (fDiffpos[0] <= 1.0f&&fDiffpos[1] <= 1.0f&& fDiffpos[2] <= 1.0f)
		{//差がなくなったら移動完了
			state = SELECTICON_STATE_STOP;
		}
		break;


	case SELECTICON_STATE_STOP:
		m_bRep = false;
		state = SELECTICON_STATE_NONE;
		break;
	}

}
//=============================================================================
// 座標入れ替え
//=============================================================================
void CStageSelect::Replacement(SELECTICONSTATE state)
{
	/* 仮置き用変数 */
	D3DXVECTOR3 Replacement = DEFAULT_POS;
	float RepW = 0.0f, RepH = 0.0f;
	D3DXCOLOR RepCol = DEFAULT_COL;

	switch (state)
	{
	case SELECTICON_STATE_MOVE_R:
		/* 位置 */
		Replacement = m_SelectPos[1];
		m_SelectPos[1] = m_SelectPos[0];
		m_SelectPos[0] = m_SelectPos[2];
		m_SelectPos[2] = Replacement;
		/* 横幅 */
		RepW = m_fWidth[1];
		m_fWidth[1] = m_fWidth[0];
		m_fWidth[0] = m_fWidth[2];
		m_fWidth[2] = RepW;
		/* 縦幅 */
		RepH = m_fHeight[1];
		m_fHeight[1] = m_fHeight[0];
		m_fHeight[0] = m_fHeight[2];
		m_fHeight[2] = RepH;
		/* 色 */
		RepCol = m_IconCol[1];
		m_IconCol[1] = m_IconCol[0];
		m_IconCol[0] = m_IconCol[2];
		m_IconCol[2] = RepCol;
		break;

	case SELECTICON_STATE_MOVE_L:
		/* 位置 */
		Replacement = m_SelectPos[1];
		m_SelectPos[1] = m_SelectPos[2];
		m_SelectPos[2] = m_SelectPos[0];
		m_SelectPos[0] = Replacement;
		/* 横幅 */
		RepW = m_fWidth[1];
		m_fWidth[1] = m_fWidth[2];
		m_fWidth[2] = m_fWidth[0];
		m_fWidth[0] = RepW;
		/* 縦幅 */
		RepH = m_fHeight[1];
		m_fHeight[1] = m_fHeight[2];
		m_fHeight[2] = m_fHeight[0];
		m_fHeight[0] = RepH;
		/* 色 */
		RepCol = m_IconCol[1];
		m_IconCol[1] = m_IconCol[2];
		m_IconCol[2] = m_IconCol[0];
		m_IconCol[0] = RepCol;
		break;
	}
}