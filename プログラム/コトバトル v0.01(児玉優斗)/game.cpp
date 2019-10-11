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
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "CameraManager.h"

#include "PlayerNumSelect.h"

#include "player.h"
#include "charactor.h"
//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH)
#define SIZE_Y (SCREEN_HEIGHT)
#define COLISIONSIZE (20.0f)
#define TIME_INI		(60)
//============================================================================
//�ÓI�����o�ϐ��錾

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

	if (pCameraManager != NULL)
	{
		pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(-0.2f, 0.0f, 0.0f), 250.0f);
		pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 620, SCREEN_HEIGHT);

		pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
			D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(-0.2f, D3DX_PI, 0.0f), 300.0f);
		pCameraManager->SetCameraViewPort("2P_CAMERA", 660, 0, 620, SCREEN_HEIGHT);

		//pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
		//	D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.2f, D3DX_PI * -0.5f, 0.0f), 200.0f);
		//pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 380, 620, 340);

		//pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
		//	D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.2f, D3DX_PI * 0.5f, 0.0f), 200.0f);
		//pCameraManager->SetCameraViewPort("4P_CAMERA", 660, 380, 620, 340);
	}

	CScene3D* p3D = NULL;
	p3D = CScene3D::Create(D3DXVECTOR3(0.0f, -50.0f, 0.0f), "BLOCK");
	p3D = CScene3D::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), "BLOCK");
	p3D->SetRot(D3DXVECTOR3(D3DX_PI,0.0f,0.0f));

	CPlayer* pPlayer = NULL;

	pPlayer = CPlayer::Create();
	if (pPlayer != NULL)
	{
		pPlayer->Set(D3DXVECTOR3(100.0f,-20.0f,100.0f),CCharaBase::MOVETYPE_PLAYER_INPUT);
		pPlayer->SetCameraName("1P_CAMERA");
		pCameraManager->SetCameraHomingChara("1P_CAMERA",(C3DCharactor*)pPlayer->GetCharaMover());

	}

	//pPlayer = CPlayer::Create();
	//if (pPlayer != NULL)
	//{
	//	pPlayer->Set(D3DXVECTOR3(-100.0f, -20.0f, 100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
	//	pPlayer->SetCameraName("2P_CAMERA");
	//	pCameraManager->SetCameraHomingChara("2P_CAMERA", (C3DCharactor*)pPlayer->GetCharaMover());

	//}

	//pPlayer = CPlayer::Create();
	//if (pPlayer != NULL)
	//{
	//	pPlayer->Set(D3DXVECTOR3(100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
	//	pPlayer->SetCameraName("3P_CAMERA");
	//	pCameraManager->SetCameraHomingChara("3P_CAMERA", (C3DCharactor*)pPlayer->GetCharaMover());

	//}

	//pPlayer = CPlayer::Create();
	//if (pPlayer != NULL)
	//{
	//	pPlayer->Set(D3DXVECTOR3(-100.0f, -20.0f, -100.0f), CCharaBase::MOVETYPE_PLAYER_INPUT);
	//	pPlayer->SetCameraName("4P_CAMERA");
	//	pCameraManager->SetCameraHomingChara("4P_CAMERA", (C3DCharactor*)pPlayer->GetCharaMover());

	//}

}
//=============================================================================
// �I������
//=============================================================================
void CGame::Uninit(void)
{
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
void CGame::CameraSetting(void)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	//�J�����̃N���G�C�g
	CCameraManager *pCameraManager = CManager::GetCameraManager();
	if (pCameraManager != NULL)
	{
		switch (NumPlayer)
		{
		case CPlayerSelect::SELECTPLAYER_1P:
			break;
		case CPlayerSelect::SELECTPLAYER_2P:
			break;
		case CPlayerSelect::SELECTPLAYER_3P:
			break;
		case CPlayerSelect::SELECTPLAYER_4P:
			pCameraManager->CreateCamera("1P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, -100.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("1P_CAMERA", 0, 0, 620, 340);

			pCameraManager->CreateCamera("2P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(0.0f, 0.0f, 100.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("2P_CAMERA", 660, 0, 620, 340);

			pCameraManager->CreateCamera("3P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(-100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("3P_CAMERA", 0, 380, 620, 340);

			pCameraManager->CreateCamera("4P_CAMERA", CCamera::TYPE_TPS,
				D3DXVECTOR3(100.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f), 100.0f);
			pCameraManager->SetCameraViewPort("4P_CAMERA", 660, 380, 620, 340);
			break;
		}
	}
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