//=============================================================================
//
// ポーズ画面クラス処理 [pause.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "pause.h"
#include "Manager.h"
#include "fade.h"

//=============================================================================
//	コンストラクタ&デストラクタ
//=============================================================================
CPause::CPause()
{
	m_pVtxBuff = NULL;
	for (int nCntTex = 0; nCntTex < PAUSE_POLYGON_NUM; nCntTex++)
	{
		m_apTexture[nCntTex] = NULL;
	}
}

CPause::~CPause()
{

}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CPause::Init(void)
{
	//変数宣言
	VERTEX_2D* pVtx;

	//デバイス取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();


	//テクスチャ適用
	m_apTexture[0] = CTexture::GetTexture("PAUSE_BG");
	m_apTexture[1] = CTexture::GetTexture("PAUSE_TUTORIAL");
	m_apTexture[2] = CTexture::GetTexture("PAUSE_MENU_CONTINUE");
	m_apTexture[3] = CTexture::GetTexture("PAUSE_MENU_QUIT");

	//初期化
	m_nSelectMenu = 0;
	m_SelectColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);


	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * PAUSE_POLYGON_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	/*バックスクリーン*/
	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラー	白
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, PAUSE_COL_A);
	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	/*操作説明*/
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH - 350.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH - 350.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx += 4;


	/*ポーズUI*/
	for (int nCntPausePolygon = 0; nCntPausePolygon < 2; nCntPausePolygon++)
	{

		pVtx[0].pos = D3DXVECTOR3(350.0f, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[1].pos = D3DXVECTOR3(780.0f, 140.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[2].pos = D3DXVECTOR3(350.0f, 190.0f + (250 * nCntPausePolygon), 0.0f);
		pVtx[3].pos = D3DXVECTOR3(780.0f, 190.0f + (250 * nCntPausePolygon), 0.0f);

		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx += 4;

	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
//	終了処理
//=============================================================================
void CPause::Uninit(void)
{
	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	for (int nCntTex = 0; nCntTex < PAUSE_POLYGON_NUM; nCntTex++)
	{
		m_apTexture[nCntTex] = NULL;
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void CPause::Update(void)
{
	CFade* pFade = CManager::GetFade();
	//モード選択(keyboard)
	if (CCommand::GetCommand("PAUSE_MENU_UP"))//↑
	{
		m_nSelectMenu = (m_nSelectMenu + 1) % SELECT_NUM;//0→1→0
	}
	else if (CCommand::GetCommand("PAUSE_MENU_DOWN"))//↓
	{
		m_nSelectMenu = (m_nSelectMenu + (SELECT_NUM - 1)) % SELECT_NUM;//0→1→0
	}

	if (CCommand::GetCommand("ENTER"))
	{//押したときのg_nSerectPauseMenuの位置に応じて挙動を決める
		switch (m_nSelectMenu)
		{
		case 0://再開
			CManager::ChangePauseFlag();
			break;
		case 1://終了
			if (*pFade->GetFade() != CFade::FADE_OUT)
			{
				pFade->SetFade(CManager::MODE_TITLE, CFade::COLOR_WHITE);
				CManager::ChangePauseFlag();
				m_nSelectMenu = 0;
				//BGMを消してSEを鳴らす
			}
			break;
		}


	}


	//色変更
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	for (int nCntPausePolygon = 2; nCntPausePolygon < PAUSE_POLYGON_NUM; nCntPausePolygon++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx += 4 * nCntPausePolygon;

		pVtx[0].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	pVtx += 4 * (m_nSelectMenu + 2);

	pVtx[0].col = m_SelectColor;
	pVtx[1].col = m_SelectColor;
	pVtx[2].col = m_SelectColor;
	pVtx[3].col = m_SelectColor;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//	描画処理
//=============================================================================
void CPause::Draw(void)
{
	//デバイス取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//描画
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_2D);//頂点フォーマットの設定

		//ポリゴンの描画
	for (int nCntPausePolygon = 0; nCntPausePolygon < PAUSE_POLYGON_NUM; nCntPausePolygon++)
	{
		// テクスチャの設定
		if (m_apTexture[nCntPausePolygon] != NULL)
		{
			pDevice->SetTexture(0, m_apTexture[nCntPausePolygon]);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類		    //プリミティブ == ポリゴン
			4 * nCntPausePolygon,				   //開始する頂点のインデックス(基本０)
			2);		   							   //プリミティブの数

	}
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

}