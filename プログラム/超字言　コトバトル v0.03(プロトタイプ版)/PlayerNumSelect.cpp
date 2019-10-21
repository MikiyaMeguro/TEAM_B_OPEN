//---------------------------------------------------------------------
// モードセレクト処理 [modeselect.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "PlayerNumSelect.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "load.h"
#include "texture.h"
#include "debugProc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODESELECT_WIDTH		(3.0f)		//ポリゴンの大きさ(横)
#define MODESELECT_HEIGHT		(1.5f)		//ポリゴンの大きさ(縦)
#define MENU_WIDTH				(450.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define MENU_HEIGHT				(250.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define MENU_INITPOS			(320.0f)	//メニューの初期位置
#define MENU_NUM_HEIGHT			(2)
#define MENU_NUM_WIDTH			(2)
#define LOGO_POS				(100.0f)
#define LOGO_WIDTH				(4.5f)		//ポリゴンの大きさ(横)
#define LOGO_HEIGHT				(1.2f)		//ポリゴンの大きさ(縦)

#define CAUTIONBG_WIDTH			(750.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define CAUTIONBG_HEIGHT		(450.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define CAUTION_WIDTH			(650.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define CAUTION_HEIGHT			(250.0f)	//ポリゴンとポリゴンの間の大きさ(縦)



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
	m_aModeSelectMenu[0].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bCaution = false;
	m_bCreate2D = false;
	m_nSelectCaution = 1;
	m_SelectCaution[0].select = SELECTTYPE_NONE;
	m_SelectCaution[1].select = SELECTTYPE_SELECT;
}

//--------------------------------------------
//モードセレクトクラス デストラクタ
//--------------------------------------------
CPlayerSelect::~CPlayerSelect()
{
}

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
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
	}

	m_pSelect2D[0] = NULL;
	m_pSelect2D[1] = NULL;
	m_pCaution2D = NULL;
	m_pCaution2DBG = NULL;
	//m_pTextureBG = CLoad::GetTexture(CLoad::TEXTURE_MODESELECT_BG);
	m_pTexture[0] = CTexture::GetTexture("MENU_1P");
	m_pTexture[1] = CTexture::GetTexture("MENU_2P");
	m_pTexture[2] = CTexture::GetTexture("MENU_3P");
	m_pTexture[3] = CTexture::GetTexture("MENU_4P");

	//BGの初期化
	m_apPolygonBG = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y, m_InitPos.z),"BLOCK");
	m_apPolygonBG->BindTexture(m_pTextureBG);
	m_apPolygonBG->SetWidthHeight(m_fWidth * 4.9f, m_fHeight * 3.5f);
	m_apPolygonBG->SetbDraw(true);

	m_InitPos.y = MENU_INITPOS;

	m_pMenuLogo = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, LOGO_POS, m_InitPos.z), "MENU_NUMPLAYER");
	m_pMenuLogo->SetWidthHeight(m_fWidth * LOGO_WIDTH, m_fHeight * LOGO_HEIGHT);
	m_pMenuLogo->SetbDraw(true);



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
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "BLOCK");
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}

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
// モードセレクトクラス 終了処理
//=============================================================================
void CPlayerSelect::Uninit(void)
{

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
	m_apPolygonBG->SetbDraw(m_bModeSelect);


#ifdef  _DEBUG
	if (pInput->GetTrigger(DIK_O) == true)
	{//TRUEならFALSE FALSEならTRUE
		m_bModeSelect = m_bModeSelect ? false : true;
	}
#endif

	//モードセレクト中
	if (m_bModeSelect == true && pFade->GetFade() == CFade::FADE_NONE)
	{
		//選択処理
		if (CCommand::GetCommand("DOWN") && m_bCaution == false)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect < 2)
			{
				m_nSelect = (m_nSelect + MAX_PLAYER_SELECTMENU / 2) % (MAX_PLAYER_SELECTMENU);
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("UP") && m_bCaution == false)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect > 1)
			{
				m_nSelect = m_nSelect - 2;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("RIGHT") && m_bCaution == false)
		{
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect == 1)
			{
				m_nSelect = 1;
			}
			else if (m_nSelect == 3)
			{
				m_nSelect =  3;
			}
			else
			{
				m_nSelect = (m_nSelect + 1) % 4;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("LEFT") && m_bCaution == false)
		{
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
		if (CCommand::GetCommand("ENTER")== true && m_bCaution == false)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_CANCEL);
			if (m_nSelect == 0)
			{
				m_SelectMode = SELECTPLAYER_1P;
			}
			else if (m_nSelect == 1)
			{
				m_SelectMode = SELECTPLAYER_2P;
			}
			else if (m_nSelect == 2)
			{
				m_SelectMode = SELECTPLAYER_3P;
			}
			else if (m_nSelect == 3)
			{
				m_SelectMode = SELECTPLAYER_4P;
			}
			//警告を表示
			m_bCaution = true;
		}

		//最終警告	2Dが作成されたら
		if (CCommand::GetCommand("ENTER") && m_bCreate2D == true)
		{
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
			if (m_bCreate2D == false)
			{
				//警告を生成
				m_pCaution2DBG = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), "BLOCK");
				m_pCaution2DBG->SetWidthHeight(CAUTIONBG_WIDTH, CAUTIONBG_HEIGHT);
				m_pCaution2DBG->SetbDraw(true);
				m_pCaution2DBG->BindTexture(m_pTextureBG);

				m_pCaution2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3.0f, 0), "BLOCK");
				m_pCaution2D->SetWidthHeight(CAUTION_WIDTH, CAUTION_HEIGHT);
				m_pCaution2D->BindTexture(CTexture::GetTexture("MENU_START"));
				m_pCaution2D->SetbDraw(true);

				//YES or NO　ポリゴン生成
				for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
				{
					//ポリゴンの位置を左上に初期化
					m_Pos[nCnt] = m_InitPos;
					m_Pos[nCnt].x = m_InitPos.x - (350 / 2);
					//位置をずらす
					m_Pos[nCnt].x = m_Pos[nCnt].x + (360 * nCnt);
					m_Pos[nCnt].y = 500.0f;
					if (m_pSelect2D[nCnt] == NULL)
					{	//生成
						m_pSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MENU_START");
						m_pSelect2D[nCnt]->SetWidthHeight(600, 300);
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
					}
					else
					{//未選択の色
						m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					//頂点情報へのポインタ
					VERTEX_2D *pVtx;
					//頂点バッファを取得
					m_pVtxBuff = m_pSelect2D[nCnt]->GetBuff();
					//頂点バッファをロックし頂点データのポインタを取得
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
					//頂点カラー
					pVtx[0].col = m_SelectCaution[nCnt].col;
					pVtx[1].col = m_SelectCaution[nCnt].col;
					pVtx[2].col = m_SelectCaution[nCnt].col;
					pVtx[3].col = m_SelectCaution[nCnt].col;
					// 頂点バッファをアンロックする
					m_pVtxBuff->Unlock();
				}
			}

			if (CCommand::GetCommand("RIGHT") && m_bCaution == true)
			{
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
				m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
				//左端で止まる
				if (m_nSelectCaution > 0)
				{
					m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
				}
				m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
			}
		}

		//色変え
		for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
		{
			if (m_aModeSelectMenu[nCnt].select == SELECTTYPE_SELECT)
			{//選択中の色
				m_aModeSelectMenu[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{//未選択の色
				m_aModeSelectMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//頂点情報へのポインタ
			VERTEX_2D *pVtx;
			//頂点バッファを取得
			m_pVtxBuff = m_apPolygon[nCnt]->GetBuff();
			//頂点バッファをロックし頂点データのポインタを取得
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			//頂点カラー
			pVtx[0].col = m_aModeSelectMenu[nCnt].col;
			pVtx[1].col = m_aModeSelectMenu[nCnt].col;
			pVtx[2].col = m_aModeSelectMenu[nCnt].col;
			pVtx[3].col = m_aModeSelectMenu[nCnt].col;
			// 頂点バッファをアンロックする
			m_pVtxBuff->Unlock();
		}

		////頂点情報へのポインタ
		//VERTEX_2D *pVtx;
		////頂点バッファを取得
		//m_pVtxBuff = m_apPolygonBG->GetBuff();
		////頂点バッファをロックし頂点データのポインタを取得
		//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		////頂点テクスチャ
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//// 頂点バッファをアンロックする
		//m_pVtxBuff->Unlock();
	}
#ifdef _DEBUG
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif

}

//=============================================================================
// モードセレクトクラス 描画処理
//=============================================================================
void CPlayerSelect::Draw(void)
{
}

//=============================================================================
// モードセレクトクラス　選択したモードを取得
//=============================================================================
CPlayerSelect::SELECTPLAYER * CPlayerSelect::GetModeSelectMode(void)
{
	return &m_SelectMode;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CPlayerSelect::Load(void)
{

	return S_OK;
}

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
// モードセレクトの状態を取得
//=============================================================================
bool CPlayerSelect::GetModeSelectBool(void)
{
	return m_bModeSelect;
}

//=============================================================================
// モードセレクトの状態を設定
//=============================================================================
void CPlayerSelect::SetModeSelectBool(bool ModeSelectBool)
{
	m_bModeSelect = ModeSelectBool;
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

