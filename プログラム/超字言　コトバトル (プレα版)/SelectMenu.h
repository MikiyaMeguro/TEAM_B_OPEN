//=============================================================================
//
// セレクトメニュー処理 [SelectMenu.h]
// Author : Mikiya Meguro/Akane Gokan
//
//=============================================================================
#ifndef _SELECTMENU_H_
#define _SELECTMENU_H_

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
#define MAX_SELECTMENU			(4)							//最大ポリゴン数数
#define MAX_SELETMODE_BG		(10)						//BGの最大ポリゴン
#define BAND_SIZE				(0.5f)						//帯のサイズ
//*********************************************************************
//ゲームクラスの定義
//*********************************************************************
class CSelectMenu : public CScene //派生クラス
{
public:
	typedef enum
	{
		SELECT_MENU_NONE = 0,
		SELECT_MENU_ONE,			//1つ目のメニュー
		SELECT_MENU_TWO,			//2つ目のメニュー
		SELECT_MENU_THREE,			//3つ目のメニュー
		SELECT_MENU_FOUR,			//4つ目のメニュー
		SELECT_MENU_MAX			//状態の総数
	}SELECT_MENU;				//列挙型

	typedef enum
	{
		SELECTTYPE_NONE = 0,	//選ばれていない状態
		SELECTTYPE_SELECT,		//選ばれている	状態
		SELECTTYPE_MAX			//状態の総数
	}SELECT;

	typedef enum
	{
		MENU_TYPE_NONE = 0,		//初期
		MENU_TYPE_TUTORIAL,		//チュートリアル
		MENU_TYPE_RESULT,		//リトライ
		MENU_TYPE_PAUSE,		//ポーズ
		MENU_TYPE_MAX			//状態の総数
	}MENU_TYPE;

	typedef struct
	{
		SELECT		select;		//セレクト
		D3DXVECTOR3 pos;		//位置
		D3DXCOLOR	col;		//カラー
	}SELECTMENU;

	CSelectMenu(int nPriority = 7);
	~CSelectMenu();
	static CSelectMenu *Create(D3DXVECTOR3 pos, float fLength, float fSpace, MENU_TYPE type);
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static SELECT_MENU *GetModeSelectMode(void) {	return &m_SelectMode;	}
	static HRESULT Load(void) { return S_OK; }
	static void UnLoad(void);
	static bool GetModeSelectBool(void) { return m_bModeSelect; }
	static void SetModeSelectBool(bool ModeSelectBool) { m_bModeSelect = ModeSelectBool; }

	void MenuDecide(SELECT_MENU MenuSelect);

	//メンバ変数
private:
	/* 背景の種類 */
	typedef enum
	{
		SELECTMODEBGTYPE_BG = 0,
		SELECTMODEBGTYPE_BAND_L,
		SELECTMODEBGTYPE_BAND_R,
		SELECTMODEBGTYPE_FRAME,
		SELECTMODEBGTYPE_EXPLANATION

	}SELECTMODEBGTYPE;

	/* ポリゴンの種類 */
	typedef enum
	{
		POLYGONTYPE_NONE = 0,
		POLYGONTYPE_MENU,
		POLYGONTYPE_BG
	}POLYGONTYPE;

	/* アニメーションの割り方種類 */
	typedef enum
	{
		ANIMTYPE_NONE=0,
		ANIMTYPE_X,
		ANIMTYPE_Y,
		ANIMTYPE_MAX

	}ANIMTYPE;
	void ScrollMenu(SELECTMODEBGTYPE type, float fScroolSpeed);
	void SelectModeExplanation(int MenuSelect);
	void SelectAnimation(int MenuSelect);
	void SelectMove(POLYGONTYPE type,int MenuNum);
	void SetSelectAnimation(POLYGONTYPE type, ANIMTYPE AnimType,int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY,int AnimSpeed);
	void InitTutorialPolygon(void);

	D3DXVECTOR3					m_InitPos;
	float						m_fWidth, m_fHeight;	// 幅高さ
	float						m_fSpace;
	float						m_fInitYpos;	//メニューの初期高さ
	D3DXVECTOR3					m_TexMove;

	static LPDIRECT3DTEXTURE9	m_pTexture[MAX_SELECTMENU];			// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;							// 頂点バッファへのポインタ
	static LPDIRECT3DTEXTURE9	m_pTextureBG;						// テクスチャポインタ
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuffBG;						// 頂点バッファへのポインタ
	CScene2D					*m_apPolygonBG[MAX_SELETMODE_BG];	// メニューのポリゴン
	MENU_TYPE					m_MenuType;							// メニューのタイプ
	SELECTMENU					m_aModeSelectMenu[MAX_SELECTMENU];	// セレクトメニュー
	D3DXVECTOR3					m_Pos[MAX_SELECTMENU];				// 位置
	static SELECT_MENU			m_SelectMode;						// 選択してるモード
	int							m_nSelect;							// 選択している番号
	CScene2D					*m_apPolygon[MAX_SELECTMENU];		// メニューのポリゴン
	static	bool				m_bModeSelect;						// セレクトメニューの状態
	int							m_nMaxMenu;							// メニュー最大数

	/* 演出面変数 */
	int m_nCntScrool;		//スクロールカウンター
	int m_nCntAnim;			//アニメカウンター
	int m_nPatturnAnim;		//アニメパターン
	int m_nCntAnim2;			//アニメカウンター
	int m_nPatturnAnim2;		//アニメパターン
	float m_fChangeMode;	//選択中モードアイコンの移動制御カウンター
	float m_fMoveMode;		//選択中モードアイコンの移動量を計る
};

#endif