//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "word_manager.h"
#include "object.h"
#include "point.h"
#include "game.h"
#include "tutorial.h"

#include "sceneX.h"

#include "debugProc.h"
#include "bullet.h"
#include "explosion.h"
#include "CameraManager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_LOCKON_LENGTH (300.0f)								//���b�N�I���ł���ŉ�����
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 40.0f, 5.0f))			//�L�����N�^�[�̓����蔻��
#define LOCKON_FUTURE_ROTATE (20.0f)								//���b�N�I���̒e�p�x���莞�ɓG�̈ړ����x�Ɋ|����萔

#define INU_BARANCE_LOADTEXT_UPPER "data/MOTION/motion_dog_up.txt"			//��(�o�����X�^)�̏㔼�g�̃��[�h�e�L�X�g
#define INU_BARANCE_LOADTEXT_LOWER "data/MOTION/motion_dog_down.txt"		//��(�o�����X�^)�̉����g�̃��[�h�e�L�X�g

#define KUMA_POWER_LOADTEXT_UPPER "data/MOTION/motion_bea_up.txt"			//�F(�p���[�^)�̏㔼�g�̃��[�h�e�L�X�g
#define KUMA_POWER_LOADTEXT_LOWER "data/MOTION/motion_bea_down.txt"			//�F(�p���[�^)�̉����g�̃��[�h�e�L�X�g

#define NECO_SPEED_LOADTEXT_UPPER "data/MOTION/motion_cat_up.txt"			//�L(�X�s�[�h�^)�̏㔼�g�̃��[�h�e�L�X�g
#define NECO_SPEED_LOADTEXT_LOWER "data/MOTION/motion_cat_down.txt"			//�L(�X�s�[�h�^)�̉����g�̃��[�h�e�L�X�g

#define USAGI_REACH_LOADTEXT_UPPER "data/MOTION/motion_rabbit_up.txt"			//�L(�X�s�[�h�^)�̏㔼�g�̃��[�h�e�L�X�g
#define USAGI_REACH_LOADTEXT_LOWER "data/MOTION/motion_rabbit_down.txt"			//�L(�X�s�[�h�^)�̉����g�̃��[�h�e�L�X�g

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CPlayer::PlayerLoadState CPlayer::m_PlayerLoadState[CPlayer::TYPE_MAX][BODY_MAX];		//���[�h���i�[�p

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_bLand = false;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pWordManager = NULL;
	m_nCntTransTime = 0;
	m_pPlayerNum = NULL;
	m_bAssist = true;
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		m_nCntKey[nCntBody] = 0;
		m_nCntFlame[nCntBody] = 0;
		m_motion[nCntBody] =  0;
		m_OldMotion[nCntBody] = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			m_pPlayerParts[nCntParts][nCntBody] = NULL;
		}
	}
}
CPlayer::~CPlayer()
{

}

//=============================================================================
// ��������
//=============================================================================
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer = NULL;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	return pPlayer;
}
//=============================================================================
// �ݒ菈��
//=============================================================================
void CPlayer::Set(D3DXVECTOR3 pos, CCharaBase::CHARACTOR_MOVE_TYPE MoveType, int nPlayerID,PLAYER_TYPE PlayerType, D3DXVECTOR3 rot)
{
	//�L�������N���X����
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot, MoveType,this);
		}
	}

	//�L������ID�ݒ�
	m_nID = (nPlayerID % 4);//�͈͊O�̐������������炻���0�`3�܂ł̐����ɂ���

	// �����Ǘ��N���X����
	if (m_pWordManager == NULL)
	{
		ObjCreate(m_pWordManager);
		m_pWordManager->SetID(m_nID);
	}

	if (m_pPlayerNum == NULL)
	{
		int nID = m_nID;
		if (MoveType == CCharaBase::MOVETYPE_NPC_AI) { nID = MAX_PLAYER; }	// COM�\���ɂ���
		m_pPlayerNum = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), 7.0f, 3.0f, "�v���C�l��");
		m_pPlayerNum->SetTexture(D3DXVECTOR2(0.0f, nID * 0.2f), D3DXVECTOR2(1.0f, (nID * 0.2f) + 0.2f));
		m_pPlayerNum->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


	//�L�������Ƃɓǂݍ��ރt�@�C���𕪂���(�t�@�C�����ł���܂ł͕����Ȃ�)
	switch (PlayerType)
	{
	case TYPE_BARANCE:
		ModelLoad(INU_BARANCE_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(INU_BARANCE_LOADTEXT_LOWER, PlayerType,LOWER_BODY);
		break;
	case TYPE_POWER:
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	case TYPE_SPEED:
		ModelLoad(NECO_SPEED_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(NECO_SPEED_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	case TYPE_REACH:
		ModelLoad(USAGI_REACH_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(USAGI_REACH_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	}

	//�㔼�g�Ɖ����g��A��
	if (m_pPlayerParts[0][0] != NULL &&
		m_pPlayerParts[0][1] != NULL)
	{//�㔼�g�̐e���f���Ɖ����g�̐e���f���̗��������݂��Ă����
		m_pPlayerParts[0][UPPER_BODY]->SetParent(m_pPlayerParts[0][LOWER_BODY]->GetMatrix());	//�㔼�g�̐e�������g
	}

	SetMotion(MOTION_LOWER_NEUTRAL,LOWER_BODY);
	SetMotion(MOTION_UPPER_NEUTRAL, UPPER_BODY);

	//�`��p���f������
	//m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	//m_pPlayerModel->SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�ϐ�������
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	m_nCntTransTime = 0;
	m_pLockOnCharactor = NULL;
	//�R�}���h�Z�b�g
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_RELEASE, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_RELEASE, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("PLAYER_HOMINGSET", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_HOLD, CInputXPad::XPAD_RIGHT_SHOULDER);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//�L�������N���X�폜
	ObjRelease(m_pCharactorMove);

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			ObjRelease(m_pPlayerParts[nCntParts][nCntBody]);
			m_pPlayerParts[nCntParts][nCntBody] = NULL;
		}
	}
	// �v���C���[�ԍ��j��
	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Uninit();
		m_pPlayerNum = NULL;
	}


	// �����Ǘ��N���X�̍폜
	if (m_pWordManager != NULL)
	{
		ObjRelease(m_pWordManager);
	}
	//�v���C���[���̂̍폜
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 testpos;
	D3DXVECTOR3 testmove;
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	if (m_pCharactorMove != NULL &&
		(CManager::GetMode() == CManager::MODE_GAME ||CManager::GetMode() == CManager::MODE_TUTORIAL))
	{
		// �O�̃t���[���̈ʒu���
		m_posOld = m_pCharactorMove->GetPosition();

		//�ړ��A��]�̍X�V
		m_pCharactorMove->Update();
		if (m_nCntTransTime <= 0)
		{
			//�e�Ƃ̓����蔻��
			CollisionDamageObj();
		}

		// ���f���Ƃ̓����蔻��
		if ((CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON)) == true)
		{
			CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		}
		testpos = m_pCharactorMove->GetPosition();
		testmove = m_pCharactorMove->GetMove();

		D3DXVECTOR3 testposFRONT = D3DXVECTOR3(sinf(m_pCharactorMove->GetRotation().y) * 10,
			sinf(m_pCharactorMove->GetRotation().x) * 10,
			cosf(m_pCharactorMove->GetRotation().y) * 10);
		testpos += testposFRONT;
		//�O��Object�����邩�ǂ���
		CollisonObject(&D3DXVECTOR3(testpos.x, testpos.y, testpos.z), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &testmove, PLAYER_COLLISON);



		//�e�ł�(�v���C���[)
		if (m_pCharactorMove->GetMoveType() == C3DCharactor::MOVETYPE_PLAYER_INPUT && m_pCharactorMove->m_bWait == false)
		{
			//�Z�b�g
			CCamera* pCam = pCameraManager->GetCamera(m_ChildCameraName);
			D3DXVECTOR3 BulletRot = m_pCharactorMove->GetRotation();
			D3DXVECTOR3 BulletPos = GetBulletMuzzle();
			float fRotY;
			D3DXVECTOR3 CamRot, LockOnPos, LockOnMove;
			// �e�̐���
			if (CCommand::GetCommand("PLAYER_SHOTBULLET", m_nID) && CGame::GetbStageSet() == false)
			{
				C3DCharactor* Homing = NULL;
				if (m_pWordManager != NULL)
				{//�����Ǘ��N���X�ɒe�̐������ϑ�����
					if (pCam != NULL)
					{
						CamRot = D3DXVECTOR3(-pCam->GetRotation().x, pCam->GetRotation().y, 0.0f);

						BulletRot = CamRot;
						if (m_pLockOnCharactor != NULL)
						{
							Homing = m_pLockOnCharactor;
							LockOnPos = m_pLockOnCharactor->GetPosition();
							LockOnMove = m_pLockOnCharactor->GetMove();

							//���ʂ̌v�Z
							fRotY = atan2f(((LockOnPos.x + (LockOnMove.x * LOCKON_FUTURE_ROTATE)) - BulletPos.x),
								((LockOnPos.z + (LockOnMove.z * LOCKON_FUTURE_ROTATE)) - BulletPos.z)) -
								atan2f(((LockOnPos.x) - BulletPos.x),
								((LockOnPos.z) - BulletPos.z));
							CUtilityMath::RotateNormarizePI(&fRotY);

							//fRotX = atan2f((LockOnPos.y - BulletPos.y),
							//	(LockOnPos.z - BulletPos.z));
							//CUtilityMath::RotateNormarizePI(&fRotX);

							BulletRot.y += fRotY;
							CUtilityMath::RotateNormarizePI(&BulletRot.y);

							//�N�H�[�^�j�I�����g�����v�Z

							//D3DXQUATERNION BaseQuat,AddQuat;
							//D3DXQuaternionIdentity(&BaseQuat);
							//D3DXQuaternionRotationYawPitchRoll(&BaseQuat,BulletRot.y,BulletRot.x,BulletRot.z);	//���̊p�x���N�H�[�^�j�I���ɕϊ�

							////
							//D3DXQuaternionIdentity(&AddQuat);

							//fRotY = atan2f(((LockOnPos.x + (LockOnMove.x * LOCKON_FUTURE_ROTATE)) - BulletPos.x),
							//				((LockOnPos.z + (LockOnMove.z * LOCKON_FUTURE_ROTATE)) - BulletPos.z)) -
							//	    atan2f(((LockOnPos.x) - BulletPos.x),
							//		((LockOnPos.z) - BulletPos.z));
							//CUtilityMath::RotateNormarizePI(&fRotY);

							//fRotX = atan2f((LockOnPos.y - BulletPos.y),
							//	(LockOnPos.z - BulletPos.z));
							//CUtilityMath::RotateNormarizePI(&fRotX);

							//D3DXQuaternionRotationYawPitchRoll(&AddQuat, fRotY, fRotX, 0.0f);	//���������p�x���N�H�[�^�j�I���ɕϊ�

							//D3DXQuaternionMultiply(&BaseQuat,&BaseQuat,&AddQuat);


						}

					}


					//CUtilityMath::RotateNormarizePI(&BulletRot.x);
					//CUtilityMath::RotateNormarizePI(&BulletRot.y);

					m_pWordManager->BulletCreate(m_nID, GetBulletMuzzle(), BulletRot, Homing);
					if (m_pWordManager->GetCntNum() == 0)
					{
						m_bSetupBullet = false;
					}
				}
				m_pLockOnCharactor = NULL;
				if (pCam != NULL)
				{
					pCam->SetLockOnChara(NULL);
				}
				m_bAssist = true;
			}

			if (CCommand::GetCommand("PLAYER_HOMINGSET", m_nID))
			{
				//�e�X�g
				int nPlayer = GetNearPlayer();

				if (m_pLockOnCharactor == NULL)
				{//�܂����b�N�I�����ĂȂ����
					if (m_bAssist == true)
					{
						if (nPlayer != -1)
						{

							if (CManager::GetMode() == CManager::MODE_GAME) { m_pLockOnCharactor = (C3DCharactor*)(CGame::GetPlayer(nPlayer)->GetCharaMover()); }
							if (CManager::GetMode() == CManager::MODE_TUTORIAL) { m_pLockOnCharactor = (C3DCharactor*)(CTutorial::GetPlayer(nPlayer)->GetCharaMover()); }

							if (pCam != NULL)
							{
								pCam->SetLockOnChara(m_pLockOnCharactor);
							}
						}
						else
						{
							m_pLockOnCharactor = NULL;
							if (pCam != NULL)
							{
								pCam->SetLockOnChara(NULL);
							}
							m_bAssist = false;
						}
					}
				}
				else
				{//���b�N�I�����Ă����
					if (nPlayer == -1)
					{
						m_pLockOnCharactor = NULL;
						if (pCam != NULL)
						{
							pCam->SetLockOnChara(NULL);
						}
						m_bAssist = false;
					}
				}
			}
			else
			{
				m_pLockOnCharactor = NULL;
				if (pCam != NULL)
				{
					pCam->SetLockOnChara(NULL);
				}
			}
			CDebugProc::Print("cfcfcf", "PLAYER.BulletRot :", BulletRot.x, " ", BulletRot.y, " ", BulletRot.z);

		}

		//�����Ǘ��N���X�̍X�V
		if (m_pWordManager != NULL)
		{
			if (m_pCharactorMove != NULL && m_pCharactorMove->GetMoveType() == CCharaBase::MOVETYPE_PLAYER_INPUT)
			{
				m_pWordManager->SearchWord();
			}
			m_pWordManager->Update();
		}

	}
	else
	{
		// �O�̃t���[���̈ʒu���
		m_posOld = m_pCharactorMove->GetPosition();
		//�ړ��A��]�̍X�V
		m_pCharactorMove->Update();
		// ���f���Ƃ̓����蔻��
	//	if ((CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON)) == true)
		{
			CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		}
	}

	//���G���Ԃ̃J�E���g�_�E��
	if (m_nCntTransTime > 0)
	{
		m_nCntTransTime--;
	}
	else
	{
		m_nCntTransTime = -1;
		for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
		{
			for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
			{
				if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
				{
					m_pPlayerParts[nCntParts][nCntBody]->SetDrawFlag(true);
				}
			}
		}
	}

	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Setpos(D3DXVECTOR3(m_pCharactorMove->GetPosition().x, m_pCharactorMove->GetPosition().y + 45.0f, m_pCharactorMove->GetPosition().z));
	}

	MotionUpdate(LOWER_BODY);
	MotionUpdate(UPPER_BODY);

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				if (m_nCntTransTime % 2 == 0)
				{//�_���[�W���̓_�ŏ���
					m_pPlayerParts[nCntParts][nCntBody]->SetDrawFlag(!m_pPlayerParts[nCntParts][nCntBody]->GetDrawFlag());
				}

				m_pPlayerParts[nCntParts][nCntBody]->Update();
			}
		}
	}
#ifdef _DEBUG
	testpos = m_pCharactorMove->GetPosition();
	testmove = m_pCharactorMove->GetMove();

	CDebugProc::Print("cfcfcf", "PLAYER.Pos :", testpos.x, " ", testpos.y, " ", testpos.z);
	CDebugProc::Print("cfcfcf", "PLAYER.Move :", testmove.x, " ", testmove.y, " ", testmove.z);
	CDebugProc::Print("cn", "PLAYER.LockOn : ", m_pLockOnCharactor != NULL ? 1 : 0);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���C�g�̖�����
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->Draw();
			}
		}
	}
	// ���C�g�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

}
//=============================================================================
// ���[�V�����X�V����
//=============================================================================
void CPlayer::MotionUpdate(BODY body)
{
	KeyProperty pKey, pKeyNext;

	float fFlameMotion;
	int nFutureKey;
	D3DXVECTOR3 aKeyPos[PLAYER_MODELNUM];
	D3DXVECTOR3 aKeyRot[PLAYER_MODELNUM];
	m_nCntFlame[body]++;

	switch (m_Mstate[body])
	{
	case STATE_NORMAL:
		nFutureKey = (m_nCntKey[body] + 1) % (m_propMotion[m_motion[body]][body].nKeyNum);
		pKey = m_propMotion[m_motion[body]][body].key[m_nCntKey[body]];
		pKeyNext = m_propMotion[m_motion[body]][body].key[nFutureKey];

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				//���݂̊p�x���擾
				D3DXVECTOR3 rot = m_pPlayerParts[nCntParts][body]->GetRotation();

				//���݂̃L�[���玟�̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
				fFlameMotion = (float)(m_nCntFlame[body] + 1) / ((float)pKey.nFrame);

				//���݂̃L�[���玟�̃L�[�ւ̊p�x�̍������Z�o
				aKeyRot[nCntParts].x = (pKeyNext.Rot[nCntParts].x - pKey.Rot[nCntParts].x);
				aKeyRot[nCntParts].y = (pKeyNext.Rot[nCntParts].y - pKey.Rot[nCntParts].y);
				aKeyRot[nCntParts].z = (pKeyNext.Rot[nCntParts].z - pKey.Rot[nCntParts].z);

				//���߂����������݂̃L�[�ɌW�����|���Ȃ��瑫��
				rot = pKey.Rot[nCntParts] + (aKeyRot[nCntParts] * fFlameMotion);

				if (nCntParts == 0 && body == LOWER_BODY)
				{
					rot.y = 3.14f;
				}

				//�p�x�̐��K��
				CUtilityMath::RotateNormarizePI(&rot.x);
				CUtilityMath::RotateNormarizePI(&rot.y);
				CUtilityMath::RotateNormarizePI(&rot.z);

				m_pPlayerParts[nCntParts][body]->SetRotation(rot);
			}
		}

		if (m_nCntFlame[body] == m_propMotion[m_motion[body]][body].key[m_nCntKey[body]].nFrame)
		{//����̃t���[�����o�߂�����

			m_nCntFlame[body] = 0;
			m_nCntKey[body]++;	//�L�[�����Z
			if (m_nCntKey[body] >= m_propMotion[m_motion[body]][body].nKeyNum)
			{//�L�[������̐��l�ɒB������
				m_nCntKey[body] = 0;
				if (m_propMotion[m_motion[body]][body].nLoop == 0)
				{
					if (m_pWordManager->GetBulletFlag())
					{
						SetMotion(MOTION_UPPER_SETUP_NEUTRAL, UPPER_BODY);
					}
					else
					{
						SetMotion(MOTION_UPPER_NEUTRAL, UPPER_BODY);
					}

					SetMotion(MOTION_LOWER_NEUTRAL, LOWER_BODY);
				}
			}
		}
		break;
	case STATE_BLEND:
		if (m_motion[body] == 0)
		{
			pKey();
		}
		else
		{
			pKey = m_propMotion[m_OldMotion[body]][body].key[m_nCntKey[body]];
		}
		pKeyNext = m_propMotion[m_motion[body]][body].key[0];

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				//���݂̊p�x���擾
				D3DXVECTOR3 rot = m_pPlayerParts[nCntParts][body]->GetRotation();

				//�u�����h�W�����Z�o
				fFlameMotion = (float)(m_nCntBlendMotion[body] + 1) / MOTION_BLENDTIME;

				//���݂̃L�[���玟�̃L�[�ւ̊p�x�̍������Z�o
				aKeyRot[nCntParts].x = (pKeyNext.Rot[nCntParts].x - pKey.Rot[nCntParts].x);
				aKeyRot[nCntParts].y = (pKeyNext.Rot[nCntParts].y - pKey.Rot[nCntParts].y);
				aKeyRot[nCntParts].z = (pKeyNext.Rot[nCntParts].z - pKey.Rot[nCntParts].z);

				//���߂����������݂̃L�[�ɌW�����|���Ȃ��瑫��
				rot = pKey.Rot[nCntParts] + (aKeyRot[nCntParts] * fFlameMotion);

				if (nCntParts == 0 && body == LOWER_BODY)
				{
					rot.y = 3.14f;
				}

				//�p�x�̐��K��
				CUtilityMath::RotateNormarizePI(&rot.x);
				CUtilityMath::RotateNormarizePI(&rot.y);
				CUtilityMath::RotateNormarizePI(&rot.z);

				m_pPlayerParts[nCntParts][body]->SetRotation(rot);
			}
		}

		m_nCntBlendMotion[body]++;
		if (m_nCntBlendMotion[body] >= MOTION_BLENDTIME)
		{//����̃t���[�����o�߂�����
			m_nCntBlendMotion[body] = 0;
			m_nCntKey[body] = 0;
			m_Mstate[body] = STATE_NORMAL;
		}
		break;
	}
	CDebugProc::Print("cn","MOTION = ",(int)m_motion[body]);
}

//=============================================================================
// ���[�V�����ݒ菈��
//=============================================================================
void	CPlayer::SetMotion(int motion, BODY body,MOTION_STATE state)
{
	if (motion != m_motion[body])
	{//���ݓ����Ă��郂�[�V�����ƈႤ���̂ł����
		//��O�̃��[�V������ۑ�����
		m_OldMotion[body] = m_motion[body];

		//���̑��ϐ��̏�����
		m_nCntBlendMotion[body] = 0;
		m_nCntFlame[body] = 0;
		if (state != STATE_BLEND)
		{
			if (m_Mstate[body] == STATE_BLEND)
			{//��O���u�����h�Ȃ�
				for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
				{
					if (m_pPlayerParts[nCntParts][body] != NULL)
					{
						//�u�����h���Ɏ��̃��[�V�����ɓ�������
						m_pPlayerParts[nCntParts][body]->SetRotation(m_propMotion[m_OldMotion[body]][body].key[0].Rot[nCntParts]);
					}
				}
			}
			m_nCntKey[body] = 0;
		}	//�u�����h���鎞�͏��������Ȃ�

		//�������
		m_motion[body] = motion;
		m_Mstate[body] = state;

	}
}

//=============================================================================
// �����蔻��(�e)����
//=============================================================================
bool CPlayer::CollisionDamageObj(void)
{
	bool bHit = false;
	CScene *pScene = NULL;
	CSound *pSound = CManager::GetSound();		//	���̎擾

	D3DXVECTOR3 PlayerPos = m_pCharactorMove->GetPosition();
	D3DXVECTOR3 ObjPos,ObjRot;
	float fObjSize = 0.0f;

	/*�e�Ƃ̓����蔻��*/
	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(BULLET_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_BULLET)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				C3DBullet *pBullet = ((C3DBullet*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
				ObjPos = pBullet->GetPosition();
				ObjRot = pBullet->GetRotation();

				float X = (ObjPos.x - PlayerPos.x) * (ObjPos.x - PlayerPos.x);
				float Y = (ObjPos.y - PlayerPos.y) * (ObjPos.y - PlayerPos.y);
				float Z = (ObjPos.z - PlayerPos.z) * (ObjPos.z - PlayerPos.z);

				if(sqrtf(X + Y + Z) < BULLET_COLLISION_SIZE &&
					m_nID != pBullet->GetID())
				{//���̔���

					/*���_���Z (���Ă��L������ID��pBullet��GetID�Ŏ擾�ł���)*/
					if (pBullet->GetType() == C3DBullet::TYPE_MODEL)
					{	// ���f���̏ꍇ�̓|�C���g���Z
						CPoint *pPoint = NULL;
						if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(pBullet->GetID()); }
						if (CManager::GetMode() == CManager::MODE_TUTORIAL) { pPoint = CTutorial::GetPoint(pBullet->GetID()); }

						CModelBullet *pModelBullet = ((CModelBullet*)pBullet);

						int nPoint = 0;
						if (pModelBullet->GetType() == CModelBullet::TYPE_NORMAL) { nPoint = 1; }
						else if (pModelBullet->GetType() != CModelBullet::TYPE_NORMAL) { nPoint = 3; }

						if (pPoint != NULL) { pPoint->AddPoint(nPoint); }
						pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTUP, 3.0f);
						pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTUP);

						C3DBullet *pBullet = ((C3DBullet*)pModelBullet);		// CBulletBase�փL���X�g(�^�̕ύX)
					}

					//������΂�
					DamageReaction(pBullet->GetKnockBackPower(),ObjRot);

					//�e�폜
					pBullet->Uninit();

					return true;
				}
			}
		}
		pScene = pSceneNext;
	}

	/*����*/
	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(EXPLOSION_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ��e�Ɠ����I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_EXPLOSION)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				CExplosion3D* pExp = (CExplosion3D*)pScene;
				ObjPos = pExp->GetPosition();
				fObjSize = pExp->GetSize();

				float fRot = atan2f((ObjPos.x - PlayerPos.x),(ObjPos.z - PlayerPos.z)) + D3DX_PI;
				float X = (ObjPos.x - PlayerPos.x) * (ObjPos.x - PlayerPos.x);
				float Y = (ObjPos.y - PlayerPos.y) * (ObjPos.y - PlayerPos.y);
				float Z = (ObjPos.z - PlayerPos.z) * (ObjPos.z - PlayerPos.z);

				CUtilityMath::RotateNormarizePI(&fRot);
				if (sqrtf(X + Y + Z) < fObjSize)
				{
					//������΂�
					DamageReaction(20.0f, D3DXVECTOR3(0.0f,fRot,0.0f));
					return true;
				}

			}
		}
		pScene = pSceneNext;
	}

	return false;
}

//=============================================================================
// �_���[�W�̔�������
//=============================================================================
void CPlayer::DamageReaction(float fDamageValue, D3DXVECTOR3 HitRotation)
{
	D3DXVECTOR3& move = m_pCharactorMove->GetMove();

	//
	move.x += sinf(HitRotation.y) * fDamageValue * 2.0f;
	move.z += cosf(HitRotation.y) * fDamageValue * 2.0f;

	move.y += fDamageValue;
	m_nCntTransTime = 30;
}
//=============================================================================
// �����蔻��(�I�u�W�F�N�g)����
//=============================================================================
bool CPlayer::CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * move, D3DXVECTOR3 radius)
{
	bool bHit = false;
	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(SCENEX_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneX�փL���X�g(�^�̕ύX)
				if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
				{
					m_bLand = pSceneX->Collision(pos, posOld, move, radius);

					CObject *pSceneObj = ((CObject*)pSceneX);		// CObject�փL���X�g(�^�̕ύX)
					if (m_bLand == true)
					{// ���f���ɓ�����
						bHit = true;

						if (pSceneObj->GetRealTimeType() == CObject::REALTIME_NOTMOVE)
						{
							if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
								pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
							{	// �x���g�R���x�A�̔���
								pSceneObj->BeltConveyor(move, pSceneObj->GetSwitch());
							}
							else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING ||
								pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
							{	// �m�b�N�o�b�N�̔���
								pSceneObj->KnockBack(move, m_nID);
							}
							else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_SWITCH)
							{//	�X�C�b�`
								pSceneObj->SwitchBeltConveyor(m_bLand);
							}
						}
						else if (pSceneObj->GetRealTimeType() == CObject::REALTIME_INITPOS)
						{
							pSceneObj->AffectedLanding(move, m_nID);		// �����Ă��郂�f���̒��n���̉e��
						}
						else if (pSceneObj->GetCollsionType() == CSceneX::COLLISIONTYPE_BOX)
						{
						}
						break;
					}
					else
					{
						bHit = false;
					}
				}
			}
		}
		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
	return bHit;
}
//=============================================================================
// �߂��v���C���[���擾���鏈��
//=============================================================================
int		CPlayer::GetNearPlayer(void)
{
	D3DXVECTOR3 PlayerPos[4] = {};
	D3DXVECTOR3 PlayerRot[4] = {};
	CCharaBase* pChara = NULL;
	CPlayer* pPlayer = NULL;
	int nCntPlayer = 0;
	//�l�̎擾
	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pChara = NULL;
		pPlayer = NULL;
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			pPlayer = CGame::GetPlayer(nCntPlayer);
		}
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			pPlayer = CTutorial::GetPlayer(nCntPlayer);
		}

		if (pPlayer != NULL)
		{
			pChara = pPlayer->GetCharaMover();
			if (pChara != NULL)
			{//�L�����N���X���ɂ�����W���擾
				PlayerPos[nCntPlayer] = pChara->GetPosition();
				PlayerRot[nCntPlayer] = pChara->GetRotation();	//��r�Ɏg������y�̒l�Ƀ΂𑫂�
			}
			else
			{//�L�����N���X���������ꍇ������Ȓl������
				PlayerPos[nCntPlayer] = D3DXVECTOR3(-99999.9f, -99999.9f, -99999.9f);
				PlayerRot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else
		{	//�v���C���[�����Ȃ��ꍇ�͋���Ȓl������
			PlayerPos[nCntPlayer] = D3DXVECTOR3(-99999.9f, -99999.9f, -99999.9f);
			PlayerRot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//�l�̔�r
	float fNearLength = 99999.9f;
	int nPlayerNum = -1;
	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != m_nID)
		{//�����ȊO�Ɣ�����s��

			//�������擾(-�͏Ȃ�)
			float fLength = fabsf(sqrtf(powf(PlayerPos[m_nID].x - PlayerPos[nCntPlayer].x, 2.0f) +
				powf(PlayerPos[m_nID].y - PlayerPos[nCntPlayer].y, 2.0f) +
				powf(PlayerPos[m_nID].z - PlayerPos[nCntPlayer].z, 2.0f)));

			//�p�x��r
				if (fLength < fNearLength &&
					fLength < PLAYER_LOCKON_LENGTH)
				{
					nPlayerNum = nCntPlayer;
					fNearLength = fLength;
				}
		}
	}
	return nPlayerNum;
}

//=============================================================================
// ���f�����[�h����
//=============================================================================
HRESULT CPlayer::ModelLoad(LPCSTR pFileName, PLAYER_TYPE type, BODY body, bool bReLoad)
{
	FILE* pFile = NULL;		// �t�@�C���|�C���^
	char ReadText[256];		// �ǂݍ��񂾕���������Ă���
	char HeadText[256];		// ��r�p
	char DustBox[256];		// �g�p���Ȃ����̂����Ă���

	int nCntMotionSetType = 0;					// ���[�V�����Z�b�g�̎�ނ̐�
	int nCntMotionType = 1;						// ���[�V�����̎�ނ̐�
	int nCntKeySet = 0;							// �L�[�Z�b�g��
	int nCntKey = 0;							// �L�[��
	int nCntPartsSet = 0;						// �p�[�c��
	int nCntFileNameNum = 0;
	int nPartsNum = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			ObjRelease(m_pPlayerParts[nCntParts][body]);
			m_pPlayerParts[nCntParts][body] = NULL;
		}
	if (m_PlayerLoadState[type][body].bLoad == false ||
		(m_PlayerLoadState[type][body].bLoad == true && bReLoad == true))
	{//	�܂����̏�񂪃��[�h����Ă��Ȃ�or����Ă��邪�ēx���[�h���������
		for (int nCntMotion = 0; nCntMotion < MOTION_UPPER_MAX; nCntMotion++)
		{
			m_PlayerLoadState[type][body].prop[nCntMotion]();
		}

		//�t�@�C���I�[�v��
		pFile = fopen(pFileName, "r");

		if (pFile != NULL)
		{//�t�@�C�����J����Ă����
			while (strcmp(HeadText, "SCRIPT") != 0)
			{// "SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);
			}
			if (strcmp(HeadText, "SCRIPT") == 0)
			{// "SCRIPT" ���ǂݎ�ꂽ�ꍇ�A�����J�n
				while (strcmp(HeadText, "END_SCRIPT") != 0)
				{// "END_SCRIPT" ���ǂݍ��܂��܂ŌJ��Ԃ��������ǂݎ��
					fgets(ReadText, sizeof(ReadText), pFile);
					sscanf(ReadText, "%s", &HeadText);

					if (strcmp(HeadText, "\n") == 0)
					{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

					}
					else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
					{
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, m_PlayerLoadState[type][body].info[nCntFileNameNum].FileName);
						nCntFileNameNum++;
					}
					else if (strcmp(HeadText, "CHARACTERSET") == 0)
					{//�L����
						while (strcmp(HeadText, "END_CHARACTERSET") != 0)
						{// "END_CHARACTERSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
							fgets(ReadText, sizeof(ReadText), pFile);
							sscanf(ReadText, "%s", &HeadText);
							if (strcmp(HeadText, "\n") == 0)
							{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

							}
							if (strcmp(HeadText, "NUM_PARTS") == 0)
							{
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].nPartsNum);
							}
							else if (strcmp(HeadText, "PARTSSET") == 0)
							{//PARTSSET��ǂ݂Ƃ�����
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "\n") == 0)
									{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

									}
									else if (strcmp(HeadText, "INDEX") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].info[nCntPartsSet].nIndex);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].info[nCntPartsSet].nParent);
									}
									else if (strcmp(HeadText, "POS") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.x,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.y,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.x,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.y,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.z);
									}
								}
								nCntPartsSet++;

							}
						}
					}
					else if (strcmp(HeadText, "MOTIONSET") == 0)
					{//���[�V����
						while (strcmp(HeadText, "END_MOTIONSET") != 0)
						{// "END_MOTIONSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
							fgets(ReadText, sizeof(ReadText), pFile);
							sscanf(ReadText, "%s", &HeadText);

							if (strcmp(HeadText, "\n") == 0)
							{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

							}
							else if (strcmp(HeadText, "LOOP") == 0)
							{//���[�v
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
									&m_PlayerLoadState[type][body].prop[nCntMotionType].nLoop);
							}
							else if (strcmp(HeadText, "NUM_KEY") == 0)
							{//�L�[��
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
									&m_PlayerLoadState[type][body].prop[nCntMotionType].nKeyNum);
							}
							else if (strcmp(HeadText, "KEYSET") == 0)
							{
								while (strcmp(HeadText, "END_KEYSET") != 0)
								{// "END_KEYSET" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);
									if (strcmp(HeadText, "\n") == 0)
									{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

									}
									else if (strcmp(HeadText, "FRAME") == 0)
									{//��ԃt���[��
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
											&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].nFrame);
									}
									else if (strcmp(HeadText, "KEY") == 0)
									{//�L�[���
										while (strcmp(HeadText, "END_KEY") != 0)
										{// "END_KEY" ���ǂݎ���܂ŌJ��Ԃ��������ǂݎ��
											fgets(ReadText, sizeof(ReadText), pFile);
											sscanf(ReadText, "%s", &HeadText);

											if (strcmp(HeadText, "\n") == 0)
											{// ������̐擪�� [\n](���s) �̏ꍇ�������Ȃ�

											}
											else if (strcmp(HeadText, "POS") == 0)
											{//���W
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].z);
											}
											else if (strcmp(HeadText, "ROT") == 0)
											{//�p�x
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].z);
											}

										}
										nCntKey++;
									}
								}
								nCntKeySet++;
								nCntKey = 0;
							}
						}
						nCntMotionType++;
						nCntKeySet = 0;
					}
				}
				nCntMotionType = 0;
			}

		}
		fclose(pFile);
		m_PlayerLoadState[type][body].bLoad = true;
	}

	//���ݒ�
	int nCntParts = 0;
		for (nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
		{

			if (ObjCreate(m_pPlayerParts[nCntParts][body]))
			{//�������ꂽ��

				m_pPlayerParts[nCntParts][body]->Set(m_PlayerLoadState[type][body].info[nCntParts].FileName,
					m_PlayerLoadState[type][body].info[nCntParts].pos,
					m_PlayerLoadState[type][body].info[nCntParts].rot, NULL);

				switch (type)
				{//�^�C�v���Ƃ̏���
				case TYPE_BARANCE:
					m_pPlayerParts[nCntParts][body]->BindTexture("INU_UV");
					break;
				case TYPE_POWER:
					m_pPlayerParts[nCntParts][body]->BindTexture("KUMA_UV");
					break;
				case TYPE_SPEED:
					m_pPlayerParts[nCntParts][body]->BindTexture("NECO_UV");
					break;
				case TYPE_REACH:
					m_pPlayerParts[nCntParts][body]->BindTexture("USAGI_UV");
					break;
				}
			}
		}

	//�e�}�g���N�X�Z�b�g
	for (int nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
	{
		int nNum = m_PlayerLoadState[type][body].info[nCntParts].nParent;
		if (nNum != -1)
		{
			m_pPlayerParts[nCntParts][body]->SetParent(m_pPlayerParts[nNum][body]->GetMatrix());
		}
		else
		{
			m_pPlayerParts[nCntParts][body]->SetParent(m_pCharactorMove->GetMatrix());
		}
	}

	//���[�V��������ǂݍ��ݕϐ�����R�s�[
	for (int nCntMotion = 0; nCntMotion < (body == LOWER_BODY ? MOTION_LOWER_MAX : MOTION_UPPER_MAX); nCntMotion++)
	{//(body == LOWER_BODY ? MOTION_LOWER_MAX : MOTION_UPPER_MAX) : �㉺�̃��[�V�������ɉ����ă��[�v����ς���
		m_propMotion[nCntMotion][body] = m_PlayerLoadState[type][body].prop[nCntMotion];
	}
	return S_OK;
}

//=============================================================================
// ���f�����[�h����
//=============================================================================
D3DXVECTOR3     CPlayer::GetBulletMuzzle(void)
{
	if (m_pPlayerParts[8][UPPER_BODY] != NULL)
	{
		return m_pPlayerParts[8][UPPER_BODY]->GetWorldPosition();
	}
	else
	{
		if (m_pCharactorMove != NULL)
		{
			return m_pCharactorMove->GetPosition() + D3DXVECTOR3(0.0f,10.0f,0.0f);
		}
	}
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}