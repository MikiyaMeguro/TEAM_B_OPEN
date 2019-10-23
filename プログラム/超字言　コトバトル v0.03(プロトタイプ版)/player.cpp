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

#include "sceneX.h"

#include "debugProc.h"
#include "bullet.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 20.0f, 5.0f))			//�L�����N�^�[�̓����蔻��

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_bLand = false;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pWordManager = NULL;
	m_nCntTransTime = 0;
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

	//�`��p���f������
	m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	m_pPlayerModel->SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//�ϐ�������
	m_pPlayerModel = NULL;
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	m_nCntTransTime = 0;
	//�R�}���h�Z�b�g
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_LEFT_SHOULDER);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	//�L�������N���X�폜
	ObjRelease(m_pCharactorMove);

	//�`�惂�f���I������
	if (m_pPlayerModel != NULL)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = NULL;
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
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
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

		//�`�悷�郂�f���ɏ�������
		m_pPlayerModel->SetPosition(m_pCharactorMove->GetPosition());
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
	}

	// �e�̐���
	if (CCommand::GetCommand("PLAYER_SHOTBULLET",m_nID))
	{
		if (m_pWordManager != NULL)
		{//�����Ǘ��N���X�ɒe�̐������ϑ�����
			m_pWordManager->BulletCreate(m_nID);
		}
	}

	//�����Ǘ��N���X�̍X�V
	if (m_pWordManager != NULL) { m_pWordManager->Update(); }

	//���G���Ԃ̃J�E���g�_�E��
	if (m_nCntTransTime > 0)
	{
		m_nCntTransTime--;

		if (m_nCntTransTime % 2 == 0)
		{
			m_pPlayerModel->SetDrawFlag(!(m_pPlayerModel->GetDrawFlag()));
		}
	}
	else
	{
		m_pPlayerModel->SetDrawFlag(true);
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
	//���f����Scene�N���X�̎q���Ȃ̂Ōʂ�Draw�͕K�v�Ȃ�
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
