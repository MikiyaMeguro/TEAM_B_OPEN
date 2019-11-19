//=============================================================================
//
// 球メッシュクラス [meshSphere.h]
// Author : Kodama Yuto
//
//	注意　爆発用なので単体では使わないこと！！
//
//=============================================================================
#ifndef _MESH_SPHERE_H_
#define _MESH_SPHERE_H_

#include "scene.h"

//=============================================================================
// クラスの定義
//=============================================================================
class CMeshSphere : public CScene
{
public:
	CMeshSphere();
	CMeshSphere(int pri = 1, OBJTYPE type = OBJTYPE_SCENE3D);
	~CMeshSphere();


	static CMeshSphere* Create(void);

	void Set(D3DXVECTOR3 pos, LPCSTR Tag, int nMeshWidth, int nMeshHeight, D3DXVECTOR3 Size,
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f));

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_pos; };
	D3DXVECTOR3& GetScale(void) { return m_Size; };
private:
	void CreateVertex(LPDIRECT3DDEVICE9 pDev);
	void CreateIndex(LPDIRECT3DDEVICE9 pDev);

	void UpdateNormal(void);

	LPDIRECT3DTEXTURE9		m_pTexture;							// テクスチャへのポインタ
	LPDIRECT3DINDEXBUFFER9	m_pIdxBuff;							// インデックスバッファへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;							// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;							// ワールドマトリックス
	D3DXVECTOR3				m_pos;								// ポリゴンの位置
	D3DXVECTOR3				m_rot;								// ポリゴンの向き

	D3DXVECTOR3*			m_VecNor;								// 法線(頂点数分自動生成)

	int						m_nVtxNum;							// 頂点数
	int						m_nIdxNum;							// インデックス数
	int						m_nPolygonNum;						// ポリゴン数

	int						m_nMeshWidth;						// メッシュの分割数(X軸)
	int						m_nMeshHeight;						// メッシュの分割数(Y軸)
	D3DXVECTOR3				m_Size;								// サイズ
};

#endif // !_MESH_SPHERE_H_
