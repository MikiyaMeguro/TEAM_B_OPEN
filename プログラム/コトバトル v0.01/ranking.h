//=============================================================================
//
// �����L���O��ʊǗ��N���X���� [ranking.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_
#include "main.h"
#include "Manager.h"

//===================================================================
//	�}�N����`
//===================================================================
#define MAX_RANKING (5)

//===================================================================
//	�N���X�̒�`
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
