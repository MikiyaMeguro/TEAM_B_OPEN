//=============================================================================
//
// ゲーム画面管理クラス処理 [ranking.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "ranking.h"
#include "Scene2D.h"
#include "fade.h"
#include "Score.h"

//==================================================================
// 静的メンバ変数
//==================================================================
int CRanking::m_aRankingScore[MAX_RANKING] = {};

//==================================================================
// コンストラクタ&デストラクタ
//==================================================================
CRanking::CRanking()
{
}
CRanking::~CRanking()
{

}

//==================================================================
// 初期化処理
//==================================================================
HRESULT CRanking::Init(void)
{

	return S_OK;
}

//==================================================================
// 終了処理
//==================================================================
void CRanking::Uninit(void)
{
	CScene::ReleaseAll(false);
}

//==================================================================
// 更新処理
//==================================================================
void CRanking::Update(void)
{
	CFade* pFade = CManager::GetFade();
	if (CCommand::GetCommand("ENTER"))
	{
		if (pFade != NULL)
		{
			pFade->SetFade(CManager::MODE_TITLE, CFade::COLOR_WHITE);
		}
	}
}

//==================================================================
// 描画処理
//==================================================================
void CRanking::Draw(void)
{

}

//==================================================================
// ランキング再集計処理
//==================================================================
void CRanking::SetRankScore(int nScore)
{
	int nRankScore = nScore;
	if (nRankScore < 0) { nRankScore = 0; }
	if (nRankScore > SCORECOUNT_MAX) { nRankScore = SCORECOUNT_MAX; }

	int nCntNum, nCntNum2;			//スコアの桁数のカウンター

	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{// 順位変更
		if (m_aRankingScore[nCntLength] < nRankScore)
		{// 上書き阻止のために数字を逃がす
			nCntNum = m_aRankingScore[nCntLength];
			m_aRankingScore[nCntLength] = nRankScore;

			// 関係ないところは並べないfor文
			for (int nCntLength2 = nCntLength + 1; nCntLength2 < MAX_RANKING; nCntLength2++)
			{// 書き換えたときの次の数字を並べ替え
				nCntNum2 = m_aRankingScore[nCntLength2];
				m_aRankingScore[nCntLength2] = nCntNum;
				nCntNum = nCntNum2;
			}
			break;
		}
	}


}