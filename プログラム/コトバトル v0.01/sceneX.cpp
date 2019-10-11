//=============================================================================
//
// xファイルオブジェクト処理 [sceneX.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "sceneX.h"
#include "Manager.h"

//==================================================================
// 静的メンバ変数宣言
//==================================================================
LPCSTR CSceneX::m_ModelNameInfo[CSceneX::MODEL_MAX] =
{
	{ "data/MODEL/airplane000.x" },
	{ "data/MODEL/car002.x" },
	{ "data/MODEL/KATANA.x" },
};

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CSceneX::CSceneX(CScene::PRIORITY pri = CScene::PRIORITY_3) : CScene(pri, OBJTYPE_XFILE)
{
	m_pBuffMat = NULL;
	m_pMesh = NULL;
	m_pTexture = NULL;
}
CSceneX::~CSceneX()
{

}

//==================================================================
// 初期化処理
//==================================================================
void CSceneX::Set(D3DXVECTOR3 pos, CSceneX::MODEL_PROPERTY prop,D3DXVECTOR3 rot)
{
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// 位置・向きの初期設定
	m_pos = pos;
	m_rot = rot;
	m_modelProperty = prop;

	if (m_pBuffMat == NULL)
	{
		// Xファイルの読み込み
		D3DXLoadMeshFromX(m_ModelNameInfo[prop],
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
		pMatBuff = NULL;
	}

	//移動量・回転量の初期化
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//頂点の取得
	GetVertex();

	m_bTargetFlag = false;

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CSceneX::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CSceneX::Uninit(void)
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
	delete[] m_pTexture;
	//マテリアルの解放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	Release();
}

//==================================================================
// 更新処理
//==================================================================
void CSceneX::Update(void)
{

}

//==================================================================
// 描画処理
//==================================================================
void CSceneX::Draw(void)
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
//==================================================================
// 頂点座標取得処理
//==================================================================
void CSceneX::GetVertex(void)
{
	//変数宣言
	int nNumVtx;	//頂点数
	DWORD sizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;	//頂点バッファへのポインタ

	m_vtxMin = D3DXVECTOR3(1000000.0f, 1000000.0f, 1000000.0f);
	m_vtxMax = D3DXVECTOR3(-1000000.0f, -1000000.0f, -1000000.0f);

	//頂点数の取得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());


	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		//頂点を比較してモデルの最小・最大を抜き出す
		//x
		if (m_vtxMin.x > vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMax.x < vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}

		//y
		if (m_vtxMin.y > vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (m_vtxMax.y < vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}

		//z
		if (m_vtxMin.z > vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}
		if (m_vtxMax.z < vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}

		pVtxBuff += sizeFVF;		//サイズ分ポインタを進める
	}
	//アンロック
	m_pMesh->UnlockVertexBuffer();

}

//==================================================================
// 各種設定処理
//==================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{//座標のみ設定
	m_pos = pos;
}

void CSceneX::SetRotation(D3DXVECTOR3 rot)
{//角度のみ設定
	m_rot = rot;
}

