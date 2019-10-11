//=============================================================================
//
// 番号クラス処理 [number.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "number.h"
#include "Manager.h"

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_pTexture = NULL;
}
CNumber::~CNumber()
{

}

//==================================================================
// 設定処理
//==================================================================
void CNumber::Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum, D3DXCOLOR Col)
{
	m_pos = pos;
	m_polygonRect = polygonRect;
	m_nNumber = nNum;
	m_Col = Col;

	// 頂点情報を設定
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, 0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_polygonRect.y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, m_polygonRect.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}
//==================================================================
// 初期化処理
//==================================================================
HRESULT CNumber::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//テクスチャの紐づけ
	m_pTexture = CTexture::GetTexture("NUMBER");

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CNumber::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	m_pTexture = NULL;
}

//==================================================================
// 更新処理
//==================================================================
void CNumber::Update(void)
{
	// 頂点情報を設定
	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, 0.0f, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, m_polygonRect.y, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(m_polygonRect.x, m_polygonRect.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();
}

//==================================================================
// 描画処理
//==================================================================
void CNumber::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	if (m_pTexture != NULL)
	{
		pDevice->SetTexture(0, m_pTexture);
	}
	else
	{
		pDevice->SetTexture(0, NULL);
	}

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


}

//==================================================================
// 番号設定処理
//==================================================================
void CNumber::SetNumber(int nNum)
{
	m_nNumber = nNum;

	VERTEX_2D* pVtx;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2((m_nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2((m_nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2((m_nNumber * 0.1f) + 0.1f, 1.0f);

	m_pVtxBuff->Unlock();


}
