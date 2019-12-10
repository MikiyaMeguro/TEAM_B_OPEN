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
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_TexUV = D3DXVECTOR2(1.0f, 1.0f);
	m_scene3dType = SCENE3DTYPE_NORMAL;
	m_bAlphaTest = false;
	m_bLigntEffect = false;
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
			pScene3D->Init();
			pScene3D->SetPos(pos);
			pScene3D->BindTexture(Tag);
		}
	}
	return pScene3D;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CScene3D::Init(void)
{
	//	デバイスの取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9	pDevice = pRenderer->GetDevice();

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4
		, D3DUSAGE_WRITEONLY
		, FVF_VERTEX_3D
		, D3DPOOL_MANAGED
		, &m_pVtxBuff
		, NULL);

	// 頂点情報の設定
	VERTEX_3D *pVtx;	// 頂点情報へのポインタ
						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, m_size.z);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, -m_size.z);

	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//	テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(m_TexUV.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, m_TexUV.y);
	pVtx[3].tex = D3DXVECTOR2(m_TexUV.x, m_TexUV.y);

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();			// デバイス取得

	D3DXMATRIX mtxRot, mtxTrans, mtxView;		// 計算用マトリックス

	if (m_bLigntEffect == false)
	{
		// ライト影響
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	}
	if (m_bAlphaTest == true)
	{
		// アルファテストの設定
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 1);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	}

	if (m_scene3dType == SCENE3DTYPE_BILLBOARD || m_scene3dType == SCENE3DTYPE_BILLEFFECT || m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
	{//	ビルボード　			加算合成ありビルボードエフェクト

		if (m_scene3dType == SCENE3DTYPE_BILLEFFECT)
		{
			// αブレンディングを加算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		else if (m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
		{
			//// αブレンディングを減算合成に設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
		// Zバッファへの書き込み
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	if (m_scene3dType == SCENE3DTYPE_NORMAL)
	{
		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);
	}
	else if (m_scene3dType == SCENE3DTYPE_BILLBOARD || m_scene3dType == SCENE3DTYPE_BILLEFFECT)
	{//	ビルボード　			加算合成ありビルボードエフェクト
	 // 逆行列
		m_mtxWorld._11 = mtxView._11;
		m_mtxWorld._12 = mtxView._21;
		m_mtxWorld._13 = mtxView._31;
		m_mtxWorld._21 = mtxView._12;
		m_mtxWorld._22 = mtxView._22;
		m_mtxWorld._23 = mtxView._32;
		m_mtxWorld._31 = mtxView._13;
		m_mtxWorld._32 = mtxView._23;
		m_mtxWorld._33 = mtxView._33;
	}

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットd
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	if (m_scene3dType == SCENE3DTYPE_BILLEFFECT || m_scene3dType == SCENE3DTYPE_BILLBOARD || m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
	{//	ビルボード　			加算合成ありビルボードエフェクト
	 // Zバッファへの書き込み
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		if (m_scene3dType == SCENE3DTYPE_BILLEFFECT || m_scene3dType == SCENE3DTYPE_SUBSYNTHESIS)
		{//	ビルボード
		 // αブレンディングを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		}
	}
	if (m_bLigntEffect == false)
	{
		// ライト影響
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	}
	if (m_bAlphaTest == true)
	{
		// アルファテストを無効
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
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
	m_size.y = fHeight;
	m_size.x = fWidth;

	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, 0.0f, m_size.y);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, 0.0f, m_size.y);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, 0.0f, -m_size.y);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, 0.0f, -m_size.y);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
// サイズの設定
//=============================================================================
void CScene3D::SetSizeY(float fHeight, float fWidth)
{
	//取得したサイズを代入
	m_size.y = fHeight;
	m_size.x = fWidth;

	if (m_pVtxBuff == NULL) { return; }
	// 頂点情報の設定
	VERTEX_3D *pVtx;
	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x, m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x, -m_size.y, 0.0f);

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