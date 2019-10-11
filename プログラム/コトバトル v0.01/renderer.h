//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//=============================================================================
//	レンダリングクラス
//=============================================================================
class CRenderer
{
public:

	CRenderer();
	~CRenderer();

	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	LPDIRECT3DDEVICE9 GetDevice(void) /*{ return m_pD3DDevice; }*/;

private:
	LPDIRECT3D9			m_pD3D = NULL;			// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9	m_pD3DDevice;			// Deviceオブジェクト(描画に必要)
};
#endif
