//=============================================================================
//
// �L�����N�^�[��{���� (CCharaBase)[charactor.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "charactor.h"
#include "manager.h"

#include "CameraManager.h"
#include "player.h"
#include "game.h"
#include "debugProc.h"
#include "meshField.h"
#include "word_manager.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.6f)			//�f�t�H���g�̈ړ��X�s�[�h
#define STEP_DEFAULT_MOVEMENT (6.0f)		//�f�t�H���g�̃X�e�b�v��
#define MOVE_DEFAULT_COEFFICIENT (0.20f)	//�f�t�H���g�̈ړ��ɂ�����W��
#define MOVE_AIR_COEFFICIENT (0.10f);
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//�f�t�H���g�̉�]�ɂ�����W��
#define CIRCLE_HOMING	 (3000)				//�ǔ��͈�(���)
#define CIRCLE_ANGLE	(100)
#define PATROL_FLAME	(60)
#define CAMERA_MOVE_SPEED (0.05f)
//=============================================================================
// �ݒ菈��
//=============================================================================
void  CCharaBase::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis)
{
	m_pos = pos;
	m_RespawnPos = pos;
	m_rot = rot;
	m_type = type;
	m_pThisCharactor = pThis;

	m_Move = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Spin = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_fSpeed = MOVE_DEFAULT_SPEED;
	m_fStep = STEP_DEFAULT_MOVEMENT;
	m_fMoveCoeffient = MOVE_DEFAULT_COEFFICIENT;
	m_fSpinCoeffient = SPIN_DEFAULT_COEFFICIENT;

	m_nCntStepCoolTime = 0;
	CCommand::RegistCommand("PLAYERMOVE_UP",CCommand::INPUTTYPE_KEYBOARD,CCommand::INPUTSTATE_PRESS,DIK_W);
	CCommand::RegistCommand("PLAYERMOVE_UP", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_UP);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_DOWN);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT);


	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_SPACE);
	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("CAMERAMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("CAMERAMOVE_LEFT", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_LEFT);
	CCommand::RegistCommand("CAMERAMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);
	CCommand::RegistCommand("CAMERAMOVE_RIGHT", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_RIGHT);
	CCommand::RegistCommand("CAMERAMOVE_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_UP);
	CCommand::RegistCommand("CAMERAMOVE_UP", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_UP);
	CCommand::RegistCommand("CAMERAMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("CAMERAMOVE_DOWN", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_DOWN);
}

//=============================================================================
//
// 3D�L�����N�^�[���� (C3DCharactor)[charactor.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// ����������
//=============================================================================
HRESULT C3DCharactor::Init(void)
{
	m_nActionTimer = 0;
	m_PatrolTimer = 0;

	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void C3DCharactor::Update(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();

	switch (CCharaBase::GetMoveType())
	{
	case CCharaBase::MOVETYPE_PLAYER_INPUT:
		CharaMove_Input();
		break;
	case CCharaBase::MOVETYPE_NPC_AI:
		if (m_nActionTimer == 0)
		{	//�l����
			Think_CPU();
		}
		else
		{	//�s������
			Action_CPU();
		}
		break;
	}
	//���b�V���t�B�[���h�Ƃ̓����蔻��
	CMeshField *pMesh = CGame::GetMeshField();

	float fHeight = pMesh->GetHeight(pos);
	if (pos.y < fHeight)
	{
		pos.y = fHeight;
	}
	//�d��
	move.y = -3.0f;
	//�������x
	if (pos.y <= -100.0f)
	{
		pos = m_RespawnPos;
		move.y = 0.0f;
	}
}

//=============================================================================
// �ړ�����
//=============================================================================
void C3DCharactor::CharaMove_Input(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	CCamera* pCamera = pCameraManager->GetCamera(GetThisCharactor()->GetCameraName());
	int nID = GetThisCharactor()->GetID();
	D3DXVECTOR3 CameraRot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	if (pCamera != NULL)
	{
		CameraRot = pCamera->GetRotation();
	}

	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();


	float fMoveCoefficientX = 1.0f;	//�ړ��W��(X)
	float fMoveCoefficientZ = 1.0f;	//�ړ��W��(Z)
	float fMoveCofBlend = 1.0f;	//�ړ��W���̓���|�����킹������
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fMoveCoefficientX = fabsf(CCommand::GetXPadStickRotation(true, false, nID));
			fMoveCoefficientZ = fabsf(CCommand::GetXPadStickRotation(true, true, nID));
			fMoveCofBlend = (fMoveCoefficientX > fMoveCoefficientZ) ? fMoveCoefficientX : fMoveCoefficientZ;
		}
	}

	//�ړ��̌����ݒ�
	if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * (speed * fMoveCofBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) *  (speed * fMoveCofBlend);
		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) *  (speed * fMoveCofBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) *  (speed * fMoveCofBlend);

		}
		else
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * (speed * fMoveCoefficientX);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * (speed * fMoveCoefficientX);

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.25f)) *  (speed * fMoveCofBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.25f)) *  (speed * fMoveCofBlend);


		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.75f)) *  (speed * fMoveCofBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.75f)) *  (speed * fMoveCofBlend);

		}
		else
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.5f)) * (speed * fMoveCoefficientX);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.5f)) * (speed * fMoveCoefficientX);

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
	{
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.0f)) * (speed * fMoveCoefficientZ);
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.0f)) * (speed * fMoveCoefficientZ);

	}
	else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
	{
		move.x += sinf(CameraRot.y + (D3DX_PI * 1.0f)) * (speed * fMoveCoefficientZ);
		move.z += cosf(CameraRot.y + (D3DX_PI * 1.0f)) * (speed * fMoveCoefficientZ);

	}

	//if (CCommand::GetCommand("TESTUP"))
	//{
	//	move.y += 10;
	//}
	//if (CCommand::GetCommand("TESTDOWN"))
	//{
	//	move.y -= 10;
	//}

	//�X�e�b�v�ړ��̐ݒ�
	if (CCommand::GetCommand("PLAYERMOVE_STEP", nID))
	{
		if (m_nCntStepCoolTime <= 0)
		{
			float fStepRot = 0.0f;
			if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * 0.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * 1.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID)) {
				fStepRot = D3DX_PI * -0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * -0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * -0.75f; }
			}
			if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID)) {
				fStepRot = D3DX_PI * 0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * 0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * 0.75f; }
			}
			move.x += sinf(CameraRot.y + fStepRot) * 6.0f;
			move.z += cosf(CameraRot.y + fStepRot) * 6.0f;

			m_nCntStepCoolTime = 30;
		}
	}
	if (m_nCntStepCoolTime > 0)
	{
		m_nCntStepCoolTime--;
	}
	CDebugProc::Print("cn" ,"STEP_COOLTIME : ",m_nCntStepCoolTime);

	//move *= MOVE_DEFAULT_COEFFICIENT;

	pos += move;
	move.x += (0.0f - move.x) * MOVE_DEFAULT_COEFFICIENT;
	move.y += (0.0f - move.y) * MOVE_DEFAULT_COEFFICIENT;
	move.z += (0.0f - move.z) * MOVE_DEFAULT_COEFFICIENT;

	spin.y = CameraRot.y - rot.y;

	//��]����
	if (spin.y > D3DX_PI)
	{
		spin.y -= D3DX_PI * 2.0f;
	}
	else if (spin.y < -D3DX_PI)
	{
		spin.y += D3DX_PI * 2.0f;
	}

	rot.y += spin.y * SPIN_DEFAULT_COEFFICIENT;

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}
	spin.y = 0.0f;

	//�J�����ʒu����
	float fCameraCoefficient = 1.0f;
	//���_�ړ�
	//Y
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fCameraCoefficient = fabsf(CCommand::GetXPadStickRotation(false,false,nID));
		}
	}
	//fCoefficient = CCommand::GetXPadStickRotation(false,false,nID);
	if (CCommand::GetCommand("CAMERAMOVE_LEFT", nID))//���v���
	{
		CameraRot.y -= CAMERA_MOVE_SPEED * fCameraCoefficient;
	}
	if (CCommand::GetCommand("CAMERAMOVE_RIGHT", nID))//�����v���
	{
		CameraRot.y += CAMERA_MOVE_SPEED * fCameraCoefficient;
	}

	//X
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fCameraCoefficient = fabsf(CCommand::GetXPadStickRotation(false, true, nID));
		}
	}

	//fCoefficient = CCommand::GetXPadStickRotation(false, true, nID);
	if (CCommand::GetCommand("CAMERAMOVE_UP", nID))
	{
		if (CameraRot.x < D3DX_PI * 0.2f)
		{
			CameraRot.x += CAMERA_MOVE_SPEED * fCameraCoefficient;
		}
		else
		{
			CameraRot.x = D3DX_PI * 0.2f;
		}
	}
	if (CCommand::GetCommand("CAMERAMOVE_DOWN", nID))
	{
		if (CameraRot.x > D3DX_PI * -0.2f)
		{
			CameraRot.x -= CAMERA_MOVE_SPEED * fCameraCoefficient;
		}
		else
		{
			CameraRot.x = -D3DX_PI * 0.2f;
		}
	}

	//�J�����ݒ�
	pCameraManager->CreateCamera(GetThisCharactor()->GetCameraName(),
		pCamera->GetType(),
		pCamera->GetPosR(),
		CameraRot,pCamera->GetLength());

	//�J�����̎Q�ƈʒu����
	m_CameraPosR = pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
}
//=============================================================================
// CPU�̎v�l����
//=============================================================================
void C3DCharactor::Think_CPU(void)
{
	m_OldCpuThink = m_CpuThink;

	m_CpuThink = THINK_NONE;
	m_OldCpuThink = THINK_NONE;
	m_CpuMove = CPU_MOVE_NONE;
	m_CpuNode = CPU_NODE_NONE;

	//�v���g�^�C�v�p
	switch (GetThisCharactor()->GetID())
	{
	case 1:
		m_Type = CPU_TYPE_ESCAPE;
		break;
	case 2:
		m_Type = CPU_TYPE_HOMING;
		break;
	case 3:
		m_Type = CPU_TYPE_PATROL;
		break;
	default:
		break;
	}

	//�s�������߂������
	if (m_bFront == true)
	{
		m_CpuThink = THINK_ROTATION;
		m_nActionTimer = 1;
		m_CpuRotation = (CPU_ROTATION)(rand() % 3);
		m_bFront = false;
	}
	else
	{
		switch (m_Type)
		{
		case CPU_TYPE_ESCAPE:
			m_CpuThink = THINK_ESCAPE;
			m_nActionTimer = 30;
			break;
		case CPU_TYPE_HOMING:
			m_CpuThink = THINK_WATCH;
			m_nActionTimer = 30;
			break;
		case CPU_TYPE_PATROL:
			m_CpuThink = THINK_MOVE;
			m_CpuMove = CPU_MOVE_PATROL;
			m_nActionTimer = 240;
			break;
		default:
			break;
		}



#if 0
		m_CpuThink = THINK_MOVE;
		/*
		�G���O�ɂ��鎞��BACK
		�G���e�������Ă�Ƃ��͉�����Ȃ��獶�E�ړ�
		�G�������Ȃ��Ƃ��͂ł��邾���O�i
		�e�������Ă���Ƃ��͑O�i���Ă���
		*/
		m_CpuMove = CPU_MOVE_FRONT;
#endif
	}

	//�����s����3��Ƃ�Ȃ�
	if (m_OldCpuThink == m_CpuThink)
	{
		m_nCntSameCnt++;
		if (m_nCntSameCnt == 3)
		{
			m_nCntSameCnt = 0;
			m_nActionTimer = 0;
		}
	}
	else
	{
		m_nCntSameCnt = 0;
	}
}

//=============================================================================
// CPU�̍s������
//=============================================================================
void C3DCharactor::Action_CPU(void)
{
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	//�s�������s�Ɉڂ�
	switch (m_CpuThink)
	{
	case  THINK_MOVE:
		CharaMove_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	case  THINK_ROTATION:
		m_bFront = false;
		Rotation_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	case  THINK_PATROL:
		Rotation_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	case  THINK_HOMING:
		Homing_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	case  THINK_WATCH:
		Homing_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	case  THINK_ESCAPE:
		Homing_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	case  THINK_ATTACK:
		Attack_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	default:
		break;
	}

	if (m_CpuThink == THINK_ESCAPE)
	{
		pos.x -= move.x;
		pos.y += move.y;
		pos.z -= move.z;
	}
	else
	{
		pos += move;
	}
	move.x += (0.0f - move.x) * MOVE_DEFAULT_COEFFICIENT;
	move.y += (0.0f - move.y) * MOVE_DEFAULT_COEFFICIENT;
	move.z += (0.0f - move.z) * MOVE_DEFAULT_COEFFICIENT;



	//�^�C�}�[�����炷
	m_nActionTimer--;
}

//=============================================================================
// CPU�̏���
//=============================================================================
void C3DCharactor::CharaMove_CPU(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	CCamera* pCamera = pCameraManager->GetCamera(GetThisCharactor()->GetCameraName());
	D3DXVECTOR3 CameraRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (pCamera != NULL)
	{
		CameraRot = pCamera->GetRotation();
	}

	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();
	D3DXVECTOR3 ChangeRot(0.0f, 0.0f, 0.0f);


	//�ړ�����
	switch (m_CpuMove)
	{
	case CPU_MOVE_FRONT:
		move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		break;
	case CPU_MOVE_BACK:
		move.x += sinf(rot.y + (D3DX_PI * 1.0f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * 1.0f)) * speed;
		break;
	case CPU_MOVE_RIGHT:
		move.x += sinf(rot.y + (D3DX_PI * 0.5f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * 0.5f)) * speed;
		break;
	case CPU_MOVE_LEFT:
		move.x += sinf(rot.y + (D3DX_PI * -0.5f)) * speed;
		move.z += cosf(rot.y + (D3DX_PI * -0.5f)) * speed;
		break;
	case CPU_MOVE_PATROL:
		if (m_PatrolTimer <= PATROL_FLAME * 1 && m_PatrolTimer > 0)
		{
			ChangeRot.y = (D3DX_PI * 0.0f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer <= PATROL_FLAME * 2 && m_PatrolTimer > PATROL_FLAME * 1)
		{
			ChangeRot.y = (D3DX_PI * 0.5f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer <= PATROL_FLAME * 3 && m_PatrolTimer > PATROL_FLAME * 2)
		{
			ChangeRot.y = (D3DX_PI * 1.0f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer <= PATROL_FLAME * 4 && m_PatrolTimer > PATROL_FLAME * 3)
		{
			ChangeRot.y = (D3DX_PI * -0.5f);
			rot.y = ChangeRot.y;
			move.x += sinf(rot.y + (D3DX_PI * 0.0f)) * speed;
			move.z += cosf(rot.y + (D3DX_PI * 0.0f)) * speed;
		}
		else if (m_PatrolTimer > PATROL_FLAME * 4)
		{
			m_PatrolTimer = 0;
		}
		m_PatrolTimer++;
		break;
	}


	if (CPU_MOVE_PATROL == m_CpuMove)
	{
		rot.y = ChangeRot.y;
	}
	else
	{
		spin.y = rot.y - rot.y;
	}


	//��]����
	if (spin.y > D3DX_PI)
	{
		spin.y -= D3DX_PI * 2.0f;
	}
	else if (spin.y < -D3DX_PI)
	{
		spin.y += D3DX_PI * 2.0f;
	}

	rot.y += spin.y * SPIN_DEFAULT_COEFFICIENT;

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}
	spin.y = 0.0f;


	//�ړ����ɕǂɂԂ�����
	if (m_bFront == true)
	{
		m_CpuThink = THINK_ROTATION;
		m_nActionTimer = 1;
		m_CpuRotation = (CPU_ROTATION)(rand() % 3);
		m_bFront = false;
	}

#ifdef _DEBUG
	CDebugProc::Print("cn", "ActionTimer :", m_nActionTimer);
	CDebugProc::Print("cn", "CpuMove :", m_CpuMove);
#endif

}


//=============================================================================
// CPU�̉�]����
//=============================================================================
void C3DCharactor::Rotation_CPU(void)
{
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	D3DXVECTOR3 ChangeRot(0.0f, 0.0f, 0.0f);

	switch (m_CpuRotation)
	{
	case CPU_ROTATION_RIGHT:
		ChangeRot.y = (D3DX_PI * 0.5f) + rot.y;
		break;
	case CPU_ROTATION_LEFT:
		ChangeRot.y = (D3DX_PI * -0.5f) + rot.y;
		break;
	case CPU_ROTATION_BACK:
		ChangeRot.y = (D3DX_PI * -1.0f) + rot.y;
		break;
	}

	bool Btest = m_bFront;

	spin.y = ChangeRot.y - rot.y;

	//��]����
	if (spin.y > D3DX_PI)
	{
		spin.y -= D3DX_PI * 2.0f;
	}
	else if (spin.y < -D3DX_PI)
	{
		spin.y += D3DX_PI * 2.0f;
	}

	rot.y += spin.y * SPIN_DEFAULT_COEFFICIENT;

	if (rot.y > D3DX_PI)
	{
		rot.y -= D3DX_PI * 2.0f;
	}
	else if (rot.y < -D3DX_PI)
	{
		rot.y += D3DX_PI * 2.0f;
	}
	spin.y = 0.0f;

}

//=============================================================================
// CPU�̓�������
//=============================================================================
void C3DCharactor::Escape_CPU(void)
{

}

//=============================================================================
// CPU�̒ǔ�(��������)����
//=============================================================================
void C3DCharactor::Homing_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	float fAngle = CIRCLE_ANGLE;
	float fLength = CIRCLE_HOMING;
	if (m_CpuThink == THINK_WATCH)
	{//WATCH�̎��͏�Ɍ���悤��
		fAngle += 50;
		fLength = 0;
	}
	else if(m_CpuThink == THINK_ESCAPE)
	{//ESCAPE�̎��͖ڐ��ɓ�������������
		fLength = 0;
	}


	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];

	D3DXVECTOR3 testpos;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);			// �v���C���[���擾
		if (pPlayer[nCntPlayer] != NULL)
		{
			PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// �v���C���[�̈ʒu���擾
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer] != NULL)
		{
			if (pPlayer[nCntPlayer]->GetID() != GetThisCharactor()->GetID())
			{//������ID�ƈ�v���Ă��Ȃ���Ύ��s
				// �����𑪂�
				float fCircle = ((Pos.x - PlayerPos[nCntPlayer].x) * (Pos.x - PlayerPos[nCntPlayer].x)) + ((Pos.z - PlayerPos[nCntPlayer].z) * (Pos.z - PlayerPos[nCntPlayer].z));
				if (fCircle < fAngle * fAngle && fCircle > fLength)
				{	// �������ɓ�������
					// �v���C���[�ɋ߂Â���
					move.x += sinf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;
					move.z += cosf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;

					float DiffDis = (PlayerPos[nCntPlayer].x + Pos.x) / 2;
					testpos = D3DXVECTOR3((PlayerPos[nCntPlayer].x + Pos.x) / 2, (PlayerPos[nCntPlayer].y + Pos.y) / 2, (PlayerPos[nCntPlayer].z + Pos.z) / 2);
					// �ړI�̊p�x
					float fDestAngle = atan2f((testpos.x - sinf(rot.y)) - Pos.x, (testpos.z - cosf(rot.y)) - Pos.z);

					// ����
					float fDiffAngle = fDestAngle - rot.y;
					if (fDiffAngle > D3DX_PI)
					{
						fDiffAngle -= D3DX_PI * 2.0f;
					}
					if (fDiffAngle < -D3DX_PI)
					{
						fDiffAngle += D3DX_PI * 2.0f;
					}
					rot.y += fDiffAngle * 0.1f;
					if (rot.y > D3DX_PI)
					{
						rot.y -= D3DX_PI * 2.0f;
					}
					if (rot.y < -D3DX_PI)
					{
						rot.y += D3DX_PI * 2.0f;
					}

					if (m_CpuThink == THINK_WATCH)
					{
						//m_CpuThink = THINK_ATTACK;
					}
				}
			}
		}
	}

	if (m_CpuThink != THINK_WATCH)
	{
		if (m_CpuThink == THINK_HOMING)
		{
			//Pos.x += move.x;
			//Pos.y += move.y;
			//Pos.z += move.z;
			//move.x += (0.0f - move.x) * MOVE_DEFAULT_COEFFICIENT;
			//move.y += (0.0f - move.y) * MOVE_DEFAULT_COEFFICIENT;
			//move.z += (0.0f - move.z) * MOVE_DEFAULT_COEFFICIENT;

		}
		else if (m_CpuThink == THINK_ESCAPE)
		{
			/*Pos.x += move.x;
			Pos.y += move.y;
			Pos.z += move.z;*/
			//move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		/*	move.x += (0.0f - move.x) * MOVE_DEFAULT_COEFFICIENT;
			move.y += (0.0f - move.y) * MOVE_DEFAULT_COEFFICIENT;
			move.z += (0.0f - move.z) * MOVE_DEFAULT_COEFFICIENT;*/
		//	move.x *= -1;
		//	move.z *= -1;
		}
	}
	else
	{
		move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}
}

//=============================================================================
// CPU�̍U������
//=============================================================================
void C3DCharactor::Attack_CPU(void)
{
	//�e�̐���
	//GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID());

}
