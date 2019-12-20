//---------------------------------------------------------------------
// クレジット処理 [credit.cpp]
// Author : Yokomichi Shun
//---------------------------------------------------------------------
#include "credit.h"
#include "scene2D.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BACK_BG_POS	 (D3DXVECTOR3(1170.0f, 680.0f, 0.0f))	// 戻るの位置
#define BACK_BG_SIZE (D3DXVECTOR2(150.0f, 50.0f))			// 戻るのサイズ
//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------

//--------------------------------------------
//モードセレクトクラス コンストラクタ
//--------------------------------------------
CCredit::CCredit(int nPriority) : CScene(7)
{
	m_pCredit = NULL;
	m_pBack = NULL;
	m_nCntFlash = 0;
}

//--------------------------------------------
//モードセレクトクラス デストラクタ
//--------------------------------------------
CCredit::~CCredit(){}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CCredit *CCredit::Create()
{
	//モードセレクトのポインタ
	CCredit *pCredit;
	pCredit = new CCredit;

	//モードセレクトの初期化
	pCredit->Init();
	//モードセレクトの情報を返す
	return pCredit;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCredit::Init(void)
{
	SetInit();	// クレジットの位置設定

	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);
	return S_OK;
}

//=============================================================================
// モードセレクトクラス 終了処理
//=============================================================================
void CCredit::Uninit(void)
{
	if (m_pCredit != NULL) { m_pCredit->Uninit(); m_pCredit = NULL; }
	if (m_pBack != NULL) { m_pBack->Uninit(); m_pBack = NULL; }

	//自分を破棄
	Release();
}

//=============================================================================
// モードセレクトクラス 更新処理
//=============================================================================
void CCredit::Update(void)
{
	Flash();	// 点滅処理

	if (CManager::GetXInput(0)->GetTrigger(CInputXPad::XPAD_RIGHT_SHOULDER) || CManager::GetInputKeyboard()->GetTrigger(DIK_BACKSPACE))
	{
		Uninit();
		CManager::SetMode(CManager::MODE_SELECT);
	}
}

//=============================================================================
// モードセレクトクラス 描画処理
//=============================================================================
void CCredit::Draw(void){}

//=============================================================================
// モードセレクトクラス 位置設定
//=============================================================================
void CCredit::SetInit(void)
{
	if (m_pCredit == NULL)
	{	//クレジット
		m_pCredit = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 , 0.0f), "CREADIT_BG", 5);
		m_pCredit->SetWidthHeight(SCREEN_WIDTH, SCREEN_HEIGHT);
	}

	if (m_pBack == NULL)
	{	// 戻るボタン
		D3DXVECTOR3 pos = BACK_BG_POS;
		m_pBack = CScene2D::Create(pos, "BACK_PRESS", 6);
		m_pBack->SetWidthHeight(BACK_BG_SIZE.x, BACK_BG_SIZE.y);
		m_pBack->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

//=============================================================================
// モードセレクトクラス 色の点滅
//=============================================================================
void CCredit::Flash(void)
{
	if (m_pBack != NULL)
	{
		D3DXCOLOR col = m_pBack->GetCol();
		col.a -= 0.01f;
		if (col.a < 0.3f) 
		{	// 指定した色の値以下の場合
			col.a = 1.0f;
		}

		m_pBack->SetCol(col);
	}
}