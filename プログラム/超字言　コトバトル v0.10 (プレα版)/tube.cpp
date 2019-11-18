//=============================================================================
//
// �����ۊǂ�UI���� [tube.h]
// Author : �ڍ� ������
//
//=============================================================================
#include "tube.h"
#include "manager.h"
#include "debugProc.h"
#include "input.h"
#include "scene2D.h"
#include "scene2D.h"
#include "game.h"
#include "PlayerNumSelect.h"
#include "point.h"
//=============================================================================
// �}�N���֐�
//=============================================================================
#define WORD_POS	(CScene2D::GetPosition())			// �����̈ʒu
#define POS_ONE_001		(D3DXVECTOR3(WORD_POS.x - 69.0f, WORD_POS.y - 70.0f, 0.0f))		// �ŏ��̈ʒu
#define POS_TOW_001		(D3DXVECTOR3(WORD_POS.x + 29.0f, WORD_POS.y - 41.0f, 0.0f))		// ��ڂ̈ʒu
#define POS_THREE_001	(D3DXVECTOR3(WORD_POS.x + 54.0f, WORD_POS.y + 64.0f, 0.0f))		// �O�ڂ̈ʒu

#define POS_ONE_002		(D3DXVECTOR3(WORD_POS.x - 46.0f, WORD_POS.y - 52.5f, 0.0f))		// �ŏ��̈ʒu
#define POS_TOW_002		(D3DXVECTOR3(WORD_POS.x + 19.0f, WORD_POS.y - 31.0f, 0.0f))		// ��ڂ̈ʒu
#define POS_THREE_002	(D3DXVECTOR3(WORD_POS.x + 36.0f, WORD_POS.y + 48.0f, 0.0f))		// �O�ڂ̈ʒu

#define SIZE_000	(D3DXVECTOR2(47.0f, 54.0f))
#define SIZE_001	(D3DXVECTOR2(30.0f, 40.0f))

#define POS_ANSWER_001	(D3DXVECTOR3(WORD_POS.x - 50.0f, WORD_POS.y + 44.0f, 0.0f))		// �����̈ʒu
#define SIZE_ANSWER_001	(D3DXVECTOR2(60.0f, 70.0f))		// �����̈ʒu

#define POS_ANSWER_002	(D3DXVECTOR3(WORD_POS.x - 32.0f, WORD_POS.y + 32.0f, 0.0f))		// �����̈ʒu
#define SIZE_ANSWER_002	(D3DXVECTOR2(38.0f, 50.0f))		// �����̈ʒu

#define MOVE			(3.0f)
#define AREA			(2.0f * 2.0f)
#define WORD_SCALE		(0.5f)				// �������k�ޑ��x
//=============================================================================
// �V�[���N���X�̃R���X�g���N�^
//=============================================================================
CTube::CTube(int nPriority, OBJTYPE objType) : CScene2D(nPriority, objType)
{
	// �l���N���A
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		m_apWord[nCntWord] = NULL;
	}
	m_pAnswerModel = NULL;
	m_nAnswer = 0;
	m_bModelTexFlag = false;
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CTube *CTube::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag,int nPriority)
{
	CTube *pTube = NULL;

	if (pTube == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pTube = new CTube(nPriority, OBJTYPE_SCENE2D);

		if (pTube != NULL)
		{
			pTube->Init(pos);
			pTube->SetWidthHeight(size.x, size.y);	// �T�C�Y�ݒ�
			pTube->BindTexture(Tag);
		}
	}

	return pTube;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTube::~CTube()
{
}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CTube::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos);

	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	if (NumPlayer == 1) { m_AnswerPos = POS_ANSWER_001; }
	else if (NumPlayer != 1) { m_AnswerPos = POS_ANSWER_002; }
	
	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CTube::Uninit(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->Uninit();
			m_apWord[nCntWord] = NULL;
		}
	}

	if (m_pAnswerModel != NULL) { m_pAnswerModel->Uninit(); m_pAnswerModel = NULL; }

	CScene2D::Uninit();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CTube::Update(void)
{
	if (m_bModelTexFlag == true) { Collect(); }		// ���S�_�ɏW�܂�

	CScene2D::Update();
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CTube::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// �����̔ԍ��ݒ�̏���
//=============================================================================
void CTube::SetWordNum(int nWordNum, int nNum)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR2 size = {};
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (NumPlayer == 1)
	{	// 1�l�v���C�̏ꍇ
		if (nNum == 0) { pos = POS_ONE_001; }
		else if (nNum == 1) { pos = POS_TOW_001; }
		else if (nNum == 2) { pos = POS_THREE_001; }
		size = SIZE_000;
	}
	else if (NumPlayer != 1)
	{ // 1�l�v���C����Ȃ��ꍇ
		if (nNum == 0) { pos = POS_ONE_002; }
		else if (nNum == 1) { pos = POS_TOW_002; }
		else if (nNum == 2) { pos = POS_THREE_002; }
		size = SIZE_001;
	}

	if (m_apWord[nNum] == NULL)
	{
		m_apWord[nNum] = CScene2D::Create(pos, "WORD", 3);
		m_apWord[nNum]->SetWidthHeight(size.x, size.y);	// �T�C�Y�ݒ�
		m_apWord[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
	}

	if (nNum == 2)
	{
		m_bModelTexFlag = true;
		if (m_pAnswerModel != NULL) { m_pAnswerModel->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f)); }
	}
	else if (nNum < 2)
	{
		SetAnswer(nWordNum);
	}
}

//=============================================================================
// �����̔ԍ��ݒ�̏���
//=============================================================================
void CTube::SetAnswer(int nAnswer)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	m_nAnswerModelNum = nAnswer;

	if (m_pAnswerModel == NULL)
	{	// ������3�����W�܂����ꍇ�ꍇ
		D3DXVECTOR2 AnswerSize = {};
		//int nAnswerNum = 
		if (NumPlayer == 1)
		{	// 1�l�v���C�̏ꍇ
			m_AnswerPos = POS_ANSWER_001;
			AnswerSize = SIZE_ANSWER_001;
		}
		else if (NumPlayer != 1)
		{	// 1�l�v���C����Ȃ��ꍇ
			m_AnswerPos = POS_ANSWER_002;
			AnswerSize = SIZE_ANSWER_002;
		}

		//	�����ō��郂�f�����܂Ƃ߂��摜�ɕς���
		m_pAnswerModel = CScene2D::Create(m_AnswerPos, "WORD", 3);
		m_pAnswerModel->SetWidthHeight(AnswerSize.x, AnswerSize.y);	// �T�C�Y�ݒ�
		m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f + ((nAnswer / 5) * 0.1f), 0.0f + ((nAnswer % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nAnswer / 5) * 0.1f), 0.2f + ((nAnswer % 5) * 0.2f)));
	}
}
//=============================================================================
// �S�Ă̕������폜
//=============================================================================
void CTube::AllDelete(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->Uninit();
			m_apWord[nCntWord] = NULL;
		}
	}

	if (m_pAnswerModel != NULL) { m_pAnswerModel->Uninit(); m_pAnswerModel = NULL; }
}

//=============================================================================
// �ꕔ�̕������폜
//=============================================================================
void CTube::Delete(int nID)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD - 1; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL&& m_apWord[nCntWord + 1] != NULL)
		{
			int nNum = CGame::GetPlayer(nID)->GetWordManager()->GetWordNum(nCntWord + 1);	// �������擾
			m_apWord[nCntWord]->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));

			if (m_pAnswerModel != NULL)
			{
				m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));
			}
		}
		

		else if (m_apWord[nCntWord] != NULL && m_apWord[nCntWord + 1] == NULL)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				m_apWord[nCntWord]->Uninit();
				m_apWord[nCntWord] = NULL;
			}
		}

		if (m_apWord[0] == NULL)
		{
			if (m_pAnswerModel != NULL)
			{
				m_pAnswerModel->Uninit();
				m_pAnswerModel = NULL;
			}
		}
	}
}

//=============================================================================
// ����������ʒu�ɏW�߂�Tex�𐶐�
//=============================================================================
void CTube::Collect(void)
{
	int nCntNum = 0;

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->SetWidthHeight(m_apWord[nCntWord]->GetSize(0) - WORD_SCALE, m_apWord[nCntWord]->GetSize(1) - WORD_SCALE);
			Approach(m_apWord[nCntWord]->GetPosition(), m_AnswerPos, nCntWord);
		}
		else if (m_apWord[nCntNum] == NULL) { nCntNum++; }
	}

	if (nCntNum == MAX_WORD)
	{
		m_bModelTexFlag = false;

		if (m_pAnswerModel != NULL)
		{
			if (NOT_NUM == m_nAnswerModelNum)
			{	// �S�~���f����tex���o��
				m_pAnswerModel->BindTexture("�S�~_���f��");
				m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
			}
			else if (NOT_NUM != m_nAnswerModelNum)
			{	// �����̃��f�����o��
				m_pAnswerModel->BindTexture("���f��_TEX");
				m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * 0.125f), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
					D3DXVECTOR2(0.125f + ((m_nAnswerModelNum / 10) * 0.125f), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
			}
			m_pAnswerModel->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// �v���C���[�ɏW�܂�̏���
//=============================================================================
void CTube::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �v���C���[�ɋ߂Â���
	move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.y - Pos.y)) * MOVE;
	move.y = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.y - Pos.y)) * MOVE;

	if (m_apWord[nNum] != NULL) 
	{
		Pos.x += move.x;
		Pos.y += move.y;

		// �͈͂𑪂�
		float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

		m_apWord[nNum]->SetPosition(Pos);

		// �͈͓��Ȃ�j�� Flag��߂�
		if (fDistance < AREA)
		{	// �������ɓ�������
			if (m_apWord[nNum] != NULL)
			{
				m_apWord[nNum]->Uninit();
				m_apWord[nNum] = NULL;
			}
		}

	}
}

//=============================================================================
// �|�C���g�̏���
//=============================================================================
void CTube::SetPoint(int nPoint, int nNum, bool bPoint)
{
	CPoint *pPoint = NULL;
	if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(nNum); }
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* �`���[�g���A���̍�Ƃɂ�肩�������ꍇ �����Ń`���[�g���A������|�C���g���擾 */ }

	if (pPoint != NULL)
	{
		if (bPoint == false) { pPoint->AddPoint(nPoint); }
		else if (bPoint == true) { pPoint->SubtractionPoint(nPoint); }
	}
}