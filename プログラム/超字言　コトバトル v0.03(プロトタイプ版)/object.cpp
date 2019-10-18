//=============================================================================
//
// �I�u�W�F�N�g�̏��� [oblect.cpp]
// Author : �ڍ� ������
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "load.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BELTCONVEYER_MOVE			(0.7f)			// �x���g�R���x�A�̑��x
#define KNOCKBACK_MOVE_SMALL		(4.0f)			// �m�b�N�o�b�N�̋��x(��)
#define KNOCKBACK_MOVE_DURING		(6.0f)			// �m�b�N�o�b�N�̋��x(��)
#define KNOCKBACK_MOVE_BIG			(9.0f)			// �m�b�N�o�b�N�̋��x(��)
#define GEAR_ROT_Y					(0.2f)			// �M�A�̉�]�ʁ@�x�[�X���

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, CSceneX::COLLISIONTYPE type, CLoad::MODEL model)
{
	CObject *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pSceneX = new CObject;

		if (pSceneX != NULL)
		{
			pSceneX->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));		// ���f���̊��蓖��
			pSceneX->SetScale(Scale);	// �X�P�[���̐ݒ�
			pSceneX->Init(pos);			// ������
			pSceneX->SetRot(rot);		// �����̐ݒ�
			pSceneX->SetCollsionType(type);	// �R���W�����̃^�C�v�ݒ�
		}
	}

	return pSceneX;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SCENEX);

	CSceneX::Init(pos);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();

	if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING || Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
	{	// �R���W�����^�C�v���m�b�N�o�b��������Ȃ�����̉�]��������
		D3DXVECTOR3 rot = CSceneX::GetRot();

		// ����̎�ނɂ���ĉ�]�ʂ�ω�
		rot.y += GEAR_ROT_Y * ((int)Collsiontype - (int)COLLSIONTYPE_CONVEYOR_LEFT);

		CSceneX::SetRot(rot);
	}
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// �x���g�R���x�A�̏���
//=============================================================================
void CObject::BeltConveyor(D3DXVECTOR3 *pMove)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT)
	{	// �O�i����
		pMove->z += BELTCONVEYER_MOVE;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_BACK)
	{	// ��ނ���
		pMove->z += -BELTCONVEYER_MOVE;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
	{	// �E�ړ�
		pMove->x += -BELTCONVEYER_MOVE;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
	{	// ���ړ�
		pMove->x += BELTCONVEYER_MOVE;
	}
}

//=============================================================================
// �m�b�N�o�b�N�̏���
//=============================================================================
void CObject::KnockBack(D3DXVECTOR3 *pMove)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	float fknockBackMove = 0.0f;	// �m�b�N�o�b�N�̋��x

	if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL)
	{	// �m�b�N�o�b�N�̈З͂�������
		fknockBackMove = KNOCKBACK_MOVE_SMALL;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING)
	{	// �m�b�N�o�b�N�̈З͂������炢
		fknockBackMove = KNOCKBACK_MOVE_DURING;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
	{	// �m�b�N�o�b�N�̈З͂��傫��
		fknockBackMove = KNOCKBACK_MOVE_BIG;
	}

	if (CSceneX::GetCollsionNum() == 0 || CSceneX::GetCollsionNum() == 1)
	{	// �� ���� �E ����̔���
		pMove->x *= -fknockBackMove;
	}
	else if (CSceneX::GetCollsionNum() == 2 || CSceneX::GetCollsionNum() == 3)
	{	// �O ���� ��� ����̔���
		pMove->z *= -fknockBackMove;
	}
}
