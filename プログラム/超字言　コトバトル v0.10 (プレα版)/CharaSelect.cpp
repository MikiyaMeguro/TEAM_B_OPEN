//=============================================================================
//
// キャラセレクト処理 [CharaSelect.cpp]
// Author : 目黒 未来也/後閑　茜
//
//=============================================================================
#include "CharaSelect.h"
#include "manager.h"
#include "debugProc.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include"game.h"
//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//横幅
#define SIZE_Y (SCREEN_HEIGHT/2)								//縦幅
#define DEFAULT_SIZE (150.0f)									//ポリゴンサイズの基本の大きさ
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//ポリゴンの初期位置
#define CHARASELCHOICE_POS	(D3DXVECTOR3(250.0f,180.0f,0.0f))	//選択肢ポリゴンの位置
#define CURSOL_INITPOS (D3DXVECTOR3(250.0f,550.0f,0.0f))		//カーソルの初期位置
#define CHARASELCHOICE_INTERVAL (260.0f)						//選択肢ポリゴン同士の感覚
#define TEX_CORRECTION (0.0001f)								//テクスチャ座標の補正
#define CURSOR_MOVE (3.0f)										//カーソルの移動速度
#define CURSOR_SIZE (0.3f)										//カーソルのサイズ

//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apCursor2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apBadge2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apConfirm2D = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_PlayerNum = NULL;
	m_OperationNum = 0;
	/* 演出系変数初期化 */
	m_nCntScrool = 0;
	m_CntFlash = 0;
	m_CntFadeF = 0;
	m_fFlashAlpha = 1.0f;
	m_moveConfPro = 0.0f;
	m_CnfProState = CONFPRODUCTION_NONE;
	m_bConfProFinish = false;
	m_bConf = false;
	m_bConfProStart = false;
	m_bCnfFlash = false;

	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		m_move[nCnt] = DEFAULT_POS;
		m_SelectState[nCnt] = SELECTSTATE_NOSELECT;
		m_SelectStateold[nCnt] = SELECTSTATE_NOSELECT;
		m_bPCSelMove[nCnt] = false;
		m_CharaType[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeOld[nCnt] = CPlayer::TYPE_MAX;
	}
}

//=============================================================================
//デストラクタ
//=============================================================================
CCharaSelect::~CCharaSelect()
{

}

//=============================================================================
// キャラセレクトの初期化処理
//=============================================================================
void CCharaSelect::Init(void)
{
	//インスタンス
	CManager *pManager = NULL;

	/* ポインタの初期化処理 */
	Initpointer();

	/* ポリゴンの初期設定 */
	InitCharaSelectPoly();

	/* コマンド設定 */
	SetCommand();
}

//=============================================================================
// キャラセレクトの終了処理
//=============================================================================
void CCharaSelect::Uninit(void)
{
	//全ての終了処理
	CScene::ReleseAll();
}

//=============================================================================
// キャラセレクトの更新処理
//=============================================================================
void CCharaSelect::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	D3DXVECTOR3 pos[MAX_CHARASELECT];
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apCursor2D[nCnt] != NULL)
		{
			pos[nCnt] = m_apCursor2D[nCnt]->GetPosition();
		}
	}
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//モード遷移
	if (ConfirmationSelect() == true)
	{//全員選択した
		if (m_bConfProStart == false)
		{
			m_CnfProState = CONFPRODUCTION_MOVE_START;
			m_bConfProStart = true;
		}
		if (m_bConfProStart == true)
		{
			m_bConfProFinish = ProductionConf();
		}
		if (m_bConfProFinish == true)
		{//演出が終了した
			m_bConf = true;	//選択操作可能にする
		}
		if (m_bConf == true)
		{//選択確定が可能になったら
			if (collisionConf(m_OperationNum) == true)
			{//ポリゴンの範囲内
				if (CCommand::GetCommand("ENTER") == true)
				{
					m_bCnfFlash = true;
					CGame::SetCharaSelect(0, m_CharaType[0]);
					CGame::SetCharaSelect(1, m_CharaType[1]);
					CGame::SetCharaSelect(2, m_CharaType[2]);
					CGame::SetCharaSelect(3, m_CharaType[3]);
					pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);

				}
			}
		}
	}
	else
	{//全員選択していない
		m_apConfirm2D->SetbDraw(false);
		m_bConfProFinish = false;
		m_bConf = false;
		m_bConfProStart = false;
	}
	//フェード処理終了後/開始前のみ動く処理
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		/* カーソル移動処理  */
		if (CCommand::GetCommand("RIGHT_R") == true)
		{//左押下
			if (CCommand::GetCommand("UP_R") == true)
			{//上押下
				m_move[m_OperationNum].x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R") == true)
			{//下押下
				m_move[m_OperationNum].x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move[m_OperationNum].x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("LEFT_R") == true)
		{//左押下
			if (CCommand::GetCommand("UP_R") == true)
			{//上押下
				m_move[m_OperationNum].x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R") == true)
			{//下押下
				m_move[m_OperationNum].x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move[m_OperationNum].x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("UP_R") == true)
		{//上押下
			m_move[m_OperationNum].x += sinf(D3DX_PI)*CURSOR_MOVE;
			m_move[m_OperationNum].y += cosf(D3DX_PI)*CURSOR_MOVE;
		}
		else if (CCommand::GetCommand("DOWN_R") == true)
		{//下押下
			m_move[m_OperationNum].x -= sinf(D3DX_PI)*CURSOR_MOVE;
			m_move[m_OperationNum].y -= cosf(D3DX_PI)*CURSOR_MOVE;
		}

		/* 移動範囲制限 */
		pos[m_OperationNum] = MoveRestriction(pos[m_OperationNum]);

		/* 慣性 */
		m_move[m_OperationNum].x += (0.0f - m_move[m_OperationNum].x) * 0.3f;
		m_move[m_OperationNum].y += (0.0f - m_move[m_OperationNum].y) * 0.3f;

		/* 移動 */
		pos[m_OperationNum] += m_move[m_OperationNum];

		/* 移動を反映 */
		m_apCursor2D[m_OperationNum]->SetPosition(pos[m_OperationNum]);

		/* 未選択時のみカーソルに追従 */
		if (m_bPCSelMove[m_OperationNum] == false)
		{
			m_apBadge2D[m_OperationNum]->SetPosition(D3DXVECTOR3(m_apCursor2D[m_OperationNum]->GetPosition().x,
				m_apCursor2D[m_OperationNum]->GetPosition().y - 50.0f,
				m_apCursor2D[m_OperationNum]->GetPosition().z));
		}

		/* 選んだキャラクターを保存 */
		if (collision(m_OperationNum, CPlayer::TYPE_BARANCE) == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{//エンター押下
				if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[m_OperationNum] = CPlayer::TYPE_BARANCE;
					m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[m_OperationNum] = true;
				}
			}
		}
		else if (collision(m_OperationNum, CPlayer::TYPE_POWER) == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{//エンター押下
				if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[m_OperationNum] = CPlayer::TYPE_POWER;
					m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[m_OperationNum] = true;
				}
			}
		}
		else if (collision(m_OperationNum, CPlayer::TYPE_SPEED) == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{//エンター押下
				if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[m_OperationNum] = CPlayer::TYPE_SPEED;
					m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[m_OperationNum] = true;
				}
			}
		}
		else if (collision(m_OperationNum, CPlayer::TYPE_REACH) == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{//エンター押下
				if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[m_OperationNum] = CPlayer::TYPE_REACH;
					m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[m_OperationNum] = true;
				}
			}
		}
		/* 選択取り消し */
		if (CCommand::GetCommand("DELETE") == true)
		{
			if (collision(m_OperationNum, m_CharaType[m_OperationNum]) == true)
			{
				m_CharaType[m_OperationNum] = CPlayer::TYPE_MAX;
				m_SelectState[m_OperationNum] = SELECTSTATE_NOSELECT;
				m_bPCSelMove[m_OperationNum] = false;
			}
		}
	}
	/* 帯のテクスチャスクロール */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* 選択時演出関数 */
	SelectProduction(m_SelectState[m_OperationNum], m_SelectStateold[m_OperationNum], m_CharaType[m_OperationNum]);

	/* 確定ポリのフラッシュ演出 */
	if (m_bCnfFlash == true) { FlashConf(); }
#ifdef _DEBUG
	CDebugProc::Print("c", "キャラセレクト");
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		m_OperationNum = 0;
	}
	else if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		m_OperationNum = 1;
	}
	else if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		m_OperationNum = 2;
	}
	else if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		m_OperationNum = 3;
	}

#endif
}

//=============================================================================
// キャラセレクトの描画処理
//=============================================================================
void CCharaSelect::Draw(void)
{

}

//=============================================================================
// ポインタの初期化処理
//=============================================================================
void CCharaSelect::Initpointer(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL)
		{
			m_apSelect2D[nCnt] = NULL;
		}
	}
}
//=============================================================================
// 横の文字スクロール処理
//=============================================================================
void CCharaSelect::ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;
	if (m_apScene2D[type] != NULL)
	{
		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)), 
									D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}
//=============================================================================
// 選択演出処理
//=============================================================================
void CCharaSelect::SelectProduction(SELECT_STATE &Sel, SELECT_STATE &Selold,CPlayer::PLAYER_TYPE type)
{
	switch (Sel)
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//演出中
		if (Selold != SELECTSTATE_FLASH)
		{//前回のモードがFlash以外の場合a値を初期化
			m_fFlashAlpha = 1.0f;
		}
		m_apScene2D[m_OperationNum+7]->SetbDraw(true);											//マスクの描画する
		m_apScene2D[m_OperationNum + 7]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha));	//色
		CharaSelTex(SELECTSTATE_SELECT, type,m_CharaTypeOld[m_OperationNum]);

		if (m_fFlashAlpha <= 0.0f)
		{//透明度が下がり切った
			m_apScene2D[m_OperationNum + 7]->SetbDraw(false);								//マスクを描画しない状況に
			m_apScene2D[m_OperationNum + 7]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//マスクの色を城に戻しておく
			m_fFlashAlpha = 0.0f;												//a値を綺麗な数字に変更
			m_SelectState[type] = SELECTSTATE_SELECT;							//選択された状態に変更
		}
		else
		{
			m_fFlashAlpha -= 0.02f;
			m_apScene2D[m_OperationNum + 7]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha));
		}
		break;

	case SELECTSTATE_SELECT:	//選択されている
		break;

	case SELECTSTATE_NOSELECT:	//選択されていない
		m_apScene2D[m_OperationNum + 7]->SetbDraw(false);		//マスクを描画されていない状態に
		CharaSelTex(SELECTSTATE_NOSELECT, type,m_CharaTypeOld[m_OperationNum]);
		break;
	}

	//今回の選択状態を前回の選択状態として保存
	Selold = Sel;
}
//=============================================================================
// ポリゴンの初期設定
//=============================================================================
void CCharaSelect::InitCharaSelectPoly(void)
{
	/* プレイヤーの人数取得 */
	m_PlayerNum = CPlayerSelect::GetModeSelectMode();

	/* 選択肢 */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* 生成と座標とテクスチャ */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CHARASELCHOICE_POS.y,
			CHARASELCHOICE_POS.z), "CHARACTORSEL_CHARA");
		/* テクスチャ座標設定 */
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.0f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 0.499f));
		/* サイズ設定 */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.0f);
	}

	/* 演出 */
	// 背景
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAUERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//モード名帯（左）
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//モード名帯（右）
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		//プレイヤーウィンド
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 3] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			550.0f,
			CURSOL_INITPOS.z), "PLAYER_UIWINDOW");
		/* サイズ設定 */
		m_apScene2D[nCnt + 3]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.5f);
		m_apScene2D[nCnt + 3]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));//初期設定は全部COM、下のSWICHで再設定

		// 選択肢のマスク
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 7] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), " ");
		/* サイズ設定 */
		m_apScene2D[nCnt + 7]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.5f);
		m_apScene2D[nCnt + 7]->SetbDraw(false);

		//バッジ
		m_apBadge2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE", 4);
		m_apBadge2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		//カーソル
		m_apCursor2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE", 4);
		m_apCursor2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		/* プレイヤー人数に合わせて設定 */
		if (nCnt < (int)*m_PlayerNum)
		{
			//カーソルとバッジ
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.5f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.0f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 0.5f));
			// プレイヤーウィンドウのテクスチャ座標
			m_apScene2D[nCnt + 3]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nCnt), D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nCnt));
		}
		else
		{
			//カーソルとバッジ
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			// プレイヤーウィンドウのテクスチャ座標
			m_apScene2D[nCnt + 3]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));
		}
	}
	
	/* キャラ選択確定 */
	m_apConfirm2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "PLAYER_CONFIRM");
	m_apConfirm2D->SetWidthHeight(DEFAULT_SIZE*4.5f, DEFAULT_SIZE*0.8f);
	m_apConfirm2D->SetbDraw(false);
}
//=============================================================================
// カーソルの移動制限
//=============================================================================
D3DXVECTOR3 CCharaSelect::MoveRestriction(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 mPos;
	mPos = pos;

	if (pos.y <= 0.0f + (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.y = 0.0f + (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.y >= SCREEN_HEIGHT - (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.y = SCREEN_HEIGHT - (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.x <= 100.0f + (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.x = 100.0f + (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.x >= 1180.0f - (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.x = 1180.0f - (DEFAULT_SIZE*CURSOR_SIZE);
	}

	return mPos;
}
//=============================================================================
// あたり判定
//=============================================================================
bool CCharaSelect::collision(int operation, CPlayer::PLAYER_TYPE type)
{
	bool bColl = false;

	/* あたり判定 */
	if (m_apBadge2D[operation]->GetPosition().x - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().x + (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D[operation]->GetPosition().x + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().x - (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D[operation]->GetPosition().y + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().y - (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D[operation]->GetPosition().y - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().y + (DEFAULT_SIZE*1.0f))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// コマンドの設定
//=============================================================================
void CCharaSelect::SetCommand(void)
{
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT);

	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);
	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_UP);
	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_W);
	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_UP);

	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_DOWN);

	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_BACKSPACE);
}

//=============================================================================
// テクスチャ座標管理
//=============================================================================
void CCharaSelect::CharaSelTex(SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type, CPlayer::PLAYER_TYPE &typeOld)
{
	switch (type)
	{/* 選ばれた時のテクスチャ座標 */
	case CPlayer::TYPE_BARANCE:	//バランス
		m_apSelect2D[0]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_BARANCE), 0.5f + TEX_CORRECTION),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_BARANCE) - TEX_CORRECTION, 1.0f));
		break;

	case CPlayer::TYPE_POWER:	//パワー
		m_apSelect2D[1]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_POWER), 0.5f + TEX_CORRECTION),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_POWER) - TEX_CORRECTION, 1.0f));
		break;
		
	case CPlayer::TYPE_SPEED:	//スピード
		m_apSelect2D[2]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_SPEED), 0.5f + TEX_CORRECTION),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_SPEED) - TEX_CORRECTION, 1.0f));
		break;

	case CPlayer::TYPE_REACH:	//リーチ
		m_apSelect2D[3]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_REACH), 0.5f + TEX_CORRECTION),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_REACH), 1.0f));
		break;

	case CPlayer::TYPE_MAX:
		/* 選ばれていない状態は前回のタイプから見てテクスチャ座標を変更する */
		switch (typeOld)
		{
		case CPlayer::TYPE_BARANCE:	//バランス
			m_apSelect2D[0]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_BARANCE), 0.0f),
				D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_BARANCE) - TEX_CORRECTION, 0.499f));
			break;
		case CPlayer::TYPE_POWER:	//パワー
			m_apSelect2D[1]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_POWER), 0.0f),
				D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_POWER) - TEX_CORRECTION, 0.499f));
			break;
		case CPlayer::TYPE_SPEED:	//スピード
			m_apSelect2D[2]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_SPEED), 0.0f),
				D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_SPEED), 0.499f));
			break;
		case CPlayer::TYPE_REACH:	//リーチ
			m_apSelect2D[3]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_REACH), 0.0f),
				D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT) * CPlayer::TYPE_REACH), 0.499f));
			break;
		}
		break;
	}

	//前回の種類を現在の種類に書き換える
	typeOld = type;
}
//=============================================================================
// プレイヤーが全員選択したか確認する
//=============================================================================
bool CCharaSelect::ConfirmationSelect(void)
{
	bool bCnfirmation = false;
	int nCount = 0;
	for (int nCnt = 0; nCnt < (int)*m_PlayerNum; nCnt++)
	{
		if (m_bPCSelMove[nCnt] == true)
		{
			nCount++;
		}
	}

	if (nCount == (int)*m_PlayerNum)
	{
		bCnfirmation = true;
	}
	return bCnfirmation;
}
//=============================================================================
// あたり判定
//=============================================================================
bool CCharaSelect::collisionConf(int operation)
{
	bool bColl = false;

	/* あたり判定 */
	if (m_apCursor2D[operation]->GetPosition().x - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apConfirm2D->GetPosition().x + (DEFAULT_SIZE*3.0f) &&
		m_apCursor2D[operation]->GetPosition().x + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apConfirm2D->GetPosition().x - (DEFAULT_SIZE*3.0f) &&
		m_apCursor2D[operation]->GetPosition().y + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apConfirm2D->GetPosition().y - (DEFAULT_SIZE*0.8f) &&
		m_apCursor2D[operation]->GetPosition().y - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apConfirm2D->GetPosition().y + (DEFAULT_SIZE*0.8f))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// 確定ポリの演出
//=============================================================================
bool CCharaSelect::ProductionConf(void)
{
	bool bFinish = false;
	D3DXVECTOR3 pos= m_apConfirm2D->GetPosition();
	switch (m_CnfProState)
	{
	case CONFPRODUCTION_NONE:
		break;

	case CONFPRODUCTION_MOVE_START:
		m_apConfirm2D->SetPosition(D3DXVECTOR3(0.0f- DEFAULT_SIZE*5.1f, SCREEN_HEIGHT / 2, 0.0f));
		m_apConfirm2D->SetbDraw(true);
		m_moveConfPro = 100.0f;
		m_CnfProState = CONFPRODUCTION_MOVE;
		break;

	case CONFPRODUCTION_MOVE:
		pos.x += m_moveConfPro;
		if (m_apConfirm2D->GetPosition().x >= SCREEN_WIDTH/2 - 50.0f)
		{
			m_CnfProState = CONFPRODUCTION_MOVE_END;
			m_moveConfPro = 0.0f;
		}
		else
		{
			m_apConfirm2D->SetPosition(pos);
		}
		break;

	case CONFPRODUCTION_MOVE_END:
		m_CnfProState = CONFPRODUCTION_NONE;
		m_apConfirm2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		bFinish = true;
		break;
	}
	return bFinish;
}
//=============================================================================
// 確定ポリの点滅処理
//=============================================================================
void CCharaSelect::FlashConf(void)
{
	m_CntFlash++;
	if (m_CntFlash >= 3)
	{
		m_apConfirm2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		m_CntFlash = 0;
	}
	else
	{
		m_apConfirm2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
}