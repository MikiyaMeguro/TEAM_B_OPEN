//=============================================================================
//
// シーン処理 [scene2D.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define PLAYER_NAME		"data/TEXTURE/player000.png"	// プレイヤーのテクスチャ名
#define BULLET_NAME		"data/TEXTURE/bullet000.png"	// 弾のテクスチャ名
#define MAX_TEX_TYPE	(2)								// テクスチャの種類

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CScene2D : public CScene
{
public:
	CScene2D(int nPriority = 3, OBJTYPE objType = OBJTYPE_SCENE2D);											// コンストラクタ
	~CScene2D();										// デストラクタ

	HRESULT Init(void) { return S_OK; };
	virtual HRESULT Init(D3DXVECTOR3 pos);				// 2Dオブジェクト初期化処理

	virtual void Uninit(void);							// 2Dオブジェクト終了処理
	virtual void Update(void);							// 2Dオブジェクト更新処理
	virtual void Draw(void);							// 2Dオブジェクト描画処理

	D3DXVECTOR3 GetPosition(void);						// 位置を取得
	void SetPosition(D3DXVECTOR3 pos);					// 位置を設定

	static CScene2D *Create(D3DXVECTOR3 pos, LPCSTR Tag, int nPriority = 3);				// オブジェクトの生成
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void BindTexture(LPCSTR TexTag);

	void SetPos(D3DXVECTOR3 pos, float fSpin, float fScale, D3DXCOLOR col);
	void SetRot(float fSpin);
	void SetWidthHeight(float fWidth, float fHeight);
	void SetRIghtLeft(float fRight, float fLeft);
	void SetCol(D3DXCOLOR col);
	void SetTex(D3DXVECTOR2 texmin, D3DXVECTOR2 texmax);
	LPDIRECT3DVERTEXBUFFER9 GetBuff(void) { return m_pVtxBuff; }
	void SetBuff(LPDIRECT3DVERTEXBUFFER9 pVtxBuff) { m_pVtxBuff = pVtxBuff; }
	void SetbDraw(bool bDraw) { m_bDraw = bDraw; };
	void SetAnimation(int m_PatternAnim, float fUV_U, float fUV_V);

private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// 頂点バッファへのポインタ

	D3DXVECTOR3				m_Pos;						// ポリゴンの位置
	float					m_fSpin;				// 回転
	float					m_fWidth, m_fHeight;	// 幅高さ
	float					m_fRight, m_fLeft;		// 左右の長さ
	float					m_fLength;				// 大きさ
	float					m_fScale;				// 大きさ変更
	D3DXCOLOR				m_Col;
	bool					m_bDraw;

};

#endif