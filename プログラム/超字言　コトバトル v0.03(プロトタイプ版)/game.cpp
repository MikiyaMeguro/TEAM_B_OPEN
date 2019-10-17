//=============================================================================
//
// ���C������ [game.cpp]
// Author :
//
//=============================================================================
#include "game.h"
#include "manager.h"
#include "light.h"
#include "scene3D.h"
#include "sceneX.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "CameraManager.h"
#include "word_manager.h"
#include "word.h"
#include "tube.h"
#include "time.h"
#include "PlayerNumSelect.h"

#include "PlayerNumSelect.h"

#include "player.h"
#include "charactor.h"
#include "SetObject.h"
//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH)
#define SIZE_Y (SCREEN_HEIGHT)
#define COLISIONSIZE (20.0f)
#define TIME_INI		(60)
//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CPlayer *CGame::m_pPlayer[MAX_PLAYER] = {};
CTube *CGame::m_apTube[MAX_PLAYER] = {};
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CGame::~CGame()
{

}

//=============================================================================
// ����������
//=============================================================================
void CGame::Init(void)
{
	//�J�����̃N���G�C�g
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	//CPlayerSelect::SELECTPLAYER *NumPlayer = CPlayerSelect::GetModeSelectMode();
	CPlayerSelect::SELECTPLAYER NumPlayer = CPlayerSelect::SELECTPLAYER_3P;//�e�X�g
	CameraSetting((int)NumPlayer);

	//�ǁA���ݒ�
	CScene3D* p3D = NULL;
	p3D = CScene3D::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), "BLOCK");
	p3D->SetSize(1000.0f,1000.0f);
	p3D = CScene3D::Create(D3DXVECTOR3(0.0f, 300.0f, 0.0f), "BLOCK");
	p3D->SetRot(D3DXVECTOR3(D3DX_PI,0.0f,0.0f));
	p3D->SetSize(1000.0f, 1000.0f);

	// �v���C���[�̐���
	PlayerSetting((int)NumPlayer);

	// �����̉���UI(2D)�̐���
	TubeSetting((int)NumPlayer);

	WordCreate();

	// �e�X�g�I�u�W�F�N�g
	CSceneX::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f), CLoad::MODEL_BOX, 0);
	CSetObject::Create();

	if (NumPlayer == CPlayerSelect::SELECTPLAYER_2P)
	{
		CTime::Create((int)NumPlayer);
		CTime::Create((int)NumPlayer);
	}
	else if (NumPlayer != CPlayerSelect::SELECTPLAYER_2P) { CTime::Create((int)NumPlayer); }
}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_pPlayer[nCntPlayer] != NULL)
		{	// �v���C���[�̔j��
			m_pPlayer[nCntPlayer]->Uninit();
			m_pPlayer[nCntPlayer] = NULL;
		}
	}
	for (int nCntTube = 0; nCntTube < MAX_PLAYER; nCntTube++)
	{
		if (m_apTube[nCntTube] != NULL)
		{	// �����̉���UI(2D)�̔j��
			m_apTube[nCntTube]->Uninit();
			m_apTube[nCntTube] = NULL;
		}
	}
	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �X�V����
//=============================================================================
void CGame::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	// �����_���Ȓl���X�V
	srand((unsigned int)time(NULL));

	CDebugProc::Print("c", "�Q�[�����[�h");

	//�C�ӂ̃L�[ENTER
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pFade->SetFade(pManager->MODE_RESULT, pFade->FADE_OUT);
	}
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);

	}

	//�J��������i�e�X�g�j
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	CCamera* pCam = pCameraManager->GetCamera("TOPVIEW_CAMERA");
	if (pCam != NULL)
	{
		pCam->SetRotation(pCam->GetRotation() + D3DXVECTOR3(0.0f,0.001f,0.0f));
	}

#ifdef _DEBUG

#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �J�����Z�b�g����
//=============================================================================
void CGame::CameraSetting(int nNumPlayer)
{
	//CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	////CPlayerSelect::SELECTPLAYER NumPlayer = CPlayerSelect::SELECTPLAYER_3P;
	//�J�����̃N���G�C�g
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		switch (nNumPlayer)
		{
		case CPlayerSelect::SELECTPLAYER_1P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
			break;

		case CPlayerSelect::SELECTPLAYER_2P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, SCREEN_WIDTH, 355);
			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(-0.2f, D3DX_PI, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 0, 365, SCREEN_WIDTH, 340);
			break;

		case CPlayerSelect::SELECTPLAYER_3P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 620, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 340);

			pCameraManager->CreateCamera("TOPVIEW_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(-2.0f, D3DX_PI * -0.5f, 0.0f), 650.0f);
			pCameraManager->SetCameraViewPort("TOPVIEW_CAMERA", 645, 365, 620, 340);
			break;

		case CPlayerSelect::SELECTPLAYER_4P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 620, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 340);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 620, 340);
			break;

		default:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 635, 355);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 645, 0, 620, 355);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 365, 635, 340);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 645, 365, 620, 340);
			break;
		}
	}
}

//=============================================================================
// �l���ɉ����ăv���C���[�����̏���
//=============================================================================
void CGame::PlayerSetting(int nNum)
{
	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (nNum == 1 || nNum == 2 || nNum == 3 || nNum == 4)
	{
		// �l�����𐶐�
		for (int nCntPlayer = 0; nCntPlayer < nNum; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}

		if (m_pPlayer[0] != NULL)
		{
			m_pPlayer[0]->Set(D3DXVECTOR3(100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 0);
			m_pPlayer[0]->SetCameraName("1P_CAMERA");
			pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
		}

		if (m_pPlayer[1] != NULL)
		{
			m_pPlayer[1]->Set(D3DXVECTOR3(-100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 1);
			m_pPlayer[1]->SetCameraName("2P_CAMERA");
			pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
		}

		if (m_pPlayer[2] != NULL)
		{
			m_pPlayer[2]->Set(D3DXVECTOR3(100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 2);
			m_pPlayer[2]->SetCameraName("3P_CAMERA");
			pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
		}

		if (m_pPlayer[3] != NULL)
		{
			m_pPlayer[3]->Set(D3DXVECTOR3(-100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 3);
			m_pPlayer[3]->SetCameraName("4P_CAMERA");
			pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
		}
	}
	else
	{
		// �l�����𐶐�
		for (int nCntPlayer = 0; nCntPlayer < 3; nCntPlayer++)
		{
			if (m_pPlayer[nCntPlayer] == NULL)
			{
				m_pPlayer[nCntPlayer] = CPlayer::Create();
			}
		}

		if (m_pPlayer[0] != NULL)
		{
			m_pPlayer[0]->Set(D3DXVECTOR3(100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 0);
			m_pPlayer[0]->SetCameraName("1P_CAMERA");
			pCameraManager->SetCameraHomingChara("1P_CAMERA", (C3DCharactor*)m_pPlayer[0]->GetCharaMover());
		}

		if (m_pPlayer[1] != NULL)
		{
			m_pPlayer[1]->Set(D3DXVECTOR3(-100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 1);
			m_pPlayer[1]->SetCameraName("2P_CAMERA");
			pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)m_pPlayer[1]->GetCharaMover());
		}

		if (m_pPlayer[2] != NULL)
		{
			m_pPlayer[2]->Set(D3DXVECTOR3(100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 2);
			m_pPlayer[2]->SetCameraName("3P_CAMERA");
			pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)m_pPlayer[2]->GetCharaMover());
		}
		if (m_pPlayer[3] != NULL)
		{
			m_pPlayer[3]->Set(D3DXVECTOR3(-100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT, 3);
			m_pPlayer[3]->SetCameraName("4P_CAMERA");
			pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)m_pPlayer[3]->GetCharaMover());
		}
	}
}

//=============================================================================
// �l���ɉ��������̐�������
//=============================================================================
void CGame::TubeSetting(int nNum)
{
	switch (nNum)
	{
	case 1:
		if (m_apTube[0] == NULL)
		{
			m_apTube[0] = CTube::Create(WORD_TUBE001_POS_1P, WORD_TUBE002_SIZE, "TUBE", 3);
		}
		break;

	case 2:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_1P, WORD_TUBE002_SIZE, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE002_POS_2P, WORD_TUBE002_SIZE, "TUBE", 3); }
			}
		}
		break;

	case 3:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_TUBE002_SIZE, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_TUBE002_SIZE, "TUBE", 3); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_TUBE002_SIZE, "TUBE", 3); }
			}
		}
		break;

	case 4:
		for (int nCntTube = 0; nCntTube < nNum; nCntTube++)
		{
			if (m_apTube[nCntTube] == NULL)
			{
				if (nCntTube == 0) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_1P, WORD_TUBE002_SIZE, "TUBE", 3); }
				if (nCntTube == 1) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_2P, WORD_TUBE002_SIZE, "TUBE", 3); }
				if (nCntTube == 2) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE003_POS_3P, WORD_TUBE002_SIZE, "TUBE", 3); }
				if (nCntTube == 3) { m_apTube[nCntTube] = CTube::Create(WORD_TUBE004_POS_4P, WORD_TUBE002_SIZE, "TUBE", 3); }
			}
		}
		break;

	default:
		break;
	}
}


//=============================================================================
// �����Ǘ��̏���
//=============================================================================
void CGame::WordCreate(void)
{
	// ��
	//CWord::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 17);
	//CWord::Create(D3DXVECTOR3(-300.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 7);
	//CWord::Create(D3DXVECTOR3(-400.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 3);

	// �G��
	/*CWord::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 3);
	CWord::Create(D3DXVECTOR3(-300.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 24);
	CWord::Create(D3DXVECTOR3(-400.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 7);*/

	// �����
	CWord::Create(D3DXVECTOR3(0.0f, -20.0f, -60.0f), 12.0f, 12.0f, "WORD", 7);
	CWord::Create(D3DXVECTOR3(-300.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 40);
	CWord::Create(D3DXVECTOR3(-400.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 30);

	// �����S
	CWord::Create(D3DXVECTOR3(-200.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 39);
	CWord::Create(D3DXVECTOR3(-200.0f, -20.0f, 150.0f), 12.0f, 12.0f, "WORD", 45);
	CWord::Create(D3DXVECTOR3(-50.0f, -20.0f, 0.0f), 12.0f, 12.0f, "WORD", 9);

	//CWord::Create(D3DXVECTOR3(-100.0f, -20.0f, 150.0f), 12.0f, 12.0f, "WORD", 6);
}


#if 0
//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CGame::Collision(D3DXVECTOR3 *pos0, float fRadius0, D3DXVECTOR3 *pos1, float fRadius1)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos0->x - pos1->x, pos0->y - pos1->y, pos0->z - pos1->z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius0 + fRadius1)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}
#endif