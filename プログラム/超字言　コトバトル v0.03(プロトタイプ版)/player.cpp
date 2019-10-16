//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "manager.h"

#include "sceneX.h"

#include "debugProc.h"

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
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot,type,this);
		}
	}
	m_nID = (nPlayerID % 4);//�͈͊O�̐������������炻���0�`3�܂ł̐����ɂ���

	m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	m_pPlayerModel->SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	m_pPlayerModel = NULL;
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPlayer::Uninit(void)
{
	ObjRelease(m_pCharactorMove);

	if (m_pPlayerModel != NULL)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = NULL;
	}

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

		m_pCharactorMove->Update();
		// ���f���Ƃ̓����蔻��
		CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);

		m_pPlayerModel->SetPosition(m_pCharactorMove->GetPosition());
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
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

}

//=============================================================================
// �����蔻�菈��
//=============================================================================
void CPlayer::CollisonObject(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * move, D3DXVECTOR3 radius)
{
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
				m_bLand = ((CSceneX*)pScene)->Collision(pos, posOld, move, radius);
				if (m_bLand == true)
				{// ���f���ɓ�����
				}
			}
		}
		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}
