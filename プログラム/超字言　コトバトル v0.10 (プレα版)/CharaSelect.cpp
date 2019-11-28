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
#define CHARASELCHOICE_POS	(D3DXVECTOR3(211.0f,230.0f,0.0f))	//選択肢ポリゴンの位置
#define CURSOL_INITPOS (D3DXVECTOR3(250.0f,545.0f,0.0f))		//カーソルの初期位置
#define CHARASELCHOICE_INTERVAL (260.0f)						//選択肢ポリゴン同士の間隔
#define CHARASELICON_INTERVAL (215.0f)							//選択肢アイコン同士の間隔
#define TEX_CORRECTION (0.001f)									//テクスチャ座標の補正
#define CURSOR_MOVE (3.0f)										//カーソルの移動速度
#define CURSOR_SIZE (0.3f)										//カーソルのサイズ

//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apCursor2D[MAX_PLAYER] = {};
CScene2D *CCharaSelect::m_apBadge2D[MAX_PLAYER] = {};
CScene2D *CCharaSelect::m_apConfirm2D = NULL;
CScene2D *CCharaSelect::m_apGauge2D[MAX_PLAYER] = {};

//=============================================================================
//	コンストラクタ
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_PlayerNum = NULL;
	/* 演出系変数初期化 */
	m_nCntScrool = 0;
	m_CntFlash = 0;
	m_CntFadeF = 0;
	m_moveConfPro = 0.0f;
	m_CnfProState = CONFPRODUCTION_NONE;
	m_bConfProFinish = false;
	m_bConf = false;
	m_bConfProStart = false;
	m_bCnfFlash = false;
	m_bCharaCard = false;
	m_CharaCardProduction = CHARACARDPRO_START;
	m_fCharaCardPro_FinishWH[0] = 0.0f;
	m_fCharaCardPro_FinishWH[1] = 0.0f;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_fFlashAlpha[nCnt] = 0.0f;
		m_fGaugeSizeX[nCnt] = 0.0f;
		m_fMaxGaugeX[nCnt]= 0.0f;
		m_nCntGauge[nCnt] = 0;
		m_move[nCnt] = DEFAULT_POS;
		m_SelectState[nCnt] = SELECTSTATE_NOSELECT;
		m_SelectStateold[nCnt] = SELECTSTATE_NOSELECT;
		m_bPCSelMove[nCnt] = false;
		m_CharaType[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeOld[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeFinal[nCnt] = CPlayer::TYPE_MAX;
		m_bBackMode[nCnt] = false;
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		m_CharaCardPro_FinishPos[nCnt] = DEFAULT_POS;
		m_fCardWidth[nCnt][0] = m_fCharaCardPro_FinishWH[0];
		m_fCardWidth[nCnt][1] = m_fCharaCardPro_FinishWH[1];
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
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL)
		{
			m_apSelect2D[nCnt]->Uninit();
			m_apSelect2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apCursor2D[nCnt] != NULL)
		{
			m_apCursor2D[nCnt]->Uninit();
			m_apCursor2D[nCnt] = NULL;
		}
		if (m_apBadge2D[nCnt] != NULL)
		{
			m_apBadge2D[nCnt]->Uninit();
			m_apBadge2D[nCnt] = NULL;
		}
		if (m_apGauge2D[nCnt] != NULL)
		{
			m_apGauge2D[nCnt]->Uninit();
			m_apGauge2D[nCnt] = NULL;
		}
	}
	if (m_apConfirm2D != NULL)
	{
		m_apConfirm2D->Uninit();
		m_apConfirm2D = NULL;
	}

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
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	/*カード演出*/
	if (m_bCharaCard == false)
	{
		ProductionCard();
	}

	if (ConfirmationSelect() == true)
	{//全員選択した
		if (m_bConfProStart == false)
		{//演出が始まっていなかったら始める
			m_CnfProState = CONFPRODUCTION_MOVE_START;
			m_bConfProStart = true;
		}
		if (m_bConfProStart == true)
		{//演出が始まったら
			m_bConfProFinish = ProductionConf();
		}
		if (m_bConfProFinish == true)
		{//演出が終了した

			m_bConf = true;	//選択操作可能にする
		}
	}
	else
	{//全員選択していない
		m_apConfirm2D->SetbDraw(false);
		m_bConfProFinish = false;
		m_bConf = false;
		m_bConfProStart = false;
	}
	//モード遷移
	if (m_bCharaCard == true)
	{
		for (int nCntXinput = 0; nCntXinput < (int)*m_PlayerNum; nCntXinput++)
		{
			Move(pFade, pManager, nCntXinput);
		}
	}

	/* 帯のテクスチャスクロール */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* 確定ポリのフラッシュ演出 */
	if (m_bCnfFlash == true) { FlashConf(); }
#ifdef _DEBUG
	CDebugProc::Print("c", "キャラセレクト");
#endif
}

//=============================================================================
// キャラセレクトの描画処理
//=============================================================================
void CCharaSelect::Draw(void)
{

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
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_X);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_LEFT_SHOULDER);

	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RETURN);
	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_A);
	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_BACKSPACE);
	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

}

//=============================================================================
// ポインタの初期化処理
//=============================================================================
void CCharaSelect::Initpointer(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL) { m_apScene2D[nCnt] = NULL; }
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL) { m_apSelect2D[nCnt] = NULL; }
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apCursor2D[nCnt] != NULL) { m_apCursor2D[nCnt] = NULL; }
		if (m_apBadge2D[nCnt] != NULL) { m_apBadge2D[nCnt] = NULL; }
		if (m_apGauge2D[nCnt] != NULL) { m_apGauge2D[nCnt] = NULL; }
	}
	if (m_apConfirm2D != NULL) { m_apConfirm2D = NULL; }
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
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELICON_INTERVAL*nCnt),
			CHARASELCHOICE_POS.y,
			CHARASELCHOICE_POS.z), "PLAYERSELECT_BACK");
		/* サイズ設定 */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);

		m_CharaCardPro_FinishPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();
		m_fCharaCardPro_FinishWH[0] = m_apSelect2D[nCnt]->GetSize(0);
		m_fCharaCardPro_FinishWH[1] = m_apSelect2D[nCnt]->GetSize(1);
		m_fCardWidth[nCnt][0] = m_apSelect2D[nCnt]->GetSize(0);
		m_fCardWidth[nCnt][1] = m_apSelect2D[nCnt]->GetSize(1);
	}

	/* 演出 */
	// 背景
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAYERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//モード名帯（左）
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//モード名帯（右）
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//戻る
	m_apScene2D[3] = CScene2D::Create(D3DXVECTOR3(SIZE_X, (DEFAULT_SIZE*0.4f) / 2, 0.0f), "CHARASEL_BACKMODE");
	m_apScene2D[3]->SetWidthHeight(DEFAULT_SIZE*5.2f, DEFAULT_SIZE*0.4f);
	m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//プレイヤーウィンド
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 4] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "PLAYER_UIWINDOW", 2);
		/* サイズ設定 */
		m_apScene2D[nCnt + 4]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));//初期設定は全部COM、下のSWICHで再設定

		// プレイヤーウィンドマスク
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 8] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), " ");
		/* サイズ設定 */
		m_apScene2D[nCnt + 8]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 8]->SetbDraw(false);

		//プレイヤーウィンドウに表示するキャラクター
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 12] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y + 20.0f,
			CURSOL_INITPOS.z), "CHARACTORSEL_CHARA", 2);
		/* サイズ設定 */
		m_apScene2D[nCnt + 12]->SetWidthHeight(DEFAULT_SIZE*1.1f, DEFAULT_SIZE*1.2f);
		m_apScene2D[nCnt + 12]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 1.0f));
		m_apScene2D[nCnt + 12]->SetbDraw(false);

		//バッジ
		m_apBadge2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE");
		m_apBadge2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		//カーソル
		m_apCursor2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE", 4);
		m_apCursor2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		//戻る長押し時のゲージ
		m_apGauge2D[nCnt] = CScene2D::Create(D3DXVECTOR3(m_apCursor2D[nCnt]->GetPosition().x-45.0f,
			m_apCursor2D[nCnt]->GetPosition().y+50.0f,
			m_apCursor2D[nCnt]->GetPosition().z), " ", 4);
		m_apGauge2D[nCnt]->SetScene2DLeftCenter(m_apGauge2D[nCnt]->GetPosition(), DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*0.03f);
		m_apGauge2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_fMaxGaugeX[nCnt] = m_apGauge2D[nCnt]->GetSize(0);
		m_apGauge2D[nCnt]->SetbDraw(false);

		/* プレイヤー人数に合わせて設定 */
		if (nCnt < (int)*m_PlayerNum)
		{
			//カーソルとバッジ
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.5f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.0f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 0.5f));
			// プレイヤーウィンドウのテクスチャ座標
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nCnt), D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nCnt));
		}
		else
		{
			//カーソルとバッジ
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			// プレイヤーウィンドウのテクスチャ座標
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));
		}
	}

	/* キャラ選択確定 */
	m_apConfirm2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "PLAYER_CONFIRM");
	m_apConfirm2D->SetWidthHeight(DEFAULT_SIZE*4.5f, DEFAULT_SIZE*0.8f);
	m_apConfirm2D->SetbDraw(false);
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
void CCharaSelect::SelectProduction(int nNum, SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type)
{
	switch (Sel)
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//演出中
		if (Selold != SELECTSTATE_FLASH)
		{//前回のモードがFlash以外の場合a値を初期化
			m_fFlashAlpha[nNum] = 1.0f;
		}
		m_apScene2D[nNum + 8]->SetbDraw(true);											//マスクの描画する
		m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[nNum]));	//色
		CharaSelTex(nNum, SELECTSTATE_SELECT, type, m_CharaTypeOld[nNum]);

		if (m_fFlashAlpha[nNum] <= 0.0f)
		{//透明度が下がり切った
			m_apScene2D[nNum + 8]->SetbDraw(false);								//マスクを描画しない状況に
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//マスクの色を城に戻しておく
			m_fFlashAlpha[nNum] = 0.0f;												//a値を綺麗な数字に変更
			m_SelectState[type] = SELECTSTATE_SELECT;							//選択された状態に変更
		}
		else
		{
			m_fFlashAlpha[nNum] -= 0.02f;
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[nNum]));
		}
		break;

	case SELECTSTATE_SELECT:	//選択されている
		if (m_apScene2D[nNum + 8]->GetbDraw() != false)
		{
			m_apScene2D[nNum + 8]->SetbDraw(false);
		}
		break;

	case SELECTSTATE_NOSELECT:	//選択されていない
		if (m_apScene2D[nNum + 8]->GetbDraw() != false)
		{
			m_apScene2D[nNum + 8]->SetbDraw(false);
		}
		CharaSelTex(nNum, SELECTSTATE_NOSELECT, type, m_CharaTypeOld[nNum]);
		break;
	}

	//今回の選択状態を前回の選択状態として保存
	Selold = Sel;
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
	if (m_apBadge2D[operation]->GetPosition().x - (m_apBadge2D[operation]->GetSize(0) / 2) <= m_apSelect2D[type]->GetPosition().x + (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apBadge2D[operation]->GetPosition().x + (m_apBadge2D[operation]->GetSize(0) / 2) >= m_apSelect2D[type]->GetPosition().x - (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apBadge2D[operation]->GetPosition().y + (m_apBadge2D[operation]->GetSize(1) / 2) >= m_apSelect2D[type]->GetPosition().y - (m_apSelect2D[operation]->GetSize(1) / 2) &&
		m_apBadge2D[operation]->GetPosition().y - (m_apBadge2D[operation]->GetSize(1) / 2) <= m_apSelect2D[type]->GetPosition().y + (m_apSelect2D[operation]->GetSize(1) / 2))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// テクスチャ座標管理
//=============================================================================
void CCharaSelect::CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type, CPlayer::PLAYER_TYPE &typeOld)
{
	switch (Sel)
	{/* 選ばれた時のテクスチャ座標 */
	case SELECTSTATE_SELECT:	//選ばれている
		m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.2f + (1.0f / 5)*(int)type, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.4f + (1.0f / 5)*(int)type, 0.2f + (1.0f / 5)*nNum));
		if (type == CPlayer::TYPE_MAX)
		{//ランダムの場合
			m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
				D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
		}
		break;
	case SELECTSTATE_NOSELECT:
		m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
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
	if (m_apCursor2D[operation]->GetPosition().x - (m_apCursor2D[operation]->GetSize(0) / 2) <= m_apConfirm2D->GetPosition().x + m_apConfirm2D->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().x + (m_apCursor2D[operation]->GetSize(0) / 2) >= m_apConfirm2D->GetPosition().x - m_apConfirm2D->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().y + (m_apCursor2D[operation]->GetSize(1) / 2) >= m_apConfirm2D->GetPosition().y - m_apConfirm2D->GetSize(1) &&
		m_apCursor2D[operation]->GetPosition().y - (m_apCursor2D[operation]->GetSize(1) / 2) <= m_apConfirm2D->GetPosition().y + m_apConfirm2D->GetSize(1))
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
		m_apConfirm2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		if (m_fFlashAlpha[0] <= 0.0f&&m_fFlashAlpha[1] <= 0.0f&&m_fFlashAlpha[2] <= 0.0f&&m_fFlashAlpha[3] <= 0.0f)
		{
			m_CnfProState = CONFPRODUCTION_NONE;
			bFinish = true;
		}
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
//=============================================================================
// キャラ選択カードの演出処理
//=============================================================================
void CCharaSelect::ProductionCard(void)
{
	D3DXVECTOR3 pos = DEFAULT_POS;
	bool bFinish[MAX_CHARASELECT] = { false };
	switch (m_CharaCardProduction)
	{
	case CHARACARDPRO_NONE:			//何もしない
		break;

	case CHARACARDPRO_START:		//開始
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(-1.0f, m_CharaCardPro_FinishPos[nCnt].y, DEFAULT_POS.z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
		}
		m_CharaCardProduction = CHARACARDPRO_MOVE;
		break;

	case CHARACARDPRO_MOVE:			//移動
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			pos = m_apSelect2D[nCnt]->GetPosition();
			if (pos.x >= m_CharaCardPro_FinishPos[nCnt].x)
			{
				m_apSelect2D[nCnt]->SetPosition(m_CharaCardPro_FinishPos[nCnt]);
			}
			else
			{
				pos.x += 10.0f + nCnt;
				m_apSelect2D[nCnt]->SetPosition(pos);
			}
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
		}
		if (m_apSelect2D[4]->GetPosition().x == m_CharaCardPro_FinishPos[4].x)
		{
			m_CharaCardProduction = CHARACARDPRO_TURNOVER_B;
		}
		break;

	case CHARACARDPRO_TURNOVER_B:	//裏返す

		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_fCardWidth[nCnt][0] -= 10.0f;
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCardWidth[nCnt][0], m_fCharaCardPro_FinishWH[1]);
			if (m_fCardWidth[nCnt][0] <= 0.0f)
			{
				m_apSelect2D[nCnt]->BindTexture("CHARACTORSEL_CHARA");
				m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt),0.0f),
					D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt),0.5f));
				m_CharaCardProduction = CHARACARDPRO_FACEUP;
			}
		}
		break;

	case CHARACARDPRO_FACEUP:		//表面になる
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_fCardWidth[nCnt][0] += 10.0f;
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCardWidth[nCnt][0], m_fCharaCardPro_FinishWH[1]);
			if (m_fCardWidth[nCnt][0] >= m_fCharaCardPro_FinishWH[0])
			{
				m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
				bFinish[nCnt] = true;
			}
		}
		if (bFinish[0] == true&& bFinish[1] == true&& bFinish[2] == true&& bFinish[3] == true&& bFinish[4] == true)
		{
			m_CharaCardProduction = CHARACARDPRO_FINISH;
		}
		break;

	case CHARACARDPRO_FINISH:		//終了
		m_bCharaCard = true;
		m_CharaCardProduction = CHARACARDPRO_NONE;
		break;
	}
}
//=============================================================================
// モード戻るポリゴンとのあたり判定
//=============================================================================
bool CCharaSelect::collisionBackMode(int operation)
{
	bool bColl = false;

	/* あたり判定 */
	if (m_apCursor2D[operation]->GetPosition().x - (m_apCursor2D[operation]->GetSize(0) / 2) <= m_apScene2D[3]->GetPosition().x + m_apScene2D[3]->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().x + (m_apCursor2D[operation]->GetSize(0) / 2) >= m_apScene2D[3]->GetPosition().x - m_apScene2D[3]->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().y + (m_apCursor2D[operation]->GetSize(1) / 2) >= m_apScene2D[3]->GetPosition().y - m_apScene2D[3]->GetSize(1) &&
		m_apCursor2D[operation]->GetPosition().y - (m_apCursor2D[operation]->GetSize(1) / 2) <= m_apScene2D[3]->GetPosition().y + m_apScene2D[3]->GetSize(1))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// 戻る長押し中ゲージの処理
//=============================================================================
void CCharaSelect::PressGauge(CFade *pFade, CManager *pManager, int operation)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
	if (m_apGauge2D[operation]->GetbDraw() == true)
	{
		if (CCommand::GetCommand("RELEASE_L", operation) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT01);
			m_nCntGauge[operation]++;
			if (m_nCntGauge[operation] >= 90)
			{//3秒経ったら
				pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
			}
		}
		else if (CCommand::GetCommand("RELEASE_L", operation) == false)
		{
			m_nCntGauge[operation] --;
			if (m_nCntGauge[operation] <= 0)
			{
				m_nCntGauge[operation] = 0;
			}
		}
		m_fGaugeSizeX[operation] = (float)m_nCntGauge[operation] / m_fMaxGaugeX[operation];
		m_apGauge2D[operation]->SetScene2DLeftCenter(D3DXVECTOR3(m_apGauge2D[operation]->GetPosition().x-45.0f, m_apGauge2D[operation]->GetPosition().y,m_apGauge2D[operation]->GetPosition().z),
			m_fMaxGaugeX[operation] *m_fGaugeSizeX[operation], m_apGauge2D[operation]->GetSize(1));
	}

	switch (operation)
	{
	case 0:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case 1:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	case 2:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case 3:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(0.9f, 0.9f, 0.0f, 1.0f));
		break;

	}

}
//=============================================================================
// 移動処理
//=============================================================================
void CCharaSelect::Move(CFade *pFade, CManager *pManager, int nControllNum)
{
	D3DXVECTOR3 pos[MAX_CHARASELECT];
	CSound *pSound = CManager::GetSound();		//	音の取得

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{//カーソルの位置を取得
		if (m_apCursor2D[nCnt] != NULL)
		{
			pos[nCnt] = m_apCursor2D[nCnt]->GetPosition();
		}
	}

	//フェード処理終了後/開始前のみ動く処理
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		/* 選択時演出関数 */
		if (m_bConf == false)
		{
			SelectProduction(nControllNum, m_SelectState[nControllNum], m_SelectStateold[nControllNum], m_CharaType[nControllNum]);
		}

		if (m_bConf == true)
		{//選択確定が可能になったら
			DecisionCharactor(pFade, pManager, nControllNum);
		}

		/* カーソル移動処理  */
		if (CCommand::GetCommand("RIGHT_R", nControllNum) == true)
		{//左押下
			if (CCommand::GetCommand("UP_R", nControllNum) == true)
			{//上押下
				m_move[nControllNum].x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
			{//下押下
				m_move[nControllNum].x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move[nControllNum].x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("LEFT_R", nControllNum) == true)
		{//左押下
			if (CCommand::GetCommand("UP_R", nControllNum) == true)
			{//上押下
				m_move[nControllNum].x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
			{//下押下
				m_move[nControllNum].x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move[nControllNum].x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("UP_R", nControllNum) == true)
		{//上押下
			m_move[nControllNum].x += sinf(D3DX_PI)*CURSOR_MOVE;
			m_move[nControllNum].y += cosf(D3DX_PI)*CURSOR_MOVE;
		}
		else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
		{//下押下
			m_move[nControllNum].x -= sinf(D3DX_PI)*CURSOR_MOVE;
			m_move[nControllNum].y -= cosf(D3DX_PI)*CURSOR_MOVE;
		}

		/* 移動範囲制限 */
		pos[nControllNum] = MoveRestriction(pos[nControllNum]);

		/* 慣性 */
		m_move[nControllNum].x += (0.0f - m_move[nControllNum].x) * 0.3f;
		m_move[nControllNum].y += (0.0f - m_move[nControllNum].y) * 0.3f;

		/* 移動 */
		pos[nControllNum] += m_move[nControllNum];

		/* 移動を反映 */
		m_apCursor2D[nControllNum]->SetPosition(pos[nControllNum]);

		/* 未選択時のみカーソルに追従 */
		if (m_bPCSelMove[nControllNum] == false)
		{
			m_apBadge2D[nControllNum]->SetPosition(D3DXVECTOR3(m_apCursor2D[nControllNum]->GetPosition().x,
				m_apCursor2D[nControllNum]->GetPosition().y - 50.0f,
				m_apCursor2D[nControllNum]->GetPosition().z));
		}
		m_apGauge2D[nControllNum]->SetPosition(D3DXVECTOR3(m_apCursor2D[nControllNum]->GetPosition().x,
			m_apCursor2D[nControllNum]->GetPosition().y + 50.0f,
			m_apCursor2D[nControllNum]->GetPosition().z));

		/* 選んだキャラクターを保存 */
		if (collision(nControllNum, CPlayer::TYPE_BARANCE) == true)
		{//バランス
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.2f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//エンター押下
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[nControllNum] = CPlayer::TYPE_BARANCE;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_POWER) == true)
		{//パワー
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.2f, 0.5f), D3DXVECTOR2(0.4f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//エンター押下
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[nControllNum] = CPlayer::TYPE_POWER;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_SPEED) == true)
		{//スピード
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.4f, 0.5f), D3DXVECTOR2(0.6f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);

			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//エンター押下
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[nControllNum] = CPlayer::TYPE_SPEED;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_REACH) == true)
		{//リーチ
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.6f, 0.5f), D3DXVECTOR2(0.8f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);

			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//エンター押下
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[nControllNum] = CPlayer::TYPE_REACH;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_RANDOM) == true)
		{//ランダム
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);

			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//エンター押下
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//セレクト状態じゃない（無限フラッシュ防止）
					m_CharaType[nControllNum] = CPlayer::TYPE_RANDOM;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else
		{//どの選択肢とも当たっていない場合
			if (m_apScene2D[nControllNum + 12]->GetbDraw() == true) { m_apScene2D[nControllNum + 12]->SetbDraw(false); }
		}
		/* 選択取り消し */
		if (CCommand::GetCommand("DELETE", nControllNum) == true)
		{
			if (collision(nControllNum, m_CharaType[nControllNum]) == true)
			{
				m_CharaType[nControllNum] = CPlayer::TYPE_MAX;
				m_SelectState[nControllNum] = SELECTSTATE_NOSELECT;
				m_bPCSelMove[nControllNum] = false;
			}
		}

		/* モードセレクトに戻るポリゴンとの判定 */
		m_bBackMode[nControllNum] = collisionBackMode(nControllNum);

		if (m_bBackMode[nControllNum] == true)
		{
			if (m_apBadge2D[nControllNum]->GetbDraw() == true) { m_apBadge2D[nControllNum]->SetbDraw(false); }
			if (m_apGauge2D[nControllNum]->GetbDraw() == false) { m_apGauge2D[nControllNum]->SetbDraw(true); }
			PressGauge(pFade, pManager, nControllNum);
		}
		else
		{
			if (m_apBadge2D[nControllNum]->GetbDraw() == false) { m_apBadge2D[nControllNum]->SetbDraw(true); }
			if (m_apGauge2D[nControllNum]->GetbDraw() == true) { m_apGauge2D[nControllNum]->SetbDraw(false); }
		}
		if (m_bBackMode[0] == true || m_bBackMode[1] == true || m_bBackMode[2] == true || m_bBackMode[3] == true)

		{
			m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			return;
		}
		else if (m_bBackMode[0] == false || m_bBackMode[1] == false || m_bBackMode[2] == false || m_bBackMode[3] == false)
		{
			m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
		}
	}

}
//=============================================================================
// 確定処理
//=============================================================================
void CCharaSelect::DecisionCharactor(CFade *pFade, CManager *pManager, int operation)
{
	CSound *pSound = CManager::GetSound();		//	音の取得
	if (collisionConf(operation) == true)
	{//ポリゴンの範囲内
		if (CCommand::GetCommand("DECISION", operation) == true)
		{
			m_bCnfFlash = true;
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT04);

			for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
			{//ランダムを選択した人がいる
				m_CharaTypeFinal[nCnt] = m_CharaType[nCnt];
				if (m_CharaTypeFinal[nCnt] == CPlayer::TYPE_RANDOM)
				{//ランダムだった場合
					m_CharaTypeFinal[nCnt] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
				}
			}
			for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
			{//プレイヤー人数分キャラの種類を渡す
				CGame::SetCharaSelect(nCnt, m_CharaTypeFinal[nCnt]);
			}

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
			}
		}
	}
}