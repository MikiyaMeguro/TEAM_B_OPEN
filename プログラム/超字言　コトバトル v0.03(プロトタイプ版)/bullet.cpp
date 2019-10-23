//=============================================================================
//
// 弾基本処理 (CBulletBase)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "manager.h"

#include "load.h"
#include "sceneBillboard.h"
#include "sceneX.h"
//=============================================================================
// コンストラクタ＆デストラクタ	(CBulletBase)
//=============================================================================
CBulletBase::CBulletBase(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
}
CBulletBase::~CBulletBase()
{

}

//=============================================================================
// 設定処理(CBulletBase)
//=============================================================================
void CBulletBase::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nID)
{
	m_pos = pos;
	m_rot = rot;
	m_fMove = fSpeed;
	m_nLife = nLife;

	m_nID = (nID % 4);//範囲外の数字が入ったらそれを0～3までの数字にする
}

//=============================================================================
// 初期化処理(CBulletBase)
//=============================================================================
HRESULT CBulletBase::Init(void)
{

	SetObjType(OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
// 終了処理(CBulletBase)
//=============================================================================
void CBulletBase::Uninit(void)
{


	Release();
}

//=============================================================================
// 更新処理(CBulletBase)
//=============================================================================
void CBulletBase::Update(void)
{
	//マトリックスを使用して移動量を求める
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, m_fMove);

	D3DXMATRIX Mtxmove, Mtxrot, Mtxtrans;
	D3DXMatrixIdentity(&Mtxmove);

	D3DXMatrixTranslation(&Mtxtrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxtrans);
	D3DXMatrixRotationYawPitchRoll(&Mtxrot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxrot);

	move = D3DXVECTOR3(Mtxmove._41, Mtxmove._42, Mtxmove._43);	//座標(移動量)を取り出す

	m_pos += move;

	//床との判定

}

//=============================================================================
// 描画処理(CBulletBase)
//=============================================================================
void CBulletBase::Draw(void)
{

}

//=============================================================================
//
// モデル弾処理 (CModelBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// コンストラクタ＆デストラクタ	(CModelBullet)
//=============================================================================
CModelBullet::CModelBullet(int nPriority) : CBulletBase(nPriority)
{

}
CModelBullet::~CModelBullet()
{

}
//=============================================================================
// 設定処理(CModelBullet)
//=============================================================================
CModelBullet* CModelBullet::Create(void)
{
	CModelBullet* pBullet = NULL;
	pBullet = new CModelBullet(BULLET_PRIORITY);
	if (pBullet != NULL)
	{
		pBullet->Init();
	}
	return pBullet;
}
//=============================================================================
// 設定処理(CModelBullet)
//=============================================================================
void CModelBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, float fSpeed, int nLife, int nID)
{
	m_pModel = CSceneX::Create(pos,rot,D3DXVECTOR3(1.0f,1.0f,1.0f),model,0);


	CBulletBase::Set(pos,rot,fSpeed,nLife, nID);
}

//=============================================================================
// 初期化処理(CModelBullet)
//=============================================================================
HRESULT CModelBullet::Init(void)
{
	CBulletBase::Init();

	m_Type = TYPE_MODEL;
	return S_OK;
}

//=============================================================================
// 終了処理(CModelBullet)
//=============================================================================
void CModelBullet::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		m_pModel = NULL;
	}

	CBulletBase::Uninit();
}

//=============================================================================
// 更新処理(CModelBullet)
//=============================================================================
void CModelBullet::Update(void)
{
	CBulletBase::Update();
	m_pModel->SetPosition(GetPosition());
	m_pModel->SetRot(GetRotation());
	int& nLife = GetLife();
	nLife--;
	if (nLife < 0)
	{
		Uninit();
	}

}

//=============================================================================
// 描画処理(CModelBullet)
//=============================================================================
void CModelBullet::Draw(void)
{

}

//=============================================================================
//
// 文字弾処理 (CWordBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// コンストラクタ＆デストラクタ	(CWordBullet)
//=============================================================================
CWordBullet::CWordBullet(int nPriority) : CBulletBase(nPriority)
{
	m_pWord = NULL;
}
CWordBullet::~CWordBullet()
{

}

//=============================================================================
// 設定処理(CModelBullet)
//=============================================================================
CWordBullet* CWordBullet::Create(void)
{
	CWordBullet* pBullet = NULL;
	pBullet = new CWordBullet(BULLET_PRIORITY);
	if (pBullet != NULL)
	{
		pBullet->Init();
	}
	return pBullet;
}

//=============================================================================
// 設定処理(CWordBullet)
//=============================================================================
void CWordBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nWordNum, int nID)
{
	CBulletBase::Set(pos, rot,fSpeed,nLife,nID);
	m_pWord = CSceneBillBoard::Create(pos,20.0f,20.0f,"WORD");
	if (m_pWord != NULL) { m_pWord->SetTexture(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)),
											   D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f))); };
}

//=============================================================================
// 初期化処理(CWordBullet)
//=============================================================================
HRESULT CWordBullet::Init(void)
{
	CBulletBase::Init();
	m_Type = TYPE_WORD;

	return S_OK;
}

//=============================================================================
// 終了処理(CWordBullet)
//=============================================================================
void CWordBullet::Uninit(void)
{
	if (m_pWord != NULL)
	{
		m_pWord->Uninit();
		m_pWord = NULL;
	}

	CBulletBase::Uninit();

}

//=============================================================================
// 更新処理(CWordBullet)
//=============================================================================
void CWordBullet::Update(void)
{
	CBulletBase::Update();

	m_pWord->Setpos(GetPosition());
	int& nLife = GetLife();
	nLife--;
	if (nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理(CWordBullet)
//=============================================================================
void CWordBullet::Draw(void)
{

}
