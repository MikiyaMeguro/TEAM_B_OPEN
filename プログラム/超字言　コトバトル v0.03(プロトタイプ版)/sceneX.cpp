//=============================================================================
//
// 3Dモデル処理 [sceneX.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "load.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define SCENEX_SIZE	(1.0f)	// サイズの調節

//=============================================================================
// 3Dモデルクラスのコンストラクタ
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pMesh = NULL;							// メッシュ情報（頂点情報）へのポインタ
	m_pBuffMat = NULL;						// マテリアル情報へのポインタ
	m_nNumMat = 0;							// マテリアル情報の数
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 向き
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//大きさ
	m_CollisionType = COLLISIONTYPE_NONE;
	m_nCollsionNum = 0;
	m_bDraw = true;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Rot, D3DXVECTOR3 Scale, CLoad::MODEL model, int nCollision)
{
	CSceneX *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		// オブジェクトクラスの生成
		pSceneX = new CSceneX;

		if (pSceneX != NULL)
		{
			pSceneX->m_ModelType = model;
			pSceneX->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));
			pSceneX->m_pos = pos;
			pSceneX->m_rot = Rot;
			pSceneX->m_Scale = Scale;
			pSceneX->m_CollisionType = (COLLISIONTYPE)nCollision;
			pSceneX->Init(pos);
		}
	}

	return pSceneX;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SCENEX);

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	SetPosition(pos);

	// 頂点座標の設定
	SetVtx();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneX::Uninit(void)
{
	//ポインタのNULLチェック (家)
	if (m_pTexture != NULL)
	{
		for (int nCnt = 0; nCnt < (int)m_nNumMat; nCnt++)
		{
			//ポインタ内のポインタのNULLチェック (家具)
			if (m_pTexture[nCnt] != NULL)
			{
				//テクスチャ破棄
				//m_pTexture[nCnt]->Release();
				//m_pTexture[nCnt] = NULL;
			}
		}
		//メモリを開放 (解体)
		//delete[] m_pTexture;
		//NULLを入れる (更地)
		//m_pTexture = NULL;
	}
	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneX::Update(void)
{

#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneX::Draw(void)
{
#if 1

	D3DXMATRIX mtxRot, mtxTrans, mtxScale;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	//頂点法線の自動正規化
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//拡大縮小の反映
	D3DXMatrixScaling(&mtxScale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	if (m_bDraw == true)
	{//モデルが見える状態なら
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			if (pMat[nCntMat].pTextureFilename != NULL)
			{// マテリアルにテクスチャがあった場合

				if (m_pTexture != NULL)
				{
					// テクスチャの設定
					pDevice->SetTexture(0, m_pTexture[nCntMat]);
				}
				else
				{// マテリアルにテクスチャが無かった場合
					pDevice->SetTexture(0, NULL);
				}
			}
			else
			{// マテリアルにテクスチャが無かった場合
				pDevice->SetTexture(0, NULL);
			}

			// モデル(パーツ)の描画
			m_pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}

	//頂点法線の自動正規化
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

#endif
}

//=============================================================================
// 頂点座標の設定処理
//=============================================================================
void CSceneX::SetVtx(void)
{
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	D3DXVECTOR3 vtx;
	int nNumVtx;	//頂点数
	BYTE *pVtxBuff;	//頂点バッファへのポインタ

					// 頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();
	// 頂点フォーマットのサイズを取得
	sizeFvF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点の最小値と最大値を代入
	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{//頂点座標の代入
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}
		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}
		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}
		if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}
		if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		//サイズ分ポインタを進める
		pVtxBuff += sizeFvF;
	}
	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();

	// 大きさに合わせて調整
	m_VtxMax = D3DXVECTOR3(m_VtxMax.x * m_Scale.x, m_VtxMax.y * m_Scale.y, m_VtxMax.z * m_Scale.z);
	m_VtxMin = D3DXVECTOR3(m_VtxMin.x * m_Scale.x, m_VtxMin.y * m_Scale.y, m_VtxMin.z * m_Scale.z);
}

//=============================================================================
// ブロックとの当たり判定処理
//=============================================================================
bool CSceneX::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	bool bLand = false;	// 乗っていない状態
	bool bHit = false;	// ヒット判定のフラグ

	D3DXVECTOR3 ScaleVtxMax;
	D3DXVECTOR3 ScaleVtxMin;

	// 拡大を反映
	ScaleVtxMax.x = m_VtxMax.x;
	ScaleVtxMax.y = m_VtxMax.y;
	ScaleVtxMax.z = m_VtxMax.z;
	ScaleVtxMin.x = m_VtxMin.x;
	ScaleVtxMin.y = m_VtxMin.y;
	ScaleVtxMin.z = m_VtxMin.z;

	if (m_CollisionType == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING || m_CollisionType == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL ||
		m_CollisionType == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG || m_CollisionType == CSceneX::COLLISIONTYPE_BOX)
	{	// ベルトコンベア以外の場合
		bHit = true;
	}

	if (m_CollisionType != COLLISIONTYPE_NONE)
	{
		if (pos->y <= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE && pos->y + radius.y >= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE
			|| pos->y + radius.y >= m_pos.y + ScaleVtxMin.y && pos->y <= m_pos.y + ScaleVtxMin.y
			|| pos->y + radius.y <= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE && pos->y >= m_pos.y + ScaleVtxMin.y)
		{// yの範囲の中
			if (pos->z - radius.z <= m_pos.z + ScaleVtxMax.z && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z)
			{// zの範囲の中
				if (posOld->x + radius.x <= m_pos.x + ScaleVtxMin.x
					&& pos->x + radius.x > m_pos.x + ScaleVtxMin.x)
				{// X座標の中に左から入った
					pos->x = posOld->x;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// ノックバック以外の種類なら
						move->x = 0.0f;
					}
					m_nCollsionNum = 0;
					bLand = true;
				}
				else if (posOld->x - radius.x >= m_pos.x + ScaleVtxMax.x
					&& pos->x - radius.x < m_pos.x + ScaleVtxMax.x)
				{// X座標の中に右から入った
					pos->x = posOld->x;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// ノックバック以外の種類なら
						move->x = 0.0f;
					}
					m_nCollsionNum = 1;
					bLand = true;
				}
			}
			if (pos->x - radius.x <= m_pos.x + ScaleVtxMax.x && pos->x + radius.x >= m_pos.x + ScaleVtxMin.x)
			{// xの範囲の中
				if (posOld->z + radius.z <= m_pos.z + ScaleVtxMin.z
					&& pos->z + radius.z > m_pos.z + ScaleVtxMin.z)
				{// Z座標の中に手前から入った
					pos->z = posOld->z;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// ノックバック以外の種類なら
						move->z = 0.0f;
					}
					m_nCollsionNum = 2;
					bLand = true;
				}
				else if (posOld->z - radius.z >= m_pos.z + ScaleVtxMax.z
					&& pos->z - radius.z < m_pos.z + ScaleVtxMax.z)
				{// Z座標の中に後ろから入った
					pos->z = posOld->z;
					if (m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_DURING && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL && m_CollisionType != CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
					{	// ノックバック以外の種類なら
						move->z = 0.0f;
					}
					m_nCollsionNum = 3;
					bLand = true;
				}
			}
		}

		if (pos->x - radius.x < m_pos.x + ScaleVtxMax.x - SCENEX_SIZE && pos->x + radius.x > m_pos.x + ScaleVtxMin.x + SCENEX_SIZE
			&& pos->z - radius.z <= m_pos.z + ScaleVtxMax.z - SCENEX_SIZE && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z + SCENEX_SIZE)
		{// 障害物の内側に乗った
			if (bHit == false) { bLand = true; }	// ベルトコンベアの場合
			if (posOld->y >= m_pos.y + ScaleVtxMax.y && pos->y < m_pos.y + ScaleVtxMax.y
				|| pos->y <= m_pos.y + ScaleVtxMax.y && posOld->y > m_pos.y + ScaleVtxMax.y)
			{// 上からブロックに当たったとき
				bLand = true;  // 乗った判定を返す
				pos->y = m_pos.y + ScaleVtxMax.y;
				move->y = 0.0f;  // 移動量をなくす
			}

			if (posOld->y + radius.y < m_pos.y + ScaleVtxMin.y && pos->y + radius.y >= m_pos.y + ScaleVtxMin.y
				|| pos->y + radius.y > m_pos.y + ScaleVtxMin.y && posOld->y + radius.y <= m_pos.y + ScaleVtxMin.y)
			{// 下からブロックに当たったとき
				pos->y = posOld->y;
				move->y = 0.0f;  // 移動量をなくす
				bLand = true;
			}
		}
	}

	return bLand;	// ブロックに乗っているかどうかを返す
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CSceneX::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// モデルを割り当てる
//=============================================================================
void CSceneX::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;

	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();
	//マテリアルデータへのポインタ
	D3DXMATERIAL *pMat;
	//マテリアル情報からテクスチャの取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//テクスチャをマテリアルの数分動的確保
	//m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	m_pTexture = CLoad::GetTexture(m_ModelType);



	//マテリアルの数回す
	//for (int nCntMatTex = 0; nCntMatTex < (int)m_nNumMat; nCntMatTex++)
	//{
	//	//NULLを入れる 中身を空に
	//	m_pTexture[nCntMatTex] = NULL;

	//	if (pMat[nCntMatTex].pTextureFilename != NULL)
	//	{
	//		// テクスチャの設定
	//		D3DXCreateTextureFromFile(pDevice,		// デバイスへのポインタ
	//			pMat[nCntMatTex].pTextureFilename,	// ファイルの名前
	//			&m_pTexture[nCntMatTex]);		// テクスチャへのポインタ
	//	}
	//}
}

//=============================================================================
// テクスチャマテリアルを割り当てる
//=============================================================================
void CSceneX::BindTex(LPDIRECT3DTEXTURE9 *pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// 頂点情報の最大値の取得
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMax(void)
{
	return m_VtxMax;
}

//=============================================================================
// 頂点情報の最大値の設定
//=============================================================================
void CSceneX::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	m_VtxMax = VtxMax;
}

//=============================================================================
// 頂点情報の最小値の取得
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMin(void)
{
	return m_VtxMin;
}

//=============================================================================
// 頂点情報の最小値の設定
//=============================================================================
void CSceneX::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	m_VtxMin = VtxMin;
}