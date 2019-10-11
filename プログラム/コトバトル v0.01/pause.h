//=============================================================================
//
// ポーズ画面クラス処理 [pause.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//
//
//
#define PAUSE_POLYGON_NUM (4)
#define PAUSE_COL_A (0.3f)		//画面の色.a
#define SELECT_NUM (2)
//
//
//
class CPause
{
public:
	CPause();
	~CPause();

	HRESULT Init(void);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);


private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	LPDIRECT3DTEXTURE9		m_apTexture[PAUSE_POLYGON_NUM];

	D3DXCOLOR				m_SelectColor;
	int						m_nSelectMenu;

};
#endif // !_PAUSE_H_
