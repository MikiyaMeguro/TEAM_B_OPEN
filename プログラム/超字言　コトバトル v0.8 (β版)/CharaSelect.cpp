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
#include "CharaSelect_Cursol.h"

//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//横幅
#define SIZE_Y (SCREEN_HEIGHT/2)								//縦幅
#define DEFAULT_SIZE (150.0f)									//ポリゴンサイズの基本の大きさ
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//ポリゴンの初期位置
#define CHARASELCHOICE_POS	(D3DXVECTOR3(211.0f,230.0f,0.0f))	//選択肢ポリゴンの位置
#define TEX_CORRECTION (0.001f)									//テクスチャ座標の補正
#define CHARASELICON_INTERVAL (215.0f)							//選択肢アイコン同士の間隔

//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apConfirm2D = NULL;
CCharaSelCursol *CCharaSelect::m_apCursol[MAX_PLAYER] = {};
bool CCharaSelect::m_bCharaCard = false;
bool CCharaSelect::m_bBackModeColl[MAX_PLAYER] = { false,false ,false ,false };
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

	/* カーソルとバッジの生成 */
	m_apCursol[0] = CCharaSelCursol::Create(0);
	m_apCursol[1] = CCharaSelCursol::Create(1);
	m_apCursol[2] = CCharaSelCursol::Create(2);
	m_apCursol[3] = CCharaSelCursol::Create(3);
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

	/* 帯のテクスチャスクロール */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* 確定ポリのフラッシュ演出 */
	if (m_bCnfFlash == true) { FlashConf(); }

	/* 戻るポリゴンの演出 */
	SetBackModeTex();
#ifdef _DEBUG
	CDebugProc::Print("c", "キャラセレクト");
#endif
}

//=============================================================================
// キャラセレクトの描画処理
//=============================================================================
void CCharaSelect::Draw(void) {}

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
		m_apScene2D[nCnt + 4] = CScene2D::Create(D3DXVECTOR3(250.0f+(260.0f*nCnt), 545.0f, 0.0f), "PLAYER_UIWINDOW", 2);
		/* サイズ設定 */
		m_apScene2D[nCnt + 4]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));//初期設定は全部COM、下のSWICHで再設定

		// プレイヤーウィンドマスク
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 8] = CScene2D::Create(D3DXVECTOR3(250.0f + (260.0f*nCnt), 545.0f, 0.0f), " ");
		/* サイズ設定 */
		m_apScene2D[nCnt + 8]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 8]->SetbDraw(false);

		//プレイヤーウィンドウに表示するキャラクター
		/* 生成と座標とテクスチャ */
		m_apScene2D[nCnt + 12] = CScene2D::Create(D3DXVECTOR3(250.0f + (260.0f*nCnt), 545.0f+20.0f, 0.0f), "CHARACTORSEL_CHARA", 2);
		/* サイズ設定 */
		m_apScene2D[nCnt + 12]->SetWidthHeight(DEFAULT_SIZE*1.1f, DEFAULT_SIZE*1.2f);
		m_apScene2D[nCnt + 12]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 1.0f));
		m_apScene2D[nCnt + 12]->SetbDraw(false);
		/* プレイヤー人数に合わせて設定 */
		// プレイヤーウィンドウのテクスチャ座標
		if (nCnt < (int)*m_PlayerNum)
		{
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nCnt), D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nCnt));
		}
		else
		{
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));
		}
	}

	/* キャラ選択確定 */
	m_apConfirm2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "PLAYER_CONFIRM",4);
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

		if (m_fFlashAlpha[nNum] <= 0.0f)
		{//透明度が下がり切った
			m_apScene2D[nNum + 8]->SetbDraw(false);								//マスクを描画しない状況に
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//マスクの色を城に戻しておく
			m_fFlashAlpha[nNum] = 0.0f;											//a値を綺麗な数字に変更
			Sel = SELECTSTATE_SELECT;											//選択された状態に変更
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
		break;
	}

	//今回の選択状態を前回の選択状態として保存
	Selold = Sel;
}
//=============================================================================
// あたり判定
//=============================================================================
bool CCharaSelect::collision(int operation, CPlayer::PLAYER_TYPE type)
{
	bool bColl = false;

	/* あたり判定 */
	if (m_apCursol[operation]->GetpBadge()->GetPosition().x - (m_apCursol[operation]->GetpBadge()->GetSize(0) / 2) <= m_apSelect2D[type]->GetPosition().x + (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apCursol[operation]->GetpBadge()->GetPosition().x + (m_apCursol[operation]->GetpBadge()->GetSize(0) / 2) >= m_apSelect2D[type]->GetPosition().x - (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apCursol[operation]->GetpBadge()->GetPosition().y + (m_apCursol[operation]->GetpBadge()->GetSize(1) / 2) >= m_apSelect2D[type]->GetPosition().y - (m_apSelect2D[operation]->GetSize(1) / 2) &&
		m_apCursol[operation]->GetpBadge()->GetPosition().y - (m_apCursol[operation]->GetpBadge()->GetSize(1) / 2) <= m_apSelect2D[type]->GetPosition().y + (m_apSelect2D[operation]->GetSize(1) / 2))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// テクスチャ座標管理
//=============================================================================
void CCharaSelect::CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type)
{
	switch (Sel)
	{/* 選ばれた時のテクスチャ座標 */
	case SELECTSTATE_FLASH:	//選ばれている
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
		if (m_apCursol[nCnt]->GetSelMove() == true)
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
	if (m_apCursol[operation]->GetpCursor()->GetPosition().x - (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) <= m_apConfirm2D->GetPosition().x + m_apConfirm2D->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().x + (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) >= m_apConfirm2D->GetPosition().x - m_apConfirm2D->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y + (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) >= m_apConfirm2D->GetPosition().y - m_apConfirm2D->GetSize(1) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y - (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) <= m_apConfirm2D->GetPosition().y + m_apConfirm2D->GetSize(1))
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
	if (m_apCursol[operation]->GetpCursor()->GetPosition().x - (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) <= m_apScene2D[3]->GetPosition().x + m_apScene2D[3]->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().x + (m_apCursol[operation]->GetpCursor()->GetSize(0) / 2) >= m_apScene2D[3]->GetPosition().x - m_apScene2D[3]->GetSize(0) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y + (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) >= m_apScene2D[3]->GetPosition().y - m_apScene2D[3]->GetSize(1) &&
		m_apCursol[operation]->GetpCursor()->GetPosition().y - (m_apCursol[operation]->GetpCursor()->GetSize(1) / 2) <= m_apScene2D[3]->GetPosition().y + m_apScene2D[3]->GetSize(1))
	{
		bColl = true;
	}

	return bColl;
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

			for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
			{//ランダムを選択した人がいる
				m_CharaType[nCnt] = m_apCursol[nCnt]->GetPlayerType();
				if (m_CharaType[nCnt] == CPlayer::TYPE_RANDOM)
				{//ランダムだった場合
					m_CharaType[nCnt] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_RANDOM);
				}
			}
			for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
			{//プレイヤー人数分キャラの種類を渡す
				CGame::SetCharaSelect(nCnt, m_CharaType[nCnt]);
			}

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
			}
		}
	}
}
//=============================================================================
// 戻るポリゴンのテクスチャ座標設定
//=============================================================================
void CCharaSelect::SetBackModeTex(void)
{
	if (m_bBackModeColl[0] == true|| m_bBackModeColl[1] == true|| m_bBackModeColl[2] == true|| m_bBackModeColl[3] == true)
	{
		m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	}
	else
	{
		m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
	}
}
//=============================================================================
// プレイヤーウィンドウの表示
//=============================================================================
void CCharaSelect::SetWindowCharaDraw(int nNum, bool bDraw)
{ m_apScene2D[nNum + 12]->SetbDraw(bDraw); }

//=============================================================================
// プレイヤーウィンドウに表示するキャラクターの設定
//=============================================================================
void CCharaSelect::SetPlayerWindowChara(int operation, CPlayer::PLAYER_TYPE type)
{
	if (m_apScene2D[operation + 12]->GetbDraw() == true)
	{
		m_apScene2D[operation + 12]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MAX_CHARASELECT)*(int)type,0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + (1.0f / MAX_CHARASELECT)*(int)type,1.0f));
	}
}