//=============================================================================
//
// プレイヤーの体パーツ処理 [CharaParts.h]
// Author : Kodama Yuto
//
//	クラスの概要
//
//=============================================================================
#ifndef _CHARA_PARTS_H_
#define _CHARA_PARTS_H_

#include "main.h"
#include "sceneX.h"
//=============================================================================
//	クラス定義
//=============================================================================
class CCharaParts
{
public:
	CCharaParts();
	~CCharaParts();

	void Set(LPCSTR ModelFile,D3DXVECTOR3 pos, D3DXVECTOR3 rot,D3DXMATRIX* pParent);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetPosition(D3DXVECTOR3 pos) { m_Pos = pos; };
	D3DXVECTOR3 GetPosition(void) { return m_Pos; };

	void SetRotation(D3DXVECTOR3 rot) { m_Rot = rot; };
	D3DXVECTOR3 GetRotation(void) { return m_Rot; };

	void SetParent(D3DXMATRIX* pParent) { m_pParent = pParent;};
	D3DXMATRIX* GetMatrix(void) { return &m_mtxWorld; };

	D3DXVECTOR3 GetWorldPosition(void) { return m_WorldPosition; };

	void SetDrawFlag(bool bFlag) { m_bDrawFlag = bFlag; };
	bool GetDrawFlag(void) { return m_bDrawFlag; };
private:
	LPDIRECT3DTEXTURE9     m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH				m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;			// マテリアル情報へのポインタ
	DWORD					m_nNumMat;			// マテリアル情報の数
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス

	D3DXVECTOR3 m_Pos;		//位置(親から見た相対位置)
	D3DXVECTOR3 m_Rot;		//角度(親から見た相対角度)
	D3DXMATRIX* m_pParent;	//親マトリックス

	D3DXVECTOR3 m_WorldPosition;	//ワールド座標での位置(m_mtxWorldから取り出す)
	bool m_bDrawFlag;				//描画するかのフラグ
};
#endif // !_CHARA_PARTS_H_
