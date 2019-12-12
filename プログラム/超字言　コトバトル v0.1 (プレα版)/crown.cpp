//=============================================================================
//
// 王冠処理 [crown.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// ヘッダファイルのインクルード
//*****************************************************************************
#include "crown.h"
#include "manager.h"		// マネージャー
#include "renderer.h"		// レンダラー
#include "crown.h"
#include "game.h"
#include "sceneBillboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CCrown::CCrown() : CSceneBillBoard()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_bDraw = true;
	m_nCamera = 0;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{	//他プレイヤーから見えているかどうか
		m_bVision[nCnt] = true;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CCrown::~CCrown()
{
}

//=============================================================================
//	アイテムの生成
//=============================================================================
CCrown *CCrown::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, char *cpName)
{
	CCrown *pWall = {};

	if (pWall == NULL)
	{//	アイテムの生成
		pWall = new CCrown;
		if (pWall != NULL)
		{//アイテムの初期化
			pWall->Init(pos, size, cpName);
		}
	}
	return pWall;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CCrown::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, char *cpName)
{
	CSceneBillBoard::Init(pos);
	CSceneBillBoard::SetBillboard(pos, size.y, size.x);
	CSceneBillBoard::BindTexture("crown");
	CSceneBillBoard::SetTexture(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2((0.333f * 1), 1.0f));
	CSceneBillBoard::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetObjType(CScene::OBJTYPE_CROWN);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CCrown::Uninit(void)
{
	CSceneBillBoard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CCrown::Update(void)
{
	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();

	CSceneBillBoard::Setpos(pos);
}

//=============================================================================
// 描画処理
//=============================================================================
void CCrown::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//if (m_bDraw == true && m_bVision[m_nCamera] == true)
	{
		//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// カリングなくす
		CSceneBillBoard::Draw();
		//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面をカリングに戻す
	}
}
