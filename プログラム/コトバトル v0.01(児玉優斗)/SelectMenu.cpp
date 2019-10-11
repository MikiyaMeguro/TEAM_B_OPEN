//---------------------------------------------------------------------
// セレクトメニュー処理 [SelectMenu.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SelectMenu.h"
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
#define MODESELECT_WIDTH		(2.0f)		//ポリゴンの大きさ(横)
#define MODESELECT_HEIGHT		(0.9f)		//ポリゴンの大きさ(縦)
#define MENU_WIDTH				(450.0f)	//ポリゴンとポリゴンの間の大きさ(横)
#define MENU_HEIGHT				(220.0f)	//ポリゴンとポリゴンの間の大きさ(縦)
#define MENU_INITPOS			(180.0f)	//メニューの初期位置
#define MENU_NUM_HEIGHT			(2)
#define MENU_NUM_WIDTH			(2)
#define MENU_INIT_POS			(400.0f)

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
CSelectMenu *CSelectMenu::Create(D3DXVECTOR3 pos, float m_fWidth, MENU_TYPE type)
{
	//セレクトメニューのポインタ
	CSelectMenu *pMenuSelect;
	pMenuSelect = new CSelectMenu;
	pMenuSelect->m_MenuType = type;
	pMenuSelect->m_InitPos = pos;
	pMenuSelect->m_fWidth = m_fWidth;
	pMenuSelect->m_fHeight = m_fWidth;
	//セレクトメニューの初期化
	pMenuSelect->Init(pos);
	//セレクトメニューの情報を返す
	return pMenuSelect;
}


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSelectMenu::Init(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < MAX_SELECTMENU; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
	}

	//m_pTextureBG = CLoad::GetTexture(CLoad::TEXTURE_MODESELECT_BG);
	m_pTexture[0] = CTexture::GetTexture("BLOCK");
	m_pTexture[1] = CTexture::GetTexture("BLOCK");
	m_pTexture[2] = CTexture::GetTexture("BLOCK");

	//BGの初期化
	m_apPolygonBG = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y, m_InitPos.z),"BLOCK");
	m_apPolygonBG->BindTexture(m_pTextureBG);
	m_apPolygonBG->SetWidthHeight(m_fWidth * 4.5f, m_fHeight * 3.5f);
	m_apPolygonBG->SetbDraw(true);

	m_InitPos.y = MENU_INITPOS;

	for (int nCnt = 0; nCnt < MAX_SELECTMENU; nCnt++)
	{
		m_Pos[nCnt] = m_InitPos;
		m_Pos[nCnt].y = m_InitPos.y + MENU_INIT_POS;
		//位置をずらす
		m_Pos[nCnt].y = m_Pos[nCnt].y + (MENU_HEIGHT * (nCnt - 2));


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
	//ジョイパッド情報を取得
	CXInputJoyPad *pXInput = NULL;
	pXInput = CManager::GetXInput();
	//フェードを取得
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();


	//サウンド情報を取得
	CSound *pSound = CManager::GetSound(0);

	//表示切替
	for (int nCnt = 0; nCnt < MAX_SELECTMENU; nCnt++)
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

	//セレクトメニュー中
	if (m_bModeSelect == true)
	{
		//選択処理
		if (CCommand::GetCommand("DOWN"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect < 2)
			{
				m_nSelect = (m_nSelect + MAX_SELECTMENU / 2) % MAX_SELECTMENU;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("UP"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect > 0)
			{
				m_nSelect = (m_nSelect + 2) % MAX_SELECTMENU;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}

		//エンターキー
		if (pInput->GetTrigger(DIK_RETURN) == true)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_CANCEL);
			if (m_nSelect == 0)
			{
				m_SelectMode = SELECT_MENU_ONE;
				MenuDecide(SELECT_MENU_TWO);
			}
			else if (m_nSelect == 1)
			{
				m_SelectMode = SELECT_MENU_TWO;
				MenuDecide(SELECT_MENU_TWO);
			}
			else if (m_nSelect == 2)
			{
				m_SelectMode = SELECT_MENU_THREE;
				MenuDecide(SELECT_MENU_TWO);
			}
			else if (m_nSelect == 3)
			{
				m_SelectMode = SELECT_MENU_FOUR;
				MenuDecide(SELECT_MENU_TWO);
			}

				m_bModeSelect = false;


		}

		//色変え
		for (int nCnt = 0; nCnt < MAX_SELECTMENU; nCnt++)
		{
			if (m_aModeSelectMenu[nCnt].select == SELECTTYPE_SELECT)
			{//選択中の色
				m_aModeSelectMenu[nCnt].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{//未選択の色
				m_aModeSelectMenu[nCnt].col = D3DXCOLOR(0.9f, 0.9f, 0.9f, 1.0f);
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

		//頂点情報へのポインタ
		VERTEX_2D *pVtx;
		//頂点バッファを取得
		m_pVtxBuff = m_apPolygonBG->GetBuff();
		//頂点バッファをロックし頂点データのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		//頂点テクスチャ
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
#ifdef _DEBUG
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif

}

//=============================================================================
// セレクトメニュークラス 描画処理
//=============================================================================
void CSelectMenu::Draw(void)
{
}

//=============================================================================
// セレクトメニュークラス　選択したモードを取得
//=============================================================================
CSelectMenu::SELECT_MENU * CSelectMenu::GetModeSelectMode(void)
{
	return &m_SelectMode;
}

//=============================================================================
// テクスチャの読み込み処理
//=============================================================================
HRESULT CSelectMenu::Load(void)
{

	return S_OK;
}

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
// セレクトメニューの状態を取得
//=============================================================================
bool CSelectMenu::GetModeSelectBool(void)
{
	return m_bModeSelect;
}

//=============================================================================
// セレクトメニューの状態を設定
//=============================================================================
void CSelectMenu::SetModeSelectBool(bool ModeSelectBool)
{
	m_bModeSelect = ModeSelectBool;
}

//=============================================================================
// 決定したメニューの処理
//=============================================================================
void CSelectMenu::MenuDecide(SELECT_MENU MenuSelect)
{
}

