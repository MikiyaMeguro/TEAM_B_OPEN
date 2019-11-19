//=============================================================================
//
// 文字のビルボードの処理 [word.h]
// Author :  Shun Yokomici
//
//=============================================================================
#ifndef _WORD_H_
#define _WORD_H_

#include "sceneBillboard.h"
#include "game.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CWord : public CSceneBillBoard //派生クラス
{
public:
	CWord();
	~CWord();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWord *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord, int nNum = 0);

	// 関数
	D3DXVECTOR3 Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle, float fDistance);
	void Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle);				// 円を作る
	void Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNumPlayer);							// 距離だけを測る
	int ComparisonDistance(int nNumPlayer);		// 距離の比較
	void SetSearchCol(D3DXCOLOR col);											// 3文字目候補の色設定
	void UninitSearchCol(D3DXCOLOR col);										// 3文字目候補が消えた場合


	// 取得 もしくは 設定の関数
	int GetWordNum(void) { return m_nWordNum; }	// 文字番号を取得
	int GetNum(void) { return m_nNum; }			// 文字自身の番号を取得
	bool GetUninitFlag(void) { return m_bFlagUninit; }
private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void SizeScale(D3DXVECTOR3 *size, float fMove, D3DXVECTOR2 MaxSize);		// 拡大縮小

	D3DXVECTOR3 m_size;		// サイズ
	D3DXVECTOR3 m_sizeOld;	// サイズ(過去)
	D3DXCOLOR m_col;		// 色
	bool m_bFlagUninit;		// 終了するためのフラグ
	bool m_bMoveFlag;		// 上下移動のフラグ
	bool m_bScaleFlag;		// 拡大縮小するフラグ
	bool m_bFlag;			// 獲得できるかできないか
	bool m_bPopFlag;		// 出現時のフラグ
	int m_nWordNum;			// 文字の番号
	int m_nNumPlayerGet;	// 取得された時のプレイヤーの番号
	float m_fDistance[MAX_PLAYER];	// プレイヤーとの距離
	float m_fMoveY;			// 移動距離
	float m_colA;			// 透明度

	int		   m_nNum;
	int		   m_nCntUninit;	// 終了するまでのカウント

	CSceneBillBoard *m_pBillBoard;
	int		m_nAnim;
	int		m_nPatten;

	// 3文字目の候補時
	D3DXCOLOR *m_SearchCol;
	bool m_bSearchFlag;		// 探す時のフラグ
	int m_nCntSearch;
	int m_nNumSearch;
};

#endif