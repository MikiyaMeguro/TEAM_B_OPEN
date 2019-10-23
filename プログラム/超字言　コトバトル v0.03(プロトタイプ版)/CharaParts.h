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
class CCharaParts : public CScene
{
public:
	CCharaParts();
	CCharaParts(int nPriority = 1);
	~CCharaParts();

	static CCharaParts* Create(void);

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

private:
	LPDIRECT3DTEXTURE9*     m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	LPD3DXMESH				m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;			// マテリアル情報へのポインタ
	DWORD					m_nNumMat;			// マテリアル情報の数
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス

	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Rot;
	D3DXMATRIX* m_pParent;
};
#endif // !_CHARA_PARTS_H_
