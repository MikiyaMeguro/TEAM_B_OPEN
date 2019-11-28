//=============================================================================
//
// ���U���g���� [result.cpp]
// Author : �ڍ�������/��Ո�
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

#define PODIUMPOS_1ST (D3DXVECTOR3(20.0f, 0.0f, 0.0f))
#define PODIUMPOS_2ND (D3DXVECTOR3(50.0f, 0.0f, 0.0f))
#define PODIUMPOS_3RD (D3DXVECTOR3(-10.0f, 0.0f, 0.0f))
#define PODIUMPOS_4TH (D3DXVECTOR3(40.0f,0.0f,0.0f))

#define TIMER_SPACE			(40.0f)										// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)

#define SIZE_X (SCREEN_WIDTH/2)											//����
#define SIZE_Y (SCREEN_HEIGHT/2)										//�c��
#define DEFAULT_SIZE (150.0f)											//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))						//�|���S���̏����ʒu
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))						//��������]
#define DEFAULT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				//�������F_��
#define DEFAULT_COL_WHITE_ALPHA_HARF (D3DXCOLOR(0.8f,0.8f,0.8f,0.5f))	//�������F_���i�������j

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
	m_pSeletMenu = NULL;
	m_bMenu = false;
	m_bMenuCreate = false;
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
	int nCntWinScore = 0;				//�����J�E���g
	int nCntRankNum[4] = { 0,0,0,0 };	//���ʂ��Ƃɉ��l���邩
	CharaSet nRepCharaSet = {};			//������ւ�

	float fPosX = 20;	//�\���䏉���ʒu
	float fNext = 30;	//�\����̊Ԃ̕�

	InitPointer();
	SetPolygon();
#if 0
	m_ResultChara[0].nPoint = 0;
	m_ResultChara[1].nPoint = 10;
	m_ResultChara[2].nPoint = 20;
	m_ResultChara[3].nPoint = 0;

#endif
	//���ʌ���
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
			nCntRankNum[3]++;
			m_apPlayerNum[nCntPlayer]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)*nCntPlayer)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCntPlayer)));
			break;
		case 1:
			m_ResultChara[nCntPlayer].nNumRank = 3;
			nCntRankNum[2]++;
			m_apPlayerNum[nCntPlayer]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)*nCntPlayer)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCntPlayer)));

			break;
		case 2:
			m_ResultChara[nCntPlayer].nNumRank = 2;
			nCntRankNum[1]++;
			m_apPlayerNum[nCntPlayer]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)*nCntPlayer)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCntPlayer)));
			break;
		case 3:
			m_ResultChara[nCntPlayer].nNumRank = 1;
			nCntRankNum[0]++;
			m_apPlayerNum[nCntPlayer]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)*nCntPlayer)),
				D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCntPlayer)));
			break;
		default:
			break;
		}
		//��������������
		nCntWinScore = 0;
	}

	/* �\�[�g */
	for (int nRank = 0; nRank < 4; nRank++)
	{
		for (int nRankCnt = nRank + 1; nRankCnt < 4; nRankCnt++)
		{
			if (m_ResultChara[nRank].nNumRank >= m_ResultChara[nRankCnt].nNumRank)
			{
				nRepCharaSet = m_ResultChara[nRank];
				m_ResultChara[nRank] = m_ResultChara[nRankCnt];
				m_ResultChara[nRankCnt] = nRepCharaSet;
			}
		}
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
	for (int nCnt = 0; nCnt < nCntRankNum[0]; nCnt++)
	{//���ʂ̐�����
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM1, 1);
		if(nCnt == 1)
		{	//3�ʂ̏ꏊ�֕ς���
			fPosX = 20;
			fNext *= -1;
		}
		//�ʒu�����炷
		fPosX += fNext;
	}

	fPosX = 50;
	for (int nCnt = 0; nCnt < nCntRankNum[1]; nCnt++)
	{//���ʂ̐�����
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM2, 1);
		if (nCnt == 0)
		{	//3�ʂ̏ꏊ�֕ς���
			fPosX = 20;
			fNext *= -1;
		}
		//�ʒu�����炷
		fPosX += fNext;
	}

	fPosX = -10;
	fNext = -30;
	for (int nCnt = 0; nCnt < nCntRankNum[2]; nCnt++)
	{//���ʂ̐�����
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM3, 1);
		//�ʒu�����炷
		fPosX += fNext;
	}

	D3DXVECTOR3 RankPos;
	int nCntRankPos[4] = { 0,0,0,0 };	//���ʂ��Ƃɉ��l���邩

	fPosX = 20;
	fNext = 30;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{	//�����ʒu�ݒ�
		switch (m_ResultChara[nCntPlayer].nNumRank)
		{
		case 1:
			if (nCntRankPos[0] == 0)
			{
				fPosX = 20;
			}
			if (nCntRankPos[0] == 1)
			{
				fPosX = 50;
			}
			if (nCntRankPos[0] == 2)
			{
				fPosX = -10;
			}
			if (nCntRankPos[0] == 3)
			{
				fPosX = -40;
			}
			RankPos = D3DXVECTOR3(fPosX, 30.0f, 0.0f);
			nCntRankPos[0]++;
			break;
		case 2:
			if (nCntRankPos[1] == 0)
			{
				fPosX = 50;
			}
			if (nCntRankPos[1] == 1)
			{
				fPosX = -10;
			}
			if (nCntRankPos[1] == 2)
			{
				fPosX = -40;
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[1]++;
			break;
		case 3:
			if (nCntRankPos[2] == 0)
			{
				fPosX = -10;
			}
			if (nCntRankPos[2] == 1)
			{
				fPosX = -40;
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[2]++;
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
			// �i���o�[�����ݒ�
			m_apNumber[nCntPlayer][nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// �R���܂�
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime), RankPos.y, RankPos.z), 0);
				m_apNumber[nCntPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f), D3DXVECTOR2((RankPos.x - TIMER_SPACE * nCntTime) + 100.0f, RankPos.y + (80.0f*nCntPlayer)));
				m_apNumber[nCntPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCntTime == 2)
			{	// 3����
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((RankPos.x - TIMER_SPACE * nCntTime) + 100.0f, RankPos.y + (80.0f*nCntPlayer), RankPos.z), 0);
			}
		}
	}

	//�����̃e�N�X�`���ݒ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		TexPoint(nCntPlayer, m_ResultChara[nCntPlayer].nPoint);
		m_apPlayerIcon[nCntPlayer]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*(int)m_ResultChara[nCntPlayer].type)),
											D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*(int)m_ResultChara[nCntPlayer].type)));
		m_apRanking[nCntPlayer]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*(m_ResultChara[nCntPlayer].nNumRank-1))),
			D3DXVECTOR2(0.5f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*(m_ResultChara[nCntPlayer].nNumRank - 1))));

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
		if (m_apPlayerIcon[nCntPlayer] != NULL)
		{
			m_apPlayerIcon[nCntPlayer]->Uninit();
			m_apPlayerIcon[nCntPlayer] = NULL;
		}
		if (m_apRanking[nCntPlayer] != NULL)
		{
			m_apRanking[nCntPlayer]->Uninit();
			m_apRanking[nCntPlayer] = NULL;
		}
		if (m_apPlayerNum[nCntPlayer] != NULL)
		{
			m_apPlayerNum[nCntPlayer]->Uninit();
			m_apPlayerNum[nCntPlayer] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_RESULT_TEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
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

	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//�����t���O���Ǘ�
		if (m_bMenuCreate == true)
		{
			if (m_bMenu == true)
			{
				m_pSeletMenu = CSelectMenu::Create(D3DXVECTOR3(530.0f, SCREEN_HEIGHT / 2, 0), 220, 320, CSelectMenu::MENU_TYPE::MENU_TYPE_RESULT);
				m_pSeletMenu->SetModeSelectBool(true);
				SetAlpha();
				m_bMenu = false;
			}
			// �ȍ~�̍X�V�������΂�
			return;
		}

		//�C�ӂ̃L�[ENTER
		if (CCommand::GetCommand("DECISION"))
		{
			if (m_bMenuCreate == false)
			{
				if (m_bMenu == false)
				{
					m_bMenu = true;
					m_bMenuCreate = true;
				}
			}
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
//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CResult::InitPointer(void)
{
	for (int nCnt = 0; nCnt < MAX_RESULT_TEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apPlayerIcon[nCnt] != NULL)
		{
			m_apPlayerIcon[nCnt] = NULL;
		}
		if (m_apRanking[nCnt] != NULL)
		{
			m_apRanking[nCnt] = NULL;
		}
		if (m_apPlayerNum[nCnt] != NULL)
		{
			m_apPlayerNum[nCnt] = NULL;
		}
	}
}
//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CResult::SetPolygon(void)
{
	m_apScene2D[RESULTTYPE_WINDOW] = CScene2D::Create(D3DXVECTOR3(0.0f+ DEFAULT_SIZE, SIZE_Y, 0.0f), "RANKING_WINDOW",1);
	m_apScene2D[RESULTTYPE_WINDOW]->SetWidthHeight(DEFAULT_SIZE*1.3f, DEFAULT_SIZE*3.35f);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_apPlayerIcon[nCnt] = CScene2D::Create(D3DXVECTOR3(100.0f,100.0f + (180.0f*nCnt), 0.0f), "RANKCHARA_ICON", 2);
		m_apPlayerIcon[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.5f);
		m_apPlayerIcon[nCnt]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));

		m_apPlayerNum[nCnt] = CScene2D::Create(D3DXVECTOR3(100.0f, 150.0f + (180.0f*nCnt), 0.0f), "RANK&PLNUM");
		m_apPlayerNum[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.3f);
		m_apPlayerNum[nCnt]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));

		m_apRanking[nCnt] = CScene2D::Create(D3DXVECTOR3(100.0f, 40.0f + (180.0f*nCnt), 0.0f), "RANK&PLNUM");
		m_apRanking[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.5f);
		m_apRanking[nCnt]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(0.5f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
	}
}
//=============================================================================
// �Z���N�g���j���[��������2D�|���S��alpha�l�̐ݒ�
//=============================================================================
void CResult::SetAlpha(void)
{
	m_apScene2D[RESULTTYPE_WINDOW]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_apPlayerIcon[nCnt]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		m_apPlayerNum[nCnt]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		m_apRanking[nCnt]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			m_apNumber[nCnt][nCntTime]->SetCol(DEFAULT_COL_WHITE_ALPHA_HARF);
		}
	}
}