//=============================================================================
//
// キャラセレクトの処理 [CharaSelect.h]
// Author : 目黒未来也/後閑茜
//
//=============================================================================
#ifndef _CHARASELECT_H_
#define _CHARASELECT_H_

#include "scene.h"
#include "PlayerNumSelect.h"
#include "player.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;
class CPlayer;
class CFade;
class CManager;
class CCharaSelCursol;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER				(4)
#define MAX_CHARASELECT			(5)
#define MAX_CHARASELTEX			(16)

class CCharaSelect
{
public:
	CCharaSelect();
	~CCharaSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCharaSelect *Create(void);

	/* 選ばれてるかの状態 */
	typedef enum
	{
		SELECTSTATE_NONE = 0,
		SELECTSTATE_FLASH,
		SELECTSTATE_SELECT,
		SELECTSTATE_NOSELECT
	}SELECT_STATE;

	bool GetCardPro(void) { return m_bCharaCard; }															//カードの演出のフラグ
	bool GetConf(void) { return m_bConf; }																	//確定のフラグ
	bool collision(int operation, CPlayer::PLAYER_TYPE type);												//あたり判定
	void SelectProduction(int nNum, SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type);	//演出処理
	void CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type);								//テクスチャ座標管理
	void DecisionCharactor(CFade *pFade, CManager *pManager, int operation);								//遷移前の設定
	bool collisionBackMode(int operation);																	//モード戻ポリゴンとあたり判定
	void SetBackModeTex(void);																				//戻るポリゴンの座標設定
	void SetPlayerWindowChara(int operation, CPlayer::PLAYER_TYPE type);									//カーソルが当たっている場所でウィンドウにキャラを出す
	void SetWindowCharaDraw(int nNum, bool bDraw);
	void SetBackMode(int nId,bool bBack) { m_bBackModeColl[nId] = bBack; }												//戻るモードの設定
	bool GetBackMode(int nId) { return m_bBackModeColl[nId]; }
private:
	/* ポリゴンの種類 */
	typedef enum
	{
		CHARASEL_POLYGONTYPE_BG = 0,		//背景
		CHARASEL_POLYGONTYPE_BAND_L,		//帯：左
		CHARASEL_POLYGONTYPE_BAND_R,		//帯：右
		CHARASEL_POLYGONTYPE_BACKMODE,		//戻る
		CHARASEL_POLYGONTYPE_MASK1,			//マスクPL_1
		CHARASEL_POLYGONTYPE_MASK2,			//マスクPL_2
		CHARASEL_POLYGONTYPE_MASK3,			//マスクPL_3
		CHARASEL_POLYGONTYPE_MASK4,			//マスクPL_4
		CHARASEL_POLYGONTYPE_PLUI_CHARA1,	//選択キャラを各プレイヤーのウィンドウに表示:PL_1
		CHARASEL_POLYGONTYPE_PLUI_CHARA2,	//選択キャラを各プレイヤーのウィンドウに表示:PL_2
		CHARASEL_POLYGONTYPE_PLUI_CHARA3,	//選択キャラを各プレイヤーのウィンドウに表示:PL_3
		CHARASEL_POLYGONTYPE_PLUI_CHARA4,	//選択キャラを各プレイヤーのウィンドウに表示:PL_4
		CHARASEL_POLYGONTYPE_MAX			//最大数

	}CHARASEL_POLYGONTYPE;
	/* 確定の演出 */
	typedef enum
	{
		CONFPRODUCTION_NONE = 0,	//何もしない
		CONFPRODUCTION_MOVE_START,	//移動開始
		CONFPRODUCTION_MOVE,		//移動
		CONFPRODUCTION_MOVE_END,	//移動終了
		CONFPRODUCTION_MAX

	}CONFPRODUCTION_STATE;

	/* キャラ選択カード演出処理 */
	typedef enum
	{
		CHARACARDPRO_NONE = 0,		//何もしてない
		CHARACARDPRO_START,			//開始
		CHARACARDPRO_MOVE,			//移動
		CHARACARDPRO_TURNOVER_B,	//ひっくり返す(裏面-＞表)
		CHARACARDPRO_FACEUP,		//表面になる
		CHARACARDPRO_FINISH,		//終了
		CHARACARDPRO_MAX

	}CHARACARDPRO_STATE;

	void Initpointer(void);											//ポインタの初期化
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);	//テクスチャスクロール処理
	void InitCharaSelectPoly(void);									//ポインタの初期化
	bool ConfirmationSelect(void);									//プレイヤーが全員選択したか確認する
	bool collisionConf(int operation);								//確定ポリとあたり判定
	bool ProductionConf(void);										//確定ポリの演出
	void FlashConf(void);											//確定ポリの点滅
	void ProductionCard(void);										//キャラ選択カード演出処理

	static CScene2D *m_apScene2D[MAX_CHARASELTEX];					//背景系のポインタ
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];					//選択肢
	static CScene2D *m_apConfirm2D;									//確定
	static CCharaSelCursol *m_apCursol[MAX_PLAYER];					//カーソル
	CPlayer::PLAYER_TYPE m_CharaType[MAX_PLAYER];					//選ばれたキャラの種類
	static bool m_bBackModeColl[MAX_PLAYER];									//戻るポリゴンと当たってるかのフラグ

	/* 演出系変数 */
	int m_nCntScrool, m_CntFlash, m_CntFadeF;						//スクロールのカウンター/確定時のフラッシュ/遷移までの秒数カウンター
	float m_fFlashAlpha[MAX_PLAYER];								//演出の透明値管理
	bool m_bConfProFinish, m_bConfProStart,m_bConf;					//演出が終わったか
	static bool m_bCharaCard;										//カード演出のフラグ
	bool m_bCnfFlash;												//確認ポリのフラシュ開始
	float m_moveConfPro;											//確定ポリの移動
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;						//プレイヤーの人数
	CONFPRODUCTION_STATE m_CnfProState;								//確定の演出状態
	CHARACARDPRO_STATE m_CharaCardProduction;						//キャラ選択カードの演出の状態
	D3DXVECTOR3 m_CharaCardPro_FinishPos[MAX_CHARASELECT];			//選択カードの最終位置
	float m_fCardWidth[MAX_CHARASELECT][2];							//カードの幅
	float m_fCharaCardPro_FinishWH[2];								//選択カードの最終幅と高さ
	float m_fGaugeSizeX[MAX_PLAYER];								//戻るゲージの長さを保管
	float m_fMaxGaugeX[MAX_PLAYER];									//ゲージの最大の長さ
#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif

};
#endif