//=============================================================================
//
// 軌跡処理 [LineOrbit.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "LineOrbit.h"
#include "manager.h"

#include "debugProc.h"
//=============================================================================
//
// 軌跡クラス (CLineOrbit)
// Author : Kodama Yuto
//
//=============================================================================

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CLineOrbit::CLineOrbit(int pri, OBJTYPE type) : CScene(pri,type)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;

	m_nVtxNum = 0;
	m_nIdxNum = 0;
	m_nPolygonNum = 0;

	m_apMesh = NULL;
}

CLineOrbit::~CLineOrbit()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CLineOrbit* CLineOrbit::Create(void)
{
	CLineOrbit* pOrbit = NULL;

	pOrbit = new CLineOrbit(6,OBJTYPE_ORBIT);

	if (pOrbit != NULL)
	{
		pOrbit->Init();
	}

	return pOrbit;
}

//=============================================================================
// 設定処理
//=============================================================================
void  CLineOrbit::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fScale, D3DXMATRIX* parent, LPCSTR Tag,
	D3DXCOLOR col, unsigned int nMeshNum, unsigned int nPointCreateTime)
{
	m_nCount = 0;
	m_pos = pos;
	m_offset = pos;
	m_rot = rot;
	m_fScale = fScale;
	m_Parent = parent;
	m_color = col;

	m_nMeshNum = nMeshNum;
	if (m_nMeshNum == 0) { m_nMeshNum = 1; }

	m_nPointCreateTime = nPointCreateTime;
	if (m_nPointCreateTime == 0) { m_nPointCreateTime = 1; }

	m_nVtxNum = (nMeshNum * 2) + 2;
	m_nIdxNum = m_nVtxNum;
	m_nPolygonNum = m_nVtxNum / 2;

	//頂点数分だけ動的生成
	m_apMesh = new D3DXVECTOR3[m_nVtxNum];
	if (m_apMesh != NULL)
	{
		for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
		{
			m_apMesh[nCntVtx] = pos + D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		m_apMesh[0] = pos + D3DXVECTOR3(0.0f,fScale,0.0f);
		m_apMesh[1] = pos + D3DXVECTOR3(0.0f, -fScale, 0.0f);

	}

	//頂点バッファ
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
		pDevice = pRenderer->GetDevice();
	}



	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtxNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
	{
		pVtx[nCntVtx].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		pVtx[nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[nCntVtx].col = m_color;
		pVtx[nCntVtx].tex = D3DXVECTOR2((nCntVtx / 2.0f) * 1.0f,(nCntVtx % 2) * 1.0f);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


	//インデックスバッファ
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nIdxNum,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);
	WORD *pIdx;	// インデックスデータへのポインタ

				// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);
	for (int nCntIdx = 0; nCntIdx < m_nIdxNum; nCntIdx++)
	{
		pIdx[nCntIdx] = nCntIdx;	//そのままつなぐ
	}
	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	//テクスチャ
	m_pTexture = CTexture::GetTexture("LINE");
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLineOrbit::Init(void)
{
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLineOrbit::Uninit(void)
{
	//
	if (m_apMesh != NULL)
	{
		delete[] m_apMesh;
		m_apMesh = NULL;
	}

	//頂点バッファ
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	//インデックスバッファ
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	m_pTexture = NULL;

	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLineOrbit::Update(void)
{
	m_nCount++;

	//CDebugProc::ReleseStr();
	//位置の更新
	m_pos = m_offset;
	if (m_Parent != NULL)
	{
		m_pos = D3DXVECTOR3(m_Parent->_41, m_Parent->_42, m_Parent->_43);
	}

	//メッシュの更新
	if (m_apMesh != NULL)
	{
		if (m_nCount % m_nPointCreateTime == 0)
		{
			//二回回す
			for (int nCntMesh = m_nVtxNum - 1; nCntMesh >= 1; nCntMesh--)
			{
				m_apMesh[nCntMesh] = m_apMesh[nCntMesh - 1];
			}
			for (int nCntMesh = m_nVtxNum - 1; nCntMesh >= 1; nCntMesh--)
			{
				m_apMesh[nCntMesh] = m_apMesh[nCntMesh - 1];
			}

			m_apMesh[0] = m_pos + D3DXVECTOR3(0.0f, m_fScale, 0.0f);
			m_apMesh[1] = m_pos + D3DXVECTOR3(0.0f, -m_fScale, 0.0f);
		}
	}

	//頂点の更新
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
	{
		pVtx[nCntVtx].pos = m_apMesh[nCntVtx];
		//CDebugProc::Print("cfcfcf","pos : X = ",m_apMesh[nCntVtx].x,
		//						   "pos : Y = ", m_apMesh[nCntVtx].y,
		//						   "pos : Z = ", m_apMesh[nCntVtx].z);
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
// 描画処理
//=============================================================================
void CLineOrbit::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
		pDevice = pRenderer->GetDevice();
	}

	//ワールドマトリックスの生成(位置は頂点バッファで反映しているので空の値を入れる)
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,D3DXVECTOR3(0.0f,0.0f,0.0f),m_rot);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	//両面カリングを行う
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//ライト無効化
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ポリゴンの描画(見栄えのために複数回描画する)
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtxNum, 0, m_nPolygonNum);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtxNum, 0, m_nPolygonNum);

	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nVtxNum, 0, m_nPolygonNum);

	// 設定を元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


}
