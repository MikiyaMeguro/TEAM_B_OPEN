//=============================================================================
//
// フェード処理 [fade.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"
#include "manager.h"
#include "scene2D.h"

//========================================
// クラスの定義
//========================================
//=====================
// フェードクラス
//=====================
class CFade
{
public:
	typedef enum
	{// フェードの状態
		FADE_NONE = 0,												// 何もしていない状態
		FADE_IN,													// フェードイン状態
		FADE_OUT,													// フェードアウト状態
		FADE_MAX
	} FADE;

	CFade();	// コンストラクタ
	~CFade();														// デストラクタ

	static CFade *Create();					// オブジェクトの生成

	HRESULT Init(D3DXVECTOR3 pos);		// フェード初期化処理
	void Uninit(void);												// フェード終了処理
	void Update(void);												// フェード更新処理
	void Draw(void);												// フェード描画処理
	static FADE GetFade(void);										// フェードの取得
	static void SetFade(CManager::MODE modeNext, FADE fade);		// フェードの取得

private:
	//LPDIRECT3DTEXTURE9		m_pTexture;								// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;								// 頂点バッファへのポインタ
	static FADE m_fade;												// フェード状態
	static CManager::MODE m_modeNext;
	static D3DXCOLOR m_colorFade;
};

#endif