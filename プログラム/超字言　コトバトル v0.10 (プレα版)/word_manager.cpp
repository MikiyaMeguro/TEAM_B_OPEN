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
#include "SetWord.h"

#include "bullet.h"
#include "CameraManager.h"

#include "sound.h"
//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
D3DXVECTOR3 *CWordManager::m_AnswerNum = &D3DXVECTOR3(99.0f, 99.0f, 99.0f);
int CWordManager::m_nAnswerDataNum = 0;
D3DXVECTOR3 *CWordManager::m_Scale = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR3 *CWordManager::m_rot = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
int *CWordManager::m_type = 0;
int *CWordManager::m_nAnswerTypeModel = 0;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWordManager::CWordManager()
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{	// �Ǘ��̒��g��������
		m_aWord[nCntWord].nNum = NOT_NUM;
		m_aWord[nCntWord].cWord = "NULL";
		m_aWord[nCntWord].bClearFlag = false;
	}
	m_nCntNum = 0;			// �񐔂̃J�E���g
	m_nCreateType = NOT_NUM;// ��������^�C�v
	m_nCntaAnswer = 0;		// �����Ƃ̔�r���č����Ă��鐔
	m_nPlayerID = 0;		// �v���C���[�����Ԃ��̕ۑ�
	m_bPress = false;		// �w�肵�������ȏ������Ȃ��t���O
	m_bSearch = false;		// �T�[�`���J�n���鎞�̃t���O

	m_fAnswerData = NULL;
	m_Scale = NULL;
	m_type = NULL;
	m_nAnswerTypeModel = NULL;
	m_rot = NULL;
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
	if (m_AnswerNum != NULL)
	{
		delete[] m_AnswerNum;
		m_AnswerNum = NULL;
	}

	if (m_fAnswerData != NULL && m_bSearch == true)
	{
		delete[] m_fAnswerData;
		m_fAnswerData = NULL;
	}

	if (m_Scale != NULL)
	{
		delete[] m_Scale;
		m_Scale = NULL;
	}

	if (m_rot != NULL)
	{
		delete[] m_rot;
		m_rot = NULL;
	}

	if (m_type != NULL)
	{
		delete[] m_type;
		m_type = NULL;
	}

	if (m_nAnswerTypeModel != NULL)
	{
		delete[] m_nAnswerTypeModel;
		m_nAnswerTypeModel = NULL;
	}
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

	if (m_nCntNum == MAX_WORD)
	{	// �ő�Ȃ炱��ȏ㐔��������Ȃ�
		m_bPress = true;
	}

	if (m_bPress == true)
	{
		if (m_nCntaAnswer == 0)
		{
			for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
			{	// �����̐�������
				for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
				{	// ���Ƃ̔�r
					if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; }
					else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; }
					else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; }
				}

				if (m_bAnswer[0] == true && m_bAnswer[1] == true && m_bAnswer[2] == true) { m_nCntaAnswer = MAX_WORD; }
				else if (m_nCntaAnswer < MAX_WORD)
				{
					for (int nCount = 0; nCount < MAX_WORD; nCount++)
					{
						m_bAnswer[nCount] = false;
					}
				}

				if (m_nCntaAnswer == MAX_WORD)
				{
					m_nCreateType = nCntAnswer;
					if (CGame::GetTube(m_nPlayerID) != NULL) { CGame::GetTube(m_nPlayerID)->SetAnswer(m_nCreateType); }
					return;
				}
				else { m_nCntaAnswer = 0; }
			}

			if (m_nCreateType > m_nAnswerDataNum) { if (CGame::GetTube(m_nPlayerID) != NULL) {
				CGame::GetTube(m_nPlayerID)->SetAnswer(NOT_NUM); } }
		}

		//�e�X�g
		//if (pInputKeyboard->GetTrigger(DIK_LSHIFT))
		//{	// �e�̐���
		//	BulletCreate(0);
		//}
	}

	if (m_nCntNum != 2 && m_bSearch == true)
	{ // �����Ă��镶����2�����ȊO�Ȃ�T�[�`�̃t���O��ύX
		m_bSearch = false;
		if (m_fAnswerData != NULL)
		{
			delete[] m_fAnswerData;
			m_fAnswerData = NULL;
		}
		//*m_fAnswerData = 99.0f;		// ��̔ԍ��������
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
		if (CGame::GetTube(m_nPlayerID) != NULL)
		{	// NULL�`�F�b�N
			CGame::GetTube(m_nPlayerID)->SetWordNum(nType, m_nCntNum);
		}
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
		m_aWord[nCntWord].nNum = NOT_NUM;
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
	if (m_nCntNum > 0)
	{
		if (m_nCntNum < 3)
		{	// 3�ȉ��̏ꍇ
			{
				m_nCntNum--;
				if (CGame::GetTube(m_nPlayerID) != NULL)
				{	// �����ۊǂ�NULL����Ȃ��ꍇ
					CGame::GetTube(m_nPlayerID)->Delete(m_nPlayerID);
				}
				m_aWord[0].nNum = NOT_NUM;	// ��̏�Ԃ�
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
// �e�̐���  Editor : Kodama Yuto
//=============================================================================
void CWordManager::BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle, D3DXVECTOR3 BulletRot)
{

	CSound *pSound = CManager::GetSound();		//	���̎擾

	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (CGame::GetPlayer(nID) != NULL)
	{//�w�肵���v���C���[�����݂��Ă����
		if (m_bPress == true)
		{
			if (m_nCntaAnswer == MAX_WORD)
			{	// �w�肵�������Ȃ�e�𐶐�����
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					int nType = m_nCreateType;
					m_nCreateType = m_nAnswerTypeModel[nType] + (int)CLoad::MODEL_CAR0;	//�e�ɂȂ郂�f���̈ʒu�܂Ń^�C�v�����炷
					//pModel->Set(BulletMuzzle, BulletRot, (CLoad::MODEL)m_nCreateType, (CModelBullet::BULLET_PROPERTY)m_type[nType] ,nID);
					pModel->Set(BulletMuzzle, BulletRot, (CLoad::MODEL)m_nCreateType, (CModelBullet::BULLET_PROPERTY)m_type[nType], nID, m_rot[nType]);
					pModel->SetModelScale(m_Scale[nType]);	//�傫���̐ݒ�
					m_nCreateType = NOT_NUM;

					if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[0])
					{
						pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET000);
					}
					else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[1])
					{
						pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET001);
					}
					else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[2])
					{
						pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET002);
					}
					else if ((CModelBullet::BULLET_PROPERTY)m_type[nType] == (CModelBullet::BULLET_PROPERTY)m_type[3])
					{
						pSound->PlaySound(CSound::SOUND_LABEL_SE_BULLET003);
					}
				}
			}
			else if (m_nCntaAnswer < MAX_WORD)
			{	// �S�~���f�����o��
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletMuzzle, BulletRot, CLoad::MODE_DUST, CModelBullet::TYPE_NORMAL, nID);
					pModel->SetModelScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));//�傫���̐ݒ�
				}
			}

			//�u�����h�����Œe�ł����[�V�����Ɉڍs
			CGame::GetPlayer(nID)->SetMotion(CPlayer::MOTION_UPPER_SHOT, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
			CGame::GetPlayer(nID)->SetMotion(CPlayer::MOTION_LOWER_SHOT, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);

			Reset();		// �ݒ��߂�
			if (CGame::GetTube(m_nPlayerID) != NULL)
			{//���N���X���̕��������폜
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
					pWord->Set(BulletMuzzle, BulletRot, 5.0f, 100, GetWordNum(0), nID);
				}

				Delete();		// �������ꕔ�폜

			}
		}
	}
}

//=============================================================================
// Text����ǂݍ��� �����̊��蓖��
//=============================================================================
void CWordManager::SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int type, int Model)
{
	m_AnswerNum[nNumModel] = AnswerNum;
	m_Scale[nNumModel] = scale;
	m_type[nNumModel] = type;
	m_nAnswerTypeModel[nNumModel] = Model;
	m_rot[nNumModel] = rot;
}

//=============================================================================
// Text����ő吔�ǂݍ��� ���I�m��
//=============================================================================
void CWordManager::SetWordAnswerNum(int nAnswerNum)
{
	m_nAnswerDataNum = nAnswerNum;
	m_AnswerNum = new D3DXVECTOR3[m_nAnswerDataNum];
	m_Scale = new D3DXVECTOR3[m_nAnswerDataNum];
	m_rot = new D3DXVECTOR3[m_nAnswerDataNum];
	m_type = new int[m_nAnswerDataNum];
	m_nAnswerTypeModel = new int[m_nAnswerDataNum];
}

//=============================================================================
// �����̑g�ݍ��킹�������Ă��邩�ǂ������擾
//=============================================================================
int CWordManager::SearchWord(void)
{
	if (m_nCntNum == 2 /*&& m_bSearch == false*/)
	{	// �E�����������Q�����̏ꍇ
		int nData = 0;
		if (m_fAnswerData == NULL)
		{
			m_fAnswerData = new float[m_nAnswerDataNum];
		}

		for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
		{	// �����̐�������
			int nAnswer = 0;
			for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
			{	// ���Ƃ̔�r
				if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; nAnswer++; }

				if (nAnswer == 2)
				{	// �����Ă��鏊��2�ӏ��̏ꍇ
					for (int nCntData = 0; nCntData < MAX_WORD; nCntData++)
					{
						if (m_bAnswer[nCntData] == false)
						{	// false�̏ꏊ��T�� ��������������
							if (nCntData == 0) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].x; }
							else if (nCntData == 1) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].y; }
							else if (nCntData == 2) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].z; }
							nData++;		// �񐔂𑝂₷
						}
					}
					nAnswer = 0;	// �����Ă���񐔂����Z�b�g
				}
			}

			for (int nCount = 0; nCount < MAX_WORD; nCount++)
			{	// �S��false�ɖ߂�
				m_bAnswer[nCount] = false;
			}
		}

		m_bSearch = true;		// Flag��ture��
		return nData;			// �����̏o����
	}

	return 0;
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
	else if (m_aWord[nCntNum].nNum == NOT_NUM)
	{	// ��̏��
		m_aWord[nCntNum].cWord = "NULL";
	}
}