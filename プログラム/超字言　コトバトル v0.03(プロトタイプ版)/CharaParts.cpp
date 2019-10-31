//=============================================================================
//
// プレイヤーの体パーツ処理 [CharaParts.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "CharaParts.h"
#include "manager.h"

//=============================================================================
//	コンストラクタ&デストラクタ
//=============================================================================
CCharaParts::CCharaParts(){
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;
}
CCharaParts::~CCharaParts()
{

}

//=============================================================================
//	設定処理
//=============================================================================
void CCharaParts::Set(LPCSTR ModelFile, D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXMATRIX* pParent)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//変数設定
	m_pParent = pParent;
	m_Pos = pos;
	m_Rot = rot;

	// Xファイルの読み込み
	D3DXLoadMeshFromX(ModelFile,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	//テクスチャクラスからテクスチャをもらう
	m_pTexture = CTexture::GetTexture("KUMA_UV");
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CCharaParts::Init(void)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
	m_nNumMat = 0;

	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_WorldPosition = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_bDrawFlag = true;
	return S_OK;
}
//=============================================================================
//	終了処理
//=============================================================================
void CCharaParts::Uninit(void)
{
	// メッシュの解放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	//マテリアルの解放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
//	更新処理
//=============================================================================
void CCharaParts::Update(void)
{

}

//=============================================================================
//	描画処理
//=============================================================================
void CCharaParts::Draw(void)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;		//現在のマテリアル保存用
	D3DXMATERIAL *pMat;			//マテリアルデータのポインタ

								// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_Rot.y,
		m_Rot.x,
		m_Rot.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_Pos.x,
		m_Pos.y,
		m_Pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	if (m_pParent != NULL)
	{
		//親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			m_pParent);
	}

	//ワールドマトリックスから座標を取り出して保管する
	m_WorldPosition = D3DXVECTOR3(m_mtxWorld._41, m_mtxWorld._42, m_mtxWorld._43);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bDrawFlag == true)
	{

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			/*テクスチャの設定*/
			//pDevice->SetTexture(0, m_pTexture[nCntMat]);//テクスチャの設定(使わなければNULLを入れる)
			pDevice->SetTexture(0, m_pTexture);//テクスチャの設定(使わなければNULLを入れる)

			// モデル(パーツ)の描画
			m_pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);

	}
}