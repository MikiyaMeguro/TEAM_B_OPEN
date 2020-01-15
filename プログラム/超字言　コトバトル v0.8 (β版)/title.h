//=============================================================================
//
// タイトル処理 [title.h]
// Author : 目黒 未来也/Akane Gokan
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"
#include<time.h>

//前方宣言
class CScene2D;

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_TITLEPOLYGON (10)											// 使用するポリゴンの最大数
#define BG_HUMAN_SIZE_W (230.0f)										// 背景(人間)の横幅大きさ
#define COL_DEFAULT (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))					// 色:デフォルト
#define COL_DEFAULT_TRANSPARENT (D3DXCOLOR(1.0f,1.0f,1.0f,0.0f))		// 色:透明
#define COL_PRODUCTION_HUMAN (D3DXCOLOR(1.0f,1.0f,1.0f,0.8f))			// 背景(人間)の変更後の色
#define POS_DEFOLT (D3DXVECTOR3(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0.0f))	// 画面の中心座標
#define TITLEROGO_CORRECTION (28.0f)									// タイトルロゴの微調整値

//クラス（シーン2Dの派生クラス）
class CTitle
{
public:
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void InitpScene2D(void);		//ポインタの初期化処理
	void UninitpScene2D(void);		//ポインタの終了処理
	void SetScene2D(void);			//2Dポリゴンの初期設定
	void Production(void);			//演出
	bool MoveBGCharactor(int Num);	//背景移動処理
	void HumanProductionPos(void);	//スキップした時の位置変更処理
	void Flash(void);				//フラッシュ
	void SparkProduction(void);		//スパークの演出
	void PressProduction(void);		//プレスボタンの演出処理
	bool TitleScaling(int Num);		//タイトル演出
	static CTitle *Create(void);

private:
	//ポリゴンの種類
	typedef enum
	{
		POLYGONTYPE_BALANCEBOY = 0,	//バランス男子
		POLYGONTYPE_REACHGIRL,		//リーチ女子
		POLYGONTYPE_POWORBOY,		//パワー男子
		POLYGONTYPE_SPEEDGIRL,		//スピード女子
		POLYGONTYPE_KOTOMON,		//コトモン
		POLYGONTYPE_SPARK,			//火花
		POLYGONTYPE_ROGO_MAIN,		//タイトルロゴ：メイン
		POLYGONTYPE_ROGO_SUB,		//タイトルロゴ：サブ
		POLYGONTYPE_FLASH,			//フラッシュ
		POLYGONTYPE_PRESSBUTTON		//プレスボタン
	}POLYGON_TYPE;

	// 演出の状態
	typedef enum
	{
		PRODUCTIONSTATE_NONE = 0,
		PRODUCTIONSTATE_START,		// 演出の開始
		PRODUCTIONSTATE_MOVE_B,		//バランス男子移動
		PRODUCTIONSTATE_MOVE_R,		//リーチ女子移動
		PRODUCTIONSTATE_MOVE_P,		//パワー男子移動
		PRODUCTIONSTATE_MOVE_S,		//スピード女子移動
		PRODUCTIONSTATE_FLASH,		//フラッシュの開始
		PRODUCTIONSTATE_TITLE_SUB,	//サブタイトルの演出
		PRODUCTIONSTATE_TITLE_MAIN,	//メインタイトルの演出
		PRODUCTIONSTATE_FINISH		// 全ての演出が終了

	}PRODUCTIONSTATE;

	//フラッシュの状態
	typedef enum
	{
		FLASHSTATE_NONE = 0,
		FLASHSTATE_START,	// フラッシュの開始
		FLASHSTATE_FADEOUT,	//フラッシュのフェードアウト
		FLASHSTATE_FINISH	// フラッシュの終了

	}FLASHSTATE;

	CScene2D* m_pScene2D[MAX_TITLEPOLYGON];	//シーン2Dのポインタ
	/* 演出全体変数 */
	PRODUCTIONSTATE m_ProductionState;		//演出の状態
	FLASHSTATE m_FlashSate;					//フラッシュの状態
	bool m_bProductionSkip,m_FlashSkip;		//演出スキップされたか/フラッシュスキップしたか否か

	/* フラッシュ変数 */
	int m_nCntFadeTime;						//フラッシュのフェード時間
	float m_fCntFade,m_fAlpha;				//フラッシュのカウンター/フラッシュのalpha値

	/* 火花変数 */
	float m_fChangeSparkMove;				//火花の移動制御カウンター
	float m_fSparkX;						//火花の移動量を計る

	/* プレスボタン変数 */
	int m_nCntFlashPress;					//点滅時間を管理するカウンター
	float m_fPressAlpha;					//点滅のalpha値
	bool m_bPressMode;						//プレスの状態管理

	/* タイトルロゴ変数 */
	float m_fTitleScal;						//拡縮のサイズ

	//タイトルコール
	bool m_bTitleCall;						//タイトルコールフラグ
	int  m_nTitleCallCnt;					//コールのタイミング

#ifdef _DEBUG
	int nCntFadeTime = 0;
#endif
};
#endif