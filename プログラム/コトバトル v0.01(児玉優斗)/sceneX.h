//=============================================================================
//
// 3Dモデル処理 [sceneX.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

#include "main.h"
#include "scene.h"
#include "load.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = SCENEX_PRIORITY, OBJTYPE objType = OBJTYPE_SCENEX);					// コンストラクタ
	~CSceneX();									// デストラクタ

	HRESULT Init(void) { return S_OK; };
	HRESULT Init(D3DXVECTOR3 pos);				// 3Dオブジェクト初期化処理

	void Uninit(void);							// 3Dオブジェクト終了処理
	void Update(void);							// 3Dオブジェクト更新処理
	void Draw(void);							// 3Dオブジェクト描画処理

	static CSceneX *Create(D3DXVECTOR3 pos, D3DXVECTOR3 Rot,D3DXVECTOR3 Scale, CLoad::MODEL model);	// オブジェクトの生成

	D3DXVECTOR3 GetPosition(void);						// 位置の取得
	void SetPosition(D3DXVECTOR3 pos);					// 位置の設定

	D3DXVECTOR3 GetRot(void);						// 向きの取得
	void SetRot(D3DXVECTOR3 rot);					// 向きの設定

	D3DXVECTOR3 GetVtxMax(void);						// 最大値の取得
	void SetVtxMax(D3DXVECTOR3 VtxMax);					// 最大値の設定

	D3DXVECTOR3 GetVtxMin(void);						// 最小値の取得
	void SetVtxMin(D3DXVECTOR3 VtxMin);					// 最小値の設定

	void SetVtx(void);																// 頂点座標の設定
	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// 当たり判定

	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// モデルを割り当てる
	void BindTex(LPDIRECT3DTEXTURE9	*m_pTexture);	// テクスチャマテリアルを割り当てる

private:
	LPDIRECT3DTEXTURE9		*m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH				m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;			// マテリアル情報へのポインタ
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	DWORD					m_nNumMat;			// マテリアル情報の数
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// モデルの最小値、最大値
	D3DXVECTOR3				m_pos;				// ポリゴンの位置
	D3DXVECTOR3				m_rot;				// 上方向ベクトル
	D3DXVECTOR3				m_Scale;			// スケール
};

#endif