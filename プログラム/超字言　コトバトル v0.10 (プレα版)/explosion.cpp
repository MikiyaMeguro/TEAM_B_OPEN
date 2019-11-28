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
	m_bNotDup = false;

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

	pExplosion = new CExplosion3D(EXPLOSION_PRIORITY, OBJTYPE_EXPLOSION);

	if (pExplosion != NULL)
	{
		pExplosion->Init();
	}

	return pExplosion;
}

//=============================================================================
// 設定処理
//=============================================================================
void CExplosion3D::Set(D3DXVECTOR3 pos, float fStartSize, float fDestSize, int nLife, float fAnimSpeed, LPCSTR Tag)
{//短縮設定版
	CMeshSphere::Set(pos, Tag, 40, 40,
		D3DXVECTOR3(fStartSize, fStartSize, fStartSize), D3DXCOLOR(0.90f,0.50f,0.05f,0.5f), D3DXVECTOR3(0.0f,0.0f,0.0f));
	CMeshSphere::SetTexAnim(D3DXVECTOR2(fAnimSpeed, -fAnimSpeed));
	CMeshSphere::SetCntAnimTime(1);

	m_fDestSize = fDestSize;
	m_fSize = fStartSize;
	m_nLife = nLife;
	m_nExpandTime = nLife;
	m_nCount = 0;
	m_spinSpeed = D3DXVECTOR3(0.0f, 0.4f, 0.0f);	//少し回す

	if (m_bNotDup == false)
	{
		//キレイに見せるために何個か重ねる
		CExplosion3D* p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, -0.005f); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, 0.02f); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, -0.015f); }
	}
	m_bNotDup = true;

}
void CExplosion3D::SetEX(D3DXVECTOR3 pos, float fStartSize, float fDestSize, int nLife, float fAnimSpeed,
	D3DXVECTOR3 rot, D3DXCOLOR col, LPCSTR Tag, int nMesh, int nExpandTime, D3DXVECTOR3 spinSpeed)
{//詳細設定版
	CMeshSphere::Set(pos, Tag, nMesh, nMesh,
		D3DXVECTOR3(fStartSize, fStartSize, fStartSize) ,col,rot);

	CMeshSphere::SetTexAnim(D3DXVECTOR2(fAnimSpeed,-fAnimSpeed));
	CMeshSphere::SetCntAnimTime(1);
	m_nCount = 0;

	m_fDestSize = fDestSize;
	m_fSize = fStartSize;
	m_nLife = nLife;
	m_nExpandTime = nExpandTime;
	m_spinSpeed = spinSpeed;

	if (m_bNotDup == false)
	{
		//キレイに見せるために何個か重ねる
		CExplosion3D* p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife,-0.005f); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, 0.02f); }

		p3D = CExplosion3D::Create();
		p3D->IsNotDup(true);
		if (p3D != NULL) { p3D->Set(pos, fStartSize, fDestSize, nLife, -0.015f); }

	}
	m_bNotDup = true;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion3D::Init(void)
{
	m_nCount = 0;
	m_bNotDup = false;
	m_spinSpeed = D3DXVECTOR3(0.0f,0.0f,0.0f);
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

	if (m_nCount <= m_nExpandTime)
	{
		D3DXVec3Lerp(&Size, &Size, &SizeDest, ((float)(m_nCount + 1) / (float)m_nExpandTime));
	}

	GetScale() = Size;

	m_fSize = Size.x;	//どれも同じなので適当な数値を入れる

	//回転(spinSpeedを加算する)
	GetRotation() += m_spinSpeed;

	//親クラスのUpdate
	CMeshSphere::Update();

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