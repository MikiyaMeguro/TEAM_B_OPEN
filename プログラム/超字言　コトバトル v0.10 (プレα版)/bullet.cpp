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

#include "debugProc.h"
#include "explosion.h"
#include "tutorial.h"

#include "LineOrbit.h"
#include "effect.h"
//=============================================================================
// コンストラクタ＆デストラクタ	(CBulletBase)
//=============================================================================
C3DBullet::C3DBullet(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
	m_fKnockBack = 0.0f;
	m_MoveResult = D3DXVECTOR3(0.0f,0.0f,0.0f);
}
C3DBullet::~C3DBullet()
{

}

//=============================================================================
// 設定処理(CBulletBase)
//=============================================================================
void C3DBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nID)
{
	m_pos = pos;
	m_rot = rot;
	m_fMove = fSpeed;
	m_nLife = nLife;
	m_nMaxLife = nLife;
	m_fHeight = pos.y;
	m_nID = (nID % 4);//範囲外の数字が入ったらそれを0～3までの数字にする

	m_fCollisionRadius = 10.0f;
	m_fKnockBack = 7.0f;
	m_nCount = 0;
	//先に回転マトリックスを作成しておく
	D3DXMatrixRotationYawPitchRoll(&m_mtxRotate, m_rot.y, m_rot.x, m_rot.z);

}

//=============================================================================
// 初期化処理(CBulletBase)
//=============================================================================
HRESULT C3DBullet::Init(void)
{
	SetObjType(OBJTYPE_BULLET);//タイプをセット

	/*変数初期化*/
	m_pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fMove = 0.0f;
	m_nLife = 0;
	m_nID = 0;
	m_fCollisionRadius = 10.0f;
	m_fKnockBack = 7.0f;
	D3DXMatrixRotationYawPitchRoll(&m_mtxRotate, m_rot.y, m_rot.x, m_rot.z);

	return S_OK;
}

//=============================================================================
// 終了処理(CBulletBase)
//=============================================================================
void C3DBullet::Uninit(void)
{
	Release();
}

//=============================================================================
// 更新処理(CBulletBase)
//=============================================================================
void C3DBullet::Update(void)
{
	m_posOld = m_pos;	//１フレーム前の座標を変数に格納

	//マトリックスを使用して移動量を求める
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, m_fMove);

	D3DXMATRIX Mtxmove, Mtxtrans;
	D3DXMatrixIdentity(&Mtxmove);

	D3DXMatrixTranslation(&Mtxtrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxtrans);

	//回転マトリックスは最初に求めたものを使う
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &m_mtxRotate);

	move = D3DXVECTOR3(Mtxmove._41, Mtxmove._42, Mtxmove._43);	//座標(移動量)を取り出す

	//床との当たり判定
	CMeshField *pMesh = CManager::GetMeshField();
	float fHeight = pMesh->GetHeight(m_pos + move);
	if (m_pos.y < fHeight)
	{
		move.y = 0.0f;
	}

	m_MoveResult = move;	//求めた差分を格納
	m_pos += move;			//座標に移動値をプラス

	//移動後の位置マトリックスを生成
	D3DXMatrixTranslation(&m_mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	/*デバック*/
	CDebugProc::Print("cf", "BULLET_ROT_Y", m_rot.y);
}

//=============================================================================
// 描画処理(CBulletBase)
//=============================================================================
void C3DBullet::Draw(void)
{

}

//=============================================================================
// オブジェクトとの当たり判定処理(CBulletBase)
//=============================================================================
bool C3DBullet::CollisionObject(CManager::DIRECTION* dir)
{//引数あり
	CScene* pScene = NULL;
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
				if (pSceneX->GetCollsionType() == CSceneX::COLLISIONTYPE_BOX)
				{
					D3DXVECTOR3 vtxMin = pSceneX->GetVtxMin();
					D3DXVECTOR3 vtxMax = pSceneX->GetVtxMax();
					D3DXVECTOR3 OBJpos = pSceneX->GetPosition();

					if (m_pos.y <= OBJpos.y + vtxMax.y &&m_pos.y + m_fCollisionRadius >= OBJpos.y + vtxMax.y ||
						m_pos.y + m_fCollisionRadius >= OBJpos.y + vtxMin.y &&m_pos.y <= OBJpos.y + vtxMin.y ||
						m_pos.y + m_fCollisionRadius <= OBJpos.y + vtxMax.y  && m_pos.y >= OBJpos.y + vtxMin.y)
					{//ｙが範囲内なら
						if (m_pos.z - m_fCollisionRadius <= OBJpos.z + vtxMax.z &&
							m_pos.z + m_fCollisionRadius >= OBJpos.z + vtxMin.z)
						{// zの範囲の中
							if (m_posOld.x + m_fCollisionRadius <= OBJpos.x + vtxMin.x
								&& m_pos.x + m_fCollisionRadius > OBJpos.x + vtxMin.x)
							{// X座標の中に左から入った
								*dir = CManager::DIR_LEFT_WEST;
								return true;
							}
							else if (m_posOld.x - m_fCollisionRadius >= OBJpos.x + vtxMax.x
								   && m_pos.x - m_fCollisionRadius < OBJpos.x + vtxMax.x)
							{// X座標の中に右から入った
								*dir = CManager::DIR_RIGHT_EAST;
								return true;
							}
						}

						if (m_pos.x - m_fCollisionRadius <= OBJpos.x + vtxMax.x &&
							m_pos.x + m_fCollisionRadius >= OBJpos.x + vtxMin.x)
						{// xの範囲の中
							if (m_posOld.z + m_fCollisionRadius <= OBJpos.z + vtxMin.z
								&& m_pos.z + m_fCollisionRadius > OBJpos.z + vtxMin.z)
							{// Z座標の中に手前から入った
								*dir = CManager::DIR_DOWN_SOUTH;
								return true;
							}
							else if (m_posOld.z - m_fCollisionRadius >= OBJpos.z + vtxMax.z
								&& m_pos.z - m_fCollisionRadius < OBJpos.z + vtxMax.z)
							{// Z座標の中に後ろから入った
								*dir = CManager::DIR_UP_NORTH;
								return true;
							}
						}

					}
				}
			}
		}

		pScene = pSceneNext;	//記録した情報を探索するためにポインタをわたす
	}

	return false;
}
bool C3DBullet::SimpleCollision(void)
{//引数なし(引数を返さずに有のほうを使う)
	CManager::DIRECTION dir;
	return CollisionObject(&dir);
}

//=============================================================================
// 追尾処理(CBulletBase)
//=============================================================================
void C3DBullet::Homing(D3DXVECTOR3 HomingPos)
{
	D3DXQUATERNION Quat,HomingQuat,dest;
	//現在の角度マトリックスからクォータニオンを生成
	D3DXQuaternionRotationMatrix(&Quat,&m_mtxRotate);

	//弾の位置ベクトルとホーミングしたい物の位置ベクトルからクォータニオンを作成(Y軸回転のみ)
	float fRotY = atan2f((HomingPos.x - m_pos.x), (HomingPos.z - m_pos.z));
	CUtilityMath::RotateNormarizePI(&fRotY);
	D3DXQuaternionRotationYawPitchRoll(&HomingQuat,fRotY,0.0f,0.0f);

	//二つのクォータニオンを球面補間する
	D3DXQuaternionSlerp(&dest,&Quat,&HomingQuat, BULLET_HOMING_COEFFICIENT);

	//求めたクォータニオンを角度マトリックスに変換
	D3DXMatrixRotationQuaternion(&m_mtxRotate,&dest);
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
	m_pModel = NULL;
	m_pOrbit = NULL;
	m_nCntEffect = 0;

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
	//float fSpeed = 1.0f;

	//タイプによって処理を分ける
	float fSpeed = 3.0f;
	int nLife = 100;
	switch (m_Prop)
	{
	case TYPE_HIGHSPEED:
		fSpeed = 8.0f;
		m_fKnockBack = 6.0f;
		m_pOrbit = CLineOrbit::Create();
		if (m_pOrbit != NULL)
		{
			m_pOrbit->Set(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10.0f, &m_mtxTrans, "",
				D3DXCOLOR(0.0f, 0.6f, 1.0f, 0.7f), 40, 1);
		}
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
		m_fKnockBack = 8.0f;
		break;
	case TYPE_MACHINEGUN:
		m_fKnockBack = 0.0f;
		fSpeed = 7.0f;
		nLife = 150;
		break;
	case TYPE_SHOTGUN:
		m_fKnockBack = 3.0f;
		fSpeed = 7.0f;
		nLife = 20;
		break;
	case TYPE_SHOTGUN_MEDIUM:
		m_fKnockBack = 3.0f;
		fSpeed = 6.5f;
		nLife = 20;
		break;
	case TYPE_SHOTGUN_SLOW:
		m_fKnockBack = 3.0f;
		fSpeed = 6.0f;
		nLife = 20;
		break;
	case TYPE_MISSILE_CENTER:
		fSpeed = 4.5f;
		m_fKnockBack = 1.0f;
		break;
	case TYPE_MISSILE_SIDE:
		fSpeed = 5.0f;
		m_fKnockBack = 1.0f;
		break;
	case TYPE_BOMB:
		fSpeed = 3.5f;
		m_fKnockBack = 10.0f;
		nLife = 60;
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
		nLife,
		nID);
}

//=============================================================================
// 初期化処理(CModelBullet)
//=============================================================================
HRESULT CModelBullet::Init(void)
{
	C3DBullet::Init();
	m_pHomingChara = NULL;
	m_Type = TYPE_MODEL;
	return S_OK;
}

//=============================================================================
// 終了処理(CModelBullet)
//=============================================================================
void CModelBullet::Uninit(void)
{
	CExplosion3D* p3D = NULL;
	switch (m_Prop)
	{
	case TYPE_HIGHSPEED:
		if (m_pOrbit != NULL)
		{
			m_pOrbit->Uninit();
			m_pOrbit = NULL;
		}
		break;
	case TYPE_KNOCKBACK:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 80.0f, 120, 0.01f); }
		break;
	case TYPE_STINGER:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_REFLECT:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_MISSILE_CENTER:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_MISSILE_SIDE:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 30.0f, 60, 0.01f); }
		break;
	case TYPE_BOMB:
		p3D = CExplosion3D::Create();
		if (p3D != NULL) { p3D->Set(GetPosition(), 0.001f, 80.0f, 120, 0.01f); }
		break;

	default:
		break;
	}

	//モデルを消す
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
	int& nLife = GetLife();
	nLife--;
	m_nCntEffect++;
	m_nCount++;

	D3DXVECTOR3 pos = CModelBullet::GetPosition();
	if (m_Prop == TYPE_MISSILE_CENTER || m_Prop == TYPE_MISSILE_SIDE || m_Prop == TYPE_STINGER || m_Prop == TYPE_REFLECT)
	{//ミサイル
		if (m_nCntEffect % 6 == 0)
		{
			CEffect::Create(pos, 4, 4);
		}

		if (m_pHomingChara != NULL)
		{
			Homing(m_pHomingChara->GetPosition());
		}
	}
	else if (m_Prop == TYPE_KNOCKBACK || m_Prop == TYPE_BOMB)
	{//爆発
		float fUp = sinf((float)m_nCount / (float) ((float)m_nMaxLife / 4.0f));
		fUp *= 100.0f;//定数を掛ける

		GetPosition().y = m_fHeight + fUp;

		//床との当たり判定
		CMeshField *pMesh = CManager::GetMeshField();
		float fHeight = pMesh->GetHeight(GetPosition());
		if (GetPosition().y < fHeight)
		{
			Uninit();
			return;
		}

		if (m_nCntEffect % 6 == 0)
		{
			CEffect::Create(pos, 5, 5);
		}
	}
	else if (m_Prop == TYPE_MACHINEGUN)
	{//	マシンガン
		if (m_nCntEffect % 7 == 0)
		{
			CEffect::Create(pos, 5, 7);
		}
		if (m_nCntEffect % 14 == 0)
		{
			CEffect::Create(pos, 5, 8);

		}
	}
	else if (m_Prop == TYPE_NORMAL)
	{//ゴミ
		if (m_nCntEffect % 6 == 0)
		{
			CEffect::Create(pos, 6, 5);
		}
	}

	C3DBullet::Update();

	//弾モデルに正しい角度を設定する
	if (m_pModel != NULL)
	{
		m_pModel->SetPosition(GetPosition());

		D3DXVECTOR3 Rotate = m_modelRotateOffSet + GetRotation();
		CUtilityMath::RotateNormarizePI(&Rotate);
		m_pModel->SetRot(Rotate);
	}

	//当たり判定
	if (m_Prop != TYPE_BOMB)
	{//爆弾は地形を無視する(なるべく爆発が自分に当たらないように)
		if (SimpleCollision())
		{
			Uninit();//当たっていたら消す
			return;
		}
	}
	//体力判定
	if (nLife < 0)
	{
		Uninit();//寿命0なら消す
		return;
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
// モデルの向き設定処理(CModelBullet)
//=============================================================================
void  CModelBullet::SetModelRot(const D3DXVECTOR3& rot)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetRot(rot);
	}
}

//=============================================================================
// 反射処理(CModelBullet)
//=============================================================================
void CModelBullet::Reflect(CManager::DIRECTION dir)
{
	D3DXVECTOR3& rot = GetRotation();

	switch (dir)
	{
	case CManager::DIR_RIGHT_EAST:	//東(+X方向)
		rot.y *= -1.0f;		//反転
		break;
	case CManager::DIR_LEFT_WEST:	//西(-X方向)
		rot.y *= -1.0f;		//反転
		break;
	case CManager::DIR_DOWN_SOUTH:  //南(-Z方向)
		rot.y = (rot.y + D3DX_PI) * -1.0f;	//線対称→反転
		break;
	case CManager::DIR_UP_NORTH:	//北(+Z方向)
		rot.y = (rot.y + D3DX_PI) * -1.0f;  //線対称→反転
		break;
	default:
		return;	//万が一それ以外の値が入っていたときは処理から抜ける
		break;
	}
	CUtilityMath::RotateNormarizePI(&rot.y);

	//モデルにも角度を設定
	SetModelRot(rot);
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
// 生成処理(CWordBullet)
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
	int& nLife = GetLife();
	nLife--;
	C3DBullet::Update();
	if (m_pWord != NULL)
	{
		m_pWord->Setpos(GetPosition());
	}

	if (SimpleCollision())
	{//当たっていれば
		Uninit();
		return;
	}
	if (nLife < 0)
	{
		Uninit();
		return;
	}
}

//=============================================================================
// 描画処理(CWordBullet)
//=============================================================================
void CWordBullet::Draw(void)
{

}

