//=============================================================================
//
// シーン2D処理 [scene2D.h]
// Author : 目黒 未来也
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "input.h"

//=============================================================================
// シーンクラスのコンストラクタ
//=============================================================================
CScene2D::CScene2D(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpin = 0.0f;	//回転
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//色
	m_fScale = 0.0f;	//拡大
	m_fWidth = 0.0f;
	m_fHeight = 0.0f;
	m_fRight = 0.0f;
	m_fLeft = 0.0f;
	m_bDraw = true;
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CScene2D *CScene2D::Create(D3DXVECTOR3 pos, LPCSTR Tag,int nPriority)
{
	CScene2D *pScene2D = NULL;

	if (pScene2D == NULL)
	{
		// オブジェクトクラスの生成
		pScene2D = new CScene2D(nPriority, OBJTYPE_SCENE2D);

		if (pScene2D != NULL)
		{
			pScene2D->Init(pos);
			pScene2D->BindTexture(Tag);
		}
	}

	return pScene2D;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene2D::~CScene2D()
{
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CScene2D::Init(D3DXVECTOR3 pos)
{
	// ポリゴンの位置を設定
	m_Pos = pos;
	m_bDraw = true;

	// オブジェクトの種類の設定
	//SetObjType(CScene::OBJTYPE_SCENE2D);

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,									// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - 50.0f, m_Pos.y - 50.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + 50.0f, m_Pos.y - 50.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - 50.0f, m_Pos.y + 50.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + 50.0f, m_Pos.y + 50.0f, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CScene2D::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CScene2D::Update(void)
{
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CScene2D::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}
	//アルファテスト(透明色を描画しないように)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 90);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	if (m_bDraw == true)
	{	// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// オブジェクトの取得
//=============================================================================
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_Pos;
}

//=============================================================================
// オブジェクトの設定
//=============================================================================
void CScene2D::SetPosition(D3DXVECTOR3 pos)
{
	m_Pos = pos;

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報を設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y - m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x - m_fWidth, m_Pos.y + m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_Pos.x + m_fWidth, m_Pos.y + m_fHeight, 0.0f);

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//=============================================================================
// テクスチャの設定
//=============================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	//持ってきた情報を代入
	m_pTexture = pTexture;
}

void CScene2D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//=============================================================================
//シーン2D位置設定
//=============================================================================
void CScene2D::SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col)
{
	m_Pos = pos;		//位置
	m_fSpin = fSpin;	//回転
	m_Col = col;		//色
	m_fScale = fScale;	//拡大

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  (m_fHeight + m_fScale);

	//頂点カラー
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
//シーン2D回転設定
//=============================================================================
void CScene2D::SetRot(float fSpin)
{
	m_fSpin = fSpin;	//回転

	VERTEX_2D *pVtx;//頂点情報へのポインタ

					//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
#if 1
	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) * m_fWidth;
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  m_fHeight;
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  m_fWidth;
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  m_fHeight;
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  m_fWidth;
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  m_fHeight;
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  m_fWidth;
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  m_fHeight;
#endif
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//=============================================================================
//シーン2D大きさ設定
//=============================================================================
void CScene2D::SetWidthHeight(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f) * m_fWidth;
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f) * m_fWidth;
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f) * m_fWidth;
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f) * m_fWidth;
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//シーン2D左右の大きさ設定
//=============================================================================
void CScene2D::SetRIghtLeft(float fRight, float fLeft)
{
	m_fRight = fRight;
	m_fLeft = fLeft;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f) * (m_fWidth + m_fLeft);
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f) * m_fHeight;
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f) * (m_fWidth + m_fRight);
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f) * m_fHeight;
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f) * (m_fWidth + m_fLeft);
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f) * m_fHeight;
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f) * (m_fWidth + m_fRight);
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f) * m_fHeight;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//=============================================================================
//シーン2D色の変更
//=============================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	m_Col = col;		//色

	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラー
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}


//=============================================================================
// アニメーションの設定処理
//=============================================================================
void CScene2D::SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V)
{
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

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
// アニメーションの設定処理
//=============================================================================
void CScene2D::SetTex(D3DXVECTOR2 texmin, D3DXVECTOR2 texmax)
{
	VERTEX_2D*pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(texmin.x, texmin.y);
	pVtx[1].tex = D3DXVECTOR2(texmax.x, texmin.y);
	pVtx[2].tex = D3DXVECTOR2(texmin.x, texmax.y);
	pVtx[3].tex = D3DXVECTOR2(texmax.x, texmax.y);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}


//=============================================================================
//大きさ変更
//=============================================================================
void CScene2D::SetScale(float fScale)
{
	m_fScale = fScale;	//拡大

						//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点バッファをロックし頂点データのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos.x = m_Pos.x + sinf(D3DX_PI * -0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[0].pos.y = m_Pos.y + cosf(D3DX_PI * -0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[1].pos.x = m_Pos.x + sinf(D3DX_PI * 0.75f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[1].pos.y = m_Pos.y + cosf(D3DX_PI * 0.75f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[2].pos.x = m_Pos.x + sinf(D3DX_PI * -0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[2].pos.y = m_Pos.y + cosf(D3DX_PI * -0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	pVtx[3].pos.x = m_Pos.x + sinf(D3DX_PI * 0.25f + m_fSpin) *  (m_fWidth + m_fScale);
	pVtx[3].pos.y = m_Pos.y + cosf(D3DX_PI * 0.25f + m_fSpin) *  (m_fHeight + m_fScale);
	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
//=============================================================================
// 2Dポリゴンの設定（左を中心座標にする）
//=============================================================================
void CScene2D::SetScene2DLeftCenter(D3DXVECTOR3 pos, float sizeW, float sizeH)
{
	VERTEX_2D *pVtx;//頂点情報へのポインタ

	m_Pos = pos;
	m_fWidth = sizeW;
	m_fHeight = sizeH;

	// 頂点情報を設定
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//ポリゴンの大きさの座標設定
	pVtx[0].pos = D3DXVECTOR3(m_Pos.x, (m_Pos.y - m_fHeight), 0.0f);
	pVtx[1].pos = D3DXVECTOR3((m_Pos.x + m_fWidth), (m_Pos.y - m_fHeight), 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_Pos.x, (m_Pos.y + m_fHeight), 0.0f);
	pVtx[3].pos = D3DXVECTOR3((m_Pos.x + m_fWidth), (m_Pos.y + m_fHeight), 0.0f);

	//頂点バッファのアンロック
	m_pVtxBuff->Unlock();

}