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

	// マテリアル情報からテクスチャを引き出す
	D3DXMATERIAL* pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();
	D3DMATERIAL9* pMatBuff = new D3DMATERIAL9[m_nNumMat];
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (DWORD nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
	{// 頂点数の数だけ繰り返し
	 // マテリアル情報を読み込む
		pMatBuff[nCntMat] = pMat[nCntMat].MatD3D;

		// 環境光を初期化する
		pMatBuff[nCntMat].Ambient = pMatBuff[nCntMat].Diffuse;

		// テクスチャ情報を初期化
		m_pTexture[nCntMat] = NULL;

		// テクスチャの情報を読み込む
		if (pMat[nCntMat].pTextureFilename != NULL &&
			lstrlen(pMat[nCntMat].pTextureFilename) > 0)
		{// テクスチャのファイル名がある
			D3DXCreateTextureFromFile(pDevice,
				pMat[nCntMat].pTextureFilename,
				&m_pTexture[nCntMat]);
		}
	}
	delete[] pMatBuff;


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
	//テクスチャの開放
	for (DWORD nCntMat = 0; nCntMat < m_nNumMat; nCntMat++)
	{
		if (m_pTexture[nCntMat] != NULL)
		{
			m_pTexture[nCntMat]->Release();
			m_pTexture[nCntMat] = NULL;
		}
	}
	delete m_pTexture;

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

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		/*テクスチャの設定*/
		pDevice->SetTexture(0, m_pTexture[nCntMat]);//テクスチャの設定(使わなければNULLを入れる)

													// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);

}