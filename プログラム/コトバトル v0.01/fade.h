//=============================================================================
//
// 画面遷移クラス処理 [fade.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_
#include "main.h"
#include "scene2D.h"
#include "Manager.h"

//=============================================================================
//
//=============================================================================
class CFade
{
public:
	typedef enum
	{
		FADE_NONE = 0,		// 何もしていない状態
		FADE_IN,			// フェードイン状態
		FADE_OUT,			// フェードアウト状態
		FADE_MAX
	} FADE;
	typedef enum
	{
		COLOR_BLACK = 0,
		COLOR_WHITE,
		COLOR_MAX
	}FADECOLOR;
	CFade();
	~CFade();

	static CFade* Create(CManager::MODE modeNext);
	HRESULT Init(CManager::MODE modeNext);
	void    Uninit(void);
	void    Update(void);
	void    Draw(void);

	void SetFade(CManager::MODE modeNext, FADECOLOR fCol);
	FADE* GetFade(void) { return &m_Fade; };
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	LPDIRECT3DTEXTURE9		m_pTexture;				// テクスチャへのポインタ
	FADE					m_Fade;					// フェードの状態
	CManager::MODE			m_modeNext;				// 次のモード
	D3DXCOLOR				m_colorFade;			// フェード色
};
#endif //!_FADE_H_