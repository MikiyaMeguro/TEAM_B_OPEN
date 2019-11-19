//---------------------------------------------------------------------
// セレクトメニュー処理 [SelectMenu.cpp]
// Author : Mikiya Meguro/Akane Gokan
//---------------------------------------------------------------------
#include "SelectMenu.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "PlayerNumSelect.h"
#include "fade.h"
#include "renderer.h"
#include "load.h"
#include "texture.h"
#include "debugProc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODESELECT_WIDTH		(1.0f)		//ポリゴンの大きさ(横)
#define MODESELECT_HEIGHT		(1.0f)		//ポリゴンの大きさ(縦)
#define MENU_WIDTH				(450.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define MENU_HEIGHT				(180.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define MENU_INITPOS			(350.0f)	//メニューの初期位置
#define MENU_NUM_HEIGHT			(2)
#define MENU_NUM_WIDTH			(2)
#define MENU_INIT_POS			(370.0f)
#define MENU_BG					(150.0f)	//ポリゴンの大きさ
#define NOSELECT_MENU_SIZE		(50.0f)		//選ばれていないときのポリゴンのサイズ

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9 CSelectMenu::m_pTexture[MAX_SELECTMENU] = {};
LPDIRECT3DTEXTURE9 CSelectMenu::m_pTextureBG = NULL;
CSelectMenu::SELECT_MENU CSelectMenu::m_SelectMode = CSelectMenu::SELECT_MENU_NONE;
bool CSelectMenu::m_bModeSelect = false;

//--------------------------------------------
//セレクトメニュークラス コンストラクタ
//--------------------------------------------
CSelectMenu::CSelectMenu(int nPriority) : CScene(7)
{
	//値の初期化
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bModeSelect = true;

	for (int nCnt = 0; nCnt < MAX_SELETMODE_BG; nCnt++)
	{
		if (m_apPolygonBG[nCnt] != NULL)
		{
			m_apPolygonBG[nCnt] = NULL;
		}
	}

	m_fSpace = 0;
	m_fInitYpos = 0;

	/* 演出面変数の初期化 */
	m_nCntScrool = 0;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_nCntAnim2 = 0;
	m_nPatturnAnim2 = 0;
	m_fChangeMode = 0.3f;
	m_fMoveMode = 0.0f;
}

//--------------------------------------------
//セレクトメニュークラス デストラクタ
//--------------------------------------------
CSelectMenu::~CSelectMenu()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CSelectMenu *CSelectMenu::Create(D3DXVECTOR3 pos, float m_fWidth, float fSpace, MENU_TYPE type)
{
	//セレクトメニューのポインタ
	CSelectMenu *pMenuSelect;
	pMenuSelect = new CSelectMenu;
	pMenuSelect->m_MenuType = type;
	pMenuSelect->m_InitPos = pos;
	pMenuSelect->m_fWidth = m_fWidth;
	pMenuSelect->m_fHeight = m_fWidth;
	pMenuSelect->m_fSpace = fSpace;
	//セレクトメニューの初期化
	pMenuSelect->Init();
	//セレクトメニューの情報を返す
	return pMenuSelect;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSelectMenu::Init()
{
	switch (m_MenuType)
	{
	case MENU_TYPE_TUTORIAL:
		m_nMaxMenu = 3;
		m_fInitYpos = 350.0f;

		InitTutorialPolygon();
		break;

	case MENU_TYPE_RESULT:
		m_fInitYpos = 270.0f;
		m_nMaxMenu = 4;
		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{//メニューポリゴンの初期化
			m_apPolygon[nCnt] = NULL;
		}

		/* メニューポリゴンの設定 */

		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
			//位置をずらす
			m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


			if (m_apPolygon[nCnt] == NULL)
			{
				m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU");
				m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 0.5f));
				m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
				m_apPolygon[nCnt]->SetbDraw(true);
			}
		}
		break;
	case MENU_TYPE_PAUSE:
		m_nMaxMenu = 2;
		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{//メニューポリゴンの初期化
			m_apPolygon[nCnt] = NULL;
		}

		/* メニューポリゴンの設定 */
		m_InitPos.y = MENU_INITPOS;

		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
			//位置をずらす
			m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


			if (m_apPolygon[nCnt] == NULL)
			{
				m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU");
				m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 1.0f));
				m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
				m_apPolygon[nCnt]->SetbDraw(true);
			}
		}
		break;
	}

	//m_pTextureBG = CLoad::GetTexture(CLoad::TEXTURE_MODESELECT_BG);

	//値の初期化
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bModeSelect = true;
	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);

	return S_OK;
}

//=============================================================================
// セレクトメニュークラス 終了処理
//=============================================================================
void CSelectMenu::Uninit(void)
{
	//自分を破棄
	Release();
}

//=============================================================================
// セレクトメニュークラス 更新処理
//=============================================================================
void CSelectMenu::Update(void)
{
	//キーボード情報を取得
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//フェードを取得
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();


	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	//セレクトメニュー中
	if (m_bModeSelect == true && pFade->GetFade() == CFade::FADE_NONE)
	{
		//選択処理
		if (CCommand::GetCommand("RIGHT"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect < m_nMaxMenu - 1)
			{
				m_nSelect = (m_nSelect + 1) % m_nMaxMenu;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("LEFT"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect > 0)
			{
				m_nSelect = (m_nSelect + (m_nMaxMenu - 1)) % m_nMaxMenu;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}

		//エンターキー
		if (CCommand::GetCommand("DECISION"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_CANCEL);
			if (m_nSelect == 0)
			{
				m_SelectMode = SELECT_MENU_ONE;
				MenuDecide(SELECT_MENU_ONE);
			}
			else if (m_nSelect == 1)
			{
				m_SelectMode = SELECT_MENU_TWO;
				MenuDecide(SELECT_MENU_TWO);
			}
			else if (m_nSelect == 2)
			{
				m_SelectMode = SELECT_MENU_THREE;
				MenuDecide(SELECT_MENU_THREE);
			}
			else if (m_nSelect == 3)
			{
				m_SelectMode = SELECT_MENU_FOUR;
				MenuDecide(SELECT_MENU_FOUR);
			}
				m_bModeSelect = false;
		}
	}

	/* 演出 */
	switch (m_MenuType)
	{
	case MENU_TYPE_TUTORIAL:
		ScrollMenu(SELECTMODEBGTYPE_BAND_L, -0.005f);
		ScrollMenu(SELECTMODEBGTYPE_BAND_R, 0.005f);

		SelectModeExplanation(m_nSelect);
		SelectAnimation(m_nSelect);

		SetSelectAnimation(POLYGONTYPE_BG, ANIMTYPE_X, 8, 4, 1, 15);
		break;

	case MENU_TYPE_RESULT:
		break;

	case MENU_TYPE_PAUSE:
		break;
	}
#ifdef _DEBUG

	if (pInput->GetTrigger(DIK_O) == true)
	{//TRUEならFALSE FALSEならTRUE
		m_bModeSelect = m_bModeSelect ? false : true;
	}

	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif
}

//=============================================================================
// セレクトメニュークラス 描画処理
//=============================================================================
void CSelectMenu::Draw(void){}

//=============================================================================
// テクスチャの破棄処理
//=============================================================================
void CSelectMenu::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_SELECTMENU; nCnt++)
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
// 決定したメニューの処理
//=============================================================================
void CSelectMenu::MenuDecide(SELECT_MENU MenuSelect)
{
	//フェードを取得
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	switch (m_MenuType)
	{
	case MENU_TYPE_TUTORIAL:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CPlayerSelect::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 150);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
			break;
		}
		break;

	case MENU_TYPE_RESULT:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_CHARASELECT, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_STAGESELECT, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		}
		break;

	case MENU_TYPE_PAUSE:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		}
		break;
	}
}

//=============================================================================
// 横の文字スクロール処理
//=============================================================================
void CSelectMenu::ScrollMenu(SELECTMODEBGTYPE type,float fScroolSpeed)
{
	m_nCntScrool++;

	m_apPolygonBG[type]->SetTex(D3DXVECTOR2(0.0f , 0.0f + (m_nCntScrool*fScroolSpeed)),D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
}

//=============================================================================
// 選択肢と説明文の同期処理
//=============================================================================
void CSelectMenu::SelectModeExplanation(int MenuSelect)
{
	if (m_MenuType == MENU_TYPE_TUTORIAL)
	{
		switch (MenuSelect)
		{
		case 0:
			/* モード選択ウィンド */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 0);	//移動演出処理
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* モード説明のテクスチャ */
			m_apPolygonBG[4]->SetAnimation(0, 0.333f, 1.0f);

			/* アニメーション位置 */
			m_apPolygonBG[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG, 5);		//移動演出処理
			m_apPolygonBG[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* 選択中UI */
			m_apPolygonBG[9]->SetPos(m_apPolygon[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1:
			/* モード選択ウィンド */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 1);	//移動演出処理
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* モード説明のテクスチャ */
			m_apPolygonBG[4]->SetAnimation(1, 0.333f, 1.0f);

			/* アニメーション位置 */
			m_apPolygonBG[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG, 6);		//移動演出処理
			m_apPolygonBG[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* 選択中UI */
			m_apPolygonBG[9]->SetPos(m_apPolygon[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			break;

		case 2:
			/* モード選択ウィンド */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 2);	//移動演出処理

			/* モード説明のテクスチャ */
			m_apPolygonBG[4]->SetAnimation(2, 0.333f, 1.0f);

			/* アニメーション位置 */
			m_apPolygonBG[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG,7);		//移動演出処理

			/* 選択中UI */
			m_apPolygonBG[9]->SetPos(m_apPolygon[2]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			break;
		}
	}

}
//=============================================================================
// セレクトしてるモードのアニメーション
//=============================================================================
void CSelectMenu::SelectAnimation(int MenuSelect)
{
	if (m_MenuType == MENU_TYPE_TUTORIAL)
	{
		switch (MenuSelect)
		{
		case 0:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygonBG[5]->SetTex(D3DXVECTOR2(0.0f+(0.5f*m_nPatturnAnim),0.666f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.999f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;

		case 1:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.333f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.666f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;

		case 2:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygonBG[7]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.0f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.333f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;
		}
	}
}
//=============================================================================
// セレクトしてるモードの移動演出
//=============================================================================
void CSelectMenu::SelectMove(POLYGONTYPE type, int MenuNum)
{
	D3DXVECTOR3 SelectPos;
	switch (type)
	{
	case POLYGONTYPE_MENU:
		SelectPos = m_apPolygon[MenuNum]->GetPosition();

		if (m_fMoveMode >= 8.0f || m_fMoveMode <= -8.0f)
		{
			m_fChangeMode *= -1.0f;
		}

		//移動量を加算
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygon[MenuNum]->SetPos(SelectPos,0.0f,0.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		break;

	case POLYGONTYPE_BG:
		SelectPos = m_apPolygonBG[MenuNum]->GetPosition();

		if (m_fMoveMode >= 8.0f || m_fMoveMode <= -8.0f)
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
// アニメーション処理
//=============================================================================
void CSelectMenu::SetSelectAnimation(POLYGONTYPE type, ANIMTYPE AnimType, int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed)
{
	m_nCntAnim2++;
	switch (type)
	{
	case POLYGONTYPE_MENU:
		if (AnimType == ANIMTYPE_X)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternX)
			{
				m_nPatturnAnim2 = 0;
			}
			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f/ MaxAnimPatternX)*m_nPatturnAnim2),0.0f + (1.0f / MaxAnimPatternY)),
										 D3DXVECTOR2(((1.0f / MaxAnimPatternX)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim2),
													(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternY)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim2)),
										 D3DXVECTOR2((1.0f / MaxAnimPatternX)+ (1.0f / MaxAnimPatternX),
													((1.0f / MaxAnimPatternY)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim2)));
		}
		break;

	case POLYGONTYPE_BG:
		if (AnimType == ANIMTYPE_X)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternX)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f+(1.0f/MaxAnimPatternX)*m_nPatturnAnim2,
														0.0f + (1.0f / MaxAnimPatternY)),
										D3DXVECTOR2((1.0f / MaxAnimPatternX)+ ((1.0f / MaxAnimPatternX)*m_nPatturnAnim2),
													(1.0f / MaxAnimPatternY)+ (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternY)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim2)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim2)));
		}
		break;
	}
}
//=============================================================================
// チュートリアルのポリゴンの初期位置
//=============================================================================
void CSelectMenu::InitTutorialPolygon(void)
{
	/* メニューポリゴンの設定 */
	m_InitPos.y = MENU_INITPOS;

	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{//メニューポリゴンの初期化
		m_apPolygon[nCnt] = NULL;
	}

	/* 背景設定 */
	//背景
	m_apPolygonBG[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_BG", 2);
	m_apPolygonBG[0]->SetWidthHeight(MENU_BG*6.0f, MENU_BG * 3.5f);

	//モード名帯（左）
	m_apPolygonBG[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_UI", 2);
	m_apPolygonBG[1]->SetWidthHeight(MENU_BG*BAND_SIZE, MENU_BG * 3.5f);

	//モード名帯（右）
	m_apPolygonBG[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_UI", 2);
	m_apPolygonBG[2]->SetWidthHeight(MENU_BG*BAND_SIZE, MENU_BG * 3.5f);

	//フレーム
	m_apPolygonBG[3] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 640.0f, m_InitPos.z), "FRAME", 2);
	m_apPolygonBG[3]->SetWidthHeight(SCREEN_WIDTH / 2 * 1.1f, MENU_BG * 0.7f);

	//説明文
	m_apPolygonBG[4] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 645.0f, m_InitPos.z), "SELECTMODE_EXPLANATION", 2);
	m_apPolygonBG[4]->SetWidthHeight(SCREEN_WIDTH / 2 * 1.0f, MENU_BG * 0.63f);
	m_apPolygonBG[4]->SetAnimation(0, 1.0f, 0.33f);

	//アニメーション：ゲーム
	m_apPolygonBG[5] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygonBG[5]->SetWidthHeight(MENU_BG*1.5f, MENU_BG * 1.5f);
	m_apPolygonBG[5]->SetTex(D3DXVECTOR2(0.0f, 0.666f), D3DXVECTOR2(0.5f, 0.999f));

	//アニメーション：文字一覧
	m_apPolygonBG[6] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygonBG[6]->SetWidthHeight(MENU_BG*1.55f, MENU_BG * 1.55f);
	m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.0f, 0.333f), D3DXVECTOR2(0.5f, 0.666f));

	//アニメーション：タイトルに戻る
	m_apPolygonBG[7] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygonBG[7]->SetWidthHeight(MENU_BG*1.2f, MENU_BG * 1.2f);
	m_apPolygonBG[7]->SetAnimation(0, 0.5f, 0.333f);

	//UI_スティック
	m_apPolygonBG[8] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 250.0f, m_InitPos.z), "UI_OPERATION1", 2);
	m_apPolygonBG[8]->SetWidthHeight(MENU_BG*0.7f, MENU_BG * 0.7f);
	m_apPolygonBG[8]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));

	//UI_選択中
	m_apPolygonBG[9] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_SELECT");
	m_apPolygonBG[9]->SetWidthHeight(m_fWidth*1.02f, m_fHeight * 1.05f);
	m_apPolygonBG[9]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));


	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{
		m_Pos[nCnt] = m_InitPos;
		m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
		//位置をずらす
		m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU", 2);
			m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 1.0f));
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}
}