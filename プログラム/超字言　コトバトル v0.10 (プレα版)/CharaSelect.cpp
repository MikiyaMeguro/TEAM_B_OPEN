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

//============================================================================
//	マクロ定義
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//横幅
#define SIZE_Y (SCREEN_HEIGHT/2)								//縦幅
#define DEFAULT_SIZE (150.0f)									//ポリゴンサイズの基本の大きさ
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//ポリゴンの初期位置
#define CHARASELCHOICE_POS	(D3DXVECTOR3(430.0f,180.0f,0.0f))	//選択肢ポリゴンの位置
#define CHARASELCHOICE_INTERVAL (350.0f)						//選択肢ポリゴン同士の感覚
#define TEX_CORRECTION (0.0001f)								//テクスチャ座標の補正
#define CURSOR_MOVE (2.0f)										//カーソルの移動速度
#define CURSOR_SIZE (0.3f)										//カーソルのサイズ
//============================================================================
//静的メンバ変数宣言
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apCursor2D = NULL;
CScene2D *CCharaSelect::m_apBadge2D = NULL;

//=============================================================================
//	コンストラクタ
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_move = DEFAULT_POS;
	m_bPCSelMove = false;

	/* 演出系変数初期化 */
	m_nCntScrool = 0;
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		m_fFlashAlpha[nCnt] = 1.0f;
		m_SelectState[nCnt] = SELECTSTATE_NOSELECT;
		m_SelectStateold[nCnt] = SELECTSTATE_NOSELECT;
		m_bPCColl[nCnt] = false;
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
	D3DXVECTOR3 pos = m_apCursor2D->GetPosition();
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//モード遷移
		if (m_bPCSelMove == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
			}
		}

		/* カーソル移動処理 ※キーボード操作のみ対応中、後日コントローラー対応  */
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{//左押下
			if (pInputKeyboard->GetPress(DIK_W) == true)
			{//上押下
				m_move.x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{//下押下
				m_move.x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move.x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{//左押下
			if (pInputKeyboard->GetPress(DIK_W) == true)
			{//上押下
				m_move.x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{//下押下
				m_move.x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move.x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true)
		{//上押下
			m_move.x += sinf(D3DX_PI)*CURSOR_MOVE;
			m_move.y += cosf(D3DX_PI)*CURSOR_MOVE;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//下押下
			m_move.x -= sinf(D3DX_PI)*CURSOR_MOVE;
			m_move.y -= cosf(D3DX_PI)*CURSOR_MOVE;
		}
		/* 移動範囲制限 */
		pos = MoveRestriction(pos);

		/* 移動 */
		pos += m_move;

		/* 慣性 */
		m_move = CUtilityMath::MoveCoeffient(m_move,0.3f);

		/* 移動を反映 */
		m_apCursor2D->SetPosition(pos);

		/* 未選択時のみカーソルに追従 */
		if (m_bPCSelMove == false)
		{
			m_apBadge2D->SetPosition(D3DXVECTOR3(m_apCursor2D->GetPosition().x, m_apCursor2D->GetPosition().y - 50.0f, m_apCursor2D->GetPosition().z));
		}

		/* あたり判定 */
		m_bPCColl[0] = collision(CHARACTORTYPE_BALANCE);
		m_bPCColl[1] = collision(CHARACTORTYPE_POWOR);
		m_bPCColl[2] = collision(CHARACTORTYPE_SPEED);
		m_bPCColl[3] = collision(CHARACTORTYPE_REACH);

		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			if (m_bPCColl[nCnt] == true)
			{
				if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
				{//エンター押下
					if (m_SelectState[nCnt] != SELECTSTATE_SELECT)
					{//セレクト状態じゃない（無限フラッシュ防止）
						m_SelectState[nCnt] = SELECTSTATE_FLASH;
						m_bPCSelMove = true;
					}
				}
			}
		}

		/* 選択取り消し */
		if (pInputKeyboard->GetPress(DIK_BACKSPACE) == true)
		{
			for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
			{
				if (collision((CHARACTORTYPE)nCnt) == true)
				{
					m_SelectState[(CHARACTORTYPE)nCnt] = SELECTSTATE_NOSELECT;
					m_bPCSelMove = false;
				}
			}
		}
	}
	/* 帯のテクスチャスクロール */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* 選択時演出関数 */
	SelectProduction(0);
	SelectProduction(1);
	SelectProduction(2);
	SelectProduction(3);

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
void CCharaSelect::SelectProduction(int SelNum)
{
	switch (m_SelectState[SelNum])
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//演出中
		if (m_SelectStateold[SelNum] != SELECTSTATE_FLASH)
		{//前回のモードがFlash以外の場合a値を初期化
			m_fFlashAlpha[SelNum] = 1.0f;
		}
		m_apScene2D[SelNum+3]->SetbDraw(true);												//マスクの描画する
		m_apScene2D[SelNum+3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[SelNum]));	//色
		/* 選択肢のテクスチャ座標の変更 */
		m_apSelect2D[SelNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*SelNum), 0.5f+ TEX_CORRECTION),
									D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*SelNum) - TEX_CORRECTION, 1.0f));

		if (m_fFlashAlpha[SelNum] <= 0.0f)
		{//透明度が下がり切った
			m_apScene2D[SelNum + 3]->SetbDraw(false);							//マスクを描画しない状況に
			m_apScene2D[SelNum + 3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//マスクの色を城に戻しておく
			m_fFlashAlpha[SelNum] = 0.0f;										//a値を綺麗な数字に変更
			m_SelectState[SelNum] = SELECTSTATE_SELECT;							//選択された状態に変更
		}
		else
		{
			m_fFlashAlpha[SelNum] -= 0.02f;
			m_apScene2D[SelNum + 3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[SelNum]));
		}
		break;

	case SELECTSTATE_SELECT:	//選択されている
		/* 選択肢のテクスチャ座標の変更 */
		m_apSelect2D[SelNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*SelNum), 0.5f + TEX_CORRECTION),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*SelNum) - TEX_CORRECTION, 1.0f));
		break;

	case SELECTSTATE_NOSELECT:	//選択されていない
		m_apScene2D[SelNum + 3]->SetbDraw(false);		//マスクを描画されていない状態に
		/* 選択肢のテクスチャ座標の変更 */
		m_apSelect2D[SelNum]->SetTex(D3DXVECTOR2(0.0f+((1.0f / MAX_CHARASELECT)*SelNum), 0.0f),
									D3DXVECTOR2((1.0f / MAX_CHARASELECT)+ ((1.0f / MAX_CHARASELECT)*SelNum), 0.499f));
		break;
	}

	//今回の選択状態を前回の選択状態として保存
	m_SelectStateold[SelNum] = m_SelectState[SelNum];
}
//=============================================================================
// ポリゴンの初期設定
//=============================================================================
void CCharaSelect::InitCharaSelectPoly(void)
{
	/* 選択肢 */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* 生成と座標とテクスチャ */
		if (nCnt < MAX_CHARASELECT / 2)
		{//0,1
			m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*nCnt),
				CHARASELCHOICE_POS.y,
				CHARASELCHOICE_POS.z), "CHARACTORSEL_CHARA");
		}
		else
		{//2,3
			m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*(nCnt - 2)),
				CHARASELCHOICE_POS.y + CHARASELCHOICE_INTERVAL,
				CHARASELCHOICE_POS.z), "CHARACTORSEL_CHARA");
		}
		/* テクスチャ座標設定 */
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.0f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 0.445f));
		/* サイズ設定 */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.5f);
	}

	/* 演出 */
	// 背景
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAUERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//モード名帯（左）
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 2);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//モード名帯（右）
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 2);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);
	/* 選択肢のマスク */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* 生成と座標とテクスチャ */
		if (nCnt < MAX_CHARASELECT / 2)
		{//0,1
			m_apScene2D[nCnt + 3] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*nCnt),
				CHARASELCHOICE_POS.y,
				CHARASELCHOICE_POS.z), " ");
		}
		else
		{//2,3
			m_apScene2D[nCnt + 3] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*(nCnt - 2)),
				CHARASELCHOICE_POS.y + CHARASELCHOICE_INTERVAL,
				CHARASELCHOICE_POS.z), " ");
		}
		/* サイズ設定 */
		m_apScene2D[nCnt + 3]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.5f);
		m_apScene2D[nCnt + 3]->SetbDraw(false);
	}

	m_apBadge2D= CScene2D::Create(CHARASELCHOICE_POS, "CHARASEL_BADGE");
	m_apBadge2D->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);
	m_apBadge2D->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.25f, 1.0f));

	m_apCursor2D = CScene2D::Create(CHARASELCHOICE_POS,"CHARASEL_BADGE");
	m_apCursor2D->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);
	m_apCursor2D->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 0.5f));

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
bool CCharaSelect::collision(CHARACTORTYPE type)
{
	bool bColl = false;

	/* あたり判定 */
	if (m_apBadge2D->GetPosition().x - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().x + (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D->GetPosition().x + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().x - (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D->GetPosition().y + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().y - (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D->GetPosition().y - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().y + (DEFAULT_SIZE*1.0f))
	{
		bColl = true;
	}

	return bColl;
}