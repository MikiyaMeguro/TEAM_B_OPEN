//=============================================================================
//
// 弾基本処理 (C3DBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "manager.h"

#include "load.h"
#include "sceneBillboard.h"
#include "sceneX.h"
#include "game.h"
//=============================================================================
// コンストラクタ＆デストラクタ	(C3DBullet)
//=============================================================================
C3DBullet::C3DBullet(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
	m_fKnockBack = 0.0f;
}
C3DBullet::~C3DBullet()
{

}

//=============================================================================
// 設定処理(C3DBullet)
//=============================================================================
void C3DBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nID)
{
	m_pos = pos;
	m_rot = rot;
	m_fMove = fSpeed;
	m_nLife = nLife;

	m_nID = (nID % 4);//範囲外の数字が入ったらそれを0～3までの数字にする

	//m_fKnockBack = 7.0f;
	m_fCollisionRadius = 10.0f;	//判定サイズを設定
}

//=============================================================================
// 初期化処理(C3DBullet)
//=============================================================================
HRESULT C3DBullet::Init(void)
{

	SetObjType(OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
// 終了処理(C3DBullet)
//=============================================================================
void C3DBullet::Uninit(void)
{


	Release();
}

//=============================================================================
// 更新処理(C3DBullet)
//=============================================================================
void C3DBullet::Update(void)
{
	m_posOld = m_pos;
	//マトリックスを使用して移動量を求める
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, m_fMove);

	D3DXMATRIX Mtxmove, Mtxrot, Mtxtrans;
	D3DXMatrixIdentity(&Mtxmove);

	D3DXMatrixTranslation(&Mtxtrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxtrans);
	D3DXMatrixRotationYawPitchRoll(&Mtxrot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxrot);

	move = D3DXVECTOR3(Mtxmove._41, Mtxmove._42, Mtxmove._43);	//座標(移動量)を取り出す
	//メッシュフィールド(床)との当たり判定
	CMeshField *pMesh = CGame::GetMeshField();

	float fHeight = pMesh->GetHeight(m_pos + move);
	if ((m_pos.y - m_fCollisionRadius) < fHeight)
	{
		move.y = 0.0f;
	}

	m_MoveResult = move;
	m_pos += move;
}

//=============================================================================
// 描画処理(C3DBullet)
//=============================================================================
void C3DBullet::Draw(void)
{

}

//=============================================================================
// 画面内オブジェクトとの判定処理(C3DBullet)
//=============================================================================
bool C3DBullet::CollisionObject(void)
{
	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(SCENEX_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
			{// オブジェクトの種類を確かめる
				CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneXへキャスト(型の変更)
				if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
				{
					if (pSceneX->Collision(&m_pos, &m_posOld, &m_MoveResult, D3DXVECTOR3(m_fCollisionRadius, m_fCollisionRadius, m_fCollisionRadius)))
					{
						return true;
					}
				}
			}
		}

		// 次のシーンに進める
		pScene = pSceneNext;
	}

	return false;
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
CModelBullet::CModelBullet(int nPriority) : C3DBullet(nPriority)
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
void CModelBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, BULLET_PROPERTY type,int nID, D3DXVECTOR3 RotateOffset)
{
	m_pModel = CSceneX::Create(pos,rot,D3DXVECTOR3(1.0f,1.0f,1.0f),model,0);
	m_Prop = type;

	float fSpeed;
	switch (m_Prop)
	{
	case TYPE_HIGHSPEED:
		fSpeed = 8.0f;
		m_fKnockBack = 6.0f;
		break;
	case TYPE_STINGER:
		fSpeed = 6.0f;
		m_fKnockBack = 9.0f;
		break;
	case TYPE_KNOCKBACK:
		fSpeed = 3.0f;
		m_fKnockBack = 20.0f;
		break;
	case TYPE_REFLECT:
		fSpeed = 5.0f;
		m_fKnockBack = 8.0f;
		break;
	default:
		fSpeed = 5.0f;
		m_fKnockBack = 6.0f;
		break;
	}
	m_modelRotateOffSet = RotateOffset;
	C3DBullet::Set(pos,
		rot,
		fSpeed,
		100,
		nID);
}

//=============================================================================
// 初期化処理(CModelBullet)
//=============================================================================
HRESULT CModelBullet::Init(void)
{
	C3DBullet::Init();

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

	C3DBullet::Uninit();
}

//=============================================================================
// 更新処理(CModelBullet)
//=============================================================================
void CModelBullet::Update(void)
{
	C3DBullet::Update();
	if (m_pModel != NULL)
	{
		m_pModel->SetPosition(GetPosition());

		D3DXVECTOR3 Rotate = m_modelRotateOffSet + GetRotation();
		CUtilityMath::RotateNormarizePI(&Rotate);
		m_pModel->SetRot(Rotate);
	}
	int& nLife = GetLife();
	nLife--;

	if (m_Prop != TYPE_STINGER)
	{//貫通タイプでなければオブジェクトとの当たり判定をチェックする
		if (C3DBullet::CollisionObject())
		{//当たっていたら
			//反射タイプなら当たった後に角度をY軸で反転させる
			if (m_Prop == TYPE_REFLECT)
			{
				Reflect();
			}
			else
			{
				Uninit();
			}
		}
	}


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
// モデルの大きさ設定処理(CModelBullet)
//=============================================================================
void  CModelBullet::SetModelScale(const D3DXVECTOR3& scale)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetScale(scale);
	}
}

//=============================================================================
// 反射処理(CModelBullet)
//=============================================================================
void CModelBullet::Reflect(void)
{
	D3DXVECTOR3& rot = GetRotation();

	////現在の角度に応じて処理を変える
	//if (rot.y >= 0.0f)
	//{
	//	if (rot.y <= D3DX_PI * 0.25f)
	//	{//パターン①(0.0f~D3DX_PI * 0.25f)
	//		rot.y += D3DX_PI * -0.5f;
	//	}
	//	else if (rot.y <= D3DX_PI * 0.5f)
	//	{//パターン②(D3DX_PI * 0.25f~D3DX_PI * 0.50f)
	//		rot.y += -D3DX_PI;
	//	}
	//	else if (rot.y <= D3DX_PI * 0.75f)
	//	{//パターン③(D3DX_PI * 0.50f~D3DX_PI * 0.75f)
	//		rot.y += D3DX_PI * -0.5f;
	//	}
	//	else
	//	{//パターン④(D3DX_PI * 0.75f~D3DX_PI)
	//		rot.y += -D3DX_PI;
	//	}
	//}
	//else
	//{
	//	if (rot.y >= -D3DX_PI * 0.25f)
	//	{//パターン⑤(-D3DX_PI * 0.25f~ 0.0f)
	//		rot.y += D3DX_PI * 0.5f;
	//	}
	//	else if (rot.y >= -D3DX_PI * 0.5f)
	//	{//パターン⑥(-D3DX_PI * 0.50f~ -D3DX_PI * 0.25f)
	//		rot.y += D3DX_PI;
	//	}
	//	else if (rot.y >= -D3DX_PI * 0.75f)
	//	{//パターン⑦(-D3DX_PI * 0.75f~ -D3DX_PI * 0.50f)
	//		rot.y += D3DX_PI * 0.5f;
	//	}
	//	else
	//	{//パターン⑧(-D3DX_PI * 1.0f~ -D3DX_PI * 0.75f)
	//		rot.y += D3DX_PI;
	//	}
	//}

	CUtilityMath::RotateNormarizePI(&rot.y);
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
CWordBullet::CWordBullet(int nPriority) : C3DBullet(nPriority)
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
	C3DBullet::Set(pos, rot,fSpeed,nLife,nID);
	m_pWord = CSceneBillBoard::Create(pos,20.0f,20.0f,"WORD");
	if (m_pWord != NULL) { m_pWord->SetTexture(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)),
											   D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f))); };
}

//=============================================================================
// 初期化処理(CWordBullet)
//=============================================================================
HRESULT CWordBullet::Init(void)
{
	C3DBullet::Init();
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

	C3DBullet::Uninit();

}

//=============================================================================
// 更新処理(CWordBullet)
//=============================================================================
void CWordBullet::Update(void)
{
	C3DBullet::Update();

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
