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

CPlayer::PlayerLoadState CPlayer::m_PlayerLoadState[CPlayer::TYPE_MAX];
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 20.0f, 5.0f))			//�L�����N�^�[�̓����蔻��
#define MODEL_LOAD_TEXT "data/MOTION/motion_bea.txt"
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

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		m_pPlayerParts[nCntParts] = NULL;
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
void CPlayer::Set(D3DXVECTOR3 pos, CCharaBase::CHARACTOR_MOVE_TYPE type, int nPlayerID, D3DXVECTOR3 rot)
{
	//�L�������N���X����
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot,type,this);
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
		if (type == CCharaBase::MOVETYPE_NPC_AI) { nID = MAX_PLAYER; }	// COM�\���ɂ���
		m_pPlayerNum = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), 7.0f, 3.0f, "�v���C�l��");
		m_pPlayerNum->SetTexture(D3DXVECTOR2(0.0f, nID * 0.2f), D3DXVECTOR2(1.0f, (nID * 0.2f) + 0.2f));
		m_pPlayerNum->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


	ModelLoad(MODEL_LOAD_TEXT,TYPE_POWER);

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

	//�R�}���h�Z�b�g
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_RIGHT_SHOULDER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//�L�������N���X�폜
	ObjRelease(m_pCharactorMove);

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		ObjRelease(m_pPlayerParts[nCntParts]);
		m_pPlayerParts[nCntParts] = NULL;
	}

	// �v���C���[�ԍ��j��
	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Uninit();
		m_pPlayerNum = NULL;
	}


	// �����Ǘ��N���X�̍폜
	ObjRelease(m_pWordManager);

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

	if (m_pCharactorMove != NULL)
	{
		// �O�̃t���[���̈ʒu���
		m_posOld = m_pCharactorMove->GetPosition();

		//�ړ��A��]�̍X�V
		m_pCharactorMove->Update();
		if (m_nCntTransTime <= 0)
		{
			//�e�Ƃ̓����蔻��
			CollisionBullet();
		}

		// ���f���Ƃ̓����蔻��
		CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		testpos = m_pCharactorMove->GetPosition();
		testmove = m_pCharactorMove->GetMove();

		D3DXVECTOR3 testposFRONT = D3DXVECTOR3(sinf(m_pCharactorMove->GetRotation().y) * 10,
			sinf(m_pCharactorMove->GetRotation().x) * 10,
			cosf(m_pCharactorMove->GetRotation().y) * 10);
		testpos += testposFRONT;
		//�O��Object�����邩�ǂ���
		CollisonObject(&D3DXVECTOR3(testpos.x, testpos.y, testpos.z), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &testmove, PLAYER_COLLISON);

	}

	// �e�̐���
	if (CCommand::GetCommand("PLAYER_SHOTBULLET",m_nID))
	{
		if (m_pWordManager != NULL)
		{//�����Ǘ��N���X�ɒe�̐������ϑ�����
			m_pWordManager->BulletCreate(m_nID,m_pCharactorMove->GetPosition() + D3DXVECTOR3(0.0f,10.0f,0.0f));
			if (m_pWordManager->GetCntNum() == 0)
			{
				m_bSetupBullet = false;
			}
		}
	}

	//�����Ǘ��N���X�̍X�V
	if (m_pWordManager != NULL) { m_pWordManager->Update(); }

	//���G���Ԃ̃J�E���g�_�E��
	if (m_nCntTransTime > 0)
	{
		m_nCntTransTime--;
	}
	else
	{
		m_nCntTransTime = -1;
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts] != NULL)
			{
				m_pPlayerParts[nCntParts]->SetDrawFlag(true);
			}
		}
	}

	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Setpos(D3DXVECTOR3(m_pCharactorMove->GetPosition().x, m_pCharactorMove->GetPosition().y + 45.0f, m_pCharactorMove->GetPosition().z));
	}

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{

		if (m_pPlayerParts[nCntParts] != NULL)
		{
			if (m_nCntTransTime % 2 == 0)
			{//�_���[�W���̓_�ŏ���
				m_pPlayerParts[nCntParts]->SetDrawFlag(!m_pPlayerParts[nCntParts]->GetDrawFlag());
			}

			m_pPlayerParts[nCntParts]->Update();
		}
	}

#ifdef _DEBUG
	testpos = m_pCharactorMove->GetPosition();
	testmove = m_pCharactorMove->GetMove();

	CDebugProc::Print("cfcfcf", "PLAYER.Pos :", testpos.x," ",testpos.y, " ", testpos.z);
	CDebugProc::Print("cfcfcf", "PLAYER.Move :", testmove.x, " ", testmove.y, " ", testmove.z);
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		if (m_pPlayerParts[nCntParts] != NULL)
		{
			m_pPlayerParts[nCntParts]->Draw();
		}
	}
}
//=============================================================================
// ���[�V�����X�V����
//=============================================================================
void CPlayer::MotionUpdate(void)
{

}

//=============================================================================
// ���[�V�����ݒ菈��
//=============================================================================
void	CPlayer::SetNextMotion(MOTION motion)
{
	m_NextMotion = motion;
	m_MotionState = STATE_BLEND;
	m_nCntBlendMotion = 0;
}

//=============================================================================
// �����蔻��(�e)����
//=============================================================================
bool CPlayer::CollisionBullet(void)
{
	bool bHit = false;
	CScene *pScene = NULL;

	D3DXVECTOR3 PlayerPos = m_pCharactorMove->GetPosition();
	D3DXVECTOR3 BulletPos,BulletRot;

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
				CBulletBase *pBullet = ((CBulletBase*)pScene);		// CBulletBase�փL���X�g(�^�̕ύX)
				BulletPos = pBullet->GetPosition();
				BulletRot = pBullet->GetRotation();

				float X = (BulletPos.x - PlayerPos.x) * (BulletPos.x - PlayerPos.x);
				float Y = (BulletPos.y - PlayerPos.y) * (BulletPos.y - PlayerPos.y);
				float Z = (BulletPos.z - PlayerPos.z) * (BulletPos.z - PlayerPos.z);

				if(sqrtf(X + Y + Z) < BULLET_COLLISION_SIZE &&
					m_nID != pBullet->GetID())
				{//���̔���

					/*���_���Z (���Ă��L������ID��pBullet��GetID�Ŏ擾�ł���)*/
					if (pBullet->GetType() == CBulletBase::TYPE_MODEL)
					{	// ���f���̏ꍇ�̓|�C���g���Z
						CPoint *pPoint = NULL;
						if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(pBullet->GetID()); }
						if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /*�`���[�g���A���Ŏ擾����*/ }

						if (pPoint != NULL) { pPoint->AddPoint(1); }
					}

					//������΂�
					DamageReaction(10.0f,BulletRot);

					//�e�폜
					pBullet->Uninit();

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
					if (m_bLand == true)
					{// ���f���ɓ�����
						bHit = true;
						CObject *pSceneObj = ((CObject*)pSceneX);		// CObject�փL���X�g(�^�̕ύX)
						if (pSceneObj->GetRealTimeType() == CObject::REALTIME_NONE)
						{
							if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
								pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
							{	// �x���g�R���x�A�̔���
								pSceneObj->BeltConveyor(move);
							}
							else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING ||
								pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
							{	// �m�b�N�o�b�N�̔���
								pSceneObj->KnockBack(move);
							}
						}
						break;
					}
					else
					{
						CObject *pSceneObj = ((CObject*)pSceneX);		// CObject�փL���X�g(�^�̕ύX)
						if (pSceneObj->GetRealTimeType() == CObject::REALTIME_INITPOS) 
						{
							if (pos->y + 10.0f > pSceneObj->GetPosition().y - pSceneObj->GetVtxMin().y) 
							{
								move->x = 2.0f; 
							}
						}
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
// ���f�����[�h����
//=============================================================================
HRESULT CPlayer::ModelLoad(LPCSTR pFileName, PLAYER_TYPE type)
{
	FILE* pFile = NULL;		// �t�@�C���|�C���^
	char ReadText[256];		// �ǂݍ��񂾕���������Ă���
	char HeadText[256];		// ��r�p
	char DustBox[256];		// �g�p���Ȃ����̂����Ă���

	int nCntMotionSetType = 0;					// ���[�V�����Z�b�g�̎�ނ̐�
												//int nCntMotionType = (int)MOTION_NEUTRAL;	// ���[�V�����̎�ނ̐�
	int nCntKeySet = 0;							// �L�[�Z�b�g��
	int nCntKey = 0;							// �L�[��
	int nCntPartsSet = 0;						// �p�[�c��
	int nCntFileNameNum = 0;
	PartsLoadInfo LoadInfo[PLAYER_MODELNUM];		//���[�h���
	int nPartsNum = 0;

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		ObjRelease(m_pPlayerParts[nCntParts]);
		m_pPlayerParts[nCntParts] = NULL;
	}

	if (m_PlayerLoadState[type].bFlag == false)
	{//	�܂����̏�񂪃��[�h����Ă��Ȃ����
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
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, m_PlayerLoadState[type].info[nCntFileNameNum].FileName);
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
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type].nPartsNum);
							}
							else if (strcmp(HeadText, "PARTSSET") == 0)
							{//PARTSSET��ǂ݂Ƃ�����
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "INDEX") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type].info[nCntPartsSet].nIndex);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type].info[nCntPartsSet].nParent);
									}
									else if (strcmp(HeadText, "POS") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type].info[nCntPartsSet].pos.x,
											&m_PlayerLoadState[type].info[nCntPartsSet].pos.y,
											&m_PlayerLoadState[type].info[nCntPartsSet].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type].info[nCntPartsSet].rot.x,
											&m_PlayerLoadState[type].info[nCntPartsSet].rot.y,
											&m_PlayerLoadState[type].info[nCntPartsSet].rot.z);
									}
								}
								nCntPartsSet++;

							}
						}
					}
				}
			}

		}
		fclose(pFile);
	}

	int nCntParts = 0;
	for (nCntParts = 0; nCntParts < m_PlayerLoadState[type].nPartsNum; nCntParts++)
	{
		ObjCreate(m_pPlayerParts[nCntParts]);
		if (m_pPlayerParts[nCntParts] != NULL)
		{
			m_pPlayerParts[nCntParts]->Set(m_PlayerLoadState[type].info[nCntParts].FileName,
				m_PlayerLoadState[type].info[nCntParts].pos,
				m_PlayerLoadState[type].info[nCntParts].rot, NULL);
		}
	}

	//�e�}�g���N�X�Z�b�g
	for (int nCntParts = 0; nCntParts < m_PlayerLoadState[type].nPartsNum; nCntParts++)
	{
		int nNum = m_PlayerLoadState[type].info[nCntParts].nParent;
		if (nNum != -1)
		{
			m_pPlayerParts[nCntParts]->SetParent(m_pPlayerParts[nNum]->GetMatrix());
		}
		else
		{
			m_pPlayerParts[nCntParts]->SetParent(m_pCharactorMove->GetMatrix());
		}
	}

	m_PlayerLoadState[TYPE_POWER].bFlag = true;
	return S_OK;
}


