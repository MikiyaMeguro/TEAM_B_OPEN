//=============================================================================
//
// 3Dポリゴン処理 [scene3D.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "scene3D.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "game.h"

//=============================================================================
// 3Dポリゴンクラスのコンストラクタ
//=============================================================================
CScene3D::CScene3D(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCntNor = 0; nCntNor < NUM_VTX; nCntNor++)
	{
		m_aVec[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
		m_aPos[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
	}
	m_Nor = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線

	m_fSize = 0.0f;							// 大きさ
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene3D::~CScene3D()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CScene3D *CScene3D::Create(D3DXVECTOR3 pos, LPCSTR Tag)
{
	CScene3D *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		// オブジェクトクラスの生成
		pScene3D = new CScene3D;

		if (pScene3D != NULL)
		{
			pScene3D->Init(pos);
			pScene3D->BindTexture(Tag);
		}
	}

	return pScene3D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(D3DXVECTOR3 pos)
{
	// ポリゴンの情報を設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntNor = 0; nCntNor < NUM_VTX; nCntNor++)
	{
		m_aVec[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
		m_aPos[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 法線
	}

	m_Nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ポリゴンの位置を設定
	m_pos = pos;

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-50, 0.0f, 50);
	pVtx[1].pos = D3DXVECTOR3(50, 0.0f, 50);
	pVtx[2].pos = D3DXVECTOR3(-50, 0.0f, -50);
	pVtx[3].pos = D3DXVECTOR3(50, 0.0f, -50);

	pVtx[0].nor = m_Nor;
	pVtx[1].nor = m_Nor;
	pVtx[2].nor = m_Nor;
	pVtx[3].nor = m_Nor;

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CScene3D::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CScene3D::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene3D::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// デバイスを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// 法線を取得
//=============================================================================
D3DXVECTOR3 CScene3D::GetNor(int nIdx)
{
	D3DXVECTOR3 vecA[2];
	return m_Nor;
}

//=============================================================================
// 法線を設定
//=============================================================================
void CScene3D::SetNor(D3DXVECTOR3 nor)
{
	m_Nor = nor;
	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].nor = m_Nor;
	pVtx[1].nor = m_Nor;
	pVtx[2].nor = m_Nor;
	pVtx[3].nor = m_Nor;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 高さを取得
//============================================================================
float CScene3D::GetHeight(D3DXVECTOR3 pos)
{
	return pos.y;
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//持ってきた情報を代入
	m_pTexture = pTexture;
}
void CScene3D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}
//=============================================================================
// サイズの設定
//=============================================================================
void CScene3D::SetSize(float fHeight,float fWidth)
{
	//取得したサイズを代入
	m_fHeight = fHeight;
	m_fWidth = fWidth;

	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, m_fHeight);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, 0.0f, m_fHeight);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, -m_fHeight);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, -m_fHeight);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
// 位置の設定
//=============================================================================
void CScene3D::SetRot(D3DXVECTOR3 rot)
{
	//取得したサイズを代入
	m_rot = rot;
}

//=============================================================================
// アニメーションの設定処理
//=============================================================================
void CScene3D::SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V)
{
	VERTEX_3D*pVtx;	//頂点情報へのポインタ

					//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標
	pVtx[0].tex = D3DXVECTOR2(fUV_U * m_PatternAnim, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fUV_U * m_PatternAnim + fUV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fUV_U * m_PatternAnim, fUV_V);
	pVtx[3].tex = D3DXVECTOR2(fUV_U * m_PatternAnim + fUV_U, fUV_V);

	////テクスチャの座標
	//pVtx[0].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V * m_PatternAnim);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, EXPLOSION_UV_V * m_PatternAnim);
	//pVtx[2].tex = D3DXVECTOR2(EXPLOSION_UV_U, EXPLOSION_UV_V * m_PatternAnim + EXPLOSION_UV_V);
	//pVtx[3].tex = D3DXVECTOR2(0.0f, EXPLOSION_UV_V * m_PatternAnim + EXPLOSION_UV_V);

	m_PatternAnim = 0;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// 色の設定
//=============================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	m_col = col;

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}