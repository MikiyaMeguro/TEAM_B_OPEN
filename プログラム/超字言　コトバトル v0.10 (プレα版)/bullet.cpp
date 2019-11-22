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

#include "debugProc.h"
#include "explosion.h"
//=============================================================================
// �R���X�g���N�^���f�X�g���N�^	(CBulletBase)
//=============================================================================
C3DBullet::C3DBullet(int nPriority) : CScene(nPriority)
{
	m_Type = TYPE_NONE;
	m_fKnockBack = 0.0f;
	m_MoveResult = D3DXVECTOR3(0.0f,0.0f,0.0f);
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

	m_fCollisionRadius = 10.0f;
	m_fKnockBack = 7.0f;

	D3DXMatrixRotationYawPitchRoll(&m_mtxRotate, m_rot.y, m_rot.x, m_rot.z);

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
	m_posOld = m_pos;

	//�}�g���b�N�X���g�p���Ĉړ��ʂ����߂�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, m_fMove);

	D3DXMATRIX Mtxmove, Mtxtrans;
	D3DXMatrixIdentity(&Mtxmove);

	D3DXMatrixTranslation(&Mtxtrans, move.x, move.y, move.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &Mtxtrans);
	//D3DXMatrixRotationYawPitchRoll(&Mtxrot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&Mtxmove, &Mtxmove, &m_mtxRotate);

	move = D3DXVECTOR3(Mtxmove._41, Mtxmove._42, Mtxmove._43);	//���W(�ړ���)�����o��


	//���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshField *pMesh = CGame::GetMeshField();

	float fHeight = pMesh->GetHeight(m_pos + move);
	if (m_pos.y < fHeight)
	{
		move.y = 0.0f;
	}
	m_MoveResult = move;		//���߂��������i�[
	m_pos += move;

	CDebugProc::Print("cf","BULLET_ROT_Y",m_rot.y);
}

//=============================================================================
// �`�揈��(CBulletBase)
//=============================================================================
void C3DBullet::Draw(void)
{

}

//=============================================================================
// �I�u�W�F�N�g�Ƃ̓����蔻�菈��(CBulletBase)
//=============================================================================
bool C3DBullet::CollisionObject(CManager::DIRECTION* dir)
{//��������
	CScene* pScene = NULL;
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
				if (pSceneX->GetCollsionType() == CSceneX::COLLISIONTYPE_BOX)
				{
					D3DXVECTOR3 vtxMin = pSceneX->GetVtxMin();
					D3DXVECTOR3 vtxMax = pSceneX->GetVtxMax();
					D3DXVECTOR3 OBJpos = pSceneX->GetPosition();

					if (m_pos.y <= OBJpos.y + vtxMax.y &&m_pos.y + m_fCollisionRadius >= OBJpos.y + vtxMax.y ||
						m_pos.y + m_fCollisionRadius >= OBJpos.y + vtxMin.y &&m_pos.y <= OBJpos.y + vtxMin.y ||
						m_pos.y + m_fCollisionRadius <= OBJpos.y + vtxMax.y  && m_pos.y >= OBJpos.y + vtxMin.y)
					{//�����͈͓��Ȃ�
						if (m_pos.z - m_fCollisionRadius <= OBJpos.z + vtxMax.z &&
							m_pos.z + m_fCollisionRadius >= OBJpos.z + vtxMin.z)
						{// z�͈̔͂̒�
							if (m_posOld.x + m_fCollisionRadius <= OBJpos.x + vtxMin.x
								&& m_pos.x + m_fCollisionRadius > OBJpos.x + vtxMin.x)
							{// X���W�̒��ɍ����������
								*dir = CManager::DIR_LEFT_WEST;
								return true;
							}
							else if (m_posOld.x - m_fCollisionRadius >= OBJpos.x + vtxMax.x
								   && m_pos.x - m_fCollisionRadius < OBJpos.x + vtxMax.x)
							{// X���W�̒��ɉE���������
								*dir = CManager::DIR_RIGHT_EAST;
								return true;
							}
						}

						if (m_pos.x - m_fCollisionRadius <= OBJpos.x + vtxMax.x &&
							m_pos.x + m_fCollisionRadius >= OBJpos.x + vtxMin.x)
						{// x�͈̔͂̒�
							if (m_posOld.z + m_fCollisionRadius <= OBJpos.z + vtxMin.z
								&& m_pos.z + m_fCollisionRadius > OBJpos.z + vtxMin.z)
							{// Z���W�̒��Ɏ�O���������
								*dir = CManager::DIR_DOWN_SOUTH;
								return true;
							}
							else if (m_posOld.z - m_fCollisionRadius >= OBJpos.z + vtxMax.z
								&& m_pos.z - m_fCollisionRadius < OBJpos.z + vtxMax.z)
							{// Z���W�̒��Ɍ�납�������
								*dir = CManager::DIR_UP_NORTH;
								return true;
							}
						}

					}
				}
			}
		}

		pScene = pSceneNext;	//�L�^��������T�����邽�߂Ƀ|�C���^���킽��
	}

	return false;
}
bool C3DBullet::SimpleCollision(void)
{//�����Ȃ�(������Ԃ����ɗL�̂ق����g��)
	CManager::DIRECTION dir;
	return CollisionObject(&dir);
}

//=============================================================================
// �ǔ�����(CBulletBase)
//=============================================================================
void C3DBullet::Homing(D3DXVECTOR3 HomingPos)
{
	D3DXQUATERNION Quat,HomingQuat,dest;
	//���݂̊p�x�}�g���b�N�X����N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationMatrix(&Quat,&m_mtxRotate);

	//�e�̈ʒu�x�N�g���ƃz�[�~���O���������̈ʒu�x�N�g������N�H�[�^�j�I�����쐬
	float fRotY = atan2f((HomingPos.x - m_pos.x), (HomingPos.z - m_pos.z));
	//float fRotX = atan2f((HomingPos.y - m_pos.y), (HomingPos.z - m_pos.z)) + D3DX_PI;
	//CUtilityMath::RotateNormarizePI(&fRotX);
	CUtilityMath::RotateNormarizePI(&fRotY);
	D3DXQuaternionRotationYawPitchRoll(&HomingQuat,fRotY,0.0f,0.0f);
	//D3DXQuaternionInverse(&HomingQuat, &HomingQuat);
	//��̃N�H�[�^�j�I�������ʕ�Ԃ���
	D3DXQuaternionSlerp(&dest,&Quat,&HomingQuat,0.1f);	//�������Ƃ�

	//���߂��N�H�[�^�j�I�����p�x�}�g���b�N�X�ɕϊ�
	D3DXMatrixRotationQuaternion(&m_mtxRotate,&dest);
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
	m_pModel = NULL;
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
void CModelBullet::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CLoad::MODEL model, BULLET_PROPERTY type,int nID, D3DXVECTOR3 RotateOffset)
{
	m_pModel = CSceneX::Create(pos,rot,D3DXVECTOR3(1.0f,1.0f,1.0f),model,0);
	m_Prop = type;
	//float fSpeed = 1.0f;

	float fSpeed = 3.0f;
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
	m_modelRotateOffSet = RotateOffset;
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
	m_pHomingChara = NULL;
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
	int& nLife = GetLife();
	nLife--;

	C3DBullet::Update();
	if (m_Prop == TYPE_MISSILE)
	{//�~�T�C���Ȃ�
		if (m_pHomingChara != NULL)
		{
			Homing(m_pHomingChara->GetPosition());
		}
	}

	if (m_pModel != NULL)
	{
		m_pModel->SetPosition(GetPosition());

		D3DXVECTOR3 Rotate = m_modelRotateOffSet + GetRotation();
		CUtilityMath::RotateNormarizePI(&Rotate);
		m_pModel->SetRot(Rotate);
	}
	if (m_Prop != TYPE_STINGER)
	{//�ђʃ^�C�v�łȂ���΃I�u�W�F�N�g�Ƃ̓����蔻����`�F�b�N����
		CManager::DIRECTION dir;
		if (CollisionObject(&dir))
		{//�������Ă����
			//���˃^�C�v�Ȃ瓖��������Ɋp�x��Y���ŉ�]������
			if (m_Prop == TYPE_REFLECT)
			{
				Reflect(dir);
			}
			else
			{
				Uninit();
				return;
			}
		}
	}


	if (nLife < 0)
	{
		Uninit();
		return;
	}

}

//=============================================================================
// �`�揈��(CModelBullet)
//=============================================================================
void CModelBullet::Draw(void)
{

}

//=============================================================================
// ���f���̑傫���ݒ菈��(CModelBullet)
//=============================================================================
void  CModelBullet::SetModelScale(const D3DXVECTOR3& scale)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetScale(scale);
	}
}

//=============================================================================
// ���f���̌����ݒ菈��(CModelBullet)
//=============================================================================
void  CModelBullet::SetModelRot(const D3DXVECTOR3& rot)
{
	if (m_pModel != NULL)
	{
		m_pModel->SetRot(rot);
	}
}

//=============================================================================
// ���ˏ���(CModelBullet)
//=============================================================================
void CModelBullet::Reflect(CManager::DIRECTION dir)
{
	D3DXVECTOR3& rot = GetRotation();

	switch (dir)
	{
	case CManager::DIR_RIGHT_EAST:	//��(+X����)
		rot.y *= -1.0f;
		break;
	case CManager::DIR_LEFT_WEST:	//��(-X����)
		rot.y *= -1.0f;
		break;
	case CManager::DIR_DOWN_SOUTH:  //��(-Z����)
		rot.y += D3DX_PI;
		rot.y *= -1.0f;
		break;
	case CManager::DIR_UP_NORTH:	//�k(+Z����)
		rot.y += D3DX_PI;
		rot.y *= -1.0f;
		break;
	default:
		return;	//�����ꂻ��ȊO�̒l�������Ă����Ƃ��͏������甲����
		break;
	}
	CUtilityMath::RotateNormarizePI(&rot.y);

	SetModelRot(rot);

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

	CExplosion3D* p3D = CExplosion3D::Create();
	if (p3D != NULL) { p3D->Set(GetPosition(), 0.01f, 100.0f, 60,0.01f); }

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
	int& nLife = GetLife();
	nLife--;
	C3DBullet::Update();
	if (m_pWord != NULL)
	{
		m_pWord->Setpos(GetPosition());
	}

	if (SimpleCollision())
	{//�������Ă����
		Uninit();
		return;
	}
	if (nLife < 0)
	{
		Uninit();
		return;
	}
}

//=============================================================================
// �`�揈��(CWordBullet)
//=============================================================================
void CWordBullet::Draw(void)
{

}
