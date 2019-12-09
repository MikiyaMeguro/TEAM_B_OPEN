//=============================================================================
//
// スポットライト処理 [SpotLignt.h]
// Author : 後閑　茜
//
//=============================================================================
#ifndef _SPOTLIGHT_H_
#define _SPOTLIGHT_H_

#include "main.h"
#include "light.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SPOTLIGHT_DEFFUSE (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//スポットライトが放射するディフューズ色
#define SPOTLIGHT_SPECULAR (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//鏡面色
#define SPOTLIGHT_AMBIENT (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	//環境光
#define SPOTLIGHT_DIRECTION (D3DXVECTOR3(0.0f,-1.0f, 0.0f))		//向き
#define SPOTLIGHT_FALLOFF (1.0f)								//フォールオフ状況

//========================================
// クラスの定義
//========================================
//=====================
// スポットライトクラス
//=====================
class CSpotLight : public CLight
{
public:
	CSpotLight();
	~CSpotLight();
	void Init(void);
	void Uninit(void);
	void Update(void);

	static CSpotLight *Create(int nNum, D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch = true);
	void SetLightEnable(int nNum, bool bEnable);
private:
	bool m_bEnable;
	/* 設定処理 */
	void SettingLight(int nNum,D3DXVECTOR3 pos, D3DXVECTOR3 Dir, D3DXCOLOR Diffuse, D3DXCOLOR Ambient, D3DXCOLOR Specular, float fAttenuation0, float fAttenuation1, float fAttenuation2, float fRange, float fFalloff, float fTheta, float fPhi, bool bSwitch);
};
#endif