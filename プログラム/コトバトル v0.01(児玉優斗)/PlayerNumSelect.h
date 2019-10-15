//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : Mikiya Meguro
//
//=============================================================================
#ifndef _PLAYERSELECT_H_
#define _PLAYERSELECT_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER_SELECTMENU		(4)	//ランキングの数
#define MAX_CAUTIONMENU				(2)	//ランキングの数

//*********************************************************************
//ゲームクラスの定義
//*********************************************************************
class CPlayerSelect : public CScene //派生クラス
{
public:
	typedef enum
	{
		SELECTPLAYER_NONE = 0,
		SELECTPLAYER_1P,			//続行状態
		SELECTPLAYER_2P,			//リトライ状態
		SELECTPLAYER_3P,			//終了
		SELECTPLAYER_4P,			//終了
		SELECTPLAYER_MAX			//状態の総数
	}SELECTPLAYER;				//列挙型

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//選ばれていない状態
		SELECTTYPE_SELECT,		//選ばれている	状態
		SELECTTYPE_MAX			//状態の総数
	}SELECT;

	typedef struct
	{
		SELECT		select;		//セレクト
		D3DXVECTOR3 pos;		//位置
		D3DXCOLOR	col;		//カラー
	}SELECTMENU;

	CPlayerSelect(int nPriority = 7);
	~CPlayerSelect();
	static CPlayerSelect *Create(D3DXVECTOR3 pos, float fLength);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static SELECTPLAYER *GetModeSelectMode(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static bool GetModeSelectBool(void);
	static void SetModeSelectBool(bool ModeSelectBool);
	void Caution2DUninit(void);
	//メンバ変数
private:
	D3DXVECTOR3					m_InitPos;
	float						m_fWidth, m_fHeight;	// 幅高さ
	D3DXVECTOR3					m_TexMove;


	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PLAYER_SELECTMENU];	// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;							// 頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTextureBG;						// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;						// 頂点バッファへのポインタ
	CScene2D					*m_apPolygonBG;						// メニューのポリゴン

	SELECTMENU					m_aModeSelectMenu[MAX_PLAYER_SELECTMENU];	// ポーズメニュー
	D3DXVECTOR3					m_Pos[MAX_PLAYER_SELECTMENU];				// 位置
	static SELECTPLAYER			m_SelectMode;								// 選択してるモード
	int							m_nSelect;									// 選択している番号
	CScene2D					*m_apPolygon[MAX_PLAYER_SELECTMENU];		// メニューのポリゴン
	static	bool				m_bModeSelect;								// ポーズの状態
	bool						m_bCaution;									// 決定の警告
	bool						m_bCreate2D;								// 2Dを作ったかどうか

	CScene2D					*m_pCaution2D;								// 警告のポリゴン
	CScene2D					*m_pSelect2D[MAX_CAUTIONMENU];							// メニューのポリゴン
	int							m_nSelectCaution;							// 選択している番号
	SELECTMENU					m_SelectCaution[MAX_CAUTIONMENU];							// メニュー
};

#endif