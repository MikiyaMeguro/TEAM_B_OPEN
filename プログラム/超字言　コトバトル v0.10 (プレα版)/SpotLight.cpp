//=============================================================================
//
// スポットライト [Spotlight.cpp]
// Author : 後閑　茜
//
//=============================================================================
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "InputKeyboard.h"
#include "SpotLight.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================

//=============================================================================
// スポットライトクラスのコンストラクタ
//=============================================================================
CSpotLight::CSpotLight()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CSpotLight::~CSpotLight()
{
}
//=============================================================================
// 生成処理
//=============================================================================
CSpotLight *CSpotLight::Create(int nNum, D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch)
{
	CSpotLight *pSpot = NULL;
	if (pSpot == NULL)
	{
		pSpot = new CSpotLight;
		if (pSpot != NULL)
		{
			pSpot->SettingLight(nNum,pos, Dir, Diffuse, Ambient, Specular, fAttenuation0, fAttenuation1, fAttenuation2, fRange, fFalloff, fTheta, fPhi, bSwitch);
		}
	}
	return pSpot;
}
//=============================================================================
// スポットライトの初期化処理
//=============================================================================
void CSpotLight::Init(void)
{

}

//=============================================================================
// スポットライトの終了処理
//=============================================================================
void CSpotLight::Uninit(void)
{
	CLight::Uninit();
}

//=============================================================================
// スポットライトの更新処理
//=============================================================================
void CSpotLight::Update(void)
{
	CLight::Update();
}
//=============================================================================
// スポットライトの生成
//=============================================================================
void CSpotLight::SettingLight(int nNum, D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch)
{
#if 1
	D3DLIGHT9 pLight;		//ライトのポインタ

	// デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL) { pDevice = pRenderer->GetDevice(); }

	 // スポットライトをクリアする
	ZeroMemory(&pLight, sizeof(D3DLIGHT9));

	// スポットライトの種類を設定
	pLight.Type = D3DLIGHT_SPOT;

	// 光源の位置を設定
	pLight.Position = pos;

	// スポットライトの方向の設定
	D3DXVECTOR3 vecDir;
	vecDir = Dir;

	D3DXVec3Normalize(&vecDir, &vecDir);				//正規化にする
	pLight.Direction = vecDir;

	//環境光(光が当たらない部分へ間接的に当たる光の強さ)??
	pLight.Ambient = Ambient;

	// スペキュラー色(輝く効果を出す反射)鏡面光/反射光
	pLight.Specular = Specular;

	// 光源の有効距離を設定
	pLight.Range = fRange;


	//スポットライトの強度 (1と2を0.0fにすることで減衰しない光になる)
	pLight.Attenuation0 = fAttenuation0;
	pLight.Attenuation1 = fAttenuation1;
	pLight.Attenuation2 = fAttenuation2;


	// スポットライトが放射するディフューズ色を設定(拡散光)
	pLight.Diffuse = Diffuse;


	// よくわからんけど開発者の多くは1.0fを設定してるらしい
	pLight.Falloff = fFalloff;

	pLight.Theta = fTheta;	//内部コーン（よく光が当たる場所）
	pLight.Phi = fPhi;		//外部コーン（若干光が当たる場所）

	SetLight(nNum,pLight);
	pDevice->SetLight(nNum, &pLight);
	pDevice->LightEnable(nNum, bSwitch);
#endif // 0
}
//=============================================================================
// 光の設定
//=============================================================================
void CSpotLight::SetLightEnable(int nNum, bool bEnable)
{
	// デバイスの取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = NULL;
	if (pRenderer != NULL) { pDevice = pRenderer->GetDevice(); }
	m_bEnable = bEnable;

	pDevice->LightEnable(nNum, m_bEnable);
}