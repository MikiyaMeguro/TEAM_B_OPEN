//=============================================================================
//
// シーン2D処理 [scene3D.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "scene3D.h"
#include "Manager.h"

//==================================================================
// 静的メンバ変数
//==================================================================
static bool g_DeleteFlag = true;		//ブロック消すフラグ(テスト)

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CScene3D::CScene3D(CScene::PRIORITY pri = PRIORITY_3) : CScene(pri, OBJTYPE_3D)
{

}
CScene3D::~CScene3D()
{

}

//==================================================================
// テクスチャの適用
//==================================================================
void CScene3D::BindTexture(LPCSTR TexTag)
{
	m_pTexture = CTexture::GetTexture(TexTag);
}

//==================================================================
// ポリゴンの設定処理
//==================================================================
void CScene3D::Set(D3DXVECTOR3 pos, LPCSTR TexTag, D3DXVECTOR3 Size,
	D3DXVECTOR3 rot,D3DXCOLOR col, D3DXVECTOR2 UVrectMin, D3DXVECTOR2 UVrectMax)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	BindTexture(TexTag);
	m_pos = pos;
	m_rot = rot;
	m_Col = col;
	m_Size = Size;
	m_UVRectMin = UVrectMin;
	m_UVRectMax = UVrectMax;

	//変数宣言
	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロックし、頂点データへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_Size.x, 0.0f, m_Size.z);
	pVtx[1].pos = D3DXVECTOR3(m_Size.x, 0.0f, m_Size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_Size.x, 0.0f, -m_Size.z);
	pVtx[3].pos = D3DXVECTOR3(m_Size.x, 0.0f, -m_Size.z);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = m_Col;
	pVtx[1].col = m_Col;
	pVtx[2].col = m_Col;
	pVtx[3].col = m_Col;

	pVtx[0].tex = D3DXVECTOR2(UVrectMin.x, UVrectMin.y);
	pVtx[1].tex = D3DXVECTOR2(UVrectMax.x, UVrectMin.y);
	pVtx[2].tex = D3DXVECTOR2(UVrectMin.x, UVrectMax.y);
	pVtx[3].tex = D3DXVECTOR2(UVrectMax.x, UVrectMax.y);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}

//==================================================================
// ポリゴンの初期化処理
//==================================================================
HRESULT CScene3D::Init(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/WS000635.JPG", &m_pTexture);

	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	return S_OK;
}

//==================================================================
// ポリゴンの終了処理
//==================================================================
void CScene3D::Uninit(void)
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
void CScene3D::Update(void)
{

}

//==================================================================
// ポリゴンの描画処理
//==================================================================
void CScene3D::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス

	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y,
		m_rot.x,
		m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));//頂点バッファをデバイスのデータストリームに設定

	pDevice->SetFVF(FVF_VERTEX_3D);//頂点フォーマットの設定

								   // テクスチャの設定
	pDevice->SetTexture(0,m_pTexture);//テクスチャの設定

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリミティブの種類					//プリミティブ == ポリゴン
		0,					   //開始する頂点のインデックス(基本０)
		2);		   	       //プリミティブの数
}

//==================================================================
// 各種設定処理
//==================================================================
void CScene3D::SetPosition(D3DXVECTOR3 pos)
{//座標のみ設定
	m_pos = pos;
}

void CScene3D::SetRotation(D3DXVECTOR3 rot)
{//角度のみ設定
	m_rot = rot;
}
void CScene3D::SetColor(D3DXCOLOR col)
{
	// 変数宣言
	VERTEX_3D* pVtx;

	m_Col = col;
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	m_pVtxBuff->Unlock();

}

void CScene3D::SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect)
{
	// 変数宣言
	VERTEX_3D* pVtx;

	m_UVRectMin = MinRect;
	m_UVRectMax = MaxRect;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = MinRect;
	pVtx[1].tex = D3DXVECTOR2(MaxRect.x, MinRect.y);
	pVtx[2].tex = D3DXVECTOR2(MinRect.x, MaxRect.y);
	pVtx[3].tex = MaxRect;

	m_pVtxBuff->Unlock();

}

