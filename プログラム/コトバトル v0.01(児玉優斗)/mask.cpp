//=============================================================================
//
// マスク処理 [mask.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "mask.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_POS_X			(0)								// フェードの左上X座標
#define FADE_POS_Y			(0)								// フェードの左上Y座標
#define FADE_WIDTH			(SCREEN_WIDTH)					// フェードの幅
#define FADE_HEIGHT			(SCREEN_HEIGHT)					// フェードの高さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// コンストラクタ
//=============================================================================
CMask::CMask()
{
	// 値をクリア
	//m_pTexture = NULL;
	//m_modeNext = CManager::MODE_NONE;
	//m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// 黒い画面（透明）にしておく
}

//=============================================================================
// デストラクタ
//=============================================================================
CMask::~CMask()
{
}

//=============================================================================
// フェードの生成処理
//=============================================================================
CMask *CMask::Create(void)
{
	CMask *pFade = NULL;

	if (pFade == NULL)
	{
		// フェードクラスの生成
		pFade = new CMask;

		if (pFade != NULL)
		{
			pFade->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			//pFade->m_fade = FADE_OUT;	// フェードアウト状態に
			//pFade->m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 黒い画面（透明）にしておく
		}

	}
	return pFade;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CMask::Init(D3DXVECTOR3 pos)
{
	// 値の初期化

														// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// テクスチャの生成
	//D3DXCreateTextureFromFile(pDevice, PLAYER_NAME, &m_pTexture);

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// 確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// 頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

						// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, 0.0f);

	// rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);

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
// 終了処理
//=============================================================================
void CMask::Uninit(void)
{
	// 頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CMask::Update(void)
{

}

//=============================================================================
// タイトル画面
//=============================================================================
void CMask::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}