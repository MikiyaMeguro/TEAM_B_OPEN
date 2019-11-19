//=============================================================================
//
// 爆発クラス [explosion.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "explosion.h"

#include "manager.h"

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CExplosion3D::CExplosion3D(int pri, OBJTYPE type) : CMeshSphere(pri, type)
{

}
CExplosion3D::~CExplosion3D()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CExplosion3D* CExplosion3D::Create(void)
{
	CExplosion3D* pExplosion = NULL;

	pExplosion = new CExplosion3D(4, OBJTYPE_PARTICLE);

	if (pExplosion != NULL)
	{
		pExplosion->Init();
	}

	return pExplosion;
}

//=============================================================================
// 設定処理
//=============================================================================
void CExplosion3D::Set(D3DXVECTOR3 pos, float fStartSize, float fDestSize, int nLife, float fAnimSpeed)
{
	CMeshSphere::Set(pos, "EXPLOSION", 120, 120,
		D3DXVECTOR3(fStartSize, fStartSize, fStartSize),D3DXCOLOR(1.0f,0.75f,0.1f,0.5f));

	CMeshSphere::SetTexAnim(D3DXVECTOR2(fAnimSpeed,-fAnimSpeed));
	CMeshSphere::SetCntAnimTime(1);
	m_fDestSize = fDestSize;
	m_fSize = fStartSize;
	m_nLife = nLife;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion3D::Init(void)
{
	m_nCount = 0;
	CMeshSphere::Init();
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion3D::Uninit(void)
{
	CMeshSphere::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion3D::Update(void)
{
	//サイズ更新
	D3DXVECTOR3 Size = D3DXVECTOR3(m_fSize, m_fSize, m_fSize);
	D3DXVECTOR3 SizeDest = D3DXVECTOR3(m_fDestSize, m_fDestSize, m_fDestSize);

	D3DXVec3Lerp(&Size,&Size,&SizeDest,((float)(m_nCount + 1) / (float)m_nLife));

	GetScale() = Size;

	m_fSize = Size.x;	//どれも同じなので適当な数値を入れる

	//親クラスのUpdate
	CMeshSphere::Update();

	//装飾


	//消滅判定
	if (m_nCount > m_nLife)
	{
		Uninit();
	}
	m_nCount++;
}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion3D::Draw(void)
{
	//デバイスを取得
	CRenderer* pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	pDevice->SetRenderState(D3DRS_LIGHTING,FALSE);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CMeshSphere::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}