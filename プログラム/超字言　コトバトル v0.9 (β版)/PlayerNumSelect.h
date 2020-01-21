//=============================================================================
//
// プレイヤー人数選択画面処理 [PlayerNumSelect.h]
// Author : Mikiya Meguro/Akane Gokan
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
#define MAX_PLAYER_SELECTMENU		(4)	//プレイヤー人数の最大値
#define MAX_CAUTIONMENU				(2)	//警告の選択しの最大数
#define MAX_PLAYERNUMSEL_BG			(7)	//BGの最大ポリゴン（演出用）

//*********************************************************************
//ゲームクラスの定義
//*********************************************************************
class CPlayerSelect : public CScene //派生クラス
{
public:
	/* プレイヤー人数の種類 */
	typedef enum
	{
		SELECTPLAYER_NONE = 0,
		SELECTPLAYER_1P,			//プレイ人数：1人
		SELECTPLAYER_2P,			//プレイ人数：2人
		SELECTPLAYER_3P,			//プレイ人数：3人
		SELECTPLAYER_4P,			//プレイ人数：4人
		SELECTPLAYER_MAX			//状態の総数
	}SELECTPLAYER;

	/* 選択肢の状態 */
	typedef enum
	{
		SELECTTYPE_NONE = 0,	//選ばれていない状態
		SELECTTYPE_SELECT,		//選ばれている	状態
		SELECTTYPE_MAX			//状態の総数
	}SELECT;

	/* メニューの列挙型 */
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

	static SELECTPLAYER *GetModeSelectMode(void) { return &m_SelectMode; }						//選択したモードの取得
	static HRESULT Load(void) { return S_OK; }													//読み込み
	static void UnLoad(void);																	//破棄
	static bool GetModeSelectBool(void) { return m_bModeSelect; }								//モードが選ばれたかの取得
	static void SetModeSelectBool(bool ModeSelectBool) { m_bModeSelect = ModeSelectBool; }		//モードが選ばれたかの設定
	void Caution2DUninit(void);																	//警告の終了処理

private:

	/* 背景の種類 */
	typedef enum
	{
		PLNUMSELECTBGTYPE_BG = 0,
		PLNUMSELECTBGTYPE_BAND_L,
		PLNUMSELECTBGTYPE_BAND_R,
		PLNUMSELECTBGTYPE_FRAME,
		PLNUMSELECTBGTYPE_MENU

	}PLNUMSELECTBGTYPE;

	/* アニメーションの割り方種類 */
	typedef enum
	{
		ANIMTYPE_NONE = 0,
		ANIMTYPE_X,
		ANIMTYPE_Y,
		ANIMTYPE_MAX

	}ANIMTYPE;

	HRESULT InitPointer(void);													//各種ポインタの初期化
	void InitProductionPos(void);												//演出ポリゴンの初期設定
	void ScrollMenu(PLNUMSELECTBGTYPE type, float fScroolSpeed);				//スクロール
	void PlayerSelectMove(PLNUMSELECTBGTYPE type, int MenuNum);					//ポリゴン移動演出
	void SetPlayerSelNumMenuPos(int MenuNum);									//選択肢の基本位置
	void SetSelectAnimation(PLNUMSELECTBGTYPE type, ANIMTYPE AnimType,
		int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed);	//アニメーション

	D3DXVECTOR3					m_InitPos;										//人数選択の初期位置
	D3DXVECTOR3					m_ChoicePos[MAX_CAUTIONMENU];					//警告の初期位置
	float						m_fWidth, m_fHeight;							// 幅高さ
	D3DXVECTOR3					m_TexMove;										//テクスチャの移動量


	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_PLAYER_SELECTMENU];				// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;										// 頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTextureBG;									// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;									// 頂点バッファへのポインタ
	CScene2D					*m_apPolygonBG[MAX_PLAYERNUMSEL_BG];			// メニューのポリゴン

	SELECTMENU					m_aModeSelectMenu[MAX_PLAYER_SELECTMENU];		// ポーズメニュー
	D3DXVECTOR3					m_Pos[MAX_PLAYER_SELECTMENU];					// 位置
	static SELECTPLAYER			m_SelectMode;									// 選択してるモード
	int							m_nSelect;										// 選択している番号
	CScene2D					*m_apPolygon[MAX_PLAYER_SELECTMENU];			// メニューのポリゴン
	static	bool				m_bModeSelect;									// ポーズの状態
	bool						m_bCaution;										// 決定の警告
	bool						m_bCreate2D;									// 2Dを作ったかどうか

	CScene2D					*m_pCaution2D;									// 警告のポリゴン
	CScene2D					*m_pCaution2DBG;								// 警告のポリゴンBG
	CScene2D					*m_pSelect2D[MAX_CAUTIONMENU];					// メニューのポリゴン
	int							m_nSelectCaution;								// 選択している番号
	SELECTMENU					m_SelectCaution[MAX_CAUTIONMENU];				// メニュー

	/* 演出面変数 */
	int m_nCntScrool;		//スクロールのカウンター
	int m_nCntAnim;			//アニメーションのカウンター
	int m_nPatturnAnim;		//アニメーションのパターン
	float m_fChangeMode;	//選択中モードアイコンの移動制御カウンター
	float m_fMoveMode;		//選択中モードアイコンの移動量を計る

	int m_nCounter;			//カウント


#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};

#endif