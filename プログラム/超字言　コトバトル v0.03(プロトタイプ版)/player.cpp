//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "manager.h"
#include "word_manager.h"
#include "object.h"
#include "point.h"
#include "game.h"
#include "tutorial.h"

#include "sceneX.h"

#include "debugProc.h"
#include "bullet.h"
#include "CameraManager.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_LOCKON_LENGTH (300.0f)								//ロックオンできる最遠距離
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 40.0f, 5.0f))			//キャラクターの当たり判定

#define KUMA_POWER_LOADTEXT			"data/MOTION/motion_bea.txt"			//熊(パワー型)のロードテキスト

#define KUMA_POWER_LOADTEXT_LOWER "data/MOTION/motion_bea_down.txt"			//熊(パワー型)の下半身のロードテキスト
#define KUMA_POWER_LOADTEXT_UPPER "data/MOTION/motion_bea_up.txt"			//熊(パワー型)の上半身のロードテキスト

#define MOTION_NUM ((MOTION_LOWER::MOTION_LOWER_MAX > MOTION_UPPER::MOTION_UPPER_MAX) ? MOTION_LOWER::MOTION_LOWER_MAX : MOTION_UPPER::MOTION_UPPER_MAX)
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
	m_pPlayerNum = NULL;
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

	// 文字管理クラス生成
	if (m_pWordManager == NULL)
	{
		ObjCreate(m_pWordManager);
		m_pWordManager->SetID(m_nID);
	}

	if (m_pPlayerNum == NULL)
	{
		int nID = m_nID;
		if (MoveType == CCharaBase::MOVETYPE_NPC_AI) { nID = MAX_PLAYER; }	// COM表示にする
		m_pPlayerNum = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), 7.0f, 3.0f, "プレイ人数");
		m_pPlayerNum->SetTexture(D3DXVECTOR2(0.0f, nID * 0.2f), D3DXVECTOR2(1.0f, (nID * 0.2f) + 0.2f));
		m_pPlayerNum->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


	//キャラごとに読み込むファイルを分ける(ファイルができるまでは分けない)
	switch (PlayerType)
	{
	case TYPE_NORMAL:
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType,LOWER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		break;
	case TYPE_POWER:
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		break;
	case TYPE_SPEED:
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
		break;
	case TYPE_REACH:
		ModelLoad(KUMA_POWER_LOADTEXT_LOWER, PlayerType, LOWER_BODY);
		ModelLoad(KUMA_POWER_LOADTEXT_UPPER, PlayerType, UPPER_BODY);
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
	//m_pPlayerModel->SetObjType(CScene::OBJTYPE_PLAYER);
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
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_RELEASE, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_RELEASE, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("PLAYER_HOMINGSET", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_HOLD, CInputXPad::XPAD_RIGHT_SHOULDER);
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
	// プレイヤー番号破棄
	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Uninit();
		m_pPlayerNum = NULL;
	}


	// 文字管理クラスの削除
	ObjRelease(m_pWordManager);

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

	if (m_pCharactorMove != NULL)
	{
		// 前のフレームの位置代入
		m_posOld = m_pCharactorMove->GetPosition();

		//移動、回転の更新
		m_pCharactorMove->Update();
		if (m_nCntTransTime <= 0)
		{
			//弾との当たり判定
			CollisionBullet();
		}

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

	}

	//セット
	CCamera* pCam = pCameraManager->GetCamera(m_ChildCameraName);
	D3DXVECTOR3 BulletRot = m_pCharactorMove->GetRotation();

	// 弾の生成
	if (CCommand::GetCommand("PLAYER_SHOTBULLET", m_nID))
	{
		if (m_pWordManager != NULL)
		{//文字管理クラスに弾の生成を委託する
			if (pCam != NULL)
			{
				BulletRot = D3DXVECTOR3(-pCam->GetRotation().x, pCam->GetRotation().y, 0.0f);
			}

			CUtilityMath::RotateNormarizePI(BulletRot.x);
			CUtilityMath::RotateNormarizePI(BulletRot.y);

			m_pWordManager->BulletCreate(m_nID, m_pCharactorMove->GetPosition() + D3DXVECTOR3(0.0f, 10.0f, 0.0f), BulletRot);
			if (m_pWordManager->GetCntNum() == 0)
			{
				m_bSetupBullet = false;
			}
		}
	}

	if (CCommand::GetCommand("PLAYER_HOMINGSET", m_nID))
	{
		//テスト
		int nPlayer = GetNearPlayer();
		if (nPlayer != -1)
		{
			m_pLockOnCharactor = (C3DCharactor*)(CGame::GetPlayer(nPlayer)->GetCharaMover());

			if (pCam != NULL)
			{
				pCam->SetLockOnChara(m_pLockOnCharactor);
			}
		}
		else
		{
			m_pLockOnCharactor = NULL;
			if (pCam != NULL)
			{
				pCam->SetLockOnChara(NULL);
			}
		}
	}
	else
	{
		m_pLockOnCharactor = NULL;
		if (pCam != NULL)
		{
			pCam->SetLockOnChara(NULL);
		}
	}

	//文字管理クラスの更新
	if (m_pWordManager != NULL) { m_pWordManager->Update(); }

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

	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Setpos(D3DXVECTOR3(m_pCharactorMove->GetPosition().x, m_pCharactorMove->GetPosition().y + 45.0f, m_pCharactorMove->GetPosition().z));
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
	CDebugProc::Print("cn", "PLAYER.LockOn : ", m_pLockOnCharactor != NULL ? 1 : 0);
	CDebugProc::Print("cfcfcf", "PLAYER.BulletRot :", BulletRot.x, " ", BulletRot.y, " ", BulletRot.z);


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

	// ライトの無効化
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
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
	// ライトを元に戻る
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

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
				CUtilityMath::RotateNormarizePI(rot.x);
				CUtilityMath::RotateNormarizePI(rot.y);
				CUtilityMath::RotateNormarizePI(rot.z);

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
					//if (m_pWordManager->GetBulletFlag())
					//{
					//	SetMotion(MOTION_SETUP_NEUTRAL,body);
					//}
					//else
					//{
					//	SetMotion(MOTION_NEUTRAL, body);
					//}
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

				if (nCntParts == 0)
				{
					rot.y += 3.14f;
				}

				//角度の正規化
				CUtilityMath::RotateNormarizePI(rot.x);
				CUtilityMath::RotateNormarizePI(rot.y);
				CUtilityMath::RotateNormarizePI(rot.z);

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
	CDebugProc::Print("cn","MOTION = ",(int)m_motion);
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

		//引数代入
		m_motion[body] = motion;
		m_Mstate[body] = state;

		//その他変数の初期化
		m_nCntBlendMotion[body] = 0;
		m_nCntFlame[body] = 0;
		if (state != STATE_BLEND) { m_nCntKey[body] = 0; }	//ブレンドする時は初期化しない
	}
}

//=============================================================================
// 当たり判定(弾)処理
//=============================================================================
bool CPlayer::CollisionBullet(void)
{
	bool bHit = false;
	CScene *pScene = NULL;

	D3DXVECTOR3 PlayerPos = m_pCharactorMove->GetPosition();
	D3DXVECTOR3 BulletPos,BulletRot;

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
				CBulletBase *pBullet = ((CBulletBase*)pScene);		// CBulletBaseへキャスト(型の変更)
				BulletPos = pBullet->GetPosition();
				BulletRot = pBullet->GetRotation();

				float X = (BulletPos.x - PlayerPos.x) * (BulletPos.x - PlayerPos.x);
				float Y = (BulletPos.y - PlayerPos.y) * (BulletPos.y - PlayerPos.y);
				float Z = (BulletPos.z - PlayerPos.z) * (BulletPos.z - PlayerPos.z);

				if(sqrtf(X + Y + Z) < BULLET_COLLISION_SIZE &&
					m_nID != pBullet->GetID())
				{//球の判定

					/*得点加算 (当てたキャラのIDはpBulletのGetIDで取得できる)*/
					if (pBullet->GetType() == CBulletBase::TYPE_MODEL)
					{	// モデルの場合はポイント加算
						CPoint *pPoint = NULL;
						if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(pBullet->GetID()); }
						if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /*チュートリアルで取得する*/ }

						if (pPoint != NULL) { pPoint->AddPoint(1); }
					}

					//吹き飛ばし
					DamageReaction(10.0f,BulletRot);

					//弾削除
					pBullet->Uninit();

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

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(SCENEX_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
		if (pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
		{// オブジェクトの種類を確かめる
			CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneXへキャスト(型の変更)
			if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
			{
				m_bLand = pSceneX->Collision(pos, posOld, move, radius);
				CObject *pSceneObj = ((CObject*)pSceneX);		// CObjectへキャスト(型の変更)
				if (m_bLand == true)
				{// モデルに当たる
					bHit = true;

					if (pSceneObj->GetRealTimeType() == CObject::REALTIME_NONE)
					{
						if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
							pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
						{	// ベルトコンベアの判定
							pSceneObj->BeltConveyor(move);
						}
						else if (pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING ||
							pSceneObj->GetCollsionType() == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
						{	// ノックバックの判定
							pSceneObj->KnockBack(move, m_nID);
						}
					}
					else if (pSceneObj->GetRealTimeType() == CObject::REALTIME_INITPOS)
					{
						pSceneObj->AffectedLanding(move, m_nID);		// 落ちてくるモデルの着地時の影響
					}
					else if (pSceneObj->GetCollsionType() == CSceneX::COLLISIONTYPE_BOX)
					{
					}
					break;
				}
				else
				{
					bHit = false;
				}
			}
		}
		}
		// 次のシーンに進める
		pScene = pSceneNext;
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

		pPlayer = CGame::GetPlayer(nCntPlayer);
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
	if (m_PlayerLoadState[type][body].bFlag == false ||
		(m_PlayerLoadState[type][body].bFlag == true && bReLoad == true))
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
											{
												sscanf(ReadText, "%s %c %f %f %f", &DustBox,
													&DustBox,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].x,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].y,
													&m_PlayerLoadState[type][body].prop[nCntMotionType].key[nCntKeySet].Pos[nCntKey].z);
											}
											else if (strcmp(HeadText, "ROT") == 0)
											{
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
		m_PlayerLoadState[type][body].bFlag = true;
	}

	int nCntParts = 0;
		for (nCntParts = 0; nCntParts < m_PlayerLoadState[type][body].nPartsNum; nCntParts++)
		{
			ObjCreate(m_pPlayerParts[nCntParts][body]);
			if (m_pPlayerParts[nCntParts][body] != NULL)
			{
				m_pPlayerParts[nCntParts][body]->Set(m_PlayerLoadState[type][body].info[nCntParts].FileName,
					m_PlayerLoadState[type][body].info[nCntParts].pos,
					m_PlayerLoadState[type][body].info[nCntParts].rot, NULL);
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

	for (int nCntMotion = 0; nCntMotion < MOTION_UPPER_MAX; nCntMotion++)
	{
		m_propMotion[nCntMotion][body] = m_PlayerLoadState[type][body].prop[nCntMotion];
	}
	return S_OK;
}


