//=============================================================================
//
// 軌跡クラス [LineOrbit.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _LINE_ORBIT_H_
#define _LINE_ORBIT_H_

#include "scene.h"

//=============================================================================
// クラスの定義
//=============================================================================

//--------------------------------------------------------------
//軌跡クラス(CLineOrbit)
//--------------------------------------------------------------
class CLineOrbit : public CScene
{
public:
	CLineOrbit();
	CLineOrbit(int pri = 1, OBJTYPE type = OBJTYPE_ORBIT);

	~CLineOrbit();

	static CLineOrbit* Create(void);

	void Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fScale, D3DXMATRIX* parent, LPCSTR	Tag,
		D3DXCOLOR col,unsigned int nMeshNum, unsigned int nPointCreateTime);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetParent(D3DXMATRIX* parent) { m_Parent = parent; };
private:
	LPDIRECT3DTEXTURE9		m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;									// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;									// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;

	D3DXVECTOR3 m_pos;					//座標
	D3DXVECTOR3 m_offset;
	D3DXVECTOR3 m_rot;					//角度
	float m_fScale;				//大きさ(マトリックスには掛けず、軌跡のサイズ算出に使う)
	D3DXMATRIX* m_Parent;				//親

	D3DXCOLOR m_color;					//色

	int m_nVtxNum;
	int m_nIdxNum;

	int m_nPolygonNum;

	unsigned int m_nMeshNum;			//軌跡を形成する点の上限数
	unsigned int m_nPointCreateTime;	//新しく点を生成するまでの時間

	D3DXVECTOR3* m_apMesh;	//
};

#endif // !_LINE_ORBIT_H_
