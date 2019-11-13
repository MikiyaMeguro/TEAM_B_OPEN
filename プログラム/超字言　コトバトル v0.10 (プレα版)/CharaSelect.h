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

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_CHARASELECT			(4)
#define MAX_CHARASELTEX			(11)

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
		CHARASEL_POLYGONTYPE_BG = 0,	//背景
		CHARASEL_POLYGONTYPE_BAND_L,	//帯：左
		CHARASEL_POLYGONTYPE_BAND_R,	//帯：右
		CHARASEL_POLYGONTYPE_MASK1,		//マスク左上
		CHARASEL_POLYGONTYPE_MASK2,		//マスク右上
		CHARASEL_POLYGONTYPE_MASK3,		//マスク左下
		CHARASEL_POLYGONTYPE_MASK4,		//マスク右下
		CHARASEL_POLYGONTYPE_MAX		//最大数

	}CHARASEL_POLYGONTYPE;

	/* キャラクターの種類 */
	typedef enum
	{
		CHARACTORTYPE_BALANCE = 0,
		CHARACTORTYPE_POWOR,
		CHARACTORTYPE_SPEED,
		CHARACTORTYPE_REACH,
		CHARACTORTYPE_NONE,
		CHARACTORTYPE_MAX
	}CHARACTORTYPE;

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

	void Initpointer(void);																//ポインタの初期化
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);						//テクスチャスクロール処理
	void SelectProduction(SELECT_STATE &Sel, SELECT_STATE &Selold, CHARACTORTYPE type);	//演出処理
	void InitCharaSelectPoly(void);														//ポインタの初期化
	bool collision(int operation,CHARACTORTYPE type);									//あたり判定
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);										//移動制限
	void SetCommand(void);																//コマンド設定
	void CharaSelTex(SELECT_STATE Sel, CHARACTORTYPE &type, CHARACTORTYPE &typeOld);	//テクスチャ座標管理
	bool ConfirmationSelect(void);														//プレイヤーが全員選択したか確認する												
	bool collisionConf(int operation);													//確定ポリとあたり判定
	bool ProductionConf(void);															//確定ポリの演出

	static CScene2D *m_apScene2D[MAX_CHARASELTEX];	//背景系のポインタ
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];	//選択肢
	static CScene2D *m_apCursor2D[MAX_CHARASELECT];	//カーソル
	static CScene2D *m_apBadge2D[MAX_CHARASELECT];	//バッジ
	static CScene2D *m_apConfirm2D;					//確定
	CHARACTORTYPE m_CharaType[MAX_CHARASELECT];		//選ばれたキャラの種類
	CHARACTORTYPE m_CharaTypeOld[MAX_CHARASELECT];	//前回選ばれたキャラの種類
	D3DXVECTOR3 m_move[MAX_CHARASELECT];			//移動量
	bool m_bPCSelMove[MAX_CHARASELECT];				//選ばれていない時のみ移動できる
	int m_OperationNum;								//現在操作しているプレイヤー番号

	/* 演出系変数 */
	int m_nCntScrool;								//スクロールのカウンター
	float m_fFlashAlpha;							//演出の透明値管理
	bool m_bConfProFinish, m_bConfProStart,m_bConf;	//演出が終わったか
	float m_moveConfPro;							//確定ポリの移動
	SELECT_STATE m_SelectState[MAX_CHARASELECT];	//演出の状態
	SELECT_STATE m_SelectStateold[MAX_CHARASELECT];	//前回の演出状態を記録
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;		//プレイヤーの人数
	CONFPRODUCTION_STATE m_CnfProState;				//確定の演出状態

};
#endif