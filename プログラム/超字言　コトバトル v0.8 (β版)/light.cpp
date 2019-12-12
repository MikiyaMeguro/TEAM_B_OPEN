//=============================================================================
//
// ライト処理 [light.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyboard.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
D3DLIGHT9 CLight::m_light[MAX_LIGHT] = {};
//=============================================================================
// ライトクラスのコンストラクタ
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ライトの初期化処理
//=============================================================================
void CLight::Init(void)
{
	D3DXVECTOR3 vecDir;

	// デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

#if(1)
	// ディレクションライト
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));
	}

	// ライトの種類を設定
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;
	m_light[3].Type = D3DLIGHT_DIRECTIONAL;
	m_light[4].Type = D3DLIGHT_DIRECTIONAL;

	// ライトの拡散光を設定
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);
	m_light[3].Diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
	m_light[4].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);

	// ライトの方向の設定
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[2].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.0f, -0.9f, 1.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[3].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.0f, -0.1f, -1.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// 正規化する
	m_light[4].Direction = vecDir;

	if (pDevice != NULL)
	{
		// ライトを設定する
		pDevice->SetLight(0, &m_light[0]);
		pDevice->SetLight(1, &m_light[1]);
		pDevice->SetLight(2, &m_light[2]);
		pDevice->SetLight(3, &m_light[3]);
		pDevice->SetLight(4, &m_light[4]);

		// ライトを有効にする
		pDevice->LightEnable(0, TRUE);
		pDevice->LightEnable(1, TRUE);
		pDevice->LightEnable(2, TRUE);
		pDevice->LightEnable(3, TRUE);
		pDevice->LightEnable(4, TRUE);
	}
#endif // 1

#if(0)
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{// ポイントライト
		// ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_POINT;

		// ライトが放射するディフューズ色を設定
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// スペキュラー色
		m_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//環境光(明るくなる)
		m_light[nCntLight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 光源の位置を設定
		m_light[nCntLight].Position = D3DXVECTOR3(100.0f, 50.0f, -100.0f);

		// ライトの方向の設定
		//vecDir = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//D3DXVec3Normalize(&vecDir, &vecDir);				//正規化にする
		//m_light[nCntLight].Direction = vecDir;

		// 光源の有効距離を設定
		m_light[nCntLight].Range = 300.0f;

		// よくわからんけど開発者の多くは1.0fを設定してるらしい
		m_light[nCntLight].Falloff = 1.0f;

		//ライトの強度
		m_light[nCntLight].Attenuation0 = 0.5f;
		m_light[nCntLight].Attenuation1 = 0.05f;
		m_light[nCntLight].Attenuation2 = 0.0f;

		m_light[nCntLight].Theta = D3DXToRadian(10.0f);	//内部コーン（よく光が当たる場所）
		m_light[nCntLight].Phi = D3DXToRadian(30.0f);		//外部コーン（若干光が当たる場所）

															// ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ライトを有効にする
		pDevice->LightEnable(nCntLight, TRUE);
	}
#endif

#if 0
	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{// スポットライト
	 // ライトをクリアする
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntLight].Type = D3DLIGHT_SPOT;

		// ライトが放射するディフューズ色を設定
		m_light[nCntLight].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// スペキュラー色(輝く効果を出す反射)??
		m_light[nCntLight].Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//環境光(光が当たらない部分へ間接的に当たる光の強さ)??
		m_light[nCntLight].Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 光源の位置を設定
		m_light[nCntLight].Position = D3DXVECTOR3(100.0f, 50.0f, -100.0f);

		// ライトの方向の設定
		vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);

		D3DXVec3Normalize(&vecDir, &vecDir);				//正規化にする
		m_light[nCntLight].Direction = vecDir;

		// 光源の有効距離を設定
		m_light[nCntLight].Range = 800.0f;

		// よくわからんけど開発者の多くは1.0fを設定してるらしい
		m_light[nCntLight].Falloff = 1.0f;

		//ライトの強度 (1と2を0.0fにすることで減衰しない光になる)
		m_light[nCntLight].Attenuation0 = 1.0f;
		m_light[nCntLight].Attenuation1 = 0.0f;
		m_light[nCntLight].Attenuation2 = 0.0f;

		m_light[nCntLight].Theta = D3DXToRadian(50.0f);	//内部コーン（よく光が当たる場所）
		m_light[nCntLight].Phi = D3DXToRadian(100.0f);		//外部コーン（若干光が当たる場所）

															// ライトを設定する
		pDevice->SetLight(nCntLight, &m_light[nCntLight]);

		// ライトを有効にする
		if (nCntLight == 0)
		{
			pDevice->LightEnable(0, TRUE);
		}
		else if (nCntLight == 1)
		{
			pDevice->LightEnable(1, FALSE);
		}
		else if (nCntLight == 2)
		{
			pDevice->LightEnable(2, FALSE);
		}
	}
#endif // 0


}

//=============================================================================
// ライトの終了処理
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ライトの更新処理
//=============================================================================
void CLight::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}


	if (pInputKeyboard->GetPress(DIK_NUMPAD1) == true)
	{
		m_light[0].Position.y -= 1.0f;
		m_light[1].Position.y -= 1.0f;
		m_light[2].Position.y -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_NUMPAD7) == true)
	{
		m_light[0].Position.y += 1.0f;
		m_light[1].Position.y += 1.0f;
		m_light[2].Position.y += 1.0f;
	}

	if (pInputKeyboard->GetPress(DIK_NUMPAD4) == true)
	{
		m_light[0].Position.x -= 1.0f;
		m_light[1].Position.x -= 1.0f;
		m_light[2].Position.x -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_NUMPAD6) == true)
	{
		m_light[0].Position.x += 1.0f;
		m_light[1].Position.x += 1.0f;
		m_light[2].Position.x += 1.0f;
	}

	if (pInputKeyboard->GetPress(DIK_NUMPAD2) == true)
	{
		m_light[0].Position.z -= 1.0f;
		m_light[1].Position.z -= 1.0f;
		m_light[2].Position.z -= 1.0f;
	}
	if (pInputKeyboard->GetPress(DIK_NUMPAD8) == true)
	{
		m_light[0].Position.z += 1.0f;
		m_light[1].Position.z += 1.0f;
		m_light[2].Position.z += 1.0f;
	}

	// ライトを設定する
	pDevice->SetLight(0, &m_light[0]);
	pDevice->SetLight(1, &m_light[1]);
	pDevice->SetLight(2, &m_light[2]);

}