//=============================================================================
//
// ビルボードの処理 [billboard.h]
// Author :  Meguro Mikiya
//
//=============================================================================
#ifndef _BILLBOARD_H_
#define _BILLBOARD_H_

#include "main.h"
#include "scene.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CSceneBillBoard : public CScene //派生クラス
{
public:
	CSceneBillBoard();
	~CSceneBillBoard();
	HRESULT Init(void) { return S_OK; };
	HRESULT Init(D3DXVECTOR3 pos);

	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Setpos(D3DXVECTOR3 pos);
	void SetBillboard(D3DXVECTOR3 pos, float fHeight, float fWidth);
	static CSceneBillBoard *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag);
	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	//TEXTUREを割り当てる
	void BindTexture(LPCSTR TexTag);
	D3DXVECTOR3 GetPos(void);
	void SetCol(D3DXCOLOR col);
	LPDIRECT3DVERTEXBUFFER9 GetVtx(void);
	void SetTexture(int PatternAnim, int X, int Y, int nNum);
	void SetTexture(D3DXVECTOR2 minRect,D3DXVECTOR2 maxRect);

	void SetDrawFlag(bool bFlag) { m_bDrawFlag = bFlag; }
	bool GetDrawFlag(void) {return m_bDrawFlag; }
private:
	//メンバ変数
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;			//頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;			// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;						// ポリゴンの位置
	D3DXVECTOR3				m_move;						// 移動量
	float					m_fWidth, m_fHeight;		// 幅,高さ
	D3DXMATRIX				m_mtrxWorld;				// ワールドマトリックス
	bool					m_bDrawFlag;

};

#endif