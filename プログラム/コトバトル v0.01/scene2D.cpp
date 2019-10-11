//=============================================================================
//
// シーン2D処理 [scene2D.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene2D.h"
#include "renderer.h"
#include "Manager.h"

//==================================================================
// 静的メンバ変数
//==================================================================
static bool g_DeleteFlag = true;		//ブロック消すフラグ(テスト)

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CScene2D::CScene2D(CScene::PRIORITY pri = PRIORITY_3) : CScene(pri,OBJTYPE_2D)
{
}
CScene2D::~CScene2D()
{

}

//==================================================================
// テクスチャの適用
//==================================================================
void CScene2D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//==================================================================
// ポリゴンの設定処理
//==================================================================
void CScene2D::Set(D3DXVECTOR3 pos, LPCSTR TexTag,bool bRoll,float fRot,
	D3DXCOLOR col, D3DXVECTOR2 Size, D3DXVECTOR2 UVrectMin, D3DXVECTOR2 UVrectMax)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	BindTexture(TexTag);		//テクスチャの適用

	m_pos = pos;
	m_Col = col;
	m_Size = Size;
	m_bFreezeRotate = bRoll;
	m_fRot = fRot;

	m_UVRectMin = UVrectMin;
	m_UVRectMax = UVrectMax;


	// 頂点情報を設定
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	if (m_bFreezeRotate == true)
	{
		pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI * 0.75f - m_fRot) * m_Size.x, cosf(-D3DX_PI * 0.75f - m_fRot) * m_Size.y, 0.0f);
		pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI * 0.75f - m_fRot) * m_Size.x, cosf(D3DX_PI * 0.75f - m_fRot) * m_Size.y, 0.0f);
		pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI * 0.25f - m_fRot) * m_Size.x, cosf(-D3DX_PI * 0.25f - m_fRot) * m_Size.y, 0.0f);
		pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI * 0.25f - m_fRot) * m_Size.x, cosf(D3DX_PI * 0.25f - m_fRot) * m_Size.y, 0.0f);
	}
	else
	{
		pVtx[0].pos = m_pos + D3DXVECTOR3(-m_Size.x, -m_Size.y, 0.0f);
		pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size.x, -m_Size.y, 0.0f);
		pVtx[2].pos = m_pos + D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
		pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	}

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2(UVrectMin.x, UVrectMin.y);
	pVtx[1].tex = D3DXVECTOR2(UVrectMax.x, UVrectMin.y);
	pVtx[2].tex = D3DXVECTOR2(UVrectMin.x, UVrectMax.y);
	pVtx[3].tex = D3DXVECTOR2(UVrectMax.x, UVrectMax.y);

	m_pVtxBuff->Unlock();
}

//==================================================================
// ポリゴンの初期化処理
//==================================================================
HRESULT CScene2D::Init()
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);
	m_Size = D3DXVECTOR2(100.0f,100.0f);
	m_bFreezeRotate = false;
	m_fRot = 0.0f;

	m_UVRectMin = D3DXVECTOR2(0.0f, 0.0f);
	m_UVRectMax = D3DXVECTOR2(1.0f, 1.0f);

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
// ポリゴンの終了処理
//==================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}

	Release();
}

//==================================================================
// ポリゴンの更新処理
//==================================================================
void CScene2D::Update(void)
{

}

//==================================================================
// ポリゴンの描画処理
//==================================================================
void CScene2D::Draw(void)
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
// 各種設定処理
//==================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{//座標のみ設定
	m_pos = pos;

	// 変数宣言
	VERTEX_2D* pVtx;


	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bFreezeRotate == true)
	{
		pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI * 0.75f - m_fRot) * m_Size.x, cosf(-D3DX_PI * 0.75f - m_fRot) * m_Size.y, 0.0f);
		pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI * 0.75f - m_fRot) * m_Size.x, cosf(D3DX_PI * 0.75f - m_fRot) * m_Size.y, 0.0f);
		pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI * 0.25f - m_fRot) * m_Size.x, cosf(-D3DX_PI * 0.25f - m_fRot) * m_Size.y, 0.0f);
		pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI * 0.25f - m_fRot) * m_Size.x, cosf(D3DX_PI * 0.25f - m_fRot) * m_Size.y, 0.0f);
	}
	else
	{
		pVtx[0].pos = m_pos + D3DXVECTOR3(-m_Size.x, -m_Size.y, 0.0f);
		pVtx[1].pos = m_pos + D3DXVECTOR3(m_Size.x, -m_Size.y, 0.0f);
		pVtx[2].pos = m_pos + D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
		pVtx[3].pos = m_pos + D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	}


	m_pVtxBuff->Unlock();

}
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR2 Size)
{
	m_Size = Size;
	SetPosition(pos);
}
void CScene2D::SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 MinOffset, D3DXVECTOR3 MaxOffset)
{
	//ここに入った時点で回転は無効化される
	m_bFreezeRotate = false;
	m_pos = pos;

	// 変数宣言
	VERTEX_2D* pVtx;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(MinOffset.x, MinOffset.y, 0.0f) + pos;
	pVtx[1].pos = D3DXVECTOR3(MaxOffset.x, MinOffset.y, 0.0f) + pos;
	pVtx[2].pos = D3DXVECTOR3(MinOffset.x, MaxOffset.y, 0.0f) + pos;
	pVtx[3].pos = D3DXVECTOR3(MaxOffset.x, MaxOffset.y, 0.0f) + pos;

	m_pVtxBuff->Unlock();

}
void CScene2D::SetRotation(float fRot)
{
	if (m_bFreezeRotate == true)
	{//回転が有効なら
		m_fRot = fRot;

		// 変数宣言
		VERTEX_2D* pVtx;

		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI * 0.75f - m_fRot) * m_Size.x, cosf(-D3DX_PI * 0.75f - m_fRot) * m_Size.y, 0.0f);
		pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI * 0.75f - m_fRot) * m_Size.x, cosf(D3DX_PI * 0.75f - m_fRot) * m_Size.y, 0.0f);
		pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI * 0.25f - m_fRot) * m_Size.x, cosf(-D3DX_PI * 0.25f - m_fRot) * m_Size.y, 0.0f);
		pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI * 0.25f - m_fRot) * m_Size.x, cosf(D3DX_PI * 0.25f - m_fRot) * m_Size.y, 0.0f);
		m_pVtxBuff->Unlock();

	}
}

void CScene2D::SetColor(D3DXCOLOR col)
{
	// 変数宣言
	VERTEX_2D* pVtx;

	m_Col = col;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();

}

void CScene2D::SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect)
{
	// 変数宣言
	VERTEX_2D* pVtx;

	m_UVRectMin = MinRect;
	m_UVRectMax = MaxRect;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = MinRect;
	pVtx[1].tex = D3DXVECTOR2(MaxRect.x, MinRect.y);
	pVtx[2].tex = D3DXVECTOR2(MinRect.x, MaxRect.y);
	pVtx[3].tex = MaxRect;

	m_pVtxBuff->Unlock();

}


void CScene2D::SetScroll(float fSpeed, int nScrollType)
{
	m_fScrollCnt += 0.01f;	//	スクロール加算

							//	頂点情報へのポインタ
	VERTEX_2D*pVtx;

	//	頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (nScrollType == 0)//横スクロール
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + (fSpeed * m_fScrollCnt), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f + (fSpeed * m_fScrollCnt), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (fSpeed * m_fScrollCnt), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f + (fSpeed * m_fScrollCnt), 1.0f);
	}

	if (nScrollType == 1)//縦スクロール
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f + (fSpeed * m_fScrollCnt));
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f + (fSpeed * m_fScrollCnt));
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f + (fSpeed * m_fScrollCnt));
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f + (fSpeed * m_fScrollCnt));
	}

	// 頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}
