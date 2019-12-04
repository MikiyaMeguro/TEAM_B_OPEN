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
#include "camera.h"
#include "CameraManager.h"
#include "sceneX.h"
#include "number.h"
//============================================================================
//	�}�N����`
//============================================================================
#define POS_4TH (D3DXVECTOR3(-50.0f,0.0f,0.0f))
#define TIMER_SPACE			(40.0f)										// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define SIZE_X (SCREEN_WIDTH/2)											//����
#define SIZE_Y (SCREEN_HEIGHT/2)										//�c��
#define DEFAULT_SIZE (150.0f)											//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))						//�|���S���̏����ʒu
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))						//��������]
#define DEFAULT_COL_WHITE (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))				//�������F_��
#define DEFAULT_COL_WHITE_ALPHA_HARF (D3DXCOLOR(0.8f,0.8f,0.8f,0.5f))	//�������F_���i�������j
#define DEFAULT_SIZE2D (D3DXVECTOR2(0.0f,0.0f))							//Vectro2��p�����T�C�Y������
#define CHARAICON_POS (D3DXVECTOR3(140.0f,100.0f,0.0f))					//�A�C�R���̈ʒu
#define CHARAICON_INTERVAL (310.0f)
#define NUMBER_INTERVAL (0.5f)

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
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_RankPos[nCnt] = DEFAULT_POS;
		m_PlayerNumPos[nCnt] = DEFAULT_POS;
		m_PlayerIconPos[nCnt] = DEFAULT_POS;
		m_RankIconSize[nCnt] = DEFAULT_SIZE2D;
		m_PlayerNumSize[nCnt] = DEFAULT_SIZE2D;
		m_PlayerIconSize[nCnt] = DEFAULT_SIZE2D;

	}
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

	float fPosX = 30;	//�\���䏉���ʒu
	float fNext = 40;	//�\����̊Ԃ̕�


	InitPointer();
	SetPolygon();
#if 0
	m_ResultChara[0].nPoint = 3;
	m_ResultChara[1].nPoint = 2;
	m_ResultChara[2].nPoint = 0;
	m_ResultChara[3].nPoint = 2;

	m_ResultChara[0].type = CPlayer::TYPE_BARANCE;
	m_ResultChara[1].type = CPlayer::TYPE_POWER;
	m_ResultChara[2].type = CPlayer::TYPE_SPEED;
	m_ResultChara[3].type = CPlayer::TYPE_REACH;
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
			break;
		case 1:
			m_ResultChara[nCntPlayer].nNumRank = 3;
			nCntRankNum[2]++;
			break;
		case 2:
			m_ResultChara[nCntPlayer].nNumRank = 2;
			nCntRankNum[1]++;
			break;
		case 3:
			m_ResultChara[nCntPlayer].nNumRank = 1;
			nCntRankNum[0]++;
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
	for (int nCnt = 0; nCnt < nCntRankNum[0]; nCnt++)
	{//���ʂ̐�����
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM1, 1);
		if(nCnt == 1)
		{	//1��(����)�̏ꏊ�֕ς���
			fPosX = 30;
			fNext *= -1;
		}
		//�ʒu�����炷
		fPosX += fNext;
	}

	fPosX = 70;
	for (int nCnt = 0; nCnt < nCntRankNum[1]; nCnt++)
	{//���ʂ̐�����
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM2, 1);
		if (nCnt == 0)
		{	//2��(����)�̏ꏊ�֕ς���
			fPosX = 30;
			fNext *= -1;
		}
		//�ʒu�����炷
		fPosX += fNext;
	}

	fPosX = -10;
	fNext = -40;
	for (int nCnt = 0; nCnt < nCntRankNum[2]; nCnt++)
	{//���ʂ̐�����
		CSceneX::Create(D3DXVECTOR3(fPosX, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f), CLoad::MODEL_PODIUM3, 1);
		//3��(����)�̈ʒu�����炷
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
				fPosX = 30;
				Set2DUI(nCntPlayer, 1);
			}
			if (nCntRankPos[0] == 1)
			{
				fPosX = 70;
				Set2DUI(nCntPlayer, 0);
			}
			if (nCntRankPos[0] == 2)
			{
				fPosX = -10;
				Set2DUI(nCntPlayer, 2);
			}
			if (nCntRankPos[0] == 3)
			{
				fPosX = -50;
				Set2DUI(nCntPlayer, 3);
			}
			RankPos = D3DXVECTOR3(fPosX, 30.0f, 0.0f);
			nCntRankPos[0]++;
			break;
		case 2:
			if (nCntRankPos[1] == 0)
			{
				fPosX = 70;
				Set2DUI(nCntPlayer, 0);
			}
			if (nCntRankPos[1] == 1)
			{
				fPosX = -10;
				Set2DUI(nCntPlayer, 2);
			}
			if (nCntRankPos[1] == 2)
			{
				fPosX = -50;
				Set2DUI(nCntPlayer, 3);
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[1]++;
			break;
		case 3:
			if (nCntRankPos[2] == 0)
			{
				fPosX = -10;
				Set2DUI(nCntPlayer, 2);
			}
			if (nCntRankPos[2] == 1)
			{
				fPosX = -50;
				Set2DUI(nCntPlayer, 3);
			}
			RankPos = D3DXVECTOR3(fPosX, 20.0f, 0.0f);
			nCntRankPos[2]++;
			break;
		case 4:
			RankPos = POS_4TH;
			Set2DUI(nCntPlayer, 3);
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
		for (int nCntTime = 0; nCntTime < MAX_POINT; nCntTime++)
		{
			// �i���o�[�����ݒ�
			m_apNumber[nCntPlayer][nCntTime] = new CNumber;
			if (nCntTime < 2)
			{	// �R���܂�
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3(((CHARAICON_POS.x+ TIMER_SPACE) * nCntTime), CHARAICON_POS.y, CHARAICON_POS.z), 0);
				m_apNumber[nCntPlayer][nCntTime]->SetSize(D3DXVECTOR2(30.0f, 30.0f), 
												D3DXVECTOR2(((m_apPlayerIcon[nCntPlayer]->GetPosition().x + 120.0f) - TIMER_SPACE * nCntTime) + (NUMBER_INTERVAL*nCntPlayer), CHARAICON_POS.y));
				m_apNumber[nCntPlayer][nCntTime]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
			else if (nCntTime == 2)
			{	// 3����
				m_apNumber[nCntPlayer][nCntTime]->Init(D3DXVECTOR3((CHARAICON_POS.x - TIMER_SPACE * nCntTime) + 100.0f + (80.0f*nCntPlayer), CHARAICON_POS.y, CHARAICON_POS.z), 0);
			}
		}
	}


#if 0
	/* �\�[�g */
	for (int nRank = 0; nRank < 4; nRank++)
	{
		for (int nRankCnt = nRank + 1; nRankCnt < 4; nRankCnt++)
		{
			if (m_ResultChara[nRank].nNumRank > m_ResultChara[nRankCnt].nNumRank)
			{
				nRepCharaSet = m_ResultChara[nRank];
				m_ResultChara[nRank] = m_ResultChara[nRankCnt];
				m_ResultChara[nRankCnt] = nRepCharaSet;
			}
		}
	}

#endif
#if 1
	//�����̃e�N�X�`���ݒ�
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		TexPoint(nCntPlayer, m_ResultChara[nCntPlayer].nPoint);
		RankTex(nCntPlayer, m_ResultChara[nCntPlayer].nNumRank-1);
		PLNumTex(nCntPlayer, m_ResultChara[nCntPlayer].type,m_ResultChara[nCntPlayer].Movetype);
	}
#endif

#endif
	//�J�����̐ݒ�
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	pCameraManager->CreateCamera("RESULT_CAMERA",CCamera::TYPE_SPECTOR,D3DXVECTOR3(5.0f, 40.0f, 110.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 135.0f);
	pCameraManager->SetCameraViewPort("RESULT_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	CCamera *pCamera = pCameraManager->GetCamera("RESULT_CAMERA");
	if (pCamera != NULL)
	{
		pCamera->SetPosR(D3DXVECTOR3(5.0f, 40.0f, 0.0f));
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
void CResult::SetRanking(int nNumPlayer, CPlayer::PLAYER_TYPE type, CCharaBase::CHARACTOR_MOVE_TYPE typeM, int nPoint)
{
	m_ResultChara[nNumPlayer].type = type;
	m_ResultChara[nNumPlayer].Movetype = typeM;
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
	m_apScene2D[RESULTTYPE_WINDOW] = CScene2D::Create(D3DXVECTOR3(SIZE_X, ((DEFAULT_SIZE*0.8f) / 2)+11.0f, 0.0f), "RANKING_WINDOW",1);
	m_apScene2D[RESULTTYPE_WINDOW]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*0.9f);
#if 1
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_apPlayerIcon[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARAICON_POS.x + (CHARAICON_INTERVAL*nCnt), CHARAICON_POS.y, CHARAICON_POS.z), "RANKCHARA_ICON", 2);
		m_apPlayerIcon[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.5f);
		m_apPlayerIcon[nCnt]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
		m_PlayerIconPos[nCnt] = m_apPlayerIcon[nCnt]->GetPosition();
		m_PlayerIconSize[nCnt].x = m_apPlayerIcon[nCnt]->GetSize(0);
		m_PlayerIconSize[nCnt].y = m_apPlayerIcon[nCnt]->GetSize(1);

		m_apPlayerNum[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARAICON_POS.x + (CHARAICON_INTERVAL*nCnt), 150.0f, 0.0f), "RANK&PLNUM");
		m_apPlayerNum[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*0.3f);
		m_apPlayerNum[nCnt]->SetTex(D3DXVECTOR2(0.5f, 0.0f + ((1.0f / MAX_PLAYER)* nCnt)), D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
		m_PlayerNumPos[nCnt] = m_apPlayerNum[nCnt]->GetPosition();
		m_PlayerNumSize[nCnt].x = m_apPlayerNum[nCnt]->GetSize(0);
		m_PlayerNumSize[nCnt].y = m_apPlayerNum[nCnt]->GetSize(1);

		m_apRanking[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARAICON_POS.x + (CHARAICON_INTERVAL*nCnt), 30.0f, 0.0f), "RANK&PLNUM");
		m_apRanking[nCnt]->SetWidthHeight(DEFAULT_SIZE*0.7f, DEFAULT_SIZE*0.4f);
		m_apRanking[nCnt]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nCnt)), D3DXVECTOR2(0.5f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nCnt)));
		m_RankPos[nCnt] = m_apRanking[nCnt]->GetPosition();
		m_RankIconSize[nCnt].x = m_apRanking[nCnt]->GetSize(0);
		m_RankIconSize[nCnt].y = m_apRanking[nCnt]->GetSize(1);
	}
#endif
}
//=============================================================================
// �Z���N�g���j���[��������3D�|���S��alpha�l�̐ݒ�
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
//=============================================================================
// 2DUI�̐ݒ�
//=============================================================================
void  CResult::Set2DUI(int nNum, int nPosNum)
{
	/*�����N�̈ʒu�Ƒ傫��*/
	m_apRanking[nNum]->SetPosition(m_RankPos[nPosNum]);
	m_apRanking[nNum]->SetWidthHeight(m_RankIconSize[nPosNum].x, m_RankIconSize[nPosNum].y);
	/*PL�ԍ��̈ʒu�Ƒ傫��*/
	m_apPlayerNum[nNum]->SetPosition(m_PlayerNumPos[nPosNum]);
	m_apPlayerNum[nNum]->SetWidthHeight(m_PlayerNumSize[nPosNum].x, m_PlayerNumSize[nPosNum].y);
	/*�L�����A�C�R���̈ʒu�Ƒ傫��*/
	m_apPlayerIcon[nNum]->SetPosition(m_PlayerIconPos[nPosNum]);
	m_apPlayerIcon[nNum]->SetWidthHeight(m_PlayerIconSize[nPosNum].x, m_PlayerIconSize[nPosNum].y);
}
//=============================================================================
// ���ʂ̃e�N�X�`�����W�ݒ�
//=============================================================================
void CResult::RankTex(int nNum,int nRank)
{
	m_apRanking[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nRank)),
		D3DXVECTOR2(0.5f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nRank)));
}
//=============================================================================
// �L�����A�C�R���̃e�N�X�`���Ǘ�
//=============================================================================
void CResult::PLNumTex(int nNum, int nChara,CCharaBase::CHARACTOR_MOVE_TYPE type)
{
	switch (type)
	{
	case CCharaBase::MOVETYPE_PLAYER_INPUT:
		m_apPlayerIcon[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / MAX_PLAYER)*nChara)),
			D3DXVECTOR2(1.0f, (1.0f / MAX_PLAYER) + ((1.0f / MAX_PLAYER)*nChara)));
		break;
	case CCharaBase::MOVETYPE_NPC_AI:
		m_apPlayerNum[nNum]->BindTexture("RANKCHARA_PLNUM_COM");
		m_apPlayerNum[nNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f + ((1.0f / 3)*nNum)),
									D3DXVECTOR2(1.0f, (1.0f / 3) + ((1.0f / 3)*nNum)));
		break;

	}
}