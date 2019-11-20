//=============================================================================
//
// �^�C�}�[���� [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "time.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// X�̒��S���W
#define TIMER_SPACE			(30.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_POSITION_Y	(70.0f)							// �^�C�}�[��Y���W(�Q�[������)
#define GAME_TIME			(130)							// �Q�[���J�n���̎���
#define GAME_TIME_MAX		(9)							// �Q�[���̎��ԍő吔
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 70.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define TIME_POS_2P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(2P�����̏ꍇ)
#define TIME_POS_3P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 140.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(3P�����̏ꍇ)
#define TIME_POS_4P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 40.0f, 380.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define WAIT_TIME_END		(180)							// �҂�����
//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
int						CTime::m_nTime = 0;
int						CTime::m_nTimeNumCount = 0;
int						CTime::m_nTimeCount = 0;
bool					CTime::m_bCountFlag = true;			//���Ԃ��J�E���g���邩
int						CTime::m_nTimeOld = 0;
int						CTime::m_nStageChange = 1;
int						CTime::m_nTimeOne = 3;
//=============================================================================
// ��������
//=============================================================================
CTime *CTime::Create(int nNumPlayer)
{
	CTime *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{//���I�m��
		pTime = new CTime;

		//NULL�`�F�b�N
		if (pTime != NULL)
		{
			//�ʒu�̐ݒ�
			if (nNumPlayer == 1) { pTime->m_pos = TIME_POS_1P; }
			if (nNumPlayer == 2 && m_nTimeNumCount == 0) { pTime->m_pos = TIME_POS_1P; }
			else if (nNumPlayer == 2 && m_nTimeNumCount == 1) { pTime->m_pos = TIME_POS_2P; }
			if (nNumPlayer == 3) { pTime->m_pos = TIME_POS_3P; }
			if (nNumPlayer == 4) { pTime->m_pos = TIME_POS_4P; }
			pTime->m_nNumPlayer = nNumPlayer;

			//����������
			pTime->Init();
		}
	}

	return pTime;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTime::CTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
	m_nTimeNum = 3;
	m_nWaitTime = 0;
	m_pColon = NULL;
	m_bStart = false;
	m_bStageCreate = false;
	m_nStageChange = 1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTime::~CTime() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTime::Init(void)
{
	int nTexData = 0;
	m_nTime = 0;
	m_nTimeOld = GAME_TIME - 30;
	m_nTimeNum = PowerCalculation(m_nTime, 0);
	m_nTimeOne = 3;

	// ���̔w�i
	if (m_nNumPlayer == 1 || m_nNumPlayer == 2 && m_nTimeNumCount == 0)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 50.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_nNumPlayer == 2 && m_nTimeNumCount == 1)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 420.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_nNumPlayer == 3)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 420.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	if (m_nNumPlayer == 4)
	{
		CScene2D *pBg = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 370.0f, 0.0f), "BG_FREAME", 5);
		pBg->SetWidthHeight(80.0f, 60.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// �^�C�}�[�����ݒ�
			m_apNumber[nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// �R���܂�
				m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntTime), m_pos.y, m_pos.z), 0);
			}
			else if (nCntTime == 2)
			{	// 3����
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(((m_pos.x - 20.0f) - TIMER_SPACE * nCntTime), m_pos.y, m_pos.z), 0);
			}
		}
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);
	}

	if (m_nNumPlayer == 1 || m_nNumPlayer == 2 && m_nTimeNumCount == 0)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 18.0f, 70.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Time�̃��S
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 35.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

		if (m_nNumPlayer == 2) { m_nTimeNumCount++; }
	}
	else if (m_nNumPlayer == 2 && m_nTimeNumCount == 1)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 18.0f, 440.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Time�̃��S
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 405.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		m_bStart = true;
	}
	else if (m_nNumPlayer == 3)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 82.0f, 440.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Time�̃��S
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 100.0f, 405.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	if (m_nNumPlayer == 4)
	{
		if (m_pColon == NULL)
		{
			m_pColon = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 18.0f, 380.0f, 0.0f), "COLON", 5);
			m_pColon->SetWidthHeight(15.0f, 20.0f);
			m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}

		// Time�̃��S
		CScene2D *pLogo = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 350.0f, 0.0f), "TIME", 5);
		pLogo->SetWidthHeight(40.0f, 20.0f);
		pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTime::Uninit(void)
{
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
		{	// �^�C�}�[�̔j��
			if (m_apNumber[nCntTime] != NULL)
			{
				m_apNumber[nCntTime]->Uninit();
				m_apNumber[nCntTime] = NULL;
			}
		}
	}

	if (m_pColon != NULL)
	{
		m_pColon->Uninit();
		m_pColon = NULL;
	}

	m_nTimeNumCount = 0;

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTime::Update(void)
{
	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// �f�o�b�N�p

	if ((GameMode == CManager::MODE_GAME) || (GameMode == CManager::MODE_TUTORIAL))
	{//��������
	 //�Q�[��
		if (m_bStart == false)
		{
			if (m_bCountFlag == true)
			{
				m_nTimeCount++;
				TimeManagement();	// ���Ԃ̊Ǘ�
			}
		}

		int nTexData = 0;
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);

		if (m_nTime == 0 && m_nTimeOne == 0 && GameMode == CManager::MODE_GAME)
		{	// �Q�[���I��
			m_nWaitTime++;	// �҂����Ԃ̉��Z
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				CFade::SetFade(CManager::MODE_RESULT, CFade::FADE_OUT);
			}
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}

	if (m_pColon != NULL)
	{
		m_pColon->Draw();
	}
}

//=============================================================================
// �^�C�}�[��Texture�Ǘ�
//=============================================================================
void CTime::TexTime(int nTexData, int nTimeOne)
{
	nTexData = m_nTime;

	for (int nCntTime = 0; nCntTime < TIME_MAX; nCntTime++)
	{// �e�N�X�`���ɔ��f

		if (m_apNumber[nCntTime] != NULL)
		{
			if (nCntTime < 2)
			{
				m_apNumber[nCntTime]->SetNumber(nTexData);
				nTexData /= 10;
			}
			else if (nCntTime == 2)
			{
				m_apNumber[nCntTime]->SetNumber(nTimeOne);
				nTexData /= 10;
			}
			// �F�̐ݒ�
			if (m_nTime <= 10 && m_nTimeOne == 0)
			{ // 10�b�ȉ� �F��Ԃ�
				m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
				if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f)); }
			}
			else
			{
				m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				if (m_pColon != NULL) { m_pColon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
			}
		}
	}
}
//=============================================================================
// �^�C�����Z����
//=============================================================================
void CTime::AddTime(int nTime)
{
	if (m_nTime > 0)
	{
		m_nTimeOne += nTime;
	}

	if (GAME_TIME_MAX < m_nTimeOne) { m_nTimeOne = GAME_TIME_MAX; }
}
//=============================================================================
// �ׂ���̌v�Z
//=============================================================================
int CTime::PowerCalculation(int nData, int nOperation)
{
	int nNum = 1;
	int nPower = (int)std::pow(POWER_X, nNum);
	int nDataNum = nData;
	while ((nDataNum / nPower) != 0)
	{
		nNum++;
		nPower = (int)std::pow(POWER_X, nNum);		// �ׂ��悷��(����O��Ȃ�)
		if (nOperation == 0)
		{	// ��������
			if (nNum >= TIME_MAX) { nNum = TIME_MAX; }
		}
	}
	return nNum;
}

//=============================================================================
// ���Ԃ̊Ǘ�
//=============================================================================
void CTime::TimeManagement(void)
{
	if (m_nTime == 0 && m_nTimeOne == 0) {m_nTime = 0; return; }

	if ((m_nStageChange % 60) == 0 && m_bStageCreate == false)
	{	// 30�b���ƂɃX�e�[�W���ς��
		m_bStageCreate = true;
		int nStageNum = (m_nStageChange / 60);
		CManager::GetGame()->SetStage(CGame::GetNumStage(),nStageNum);
	}

	if (m_nTimeCount % 60 == 0)
	{// 1�b���ƂɌ��Z(��������)
		m_nTime--;
		m_nStageChange++;
		m_bStageCreate = false;

		if (m_nTime < 0) { m_nTime = 59; m_nTimeOne -= 1; }
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// �f�o�b�N�p
//=============================================================================
void CTime::DebugKey(void)
{
	// �f�o�b�N�p
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD0))
	{	// �������ԉ��Z
		AddTime(1);
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// ���U���g��ʂ�
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}