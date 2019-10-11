//=============================================================================
//
// オブジェクト3D処理 [scene3D.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "scene.h"

//==================================================================
//	クラスの定義
//==================================================================
//オブジェクト3Dクラス
class CScene3D : public CScene
{
public:

	CScene3D();
	CScene3D(CScene::PRIORITY pri);

	~CScene3D();
	void Set(D3DXVECTOR3 pos,LPCSTR TexTag,
		D3DXVECTOR3 Size = D3DXVECTOR3(100.0f,0.0f,100.0f),
		D3DXVECTOR3 rot = D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),
		D3DXVECTOR2 UVrectMin = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 UVrectMax = D3DXVECTOR2(1.0f, 1.0f));

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetColor(D3DXCOLOR col);
	void SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect);

	void        SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };

	void        SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void) { return m_rot; };

	D3DXMATRIX GetMatrix(void) { return m_mtxWorld; };
	void		BindTexture(LPCSTR TexTag);

private:
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;						// ポリゴンの位置
	D3DXVECTOR3				m_rot;						// 角度
	D3DXCOLOR				m_Col;						// 色
	D3DXMATRIX				m_mtxWorld;					// ポリゴンのマトリックス
	D3DXVECTOR3				m_Size;						// 大きさ

	D3DXVECTOR2				m_UVRectMin;				// ポリゴンの左上のUV位置
	D3DXVECTOR2				m_UVRectMax;				// ポリゴンの右下のUV位置
};


#endif // !_SCENE2D_H_

