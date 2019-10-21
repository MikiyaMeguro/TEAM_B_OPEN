//=============================================================================
//
// キャラクター基本処理 (CCharaBase)[charactor.cpp]
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
// マクロ定義
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.6f)			//デフォルトの移動スピード
#define STEP_DEFAULT_MOVEMENT (6.0f)		//デフォルトのステップ量
#define MOVE_DEFAULT_COEFFICIENT (0.20f)	//デフォルトの移動にかかる係数
#define MOVE_AIR_COEFFICIENT (0.10f);
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//デフォルトの回転にかかる係数
#define CIRCLE_HOMING	 (3000)				//追尾範囲(上限)
#define CIRCLE_ANGLE	(100)
#define PATROL_FLAME	(60)
#define CAMERA_MOVE_SPEED (0.05f)
//=============================================================================
// 設定処理
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
// 3Dキャラクター処理 (C3DCharactor)[charactor.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT C3DCharactor::Init(void)
{
	m_nActionTimer = 0;
	m_PatrolTimer = 0;

	return S_OK;
}

//=============================================================================
// 更新処理
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
		{	//考える
			Think_CPU();
		}
		else
		{	//行動する
			Action_CPU();
		}
		break;
	}
	//メッシュフィールドとの当たり判定
	CMeshField *pMesh = CGame::GetMeshField();

	float fHeight = pMesh->GetHeight(pos);
	if (pos.y < fHeight)
	{
		pos.y = fHeight;
	}
	//重力
	move.y = -3.0f;
	//落下高度
	if (pos.y <= -100.0f)
	{
		pos = m_RespawnPos;
		move.y = 0.0f;
	}
}

//=============================================================================
// 移動処理
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


	float fMoveCoefficientX = 1.0f;	//移動係数(X)
	float fMoveCoefficientZ = 1.0f;	//移動係数(Z)
	float fMoveCofBlend = 1.0f;	//移動係数の二つを掛け合わせたもの
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fMoveCoefficientX = fabsf(CCommand::GetXPadStickRotation(true, false, nID));
			fMoveCoefficientZ = fabsf(CCommand::GetXPadStickRotation(true, true, nID));
			fMoveCofBlend = (fMoveCoefficientX > fMoveCoefficientZ) ? fMoveCoefficientX : fMoveCoefficientZ;
		}
	}

	//移動の向き設定
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

	//ステップ移動の設定
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

	//回転制御
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

	//カメラ位置制御
	float fCameraCoefficient = 1.0f;
	//視点移動
	//Y
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fCameraCoefficient = fabsf(CCommand::GetXPadStickRotation(false,false,nID));
		}
	}
	//fCoefficient = CCommand::GetXPadStickRotation(false,false,nID);
	if (CCommand::GetCommand("CAMERAMOVE_LEFT", nID))//時計回り
	{
		CameraRot.y -= CAMERA_MOVE_SPEED * fCameraCoefficient;
	}
	if (CCommand::GetCommand("CAMERAMOVE_RIGHT", nID))//反時計回り
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

	//カメラ設定
	pCameraManager->CreateCamera(GetThisCharactor()->GetCameraName(),
		pCamera->GetType(),
		pCamera->GetPosR(),
		CameraRot,pCamera->GetLength());

	//カメラの参照位置制御
	m_CameraPosR = pos + D3DXVECTOR3(0.0f, 20.0f, 0.0f);
}
//=============================================================================
// CPUの思考処理
//=============================================================================
void C3DCharactor::Think_CPU(void)
{
	m_OldCpuThink = m_CpuThink;

	m_CpuThink = THINK_NONE;
	m_OldCpuThink = THINK_NONE;
	m_CpuMove = CPU_MOVE_NONE;
	m_CpuNode = CPU_NODE_NONE;

	//プロトタイプ用
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

	//行動を決める条件文
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
		敵が前にいる時はBACK
		敵が弾を持ってるときは下がりながら左右移動
		敵が見えないときはできるだけ前進
		弾を持っているときは前進していく
		*/
		m_CpuMove = CPU_MOVE_FRONT;
#endif
	}

	//同じ行動を3回とらない
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
// CPUの行動処理
//=============================================================================
void C3DCharactor::Action_CPU(void)
{
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	//行動を実行に移す
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



	//タイマーを減らす
	m_nActionTimer--;
}

//=============================================================================
// CPUの処理
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


	//移動処理
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


	//回転制御
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


	//移動中に壁にぶつかった
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
// CPUの回転処理
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

	//回転制御
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
// CPUの逃避処理
//=============================================================================
void C3DCharactor::Escape_CPU(void)
{

}

//=============================================================================
// CPUの追尾(見続ける)処理
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
	{//WATCHの時は常に見るように
		fAngle += 50;
		fLength = 0;
	}
	else if(m_CpuThink == THINK_ESCAPE)
	{//ESCAPEの時は目線に入った時逃げる
		fLength = 0;
	}


	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];

	D3DXVECTOR3 testpos;

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);			// プレイヤーを取得
		if (pPlayer[nCntPlayer] != NULL)
		{
			PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// プレイヤーの位置を取得
		}
	}

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer] != NULL)
		{
			if (pPlayer[nCntPlayer]->GetID() != GetThisCharactor()->GetID())
			{//自分のIDと一致していなければ実行
				// 距離を測る
				float fCircle = ((Pos.x - PlayerPos[nCntPlayer].x) * (Pos.x - PlayerPos[nCntPlayer].x)) + ((Pos.z - PlayerPos[nCntPlayer].z) * (Pos.z - PlayerPos[nCntPlayer].z));
				if (fCircle < fAngle * fAngle && fCircle > fLength)
				{	// 距離内に入ったら
					// プレイヤーに近づける
					move.x += sinf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;
					move.z += cosf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;

					float DiffDis = (PlayerPos[nCntPlayer].x + Pos.x) / 2;
					testpos = D3DXVECTOR3((PlayerPos[nCntPlayer].x + Pos.x) / 2, (PlayerPos[nCntPlayer].y + Pos.y) / 2, (PlayerPos[nCntPlayer].z + Pos.z) / 2);
					// 目的の角度
					float fDestAngle = atan2f((testpos.x - sinf(rot.y)) - Pos.x, (testpos.z - cosf(rot.y)) - Pos.z);

					// 差分
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
// CPUの攻撃処理
//=============================================================================
void C3DCharactor::Attack_CPU(void)
{
	//弾の生成
	//GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID());

}
