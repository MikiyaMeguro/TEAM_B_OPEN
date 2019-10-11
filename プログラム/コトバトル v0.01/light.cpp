//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "light.h"
#include "Manager.h"
#include "renderer.h"

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CLight::CLight()
{
}
CLight::~CLight()
{

}


void CLight::Init(void)
{
	CRenderer* pRenderder = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderder->GetDevice();	// デバイスの取得


	m_VecDir[0] = D3DXVECTOR3(0.22f, -0.87f, 0.44f);
	m_VecDir[1] = D3DXVECTOR3(-0.18f, 0.88f, -0.44f);
	m_VecDir[2] = D3DXVECTOR3(0.89f, -0.11f, 0.44f);

	m_DifCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_DifCol[1] = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_DifCol[2] = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ライトをクリアする
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		//ライトの初期化
		ZeroMemory(&m_Light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_Light[nCntLight].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_Light[nCntLight].Diffuse = m_DifCol[nCntLight];
		// ライトの方向の設定
		D3DXVec3Normalize(&m_VecDir[nCntLight], &m_VecDir[nCntLight]);
		m_Light[nCntLight].Direction = m_VecDir[nCntLight];

		// ライトを設定する
		pDevice->SetLight(nCntLight, &m_Light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
}

void CLight::Uninit(void)
{

}

void CLight::Update(void)
{

}
