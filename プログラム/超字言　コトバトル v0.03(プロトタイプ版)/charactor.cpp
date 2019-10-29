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
#include "point.h"
#include "word.h"
#include "tutorial.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define MOVE_DEFAULT_SPEED (0.6f)			//デフォルトの移動スピード
#define STEP_DEFAULT_MOVEMENT (10.0f)		//デフォルトのステップ量
#define MOVE_DEFAULT_COEFFICIENT (0.20f)	//デフォルトの移動にかかる係数
#define MOVE_AIR_COEFFICIENT (0.10f);
#define SPIN_DEFAULT_COEFFICIENT (0.50f)	//デフォルトの回転にかかる係数
#define CIRCLE_HOMING	 (3000)				//追尾範囲(上限)
#define CIRCLE_ANGLE	(100)
#define PATROL_FLAME	(60)
#define CAMERA_MOVE_SPEED (0.05f)
#define NEAR_DISTANCE	(100)
#define FIELD_OUTSIDE	(300)

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

	nTestCnt = 0;


	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_bNear[nCnt] = false;
	}
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

	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//if (CCharaBase::GetMoveType() == CCharaBase::MOVETYPE_NPC_AI)
	//{
	//	//CPUが場外行かないように
	//	if (m_bJyougai == false)
	//	{
	//		if (FIELD_OUTSIDE < pos.x || -FIELD_OUTSIDE > pos.x ||
	//			FIELD_OUTSIDE < pos.z || -FIELD_OUTSIDE > pos.z)
	//		{//場外に移動しそうになった時

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
	//		{//場内に移動した
	//			m_bJyougai = true;
	//		}
	//	}
	//}

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
	m_CameraPosR = pos + D3DXVECTOR3(0.0f, 40.0f, 0.0f);
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

	//行動を決める条件文
	if (m_bFront == true)
	{	//壁に当たってる
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
		敵が前にいる時はBACK
		敵が弾を持ってるときは下がりながら左右移動
		敵が見えないときはできるだけ前進
		弾を持っているときは前進していく
		*/
		m_CpuMove = CPU_MOVE_FRONT;
#endif
	}
#if 1

	if ((GetThisCharactor()->GetWordManager()->GetBulletFlag() == true))
	{	//弾を持っているとき
		m_Type = CPU_TYPE_NONE;
		m_CpuThink = THINK_HAVEBULLET;
		m_nActionTimer = 10;
	}
	else
	{	//弾を持っていないとき
		m_CpuThink = THINK_NOTBULLET;
		m_nActionTimer = 10;
	}

	//同じ行動を3回とらない
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
		PickUP_CPU();
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
	move.x += (0.0f - move.x) * MOVE_DEFAULT_COEFFICIENT;
	move.y += (0.0f - move.y) * MOVE_DEFAULT_COEFFICIENT;
	move.z += (0.0f - move.z) * MOVE_DEFAULT_COEFFICIENT;

	//タイマーを減らす
	m_nActionTimer--;
}

void C3DCharactor::DiffAngle(float fDiffAngle)
{
	D3DXVECTOR3& rot = CCharaBase::GetRotation();

	// 差分
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

	D3DXVECTOR3 TargetPos;

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
					if (m_CpuThink != THINK_WATCH)
					{
						// プレイヤーに近づける
						move.x += sinf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;
						move.z += cosf(atan2f(PlayerPos[nCntPlayer].x - Pos.x, PlayerPos[nCntPlayer].z - Pos.z)) * speed;
					}
					float DiffDis = (PlayerPos[nCntPlayer].x + Pos.x) / 2;
					TargetPos = D3DXVECTOR3((PlayerPos[nCntPlayer].x + Pos.x) / 2, (PlayerPos[nCntPlayer].y + Pos.y) / 2, (PlayerPos[nCntPlayer].z + Pos.z) / 2);
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
// CPUの攻撃処理
//=============================================================================
void C3DCharactor::Attack_CPU(void)
{
	//弾の生成	弾を持っているときだけ
	if (GetThisCharactor()->GetWordManager()->GetBulletFlag() == true)
	{
		GetThisCharactor()->GetWordManager()->BulletCreate(GetThisCharactor()->GetID(),GetThisCharactor()->GetPosition());
		m_CpuThink = THINK_NONE;
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
	D3DXVECTOR3 MOKUHYO;	//一番近い目標位置
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

				if (fCircle < 300 * 100)
				{//範囲内に文字があった
					nCntNearWord++;		//加算
					float fNum = (float)pWord->GetWordNum();	// 文字の番号を取得
					for (int nCntAnswer = 0; nCntAnswer < nCntData; nCntAnswer++)
					{	// 候補の数回して 文字番号と合っているかを比較
						if (fAnswerNum[nCntAnswer] == fNum)
						{	// 合っていた場合 位置を取得しbreakする
							m_fCompareRange = fCircle;
							MOKUHYO = pWord->GetPos();
							bWord = true;
							bTango = true;
							break;
						}
					}
					if (bTango == false)
					{//単語が完成しないときは適当に拾う
						//一番近い距離を記憶
						m_fCompareRange = fCircle;
						MOKUHYO = pWord->GetPos();
						bWord = true;
					}
				}
			}
		}
		// 次のシーンに進める
		pScene = pSceneNext;
	}

	//ワードが範囲内にある時移動する
	if (bWord == true)
	{
		// 目的の角度
		float fDestAngle = atan2f((MOKUHYO.x - sinf(rot.y)) - Pos.x, (MOKUHYO.z - cosf(rot.y)) - Pos.z);
		// 差分
		float fDiffAngle = fDestAngle - rot.y;
		DiffAngle(fDiffAngle);
		//移動
		move.x += sinf(atan2f(MOKUHYO.x - Pos.x, MOKUHYO.z - Pos.z)) * speed;
		move.z += cosf(atan2f(MOKUHYO.x - Pos.x, MOKUHYO.z - Pos.z)) * speed;
	}

	if (nCntNearWord == 0)
	{//近くに文字が一つもない
		m_bWordNear = true;
		m_CpuThink = THINK_MOVE;
		m_CpuMove = CPU_MOVE_FRONT;
		m_nActionTimer = 30;
		m_bWordNear = false;
	}

}

//=============================================================================
// 弾を持っているときの処理
//=============================================================================
void C3DCharactor::HaveBullet_CPU(void)
{

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
// ステップ処理
//=============================================================================
void C3DCharactor::StepMove(D3DXVECTOR3& move, float& fRot)
{
	move.x += sinf(fRot) * STEP_DEFAULT_MOVEMENT;
	move.z += cosf(fRot) * STEP_DEFAULT_MOVEMENT;

	m_nCntStepCoolTime = 30;
	GetThisCharactor()->SetTransTime(5);
}