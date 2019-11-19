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
	m_VecNor = NULL;
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

	pSphere = new CMeshSphere(1, OBJTYPE_PARTICLE);

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

	// 頂点数
	m_nVtxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1);

	// インデックス数
	m_nIdxNum = (m_nMeshWidth + 1) * (m_nMeshHeight + 1)
		+ (2 * (m_nMeshHeight - 1))
		+ (m_nMeshWidth + 1) * (m_nMeshHeight - 1);

	// ポリゴン数
	m_nPolygonNum = m_nIdxNum - 2;
	if (m_VecNor != NULL)
	{
		delete[] m_VecNor;
		m_VecNor = NULL;
	}
	m_VecNor = new D3DXVECTOR3[m_nPolygonNum];

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
	m_VecNor = NULL;

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
	//法線情報の削除
	if (m_VecNor != NULL)
	{
		delete[] m_VecNor;
		m_VecNor = NULL;
	}
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

		for (int nCntVtxY = 0; nCntVtxY <= m_nMeshHeight; nCntVtxY++)
		{
			for (int nCntVtxX = 0; nCntVtxX < m_nMeshWidth; nCntVtxX++)
			{
				int nNum = (m_nMeshWidth * nCntVtxY) + nCntVtxX;
				pVtx[nNum].tex += m_AnimTexUV;

			}
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

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//拡大縮小の反映
	D3DXMatrixScaling(&mtxScale, m_Size.x, m_Size.y, m_Size.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

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

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0,
		m_nVtxNum, 0, m_nPolygonNum);

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

	for (int nCntVtxY = 0; nCntVtxY <= m_nMeshHeight; nCntVtxY++)
	{
		for (int nCntVtxX = 0; nCntVtxX < m_nMeshWidth; nCntVtxX++)
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

			pVtx[nNum].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[nNum].col = m_Color;

		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	//法線の更新
	UpdateNormal();
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
// 法線処理
//=============================================================================
void CMeshSphere::UpdateNormal(void)
{
	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	int nVecNum = 0;

	//ポリゴンの法線設定
	D3DXVECTOR3 VecA, VecB;

	for (int nCntHeight = 0; nCntHeight <= m_nMeshHeight; nCntHeight++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		for (int nCntWidth = 0; nCntWidth < m_nMeshWidth; nCntWidth++)
		{
			int nNum = (m_nMeshWidth * nCntHeight) + nCntWidth;

			VecA = pVtx[nNum + (m_nMeshWidth + 2)].pos - pVtx[nNum].pos;
			VecB = pVtx[nNum + (m_nMeshWidth + 1)].pos - pVtx[nNum].pos;
			D3DXVec3Cross(&m_VecNor[nVecNum], &VecA, &VecB);

			D3DXVec3Normalize(&m_VecNor[nVecNum], &m_VecNor[nVecNum]);
			nVecNum++;

			VecA = pVtx[nNum + 1].pos - pVtx[nNum].pos;
			VecB = pVtx[nNum + (m_nMeshWidth + 2)].pos - pVtx[nNum].pos;
			D3DXVec3Cross(&m_VecNor[nVecNum], &VecA, &VecB);

			D3DXVec3Normalize(&m_VecNor[nVecNum], &m_VecNor[nVecNum]);
			nVecNum++;
		}
	}
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


	//頂点ごとの法線設定
	D3DXVECTOR3 VecC;
	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntHeight = 0; nCntHeight <= m_nMeshHeight; nCntHeight++)
	{
		//頂点バッファをロックし、頂点データへのポインタを取得
		for (int nCntWidth = 0; nCntWidth < m_nMeshWidth; nCntWidth++)
		{
			if (nCntWidth == 0)
			{
				if (nCntHeight == 0)
				{
					VecC = (m_VecNor[0] + m_VecNor[1]) / 2;
					D3DXVec3Normalize(&pVtx[0].nor, &VecC);
				}
				else if (nCntHeight == m_nMeshHeight)
				{
					VecC = m_VecNor[((m_nMeshWidth) * 2) * (m_nMeshHeight - 1)];
					D3DXVec3Normalize(&pVtx[(m_nMeshWidth + 1) * m_nMeshHeight].nor, &VecC);
				}
				else
				{
					int nA = (m_nMeshWidth * 2) * (nCntHeight - 1);
					VecC = (m_VecNor[nA] + m_VecNor[nA + (m_nMeshWidth * 2)] + m_VecNor[nA + (m_nMeshWidth * 2) + 1]) / 3;
					D3DXVec3Normalize(&pVtx[(m_nMeshWidth + 1) * nCntHeight].nor, &VecC);
				}
			}
			else if (nCntWidth == m_nMeshWidth)
			{
				if (nCntHeight == 0)
				{
					VecC = m_VecNor[(m_nMeshWidth * 2) - 1];
					D3DXVec3Normalize(&pVtx[m_nMeshWidth].nor, &VecC);
				}
				else if (nCntHeight == m_nMeshHeight)
				{
					VecC = (m_VecNor[(m_nMeshWidth * m_nMeshHeight * 2) - 2] + m_VecNor[(m_nMeshWidth * m_nMeshHeight * 2) - 1]) / 2;
					D3DXVec3Normalize(&pVtx[((m_nMeshHeight + 1) * (m_nMeshWidth + 1)) - 1].nor, &VecC);

				}
				else
				{
					int nB = m_nMeshWidth * 2;
					VecC = (m_VecNor[(nB * nCntHeight) - 2] + m_VecNor[(nB * nCntHeight) - 1] + m_VecNor[(nB * (nCntHeight + 1)) - 1]) / 3;
					D3DXVec3Normalize(&pVtx[((m_nMeshWidth + 1) * (nCntHeight + 1)) - 1].nor, &VecC);
				}
			}
			else
			{
				if (nCntHeight == 0)
				{
					int nC = (nCntWidth * 2) - 1;
					VecC = (m_VecNor[nC] + m_VecNor[nC + 1] + m_VecNor[nC + 2]) / 3;
					D3DXVec3Normalize(&pVtx[nCntWidth].nor, &VecC);

				}
				else if (nCntHeight == m_nMeshHeight)
				{
					int nD = ((m_nMeshWidth * 2) * (m_nMeshHeight - 1)) + ((nCntWidth - 1) * 2);
					VecC = (m_VecNor[nD] + m_VecNor[nD + 1] + m_VecNor[nD + 2]) / 3;
					D3DXVec3Normalize(&pVtx[((m_nMeshWidth + 1) * m_nMeshHeight) + nCntWidth].nor, &VecC);
				}
				else
				{
					int nE = ((nCntWidth - 1) * 2) + ((m_nMeshWidth * 2) * (nCntHeight - 1));
					int nF = nE + ((m_nMeshWidth) * 2) + 1;
					VecC = (m_VecNor[nE] + m_VecNor[nE + 1] + m_VecNor[nE + 2] +
						m_VecNor[nF] + m_VecNor[nF + 1] + m_VecNor[nF + 2]) / 6;
					D3DXVec3Normalize(&pVtx[nCntWidth + ((m_nMeshWidth + 1) * nCntHeight)].nor, &VecC);

				}
			}
		}
	}


	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();


}