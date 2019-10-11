//=============================================================================
//
// �Q�[����ʊǗ��N���X���� [ranking.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "ranking.h"
#include "Scene2D.h"
#include "fade.h"
#include "Score.h"

//==================================================================
// �ÓI�����o�ϐ�
//==================================================================
int CRanking::m_aRankingScore[MAX_RANKING] = {};

//==================================================================
// �R���X�g���N�^&�f�X�g���N�^
//==================================================================
CRanking::CRanking()
{
}
CRanking::~CRanking()
{

}

//==================================================================
// ����������
//==================================================================
HRESULT CRanking::Init(void)
{

	return S_OK;
}

//==================================================================
// �I������
//==================================================================
void CRanking::Uninit(void)
{
	CScene::ReleaseAll(false);
}

//==================================================================
// �X�V����
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
// �`�揈��
//==================================================================
void CRanking::Draw(void)
{

}

//==================================================================
// �����L���O�ďW�v����
//==================================================================
void CRanking::SetRankScore(int nScore)
{
	int nRankScore = nScore;
	if (nRankScore < 0) { nRankScore = 0; }
	if (nRankScore > SCORECOUNT_MAX) { nRankScore = SCORECOUNT_MAX; }

	int nCntNum, nCntNum2;			//�X�R�A�̌����̃J�E���^�[

	for (int nCntLength = 0; nCntLength < MAX_RANKING; nCntLength++)
	{// ���ʕύX
		if (m_aRankingScore[nCntLength] < nRankScore)
		{// �㏑���j�~�̂��߂ɐ����𓦂���
			nCntNum = m_aRankingScore[nCntLength];
			m_aRankingScore[nCntLength] = nRankScore;

			// �֌W�Ȃ��Ƃ���͕��ׂȂ�for��
			for (int nCntLength2 = nCntLength + 1; nCntLength2 < MAX_RANKING; nCntLength2++)
			{// �����������Ƃ��̎��̐�������בւ�
				nCntNum2 = m_aRankingScore[nCntLength2];
				m_aRankingScore[nCntLength2] = nCntNum;
				nCntNum = nCntNum2;
			}
			break;
		}
	}


}