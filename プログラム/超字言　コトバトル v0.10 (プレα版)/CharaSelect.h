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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_PLAYER				(4)
#define MAX_CHARASELECT			(5)
#define MAX_CHARASELTEX			(15)

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

private:
	/* ポリゴンの種類 */
	typedef enum
	{
		CHARASEL_POLYGONTYPE_BG = 0,		//背景
		CHARASEL_POLYGONTYPE_BAND_L,		//帯：左
		CHARASEL_POLYGONTYPE_BAND_R,		//帯：右
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

	/* 選ばれてるかの状態 */
	typedef enum
	{
		SELECTSTATE_NONE = 0,
		SELECTSTATE_FLASH,
		SELECTSTATE_SELECT,
		SELECTSTATE_NOSELECT
	}SELECT_STATE;

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

	void Initpointer(void);																						//ポインタの初期化
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);												//テクスチャスクロール処理
	void SelectProduction(int nNum,SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type);			//演出処理
	void InitCharaSelectPoly(void);																				//ポインタの初期化
	bool collision(int operation,CPlayer::PLAYER_TYPE type);													//あたり判定
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);																//移動制限
	void SetCommand(void);																						//コマンド設定
	void CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type, CPlayer::PLAYER_TYPE &typeOld);	//テクスチャ座標管理
	bool ConfirmationSelect(void);																				//プレイヤーが全員選択したか確認する												
	bool collisionConf(int operation);																			//確定ポリとあたり判定
	bool ProductionConf(void);																					//確定ポリの演出
	void FlashConf(void);																						//確定ポリの点滅
	void ProductionCard(void);																					//キャラ選択カード演出処理
	void Move(CFade *pFade, CManager *pManager, int nControllNum);												//移動/選択処理


	static CScene2D *m_apScene2D[MAX_CHARASELTEX];		//背景系のポインタ
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];		//選択肢
	static CScene2D *m_apCursor2D[MAX_PLAYER];			//カーソル
	static CScene2D *m_apBadge2D[MAX_PLAYER];			//バッジ
	static CScene2D *m_apConfirm2D;						//確定
	CPlayer::PLAYER_TYPE m_CharaType[MAX_PLAYER];		//選ばれたキャラの種類
	CPlayer::PLAYER_TYPE m_CharaTypeOld[MAX_PLAYER];	//前回選ばれたキャラの種類
	CPlayer::PLAYER_TYPE m_CharaTypeFinal[MAX_PLAYER];	//最終的に選ばれたキャラの種類
	D3DXVECTOR3 m_move[MAX_PLAYER];						//移動量
	bool m_bPCSelMove[MAX_PLAYER];						//選ばれていない時のみ移動できる
	int m_OperationNum;									//現在操作しているプレイヤー番号

	/* 演出系変数 */
	int m_nCntScrool, m_CntFlash, m_CntFadeF;						//スクロールのカウンター/確定時のフラッシュ/遷移までの秒数カウンター
	float m_fFlashAlpha;											//演出の透明値管理
	bool m_bConfProFinish, m_bConfProStart,m_bConf,m_bCharaCard;	//演出が終わったか
	bool m_bCnfFlash;												//確認ポリのフラシュ開始
	float m_moveConfPro;											//確定ポリの移動
	SELECT_STATE m_SelectState[MAX_PLAYER];							//演出の状態
	SELECT_STATE m_SelectStateold[MAX_PLAYER];						//前回の演出状態を記録
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;						//プレイヤーの人数
	CONFPRODUCTION_STATE m_CnfProState;								//確定の演出状態
	CHARACARDPRO_STATE m_CharaCardProduction;						//キャラ選択カードの演出の状態
	D3DXVECTOR3 m_CharaCardPro_FinishPos[MAX_CHARASELECT];			//選択カードの最終位置
	float m_fCardWidth[MAX_CHARASELECT][2];
	float m_fCharaCardPro_FinishWH[2];								//選択カードの最終幅と高さ
};
#endif