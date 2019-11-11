//=============================================================================
//
// �e��{���� (C3DBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "manager.h"

#include "load.h"
#include "sceneBillboard.h"
#include "sceneX.h"
#include "game.h"
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CBulletBase)
//=============================================================================
C3DBullet::C3DBullet(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
	m_fKnockBack = 0.0f;
}
C3DBullet::~C3DBullet()
{

}

//=============================================================================
// �ݒ菈��(CBulletBase)
//=============================================================================
void C3DBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nID)
{
	m_pos = pos;
	m_rot = rot;
	m_fMove = fSpeed;
	m_nLife = nLife;

	m_nID = (nID % 4);//�͈͊O�̐������������炻���0�`3�܂ł̐����ɂ���

	m_fKnockBack = 7.0f;
}

//=============================================================================
// ����������(CBulletBase)
//=============================================================================
HRESULT C3DBullet::Init(void)
{

	SetObjType(OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
// �I������(CBulletBase)
//=============================================================================
void C3DBullet::Uninit(void)
{


	Release();
}

//=============================================================================
// �X�V����(CBulletBase)
//=============================================================================
void C3DBullet::Update(void)
{
	//�}�g���b�N�X���g�p���Ĉړ��ʂ����߂�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, m_fMove);

	D3DXMATRIX Mtxmove, Mtxrot, Mtxtrans;
	D3DXMatrixIdentity(&Mtxmove);

	D3DXMatrixTranslation(&Mtxtrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxtrans);
	D3DXMatrixRotationYawPitchRoll(&Mtxrot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxrot);

	move = D3DXVECTOR3(Mtxmove._41, Mtxmove._42, Mtxmove._43);	//���W(�ړ���)�����o��


																//���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshField *pMesh = CGame::GetMeshField();

	float fHeight = pMesh->GetHeight(m_pos + move);
	if (m_pos.y < fHeight)
	{
		move.y = 0.0f;
	}

	m_pos += move;


	//���Ƃ̔���

}

//=============================================================================
// �`�揈��(CBulletBase)
//=============================================================================
void C3DBullet::Draw(void)
{

}

//=============================================================================
//
// ���f���e���� (CModelBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CModelBullet)
//=============================================================================
CModelBullet::CModelBullet(int nPriority) : C3DBullet(nPriority)
{

}
CModelBullet::~CModelBullet()
{

}
//=============================================================================
// �ݒ菈��(CModelBullet)
//=============================================================================
CModelBullet* CModelBullet::Create(void)
{
	CModelBullet* pBullet = NULL;
	pBullet = new CModelBullet(BULLET_PRIORITY);
	if (pBullet != NULL)
	{
		pBullet->Init();
	}
	return pBullet;
}
//=============================================================================
// �ݒ菈��(CModelBullet)
//=============================================================================
void CModelBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, BULLET_PROPERTY type,int nID)
{
	m_pModel = CSceneX::Create(pos,rot,D3DXVECTOR3(1.0f,1.0f,1.0f),model,0);
	m_Prop = type;

	float fSpeed;
	switch (m_Prop)
	{
	case TYPE_HIGHSPEED:
		fSpeed = 8.0f;
		m_fKnockBack = 6.0f;
		break;
	case TYPE_STINGER:
		fSpeed = 6.0f;
		m_fKnockBack = 9.0f;
		break;
	case TYPE_KNOCKBACK:
		fSpeed = 3.0f;
		m_fKnockBack = 20.0f;
		break;
	case TYPE_REFLECT:
		m_fKnockBack = 8.0f;
		break;
	default:
		fSpeed = 5.0f;
		m_fKnockBack = 6.0f;
		break;
	}

	C3DBullet::Set(pos,
		rot,
		fSpeed,
		100,
		nID);
}

//=============================================================================
// ����������(CModelBullet)
//=============================================================================
HRESULT CModelBullet::Init(void)
{
	C3DBullet::Init();

	m_Type = TYPE_MODEL;
	return S_OK;
}

//=============================================================================
// �I������(CModelBullet)
//=============================================================================
void CModelBullet::Uninit(void)
{
	if (m_pModel != NULL)
	{
		m_pModel->Uninit();
		m_pModel = NULL;
	}

	C3DBullet::Uninit();
}

//=============================================================================
// �X�V����(CModelBullet)
//=============================================================================
void CModelBullet::Update(void)
{
	C3DBullet::Update();
	m_pModel->SetPosition(GetPosition());
	m_pModel->SetRot(GetRotation());
	int& nLife = GetLife();
	nLife--;

	if (m_Prop != TYPE_STINGER)
	{//�ђʃ^�C�v�łȂ���Γ����蔻����`�F�b�N����

	 //���˃^�C�v�Ȃ瓖��������Ɋp�x��Y���Ŕ��]������
	}


	if (nLife < 0)
	{
		Uninit();
	}

}

//=============================================================================
// �`�揈��(CModelBullet)
//=============================================================================
void CModelBullet::Draw(void)
{

}

//=============================================================================
//
// �����e���� (CWordBullet)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CWordBullet)
//=============================================================================
CWordBullet::CWordBullet(int nPriority) : C3DBullet(nPriority)
{
	m_pWord = NULL;
}
CWordBullet::~CWordBullet()
{

}

//=============================================================================
// �ݒ菈��(CModelBullet)
//=============================================================================
CWordBullet* CWordBullet::Create(void)
{
	CWordBullet* pBullet = NULL;
	pBullet = new CWordBullet(BULLET_PRIORITY);
	if (pBullet != NULL)
	{
		pBullet->Init();
	}
	return pBullet;
}

//=============================================================================
// �ݒ菈��(CWordBullet)
//=============================================================================
void CWordBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nWordNum, int nID)
{
	C3DBullet::Set(pos, rot,fSpeed,nLife,nID);
	m_pWord = CSceneBillBoard::Create(pos,20.0f,20.0f,"WORD");
	if (m_pWord != NULL) { m_pWord->SetTexture(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)),
											   D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f))); };
}

//=============================================================================
// ����������(CWordBullet)
//=============================================================================
HRESULT CWordBullet::Init(void)
{
	C3DBullet::Init();
	m_Type = TYPE_WORD;

	return S_OK;
}

//=============================================================================
// �I������(CWordBullet)
//=============================================================================
void CWordBullet::Uninit(void)
{
	if (m_pWord != NULL)
	{
		m_pWord->Uninit();
		m_pWord = NULL;
	}

	C3DBullet::Uninit();

}

//=============================================================================
// �X�V����(CWordBullet)
//=============================================================================
void CWordBullet::Update(void)
{
	C3DBullet::Update();

	m_pWord->Setpos(GetPosition());
	int& nLife = GetLife();
	nLife--;
	if (nLife < 0)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��(CWordBullet)
//=============================================================================
void CWordBullet::Draw(void)
{

}
