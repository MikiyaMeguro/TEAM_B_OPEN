//=============================================================================
//
// 数字処理 [number.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "number.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "texture.h"
//=============================================================================
//	静的メンバ変数
//=============================================================================

//=============================================================================
//	マクロ定義
//=============================================================================
#define NUMBER_SIZE_X		(18.0f)									// 数字の横幅
#define NUMBER_SIZE_Y		(22.0f)									// 数字の縦幅

//=============================================================================
// コンストラクタ
//=============================================================================
CNumber::CNumber()
{
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0, 1.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CNumber::~CNumber(){}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, int nType)
{
	m_pos = D3DXVECTOR2(pos.x, pos.y);
	// デバイス取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ゲームの情報
	CManager::MODE pMode = CManager::GetMode();

	// 番号の設定
	m_nType = nType;

	// 頂点バッファ生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報へのポインタ
	VERTEX_2D * pVtx;

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	
	pVtx[0].pos = D3DXVECTOR3(pos.x - NUMBER_SIZE_X, pos.y - NUMBER_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + NUMBER_SIZE_X, pos.y - NUMBER_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - NUMBER_SIZE_X, pos.y + NUMBER_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + NUMBER_SIZE_X, pos.y + NUMBER_SIZE_Y, 0.0f);

	for (int nCntrhw = 0; nCntrhw < 4; nCntrhw++)
	{
		pVtx[nCntrhw].rhw = 1.0f;
	}

	for (int nCntCol = 0; nCntCol < 4; nCntCol++)
	{
		pVtx[nCntCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファ破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	delete this;
}

//=============================================================================
// 更新処理
//=============================================================================
void CNumber::Update(void){}

//=============================================================================
// 描画処理
//=============================================================================
void CNumber::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 	pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマット設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャ設定
	pDevice->SetTexture(0, CTexture::GetTexture("NUMBER"));

	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ナンバーの設定
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2((nNumber % 10) * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2((nNumber % 10) * 0.1f + 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2((nNumber % 10) * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2((nNumber % 10) * 0.1f + 0.1f, 1.0f);

		//頂点バッファをアンロックする
		m_pVtxBuff->Unlock();
	}
}

//=============================================================================
// サイズ設定
//=============================================================================
void CNumber::SetSize(D3DXVECTOR2 size, D3DXVECTOR2 pos)
{
	m_size = size;
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//サイズ設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x , pos.y - size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定
//=============================================================================
void CNumber::SetCol(D3DXCOLOR col)
{
	m_col = col;
	VERTEX_2D *pVtx;				//頂点情報へのポインタ

	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 色の設定
	for (int nCntCol = 0; nCntCol < 4; nCntCol++)
	{
		pVtx[nCntCol].col = col;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}