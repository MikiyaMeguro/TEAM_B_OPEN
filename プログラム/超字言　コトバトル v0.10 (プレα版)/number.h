//=============================================================================
//
// 数字処理 [number.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "scene2D.h"

//=============================================================================
// クラス定義
//=============================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	HRESULT Init(D3DXVECTOR3 pos, int nType);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);
	void SetSize(D3DXVECTOR2 size, D3DXVECTOR2 pos);

	D3DXVECTOR2 GetSize(void) { return m_size; }
	D3DXVECTOR2 GetPos(void) { return m_pos; }
	D3DXCOLOR GetCol(void) { return m_col; }
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// 頂点バッファへのポインタ
	int							m_nType;				// テクスチャの番号
	D3DXVECTOR2					m_size;					// サイズ
	D3DXVECTOR2					m_pos;					// 位置
	D3DXCOLOR					m_col;					// 色
};

class CBillNumber
{
public:
	CBillNumber();
	~CBillNumber();

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNumber(int nNumber);
	void SetCol(D3DXCOLOR col);
	void SetSize(D3DXVECTOR3 size);
	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetSize(void) { return m_size; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXCOLOR GetCol(void) { return m_col; }

private:
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;				// 頂点バッファへのポインタ
	int							m_nType;				// テクスチャの番号
	D3DXVECTOR3					m_size;					// サイズ
	D3DXVECTOR3					m_pos;					// 位置
	D3DXCOLOR					m_col;					// 色
	D3DXMATRIX					m_mtrxWorld;			// ワールドマトリックス

};
#endif