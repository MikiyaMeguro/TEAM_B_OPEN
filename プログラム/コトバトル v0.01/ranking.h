//=============================================================================
//
// ランキング画面管理クラス処理 [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "Manager.h"

//===================================================================
//	マクロ定義
//===================================================================
#define MAX_RANKING (5)

//===================================================================
//	クラスの定義
//===================================================================
class CRanking
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);

	static void SetRankScore(int nScore);
private:
	static int m_aRankingScore[MAX_RANKING];

};
#endif // !_RANKING_H_
