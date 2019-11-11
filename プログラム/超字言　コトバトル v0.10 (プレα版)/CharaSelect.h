//=============================================================================
//
// キャラセレクトの処理 [CharaSelect.h]
// Author : 目黒未来也/後閑茜
//
//=============================================================================
#ifndef _CHARASELECT_H_
#define _CHARASELECT_H_

#include "scene.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_CHARASELECT			(4)
#define MAX_CHARASELTEX			(7)

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

	void Initpointer(void);											//ポインタの初期化
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);	//テクスチャスクロール処理
	void SelectProduction(int SelNum);
	void InitCharaSelectPoly(void);
	bool collision(CHARACTORTYPE type);
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);

	//void SelectState(void);
	static CScene2D *m_apScene2D[MAX_CHARASELTEX];
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];
	static CScene2D *m_apCursor2D;
	static CScene2D *m_apBadge2D;

	D3DXVECTOR3 m_move;
	bool m_bPCColl[MAX_CHARASELECT];
	bool m_bPCSelMove;

	/* 演出系変数 */
	int m_nCntScrool;
	float m_fFlashAlpha[MAX_CHARASELECT];
	SELECT_STATE m_SelectState[MAX_CHARASELECT];
	SELECT_STATE m_SelectStateold[MAX_CHARASELECT];

};
#endif