//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "charactor.h"
#include "manager.h"
#include "word_manager.h"
#include "object.h"
#include "point.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"
#include "sceneX.h"
#include "time.h"
#include "debugProc.h"
#include "bullet.h"
#include "explosion.h"
#include "CameraManager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_LOCKON_LENGTH (300.0f)								//ロックオンできる最遠距離
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 40.0f, 5.0f))			//キャラクターの当たり判定
#define LOCKON_FUTURE_ROTATE (20.0f)								//ロックオンの弾角度決定時に敵の移動速度に掛ける定数

#define INU_BARANCE_LOADTEXT_UPPER "data/MOTION/motion_dog_up.txt"			//犬(バランス型)の上半身のロードテキスト
#define INU_BARANCE_LOADTEXT_LOWER "data/MOTION/motion_dog_down.txt"		//犬(バランス型)の下半身のロードテキスト

#define KUMA_POWER_LOADTEXT_UPPER "data/MOTION/motion_bea_up.txt"			//熊(パワー型)の上半身のロードテキスト
#define KUMA_POWER_LOADTEXT_LOWER "data/MOTION/motion_bea_down.txt"			//熊(パワー型)の下半身のロードテキスト

#define NECO_SPEED_LOADTEXT_UPPER "data/MOTION/motion_cat_up.txt"			//猫(スピード型)の上半身のロードテキスト
#define NECO_SPEED_LOADTEXT_LOWER "data/MOTION/motion_cat_down.txt"			//猫(スピード型)の下半身のロードテキスト

#define USAGI_REACH_LOADTEXT_UPPER "data/MOTION/motion_rabbit_up.txt"			//猫(スピード型)の上半身のロードテキスト
#define USAGI_REACH_LOADTEXT_LOWER "data/MOTION/motion_rabbit_down.txt"			//猫(スピード型)の下半身のロードテキスト

#define STEALTH_TIMER		(120)

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPlayer::PlayerLoadState CPlayer::m_PlayerLoadState[CPlayer::TYPE_MAX][BODY_MAX];		//ロード情報格納用

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_bLand = false;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pWordManager = NULL;
	m_nCntTransTime = 0;
	m_bAssist = true;
	m_bStealth = true;		//ステルス状態になれるかどうか
	m_nStealthTimer = 0;
	m_BulletRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bMachineGun = false;
	m_MachineGunPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMachineGunTime = 0;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{	//他プレイヤーから見えているかどうか
		m_bVision[nCnt] = true;
	}

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		m_nCntKey[nCntBody] = 0;
		m_nCntFlame[nCntBody] = 0;
		m_motion[nCntBody] =  0;
		m_OldMotion[nCntBody] = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			m_pPlayerParts[nCntParts][nCntBody] = NULL;
		}
	}
}
CPlayer::~CPlayer()
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPlayer* CPlayer::Create(void)
{
	CPlayer* pPlayer = NULL;

	pPlayer = new CPlayer;

	if (pPlayer != NULL)
	{
		pPlayer->Init();
	}

	return pPlayer;
}
//=============================================================================
// 設定処理
//=============================================================================
void CPlayer::Set(D3DXVECTOR3 pos, CCharaBase::CHARACTOR_MOVE_TYPE MoveType, int nPlayerID,PLAYER_TYPE PlayerType, D3DXVECTOR3 rot)
{
	//キャラ情報クラス生成
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot, MoveType,this);
		}
	}

	//キャラのID設定
	m_nID = (nPlayerID % 4);//範囲外の数字が入ったらそれを0～3までの数字にする
	m_PlayerType = PlayerType;

	// 文字管理クラス生成
	if (m_pWordManager == NULL)
	{
		ObjCreate(m_pWordManager);
		m_pWordManager->SetID(m_nID);
	}


	//キャラごとに読み込むファイルを分ける(ファイルができるまでは分けない)
	switch (PlayerType)
	{
	case TYPE_BARANCE:
		ModelLoad(INU_BARANCE_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(INU_BARANCE_LOADTEXT_LOWER, PlayerType,LOWER_BODY);
		break;
	case TYPE_POWER:
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	case TYPE_SPEED:
		ModelLoad(NECO_SPEED_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(NECO_SPEED_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	case TYPE_REACH:
		ModelLoad(USAGI_REACH_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		ModelLoad(USAGI_REACH_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		break;
	}

	//上半身と下半身を連結
	if (m_pPlayerParts[0][0] != NULL &&
		m_pPlayerParts[0][1] != NULL)
	{//上半身の親モデルと下半身の親モデルの両方が存在していれば
		m_pPlayerParts[0][UPPER_BODY]->SetParent(m_pPlayerParts[0][LOWER_BODY]->GetMatrix());	//上半身の親が下半身
	}

	SetMotion(MOTION_LOWER_NEUTRAL,LOWER_BODY);
	SetMotion(MOTION_UPPER_NEUTRAL, UPPER_BODY);

	//描画用モデル生成
	//m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//変数初期化
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	m_nCntTransTime = 0;
	m_pLockOnCharactor = NULL;
	//コマンドセット
	CCommand::RegistCommand("PLAYER_BULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_RELEASE, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_BULLET", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_RELEASE, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("PLAYER_SELF_AIM", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_HOLD, CInputXPad::XPAD_RIGHT_SHOULDER);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//キャラ情報クラス削除
	ObjRelease(m_pCharactorMove);

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			ObjRelease(m_pPlayerParts[nCntParts][nCntBody]);
			m_pPlayerParts[nCntParts][nCntBody] = NULL;
		}
	}

	// 文字管理クラスの削除
	if (m_pWordManager != NULL)
	{
		ObjRelease(m_pWordManager);
	}
	//プレイヤー自体の削除
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	D3DXVECTOR3 testpos;
	D3DXVECTOR3 testmove;
	CCameraManager* pCameraManager = CManager::GetCameraManager();

	CPlayer *pPlayer[MAX_PLAYER];
	// プレイヤーを取得
	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// プレイヤーを取得
	}


	if (m_pCharactorMove != NULL &&
		(CManager::GetMode() == CManager::MODE_GAME ||CManager::GetMode() == CManager::MODE_TUTORIAL))
	{
		// 前のフレームの位置代入
		m_posOld = m_pCharactorMove->GetPosition();
		//移動、回転の更新
		m_pCharactorMove->Update();
		//弾との当たり判定
		CollisionDamageObj();

		// モデルとの当たり判定
		if ((CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON)) == true)
		{
			CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		}
		testpos = m_pCharactorMove->GetPosition();
		testmove = m_pCharactorMove->GetMove();

		D3DXVECTOR3 testposFRONT = D3DXVECTOR3(sinf(m_pCharactorMove->GetRotation().y) * 10,
			sinf(m_pCharactorMove->GetRotation().x) * 10,
			cosf(m_pCharactorMove->GetRotation().y) * 10);
		testpos += testposFRONT;
		//前にObjectがあるかどうか
		CollisonObject(&D3DXVECTOR3(testpos.x, testpos.y, testpos.z), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &testmove, PLAYER_COLLISON);



		//弾打ち(プレイヤー)
		if (m_pCharactorMove->GetMoveType() == C3DCharactor::MOVETYPE_PLAYER_INPUT && m_pCharactorMove->m_bWait == false)
		{
			//セット
			CCamera* pCam = pCameraManager->GetCamera(m_ChildCameraName);
			static D3DXVECTOR3 BulletRot;
			D3DXVECTOR3 BulletPos(GetBulletMuzzle());
			D3DXVECTOR3 LockOnObjRot, LockOnObjPos, LockOnMove;

			// 弾の生成
			if (CCommand::GetCommand("PLAYER_BULLET", m_nID) && CGame::GetbStageSet() == false && m_bMachineGun == false)
			{
				C3DCharactor* pChara = NULL;
				int nNear = GetNearPlayer();
				if (nNear != -1)
				{//近いプレイヤーがいればその方向に弾を打つ
					pChara = (C3DCharactor*)CManager::GetPlayer(nNear)->GetCharaMover();
				}
				if (m_bAssist == true)
				{//オートエイムモードなら弾角度を敵の方向に合わせる
					if (pChara != NULL)
					{//近いプレイヤーがいればその方向に弾を打つ
						LockOnObjPos = pChara->GetPosition();
						LockOnObjRot = pChara->GetRotation();
						BulletRot.y = atan2f((LockOnObjPos.x - BulletPos.x), (LockOnObjPos.z - BulletPos.z));
						CUtilityMath::RotateNormarizePI(&BulletRot.y);
					}
					else
					{//近いプレイヤーがいなければプレイヤーの向きに打つ
						BulletRot.y = m_pCharactorMove->GetRotation().y;
					}
					//発射方向保持
					m_BulletRot.y = BulletRot.y;
				}

				if (m_pWordManager->GetBulletFlag() == true)
				{	//可視化
					m_bStealth = false;
					if (m_PlayerType == TYPE_REACH)
					{
						//マシンガン発射時間初期化
						m_nMachineGunTime = 0;
						m_bMachineGun = true;
					}
				}

				if (m_PlayerType != TYPE_REACH)
				{	//ウサギ以外
					m_pWordManager->BulletCreate(m_nID, BulletPos, m_BulletRot, m_PlayerType,
						(m_PlayerType == TYPE_SPEED) ? pChara : NULL);
				}
			}

			if (CCommand::GetCommand("PLAYER_SELF_AIM", m_nID))
			{

				if (CManager::GetXInput(m_nID) != NULL)
				{//スティック角を取得して発射角とする
					BulletRot.y = CManager::GetXInput(m_nID)->GetStickRot(false, m_pCharactorMove->GetRotation().y);
					//発射方向保持
					m_BulletRot.y = BulletRot.y;
				}
				m_bAssist = false;//セルフエイムモードに設定
			}
			else
			{
				BulletRot.y = m_pCharactorMove->GetRotation().y;
				m_bAssist = true;
			}

			//マシンガン発射
			if (m_bMachineGun == true)
			{
				m_nMachineGunTime++;
				if (m_nMachineGunTime % 10 == 0)
				{//10フレームに一回弾発射
					m_MachineGunPos.x = (float)((rand() % 16) - (rand() % 16));
					m_MachineGunPos.z = (float)((rand() % 16) - (rand() % 16));
					m_pWordManager->BulletCreate(m_nID, BulletPos + m_MachineGunPos, m_BulletRot, m_PlayerType,NULL);
				}
				else if (m_nMachineGunTime > 60)
				{//6回発射したら弾情報を削除
					m_bMachineGun = false;
					m_pWordManager->Reset();
				}
				else if (m_pWordManager->Getm_nStock(0) == 99)
				{//ゴミモデル用の発射
					m_pWordManager->BulletCreate(m_nID, BulletPos + m_MachineGunPos, m_BulletRot, m_PlayerType, NULL);
					m_bMachineGun = false;
					m_pWordManager->Reset();
				}
			}


			m_pCharactorMove->GetRotation().y = BulletRot.y;
			m_pCharactorMove->GetSpin().y = 0.0f;

			CDebugProc::Print("cfcfcf","BulletRot = X:",BulletRot.x,"| Y:",BulletRot.y,"| Z:",BulletRot.z);
		}

		//弾発射時に半透明
		if(m_bStealth == false)
		{
			m_nStealthTimer++;
			if (m_nStealthTimer > STEALTH_TIMER)
			{
				m_bStealth = true;
				m_nStealthTimer = 0;
			}
			for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
			{
				if (pPlayer[nCntPlayer] != NULL && nCntPlayer != GetID())
				{	//他プレイヤーに見えている
					pPlayer[nCntPlayer]->SetVision(GetID(), true);
				}
			}
		}


		//文字管理クラスの更新
		if (m_pWordManager != NULL)
		{
			if (m_pCharactorMove != NULL && m_pCharactorMove->GetMoveType() == CCharaBase::MOVETYPE_PLAYER_INPUT)
			{
				m_pWordManager->SearchWord();
			}
			m_pWordManager->Update();
		}

	}
	else
	{
		// 前のフレームの位置代入
		m_posOld = m_pCharactorMove->GetPosition();
		//移動、回転の更新
		m_pCharactorMove->Update();
		// モデルとの当たり判定
	//	if ((CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON)) == true)
		{
			CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		}
	}

	//無敵時間のカウントダウン
	if (m_nCntTransTime > 0)
	{
		m_nCntTransTime--;
	}
	else
	{
		m_nCntTransTime = -1;
		for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
		{
			for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
			{
				if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
				{
					m_pPlayerParts[nCntParts][nCntBody]->SetDrawFlag(true);
				}
			}
		}
	}

	MotionUpdate(LOWER_BODY);
	MotionUpdate(UPPER_BODY);

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				if (m_nCntTransTime % 2 == 0)
				{//ダメージ時の点滅処理
					m_pPlayerParts[nCntParts][nCntBody]->SetDrawFlag(!m_pPlayerParts[nCntParts][nCntBody]->GetDrawFlag());
				}

				m_pPlayerParts[nCntParts][nCntBody]->Update();
			}
		}
	}
#ifdef _DEBUG
	testpos = m_pCharactorMove->GetPosition();
	testmove = m_pCharactorMove->GetMove();

	CDebugProc::Print("cfcfcf", "PLAYER.Pos :", testpos.x, " ", testpos.y, " ", testpos.z);
	CDebugProc::Print("cfcfcf", "PLAYER.Move :", testmove.x, " ", testmove.y, " ", testmove.z);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->Draw();
			}
		}
	}

	if (m_pPlayerParts[0][0] != NULL)
	{
		CDebugProc::Print("cf","ALPHA = ", m_pPlayerParts[0][0]->GetAlpha());
	}
}
//=============================================================================
// モーション更新処理
//=============================================================================
void CPlayer::MotionUpdate(BODY body)
{
	KeyProperty pKey, pKeyNext;

	float fFlameMotion;
	int nFutureKey;
	D3DXVECTOR3 aKeyPos[PLAYER_MODELNUM];
	D3DXVECTOR3 aKeyRot[PLAYER_MODELNUM];
	m_nCntFlame[body]++;

	switch (m_Mstate[body])
	{
	case STATE_NORMAL:
		nFutureKey = (m_nCntKey[body] + 1) % (m_propMotion[m_motion[body]][body].nKeyNum);
		pKey = m_propMotion[m_motion[body]][body].key[m_nCntKey[body]];
		pKeyNext = m_propMotion[m_motion[body]][body].key[nFutureKey];

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				//現在の角度を取得
				D3DXVECTOR3 rot = m_pPlayerParts[nCntParts][body]->GetRotation();

				//現在のキーから次のキーへの再生フレーム数におけるモーションカウンターの相対値を算出
				fFlameMotion = (float)(m_nCntFlame[body] + 1) / ((float)pKey.nFrame);

				//現在のキーから次のキーへの角度の差分を算出
				aKeyRot[nCntParts].x = (pKeyNext.Rot[nCntParts].x - pKey.Rot[nCntParts].x);
				aKeyRot[nCntParts].y = (pKeyNext.Rot[nCntParts].y - pKey.Rot[nCntParts].y);
				aKeyRot[nCntParts].z = (pKeyNext.Rot[nCntParts].z - pKey.Rot[nCntParts].z);

				//求めた差分を現在のキーに係数を掛けながら足す
				rot = pKey.Rot[nCntParts] + (aKeyRot[nCntParts] * fFlameMotion);

				if (nCntParts == 0 && body == LOWER_BODY)
				{
					rot.y = 3.14f;
				}

				//角度の正規化
				CUtilityMath::RotateNormarizePI(&rot.x);
				CUtilityMath::RotateNormarizePI(&rot.y);
				CUtilityMath::RotateNormarizePI(&rot.z);

				m_pPlayerParts[nCntParts][body]->SetRotation(rot);
			}
		}

		if (m_nCntFlame[body] == m_propMotion[m_motion[body]][body].key[m_nCntKey[body]].nFrame)
		{//既定のフレームが経過したら

			m_nCntFlame[body] = 0;
			m_nCntKey[body]++;	//キーを加算
			if (m_nCntKey[body] >= m_propMotion[m_motion[body]][body].nKeyNum)
			{//キーが既定の数値に達したら
				m_nCntKey[body] = 0;
				if (m_propMotion[m_motion[body]][body].nLoop == 0)
				{
					if (m_pWordManager->GetBulletFlag())
					{
						SetMotion(MOTION_UPPER_SETUP_NEUTRAL, UPPER_BODY);
					}
					else
					{
						SetMotion(MOTION_UPPER_NEUTRAL, UPPER_BODY);
					}

					SetMotion(MOTION_LOWER_NEUTRAL, LOWER_BODY);
				}
			}
		}
		break;
	case STATE_BLEND:
		if (m_motion[body] == 0)
		{
			pKey();
		}
		else
		{
			pKey = m_propMotion[m_OldMotion[body]][body].key[m_nCntKey[body]];
		}
		pKeyNext = m_propMotion[m_motion[body]][body].key[0];

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				//現在の角度を取得
				D3DXVECTOR3 rot = m_pPlayerParts[nCntParts][body]->GetRotation();

				//ブレンド係数を算出
				fFlameMotion = (float)(m_nCntBlendMotion[body] + 1) / MOTION_BLENDTIME;

				//現在のキーから次のキーへの角度の差分を算出
				aKeyRot[nCntParts].x = (pKeyNext.Rot[nCntParts].x - pKey.Rot[nCntParts].x);
				aKeyRot[nCntParts].y = (pKeyNext.Rot[nCntParts].y - pKey.Rot[nCntParts].y);
				aKeyRot[nCntParts].z = (pKeyNext.Rot[nCntParts].z - pKey.Rot[nCntParts].z);

				//求めた差分を現在のキーに係数を掛けながら足す
				rot = pKey.Rot[nCntParts] + (aKeyRot[nCntParts] * fFlameMotion);

				if (nCntParts == 0 && body == LOWER_BODY)
				{
					rot.y = 3.14f;
				}

				//角度の正規化
				CUtilityMath::RotateNormarizePI(&rot.x);
				CUtilityMath::RotateNormarizePI(&rot.y);
				CUtilityMath::RotateNormarizePI(&rot.z);

				m_pPlayerParts[nCntParts][body]->SetRotation(rot);
			}
		}

		m_nCntBlendMotion[body]++;
		if (m_nCntBlendMotion[body] >= MOTION_BLENDTIME)
		{//既定のフレームが経過したら
			m_nCntBlendMotion[body] = 0;
			m_nCntKey[body] = 0;
			m_Mstate[body] = STATE_NORMAL;
		}
		break;
	}
	CDebugProc::Print("cn","MOTION = ",(int)m_motion[body]);
}

//=============================================================================
// モーション設定処理
//=============================================================================
void	CPlayer::SetMotion(int motion, BODY body,MOTION_STATE state)
{
	if (motion != m_motion[body])
	{//現在入っているモーションと違うものであれば
		//一つ前のモーションを保存する
		m_OldMotion[body] = m_motion[body];

		//その他変数の初期化
		m_nCntBlendMotion[body] = 0;
		m_nCntFlame[body] = 0;
		if (state != STATE_BLEND)
		{
			if (m_Mstate[body] == STATE_BLEND)
			{//一つ前もブレンドなら
				for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
				{
					if (m_pPlayerParts[nCntParts][body] != NULL)
					{
						//ブレンド中に次のモーションに入った時
						m_pPlayerParts[nCntParts][body]->SetRotation(m_propMotion[m_OldMotion[body]][body].key[0].Rot[nCntParts]);
					}
				}
			}
			m_nCntKey[body] = 0;
		}	//ブレンドする時は初期化しない

		//引数代入
		m_motion[body] = motion;
		m_Mstate[body] = state;

	}
}

//=============================================================================
// キャラの透明度設定処理
//=============================================================================
void CPlayer::SetPartsAlpha(float fAlpha)
{
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->SetAlpha(fAlpha);
			}
		}
	}
}

//=============================================================================
// 当たり判定(弾)処理
//=============================================================================
bool CPlayer::CollisionDamageObj(void)
{
	bool bHit = false;
	CScene *pScene = NULL;
	CSound *pSound = CManager::GetSound();		//	音の取得

	D3DXVECTOR3 PlayerPos = m_pCharactorMove->GetPosition();
	D3DXVECTOR3 ObjPos,ObjRot;
	float fObjSize = 0.0f;

	/*弾との当たり判定*/
	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(BULLET_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が弾と同じオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_BULLET)
			{// オブジェクトの種類を確かめる
				C3DBullet *pBullet = ((C3DBullet*)pScene);		// CBulletBaseへキャスト(型の変更)
				ObjPos = pBullet->GetPosition();
				ObjRot = pBullet->GetRotation();

				float X = (ObjPos.x - PlayerPos.x) * (ObjPos.x - PlayerPos.x);
				float Y = (ObjPos.y - PlayerPos.y) * (ObjPos.y - PlayerPos.y);
				float Z = (ObjPos.z - PlayerPos.z) * (ObjPos.z - PlayerPos.z);

				if(sqrtf(X + Y + Z) < BULLET_COLLISION_SIZE &&
					m_nID != pBullet->GetID())
				{//球の判定

					/*得点加算 (当てたキャラのIDはpBulletのGetIDで取得できる)*/
					if (pBullet->GetType() == C3DBullet::TYPE_MODEL)
					{	// モデルの場合はポイント加算
						CPoint *pPoint = NULL;
						if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(pBullet->GetID()); }
						if (CManager::GetMode() == CManager::MODE_TUTORIAL) { pPoint = CTutorial::GetPoint(pBullet->GetID()); }

						CModelBullet *pModelBullet = ((CModelBullet*)pBullet);


						int nPoint = 0;
						if (pModelBullet->GetType() == CModelBullet::TYPE_NORMAL) { nPoint = 1; }
						else if (pModelBullet->GetType() == CModelBullet::TYPE_MACHINEGUN) { nPoint = 1; }
						else if (pModelBullet->GetType() == CModelBullet::TYPE_SHOTGUN
							||pModelBullet->GetType() == CModelBullet::TYPE_SHOTGUN_MEDIUM
							||pModelBullet->GetType() == CModelBullet::TYPE_SHOTGUN_SLOW) { nPoint = 1; }
						else if (pModelBullet->GetType() != CModelBullet::TYPE_NORMAL) { nPoint = 3; }
						//フィーバータイム時に得点２倍
						if (CTime::GetFeverFlag() == true)
						{
							nPoint *= 2;
						}

						if (pPoint != NULL) { pPoint->AddPoint(nPoint); }
						pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTUP, 3.0f);
						pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTUP);

						C3DBullet *pBullet = ((C3DBullet*)pModelBullet);		// CBulletBaseへキャスト(型の変更)
					}

					//吹き飛ばし
					DamageReaction(pBullet->GetKnockBackPower(),ObjRot);

					//弾削除
					pBullet->Uninit();

					//可視化
					m_bStealth = false;

					return true;
				}
			}
		}
		pScene = pSceneNext;
	}

	/*爆発*/
	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(EXPLOSION_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が弾と同じオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_EXPLOSION)
			{// オブジェクトの種類を確かめる
				CExplosion3D* pExp = (CExplosion3D*)pScene;
				ObjPos = pExp->GetPosition();
				fObjSize = pExp->GetSize();

				float fRot = atan2f((ObjPos.x - PlayerPos.x),(ObjPos.z - PlayerPos.z)) + D3DX_PI;
				float X = (ObjPos.x - PlayerPos.x) * (ObjPos.x - PlayerPos.x);
				float Y = (ObjPos.y - PlayerPos.y) * (ObjPos.y - PlayerPos.y);
				float Z = (ObjPos.z - PlayerPos.z) * (ObjPos.z - PlayerPos.z);

				CUtilityMath::RotateNormarizePI(&fRot);
				if (sqrtf(X + Y + Z) < fObjSize)
				{
					//吹き飛ばし
					DamageReaction(20.0f, D3DXVECTOR3(0.0f,fRot,0.0f));
					return true;
				}

			}
		}
		pScene = pSceneNext;
	}

	return false;
}

//=============================================================================
// ダメージの反応処理
//=============================================================================
void CPlayer::DamageReaction(float fDamageValue, D3DXVECTOR3 HitRotation)
{
	D3DXVECTOR3& move = m_pCharactorMove->GetMove();

	//
	move.x += sinf(HitRotation.y) * fDamageValue * 2.0f;
	move.z += cosf(HitRotation.y) * fDamageValue * 2.0f;

	move.y += fDamageValue;
	m_nCntTransTime = 30;
}
//=============================================================================
// 当たり判定(オブジェクト)処理
//=============================================================================
bool CPlayer::CollisonObject(D3DXVECTOR3 *pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * move, D3DXVECTOR3 radius)
{
	bool bHit = false;
	CScene *pScene = NULL;
	CPlayer *pPlayer[MAX_PLAYER];
	int nCntBush = 0;

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(SCENEX_PRIORITY);

	for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetPlayer(nCntPlayer);			// プレイヤーを取得
	}

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
		{// 死亡フラグが立っていないもの
			// オブジェクトの種類を確かめる
			CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneXへキャスト(型の変更)
			if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
			{
				m_bLand = pSceneX->Collision(pos, posOld, move, radius, m_nID);

				CObject *pSceneObj = ((CObject*)pSceneX);		// CObjectへキャスト(型の変更)
				if (m_bLand == true)
				{// モデルに当たる
					bHit = true;

					if (pSceneObj->GetRealTimeType() == CObject::REALTIME_NOTMOVE)
					{
						if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
							pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
						{	// ベルトコンベアの判定
							pSceneObj->BeltConveyor(move, pSceneObj->GetSwitch());
						}
						else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING ||
							pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
						{	// ノックバックの判定
							pSceneObj->KnockBack(move, m_nID);
						}
						else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_SWITCH)
						{//	スイッチ
							pSceneObj->SwitchBeltConveyor(m_bLand);
						}

					}
					else if (pSceneObj->GetRealTimeType() == CObject::REALTIME_INITPOS)
					{
						pSceneObj->AffectedLanding(move, m_nID);
					}

					if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_BUSH)
					{	//草むらにいるとき透明にする
						PlayerAlpha(0.5f);
						//今いる草むらの番号を取得
						m_nObjNumber = pSceneObj->GetSceneXNum();

						for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
						{
							if (pPlayer[nCntPlayer] != NULL && nCntPlayer != GetID())
							{//他プレイヤーに見えていない
								int ntest = GetID();
								if (m_nObjNumber != pPlayer[nCntPlayer]->GetLandObjNumber())
								{	//同じ草むらにいないとき
									pPlayer[nCntPlayer]->SetVision(GetID(), false);
								}
							}
						}
						nCntBush++;
					}
					else if (pSceneObj->GetCollsionType() == CSceneX::COLLISIONTYPE_BOX)
					{
					}
					break;
				}
				else
				{
					if (nCntBush == 0)
					{//草むらに入っていないとき
						//透明を戻す
						PlayerAlpha(1.0f);

						for (int nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
						{
							if (pPlayer[nCntPlayer] != NULL && nCntPlayer != GetID())
							{	//他プレイヤーに見えている
								int nte = GetID();
								pPlayer[nCntPlayer]->SetVision(GetID(), true);
							}
						}
						//m_bStealth = true;
						bHit = false;
						m_nObjNumber = 0;
						//透明な草を戻す
						//CSceneX::SetTranslucentBush(0);
					}
				}
			}
		}
		// 次のシーンに進める
		pScene = pSceneNext;
	}

	if (nCntBush == 0)
	{//草むらに入っていないとき
	 //透明な草を戻す
	 CSceneX::SetTranslucentBush(GetID(),0);
	}

	return bHit;
}
//=============================================================================
// 近いプレイヤーを取得する処理
//=============================================================================
int		CPlayer::GetNearPlayer(void)
{
	D3DXVECTOR3 PlayerPos[4] = {};
	D3DXVECTOR3 PlayerRot[4] = {};
	CCharaBase* pChara = NULL;
	CPlayer* pPlayer = NULL;
	int nCntPlayer = 0;
	//値の取得
	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		pChara = NULL;
		pPlayer = NULL;

		pPlayer = CManager::GetPlayer(nCntPlayer);			// プレイヤーを取得

		if (pPlayer != NULL)
		{
			pChara = pPlayer->GetCharaMover();
			if (pChara != NULL)
			{//キャラクラス内にある座標を取得
				PlayerPos[nCntPlayer] = pChara->GetPosition();
				PlayerRot[nCntPlayer] = pChara->GetRotation();	//比較に使うためyの値にπを足す
			}
			else
			{//キャラクラスが消えた場合も巨大な値を入れる
				PlayerPos[nCntPlayer] = D3DXVECTOR3(-99999.9f, -99999.9f, -99999.9f);
				PlayerRot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}
		else
		{	//プレイヤーがいない場合は巨大な値を入れる
			PlayerPos[nCntPlayer] = D3DXVECTOR3(-99999.9f, -99999.9f, -99999.9f);
			PlayerRot[nCntPlayer] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
	}

	//値の比較
	float fNearLength = 99999.9f;
	int nPlayerNum = -1;
	for (nCntPlayer = 0; nCntPlayer < MAX_PLAYER; nCntPlayer++)
	{
		if (nCntPlayer != m_nID)
		{//自分以外と判定を行う

			//距離を取得(-は省く)
			float fLength = fabsf(sqrtf(powf(PlayerPos[m_nID].x - PlayerPos[nCntPlayer].x, 2.0f) +
				powf(PlayerPos[m_nID].y - PlayerPos[nCntPlayer].y, 2.0f) +
				powf(PlayerPos[m_nID].z - PlayerPos[nCntPlayer].z, 2.0f)));

			//角度比較
				if (fLength < fNearLength &&
					fLength < PLAYER_LOCKON_LENGTH)
				{
					nPlayerNum = nCntPlayer;
					fNearLength = fLength;
				}
		}
	}
	return nPlayerNum;
}

//=============================================================================
// 透明度の設定処理
//=============================================================================
void CPlayer::PlayerAlpha(float fAlpha)
{
	for (int nCntBody = 0; nCntBody < BODY_MAX; nCntBody++)
	{
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts][nCntBody] != NULL)
			{
				m_pPlayerParts[nCntParts][nCntBody]->SetAlpha(fAlpha, 300);
			}
		}
	}
}

//=============================================================================
// モデルロード処理
//=============================================================================
HRESULT CPlayer::ModelLoad(LPCSTR pFileName, PLAYER_TYPE type, BODY body, bool bReLoad)
{
	FILE* pFile = NULL;		// ファイルポインタ
	char ReadText[256];		// 読み込んだ文字列を入れておく
	char HeadText[256];		// 比較用
	char DustBox[256];		// 使用しないものを入れておく

	int nCntMotionSetType = 0;					// モーションセットの種類の数
	int nCntMotionType = 1;						// モーションの種類の数
	int nCntKeySet = 0;							// キーセット数
	int nCntKey = 0;							// キー数
	int nCntPartsSet = 0;						// パーツ数
	int nCntFileNameNum = 0;
	int nPartsNum = 0;

		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			ObjRelease(m_pPlayerParts[nCntParts][body]);
			m_pPlayerParts[nCntParts][body] = NULL;
		}
	if (m_PlayerLoadState[type][body].bLoad == false ||
		(m_PlayerLoadState[type][body].bLoad == true && bReLoad == true))
	{//	まだこの情報がロードされていないorされているが再度ロードしたければ
		for (int nCntMotion = 0; nCntMotion < MOTION_UPPER_MAX; nCntMotion++)
		{
			m_PlayerLoadState[type][body].prop[nCntMotion]();
		}

		//ファイルオープン
		pFile = fopen(pFileName, "r");

		if (pFile != NULL)
		{//ファイルが開かれていれば
			while (strcmp(HeadText, "SCRIPT") != 0)
			{// "SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
				fgets(ReadText, sizeof(ReadText), pFile);
				sscanf(ReadText, "%s", &HeadText);
			}
			if (strcmp(HeadText, "SCRIPT") == 0)
			{// "SCRIPT" が読み取れた場合、処理開始
				while (strcmp(HeadText, "END_SCRIPT") != 0)
				{// "END_SCRIPT" が読み込まれるまで繰り返し文字列を読み取る
					fgets(ReadText, sizeof(ReadText), pFile);
					sscanf(ReadText, "%s", &HeadText);

					if (strcmp(HeadText, "\n") == 0)
					{// 文字列の先頭が [\n](改行) の場合処理しない

					}
					else if (strcmp(HeadText, "MODEL_FILENAME") == 0)
					{
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, m_PlayerLoadState[type][body].info[nCntFileNameNum].FileName);
						nCntFileNameNum++;
					}
					else if (strcmp(HeadText, "CHARACTERSET") == 0)
					{//キャラ
						while (strcmp(HeadText, "END_CHARACTERSET") != 0)
						{// "END_CHARACTERSET" が読み取れるまで繰り返し文字列を読み取る
							fgets(ReadText, sizeof(ReadText), pFile);
							sscanf(ReadText, "%s", &HeadText);
							if (strcmp(HeadText, "\n") == 0)
							{// 文字列の先頭が [\n](改行) の場合処理しない

							}
							if (strcmp(HeadText, "NUM_PARTS") == 0)
							{
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].nPartsNum);
							}
							else if (strcmp(HeadText, "PARTSSET") == 0)
							{//PARTSSETを読みとったら
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "\n") == 0)
									{// 文字列の先頭が [\n](改行) の場合処理しない

									}
									else if (strcmp(HeadText, "INDEX") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].info[nCntPartsSet].nIndex);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type][body].info[nCntPartsSet].nParent);
									}
									else if (strcmp(HeadText, "POS") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.x,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.y,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.x,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.y,
											&m_PlayerLoadState[type][body].info[nCntPartsSet].rot.z);
									}
								}
								nCntPartsSet++;

							}
						}
					}
					else if (strcmp(HeadText, "MOTIONSET") == 0)
					{//モーション
						while (strcmp(HeadText, "END_MOTIONSET") != 0)
						{// "END_MOTIONSET" が読み取れるまで繰り返し文字列を読み取る
							fgets(ReadText, sizeof(ReadText), pFile);
							sscanf(ReadText, "%s", &HeadText);

							if (strcmp(HeadText, "\n") == 0)
							{// 文字列の先頭が [\n](改行) の場合処理しない

							}
							else if (strcmp(HeadText, "LOOP") == 0)
							{//ループ
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
									&m_PlayerLoadState[type][body].prop[nCntMotionType].nLoop);
							}
							else if (strcmp(HeadText, "NUM_KEY") == 0)
							{//キー数
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
									&m_PlayerLoadState[type][body].prop[nCntMotionType].nKeyNum);
							}
							else if (strcmp(HeadText, "KEYSET") == 0)
							{
								while (strcmp(HeadText, "END_KEYSET") != 0)
								{// "END_KEYSET" が読み取れるまで繰り返し文字列を読み取る
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);
									if (strcmp(HeadText, "\n") == 0)
									{// 文字列の先頭が [\n](改行) の場合処理しない

									}
									else if (strcmp(HeadText, "FRAME") == 0)
									{//補間フレーム
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox,
											&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].nFrame);
									}
									else if (strcmp(HeadText, "KEY") == 0)
									{//キー情報
										while (strcmp(HeadText, "END_KEY") != 0)
										{// "END_KEY" が読み取れるまで繰り返し文字列を読み取る
											fgets(ReadText, sizeof(ReadText), pFile);
											sscanf(ReadText, "%s", &HeadText);

											if (strcmp(HeadText, "\n") == 0)
											{// 文字列の先頭が [\n](改行) の場合処理しない

											}
											else if (strcmp(HeadText, "POS") == 0)
											{//座標
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].z);
											}
											else if (strcmp(HeadText, "ROT") == 0)
											{//角度
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Rot[nCntKey].z);
											}

										}
										nCntKey++;
									}
								}
								nCntKeySet++;
								nCntKey = 0;
							}
						}
						nCntMotionType++;
						nCntKeySet = 0;
					}
				}
				nCntMotionType = 0;
			}

		}
		fclose(pFile);
		m_PlayerLoadState[type][body].bLoad = true;
	}

	//情報設定
	int nCntParts = 0;
		for (nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
		{

			if (ObjCreate(m_pPlayerParts[nCntParts][body]))
			{//生成されたら

				m_pPlayerParts[nCntParts][body]->Set(m_PlayerLoadState[type][body].info[nCntParts].FileName,
					m_PlayerLoadState[type][body].info[nCntParts].pos,
					m_PlayerLoadState[type][body].info[nCntParts].rot, NULL);

				switch (type)
				{//タイプごとの処理
				case TYPE_BARANCE:
					m_pPlayerParts[nCntParts][body]->BindTexture("INU_UV");
					break;
				case TYPE_POWER:
					m_pPlayerParts[nCntParts][body]->BindTexture("KUMA_UV");
					break;
				case TYPE_SPEED:
					m_pPlayerParts[nCntParts][body]->BindTexture("NECO_UV");
					break;
				case TYPE_REACH:
					m_pPlayerParts[nCntParts][body]->BindTexture("USAGI_UV");
					break;
				}
			}
		}

	//親マトリクスセット
	for (int nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
	{
		int nNum = m_PlayerLoadState[type][body].info[nCntParts].nParent;
		if (nNum != -1)
		{
			m_pPlayerParts[nCntParts][body]->SetParent(m_pPlayerParts[nNum][body]->GetMatrix());
		}
		else
		{
			m_pPlayerParts[nCntParts][body]->SetParent(m_pCharactorMove->GetMatrix());
		}
	}

	//モーション情報を読み込み変数からコピー
	for (int nCntMotion = 0; nCntMotion < (body == LOWER_BODY ? MOTION_LOWER_MAX : MOTION_UPPER_MAX); nCntMotion++)
	{//(body == LOWER_BODY ? MOTION_LOWER_MAX : MOTION_UPPER_MAX) : 上下のモーション数に応じてループ数を変える
		m_propMotion[nCntMotion][body] = m_PlayerLoadState[type][body].prop[nCntMotion];
	}
	return S_OK;
}

//=============================================================================
// モデルロード処理
//=============================================================================
D3DXVECTOR3     CPlayer::GetBulletMuzzle(void)
{
	if (m_pPlayerParts[8][UPPER_BODY] != NULL)
	{
		return m_pPlayerParts[8][UPPER_BODY]->GetWorldPosition();
	}
	else
	{
		if (m_pCharactorMove != NULL)
		{
			return m_pCharactorMove->GetPosition() + D3DXVECTOR3(0.0f,10.0f,0.0f);
		}
	}
	return D3DXVECTOR3(0.0f,0.0f,0.0f);
}