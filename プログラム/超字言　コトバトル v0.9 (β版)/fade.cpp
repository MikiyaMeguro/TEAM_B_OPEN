//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "fade.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FADE_POS_X			(0)				// フェードの左上X座標
#define FADE_POS_Y			(0)				// フェードの左上Y座標
#define FADE_WIDTH			(SCREEN_WIDTH)	// フェードの幅
#define FADE_HEIGHT			(SCREEN_HEIGHT)	// フェードの高さ
#define FADE_SPEED			(0.02f)			// フェードの速さ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CFade::FADE CFade::m_fade = CFade::FADE_NONE;
CManager::MODE CFade::m_modeNext = CManager::MODE_NONE;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// 黒い画面（透明）にしておく

//=============================================================================
// コンストラクタ
//=============================================================================
CFade::CFade()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// フェードの生成処理
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		// フェードクラスの生成
		pFade = new CFade;

		if (pFade != NULL)
		{
			pFade->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}

	}
	return pFade;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos)
{
	// 値の初期化
	m_fade = FADE_NONE;	// フェードアウト状態に
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// 黒い画面（不透明）にしておく

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
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

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
void CFade::Uninit(void)
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
void CFade::Update(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// 頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)	// フェードイン状態
		{
			m_colorFade.a -= FADE_SPEED;	// 画面を透明にしていく
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;	// 何もしていない状態に
			}
		}
		else if (m_fade == FADE_OUT)	// フェードアウト状態
		{
			m_colorFade.a += FADE_SPEED;	// 画面を不透明にしていく
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;	// フェードイン状態に

				// モードの設定
				CManager::SetMode(m_modeNext);
			}
		}
	}
}

//=============================================================================
// タイトル画面
//=============================================================================
void CFade::Draw(void)
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

//=============================================================================
// フェードの状態の取得
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

//=============================================================================
// フェードの状態の設定
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext, FADE fade)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;
		m_modeNext = modeNext;

		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		if (fade == FADE_IN)
		{
			m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		}
	}

}