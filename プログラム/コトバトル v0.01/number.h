//=============================================================================
//
// 番号クラス処理 [number.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "main.h"

//==================================================================
// クラスの定義
//==================================================================
class CNumber
{
public:
	CNumber();
	~CNumber();

	void	Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect, int nNum,D3DXCOLOR Col);
	HRESULT Init(void);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetNumber(int nNum);
	D3DXVECTOR3 GetPosition(void) { return m_pos; };
	D3DXCOLOR GetColor(void) { return m_Col; };
	D3DXVECTOR2 GetRect(void) { return m_polygonRect; };
	int GetNumber(void) { return m_nNumber; };

private:
	LPDIRECT3DTEXTURE9				m_pTexture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuff;					// 頂点バッファへのポインタ
	D3DXVECTOR3						m_pos;						// ポリゴンの位置(左上)
	D3DXCOLOR						m_Col;						// 色
	D3DXVECTOR2						m_polygonRect;				// ポリゴンの大きさ
	int								m_nNumber;					// 番号
};
#endif // !_NUMBER_H_
