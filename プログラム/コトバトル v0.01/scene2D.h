//=============================================================================
//
// オブジェクト2D処理 [scene2D.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "scene.h"

//==================================================================
//	クラスの定義
//==================================================================
//オブジェクト2Dクラス
class CScene2D : public CScene
{
public:

	CScene2D();
	CScene2D(CScene::PRIORITY pri);

	~CScene2D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(D3DXVECTOR3 pos, LPCSTR TexTag,
		bool bRoll = false,float fRot = 0.0f,
		D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2 Size = D3DXVECTOR2(100.0f,100.0f),
		D3DXVECTOR2 UVrectMin = D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2 UVrectMax = D3DXVECTOR2(1.0f, 1.0f));

	void SetColor(D3DXCOLOR col);
	void SetUV(D3DXVECTOR2 MinRect, D3DXVECTOR2 MaxRect);

	void        SetPosition(D3DXVECTOR3 pos);
	void        SetPosition(D3DXVECTOR3 pos, D3DXVECTOR2 Size);
	void        SetPosition(D3DXVECTOR3 pos, D3DXVECTOR3 MinOffset, D3DXVECTOR3 MaxOffset);

	void		SetRotation(float fRot);

	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXVECTOR2 GetSize(void) { return m_Size; };
	float GetRotation(void) { return m_fRot; };
	void		BindTexture(LPCSTR TexTag);

	//	---<<追加>>---
	void SetScroll(float fSpeed, int nScrollType);	//	スクロール(速度 , 縦or横)
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★


private:
	void UpdateVtx(void);

	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;						// ポリゴンの位置
	D3DXCOLOR				m_Col;						// 色
	D3DXVECTOR2				m_Size;						// サイズ変更用

	D3DXVECTOR2				m_UVRectMin;				//ポリゴンの左上のUV位置
	D3DXVECTOR2				m_UVRectMax;				//ポリゴンの右下のUV位置

	bool m_bFreezeRotate;	//回転するオブジェクトかどうかの判定用
	float m_fRot;			//角度


	//	---<<追加>>---
	float m_fScrollCnt;
	//	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★	★


};


#endif // !_SCENE2D_H_

