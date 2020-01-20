//=============================================================================
//
// �^�C�}�[���� [tutotime.cpp]
// Author : Meguroo Mikiya
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "tutotime.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"
#include "charactor.h"
#include "result.h"
#include "point.h"
#include "sceneBillboard.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// X�̒��S���W
#define TIMER_SPACE1P2P		(18.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_SPACE3P4P		(22.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_WIDTH1P2P		(40.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_WIDTH3P4P		(30.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_HEIGHT1P2P	(20.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_HEIGHT3P4P	(15.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_POSITION_Y	(40.0f)							// �^�C�}�[��Y���W(�Q�[������)
#define GAME_TIME			(130)							// �Q�[���J�n���̎���
#define GAME_TUTOTIME_MAX		(9)								// �Q�[���̎��ԍő吔
#define POWER_X				(10)
#define TIME_POS_1P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 30.0f, 70.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define TIME_POS_2P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 50.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(2P�����̏ꍇ)
#define TIME_POS_3P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 150.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(3P�����̏ꍇ)
#define TIME_POS_4P			(D3DXVECTOR3(SCREEN_WIDTH / 2 + 160.0f, 380.0f, 0.0f))	// �������Ԃ̈ʒu(4P�����̏ꍇ)
#define WAIT_TIME_END		(180)							// �҂�����

#define COUNTDOWN_SCALE		(3.5f)							// �҂�����
#define DEFAULT_SIZE		(D3DXVECTOR3(10.0f, 15.0f, 0.0f))	// �f�t�H���g�T�C�Y
#define DEFAULT_SIZE1P2P	(D3DXVECTOR3(12.0f, 20.0f, 0.0f))	// �f�t�H���g�T�C�Y
#define DEFAULT_SIZE3P4P	(D3DXVECTOR3(12.0f, 20.0f, 0.0f))	// �f�t�H���g�T�C�Y
#define SCALE_CHANGE_TIME	(10)								// �X�P�[���ω��̎���
#define SCALE_UI			(100)								// UI�̑傫��
#define SCALE_UI_WIDTH		(200)								// UI�̑傫��
#define FEVER_COLOR			(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))
//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================
int						CTutoTime::m_nTime = 0;
int						CTutoTime::m_nTimeCount = 0;
bool					CTutoTime::m_bCountFlag = true;			//���Ԃ��J�E���g���邩
int						CTutoTime::m_nTimeOld = 0;
int						CTutoTime::m_nTimeOne = 3;
int						CTutoTime::m_nStageNum = 0;
//=============================================================================
// ��������
//=============================================================================
CTutoTime *CTutoTime::Create(int nNumPlayer)
{
	CTutoTime *pTime = NULL;

	//NULL�`�F�b�N
	if (pTime == NULL)
	{//���I�m��
		pTime = new CTutoTime;

		//NULL�`�F�b�N
		if (pTime != NULL)
		{
			//�ʒu�̐ݒ�
#if 0
			if (nNumPlayer == 1) { pTime->m_pos = TIME_POS_1P; }
			if (nNumPlayer == 2 && m_nTimeNumCount == 0) { pTime->m_pos = TIME_POS_1P; }
			else if (nNumPlayer == 2 && m_nTimeNumCount == 1) { pTime->m_pos = TIME_POS_2P; }
			if (nNumPlayer == 3) { pTime->m_pos = TIME_POS_3P; }
			if (nNumPlayer == 4) { pTime->m_pos = TIME_POS_4P; }
#endif
			pTime->m_pos = D3DXVECTOR3(20.0f, 80.0f, 0.0f);

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
CTutoTime::CTutoTime(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nTimeCount = 0;
	m_nTimeNum = 3;
	m_nWaitTime = 0;
	m_StageCounter = 0;
	//�l�̏�����
	m_bCntDown = false;
	m_ScaleCounter = 0;
	m_fScale = 0;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nColorFlash = 0;
	m_nType = 0;
	m_fWidth = 100;
	m_fHeight = 100;
	m_bEndCntDown = false;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_pPlayer[nCntPlayer] = NULL;			// �v���C���[���擾
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTutoTime::~CTutoTime() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CTutoTime::Init(void)
{
	int nTexData = 0;
	m_nTime = 0;
	m_nTimeOld = GAME_TIME - 30;
	m_nTimeNum = PowerCalculation(m_nTime, 0);
	m_nTimeOne = 3;
	m_StageCounter = 0;

	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{	// �^�C�}�[�����ݒ�
			m_apNumber[nCntTime] = new CNumber;
			float Space = 0.0f;
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				Space = TIMER_SPACE1P2P;
			}
			else
			{
				Space = TIMER_SPACE3P4P;
			}


			if (nCntTime < 2)
			{	// �R���܂�
				//m_apNumber[nCntTime]->Init(D3DXVECTOR3((m_pos.x - Space * nCntTime), m_pos.y, m_pos.z),1);
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}
			else if (nCntTime == 2)
			{	// 3����
				//m_apNumber[nCntTime]->Init(D3DXVECTOR3(((m_pos.x - 10.0f) - Space * nCntTime), m_pos.y, m_pos.z),2);
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}
			if (m_nNumPlayer == 1 || m_nNumPlayer == 2)
			{
				//m_apNumber[nCntTime]->SetSize(D3DXVECTOR2(TIMER_WIDTH1P2P, TIMER_HEIGHT1P2P), D3DXVECTOR2((m_pos.x - 10.0f) - Space * nCntTime, m_pos.y));
				m_apNumber[nCntTime]->Init(D3DXVECTOR3(100.0f, 200.0f, 0.0f), 0);
			}
			else
			{
				m_apNumber[nCntTime]->SetSize(D3DXVECTOR2(100, 100), D3DXVECTOR2(100.0f, 200.0f));
			}
		}
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);
	}

	//�J�E���g�_�E������
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_pScene2D[nCnt] = NULL;
	}

	if (m_nNumPlayer == 1)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2+50, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
	}
	else if (m_nNumPlayer == 2)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
	}
	else if (m_nNumPlayer == 3)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
	}
	if (m_nNumPlayer == 4)
	{
		//�J�E���g�_�E���̈ʒu�ݒ�
		m_pScene2D[0] = CScene2D::Create(D3DXVECTOR3(320.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[0]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[1] = CScene2D::Create(D3DXVECTOR3(940.0f, 200.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[1]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[2] = CScene2D::Create(D3DXVECTOR3(320.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[2]->SetWidthHeight(m_fWidth, m_fHeight);
		m_pScene2D[3] = CScene2D::Create(D3DXVECTOR3(940.0f, 570.0f, m_pos.z), "COUNTDOWN0");
		m_pScene2D[3]->SetWidthHeight(m_fWidth, m_fHeight);
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	// �v���C���[���擾
		m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(true);
		}
	}


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CTutoTime::Uninit(void)
{
	m_nStageNum = 0;
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
		{	// �^�C�}�[�̔j��
			if (m_apNumber[nCntTime] != NULL)
			{
				m_apNumber[nCntTime]->Uninit();
				m_apNumber[nCntTime] = NULL;
			}
		}
	}

	for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
	{
		if (m_pScene2D[nCnt] != NULL)
		{
			m_pScene2D[nCnt]->Uninit();
			m_pScene2D[nCnt] = NULL;
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CTutoTime::Update(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// �f�o�b�N�p

	if ((GameMode == CManager::MODE_GAME) && m_bEndCntDown == true || (GameMode == CManager::MODE_TUTORIAL) && m_bEndCntDown == true)
	{//��������
	 //�Q�[��
		if (m_bCountFlag == true)
		{
			m_nTimeCount++;
			TimeManagement();	// ���Ԃ̊Ǘ�
		}

		int nTexData = 0;
		// �����̃e�N�X�`���ݒ�
		TexTime(nTexData, m_nTimeOne);

		if (m_nTime == 0 && m_nTimeOne == 0 && GameMode == CManager::MODE_GAME)
		{
			// �Q�[���I��
			m_nWaitTime++;	// �҂����Ԃ̉��Z
			if ((m_nWaitTime % WAIT_TIME_END) == 0)
			{
				CFade::SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
			}
		}
	}

	CountDown();	// �J�E���g�_�E������

	//�X�e�[�W���������^�C�}�[
	if (CGame::GetbStageSet() == true)
	{
		m_StageCounter++;
		if (m_StageCounter > 120)
		{
			CManager::GetGame()->SetCreateWord();
			m_StageCounter = 0;
			CGame::bStageSet(false);
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void CTutoTime::Draw(void)
{
	for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
	{
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->Draw();
		}
	}
}

//=============================================================================
// �J�E���g�_�E��
//=============================================================================
void CTutoTime::CountDown(void)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾

	//�J�E���g�_�E��
	if (m_bEndCntDown == false)
	{
		//�傫���ω�
		m_fScale += COUNTDOWN_SCALE;
		//�����x�グ
		if (m_fScale > 200 && m_fScale <= 250)
		{
			//�J�E���^�[���Z
			if (m_bCntDown == false)
			{
				m_Col.a -= 0.1f;
			}
		}
		//�傫���ő�
		if (m_fScale > COUNTDOWN_SCALE * 75)
		{
			m_fScale = COUNTDOWN_SCALE * 75;
			if (m_nType < 1)
			{
				//�e�N�X�`���ւ�
				m_bCntDown = true;
				m_nType += 1;
				m_fScale = 0;
				m_Col.a = 1.0f;

				pSound->SetVolume(CSound::SOUND_LABEL_SE_GAMESTART01, 5.0f);
				pSound->PlaySound(CSound::SOUND_LABEL_SE_GAMESTART01);
			}
			else if (m_nType == 1)
			{
				m_bEndCntDown = true;
				m_Col.a = 0.0f;
				for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
				{	// �v���C���[���擾
					m_pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
					if (m_pPlayer[nCntPlayer] != NULL)
					{
						m_pPlayer[nCntPlayer]->GetCharaMover()->SetWaitBool(false);
					}
				}
			}

			for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
			{
				if (m_pScene2D[nCnt] != NULL)
				{
					switch (m_nType)
					{
					case 0:
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN0");
						break;
					case 1:
						//�X�^�[�g�\��
						m_pScene2D[nCnt]->BindTexture("COUNTDOWN1");
						m_pScene2D[nCnt]->SetWidthHeight(m_fWidth + 100, m_fHeight + 100);
						break;
					default:
						break;
					}
				}
			}
		}
		//�F�E�傫���X�V
		for (int nCnt = 0; nCnt < PLAYER_MAX; nCnt++)
		{
			if (m_pScene2D[nCnt] != NULL)
			{
				m_pScene2D[nCnt]->SetCol(m_Col);
				m_pScene2D[nCnt]->SetScale(m_fScale);
			}
		}
	}

}
//=============================================================================
// �^�C�}�[��Texture�Ǘ�
//=============================================================================
void CTutoTime::TexTime(int nTexData, int nTimeOne)
{
	nTexData = m_nTime;

	//for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
	//{// �e�N�X�`���ɔ��f

	//	if (m_apNumber[nCntTime] != NULL)
	//	{
	//		if (nCntTime < 2)
	//		{
	//			m_apNumber[nCntTime]->SetNumber(nTexData);
	//			nTexData /= 10;
	//		}
	//		else if (nCntTime == 2)
	//		{
	//			m_apNumber[nCntTime]->SetNumber(nTimeOne);
	//			nTexData /= 10;
	//		}
	//	}
	//}
}
//=============================================================================
// �^�C�����Z����
//=============================================================================
void CTutoTime::AddTime(int nTime)
{
	if (m_nTime > 0)
	{
		m_nTimeOne += nTime;
	}

	if (GAME_TUTOTIME_MAX < m_nTimeOne) { m_nTimeOne = GAME_TUTOTIME_MAX; }
}
//=============================================================================
// �ׂ���̌v�Z
//=============================================================================
int CTutoTime::PowerCalculation(int nData, int nOperation)
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
			if (nNum >= TUTOTIME_MAX) { nNum = TUTOTIME_MAX; }
		}
	}
	return nNum;
}

//=============================================================================
// ���Ԃ̊Ǘ�
//=============================================================================
void CTutoTime::TimeManagement(void)
{
	if (m_nTime == 0 && m_nTimeOne == 0) {m_nTime = 0; return; }

	//���s�[�g���[�h�̎��͑���
	int nFlameSecond = 60;
#ifdef _DEBUG
	if (CManager::GetRepeat() == true)
	{
		nFlameSecond = 1;
	}
#endif
	if (m_nTimeCount % nFlameSecond == 0)
	{// 1�b���ƂɌ��Z(��������)
		m_nTime--;
		if (m_nTime < 0) { m_nTime = 59; m_nTimeOne -= 1; 	DefaultCol();}
		//m_nTimeNum = PowerCalculation(m_nTime, 0);
	}
}
//=============================================================================
// �X�e�[�W�ؑ֎��̉��o
//=============================================================================
void CTutoTime::ChangeStage(void)
{

}

//=============================================================================
// �F�����ɖ߂�
//=============================================================================
void CTutoTime::DefaultCol(void)
{
	for (int nCntTime = 0; nCntTime < TUTOTIME_MAX; nCntTime++)
	{// �e�N�X�`���ɔ��f
		if (m_apNumber[nCntTime] != NULL)
		{
			m_apNumber[nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}

//=============================================================================
// �f�o�b�N�p
//=============================================================================
void CTutoTime::DebugKey(void)
{
	// �f�o�b�N�p
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD0))
	{	// �������ԉ��Z
		AddTime(1);
	}

	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD6))
	{	// �������ԉ��Z
		m_nTimeCount--;
	}
	if (CManager::GetInputKeyboard()->GetPress(DIK_NUMPAD4))
	{	// �������ԉ��Z
		m_nTimeCount++;
	}
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_NUMPAD9))
	{	// ���U���g��ʂ�
		m_nTime = 0;
		m_nTimeOne = 0;
	}
}