//=============================================================================
//
// 制限時間処理 [time.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _POINT_H_
#define _POINT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;
class CBillNumber;
class CScene2D;
class CSceneBillBoard;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POINT_NUM			(2)		// タイマーの桁数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPoint : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// 何もなし
		TYPR_PLAYER,	// プレイヤー
		TYPE_CPU,		// 敵
		TYPE_MAX
	}TYPE_CHARACTER;

	CPoint(int nPriority = 6, OBJTYPE objType = OBJTYPE_POINT);
	~CPoint();

	static CPoint *Create(int nID, int nNumPlayer, TYPE_CHARACTER type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexPoint(int nTexData);

	//============================
	// 設定　取得　の関数
	//============================
	int GetPoint(void) { return m_nTotalPoint; };

	//============================
	// 加算　減算　の関数
	//============================
	void AddPoint(int nPoint);				// 加算処理
	void SubtractionPoint(int nPoint);		// 減算処理
	void RankLogoTex(int nWinNum);			// 順位のTEX変更


private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData);
	void UIPosition(int nID);			// UIの位置まとめ
	void PointPostion();				// ポイントの位置まとめ
	void SizeChange(void);				// 増減時のサイズ変更
	void RankPos(void);					// 順位の位置まとめ
	void ChangeRank(void);				// 順位入れ替わり処理
	void ConfirmDirecting(D3DXVECTOR2 size);		// 確定演出

	CBillNumber *m_apNumber[MAX_POINT_NUM];	// ナンバーへのポインタ
	int m_nTotalPoint;							// トータルのポイント
	int						m_nPointNum;		// ポイントの表示数字数
	int						m_nNumPlayer;		// 人数保管
	int						m_nID;				// 自分の番号
	int						m_nCount;			// 二桁目に行くかのカウント
	int						m_nWinNum;			// 現時点での勝利数
	int						m_nCntbConfirm;		// 確定の時間カウント
	int						m_nCountNum;			// カウント
	float					m_fPosOld;
	bool					m_bStart;
	bool					m_bSizeChange;		// ポイント増減時のサイズ変更
	bool					m_bColChange;		// 色の切替
	bool					m_bChangeFlag;		// 切替フラグ
	bool					m_bFlag;
	bool					m_bRankChangeFlag;	// 順位入れ替え時のフラグ
	bool					m_bFlag001;
	bool					m_bConfirmFlag;		// 順位確定フラグ
	D3DXVECTOR3				m_pos;				// 位置
	D3DXVECTOR3				m_RnakSize;			// 順位のサイズ
	CScene2D				*m_pIcon;			// プレイヤーアイコン
	CScene2D				*m_pRank;			// 順位のロゴ
	CSceneBillBoard			*m_pCrown;			// 王冠
	TYPE_CHARACTER			m_type;				// 種類
	CSceneBillBoard			*m_pDouble;			// 2倍の表示

	D3DXVECTOR2				m_TexMin, m_TexMax;	// テクスチャ座標保存
};
#endif
