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
#include "player.h"
#include "game.h"
#include "time.h"
#include "scene3D.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define BELTCONVEYER_MOVE			(0.2f)			// �x���g�R���x�A�̑��x
#define KNOCKBACK_MOVE_SMALL		(4.0f)			// �m�b�N�o�b�N�̋��x(��)
#define KNOCKBACK_MOVE_DURING		(6.0f)			// �m�b�N�o�b�N�̋��x(��)
#define KNOCKBACK_MOVE_BIG			(9.0f)			// �m�b�N�o�b�N�̋��x(��)
#define GEAR_ROT_Y					(0.1f)			// �M�A�̉�]�ʁ@�x�[�X���
#define MODEL_MOVE_Y				(2.0f)			// ���f���ړ����̈ړ����x
#define AFFECTED_LANDING			(15.0f)			// ���f�����n���̃m�b�N�o�b�N�e����

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject::CObject()
{
	m_bMoveFlag = false;		// �ړ��t���O
	m_pIcon = NULL;				// �x���g�R���x�A�̃A�C�R��
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
	CObject *pObject = NULL;

	if (pObject == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pObject = new CObject;

		if (pObject != NULL)
		{
			pObject->SetModelType(model);
			pObject->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));		// ���f���̊��蓖��
			pObject->SetScale(Scale);	// �X�P�[���̐ݒ�
			pObject->Init(pos);			// ������
			pObject->SetRot(rot);		// �����̐ݒ�
			pObject->SetCollsionType(type);	// �R���W�����̃^�C�v�ݒ�
			pObject->m_nRealTime = REALTIME_INITPOS;
		}
	}

	return pObject;
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
	if (m_pIcon != NULL)
	{	// �A�C�R���̔j��
		m_pIcon->Uninit();
		m_pIcon = NULL;
	}
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	D3DXVECTOR3 pos = CSceneX::GetPosition();	// �ʒu�擾

	ModelMove(Collsiontype, pos);	// ���f���̈ړ�

#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{	// �ړ�Flag�ω��p
		m_nRealTime = REALTIME_ENDPOS;
	}
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	if (m_pIcon != NULL)
	{
		m_pIcon->Draw();
	}
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
void CObject::KnockBack(D3DXVECTOR3 *pMove, int nID)
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

	// �v���C���[�̌����������]������悤�ɂȂ�����폜
	if (CSceneX::GetCollsionNum() == 0 || CSceneX::GetCollsionNum() == 1)
	{	// �� ���� �E ����̔���
		pMove->x *= -fknockBackMove;
	}
	else if (CSceneX::GetCollsionNum() == 2 || CSceneX::GetCollsionNum() == 3)
	{	// �O ���� ��� ����̔���
		pMove->z *= -fknockBackMove;
	}

	// �v���C���[�̌����������]������悤�ɂȂ�����R�����g���O��
	/*float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
	pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);
	pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);*/
}

//=============================================================================
// ���f�����n���̎󂯂�e���̏���
//=============================================================================
void CObject::AffectedLanding(D3DXVECTOR3 *pMove, int nID)
{
	float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
	pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (AFFECTED_LANDING);
	pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (AFFECTED_LANDING);
}

//=============================================================================
// ���f���̈ړ��֌W�̏���
//=============================================================================
void CObject::ModelMove(CSceneX::COLLISIONTYPE Type, D3DXVECTOR3 pos)
{
	if (m_nRealTime == REALTIME_INITPOS)
	{	// �ړ��t���O��false �����Ȃ��ꍇ
		pos.y -= MODEL_MOVE_Y;						// �ړ����x

		if (pos.y - CSceneX::GetVtxMin().y < 0)
		{	// �n�ʂɒ������ꍇ
			if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || Type == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
				Type == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT || Type == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// �x���g�R���x�A�̏ꍇ
				pos.y = pos.y - CSceneX::GetVtxMin().y - 1.9f;
				CSceneX::SetPosition(pos);
				m_nRealTime = REALTIME_NONE;

				if (m_pIcon == NULL)
				{
					
					
					if (Type == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT /*|| Type == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT*/)
					{
						if (pos.z < 0)
						{
							m_pIcon = CScene3D::Create(D3DXVECTOR3(pos.x, 10.0f, pos.z), "�x���g�R���x�A_�A�C�R��");
							m_pIcon->SetSize(50.0f, 40.0f);
							m_pIcon->SetAnimation(0, 0.1f, 1.0f);
							m_pIcon->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));
						}
					}
				}
			}
			else if (Type != CSceneX::COLLSIONTYPE_CONVEYOR_FRONT && Type != CSceneX::COLLSIONTYPE_CONVEYOR_BACK &&
				Type != CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT && Type != CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// �x���g�R���x�A�ȊO�̏ꍇ
				pos.y = pos.y - CSceneX::GetVtxMin().y;
				CSceneX::SetPosition(pos);
				m_nRealTime = REALTIME_NONE;
			}
		}
		CSceneX::SetPosition(pos);
	}
	else if (m_nRealTime == REALTIME_NONE)
	{	// �����Ȃ��ꍇ
		if (Type == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || Type == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING || Type == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
		{	// �R���W�����^�C�v���m�b�N�o�b��������Ȃ�����̉�]��������
			D3DXVECTOR3 rot = CSceneX::GetRot();

			// ����̎�ނɂ���ĉ�]�ʂ�ω�
			rot.y += GEAR_ROT_Y * ((int)Type - (int)COLLSIONTYPE_CONVEYOR_LEFT);

			CSceneX::SetRot(rot);
		}

		if ((CTime::GetStageTime() % 30) == 0) { m_nRealTime = REALTIME_ENDPOS; }
	}
	else if (m_nRealTime == REALTIME_ENDPOS)
	{	// �ړ��t���O��true �����ꍇ

		pos.y -= MODEL_MOVE_Y;						// �ړ����x

		CSceneX::SetPosition(pos);

		if (pos.y + CSceneX::GetVtxMax().y < 0)
		{	// �n�ʂ�艺�̏ꍇ
			Uninit();
			return;
		}
	}

}