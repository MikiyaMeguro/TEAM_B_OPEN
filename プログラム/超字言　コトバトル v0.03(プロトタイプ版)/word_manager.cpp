//=============================================================================
//
// �����̊Ǘ����� [word_manager.cpp]
// Author : ���� �x
//
//=============================================================================
#include "word_manager.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "sceneX.h"
#include "debugProc.h"
#include "game.h"

#include "bullet.h"
#include "CameraManager.h"
//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWordManager::CWordManager()
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{	// �Ǘ��̒��g��������
		m_aWord[nCntWord].nNum = 99;
		m_aWord[nCntWord].cWord = "NULL";
		m_aWord[nCntWord].bClearFlag = false;
	}
	m_nCntNum = 0;			// �񐔂̃J�E���g
	m_nCreateType = 0;		// ��������^�C�v
	m_nCntaAnswer = 0;		// �����Ƃ̔�r���č����Ă��鐔
	m_nPlayerID = 0;		// �v���C���[�����Ԃ��̕ۑ�
	m_bPress = false;		// �w�肵�������ȏ������Ȃ��t���O

	for (int nCntAnswer = 0; nCntAnswer < MAX_ANSWER; nCntAnswer++)
	{	// �����̏�����(�����̓���)
		if (nCntAnswer == 0) { AnswerNum[nCntAnswer] = D3DXVECTOR3(7.0f, 40.0f, 30.0f); }			// ��
		else if (nCntAnswer == 1) { AnswerNum[nCntAnswer] = D3DXVECTOR3(27.0f, 19.0f, 45.0f); }		// �z�c
		else if (nCntAnswer == 2) { AnswerNum[nCntAnswer] = D3DXVECTOR3(17.0f, 7.0f, 3.0f); }		// ��
		else if (nCntAnswer == 3) { AnswerNum[nCntAnswer] = D3DXVECTOR3(27.0f, 39.0f, 45.0f); }		// �v����
		else if (nCntAnswer == 4) { AnswerNum[nCntAnswer] = D3DXVECTOR3(20.0f, 1.0f, 27.0f); }		// �i�C�t
		else if (nCntAnswer == 5) { AnswerNum[nCntAnswer] = D3DXVECTOR3(39.0f, 45.0f, 9.0f); }		// �����S
		else if (nCntAnswer == 6) { AnswerNum[nCntAnswer] = D3DXVECTOR3(3.0f, 24.0f, 7.0f); }		// �G��
		else if (nCntAnswer == 7) { AnswerNum[nCntAnswer] = D3DXVECTOR3(15.0f, 1.0f, 35.0f); }		// �^�C��
		else if (nCntAnswer == 8) { AnswerNum[nCntAnswer] = D3DXVECTOR3(15.0f, 1.0f, 9.0f); }		// ����
		else if (nCntAnswer == 9) { AnswerNum[nCntAnswer] = D3DXVECTOR3(9.0f, 1.0f, 45.0f); }		// ����
	}
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWordManager::~CWordManager() {}

//=============================================================================
// ����������
//=============================================================================
void CWordManager::Init()
{

}

//=============================================================================
// �I������
//=============================================================================
void CWordManager::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CWordManager::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CreateOblDebug();		// �����ŕ����̊Ǘ�(�f�o�b�N�p)

	if (m_bPress == true)
	{
		if (m_nCntaAnswer == 0)
		{
			for (int nCntAnswer = 0; nCntAnswer < MAX_ANSWER; nCntAnswer++)
			{	// �����̐�������
				for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
				{	// ���Ƃ̔�r
					if (AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; }
					else if (AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; }
					else if (AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; }
				}

				if (m_bAnswer[0] == true && m_bAnswer[1] == true && m_bAnswer[2] == true) { m_nCntaAnswer = MAX_WORD; }
				else if (m_nCntaAnswer < MAX_WORD)
				{
					for (int nCount = 0; nCount < MAX_WORD; nCount++)
					{
					m_bAnswer[nCount] = false;
					}
				}

				if (m_nCntaAnswer == MAX_WORD) { m_nCreateType = nCntAnswer; return; }
				else { m_nCntaAnswer = 0; }
			}
		}

		//�e�X�g
		//if (pInputKeyboard->GetTrigger(DIK_LSHIFT))
		//{	// �e�̐���
		//	BulletCreate(0);
		//}
	}

#ifdef _DEBUG
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		CDebugProc::Print("cc", "m_aWord = ", m_aWord[nCntWord].cWord);
	}
#endif
}

//=============================================================================
// �ݒ菈��
//=============================================================================
void CWordManager::SetWord(int nType)
{
	if (m_nCntNum < MAX_WORD)
	{
		m_aWord[m_nCntNum].nNum = nType;
		WordDebug(m_nCntNum);
		CGame::GetTube(m_nPlayerID)->SetWordNum(nType, m_nCntNum);
		m_nCntNum++;
	}
}

//=============================================================================
// ���Z�b�g�֐�
//=============================================================================
void CWordManager::Reset(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		m_aWord[nCntWord].nNum = 99;
		m_aWord[nCntWord].cWord = "NULL";
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_bAnswer[nCount] = false;
	}

	m_nCntaAnswer = 0;
	m_nCntNum = 0;
	m_bPress = false;
}

//=============================================================================
// �����̍폜
//=============================================================================
void CWordManager::Delete(void)
{
	//if (CManager::GetInputKeyboard()->GetTrigger(DIK_LCONTROL))
	{
		if (m_nCntNum < 3)
		{	// 3�ȉ��̏ꍇ
			if (m_nCntNum > 0)
			{
				m_nCntNum--;
				if (CGame::GetTube(m_nPlayerID) != NULL)
				{	// �����ۊǂ�NULL����Ȃ��ꍇ
					CGame::GetTube(m_nPlayerID)->Delete(m_nPlayerID);
				}
				m_aWord[0].nNum = 99;	// ��̏�Ԃ�
				for (int nCntWord = 0; nCntWord < MAX_WORD - 1; nCntWord++)
				{
					m_aWord[nCntWord].nNum = m_aWord[nCntWord + 1].nNum;
					WordDebug(nCntWord);
				}
			}
		}
	}
}
//=============================================================================
// �e�̐���
//=============================================================================
void CWordManager::BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle)
{
	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (CGame::GetPlayer(nID) != NULL)
	{//�w�肵���v���C���[�����݂��Ă����
		CCamera* pCam = pCameraManager->GetCamera(CGame::GetPlayer(nID)->GetCameraName());
		D3DXVECTOR3 BulletPos = BulletMuzzle;
		D3DXVECTOR3 BulletRot = CGame::GetPlayer(nID)->GetRotation();
		if (pCam != NULL)
		{
			BulletRot = D3DXVECTOR3(-pCam->GetRotation().x, pCam->GetRotation().y, 0.0f);
		}

		if (m_bPress == true)
		{
			if (m_nCntaAnswer == MAX_WORD)
			{	// // �w�肵�������Ȃ�e�𐶐�����
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletPos, BulletRot, (CLoad::MODEL)m_nCreateType, 5.0f, 100, nID);
				}
			}
			else if (m_nCntaAnswer < MAX_WORD)
			{	// �S�~���f�����o��
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletPos, BulletRot, CLoad::MODE_DUST, 5.0f, 100, nID);
				}
			}

			Reset();		// �ݒ��߂�
			if (CGame::GetTube(m_nPlayerID) != NULL)
			{
				CGame::GetTube(m_nPlayerID)->AllDelete();
			}
		}
		else if(m_bPress == false)
		{	// ����ȊO�̏ꍇ
			if (m_nCntNum > 0)
			{
				CWordBullet* pWord = CWordBullet::Create();

				if (pWord != NULL)
				{
					pWord->Set(BulletPos, BulletRot, 5.0f, 100, GetWordNum(0), nID);
				}

				Delete();		// �������ꕔ�폜

			}
		}
	}
}

//=============================================================================
// �����Ő����̃f�o�b�N�p(�����Ǘ�)
//=============================================================================
void CWordManager::CreateOblDebug(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	if (m_bPress == false)
	{
		if (pKey->GetPress(DIK_1))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 0;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 1;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 2;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 3;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 4;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_2))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 5;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 6;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 7;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 8;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 9;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_3))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 10;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 11;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 12;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 13;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 14;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_4))
		{	// ���s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 15;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 16;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 17;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 18;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 19;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_5))
		{	// �ȍs
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 20;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 21;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 22;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 23;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 24;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_6))
		{	// �͍s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 25;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 26;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 27;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 28;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 29;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_7))
		{	// �܍s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 30;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 31;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 32;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 33;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 34;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_8))
		{	// ��s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 35;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 36;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 37;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_9))
		{	// ��s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 38;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 39;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 40;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ��
				m_aWord[m_nCntNum].nNum = 41;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ��
				m_aWord[m_nCntNum].nNum = 42;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_0))
		{	// ��s
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ��
				m_aWord[m_nCntNum].nNum = 43;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ��
				m_aWord[m_nCntNum].nNum = 44;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ��
				m_aWord[m_nCntNum].nNum = 45;
				m_aWord[m_nCntNum].cWord = "��";
				m_nCntNum++;
			}
		}
	}

	if (m_nCntNum == MAX_WORD)
	{	// �ő�Ȃ炱��ȏ㐔��������Ȃ�
		m_bPress = true;
	}
}

//=============================================================================
// �����̃f�o�b�N�p
//=============================================================================
void CWordManager::WordDebug(int nCntNum)
{
	if (m_aWord[nCntNum].nNum == 0)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 1)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 2)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 3)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 4)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 5)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 6)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 7)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 8)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 9)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 10)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 11)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 12)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 13)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 14)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 15)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 16)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 17)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 18)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 19)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 20)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 21)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 22)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 23)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 24)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 25)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 26)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 27)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 28)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 29)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 30)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 31)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 32)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 33)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 34)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 35)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 36)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 37)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 38)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 39)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 40)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 41)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 42)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 43)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 44)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 45)
	{	// ��
		m_aWord[nCntNum].cWord = "��";
	}
	else if (m_aWord[nCntNum].nNum == 99)
	{	// ��̏��
		m_aWord[nCntNum].cWord = "NULL";
	}
}