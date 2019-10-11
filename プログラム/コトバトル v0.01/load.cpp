//=============================================================================
//
// テクスチャ処理 [texture.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "load.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH *CLoad::m_pMesh = NULL;			// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER *CLoad::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD *CLoad::m_nNumMat = 0;				// マテリアル情報の数

const char *CLoad::m_apModelFilename[] =
{// モデル
	"data\\MODEL\\car000.x",				//0
	"data\\MODEL\\car001.x",				//1
	"data\\MODEL\\box000.x",				//2
	"data\\MODEL\\SampleModel_Player.x",	//3
};

//=============================================================================
// コンストラクタ
//=============================================================================
CLoad::CLoad()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLoad::~CLoad()
{
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
HRESULT CLoad::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pMesh != NULL)
	{
		// メモリを解放する
		delete[] m_pMesh;
		m_pMesh = NULL;
	}

	if (m_pBuffMat != NULL)
	{
		// メモリを解放する
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// メモリを解放する
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	int nModelData = (sizeof m_apModelFilename);
	int nModelSize = (sizeof m_apModelFilename[0]);
	int nNumModel = nModelData / nModelSize;

	// 動的に確保
	m_pMesh = new LPD3DXMESH[nNumModel];
	m_pBuffMat = new LPD3DXBUFFER[nNumModel];
	m_nNumMat = new DWORD[nNumModel];

	for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
	{
		D3DXLoadMeshFromX(m_apModelFilename[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntModel],
			NULL,
			&m_nNumMat[nCntModel],
			&m_pMesh[nCntModel]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ解放処理
//=============================================================================
void CLoad::UnloadModel(void)
{
	if (m_pBuffMat != NULL)
	{
		// メモリを解放する
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// メモリを解放する
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		// メモリを解放する
		delete[] m_pMesh;
		m_pMesh = NULL;
	}
}

//=============================================================================
// メッシュ取得
//=============================================================================
LPD3DXMESH CLoad::GetMesh(int nIdx)
{
	return m_pMesh[nIdx];
}

//=============================================================================
// マテリアル情報取得
//=============================================================================
LPD3DXBUFFER CLoad::GetBuffMat(int nIdx)
{
	return m_pBuffMat[nIdx];
}

//=============================================================================
// マテリアル情報の数取得
//=============================================================================
DWORD CLoad::GetNumMat(int nIdx)
{
	return m_nNumMat[nIdx];
}