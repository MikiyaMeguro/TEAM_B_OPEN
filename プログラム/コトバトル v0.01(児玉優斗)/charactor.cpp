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
#define MOVE_COEFFICIENT (0.85f);	//移動にかかる係数
#define SPIN_COEFFICIENT (0.10f);	//回転にかかる係数


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
	m_fSpeed = 0.25f;
	m_nCntStepCoolTime = 0;
	CCommand::RegistCommand("PLAYERMOVE_UP",CCommand::INPUTTYPE_KEYBOARD,CCommand::INPUTSTATE_PRESS,DIK_W);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);

	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_SPACE);

}

//=============================================================================
//
// 2Dキャラクター処理 (C2DCharactor)[charactor.cpp]
// Author : Kodama Yuto
//
//=============================================================================
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT C2DCharactor::Init(void)
{
	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void C2DCharactor::Update(void)
{
	switch (CCharaBase::GetMoveType())
	{
	case CCharaBase::MOVETYPE_PLAYER_INPUT:


		break;
	case CCharaBase::MOVETYPE_NPC_AI:
		break;
	}
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
	if (CCommand::GetCommand("PLAYERMOVE_RIGHT"))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP"))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) * speed;


		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN"))
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
	else if (CCommand::GetCommand("PLAYERMOVE_LEFT"))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP"))
		{
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.25f)) * speed;
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.25f)) * speed;


		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN"))
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
	else if (CCommand::GetCommand("PLAYERMOVE_UP"))
	{
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.0f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.0f)) * speed;

	}
	else if (CCommand::GetCommand("PLAYERMOVE_DOWN"))
	{
		move.x += sinf(CameraRot.y + (D3DX_PI * 1.0f)) * speed;
		move.z += cosf(CameraRot.y + (D3DX_PI * 1.0f)) * speed;

	}

	//ステップ移動の設定
	if (CCommand::GetCommand("PLAYERMOVE_STEP"))
	{
		if (m_nCntStepCoolTime <= 0)
		{
			float fStepRot = 0.0f;
			if (CCommand::GetCommand("PLAYERMOVE_UP")) { fStepRot = D3DX_PI * 0.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_DOWN")) { fStepRot = D3DX_PI * 1.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_LEFT")) {
				fStepRot = D3DX_PI * -0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP")) { fStepRot = D3DX_PI * -0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN")) { fStepRot = D3DX_PI * -0.75f; }
			}
			if (CCommand::GetCommand("PLAYERMOVE_RIGHT")) {
				fStepRot = D3DX_PI * 0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP")) { fStepRot = D3DX_PI * 0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN")) { fStepRot = D3DX_PI * 0.75f; }
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

	move *= MOVE_COEFFICIENT;
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

	rot.y += spin.y * SPIN_COEFFICIENT;

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