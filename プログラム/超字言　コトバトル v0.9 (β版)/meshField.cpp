//=============================================================================
//
// メッシュフィールドの処理 [meshField.cpp]
// Author :
//
//=============================================================================
#include "meshField.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"

//=============================================================================
// グローバル変数宣言
//=============================================================================

//=============================================================================
// メッシュフィールドのコンストラクタ
//=============================================================================
CMeshField::CMeshField(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;	// テクスチャへのポインタ
	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bRand = false;
	m_nSplitX = 0;
	m_nSplitZ = 0;
	m_fDepth = 0;
	m_fWidth = 0;

	for (int nCntNor = 0; nCntNor < NUM_POLYGON; nCntNor++)
	{
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos, int nSplitX, int nSplitZ, float fWidth)
{
	CMeshField *pMeshField = NULL;

	if (pMeshField == NULL)
	{
		// オブジェクトクラスの生成
		pMeshField = new CMeshField;

		if (pMeshField != NULL)
		{
			pMeshField->m_pos = pos;
			pMeshField->m_nSplitX = nSplitX;
			pMeshField->m_nSplitZ = nSplitZ;
			pMeshField->m_fWidth = fWidth;
			pMeshField->Init();
		}
	}

	return pMeshField;
}
//=============================================================================
// テクスチャの設定
//=============================================================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//持ってきた情報を代入
	m_pTexture = pTexture;
}

void CMeshField::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMeshField::Init(void)
{
	// 値の初期化
	m_pTexture = NULL;	// テクスチャへのポインタ
	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bRand = false;

	//中央に配置
	float TestX = MESH_CENTER;
	float TestZ = -MESH_CENTER;
	//TestX = MESH_CENTER;

	//MESH_CENTER
	//m_pos.x = (m_nSplitX / 2) * -MESHFIELD_SIZE + (MESHFIELD_SIZE / 2);
	//m_pos.z = (m_nSplitZ / 2) * MESHFIELD_SIZE - (MESHFIELD_SIZE / 2);

	//for (int nCntZ = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	//{
	//	for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
	//	{
			//g_aHeight[nCntZ][nCntX] = 0.0f;
	//	}
	//}

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// 頂点情報の作成
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// 頂点数
	m_nNumVerTex = (m_nSplitX + 1) * (m_nSplitZ + 1);

	// インデックス数
	m_nNumIndex = (m_nSplitX + 1) * (m_nSplitZ + 1)
		+ (2 * (m_nSplitZ - 1))
		+ (m_nSplitX + 1) * (m_nSplitZ - 1);

	// ポリゴン数
	m_nNumPolygon = m_nNumIndex - 2;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16ビットのデータを確保
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < m_nSplitZ + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < m_nSplitX + 1; nCntVtxX++)
		{
			// 頂点座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3(TestX + (-m_fWidth + (nCntVtxX * m_fWidth)), 0.0f, TestZ + (m_fWidth - (nCntVtxZ * m_fWidth)));
			// 法線の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// 頂点カラーの設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// テクスチャ座標の設定
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex =
				D3DXVECTOR2(0.0f + (nCntVtxX /** (10.0f / m_nSplitX)*/), 0.0f + (nCntVtxZ /** (10.0f / m_nSplitZ)*/));
		}
		nVtxCounter += m_nSplitX;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

#if(1)
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;

	int nData = 0;
	int nData2 = 0;
	int nData3 = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// 一方のポリゴンの２つのベクトルから法線を算出
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1) + 1].pos;
			pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;

			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			// 外積を使って各ポリゴンの法線を求める
			D3DXVec3Cross(&nor, &vec1, &vec0);
			// 正規化する
			D3DXVec3Normalize(&nor, &nor);
			// 法線を保存
			m_aNor[(nCntZ * m_nSplitZ) + (nCntX * m_nSplitX) + nCntPolygon] = nor;

			// 外積を使って各ポリゴンの法線を求める
			D3DXVec3Cross(&nor, &vec2, &vec1);
			// 正規化する
			D3DXVec3Normalize(&nor, &nor);
			// 法線を保存
			m_aNor[(nCntZ * m_nSplitZ) + (nCntX * m_nSplitX) + nCntPolygon + 1] = nor;
		}

		nCntPolygon += m_nSplitX;
	}

	for (int nCntPolygonZ = 0; nCntPolygonZ < m_nSplitZ + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < m_nSplitX + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// 上端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// 右端
					pVtx[m_nSplitX].nor = m_aNor[m_nSplitX + (m_nSplitX - 1)];
				}
				else
				{// 上端の真ん中
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == m_nSplitZ)
			{// 下端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[m_nSplitZ * (m_nSplitX + 1)].nor = m_aNor[2 * (m_nSplitX * (m_nSplitZ - 1))];
				}
				else if (nCntPolygonX == m_nSplitX)
				{// 右端
					pVtx[(m_nSplitX * m_nSplitZ) + (m_nSplitX + m_nSplitZ)].nor =
						(m_aNor[(m_nSplitX * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))] +
							m_aNor[((2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))) + 1]) / 2;
				}
				else
				{// 下端の真ん中
					pVtx[(m_nSplitZ * (m_nSplitX + 1)) + nCntPolygonX].nor =
						(m_aNor[(m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// 真ん中
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[(m_nSplitX + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)] +
							m_aNor[(nCntPolygonZ * (2 * m_nSplitX))] +
							m_aNor[(nCntPolygonZ * (2 * m_nSplitX) + 1)]) / 3;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// 右端
					pVtx[((nCntPolygonZ + 1) * m_nSplitX) + nCntPolygonZ].nor =
						(m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + ((m_nSplitX * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(m_nSplitX + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (m_nSplitX + 1)) - (m_nSplitX + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
							m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))) + ((nCntPolygonX * 2) - 2)] +
							m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 1) + ((nCntPolygonX * 2) - 2)] +
							m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 2) + ((nCntPolygonX * 2) - 2)]) / 6;
				}
			}
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

#endif

	WORD *pIdx;	// インデックスデータへのポインタ

	// インデックスバッファをロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < m_nSplitZ; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < m_nSplitX + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + m_nSplitX + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < m_nSplitZ - 1 && nCntIdxX == m_nSplitX)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (m_nSplitX + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// インデックスバッファをアンロック
	m_pIdxBuff->Unlock();

	//LoadHeight();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CMeshField::Uninit(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの開放
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
void CMeshField::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

#if(1)

	if (m_pVtxBuff == NULL) { return; }
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// 一方のポリゴンの２つのベクトルから法線を算出
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1) + 1].pos;
			pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;

			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			// 外積を使って各ポリゴンの法線を求める
			D3DXVec3Cross(&nor, &vec1, &vec0);
			// 正規化する
			D3DXVec3Normalize(&nor, &nor);
			// 法線を保存
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon] = nor;

			// 外積を使って各ポリゴンの法線を求める
			D3DXVec3Cross(&nor, &vec2, &vec1);
			// 正規化する
			D3DXVec3Normalize(&nor, &nor);
			// 法線を保存
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon + 1] = nor;
		}

		nCntPolygon += m_nSplitX;
		nCntNorPolygon += (m_nSplitX * 2) - 2;
	}

	int nData0 = 0;
	int nData1 = 0;

	for (int nCntPolygonZ = 0; nCntPolygonZ < m_nSplitZ + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < m_nSplitX + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// 上端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// 右端
					pVtx[m_nSplitX].nor = m_aNor[m_nSplitX + (m_nSplitX - 1)];
				}
				else
				{// 上端の真ん中
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == m_nSplitZ)
			{// 下端
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[m_nSplitZ * (m_nSplitX + 1)].nor = m_aNor[2 * (m_nSplitX * (m_nSplitZ - 1))];
				}
				else if (nCntPolygonX == m_nSplitX)
				{// 右端
					pVtx[(m_nSplitX * m_nSplitZ) + (m_nSplitX + m_nSplitZ)].nor =
						(m_aNor[(2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))] +
							m_aNor[((2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))) + 1]) / 2;
				}
				else
				{// 下端の真ん中
					pVtx[(m_nSplitZ * (m_nSplitX + 1)) + nCntPolygonX].nor =
						(m_aNor[(m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((m_nSplitZ - 1) * (m_nSplitX * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// 真ん中
				if (nCntPolygonX == 0)
				{// 左端
					pVtx[(m_nSplitX + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)] +
						m_aNor[(nCntPolygonZ * (2 * m_nSplitX))] +
						m_aNor[(nCntPolygonZ * (2 * m_nSplitX) + 1)]) / 3;
				}
				else if (nCntPolygonX == m_nSplitX)
				{// 右端
					pVtx[((nCntPolygonZ + 1) * m_nSplitX) + nCntPolygonZ].nor =
						(m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((m_nSplitX - 1) * 2 + ((m_nSplitX * 2)* (nCntPolygonZ - 1))) + ((m_nSplitX * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(m_nSplitX + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (m_nSplitX + 1)) - (m_nSplitX + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))] +
						 m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
						 m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)))] +
						 m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX))) + ((nCntPolygonX * 2) - 1)] +
						 m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 1) + ((nCntPolygonX * 2) - 1)] +
						 m_aNor[((2 * m_nSplitX) + ((nCntPolygonZ * (2 * m_nSplitX)) - (2 * m_nSplitX)) + 2) + ((nCntPolygonX * 2) - 1)]) / 6;

					nData0 = (m_nSplitX + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (m_nSplitX + 1)) - (m_nSplitX + 1));
					/*nData1 = ((2 * (m_nSplitX * (m_nSplitZ - 1))) + (2 * (m_nSplitX - 1))) + 1;*/
				}
			}
		}
	}

	int nVtxCounter = 0;

	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{// 0キーが押されたら
		SaveHeight();
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

#endif

#ifdef _DEBUG
	CDebugProc::Print("c", "フィールド");

#endif


}

//=============================================================================
// 描画処理
//=============================================================================
void CMeshField::Draw(void)
{

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// デバイスの取得
		pDevice = pRenderer->GetDevice();
	}

	//マトリックスの計算
	CUtilityMath::CalWorldMatrix(&m_mtxWorld,m_pos,m_rot);

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
	if (CManager::GetMode() != CManager::MODE_TUTORIAL)
	{// ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTex, 0, m_nNumPolygon);
	}
}

//=============================================================================
// 高さを取得
//============================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	bool bX = false;
	bool bZ = false;
	bool *abX = new bool[m_nSplitX];
	bool *abZ = new bool[m_nSplitZ];
	bool bRand = false;

	for (int nCount = 0; nCount < m_nSplitX; nCount++)
	{
		abX[nCount] = false;
	}

	for (int nCount = 0; nCount < m_nSplitZ; nCount++)
	{
		abZ[nCount] = false;
	}

	// 自分が今どのポリゴンに乗っているか
	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX -1; nCntX++)
		{
			float  test = MESH_CENTER - m_fWidth + (nCntX * m_fWidth);
			float  test1 = MESH_CENTER + m_fWidth + (nCntX * m_fWidth);
			float  test2 = MESH_CENTER - m_fWidth + (nCntZ * m_fWidth);
			float  test3 = MESH_CENTER  + (nCntZ * m_fWidth);

			if (pos.x >= test && pos.x < test1)
			{
				bX = true;
				abX[nCntX] = true;
			}

			if (pos.z >= test2 && pos.z < test3)
			{
				bZ = true;
				abZ[nCntZ] = true;
			}
		}
	}

	int nCount = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			if (abX[nCntX] == true && abZ[nCntZ] == true)
			{
				//CDebugProc::Print("nc", nCntX + nCntZ + nCount, ": 中");
				bRand = true;
			}
			else
			{
				//CDebugProc::Print("nc", nCntX + nCntZ + nCount, ": 外");

				bRand = false;
			}
		}
		nCount+= 2;
	}


	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < m_nSplitZ; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX; nCntX++)
		{
			if (abX[nCntX] == true && abZ[nCntZ] == true)
			{
				D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
				D3DXVECTOR3 vec0, vec1, vec2, vec3;
				D3DXVECTOR3 nor0, nor1;
				float fData = 0.0f;

				// 一方のポリゴンの２つのベクトルから法線を算出
				pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;							// 左上
				pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1)].pos;		// 左下
				pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (m_nSplitX + 1) + 1].pos;	// 右下
				pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;					// 右上

				vec0 = *pPos1 - *pPos0;	// 左の辺のベクトル
				vec1 = *pPos2 - *pPos0;	// 左上から右下のベクトル
				vec2 = *pPos3 - *pPos0;	// 上の辺のベクトル
				vec3 = pos - *pPos0;

				// 外積を使って各ポリゴンの法線を求める
				D3DXVec3Cross(&nor0, &vec1, &vec0);
				// 正規化する
				D3DXVec3Normalize(&nor0, &nor0);

				// 外積を使って各ポリゴンの法線を求める
				D3DXVec3Cross(&nor1, &vec2, &vec1);
				// 正規化する
				D3DXVec3Normalize(&nor1, &nor1);

				fData = ((vec1.z * vec3.x) - (vec1.x * vec3.z));

				if (fData > 0)
				{
					pos.y = (((nor0.x * (pos.x - pPos0->x) + nor0.z * (pos.z - pPos0->z)) / -nor0.y) + pPos0->y);
				}
				else
				{
					pos.y = (((nor1.x * (pos.x - pPos2->x) + nor1.z * (pos.z - pPos2->z)) / -nor1.y) + pPos2->y);
				}

				break;
			}
		}

		nCntPolygon += m_nSplitX;
		nCntNorPolygon += (m_nSplitX * 2) - 2;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	delete[] abX;
	delete[] abZ;

	return pos.y;
}

//=============================================================================
// 高さを設定
//============================================================================
void CMeshField::SetHeight(D3DXVECTOR3 pos, float fValue, float fRange)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntZ = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{
			// posから対象の頂点までの距離
			float fLength = sqrtf
				// xの距離
				((pos.x - pVtx->pos.x) * (pos.x - pVtx->pos.x) +
				// zの距離
				(pos.z - pVtx->pos.z) * (pos.z - pVtx->pos.z));

			if (fLength < fRange)
			{// 対象の頂点が範囲内
				// 範囲内での距離の比率に応じた高さ
				float fHeight = cosf((fLength / fRange) * (D3DX_PI * 0.5f)) * fValue;

				pVtx->pos.y += fHeight;
			}

			// 高さを代入
			//g_aHeight[nCntZ][nCntX] = pVtx->pos.y;

			pVtx++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 地面の高さを返す(ブールを返す)
//=============================================================================
bool CMeshField::GetHeightbool(D3DXVECTOR3 &pos)
{
#if 0
	//変数宣言
	D3DXVECTOR3 vec0;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 nor;
	D3DXVECTOR3 VtxPos[3];
	D3DXVECTOR3 VtxNor[6];
	int			nNumber;
	float		fHeight;

	//プレイヤーとメッシュフィールドの位置の差分を出す
	D3DXVECTOR3 posMtx = pos - m_pos;

	int test1, test2;
	test1 = m_nSplitX;
	test2 = m_nSplitZ;
	//現在プレイヤーが何ブロック目にいるかを確認する式
	int			nMeshX = (int)((posMtx.x) / (MESHFIELD_SIZE / m_nSplitX));
	int			nMeshZ = (int)((posMtx.z) / (MESHFIELD_SIZE / m_nSplitZ) * -1);

	if (nMeshX >= m_nSplitX || nMeshX < 0)
	{
		return false;
	}
	if (nMeshZ >= m_nSplitZ || nMeshZ < 0)
	{
		return false;
	}

	//現在の乗っかっているブロックの頂点の出し方
	int			nMeshLU = nMeshX + nMeshZ * (m_nSplitX + 1);					//例　0番目の頂点
	int			nMeshRU = (nMeshX + 1) + nMeshZ * (m_nSplitX + 1);			//例　1番目の頂点
	int			nMeshLD = nMeshX + (nMeshZ + 1) * (m_nSplitX + 1);			//例　3番目の頂点
	int			nMeshRD = (nMeshX + 1) + (nMeshZ + 1) * (m_nSplitX + 1);		//例　4番目の頂点

																				//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (posMtx.x < 0 || posMtx.x > pVtx[m_nSplitX].pos.x)
	{
		return false;
	}
	if (posMtx.z > 0 || posMtx.z > pVtx[m_nSplitX].pos.z)
	{
		return false;
	}

	CDebugProc::Print("cn", "現在のブロック　横に %d　ブロック目\n", nMeshX);
	//	CDebugProc::Print("cncfcfcfc", "pos[", nCntNor, "] : (", pVtx[nCntNor].pos.x, ", ", pVtx[nCntNor].pos.y, ", ", pVtx[nCntNor].pos.z, ")");
	CDebugProc::Print("cn", "現在のブロック　縦に %d　ブロック目\n", nMeshZ);

	//ベクトル計算式 目的 - 現在
	vec0 = pVtx[nMeshLU].pos - pVtx[nMeshRD].pos;
	//ベクトル計算式 自分の位置　- 現在
	vec1 = posMtx - pVtx[nMeshRD].pos;

	if ((vec0.x * vec1.z) - (vec0.z * vec1.x) <= 0)
	{//三角形より右にいる場合
		CDebugProc::Print("c", "MeshField△右範囲 : TURE\n");
		vec0 = (posMtx - pVtx[nMeshLU].pos);

		//各頂点の保管
		VtxPos[0] = pVtx[nMeshRU].pos;
		VtxPos[1] = pVtx[nMeshRD].pos;
		VtxPos[2] = pVtx[nMeshLU].pos;

		nNumber = 3;
	}
	else if ((vec0.x * vec1.z) - (vec0.z * vec1.x) >= 0)
	{//三角形より左にいる場合
		CDebugProc::Print("c", "MeshField△左範囲 : TURE\n");
		vec0 = (posMtx - pVtx[nMeshRD].pos);

		//各頂点の保管
		VtxPos[0] = pVtx[nMeshLD].pos;
		VtxPos[1] = pVtx[nMeshLU].pos;
		VtxPos[2] = pVtx[nMeshRD].pos;

		nNumber = 0;
	}

	//引く法線を引く前に保存する
	fHeight = VtxPos[0].y;

	//3頂点に0の値をひいてあげて法線とプレイヤーのベクトルを直交させるため
	VtxPos[2].y -= VtxPos[0].y;
	VtxPos[1].y -= VtxPos[0].y;
	VtxPos[0].y -= VtxPos[0].y;

	//法線の計算
	vec0 = VtxPos[1] - VtxPos[0];
	vec1 = VtxPos[2] - VtxPos[0];

	//外積の計算
	D3DXVec3Cross(&nor, &vec0, &vec1);
	//正規化
	D3DXVec3Normalize(&nor, &nor);
	//プレイヤーへのベクトル
	vec0 = posMtx - VtxPos[0];
	//内積公式
	((vec0.x * pVtx[nNumber].nor.x) + (vec0.y * pVtx[nNumber].nor.y) + (vec0.z * pVtx[nNumber].nor.z));
	//内積計算式
	vec0.y = (-(vec0.x * nor.x) - (vec0.z * nor.z)) / nor.y;
	//プレイヤーのyに入れる
	posMtx.y = vec0.y + fHeight + m_pos.y;
	//頂点バッファのアンロックする
	m_pVtxBuff->Unlock();

	if (pos.y < posMtx.y)
	{// プレイヤーを地面に乗せる
		pos.y = posMtx.y;
		return true;
	}
#endif
	return false;

}


//=============================================================================
// 高さをセーブ
//=============================================================================
void CMeshField::SaveHeight(void)
{
	FILE *pFile = NULL;

	// ファイルに書き込む
	pFile = fopen(TOUL_FILENAME, "wb");

	if (pFile != NULL)
	{
		//fwrite(&g_aHeight[0][0], sizeof(float), m_nSplitZ * m_nSplitX, pFile);	// データのアドレス,データのサイズ,データの個数,ファイルポインタ

		fclose(pFile);
	}
	else
	{
		MessageBox(0, "NULLでした", "警告", MB_OK);
	}

}

//=============================================================================
// 高さをロード
//=============================================================================
void CMeshField::LoadHeight(void)
{
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	FILE *pFile = NULL;

	pFile = fopen(TOUL_FILENAME, "rb");

	if (pFile != NULL)
	{
		//fread(&g_aHeight[0][0], sizeof(float), m_nSplitZ * m_nSplitX, pFile);	// データのアドレス,データのサイズ,データの個数,ファイルポインタ

		fclose(pFile);
	}
	else
	{
		MessageBox(0, "NULLでした", "警告", MB_OK);
	}

	for (int nCntZ = 0; nCntZ < m_nSplitZ + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < m_nSplitX + 1; nCntX++)
		{// posを代入
			//pVtx->pos.y = g_aHeight[nCntZ][nCntX];

			pVtx++;
		}
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}