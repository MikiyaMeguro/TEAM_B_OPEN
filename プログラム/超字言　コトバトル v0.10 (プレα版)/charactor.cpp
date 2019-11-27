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
#include "tutorial.h"
#include "game.h"
#include "result.h"
#include "debugProc.h"
#include "meshField.h"
#include "word_manager.h"
#include "point.h"
#include "word.h"

#include "waypoint.h"

#include "avoidui.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.6f)			//デフォルトの移動スピード
#define STEP_DEFAULT_MOVEMENT (10.0f)		//デフォルトのステップ量
#define MOVE_DEFAULT_COEFFICIENT (0.20f)	//デフォルトの移動にかかる係数
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//デフォルトの回転にかかる係数
#define CIRCLE_HOMING	 (3000)				//追尾範囲(上限)
#define CIRCLE_ANGLE	(100000)
#define PATROL_FLAME	(60)
#define CAMERA_MOVE_SPEED (0.05f)
#define NEAR_DISTANCE	(100)
#define FIELD_OUTSIDE	(300)

//CAvoidUi *C3DCharactor::m_pCAvoidUi = NULL;

//=============================================================================
// 設定処理
//=============================================================================
void  CCharaBase::Set(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CHARACTOR_MOVE_TYPE type, CPlayer* pThis)
{
	//変数初期化
	m_pos = pos;
	m_RespawnPos = pos;
	m_rot = rot;
	m_type = type;
	m_pThisCharactor = pThis;

	m_Move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Spin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fSpeed = MOVE_DEFAULT_SPEED;
	m_fStep = STEP_DEFAULT_MOVEMENT;
	m_fMoveCoeffient = MOVE_DEFAULT_COEFFICIENT;
	m_fSpinCoeffient = SPIN_DEFAULT_COEFFICIENT;
	m_fCofMoveBlend = 1.0f;
	m_nCntStepCoolTime = 0;

	m_pWayPoint = NULL;
	if (m_pWayPoint == NULL)
	{
		//m_pWayPoint = CWaypoint::Create(m_pos, 10, 10, "NUMBER");
	}

	//コマンド定義
	CCommand::RegistCommand("PLAYERMOVE_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_W);
	CCommand::RegistCommand("PLAYERMOVE_UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_UP);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("PLAYERMOVE_DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_DOWN);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("PLAYERMOVE_RIGHT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);
	CCommand::RegistCommand("PLAYERMOVE_LEFT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_SPACE);
	CCommand::RegistCommand("PLAYERMOVE_STEP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

	CCommand::RegistCommand("CAMERAMOVE_LEFT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("CAMERAMOVE_LEFT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_LEFT);
	CCommand::RegistCommand("CAMERAMOVE_RIGHT", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);
	CCommand::RegistCommand("CAMERAMOVE_RIGHT", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_RIGHT);
	CCommand::RegistCommand("CAMERAMOVE_UP", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_UP);
	CCommand::RegistCommand("CAMERAMOVE_UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_UP);
	CCommand::RegistCommand("CAMERAMOVE_DOWN", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("CAMERAMOVE_DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHTSTICK_DOWN);

	CCommand::RegistCommand("TEST_FLY_UP", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_Y);
	CCommand::RegistCommand("TEST_FLY_DOWN", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
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
	m_nSameCnt = 0;
	m_fCompareRange = 0;
	m_bWordNear = false;
	m_bJyougai = false;
	m_bGoal = true;
	m_bSearch = false;
	m_bBlock = false;
	m_bNearWard = false;
	m_MarkWardPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_MarkWayPoint = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTargetWP = 0;
	nTestCnt = 0;
	m_bWait = false;
	m_nTimerMove = 0;
	m_bNotWayPoint = false;
	m_fOldCircle = 0;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_bNear[nCnt] = false;
	}

	//	回避UI
	m_pCAvoidUi = CAvoidUi::Create(CCharaBase::GetPosition() + D3DXVECTOR3(0.0f, 13.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f),
		D3DXVECTOR3(18.0f, 18.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// 更新処理
//=============================================================================
void C3DCharactor::Update(void)
{
	CCameraManager* pCameraManager = CManager::GetCameraManager();
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& move = CCharaBase::GetMove();

	//経路情報
	if (m_pWayPoint != NULL)
	{
		m_pWayPoint->InRange(pos);
	}
	if (m_bWait == false)
	{
		switch (CCharaBase::GetMoveType())
		{
		case CCharaBase::MOVETYPE_PLAYER_INPUT:
			if (m_pWayPoint == NULL)
			{
				//	m_nTargetWP = 1;
				//	m_pWayPoint = CWaypoint::Create(m_RespawnPos, 10, 10, "NUMBER");
			}
			CharaMove_Input();
			break;
		case CCharaBase::MOVETYPE_NPC_AI:
			if (CGame::GetbStageSet() == false)
			{
				if (m_nActionTimer == 0)
				{	//考える
					Think_CPU();
				}
				else
				{	//行動する
					Action_CPU();
				}
			}
			//CPUが場外行かないように
			if (m_bJyougai == false)
			{
				if (FIELD_OUTSIDE < pos.x || -FIELD_OUTSIDE > pos.x ||
					FIELD_OUTSIDE < pos.z || -FIELD_OUTSIDE > pos.z)
				{//場外に移動しそうになった時
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
				{//場内に移動した
					m_bJyougai = false;
				}
			}
			break;
		case CCharaBase::MOVETYPE_RANKING_CHARA:
			pos += move;
			//速度に係数を掛ける
			CUtilityMath::MoveCoeffient(move, GetMoveCoeffient());
			break;
		}
	}

	//メッシュフィールドとの当たり判定
	CMeshField *pMesh = NULL;

	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		pMesh = CGame::GetMeshField();
	}
	else if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		pMesh = CResult::GetMeshField();
	}
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		pMesh = CTutorial::GetMeshField();
	}

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
		//設定
		pos = m_RespawnPos;
		GetThisCharactor()->SetOldPosition(m_RespawnPos);
		move.y = 0.0f;
		GetThisCharactor()->SetTransTime(60);

		CPoint *pPoint = NULL;
		if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(GetThisCharactor()->GetID()); }
		else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* チュートリアルの作業によりかかった場合 ここでチュートリアルからポイントを取得 */ }

		if (pPoint != NULL)
		{
			pPoint->SubtractionPoint(1);
		}
	}

	//ステップの待機時間のカウントダウン
	if (m_nCntStepCoolTime > 0)
	{
		m_nCntStepCoolTime--;
	}

	//マトリックスの計算
	CUtilityMath::CalWorldMatrix(&m_mtxWorld, pos, rot);
	//カメラの参照位置制御
	m_CameraPosR = GetPosition() + D3DXVECTOR3(0.0f, 40.0f, 0.0f);

#ifdef _DEBUG

	if (m_pWayPoint != NULL)
	{
		CDebugProc::Print("cfcfcf", "MarkWayPoint : X ", m_MarkWayPoint.x, " Y ", m_MarkWayPoint.y, " Z ", m_MarkWayPoint.z);
		CDebugProc::Print("cn", "m_bGoal : ", (int)m_bGoal);
		CDebugProc::Print("cn", "m_bNearWard : ", (int)m_bNearWard);
		CDebugProc::Print("cn", "m_bSearch : ", (int)m_bSearch);
	}

	switch (m_CpuThink)
	{
	case  THINK_HAVEBULLET:
		CDebugProc::Print("c", "THINK_HAVEBULLET");
		break;
	case  THINK_NOTBULLET:
		CDebugProc::Print("c", "THINK_NOTBULLET");
		break;
	case  THINK_PICKUP:
		CDebugProc::Print("c", "THINK_PICKUP");
		break;
	case  THINK_WAYPOINTMOVE:
		CDebugProc::Print("c", "THINK_WAYPOINTMOVE");
		break;
	case  THINK_WAYPOINTROUTE:
		CDebugProc::Print("c", "THINK_WAYPOINTROUTE");
		break;
	default:
		break;
	}
#endif


	if (m_pCAvoidUi != NULL)
	{//	回避UIが使用されてつ
		m_pCAvoidUi->SetPos(pos + D3DXVECTOR3(0.0f, 13.0f, 0.0f));
		if (m_nCntStepCoolTime < 1)
		{//	step時間外
			m_pCAvoidUi->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{//	step時間内
			m_pCAvoidUi->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

		}
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
	D3DXVECTOR3 CameraRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	if (pCamera != NULL)
	{
		CameraRot = pCamera->GetRotation();
	}

	//親クラスから値を取得(参照を使う)
	D3DXVECTOR3& pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	//XPadコントローラのスティック感度設定
	float fMoveCoefficientX = 1.0f;	//移動係数(X)
	float fMoveCoefficientZ = 1.0f;	//移動係数(Z)
	m_fCofMoveBlend = 1.0f;	//移動係数の二つを掛け合わせたもの
	if (CManager::GetXInput(nID) != NULL)
	{
		if (CManager::GetXInput(nID)->GetConnect() == true)
		{
			fMoveCoefficientX = fabsf(CCommand::GetXPadStickRotation(true, false, nID));
			fMoveCoefficientZ = fabsf(CCommand::GetXPadStickRotation(true, true, nID));
			m_fCofMoveBlend = (fMoveCoefficientX > fMoveCoefficientZ) ? fMoveCoefficientX : fMoveCoefficientZ;
		}
	}

	//移動の向き設定
	if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{//右上
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.25f)) * (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.25f)) *  (speed * m_fCofMoveBlend);
		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{//右下
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.75f)) *  (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.75f)) *  (speed * m_fCofMoveBlend);

		}
		else
		{//右
			move.x += sinf(CameraRot.y + (D3DX_PI * 0.5f)) * (speed * fMoveCoefficientX);
			move.z += cosf(CameraRot.y + (D3DX_PI * 0.5f)) * (speed * fMoveCoefficientX);


		}
		//if (GetThisCharactor()->GetMotion() != CPlayer::MOTION_STEP&&
		//	GetThisCharactor()->GetMotion() != CPlayer::MOTION_SHOT)
		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//今のモーションがステップでも弾打ちでもなければ

		 //モーション分け
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_RIGHT, CPlayer::LOWER_BODY);

		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID))
	{
		if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
		{//左上
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.25f)) *  (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.25f)) *  (speed * m_fCofMoveBlend);


		}
		else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
		{//左下
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.75f)) *  (speed * m_fCofMoveBlend);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.75f)) *  (speed * m_fCofMoveBlend);

		}
		else
		{//左
			move.x += sinf(CameraRot.y + (D3DX_PI * -0.5f)) * (speed * fMoveCoefficientX);
			move.z += cosf(CameraRot.y + (D3DX_PI * -0.5f)) * (speed * fMoveCoefficientX);

		}
		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//今のモーションがステップでも弾打ちでもなければ

		 //モーション分け
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_LEFT, CPlayer::LOWER_BODY);
		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_UP", nID))
	{//上
		move.x += sinf(CameraRot.y + (D3DX_PI * 0.0f)) * (speed * fMoveCoefficientZ);
		move.z += cosf(CameraRot.y + (D3DX_PI * 0.0f)) * (speed * fMoveCoefficientZ);

		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//今のモーションがステップでも弾打ちでもなければ

		 //モーション分け
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
		}
	}
	else if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID))
	{//下
		move.x += sinf(CameraRot.y + (D3DX_PI * 1.0f)) * (speed * fMoveCoefficientZ);
		move.z += cosf(CameraRot.y + (D3DX_PI * 1.0f)) * (speed * fMoveCoefficientZ);

		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)

		{//今のモーションがステップでも弾打ちでもなければ

		 //モーション分け
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_WALK, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_WALK, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_WALK_FRONT, CPlayer::LOWER_BODY);
		}
	}
	else
	{
		if (GetThisCharactor()->GetMotion() != 6 &&
			GetThisCharactor()->GetMotion() != 7)
		{//今のモーションがステップでも弾打ちでもなければ
		 //モーション分け
			if (GetThisCharactor()->GetWordManager()->GetBulletFlag())
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_SETUP_NEUTRAL, CPlayer::UPPER_BODY);
			}
			else
			{
				GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_NEUTRAL, CPlayer::UPPER_BODY);
			}
			GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_NEUTRAL, CPlayer::LOWER_BODY);
		}
	}

	//飛行(TEST)
	//if (CCommand::GetCommand("TEST_FLY_UP", nID))
	//{
	//	pos.y -= speed;
	//}
	//else if (CCommand::GetCommand("TEST_FLY_DOWN", nID))
	//{
	//	pos.y += speed;
	//}

	//ステップ移動の設定
	if (CCommand::GetCommand("PLAYERMOVE_STEP", nID))
	{
		if (m_nCntStepCoolTime <= 0)
		{
			//ステップの角度設定
			float fStepRot = 0.0f;
			if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * 0.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * 1.0f; }
			if (CCommand::GetCommand("PLAYERMOVE_LEFT", nID))
			{
				fStepRot = D3DX_PI * -0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * -0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * -0.75f; }
			}
			if (CCommand::GetCommand("PLAYERMOVE_RIGHT", nID))
			{
				fStepRot = D3DX_PI * 0.5f;
				if (CCommand::GetCommand("PLAYERMOVE_UP", nID)) { fStepRot = D3DX_PI * 0.25f; }
				if (CCommand::GetCommand("PLAYERMOVE_DOWN", nID)) { fStepRot = D3DX_PI * 0.75f; }
			}

			fStepRot += CameraRot.y;

			StepMove(move, fStepRot);

		}
	}
	CDebugProc::Print("cn", "STEP_COOLTIME : ", m_nCntStepCoolTime);

	pos += move;

	//速度に係数を掛ける
	CUtilityMath::MoveCoeffient(move, GetMoveCoeffient());

	spin.y = CameraRot.y - rot.y;

	//回転制御
	CUtilityMath::RotateNormarizePI(&spin.y);

	rot.y += spin.y * GetSpinCoeffient();

	CUtilityMath::RotateNormarizePI(&rot.y);

	spin.y = 0.0f;

	//カメラ位置制御
	if (GetThisCharactor()->GetLockOnCharactor() == NULL)
	{//ロックオンしていなければ
		float fCameraCoefficient = 1.0f;
		//視点移動
		//Y
		if (CManager::GetXInput(nID) != NULL)
		{
			if (CManager::GetXInput(nID)->GetConnect() == true)
			{
				fCameraCoefficient = fabsf(CCommand::GetXPadStickRotation(false, false, nID));
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

#ifdef _DEBUG
		// 入力情報を取得
		CInputKeyboard *pInputKeyboard;
		pInputKeyboard = CManager::GetInputKeyboard();

		if (pInputKeyboard->GetTrigger(DIK_NUMPAD2))
		{
			m_nTargetWP = 1;
		}
		if (pInputKeyboard->GetTrigger(DIK_NUMPAD8))
		{
			m_nTargetWP = 6;
		}
		if (pInputKeyboard->GetTrigger(DIK_NUMPAD4))
		{
			m_nTargetWP = 3;
		}
		if (pInputKeyboard->GetTrigger(DIK_NUMPAD6))
		{
			m_nTargetWP = 4;
		}
		//目標のマスの番号を渡す
		if (m_pWayPoint != NULL)
		{
			m_pWayPoint->ReturnPointMove();
			int nNextPoint = 0;
			nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);

			if (m_pWayPoint->GetWPbBlock(nNextPoint) == true)
			{
				m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
				m_bBlock = true;
			}
			CDebugProc::Print("cn", "目標マス :", m_nTargetWP);
			CDebugProc::Print("cn", "現在のマス :", m_pWayPoint->GetNowWP());
		}
#endif

		//カメラ設定
		pCameraManager->CreateCamera(GetThisCharactor()->GetCameraName(),
			pCamera->GetType(),
			pCamera->GetPosR(),
			CameraRot,
			pCamera->GetLength());
	}
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
#if 1
		if (m_pWayPoint == NULL)
		{
			m_pWayPoint = CWaypoint::Create(m_RespawnPos, 10, 10, "NUMBER");
		}

		if ((GetThisCharactor()->GetWordManager()->GetBulletFlag() == true))
		{	//弾を持っているとき
			m_Type = CPU_TYPE_NONE;
			m_CpuThink = THINK_HAVEBULLET;
			m_nActionTimer = 30;
		}
		else
		{	//弾を持っていないとき
			m_CpuThink = THINK_NOTBULLET;
			m_nActionTimer = 30;
		}
#endif

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

#if 0
	if (m_pWayPoint == NULL)
	{
		m_pWayPoint = CWaypoint::Create(m_RespawnPos, 10, 10, "NUMBER");
	}
	if ((GetThisCharactor()->GetWordManager()->GetBulletFlag() == true))
	{	//弾を持っているとき
		m_Type = CPU_TYPE_NONE;
		m_CpuThink = THINK_HAVEBULLET;
		m_nActionTimer = 30;
	}
	else
	{	//弾を持っていないとき
		m_CpuThink = THINK_NOTBULLET;
		m_nActionTimer = 30;
	}
#endif

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
	case  THINK_WORD:	//文字を考える
		break;
	case  THINK_SIGHT:	//敵が見えたとき
		break;
	case  THINK_MISSING:	//敵を見失った
		break;
	case  THINK_HAVEBULLET:	//弾を持っているとき
		HaveBullet_CPU();
		break;
	case  THINK_NOTBULLET:	//弾を持っていない
		NotBullet_CPU();
		break;
	case  THINK_PICKUP:	//文字を拾う
		if (m_bGoal == true && m_bNearWard == false && m_bSearch == false)
		{
			PickUP_CPU();
		}
		else if (m_bNotWayPoint == true)
		{
			WayPointMove_CPU();
		}
		else
		{
			//WayPointMove_CPU();
			WayPointRoute_CPU();
		}
		break;
	case  THINK_ESCAPE:	//逃げる
		Homing_CPU();
		break;
	case  THINK_ENEMY_HAVEBULLET:	//敵が弾を持っているとき
		break;
	case  THINK_ENEMY_NOBULLET:	//敵が弾を持っているとき
		break;
	case  THINK_DODGE:	//かわす
		break;
	case  THINK_ATTACK:	//攻撃
		Attack_CPU();
		break;
	case  THINK_NEAR_ENEMY:	//敵が近い
		break;
	case  THINK_FUR_ENEMY:	//敵が遠い
		break;
	case  THINK_MOVE:	//移動処理
		CharaMove_CPU();
		break;
	case  THINK_ROTATION:	//回転処理
		m_bFront = false;
		Rotation_CPU();
		break;
	case  THINK_PATROL: //巡回
		Rotation_CPU();
		break;
	case  THINK_HOMING:	//追尾
		Homing_CPU();
		break;
	case  THINK_WATCH:	//敵を見る
		Homing_CPU();
		break;
	case  THINK_WAYPOINTMOVE:	//ランダム経路
		WayPointMove_CPU();
		break;
	case  THINK_WAYPOINTROUTE:	//ランダム経路
								//WayPointMove_CPU();
		WayPointRoute_CPU();
		break;
	default:
		break;
	}

	if (m_CpuThink == THINK_ESCAPE)
	{	//逃げるときだけ逆に移動
		pos.x -= move.x;
		pos.y += move.y;
		pos.z -= move.z;
	}
	else
	{
		pos += move;
	}

	//速度に係数を掛ける
	CUtilityMath::MoveCoeffient(move, GetMoveCoeffient());

	//タイマーを減らす
	m_nActionTimer--;
}

//=============================================================================
// CPUの回転処理
//=============================================================================
void C3DCharactor::DiffAngle(float fDiffAngle)
{
	D3DXVECTOR3& rot = CCharaBase::GetRotation();

	// 差分
	CUtilityMath::RotateNormarizePI(&fDiffAngle);
	rot.y += fDiffAngle * 0.1f;
	CUtilityMath::RotateNormarizePI(&rot.y);
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
	CUtilityMath::RotateNormarizePI(&spin.y);

	rot.y += spin.y * GetSpinCoeffient();

	CUtilityMath::RotateNormarizePI(&rot.y);

	spin.y = 0.0f;

	//移動中に壁にぶつかった
	if (m_bFront == true)
	{
		m_CpuThink = THINK_ROTATION;
		m_nActionTimer = 2;
		m_CpuRotation = (CPU_ROTATION)(rand() % 3);
		m_bFront = false;
	}

#ifdef _DEBUG
	//CDebugProc::Print("cn", "ActionTimer :", m_nActionTimer);
	//CDebugProc::Print("cn", "CpuMove :", m_CpuMove);
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
		ChangeRot.y = (D3DX_PI * 1.0f) + rot.y;
		break;
	}

	//回転制御
	spin.y = ChangeRot.y - rot.y;

	//回転制御
	CUtilityMath::RotateNormarizePI(&spin.y);

	rot.y += spin.y * GetSpinCoeffient();

	CUtilityMath::RotateNormarizePI(&rot.y);

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
		fAngle += 50000;
		fLength = 0;
	}
	else if (m_CpuThink == THINK_ESCAPE)
	{//ESCAPEの時は目線に入った時逃げる
		fLength = 0;
	}

	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];

	D3DXVECTOR3 TargetPos;
	float fCircle = 0;				//距離
	float fCompare = 1000000;		//比べる
	int nNearPlayer;


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
				fCircle = ((Pos.x - PlayerPos[nCntPlayer].x) * (Pos.x - PlayerPos[nCntPlayer].x)) + ((Pos.z - PlayerPos[nCntPlayer].z) * (Pos.z - PlayerPos[nCntPlayer].z));
				if (fCircle < fCompare)
				{	//一番近いプレイヤーを記憶
					fCompare = fCircle;
					nNearPlayer = nCntPlayer;
				}
			}
		}
	}

#if 1
	if (fCompare < 100000 && GetThisCharactor()->GetWordManager()->GetBulletFlag() == false)
	{	// 距離内に入ったら逃げるための処理
		if (m_CpuThink != THINK_WATCH)
		{
			// プレイヤーに近づける
			move.x += sinf(atan2f(PlayerPos[nNearPlayer].x - Pos.x, PlayerPos[nNearPlayer].z - Pos.z)) * speed;
			move.z += cosf(atan2f(PlayerPos[nNearPlayer].x - Pos.x, PlayerPos[nNearPlayer].z - Pos.z)) * speed;
		}
		float DiffDis = (PlayerPos[nNearPlayer].x + Pos.x) / 2;
		TargetPos = D3DXVECTOR3((PlayerPos[nNearPlayer].x + Pos.x) / 2, (PlayerPos[nNearPlayer].y + Pos.y) / 2, (PlayerPos[nNearPlayer].z + Pos.z) / 2);
		// 目的の角度
		float fDestAngle = atan2f((TargetPos.x - sinf(rot.y)) - Pos.x, (TargetPos.z - cosf(rot.y)) - Pos.z);
		// 差分
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
	}
#endif

	if (fCompare < 100000 && GetThisCharactor()->GetWordManager()->GetBulletFlag() == true)
	{// 距離内に入り弾を持っている時
		TargetPos = D3DXVECTOR3((PlayerPos[nNearPlayer].x + Pos.x) / 2, (PlayerPos[nNearPlayer].y + Pos.y) / 2, (PlayerPos[nNearPlayer].z + Pos.z) / 2);
		// 目的の角度
		float fDestAngle = atan2f((TargetPos.x - sinf(rot.y)) - Pos.x, (TargetPos.z - cosf(rot.y)) - Pos.z);
		// 差分
		float fDiffAngle = fDestAngle - rot.y;
		CUtilityMath::RotateNormarizePI(&fDiffAngle);
		DiffAngle(fDiffAngle);
		if (fDestAngle > D3DX_PI)
		{
			fDestAngle -= D3DX_PI * 2.0f;
		}
		if (fDestAngle < -D3DX_PI)
		{
			fDestAngle += D3DX_PI * 2.0f;
		}
		//視野内に入ったら撃つ
		if (fDestAngle - 0.11f < rot.y && fDestAngle + 0.11f > rot.y)
		{
			m_CpuThink = THINK_ATTACK;
		}
	}
	else if (fCompare >= 100000 && GetThisCharactor()->GetWordManager()->GetBulletFlag() == true)
	{// 距離外で弾を持っている時
		float	fMinCircle = 100000;
		int nNumWP = 0;

		//位置情報を取得
		m_pWayPointPos = &m_pWayPoint->ReturnPointMove();
		//移動可能なマスは何マスあるか
		int nCntWP = m_pWayPoint->CntWayPoint();
		//どのマスに移動するか決める
		for (int nCnt = 0; nCnt < nCntWP; nCnt++)
		{
			// 距離を測る 一番近い敵と自分の周りのウェイポイントを比べてどのポイントに行くか決める
			float fCircle = ((PlayerPos[nNearPlayer].x - m_pWayPointPos[nCnt].x) * (PlayerPos[nNearPlayer].x - m_pWayPointPos[nCnt].x)) + ((PlayerPos[nNearPlayer].z - m_pWayPointPos[nCnt].z) * (PlayerPos[nNearPlayer].z - m_pWayPointPos[nCnt].z));
			if (fCircle < fMinCircle)
			{
				fMinCircle = fCircle;
				nNumWP = nCnt;
				m_nTargetWP = nCnt;
			}
		}

		//目標のマスの位置を渡す
		m_MarkWayPoint = m_pWayPointPos[m_nTargetWP];

		// 目的の角度
		float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
		// 差分
		float fDiffAngle = fDestAngle - rot.y;
		DiffAngle(fDiffAngle);
		//移動
		move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
		move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
	}
}

//=============================================================================
// CPUの攻撃処理
//=============================================================================
void C3DCharactor::Attack_CPU(void)
{
	//弾の生成	弾を持っているときだけ
	if (GetThisCharactor()->GetWordManager()->GetBulletFlag() == true && CGame::GetbStageSet() == false)
	{
		GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition(), CCharaBase::GetRotation());
		m_CpuThink = THINK_NONE;
	}
	else if(GetThisCharactor()->GetWordManager()->GetBulletFlag() == false
		&& GetThisCharactor()->GetWordManager()->GetCntNum() > 1 && CGame::GetbStageSet() == false)
	{
		GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(), CCharaBase::GetPosition(), CCharaBase::GetRotation());
	}
}

//=============================================================================
// CPUの文字探し処理
//=============================================================================
void C3DCharactor::PickUP_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	CScene *pScene = NULL;
	m_fCompareRange = 1000000;	//初期の距離から近いものを選ぶ
								//D3DXVECTOR3 MOKUHYO;	//一番近い目標位置
	bool bWord = false;		//文字を見つけた
	bool bTango = false;	//単語が完成する可能性がある
	int nCntNearWord = 0;		//近くに何個文字があるか

								// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(5);

	int nCntData = GetThisCharactor()->GetWordManager()->SearchWord();	// 組み立てられる候補の回数を取得
	float *fAnswerNum = NULL;
	if (nCntData > 0)
	{	// 候補が0以上の場合
		fAnswerNum = GetThisCharactor()->GetWordManager()->GetAnswerData();	// 答えを取得
	}

	while (pScene != NULL)
	{// 優先順位が5のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_WORD)
			{// オブジェクトの種類を確かめる
				CWord *pWord = ((CWord*)pScene);		// CWordへキャスト(型の変更)
														// 距離を測る
				float fCircle = ((Pos.x - pWord->GetPos().x) * (Pos.x - pWord->GetPos().x)) + ((Pos.z - pWord->GetPos().z) * (Pos.z - pWord->GetPos().z));
				if (bTango == false)
				{
					float fNum = (float)pWord->GetWordNum();	// 文字の番号を取得
					for (int nCntAnswer = 0; nCntAnswer < nCntData; nCntAnswer++)
					{	// 候補の数回して 文字番号と合っているかを比較
						if (fAnswerNum[nCntAnswer] == fNum)
						{	// 合っていた場合 位置を取得しbreakする
							m_fCompareRange = fCircle;
							m_MarkWardPos = pWord->GetPos();
							bWord = true;
							bTango = true;
							break;
						}
					}
					if (bTango == true)
					{
						break;
					}
				}

				if (GetThisCharactor()->GetWordManager()->GetCntNum() < 2 && fCircle < 50000 && bTango == false)
				{//範囲内に文字があった
					nCntNearWord++;
					 //一番近い距離を記憶
					m_fCompareRange = fCircle;
					m_MarkWardPos = pWord->GetPos();
					bWord = true;
				}
			}
		}
		// 次のシーンに進める
		pScene = pSceneNext;
	}

	if (GetThisCharactor()->GetWordManager()->GetCntNum() ==  2 && bTango == false)
	{//
		m_CpuThink = THINK_ATTACK;
		bWord = true;
	}

	//ワードが範囲内にある時移動する
	if (bWord == true)
	{
		//WayPointMove_CPU();
		WayPointRoute_CPU();
	}
	else if (nCntNearWord == 0)
	{//近くに文字が一つもない
		m_bWordNear = false;
		m_CpuThink = THINK_WAYPOINTMOVE;
		m_nActionTimer = 60;
	}

}

//=============================================================================
// 弾を持っているときの処理
//=============================================================================
void C3DCharactor::HaveBullet_CPU(void)
{
	int	nCntNear = 0;

	//誰が近いか
	NearOrFur_CPU();
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_bNear[nCntPlayer] == true)
		{
			nCntNear++;
		}
	}

	if (nCntNear > 0)
	{//近くに敵がいる
		m_CpuThink = THINK_HOMING;
		m_nActionTimer = 60;
	}
	else
	{//近くに敵がいない
		m_CpuThink = THINK_WAYPOINTMOVE;
		m_CpuMove = CPU_MOVE_FRONT;
		m_nActionTimer = 60;
	}

}

//=============================================================================
// 弾を持っていない時の処理
//=============================================================================
void C3DCharactor::NotBullet_CPU(void)
{
	bool bPICKUP = false;
	int	nCntNear = 0;

	//誰が近いか
	NearOrFur_CPU();
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (m_bNear[nCntPlayer] == true)
		{
			nCntNear++;
		}
	}

	if (nCntNear < 3)
	{
		m_CpuThink = THINK_PICKUP;
		m_nActionTimer = 30;
	}
	else
	{
		m_CpuThink = THINK_PICKUP;
		m_nActionTimer = 30;
	}
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		m_bNear[nCntPlayer] = false;
	}

}

//=============================================================================
// 近いか遠いか
//=============================================================================
void C3DCharactor::NearOrFur_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();

	CPlayer *pPlayer[MAX_PLAYER];
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];
	m_fCompareRange = 1000000;

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
				if (fCircle < 80000)
				{
					m_bNear[nCntPlayer] = true;
				}
			}
		}
	}
}

//=============================================================================
//　マス目ランダム移動
//=============================================================================
void C3DCharactor::WayPointMove_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	int nRandPos = 0;
	int nNextPoint = 0;
	int nNowWp = 0;

	float fCircle = ((Pos.x - m_MarkWayPoint.x) * (Pos.x - m_MarkWayPoint.x)) + ((Pos.z - m_MarkWayPoint.z) * (Pos.z - m_MarkWayPoint.z));

	if (fCircle < 100)
	{
		m_bRandomGoal = true;
		if (m_bNotWayPoint == true)
		{
			m_bNotWayPoint = false;
		}
	}

	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (m_bRandomGoal == true)
	{
		//位置情報を取得
		m_pWayPointPos = &m_pWayPoint->ReturnPointMove();
		//移動可能なマスは何マスあるか
		int nCntWP = m_pWayPoint->CntWayPoint();
		//ランダムで決める
		int nRand = 0;

		if (nCntWP != 0)
		{
			nRand = rand() % nCntWP;
		}

		m_pWayPoint->ReturnPointMove();
		nNextPoint = m_pWayPoint->GetNumTargetPoint(nRand);
		nNowWp = m_pWayPoint->GetNowWP();

		if (m_pWayPointPos[nRand] != NULL)
		{
			//m_MarkWayPoint = m_pWayPointPos[nRand];
			m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
			m_bRandomGoal = false;
		}
	}

	if (m_bNotWayPoint == true)
	{
		m_nTimerMove++;

		if (m_nTimerMove >= 30)
		{
			m_nTimerMove = 0;
			m_bRandomGoal = true;
		}
	}

	// 目的の角度
	float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
	// 差分
	float fDiffAngle = fDestAngle - rot.y;
	DiffAngle(fDiffAngle);
	//移動
	move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
	move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;

#ifdef _DEBUG
	CDebugProc::Print("cfcfcf", "目標のマスの位置 : X ", m_MarkWayPoint.x, " Y ", m_MarkWayPoint.y, " Z ", m_MarkWayPoint.z);
#endif
}

//=============================================================================
//最短ルート処理
//=============================================================================
void C3DCharactor::WayPointRoute_CPU(void)
{
#if 1
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	D3DXVECTOR3 MarkPos;	//一番近い目標位置
	float	fMinCircle = 100000;
	int nRandPos = 0;
	int nNextPoint = 0;
	int nNowWp = 0;

	if (m_bGoal == true && /*m_bNearWard == false &&*/ m_bSearch == false)
	{
		//位置情報を取得
		m_pWayPointPos = &m_pWayPoint->ReturnPointMove();
		//移動可能なマスは何マスあるか
		int nCntWP = m_pWayPoint->CntWayPoint();
		//どのマスに移動するか決める
		for (int nCnt = 0; nCnt < nCntWP; nCnt++)
		{
			// 距離を測る 一番近い文字とウェイポイントを比べてどのポイントに行くか決める
			float fCircle = ((m_MarkWardPos.x - m_pWayPointPos[nCnt].x) * (m_MarkWardPos.x - m_pWayPointPos[nCnt].x)) + ((m_MarkWardPos.z - m_pWayPointPos[nCnt].z) * (m_MarkWardPos.z - m_pWayPointPos[nCnt].z));
			if (fCircle < fMinCircle)
			{
				fMinCircle = fCircle;
				//目標のマス番号を記憶
				m_nTargetWP = nCnt;
				if (m_bNearWard == false)
				{
					m_bSearch = true;
					m_bGoal = false;
				}
			}
		}
	}

	//移動処理
	//目標のマスの番号を渡す
	if (m_bSearch == true)
	{
		m_pWayPoint->ReturnPointMove();
		nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);
		nNowWp = m_pWayPoint->GetNowWP();
		//目標についていたら
		//if (m_pWayPoint->GetWPbBlock(nNowWp) == true)
		//{//自分がブロックマスにいるかの判定
		//	m_CpuThink = THINK_WAYPOINTMOVE;
		//	m_nActionTimer = 60;
		//	m_bGoal = false;
		//}

		if (nNextPoint > MAX_WAYPOINT)
		{
			nNextPoint = 0;
		}
		if (nNextPoint < 0)
		{
			nNextPoint = 0;
			nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);
			nNowWp = m_pWayPoint->GetNowWP();
		}

		if (m_pWayPoint->GetWPbBlock(nNextPoint) == true && m_bNearWard == false)
		{//目標マスがブロック　近くに文字がない
			m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
		}
		else if (m_pWayPoint->GetWPbBlock(nNextPoint) == false && m_bNearWard == false)
		{//目標マスがブロックではない　近くに文字がない
			m_MarkWayPoint = m_pWayPoint->GetNextWayPoint(nNextPoint);
		}
		else if (m_bNearWard == true || m_bBlock == false)
		{//近くに文字がある　ブロックマスではない
			m_MarkWayPoint = m_MarkWardPos;
		}

		m_bSearch = false;
	}

	if (m_bNearWard == true)
	{
		m_pWayPoint->ReturnPointMove();
		nNextPoint = m_pWayPoint->GetNumTargetPoint(m_nTargetWP);
		nNowWp = m_pWayPoint->GetNowWP();

		m_MarkWayPoint = m_MarkWardPos;
	}


	float fCircle = ((Pos.x - m_MarkWayPoint.x) * (Pos.x - m_MarkWayPoint.x)) + ((Pos.z - m_MarkWayPoint.z) * (Pos.z - m_MarkWayPoint.z));

	if (fCircle < 400 && m_bNearWard == false)
	{	//文字の近くのマスまで移動した
		m_bNearWard = true;
		m_bGoal = true;
		m_nTimerMove = 0;
	}
	else if (fCircle < 100 && m_bNearWard == true)
	{
		m_bNearWard = false;
		m_nTimerMove = 0;
	}
	else if (m_fOldCircle == fCircle)
	{
		m_nTimerMove++;

		if (m_nTimerMove >= 10)
		{
			m_nTimerMove = 0;
			m_bNotWayPoint = true;
			WayPointMove_CPU();
		}
	}
	else
	{
		//m_nTimerMove++;

		//if (m_nTimerMove >= 240)
		//{
		//	m_nTimerMove = 0;
		//	m_bNotWayPoint = true;
		//	WayPointMove_CPU();
		//}
	}



	// 目的の角度
	float fDestAngle = atan2f((m_MarkWayPoint.x - sinf(rot.y)) - Pos.x, (m_MarkWayPoint.z - cosf(rot.y)) - Pos.z);
	// 差分
	float fDiffAngle = fDestAngle - rot.y;
	DiffAngle(fDiffAngle);
	//移動
	move.x += sinf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;
	move.z += cosf(atan2f(m_MarkWayPoint.x - Pos.x, m_MarkWayPoint.z - Pos.z)) * speed;

	//距離を記憶
	m_fOldCircle = fCircle;

#endif
}

//=============================================================================
//後退移動処理
//=============================================================================
void C3DCharactor::WayPointBack_CPU(void)
{
	D3DXVECTOR3& Pos = CCharaBase::GetPosition();
	D3DXVECTOR3& move = CCharaBase::GetMove();
	D3DXVECTOR3& rot = CCharaBase::GetRotation();
	D3DXVECTOR3& spin = CCharaBase::GetSpin();
	float		 speed = CCharaBase::GetSpeed();

	move.x += sinf(rot.y + (D3DX_PI * 1.0f)) * speed;
	move.z += cosf(rot.y + (D3DX_PI * 1.0f)) * speed;

}


//=============================================================================
// ステップ処理
//=============================================================================
void C3DCharactor::StepMove(D3DXVECTOR3& move, float& fRot)
{
	move.x += sinf(fRot) * GetStep();
	move.z += cosf(fRot) * GetStep();

	GetThisCharactor()->SetMotion(CPlayer::MOTION_LOWER_STEP, CPlayer::LOWER_BODY, CPlayer::STATE_NORMAL);
	GetThisCharactor()->SetMotion(CPlayer::MOTION_UPPER_STEP, CPlayer::UPPER_BODY, CPlayer::STATE_NORMAL);
	m_nCntStepCoolTime = 30;
	GetThisCharactor()->SetTransTime(5);
}