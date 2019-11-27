//=============================================================================
//
// 球メッシュクラス [meshSphere.cpp]
// Author : Kodama Yuto
//	注意　爆発用なので単体では使わないこと！！
//
//=============================================================================
#include "meshSphere.h"
#include "manager.h"

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CMeshSphere::CMeshSphere(int pri, OBJTYPE type) : CScene(pri,type)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;
}
CMeshSphere::~CMeshSphere()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CMeshSphere* CMeshSphere::Create(void)
{
	CMeshSphere* pSphere = NULL;

	pSphere = new CMeshSphere(1, OBJTYPE_MESH_SPHERE);

	if (pSphere != NULL)
	{
		pSphere->Init();
	}

	return pSphere;
}

//=============================================================================
// 設定処理
//=============================================================================
void CMeshSphere::Set(D3DXVECTOR3 pos, LPCSTR Tag, int nMeshWidth, int nMeshHeight, D3DXVECTOR3 Size, D3DXCOLOR Col,D3DXVECTOR3 rot)
{
	//デバイスを取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//値の設定
	m_pos = pos;
	m_rot = rot;
	m_Size = Size;
	m_Color = Col;

	m_nMeshWidth = nMeshWidth;
	m_nMeshHeight = nMeshHeight;

	//// 頂点数
	//m_nVtxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1);
	m_nVtxNum = m_nMeshWidth * (m_nMeshHeight + 1);

	//// インデックス数
	//m_nIdxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1)
	//	+ (2 * (m_nMeshHeight - 1))
	//	+ (m_nMeshWidth + 1) * (m_nMeshHeight - 1);
	m_nIdxNum = 2 * m_nMeshHeight * (m_nMeshWidth + 1);

	//// ポリゴン数
	m_nPolygonNum =(m_nMeshWidth * m_nMeshHeight * 2) + (4 * (m_nMeshHeight - 1));

	//m_nPolygonNum = m_nIdxNum - 2;
	//頂点バッファ・インデックスバッファの設定
	CreateVertex(pDevice);
	CreateIndex(pDevice);

	//テクスチャの設定
	m_pTexture = CTexture::GetTexture(Tag);
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshSphere::Init(void)
{
	m_pVtxBuff = NULL;
	m_pIdxBuff = NULL;
	m_pTexture = NULL;

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_nMeshWidth = 2;
	m_nMeshHeight = 2;
	m_nVtxNum = 2;

	m_AnimTexUV = D3DXVECTOR2(0.0f,0.0f);
	m_nCntTexAnim = 2;
	m_nCount = 0;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshSphere::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}


	// オブジェクトの解放
	Release();

}

//=============================================================================
// 更新処理
//=============================================================================
void CMeshSphere::Update(void)
{
	m_nCount++;

	if (m_nCount % m_nCntTexAnim == 0)
	{
		// 頂点情報の設定
		VERTEX_3D *pVtx;	// 頂点情報へのポインタ
							// 頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
		{
				pVtx[nCntVtx].tex += m_AnimTexUV;
		}

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshSphere::Draw(void)
{
	//デバイスを取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;	// 計算用マトリックス

	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,m_rot,NULL,m_Size);

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

	//pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		m_nVtxNum, 0, m_nPolygonNum);

	//pDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0, 0,
	//	m_nVtxNum, 0, m_nPolygonNum);

}

//=============================================================================
// 頂点バッファ生成処理
//=============================================================================
void CMeshSphere::CreateVertex(LPDIRECT3DDEVICE9 pDev)
{
	//既に作られていたらいったん削除
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// 頂点バッファを生成
	pDev->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nVtxNum,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ
						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntVtxX = 0; nCntVtxX < m_nMeshWidth; nCntVtxX++)
	{
		for (int nCntVtxY = 0; nCntVtxY <= m_nMeshHeight; nCntVtxY++)
		{
			int nNum = (m_nMeshWidth * nCntVtxY) + nCntVtxX;

			float fTheta = D3DXToRadian((180.0f * nCntVtxY) / m_nMeshHeight);
			float fPhi = D3DXToRadian((360.0f * nCntVtxX) / m_nMeshWidth);

			pVtx[nNum].pos = D3DXVECTOR3(sinf(fTheta) * sinf(fPhi),
				cosf(fTheta),
				sinf(fTheta) * cosf(fPhi));

			pVtx[nNum].tex =
				D3DXVECTOR2((nCntVtxX * (1.0f / (float)m_nMeshWidth)),
					(nCntVtxY * (1.0f / (float)m_nMeshHeight)));

			D3DXVECTOR3 nor;
			D3DXVec3Normalize(&nor, &pVtx[nNum].pos);

			pVtx[nNum].nor = nor;
			pVtx[nNum].col = m_Color;

		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// インデックスバッファ生成処理
//=============================================================================
void CMeshSphere::CreateIndex(LPDIRECT3DDEVICE9 pDev)
{
	//既に作られていたらいったん削除
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// インデックスバッファの生成
	pDev->CreateIndexBuffer(sizeof(WORD) * m_nIdxNum,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	WORD *pIdx;	// インデックスデータへのポインタ
	int nIdxCounter = 0;

				// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (int nCntIdxY = 0; nCntIdxY <= m_nMeshHeight; nCntIdxY++) {
		for (int nCntIdxX = 0; nCntIdxX < m_nMeshWidth; nCntIdxX++) {
			if (nCntIdxX == m_nMeshWidth) {
				pIdx[nIdxCounter++] = nCntIdxY * m_nMeshWidth;
				pIdx[nIdxCounter++] = (nCntIdxY + 1) * m_nMeshWidth;
			}
			else {
				pIdx[nIdxCounter++] = (nCntIdxY * m_nMeshWidth) + nCntIdxX;
				pIdx[nIdxCounter++] = pIdx[nIdxCounter - 1] + m_nMeshWidth;
			}
		}
	}


	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

}

//=============================================================================
// 頂点色設定処理
//=============================================================================
void CMeshSphere::SetColor(D3DXCOLOR col)
{
	if (m_pVtxBuff != NULL)
	{
		m_Color = col;

		// 頂点情報の設定
		VERTEX_3D *pVtx;	// 頂点情報へのポインタ
							// 頂点バッファをロックし、頂点データへのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCntVtx = 0; nCntVtx < m_nVtxNum; nCntVtx++)
		{
			pVtx[nCntVtx].col = m_Color;
		}

		// 頂点バッファをアンロックする
		m_pVtxBuff->Unlock();

	}
}