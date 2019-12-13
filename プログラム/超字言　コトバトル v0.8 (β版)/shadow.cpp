//=============================================================================
//
// 影の処理 [polygon.cpp]
// Author : 目黒未来也
//
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "load.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_POS_X_INIT			(1.0f)		//テクスチャ座標Uの初期位置
#define TEX_POS_Y_INIT			(1.0f)		//テクスチャ座標Vの初期位置
#define TEX_LEFT				(0.0f)		//テクスチャ座標U左
#define TEX_RIGHT				(1.0f)		//テクスチャ座標U右
#define TEX_TOP					(0.0f)		//テクスチャ座標V上
#define TEX_BOT					(1.0f)		//テクスチャ座標V下

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------

//--------------------------------------------
//影クラス コンストラクタ
//--------------------------------------------
CShadow::CShadow() : CScene3D(SHADOW_PRIORITY)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//位置
	m_rot = D3DXVECTOR3(0, 0, 0);		//向き
	D3DXMatrixIdentity(&m_mtxWorld);	//ワールドマトリックス
}

//--------------------------------------------
//影クラス デストラクタ
//--------------------------------------------
CShadow::~CShadow()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CShadow * CShadow::Create(D3DXVECTOR3 pos, float fWidth, float fDepth)
{
	CShadow *pShadow;

	pShadow = new CShadow;

	pShadow->m_pos = pos;
	pShadow->m_fWidth = fWidth;
	pShadow->m_fDepth = fDepth;
	pShadow->Init();

	return pShadow;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShadow::Init(void)
{
	CScene3D::Init();
	CScene3D::SetSize(m_fDepth, m_fWidth);
	CScene3D::BindTexture("SHADOW");
	CScene3D::SetPos(m_pos);
	//色の設定
	CScene3D::SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

	//オブジェクト種類の設定
	CScene3D::SetObjType(CScene::OBJTYPE_SHADOW);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShadow::Uninit(void)
{
	//終了処理
	CScene3D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CShadow::Update(void)
{
	//CScene3D::SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 10.0f, m_pos.z));
}

//=============================================================================
// 描画処理
//=============================================================================
void CShadow::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスを取得
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	//αブレンディングを減算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//アルファテスト(透明色を描画しないように)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 90);

	//描画処理
	CScene3D::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CShadow::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}