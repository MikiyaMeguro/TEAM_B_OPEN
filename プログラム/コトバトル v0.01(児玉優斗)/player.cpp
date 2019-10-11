//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "manager.h"

#include "sceneX.h"
//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{

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
void CPlayer::Set(D3DXVECTOR3 pos, CCharaBase::CHARACTOR_MOVE_TYPE type, D3DXVECTOR3 rot)
{
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot,type,this);
		}
	}

	m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER);
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
	if (m_pCharactorMove != NULL)
	{
		m_pCharactorMove->Update();
		m_pPlayerModel->SetPosition(m_pCharactorMove->GetPosition());
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPlayer::Draw(void)
{

}