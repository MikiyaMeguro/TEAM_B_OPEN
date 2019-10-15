//=============================================================================
//
// 3Dポリゴン処理 [scene3D.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GROUND_TEXTURE_NAME			"data\\TEXTURE\\field.jpg"	// 地面のテクスチャ名
#define GROUND_SIZE					(130.0f)							// 地面の大きさ
#define NUM_VTX						(4)								// 頂点の数
//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = 3, OBJTYPE objType = OBJTYPE_SCENE3D);											// コンストラクタ
	~CScene3D();										// デストラクタ

	HRESULT Init(void) { return S_OK; };
	HRESULT Init(D3DXVECTOR3 pos);				// 3Dオブジェクト初期化処理
	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	D3DXVECTOR3 GetNor(int nIdx);				// 法線を取得
	void SetNor(D3DXVECTOR3 nor);				// 法線を設定

	float GetHeight(D3DXVECTOR3 pos);			// 高さの取得

	static CScene3D *Create(D3DXVECTOR3 pos, LPCSTR Tag);			// オブジェクトの生成
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);
	void BindTexture(LPCSTR TexTag);
	void SetSize(float fHeight,float fWidth);
	void SetRot(D3DXVECTOR3 rot);
	void SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V);
	void SetColor(D3DXCOLOR col);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3				m_Nor;					// 法線
	D3DXVECTOR3				m_aVec[NUM_VTX];					// ベクトル
	D3DXVECTOR3				m_pos;						// ポリゴンの位置
	D3DXVECTOR3				m_aPos[NUM_VTX];					// 頂点の位置
	D3DXVECTOR3				m_rot;						// 上方向ベクトル
	D3DXCOLOR               m_col;
	float					m_fSize;					// 大きさ
	float					m_fHeight;
	float					m_fWidth;
};

#endif