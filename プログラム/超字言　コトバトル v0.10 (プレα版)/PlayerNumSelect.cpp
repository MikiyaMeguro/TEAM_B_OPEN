//---------------------------------------------------------------------
// プレイヤー人数選択画面処理 [PlayerNumSelect.cpp]
// Author : Mikiya Meguro/Akane Gokan
//---------------------------------------------------------------------
#include "PlayerNumSelect.h"
#include "select.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "player.h"
#include "debugProc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODESELECT_WIDTH		(1.5f)		//ポリゴンの大きさ(横)
#define MODESELECT_HEIGHT		(1.5f)		//ポリゴンの大きさ(縦)
#define MENU_WIDTH				(350.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define MENU_HEIGHT				(310.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define MENU_INITPOS			(250.0f)	//メニューの初期位置
#define MENU_NUM_HEIGHT			(2)			//メニューの縦段数
#define MENU_NUM_WIDTH			(2)			//メニューの横段数
#define CAUTIONBG_WIDTH			(750.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define CAUTIONBG_HEIGHT		(450.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define CAUTION_WIDTH			(450.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define CAUTION_HEIGHT			(150.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define BAND_SIZE				(0.5f)		//帯のサイズ
#define PLNUMMENU_BG			(150.0f)	//ポリゴンの大きさ
#define NOSELECT_SIZE			(50.0f)		//選ばれていないときのポリゴンのサイズ

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9 CPlayerSelect::m_pTexture[MAX_PLAYER_SELECTMENU] = {};
LPDIRECT3DTEXTURE9 CPlayerSelect::m_pTextureBG = NULL;
CPlayerSelect::SELECTPLAYER CPlayerSelect::m_SelectMode = CPlayerSelect::SELECTPLAYER_NONE;
bool CPlayerSelect::m_bModeSelect = false;

//--------------------------------------------
//モードセレクトクラス コンストラクタ
//--------------------------------------------
CPlayerSelect::CPlayerSelect(int nPriority) : CScene(7)
{
	//値の初期化
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_ChoicePos[0] = D3DXVECTOR3(0, 0, 0);
	m_ChoicePos[1] = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[0].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bCaution = false;
	m_bCreate2D = false;
	m_bModeSelect = true;
	m_nSelectCaution = 1;
	m_SelectCaution[0].select = SELECTTYPE_NONE;
	m_SelectCaution[1].select = SELECTTYPE_SELECT;

	/* 演出系変数の初期化 */
	m_nCntScrool = 0;
	m_fChangeMode = 0.1f;
	m_fMoveMode = 0.0f;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;

}

//--------------------------------------------
//モードセレクトクラス デストラクタ
//--------------------------------------------
CPlayerSelect::~CPlayerSelect(){}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CPlayerSelect *CPlayerSelect::Create(D3DXVECTOR3 pos, float m_fWidth)
{
	//モードセレクトのポインタ
	CPlayerSelect *pModeSelect;
	pModeSelect = new CPlayerSelect;

	pModeSelect->m_InitPos = pos;
	pModeSelect->m_fWidth = m_fWidth;
	pModeSelect->m_fHeight = m_fWidth;
	//モードセレクトの初期化
	pModeSelect->Init();
	//モードセレクトの情報を返す
	return pModeSelect;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayerSelect::Init(void)
{
	/* 各種ポインタの初期化 */
	InitPointer();

	/* 演出用ポインタの初期位置設定 */
	InitProductionPos();

	/* 選択肢の初期位置設定 */
	m_InitPos.y = MENU_INITPOS;

	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		if (nCnt < 2)
		{
			//ポリゴンの位置を左上に初期化
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x - (MENU_WIDTH / 2);
			//位置をずらす
			m_Pos[nCnt].x = m_Pos[nCnt].x + (MENU_WIDTH * nCnt);
		}
		else if (nCnt > 1)
		{
			//ポリゴンの位置を左上に初期化
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x - (MENU_WIDTH / 2);
			m_Pos[nCnt].y = m_InitPos.y + MENU_HEIGHT;
			//位置をずらす
			m_Pos[nCnt].x = m_Pos[nCnt].x + (MENU_WIDTH * (nCnt - 2));
		}

		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "PLAYERNUMSELECT_MENU");
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.25f*nCnt), 0.0f), D3DXVECTOR2(0.25f + (0.25f*nCnt), 1.0f));
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}

	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);

	/* コマンド */
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_BACKSPACE);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

	return S_OK;
}

//=============================================================================
// モードセレクトクラス 終了処理
//=============================================================================
void CPlayerSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYERNUMSEL_BG; nCnt++)
	{
		if (m_apPolygonBG[nCnt] != NULL)
		{
			m_apPolygonBG[nCnt]->Uninit();
			m_apPolygonBG[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt]->Uninit();
			m_apPolygon[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt]->Uninit();
			m_pSelect2D[nCnt] = NULL;
		}
	}
	if (m_pCaution2D != NULL)
	{
		m_pCaution2D->Uninit();
		m_pCaution2D = NULL;
	}
	if (m_pCaution2DBG != NULL)
	{
		m_pCaution2DBG->Uninit();
		m_pCaution2DBG = NULL;
	}

	//自分を破棄
	Release();
}

//=============================================================================
// モードセレクトクラス 更新処理
//=============================================================================
void CPlayerSelect::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//フェードを取得
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();


	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	//表示切替
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		m_apPolygon[nCnt]->SetbDraw(m_bModeSelect);
	}
	m_apPolygonBG[0]->SetbDraw(m_bModeSelect);


#ifdef  _DEBUG
	if (pInput->GetTrigger(DIK_O) == true)
	{//TRUEならFALSE FALSEならTRUE
		m_bModeSelect = m_bModeSelect ? false : true;
	}
#endif

	//モードセレクト中
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		if (m_bModeSelect == true)
		{
			//選択処理
			if (CCommand::GetCommand("DOWN") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect < 2)
				{
					m_nSelect = (m_nSelect + MAX_PLAYER_SELECTMENU / 2) % (MAX_PLAYER_SELECTMENU);
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("UP") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect > 1)
				{
					m_nSelect = m_nSelect - 2;
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("RIGHT") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect == 1)
				{
					m_nSelect = 1;
				}
				else if (m_nSelect == 3)
				{
					m_nSelect = 3;
				}
				else
				{
					m_nSelect = (m_nSelect + 1) % 4;
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("LEFT") && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
				if (m_nSelect == 0)
				{
					m_nSelect = 0;
				}
				else if (m_nSelect == 2)
				{
					m_nSelect = 2;
				}
				else
				{
					m_nSelect = (m_nSelect + 3) % 4;
				}
				m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
			}

			//エンターキー
			if (CCommand::GetCommand("DECISION") == true && m_bCaution == false)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT00);
				if (m_nSelect == 0)
				{
					m_SelectMode = SELECTPLAYER_1P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));
				}
				else if (m_nSelect == 1)
				{
					m_SelectMode = SELECTPLAYER_2P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
				}
				else if (m_nSelect == 2)
				{
					m_SelectMode = SELECTPLAYER_3P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.5f, 0.0f), D3DXVECTOR2(0.75f, 1.0f));
				}
				else if (m_nSelect == 3)
				{
					m_SelectMode = SELECTPLAYER_4P;
					m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.75f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
				}
				//警告を表示
				m_bCaution = true;
			}

			//最終警告	2Dが作成されたら
			if (CCommand::GetCommand("DECISION") && m_bCreate2D == true)
			{
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT00);
				switch (m_SelectMode)
				{
				case SELECTPLAYER_1P:
					break;
				case SELECTPLAYER_2P:
					break;
				case SELECTPLAYER_3P:
					break;
				case SELECTPLAYER_4P:
					break;
				}
				//2Dを破棄
				Caution2DUninit();
				m_apPolygonBG[5]->SetbDraw(false);
				m_apPolygonBG[6]->SetbDraw(false);
				if (m_nSelectCaution == 0)
				{
					CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
				}

				m_nSelectCaution = 1;
				m_SelectCaution[0].select = SELECTTYPE_NONE;
				m_SelectCaution[1].select = SELECTTYPE_SELECT;
				m_bCreate2D = false;
			}
			else if (pInput->GetTrigger(DIK_B) == true)
			{
				//2Dを破棄
				Caution2DUninit();

				m_nSelectCaution = 1;
				m_SelectCaution[0].select = SELECTTYPE_NONE;
				m_SelectCaution[1].select = SELECTTYPE_SELECT;
				m_bCreate2D = false;
			}

			//警告表示中
			if (m_bCaution == true)
			{
				m_apPolygonBG[5]->SetbDraw(true);
				m_apPolygonBG[6]->SetbDraw(true);

				if (m_bCreate2D == false)
				{
					//警告を生成
					m_pCaution2DBG = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), "PLAYERNUMSEL_BG");
					m_pCaution2DBG->SetWidthHeight(CAUTIONBG_WIDTH, CAUTIONBG_HEIGHT);
					m_pCaution2DBG->SetbDraw(true);

					m_pCaution2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 100.0f, 0), "BLOCK", 4);
					m_pCaution2D->SetWidthHeight(CAUTION_WIDTH, CAUTION_HEIGHT);
					m_pCaution2D->BindTexture(CTexture::GetTexture("MENU_START"));
					m_pCaution2D->SetbDraw(true);

					//YES or NO　ポリゴン生成
					for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
					{
						//ポリゴンの位置を左上に初期化
						m_ChoicePos[nCnt] = m_InitPos;
						m_ChoicePos[nCnt].x = m_InitPos.x - (480 / 2);
						//位置をずらす
						m_ChoicePos[nCnt].x = m_ChoicePos[nCnt].x + (500 * nCnt);
						m_ChoicePos[nCnt].y = 500.0f;
						if (m_pSelect2D[nCnt] == NULL)
						{	//生成
							m_pSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(m_ChoicePos[nCnt].x, m_ChoicePos[nCnt].y + 100.0f, m_ChoicePos[nCnt].z), "MENU_START");
							m_pSelect2D[nCnt]->SetWidthHeight(400, 200);
							if (nCnt == 0)
							{
								m_pSelect2D[nCnt]->BindTexture(CTexture::GetTexture("MENU_YES"));
							}
							if (nCnt == 1)
							{
								m_pSelect2D[nCnt]->BindTexture(CTexture::GetTexture("MENU_NO"));
							}
							m_pSelect2D[nCnt]->SetbDraw(true);
						}
					}
					//2Dポリゴンを生成した
					m_bCreate2D = true;
				}
				else
				{
					//色変え
					for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
					{
						if (m_SelectCaution[nCnt].select == SELECTTYPE_SELECT)
						{//選択中の色
							m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
							m_pSelect2D[nCnt]->SetCol(m_SelectCaution[nCnt].col);
						}
						else
						{//未選択の色
							m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
							m_pSelect2D[nCnt]->SetCol(m_SelectCaution[nCnt].col);
						}
					}
				}

				if (CCommand::GetCommand("RIGHT") && m_bCaution == true)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
					//右端で止まる
					if (m_nSelectCaution < 1)
					{
						m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
					}
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
				}
				else if (CCommand::GetCommand("LEFT") && m_bCaution == true)
				{
					pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT02);
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
					//左端で止まる
					if (m_nSelectCaution > 0)
					{
						m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
					}
					m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
				}
			}

			//モード選択に戻る
			if (CCommand::GetCommand("DELETE") == true && m_bCaution == false)
			{
				Uninit();
				pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT01);
				CManager::SetMode(CManager::MODE_SELECT);
				return;
			}
		}
	}
	/* モードタイトル帯のスクロール処理 */
	ScrollMenu(PLNUMSELECTBGTYPE_BAND_L, -0.005f);
	ScrollMenu(PLNUMSELECTBGTYPE_BAND_R, 0.005f);

	if (m_bCaution == false)
	{//警告が出てない場合の選択肢の設定
		SetPlayerSelNumMenuPos(m_nSelect);
	}
	else
	{//警告が出てる時の選択肢の設定
		SetPlayerSelNumMenuPos(m_nSelectCaution);
	}

	/* 操作方法UIのアニメーション */
	SetSelectAnimation(PLNUMSELECTBGTYPE_BG, ANIMTYPE_X, 3, 4, 1, 15);


#ifdef _DEBUG
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif

}

//=============================================================================
// モードセレクトクラス 描画処理
//=============================================================================
void CPlayerSelect::Draw(void){}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CPlayerSelect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		// テクスチャの破棄
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	if (m_pTextureBG != NULL)
	{
		m_pTextureBG->Release();
		m_pTextureBG = NULL;
	}
}
//=============================================================================
// 警告2Dの破棄
//=============================================================================
void CPlayerSelect::Caution2DUninit(void)
{
	//2Dを破棄
	if (m_pCaution2D != NULL)
	{
		m_pCaution2D->Uninit();
		m_pCaution2D = NULL;
		m_bCaution = false;
	}
	if (m_pCaution2DBG != NULL)
	{
		m_pCaution2DBG->Uninit();
		m_pCaution2DBG = NULL;
		m_bCaution = false;
	}
	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt]->Uninit();
			m_pSelect2D[nCnt] = NULL;
			m_pSelect2D[nCnt] = false;
		}
	}
}
//=============================================================================
// 各種ポインタの初期化
//=============================================================================
HRESULT CPlayerSelect::InitPointer(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{/* 人数選択のポインタ */
		if (m_apPolygon[nCnt] != NULL)
		{
			m_apPolygon[nCnt] = NULL;
		}
	}

	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{/* 警告の選択肢のポインタ */
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt] = NULL;	//警告の選択肢のポインタの初期化
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYERNUMSEL_BG; nCnt++)
	{/* 演出用背景のポインタ */
		if (m_apPolygonBG[nCnt] != NULL)
		{
			m_apPolygonBG[nCnt] = NULL;
		}
	}
	m_pCaution2D = NULL;	//警告題字のポインタの初期化
	m_pCaution2DBG = NULL;	//警告背景のポインタ初期化

	return S_OK;
}
//=============================================================================
// 演出の初期位置の決定
//=============================================================================
void CPlayerSelect::InitProductionPos(void)
{
	//BG
	m_apPolygonBG[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_BG");
	m_apPolygonBG[0]->SetWidthHeight(PLNUMMENU_BG*6.0f, PLNUMMENU_BG * 3.5f);

	//モード名帯（左）
	m_apPolygonBG[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "PLAYERNUMSEL_BAND");
	m_apPolygonBG[1]->SetWidthHeight(PLNUMMENU_BG*BAND_SIZE, PLNUMMENU_BG * 3.5f);

	//モード名帯（右）
	m_apPolygonBG[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "PLAYERNUMSEL_BAND");
	m_apPolygonBG[2]->SetWidthHeight(PLNUMMENU_BG*BAND_SIZE, PLNUMMENU_BG * 3.5f);

	//UI_スティック
	m_apPolygonBG[3] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_OPERATION1", 4);
	m_apPolygonBG[3]->SetWidthHeight(PLNUMMENU_BG*0.5f, PLNUMMENU_BG * 0.5f);
	m_apPolygonBG[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));

	//UI_選択中
	m_apPolygonBG[4] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_SELECT", 4);
	m_apPolygonBG[4]->SetWidthHeight(m_fWidth*1.5f, m_fHeight * 1.5f);
	m_apPolygonBG[4]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	//マスク
	m_apPolygonBG[5] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), " ");
	m_apPolygonBG[5]->SetWidthHeight(PLNUMMENU_BG*6.5f, PLNUMMENU_BG * 3.5f);
	m_apPolygonBG[5]->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.7f));
	m_apPolygonBG[5]->SetbDraw(false);

	//選択した人数Icon
	m_apPolygonBG[6] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 30.0f, m_InitPos.z), "PLAYERNUMSELECT_MENU", 4);
	m_apPolygonBG[6]->SetWidthHeight(m_fWidth * 1.8f, m_fHeight * 1.8f);
	m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.25f, 0.0f), D3DXVECTOR2(0.5f, 1.0f));
	m_apPolygonBG[6]->SetbDraw(false);

}
//=============================================================================
// 横の文字スクロール処理
//=============================================================================
void CPlayerSelect::ScrollMenu(PLNUMSELECTBGTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;

	if (m_apPolygonBG[type] != NULL)
	{
		m_apPolygonBG[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)), D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}

//=============================================================================
// セレクトしてるモードの移動演出
//=============================================================================
void CPlayerSelect::PlayerSelectMove(PLNUMSELECTBGTYPE type, int MenuNum)
{
	D3DXVECTOR3 SelectPos;
	switch (type)
	{
	case PLNUMSELECTBGTYPE_MENU:	//選択肢のポリゴン
		SelectPos = m_apPolygon[MenuNum]->GetPosition();

		if (m_fMoveMode >= 1.5f || m_fMoveMode <= -1.5f)
		{
			m_fChangeMode *= -1.0f;
		}

		//移動量を加算
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygon[MenuNum]->SetPos(SelectPos, 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	case PLNUMSELECTBGTYPE_BG:		//演出用のポリゴン
		SelectPos = m_apPolygonBG[MenuNum]->GetPosition();

		if (m_fMoveMode >= 1.5f || m_fMoveMode <= -1.5f)
		{
			m_fChangeMode *= -1.0f;
		}

		//移動量を加算
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygonBG[MenuNum]->SetPos(SelectPos, 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}
}
//=============================================================================
// セレクトしてるアイコンとそれ以外のアイコンの状態の位置設定
//=============================================================================
void CPlayerSelect::SetPlayerSelNumMenuPos(int MenuNum)
{
	if (m_bCaution == false)
	{//警告が出ていない時
		m_apPolygonBG[4]->SetWidthHeight(m_fWidth*1.5f, m_fHeight * 1.5f);
		m_apPolygonBG[3]->SetPos(D3DXVECTOR3(m_InitPos.x, m_InitPos.y-200.0f, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apPolygonBG[3]->SetWidthHeight(PLNUMMENU_BG*0.5f, PLNUMMENU_BG * 0.5f);
		m_apPolygonBG[3]->BindTexture("UI_OPERATION2");
		switch (MenuNum)
		{//人数選択
		case 0:	//一人
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* カーソル */
			m_apPolygonBG[4]->SetPos(m_apPolygon[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1://二人
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* カーソル */
			m_apPolygonBG[4]->SetPos(m_apPolygon[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 2://三人
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* カーソル */
			m_apPolygonBG[4]->SetPos(m_apPolygon[2]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 3://四人
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[3]->SetPos(m_Pos[3], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			/* カーソル */
			m_apPolygonBG[4]->SetPos(m_apPolygon[3]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		}
		PlayerSelectMove(PLNUMSELECTBGTYPE_MENU, m_nSelect);
	}
	else
	{//警告ウィンド
		m_apPolygonBG[4]->SetWidthHeight(200.0f, 120.0f);
		m_apPolygonBG[3]->SetPos(D3DXVECTOR3(m_InitPos.x, m_InitPos.y+350.0f, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apPolygonBG[3]->SetWidthHeight(PLNUMMENU_BG*0.8f, PLNUMMENU_BG * 0.8f);
		m_apPolygonBG[3]->BindTexture("UI_OPERATION1");

		switch (MenuNum)
		{
		case 0:	//YES
			m_pSelect2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pSelect2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* カーソル */
			m_apPolygonBG[4]->SetPos(m_pSelect2D[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1:	//NO
			m_pSelect2D[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_pSelect2D[1]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			/* カーソル */
			m_apPolygonBG[4]->SetPos(m_pSelect2D[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;
		}
	}
}

//=============================================================================
// アニメーション処理
//=============================================================================
void CPlayerSelect::SetSelectAnimation(PLNUMSELECTBGTYPE type, ANIMTYPE AnimType, int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed)
{
	/*　1段のみのアニメーションに対応※　*/

	m_nCntAnim++;
	switch (type)
	{
	case PLNUMSELECTBGTYPE_MENU:		//選択肢
		if (AnimType == ANIMTYPE_X)
		{//横割り
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternX)
			{
				m_nPatturnAnim = 0;
			}
			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim), 0.0f + (1.0f / MaxAnimPatternY)),
				D3DXVECTOR2(((1.0f / MaxAnimPatternX)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim),
				(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{//縦割り
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternY)
			{
				m_nPatturnAnim = 0;
			}

			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim)));
		}
		break;

	case PLNUMSELECTBGTYPE_BG:		//演出用ポリゴン
		if (AnimType == ANIMTYPE_X)
		{//横割り
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternX)
			{
				m_nPatturnAnim = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX)*m_nPatturnAnim,
				0.0f + (1.0f / MaxAnimPatternY)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim),
				(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{//縦割り
			if (m_nCntAnim > AnimSpeed)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;
			}
			if (m_nPatturnAnim >= MaxAnimPatternY)
			{
				m_nPatturnAnim = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim)));
		}
		break;
	}

}