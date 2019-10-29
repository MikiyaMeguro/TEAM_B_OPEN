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
#include "point.h"
#include "word.h"
#include "tutorial.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.6f)			//�f�t�H���g�̈ړ��X�s�[�h
#define STEP_DEFAULT_MOVEMENT (10.0f)		//�f�t�H���g�̃X�e�b�v��
#define MOVE_DEFAULT_COEFFICIENT (0.20f)	//�f�t�H���g�̈ړ��ɂ�����W��
#define MOVE_AIR_COEFFICIENT (0.10f);
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//�f�t�H���g�̉�]�ɂ�����W��
#define CIRCLE_HOMING	 (3000)				//�ǔ��͈�(���)
#define CIRCLE_ANGLE	(100)
#define PATROL_FLAME	(60)
#define CAMERA_MOVE_SPEED (0.05f)
#define NEAR_DISTANCE	(100)
#define FIELD_OUTSIDE	(300)

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
	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

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
	m_nSameCnt = 0;
	m_fCompareRange = 0;
	m_bWordNear = false;
	m_bJyougai = false;

	nTestCnt = 0;


	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_bNear[nCnt] = false;
	}
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void C3DCharactor::Update(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
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

		//CPU����O�s���Ȃ��悤��
		if (m_bJyougai == false)
		{
			if (FIELD_OUTSIDE < pos.x || -FIELD_OUTSIDE > pos.x ||
				FIELD_OUTSIDE < pos.z || -FIELD_OUTSIDE > pos.z)
			{//��O�Ɉړ��������ɂȂ�����
				m_bJyougai = true;
				move.x = 0;
				move.z = 0;
				m_CpuThink = THINK_ROTATION;
				m_nActionTimer = 2;
				m_CpuRotation = (CPU_ROTATION)(rand() % 3);
			}
		}
		else
		{
			if (FIELD_OUTSIDE - 10 > pos.x && -FIELD_OUTSIDE + 10 < pos.x &&
				FIELD_OUTSIDE - 10 > pos.z && -FIELD_OUTSIDE + 10 < pos.z)
			{//����Ɉړ�����
				m_bJyougai = false;
			}
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

		CPoint *pPoint = NULL;
		if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(GetThisCharactor()->GetID()); }
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* �`���[�g���A���̍�Ƃɂ�肩�������ꍇ �����Ń`���[�g���A������|�C���g���擾 */ }

		if (pPoint != NULL)
		{
			pPoint->SubtractionPoint(1);
		}
	}

	//�X�e�b�v�̑ҋ@���Ԃ̃J�E���g�_�E��
	if (m_nCntStepCoolTime > 0)
	{
		m_nCntStepCoolTime--;
	}

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//if (CCharaBase::GetMoveType() == CCharaBase::MOVETYPE_NPC_AI)
	//{
	//	//CPU����O�s���Ȃ��悤��
	//	if (m_bJyougai == false)
	//	{
	//		if (FIELD_OUTSIDE < pos.x || -FIELD_OUTSIDE > pos.x ||
	//			FIELD_OUTSIDE < pos.z || -FIELD_OUTSIDE > pos.z)
	//		{//��O�Ɉړ��������ɂȂ�����

	//			move.x = 0;
	//			move.z = 0;
	//			m_CpuThink = THINK_ROTATION;
	//			m_nActionTimer = 2;
	//			m_CpuRotation = CPU_ROTATION_BACK;
	//		}
	//	}
	//	else
	//	{
	//		if (FIELD_OUTSIDE - 10 > pos.x && -FIELD_OUTSIDE + 10 < pos.x &&
	//			FIELD_OUTSIDE - 10 > pos.z && -FIELD_OUTSIDE + 10 < pos.z)
	//		{//����Ɉړ�����
	//			m_bJyougai = true;
	//		}
	//	}
	//}

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

			fStepRot += CameraRot.y;

			StepMove(move,fStepRot);

		}
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
	m_CameraPosR = pos + D3DXVECTOR3(0.0f, 40.0f, 0.0f);
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
	//	m_Type = CPU_TYPE_ESCAPE;
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
	{	//�ǂɓ������Ă�
		m_CpuThink = THINK_ROTATION;
		m_nActionTimer = 1;
		m_CpuRotation = (CPU_ROTATION)(rand() % 3);
		m_bFront = false;
	}
	else
	{
#if 0
		switch (m_Type)
		{
		case CPU_TYPE_ESCAPE:
			//m_CpuThink = THINK_ESCAPE;
			//m_nActionTimer = 30;
			m_CpuThink = THINK_PICKUP;
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
#if 1

	if ((GetThisCharactor()->GetWordManager()->GetBulletFlag() == true))
	{	//�e�������Ă���Ƃ�
		m_Type = CPU_TYPE_NONE;
		m_CpuThink = THINK_HAVEBULLET;
		m_nActionTimer = 10;
	}
	else
	{	//�e�������Ă��Ȃ��Ƃ�
		m_CpuThink = THINK_NOTBULLET;
		m_nActionTimer = 10;
	}

	//�����s����3��Ƃ�Ȃ�
	//if (m_OldCpuThink == m_CpuThink)
	//{
	//	m_nSameCnt++;
	//	if (m_nSameCnt == 3)
	//	{
	//		m_nSameCnt = 0;
	//		m_nActionTimer = 0;
	//	}
	//}
	//else
	//{
	//	m_nSameCnt = 0;
	//}
#endif

	//nTestCnt++;
	//if (nTestCnt > 60)
	//{
	//	m_CpuThink = THINK_ROTATION;
	//	m_nActionTimer = 2;
	//	m_CpuRotation = CPU_ROTATION_BACK;
	//	nTestCnt = 0;
	//}
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
	case  THINK_WORD:	//�������l����
		break;
	case  THINK_SIGHT:	//�G���������Ƃ�
		break;
	case  THINK_MISSING:	//�G����������
		break;
	case  THINK_HAVEBULLET:	//�e�������Ă���Ƃ�
		HaveBullet_CPU();
		break;
	case  THINK_NOTBULLET:	//�e�������Ă��Ȃ�
		NotBullet_CPU();
		break;
	case  THINK_PICKUP:	//�������E��
		PickUP_CPU();
		break;
	case  THINK_ESCAPE:	//������
		Homing_CPU();
		break;
	case  THINK_ENEMY_HAVEBULLET:	//�G���e�������Ă���Ƃ�
		break;
	case  THINK_ENEMY_NOBULLET:	//�G���e�������Ă���Ƃ�
		break;
	case  THINK_DODGE:	//���킷
		break;
	case  THINK_ATTACK:	//�U��
		Attack_CPU();
		break;
	case  THINK_NEAR_ENEMY:	//�G���߂�
		break;
	case  THINK_FUR_ENEMY:	//�G������
		break;
	case  THINK_MOVE:	//�ړ�����
		CharaMove_CPU();
		break;
	case  THINK_ROTATION:	//��]����
		m_bFront = false;
		Rotation_CPU();
		break;
	case  THINK_PATROL: //����
		Rotation_CPU();
		break;
	case  THINK_HOMING:	//�ǔ�
		Homing_CPU();
		break;
	case  THINK_WATCH:	//�G������
		Homing_CPU();
		break;
	default:
		break;
	}

	if (m_CpuThink == THINK_ESCAPE)
	{	//������Ƃ������t�Ɉړ�
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

void C3DCharactor::DiffAngle(float fDiffAngle)
{
	D3DXVECTOR3& rot = CCharaBase::GetRotation();

	// ����
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
	if (m_bFront == true )
	{
		m_CpuThink = THINK_ROTATION;
		m_nActionTimer = 2;
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
		ChangeRot.y = (D3DX_PI * 1.0f) + rot.y;
		break;
	}

	//��]����
	spin.y = ChangeRot.y - rot.y;

	if (spin.y > D3DX_PI)
	{
		spin.y = D3DX_PI;
	}
	else if (spin.y < -D3DX_PI)
	{
		spin.y = -D3DX_PI;
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

	D3DXVECTOR3 TargetPos;

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
					if (m_CpuThink != THINK_WATCH)
					{
						// �v���C���[�ɋ߂Â���
						move.x += sinf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;
						move.z += cosf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;
					}
					float DiffDis = (PlayerPos[nCntPlayer].x + Pos.x) / 2;
					TargetPos = D3DXVECTOR3((PlayerPos[nCntPlayer].x + Pos.x) / 2, (PlayerPos[nCntPlayer].y + Pos.y) / 2, (PlayerPos[nCntPlayer].z + Pos.z) / 2);
					// �ړI�̊p�x
					float fDestAngle = atan2f((TargetPos.x - sinf(rot.y)) - Pos.x, (TargetPos.z - cosf(rot.y)) - Pos.z);

					// ����
					float fDiffAngle = fDestAngle - rot.y;

					DiffAngle(fDiffAngle);

					if (fDestAngle > D3DX_PI)
					{
						fDestAngle -= D3DX_PI * 2.0f;
					}
					if (fDestAngle < -D3DX_PI)
					{
						fDestAngle += D3DX_PI * 2.0f;
					}

					if (fDestAngle - 0.05f < rot.y && fDestAngle + 0.05f > rot.y)
					{
						m_CpuThink = THINK_ATTACK;
					}
				}
			}
		}
	}
}

//=============================================================================
// CPU�̍U������
//=============================================================================
void C3DCharactor::Attack_CPU(void)
{
	//�e�̐���	�e�������Ă���Ƃ�����
	if (GetThisCharactor()->GetWordManager()->GetBulletFlag() == true)
	{
		GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(),GetThisCharactor()->GetPosition());
		m_CpuThink = THINK_NONE;
	}
}

//=============================================================================
// CPU�̕����T������
//=============================================================================
void C3DCharactor::PickUP_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	CScene *pScene = NULL;
	m_fCompareRange = 1000000;	//�����̋�������߂����̂�I��
	D3DXVECTOR3 MOKUHYO;	//��ԋ߂��ڕW�ʒu
	bool bWord = false;		//������������
	bool bTango = false;	//�P�ꂪ��������\��������
	int nCntNearWord = 0;		//�߂��ɉ����������邩

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(5);

	int nCntData = GetThisCharactor()->GetWordManager()->SearchWord();	// �g�ݗ��Ă�����̉񐔂��擾
	float *fAnswerNum = NULL;
	if (nCntData > 0)
	{	// ��₪0�ȏ�̏ꍇ
		fAnswerNum = GetThisCharactor()->GetWordManager()->GetAnswerData();	// �������擾
	}

	while (pScene != NULL)
	{// �D�揇�ʂ�5�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				CWord *pWord = ((CWord*)pScene);		// CWord�փL���X�g(�^�̕ύX)

				// �����𑪂�
				float fCircle = ((Pos.x - pWord->GetPos().x) * (Pos.x - pWord->GetPos().x)) + ((Pos.z - pWord->GetPos().z) * (Pos.z - pWord->GetPos().z));

				if (fCircle < 300 * 100)
				{//�͈͓��ɕ�����������
					nCntNearWord++;		//���Z
					float fNum = (float)pWord->GetWordNum();	// �����̔ԍ����擾
					for (int nCntAnswer = 0; nCntAnswer < nCntData; nCntAnswer++)
					{	// ���̐��񂵂� �����ԍ��ƍ����Ă��邩���r
						if (fAnswerNum[nCntAnswer] == fNum)
						{	// �����Ă����ꍇ �ʒu���擾��break����
							m_fCompareRange = fCircle;
							MOKUHYO = pWord->GetPos();
							bWord = true;
							bTango = true;
							break;
						}
					}
					if (bTango == false)
					{//�P�ꂪ�������Ȃ��Ƃ��͓K���ɏE��
						//��ԋ߂��������L��
						m_fCompareRange = fCircle;
						MOKUHYO = pWord->GetPos();
						bWord = true;
					}
				}
			}
		}
		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}

	//���[�h���͈͓��ɂ��鎞�ړ�����
	if (bWord == true)
	{
		// �ړI�̊p�x
		float fDestAngle = atan2f((MOKUHYO.x - sinf(rot.y)) - Pos.x, (MOKUHYO.z - cosf(rot.y)) - Pos.z);
		// ����
		float fDiffAngle = fDestAngle - rot.y;
		DiffAngle(fDiffAngle);
		//�ړ�
		move.x += sinf(atan2f(MOKUHYO.x - Pos.x, MOKUHYO.z - Pos.z)) * speed;
		move.z += cosf(atan2f(MOKUHYO.x - Pos.x, MOKUHYO.z - Pos.z)) * speed;
	}

	if (nCntNearWord == 0)
	{//�߂��ɕ���������Ȃ�
		m_bWordNear = true;
		m_CpuThink = THINK_MOVE;
		m_CpuMove = CPU_MOVE_FRONT;
		m_nActionTimer = 30;
		m_bWordNear = false;
	}

}

//=============================================================================
// �e�������Ă���Ƃ��̏���
//=============================================================================
void C3DCharactor::HaveBullet_CPU(void)
{

}

//=============================================================================
// �e�������Ă��Ȃ����̏���
//=============================================================================
void C3DCharactor::NotBullet_CPU(void)
{
	bool bPICKUP = false;
	int	nCntNear = 0;

	//�N���߂���
	NearOrFur_CPU();
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_bNear[nCntPlayer] == false)
		{
			nCntNear++;
		}
	}

	if (nCntNear == 4)
	{
		m_CpuThink = THINK_PICKUP;
	}
	else
	{
		m_CpuThink = THINK_MOVE;
		m_CpuMove = CPU_MOVE_FRONT;
		m_nActionTimer = 30;
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_bNear[nCntPlayer] = false;
	}

}

//=============================================================================
// �߂���������
//=============================================================================
void C3DCharactor::NearOrFur_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();

	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];
	m_fCompareRange = 1000000;

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
				if (fCircle < 50 * 100)
				{
					if (pPlayer[nCntPlayer]->GetWordManager()->GetBulletFlag() == true)
					{
						m_bNear[nCntPlayer] = true;
					}
				}
			}
		}
	}

}

//=============================================================================
// �X�e�b�v����
//=============================================================================
void C3DCharactor::StepMove(D3DXVECTOR3& move, float& fRot)
{
	move.x += sinf(fRot) * STEP_DEFAULT_MOVEMENT;
	move.z += cosf(fRot) * STEP_DEFAULT_MOVEMENT;

	m_nCntStepCoolTime = 30;
	GetThisCharactor()->SetTransTime(5);
}