//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �ڍ�������
//
//=============================================================================
#include "result.h"
#include "debugProc.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "fade.h"
#include "time.h"
#include "camera.h"
#include "SelectMenu.h"
#include "CameraManager.h"
#include "camera.h"
#include "meshField.h"
#include "sceneX.h"
#include "number.h"
//============================================================================
//	�}�N����`
//============================================================================
#define POS_1ST (D3DXVECTOR3(20.0f,30.0f,0.0f))
#define POS_2ND (D3DXVECTOR3(50.0f,20.0f,0.0f))
#define POS_3RD (D3DXVECTOR3(-10.0f,20.0f,0.0f))
#define POS_4TH (D3DXVECTOR3(-40.0f,0.0f,0.0f))

#define NUMBERPOS_1ST (D3DXVECTOR3(150.0f,100.0f,0.0f))
#define NUMBERPOS_2ND (D3DXVECTOR3(150.0f,200.0f,0.0f))
#define NUMBERPOS_3RD (D3DXVECTOR3(150.0f,300.0f,0.0f))
#define NUMBERPOS_4TH (D3DXVECTOR3(150.0f,400.0f,0.0f))


#define TIMER_SPACE			(40.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CPlayer *CResult::m_pPlayer[MAX_PLAYER] = {};
CResult::CharaSet CResult::m_ResultChara[MAX_PLAYER] = {};
CMeshField *CResult::m_pMeshField = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// �|���S���̏���������
//=============================================================================
HRESULT CResult::Init(void)
{


#if 1
	m_ResultChara[0].nPoint = 1;
	m_ResultChara[1].nPoint = 2;
	m_ResultChara[2].nPoint = 3;
	m_ResultChara[3].nPoint = 4;

#endif
	//���ʌ���
	int nCntWinScore = 0;

	//�\�[�g���� �傫����
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
		{
			if (nCnt != nCntPlayer && m_ResultChara[nCntPlayer].nPoint >= m_ResultChara[nCnt].nPoint)
			{//���Ɣ�ׂĎ������傫���������J�E���g�𑝂₷
				nCntWinScore++;
			}
		}
		//���񏟂������ŏ��ʌ���
		switch (nCntWinScore)
		{
		case 0:
			m_ResultChara[nCntPlayer].nNumRank = 4;
			break;
		case 1:
			m_ResultChara[nCntPlayer].nNumRank = 3;
			break;
		case 2:
			m_ResultChara[nCntPlayer].nNumRank = 2;
			break;
		case 3:
			m_ResultChara[nCntPlayer].nNumRank = 1;
			break;
		default:
			break;
		}
		//��������������
		nCntWinScore = 0;
	}


#if 1
	//���b�V���t�B�[���h����
	m_pMeshField = NULL;
	if (m_pMeshField == NULL)
	{
		m_pMeshField = CMeshField::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] == NULL)
		{
			m_pPlayer[nCntPlayer] = CPlayer::Create();
		}
	}

	//�\���䐶��
	CSceneX::Create(D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM1, 1);
	CSceneX::Create(D3DXVECTOR3(50.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM2, 1);
	CSceneX::Create(D3DXVECTOR3(-10.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM3, 1);

	D3DXVECTOR3 RankPos;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	//�����ʒu�ݒ�
		switch (m_ResultChara[nCntPlayer].nNumRank)
		{
		case 1:
			RankPos = POS_1ST;
			break;
		case 2:
			RankPos = POS_2ND;
			break;
		case 3:
			RankPos = POS_3RD;
			break;
		case 4:
			RankPos = POS_4TH;
			break;
		}

		if (m_pPlayer[nCntPlayer] != NULL)
		{
			m_pPlayer[nCntPlayer]->Set(RankPos, CCharaBase::MOVETYPE_RANKING_CHARA, nCntPlayer, m_ResultChara[nCntPlayer].type);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
			m_pPlayer[nCntPlayer]->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);
		}
	}


	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	//�����ʒu�ݒ�
		switch (nCntPlayer)
		{
		case 0:
			RankPos = NUMBERPOS_1ST;
			break;
		case 1:
			RankPos = NUMBERPOS_2ND;
			break;
		case 2:
			RankPos = NUMBERPOS_3RD;
			break;
		case 3:
			RankPos = NUMBERPOS_4TH;
			break;
		}

		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			// �^�C�}�[�����ݒ�
			m_apNumber[nCntPlayer][nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// �R���܂�
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
				m_apNumber[nCntPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f), D3DXVECTOR2((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y));
				m_apNumber[nCntPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCntTime == 2)
			{	// 3����
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
			}
		}
	}

	//�����̃e�N�X�`���ݒ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		TexPoint(nCntPlayer, m_ResultChara[nCntPlayer].nPoint);
	}

#endif
	//�J�����̐ݒ�
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("RESULT_CAMERA",CCamera::TYPE_SPECTOR,D3DXVECTOR3(20.0f, 40.0f, 110.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 135.0f);
	pCameraManager->SetCameraViewPort("RESULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("RESULT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(20.0f, 40.0f, 0.0f));
	}

	//���j���[�𐶐�
	//m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(740, 100.0f, 0), 120, 180, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);

	return S_OK;
}

//=============================================================================
// �|���S���̏I������
//=============================================================================
void CResult::Uninit(void)
{
	//���j���[�̔j��
	if (m_pSeletMenu != NULL)
	{
		m_pSeletMenu->Uninit();
		m_pSeletMenu = NULL;
	}

	//���b�V���t�B�[���h�̔j��
	if (m_pMeshField != NULL)
	{
		m_pMeshField->Uninit();
		m_pMeshField = NULL;
	}

	//�i���o�[�̔j��
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				m_apNumber[nCntPlayer][nCntTime]->Uninit();
				m_apNumber[nCntPlayer][nCntTime] = NULL;
			}
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{	// �v���C���[�̔j��
			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}
	//�S�Ă̏I������
	Release();
}

//=============================================================================
// �|���S���̍X�V����
//=============================================================================
void CResult::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	//�C�ӂ̃L�[ENTER
	if (CCommand::GetCommand("DECISION"))
	{
		if (m_bMenu == false)
		{
			m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(740, 100.0f, 0), 120, 180, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);
			m_bMenu = true;
		}
	}
#ifdef _DEBUG
	CDebugProc::Print("c", "���U���g");

#endif
}

//=============================================================================
// �|���S���̕`�揈��
//=============================================================================
void CResult::Draw(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			if (m_apNumber[nCntPlayer][nCntTime] != NULL)
			{
				m_apNumber[nCntPlayer][nCntTime]->Draw();
			}
		}
	}
}

//=============================================================================
// �L�����N�^�[����ݒ�
//=============================================================================
void CResult::SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, int nPoint)
{
	m_ResultChara[nNumPlayer].type = type;
	m_ResultChara[nNumPlayer].nPoint = nPoint;
}

//=============================================================================
// �e�N�X�`����ݒ�
//=============================================================================
void CResult::TexPoint(int nPlayer, int nPoint)
{

	for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
	{// �e�N�X�`���ɔ��f

		if (m_apNumber[nPlayer][nCntTime] != NULL)
		{
			if (nCntTime < 2)
			{
				m_apNumber[nPlayer][nCntTime]->SetNumber(nPoint);
				nPoint /= 10;
			}
			else if (nCntTime == 2)
			{
				m_apNumber[nPlayer][nCntTime]->SetNumber(nPoint);
				nPoint /= 10;
			}
		}
	}
}
