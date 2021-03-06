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
#include "debugProc.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.25f)			//デフォルトの移動スピード
#define STEP_DEFAULT_MOVEMENT (6.0f)		//デフォルトのステップ量
#define MOVE_DEFAULT_COEFFICIENT (0.85f)	//デフォルトの移動にかかる係数
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//デフォルトの回転にかかる係数

//=============================================================================
// 設定処理
//=============================================================================
void  CCharaBase::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis)
{
	m_pos = pos;
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
	m_CpuThink = THINK_NONE;
	m_CpuMove = CPU_MOVE_NONE;
	m_CpuNode = CPU_NODE_NONE;
	m_nActionTimer = 0;
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void C3DCharactor::Update(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();

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

	//移動の向き設定
	if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * speed;
		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) * speed;

		}
		else
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * speed;

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.25f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.25f)) * speed;


		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.75f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.75f)) * speed;

		}
		else
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.5f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.5f)) * speed;

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
	{
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.0f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.0f)) * speed;

	}
	else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
	{
		move.x += sinf(CameraRot.y + (D3DX_PI * 1.0f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 1.0f)) * speed;
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

	move *= MOVE_DEFAULT_COEFFICIENT;
	pos += move;

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
	//視点移動
	//Y
	if (CCommand::GetCommand("CAMERAMOVE_LEFT", nID))//時計回り
	{
		CameraRot.y -= 0.03f;
	}
	if (CCommand::GetCommand("CAMERAMOVE_RIGHT", nID))//反時計回り
	{
		CameraRot.y += 0.03f;
	}

	//X
	if (CCommand::GetCommand("CAMERAMOVE_UP", nID))
	{
		if (CameraRot.x < D3DX_PI * 0.2f)
		{
			CameraRot.x += 0.03f;
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
			CameraRot.x -= 0.03f;
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


	m_CpuMove = (CPU_MOVE)(rand() % (CPU_MOVE_MAX -1));

	//移動処理
	switch (m_CpuMove)
	{
	case CPU_MOVE_FRONT:
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.0f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.0f)) * speed;
		break;
	case CPU_MOVE_BACK:
		move.x += sinf(CameraRot.y + (D3DX_PI * 1.0f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 1.0f)) * speed;
		break;
	case CPU_MOVE_RIGHT:
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * speed;
		break;
	case CPU_MOVE_LEFT:
		move.x += sinf(CameraRot.y + (D3DX_PI * -0.5f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * -0.5f)) * speed;
		break;
	}



	move *= MOVE_DEFAULT_COEFFICIENT;
	pos += move;

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
	//視点移動
	//Y
	if (CCommand::GetCommand("CAMERAMOVE_LEFT"))//時計回り
	{
		CameraRot.y -= 0.03f;
	}
	if (CCommand::GetCommand("CAMERAMOVE_RIGHT"))//反時計回り
	{
		CameraRot.y += 0.03f;
	}
}

//=============================================================================
// CPUの思考処理
//=============================================================================
void C3DCharactor::Think_CPU(void)
{
	//行動を決める条件文
	m_CpuThink = THINK_MOVE;
	m_nActionTimer = 60;

}

//=============================================================================
// CPUの行動処理
//=============================================================================
void C3DCharactor::Action_CPU(void)
{
	//行動を実行に移す
	switch (m_CpuThink)
	{
	case  THINK_MOVE:
		CharaMove_CPU();
		m_CpuNode = CPU_NODE_RUN;
		break;
	default:
		break;
	}

	//タイマーを減らす
	m_nActionTimer--;
}
