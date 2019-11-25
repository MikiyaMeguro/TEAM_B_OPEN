//=============================================================================
//
// ステージセレクト処理 [StageSelect.cpp]
// Author : 目黒 未来也/後閑 茜
//
//=============================================================================
#include "StageSelect.h"
#include "manager.h"
#include "light.h"
#include "CameraManager.h"
#include "camera.h"
#include "scene3D.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "SetObject.h"
#include "object.h"
#include "meshField.h"
#include "wall.h"
#include <time.h>

//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)
#define SIZE_Y (SCREEN_HEIGHT/2)
#define DEFAULT_SIZE (150.0f)														//ポリゴンサイズの基本の大きさ
#define DEFAULT_POS (D3DXVECTOR3(SIZE_X,SIZE_Y,0.0f))								//初期化位置
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))									//初期化回転
#define DEFAULT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))							//初期化色_白
#define STAGESELCHOICE_POS	(D3DXVECTOR3(300.0f,130.0f,0.0f))						//選択肢ポリゴンの位置
#define STAGESELCHOICE_INTERVAL (350.0f)											//選択肢ポリゴン同士の間隔
#define STAGESEL_DIFF (0.3f)														//移動の変化量
#define MACHINE_STAGE_MACHINE	("data\\TEXT\\機械ステージ\\Machine_Stage_0.txt")	//機械ステージ
#define MACHINE_STAGE_WEATHER	("data\\TEXT\\天候ステージ\\Machine_Stage_0.txt")	//天候ステージ
#define MACHINE_STAGE_TIKEI	("data\\TEXT\\機械ステージ\\Machine_Stage_0.txt")		//地形

//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CStageSelect::m_apScene2D[MAX_STAGESELECT_TEX] = {};
CScene2D *CStageSelect::m_apSelect2D[MAX_STAGESELECT] = {};
CScene2D *CStageSelect::m_pMask2D = NULL;
CMeshField *CStageSelect::m_pMeshField = NULL;
CWall *CStageSelect::m_pWall = NULL;
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
	m_bLoad = false;
	m_CameraRot = DEFAULT_ROT;
	m_CameraPosV = DEFAULT_POS;
	m_CameraPosR = DEFAULT_POS;
	m_MaskFade = MASKFADE_NONE;
	m_fMaskAlpha = 0.05f;
	m_pObj = NULL;
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		m_SelectPos[nCnt] = DEFAULT_POS;
		m_IconCol[nCnt] = DEFAULT_COL_WHITE;
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

	//カメラの設定
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("STAGESELECT_CAMERA", CCamera::TYPE_SPECTOR, D3DXVECTOR3(20.0f, 1500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 1000.0f);
	pCameraManager->SetCameraViewPort("STAGESELECT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("STAGESELECT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	}

	m_pcStageSelect[0] = MACHINE_STAGE_MACHINE;
	m_pcStageSelect[1] = MACHINE_STAGE_WEATHER;
	m_pcStageSelect[2] = MACHINE_STAGE_TIKEI;

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
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CCamera *pCamera = pCameraManager->GetCamera("STAGESELECT_CAMERA");

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	if (pFade->GetFade() == CFade::FADE_NONE)
	{

		/* 選択処理 */
		if (CCommand::GetCommand("RIGHT"))
		{//右
			if (m_MoveIconState == SELECTICON_STATE_NONE)
			{//移動処理中に数値が変わらないようにする
				//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
				m_nSelect = (m_nSelect + 1) % MAX_STAGESELECT;
				m_MoveIconState = SELECTICON_STATE_MOVE_R;
			}
		}
		else if (CCommand::GetCommand("LEFT"))
		{//左
			if (m_MoveIconState == SELECTICON_STATE_NONE)
			{//移動処理中に数値が変わらないようにする
				//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
				m_nSelect = (m_nSelect + (MAX_STAGESELECT - 1)) % MAX_STAGESELECT;
				m_MoveIconState = SELECTICON_STATE_MOVE_L;
			}
		}

		//選択番号を状態変数に反映し、状態にあわせて処理を行う
		ProductionIcon(m_MoveIconState, m_type);
		if (m_MoveIconState == SELECTICON_STATE_NONE)
		{//移動が完了したら
			m_type = (SELECTTYPE)m_nSelect;
			Selecttype(m_type, pFade, pManager);
		}
		if (pCamera != NULL)
		{
			m_CameraRot.y = pCamera->GetRotation().y;
			m_CameraPosV = pCamera->GetPosV();
			m_CameraPosR = pCamera->GetPosR();
			m_CameraRot.y += 0.001f;
			m_CameraPosV.x = m_CameraPosR.x + sinf(m_CameraRot.y - D3DX_PI) * pCamera->GetLength();
			m_CameraPosV.z = m_CameraPosR.z + cosf(m_CameraRot.y - D3DX_PI) * pCamera->GetLength();

			pCamera->SetRotation(D3DXVECTOR3(0.0f, m_CameraRot.y, 0.0f));
			pCamera->SetPosV(m_CameraPosV);

		}
		/* マスクのフェード処理 */
		MaskFade();
	}
	/* 帯のテクスチャスクロール */
	ScrollMenu(STAGESELECTTYPE_BAND_R, 0.005f);
	ScrollMenu(STAGESELECTTYPE_BAND_L, -0.005f);

#ifdef _DEBUG
	CDebugProc::Print("c", "ステージセレクト");
	CDebugProc::Print("cn", "m_MoveIconState:", m_MoveIconState);
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
	CDebugProc::Print("cf", "カメラRot : ", m_CameraRot.y);
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
	m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.8f, DEFAULT_SIZE*1.3f);
	m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.3f, DEFAULT_SIZE*1.0f);
	m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.3f, DEFAULT_SIZE*1.0f);

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

	//字幕枠
	m_apScene2D[STAGESELECTTYPE_FRAME] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SCREEN_HEIGHT-90.0f, 0.0f), "FRAME");
	m_apScene2D[STAGESELECTTYPE_FRAME]->SetWidthHeight(DEFAULT_SIZE*5.0f, DEFAULT_SIZE*0.8f);

	//マスク
	m_pMask2D = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0.0f), " ",2);
	m_pMask2D->SetWidthHeight(DEFAULT_SIZE*5.2f, DEFAULT_SIZE*4.0f);
	m_pMask2D->SetCol(DEFAULT_COL_WHITE);
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
void CStageSelect::Selecttype(CStageSelect::SELECTTYPE TYPE, CFade *pFade, CManager *pManager)
{
	switch (TYPE)
	{
	case SELECTTYPE_SELECT_MACHINE:	//機械	
	
		//任意のキーENTER
		if (CCommand::GetCommand("DECISION") == true)
		{
			pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
		}
		break;

	case SELECTTYPE_SELECT_WEATHER:	//天候
		if (CCommand::GetCommand("DECISION") == true)
		{
			pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
		}
		break;

	case SELECTTYPE_SELECT_TERRAIN:	//地形
		if (CCommand::GetCommand("DECISION") == true)
		{
			//pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
		}
		break;
	}
	if (m_bLoad == false)
	{
		if (m_MaskFade == MASKFADE_NONE)
		{
			StageLoadState(STAGELOAD_LOAD, m_nSelect);
			m_bLoad = true;
		}
	}
	else if (m_bLoad == true)
	{
		if (m_MaskFade == MASKFADE_IN)
		{
			StageLoadState(STAGELOAD_UNLOAD, m_nSelect);
			m_bLoad = false;
		}
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

	case SELECTICON_STATE_MOVE_R:			//右回転
		if (m_bRep == false)
		{//最初の１回だけ数値の入れ替えを行う
			Replacement(state);
			m_bRep = true;
			m_MaskFade = MASKFADE_IN;
		}
		for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
		{
			//移動後と移動前の位置とサイズの差を計算する
			fDiffpos[nCnt] = m_SelectPos[nCnt].x - m_apSelect2D[nCnt]->GetPosition().x;
			fDiffScal[nCnt] = D3DXVECTOR2(m_fWidth[nCnt] - m_apSelect2D[nCnt]->GetSize(0), m_fHeight[nCnt] - m_apSelect2D[nCnt]->GetSize(1));
			if (fDiffpos[nCnt] <= 0.0f)
			{//負の値だったら正の値に変換
				fDiffpos[nCnt] *= -1.0f;
			}
			if (fScal[nCnt].x <= 0.0f)
			{//負の値だったら正の値に変換
				fScal[nCnt].x *= -1.0f;
			}
			if (fScal[nCnt].y <= 0.0f)
			{//負の値だったら正の値に変換
				fScal[nCnt].y *= -1.0f;
			}
			//差から移動量を計算
			fmove[nCnt] = fDiffpos[nCnt] - (fDiffpos[nCnt] * STAGESEL_DIFF);
			fScal[nCnt] = D3DXVECTOR2(fDiffScal[nCnt].x - (fDiffScal[nCnt].x*STAGESEL_DIFF), fDiffScal[nCnt].y - (fDiffScal[nCnt].y*STAGESEL_DIFF));

			//位置を反映
			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(m_SelectPos[nCnt].x + fmove[nCnt], m_SelectPos[nCnt].y, m_SelectPos[nCnt].z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fWidth[nCnt] - fScal[nCnt].x, m_fHeight[nCnt] - fScal[nCnt].y);
			m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
		}

		if (fDiffpos[0] <= 1.0f&&fDiffpos[1] <= 1.0f&& fDiffpos[2] <= 1.0f)
		{//差がなくなったら移動完了
			state = SELECTICON_STATE_STOP;
		}
		break;

	case SELECTICON_STATE_MOVE_L:			//左回転
		if (m_bRep == false)
		{//最初の１回だけ数値の入れ替えを行う
			Replacement(state);
			m_bRep = true;
			m_MaskFade = MASKFADE_IN;
		}
		for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
		{
			//移動後と移動前の位置とサイズの差を計算する
			fDiffpos[nCnt] = m_SelectPos[nCnt].x - m_apSelect2D[nCnt]->GetPosition().x;
			fDiffScal[nCnt] = D3DXVECTOR2(m_fWidth[nCnt] - m_apSelect2D[nCnt]->GetSize(0), m_fHeight[nCnt] - m_apSelect2D[nCnt]->GetSize(1));
			if (fDiffpos[nCnt] <= 0.0f)
			{//負の値だったら正の値に変換
				fDiffpos[nCnt] *= -1.0f;
			}
			if (fScal[nCnt].x <= 0.0f)
			{//負の値だったら正の値に変換
				fScal[nCnt].x *= -1.0f;
			}
			if (fScal[nCnt].y <= 0.0f)
			{//負の値だったら正の値に変換
				fScal[nCnt].y *= -1.0f;
			}
			//差から移動量を計算
			fmove[nCnt] = fDiffpos[nCnt] - (fDiffpos[nCnt] * STAGESEL_DIFF);
			fScal[nCnt] = D3DXVECTOR2(fDiffScal[nCnt].x - (fDiffScal[nCnt].x*STAGESEL_DIFF), fDiffScal[nCnt].y - (fDiffScal[nCnt].y*STAGESEL_DIFF));
			
			//位置を反映
			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(m_SelectPos[nCnt].x - fmove[nCnt], m_SelectPos[nCnt].y, m_SelectPos[nCnt].z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fWidth[nCnt] - fScal[nCnt].x, m_fHeight[nCnt] - fScal[nCnt].y);
			m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
		}

		if (fDiffpos[0] <= 1.0f&&fDiffpos[1] <= 1.0f&& fDiffpos[2] <= 1.0f)
		{//差がなくなったら移動完了
			state = SELECTICON_STATE_STOP;
		}
		break;


	case SELECTICON_STATE_STOP:				//回転終了
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
	D3DXCOLOR RepCol = DEFAULT_COL_WHITE;

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
//=============================================================================
// ステージ生成の処理
//=============================================================================
void CStageSelect::SetStage(int nNumState)
{
	m_pObj->LoadFile(m_pcStageSelect[nNumState]);
}
//=============================================================================
// ステージ読み込み
//=============================================================================
void CStageSelect::LoadStage(int nNum)
{
	if (m_pObj == NULL)
	{
		m_pObj = CSetObject::Create();
		SetStage(nNum);
	}

}
//=============================================================================
// ステージの読み込み状況
//=============================================================================
void CStageSelect::StageLoadState(STAGELOAD Load, int nSel)
{
	switch (Load)
	{
	case STAGELOAD_NONE:
		break;

	case STAGELOAD_LOAD:
		LoadStage(m_nSelect);
		//switch (m_nSelect)
		//{
		//case SELECTTYPE_SELECT_MACHINE:
		if (m_pMeshField == NULL)
		{
			m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}
		if (m_pWall == NULL)
		{
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, 400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0);
			m_pWall = CWall::Create(D3DXVECTOR3(0.0f, -100.0f, -400.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0);
			m_pWall = CWall::Create(D3DXVECTOR3(400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0);
			m_pWall = CWall::Create(D3DXVECTOR3(-400.0f, -100.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), D3DXVECTOR3(400.0f, 100.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(5.0f, 5.0f), 0);
		}
		//	break;
		//case SELECTTYPE_SELECT_WEATHER:
		//	break;
		//case SELECTTYPE_SELECT_TERRAIN:
		//	break;
		//}
		m_MaskFade = MASKFADE_OUT;
		break;

	case STAGELOAD_UNLOAD:
		if (m_pObj != NULL)
		{
			m_pObj->UnLoadObj();
			m_pObj = NULL;
		}
		if (m_pMeshField != NULL)
		{
			m_pMeshField->Uninit();
			m_pMeshField = NULL;
		}
		if (m_pWall != NULL)
		{
			m_pWall->Uninit();
			m_pWall = NULL;
		}
		break;
	}
}
//=============================================================================
// マスクのフェード処理
//=============================================================================
void CStageSelect::MaskFade(void)
{
	D3DXCOLOR col = m_pMask2D->GetCol();

	switch (m_MaskFade)
	{
	case MASKFADE_NONE:
		break;

	case MASKFADE_IN:
		if (col.a >= 1.0f)
		{
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, 1.0f));
			m_MaskFade = MASKFADE_NONE;
			m_bLoad = false;
		}
		else
		{
			col.a += m_fMaskAlpha;
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, col.a));
		}
		break;

	case MASKFADE_OUT:
		if (col.a <= 0.0f)
		{
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, 0.0f));
			m_MaskFade = MASKFADE_NONE;
		}
		else
		{
			col.a -= m_fMaskAlpha;
			m_pMask2D->SetCol(D3DXCOLOR(DEFAULT_COL_WHITE.r, DEFAULT_COL_WHITE.g, DEFAULT_COL_WHITE.b, col.a));
		}
		break;
	}
}