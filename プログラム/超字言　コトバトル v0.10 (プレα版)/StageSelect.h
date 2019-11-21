//=============================================================================
//
// ステージセレクトの処理 [StageSelect.h]
// Author : 目黒未来也
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_STAGESELECT		(3)
#define MAX_STAGESELECT_TEX (3)

class CStageSelect
{
public:
	CStageSelect();
	~CStageSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CStageSelect *Create(void);
	static int GetStageState(void) { return m_nSelect; }

private:
	/* ポリゴンの種類 */
	typedef enum
	{
		STAGESELECTTYPE_BG = 0,		//背景
		STAGESELECTTYPE_BAND_L,		//帯：左
		STAGESELECTTYPE_BAND_R,		//帯：右
		STAGESELECTTYPE_MAX			//最大数
	}STAGESELECTTYPE;

	/* 選択状態 */
	typedef enum
	{
		SELECTTYPE_SELECT_MACHINE = 0,			//機械ステージ
		SELECTTYPE_SELECT_WEATHER,				//天候ステージ
		SELECTTYPE_SELECT_TERRAIN,				//地形ステージ
		SELECTTYPE_MAX							//状態の総数
	}SELECTTYPE;

	/* 選択肢移動の状態 */
	typedef enum
	{
		SELECTICON_STATE_NONE = 0,
		SELECTICON_STATE_MOVE_R,	//右回り
		SELECTICON_STATE_MOVE_L,	//左回り
		SELECTICON_STATE_STOP,
		SELECTICON_STATE_MAX
	}SELECTICONSTATE;

	void InitPolygon(void);																				//ポリゴンの初期設定
	void ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed);											//テクスチャスクロール処理
	void Selecttype(SELECTTYPE state);																	//選択状態の管理
	void ProductionIcon(SELECTICONSTATE &state, SELECTTYPE type);		//選択肢の移動演出
	void Replacement(SELECTICONSTATE state);

	/* 変数 */
	static CScene2D *m_apScene2D[MAX_STAGESELECT_TEX];
	static CScene2D *m_apSelect2D[MAX_STAGESELECT];
	static int	m_nSelect;											// 選択している番号
	SELECTTYPE m_type;												//選択されている番号の状態

	/* 演出系変数 */
	int m_nCntScrool;												//スクロールのカウンター
	char *m_pcStageName[MAX_STAGESELECT];							// ステージの名前保管
	D3DXVECTOR3 m_SelectPos[MAX_STAGESELECT];						//セレクトの位置を保存
	SELECTICONSTATE m_MoveIconState;								//移動の状態
	float m_fWidth[MAX_STAGESELECT], m_fHeight[MAX_STAGESELECT];	//縦と横の形を保存しておく
	D3DXCOLOR m_IconCol[MAX_STAGESELECT];							//色を保存しておく
	bool m_bRep;													//入れ替えを一回だけやるフラグ
};
#endif