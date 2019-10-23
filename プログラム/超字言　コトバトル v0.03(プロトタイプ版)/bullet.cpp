//=============================================================================
//
// �e��{���� (CBulletBase)[bullet.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "bullet.h"
#include "manager.h"

#include "load.h"
#include "sceneBillboard.h"
#include "sceneX.h"
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CBulletBase)
//=============================================================================
CBulletBase::CBulletBase(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
}
CBulletBase::~CBulletBase()
{

}

//=============================================================================
// �ݒ菈��(CBulletBase)
//=============================================================================
void CBulletBase::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fSpeed, int nLife, int nID)
{
	m_pos = pos;
	m_rot = rot;
	m_fMove = fSpeed;
	m_nLife = nLife;

	m_nID = (nID % 4);//�͈͊O�̐������������炻���0�`3�܂ł̐����ɂ���
}

//=============================================================================
// ����������(CBulletBase)
//=============================================================================
HRESULT CBulletBase::Init(void)
{

	SetObjType(OBJTYPE_BULLET);
	return S_OK;
}

//=============================================================================
// �I������(CBulletBase)
//=============================================================================
void CBulletBase::Uninit(void)
{


	Release();
}

//=============================================================================
// �X�V����(CBulletBase)
//=============================================================================
void CBulletBase::Update(void)
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

	m_pos += move;

	//���Ƃ̔���

}

//=============================================================================
// �`�揈��(CBulletBase)
//=============================================================================
void CBulletBase::Draw(void)
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
CModelBullet::CModelBullet(int nPriority) : CBulletBase(nPriority)
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
void CModelBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, float fSpeed, int nLife, int nID)
{
	m_pModel = CSceneX::Create(pos,rot,D3DXVECTOR3(1.0f,1.0f,1.0f),model,0);


	CBulletBase::Set(pos,rot,fSpeed,nLife, nID);
}

//=============================================================================
// ����������(CModelBullet)
//=============================================================================
HRESULT CModelBullet::Init(void)
{
	CBulletBase::Init();

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

	CBulletBase::Uninit();
}

//=============================================================================
// �X�V����(CModelBullet)
//=============================================================================
void CModelBullet::Update(void)
{
	CBulletBase::Update();
	m_pModel->SetPosition(GetPosition());
	m_pModel->SetRot(GetRotation());
	int& nLife = GetLife();
	nLife--;
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
CWordBullet::CWordBullet(int nPriority) : CBulletBase(nPriority)
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
	CBulletBase::Set(pos, rot,fSpeed,nLife,nID);
	m_pWord = CSceneBillBoard::Create(pos,20.0f,20.0f,"WORD");
	if (m_pWord != NULL) { m_pWord->SetTexture(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)),
											   D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f))); };
}

//=============================================================================
// ����������(CWordBullet)
//=============================================================================
HRESULT CWordBullet::Init(void)
{
	CBulletBase::Init();
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

	CBulletBase::Uninit();

}

//=============================================================================
// �X�V����(CWordBullet)
//=============================================================================
void CWordBullet::Update(void)
{
	CBulletBase::Update();

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
