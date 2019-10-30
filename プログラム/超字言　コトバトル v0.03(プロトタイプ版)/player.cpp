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

CPlayer::PlayerLoadState CPlayer::m_PlayerLoadState[CPlayer::TYPE_MAX];
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 20.0f, 5.0f))			//キャラクターの当たり判定
#define MODEL_LOAD_TEXT "data/MOTION/motion_bea.txt"
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

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		m_pPlayerParts[nCntParts] = NULL;
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
void CPlayer::Set(D3DXVECTOR3 pos, CCharaBase::CHARACTOR_MOVE_TYPE type, int nPlayerID, D3DXVECTOR3 rot)
{
	//キャラ情報クラス生成
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot,type,this);
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
		if (type == CCharaBase::MOVETYPE_NPC_AI) { nID = MAX_PLAYER; }	// COM表示にする
		m_pPlayerNum = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, pos.y + 45.0f, pos.z), 7.0f, 3.0f, "プレイ人数");
		m_pPlayerNum->SetTexture(D3DXVECTOR2(0.0f, nID * 0.2f), D3DXVECTOR2(1.0f, (nID * 0.2f) + 0.2f));
		m_pPlayerNum->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}


	ModelLoad(MODEL_LOAD_TEXT,TYPE_POWER);

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

	//コマンドセット
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_RIGHT_SHOULDER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//キャラ情報クラス削除
	ObjRelease(m_pCharactorMove);

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		ObjRelease(m_pPlayerParts[nCntParts]);
		m_pPlayerParts[nCntParts] = NULL;
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
		CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);
		testpos = m_pCharactorMove->GetPosition();
		testmove = m_pCharactorMove->GetMove();

		D3DXVECTOR3 testposFRONT = D3DXVECTOR3(sinf(m_pCharactorMove->GetRotation().y) * 10,
			sinf(m_pCharactorMove->GetRotation().x) * 10,
			cosf(m_pCharactorMove->GetRotation().y) * 10);
		testpos += testposFRONT;
		//前にObjectがあるかどうか
		CollisonObject(&D3DXVECTOR3(testpos.x, testpos.y, testpos.z), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &testmove, PLAYER_COLLISON);

	}

	// 弾の生成
	if (CCommand::GetCommand("PLAYER_SHOTBULLET",m_nID))
	{
		if (m_pWordManager != NULL)
		{//文字管理クラスに弾の生成を委託する
			m_pWordManager->BulletCreate(m_nID,m_pCharactorMove->GetPosition() + D3DXVECTOR3(0.0f,10.0f,0.0f));
			if (m_pWordManager->GetCntNum() == 0)
			{
				m_bSetupBullet = false;
			}
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
		for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
		{
			if (m_pPlayerParts[nCntParts] != NULL)
			{
				m_pPlayerParts[nCntParts]->SetDrawFlag(true);
			}
		}
	}

	if (m_pPlayerNum != NULL)
	{
		m_pPlayerNum->Setpos(D3DXVECTOR3(m_pCharactorMove->GetPosition().x, m_pCharactorMove->GetPosition().y + 45.0f, m_pCharactorMove->GetPosition().z));
	}

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{

		if (m_pPlayerParts[nCntParts] != NULL)
		{
			if (m_nCntTransTime % 2 == 0)
			{//ダメージ時の点滅処理
				m_pPlayerParts[nCntParts]->SetDrawFlag(!m_pPlayerParts[nCntParts]->GetDrawFlag());
			}

			m_pPlayerParts[nCntParts]->Update();
		}
	}

#ifdef _DEBUG
	testpos = m_pCharactorMove->GetPosition();
	testmove = m_pCharactorMove->GetMove();

	CDebugProc::Print("cfcfcf", "PLAYER.Pos :", testpos.x," ",testpos.y, " ", testpos.z);
	CDebugProc::Print("cfcfcf", "PLAYER.Move :", testmove.x, " ", testmove.y, " ", testmove.z);
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		if (m_pPlayerParts[nCntParts] != NULL)
		{
			m_pPlayerParts[nCntParts]->Draw();
		}
	}
}
//=============================================================================
// モーション更新処理
//=============================================================================
void CPlayer::MotionUpdate(void)
{

}

//=============================================================================
// モーション設定処理
//=============================================================================
void	CPlayer::SetNextMotion(MOTION motion)
{
	m_NextMotion = motion;
	m_MotionState = STATE_BLEND;
	m_nCntBlendMotion = 0;
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
					if (m_bLand == true)
					{// モデルに当たる
						bHit = true;
						CObject *pSceneObj = ((CObject*)pSceneX);		// CObjectへキャスト(型の変更)
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
								pSceneObj->KnockBack(move);
							}
						}
						break;
					}
					else
					{
						CObject *pSceneObj = ((CObject*)pSceneX);		// CObjectへキャスト(型の変更)
						if (pSceneObj->GetRealTimeType() == CObject::REALTIME_INITPOS) 
						{
							if (pos->y + 10.0f > pSceneObj->GetPosition().y - pSceneObj->GetVtxMin().y) 
							{
								move->x = 2.0f; 
							}
						}
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
// モデルロード処理
//=============================================================================
HRESULT CPlayer::ModelLoad(LPCSTR pFileName, PLAYER_TYPE type)
{
	FILE* pFile = NULL;		// ファイルポインタ
	char ReadText[256];		// 読み込んだ文字列を入れておく
	char HeadText[256];		// 比較用
	char DustBox[256];		// 使用しないものを入れておく

	int nCntMotionSetType = 0;					// モーションセットの種類の数
												//int nCntMotionType = (int)MOTION_NEUTRAL;	// モーションの種類の数
	int nCntKeySet = 0;							// キーセット数
	int nCntKey = 0;							// キー数
	int nCntPartsSet = 0;						// パーツ数
	int nCntFileNameNum = 0;
	PartsLoadInfo LoadInfo[PLAYER_MODELNUM];		//ロード情報
	int nPartsNum = 0;

	for (int nCntParts = 0; nCntParts < PLAYER_MODELNUM; nCntParts++)
	{
		ObjRelease(m_pPlayerParts[nCntParts]);
		m_pPlayerParts[nCntParts] = NULL;
	}

	if (m_PlayerLoadState[type].bFlag == false)
	{//	まだこの情報がロードされていなければ
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
						sscanf(ReadText, "%s %c %s", &DustBox, &DustBox, m_PlayerLoadState[type].info[nCntFileNameNum].FileName);
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
								sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type].nPartsNum);
							}
							else if (strcmp(HeadText, "PARTSSET") == 0)
							{//PARTSSETを読みとったら
								while (strcmp(HeadText, "END_PARTSSET") != 0)
								{
									fgets(ReadText, sizeof(ReadText), pFile);
									sscanf(ReadText, "%s", &HeadText);

									if (strcmp(HeadText, "INDEX") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type].info[nCntPartsSet].nIndex);
									}
									else if (strcmp(HeadText, "PARENT") == 0)
									{
										sscanf(ReadText, "%s %c %d", &DustBox, &DustBox, &m_PlayerLoadState[type].info[nCntPartsSet].nParent);
									}
									else if (strcmp(HeadText, "POS") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type].info[nCntPartsSet].pos.x,
											&m_PlayerLoadState[type].info[nCntPartsSet].pos.y,
											&m_PlayerLoadState[type].info[nCntPartsSet].pos.z);
									}
									else if (strcmp(HeadText, "ROT") == 0)
									{
										sscanf(ReadText, "%s %c %f %f %f", &DustBox,
											&DustBox,
											&m_PlayerLoadState[type].info[nCntPartsSet].rot.x,
											&m_PlayerLoadState[type].info[nCntPartsSet].rot.y,
											&m_PlayerLoadState[type].info[nCntPartsSet].rot.z);
									}
								}
								nCntPartsSet++;

							}
						}
					}
				}
			}

		}
		fclose(pFile);
	}

	int nCntParts = 0;
	for (nCntParts = 0; nCntParts < m_PlayerLoadState[type].nPartsNum; nCntParts++)
	{
		ObjCreate(m_pPlayerParts[nCntParts]);
		if (m_pPlayerParts[nCntParts] != NULL)
		{
			m_pPlayerParts[nCntParts]->Set(m_PlayerLoadState[type].info[nCntParts].FileName,
				m_PlayerLoadState[type].info[nCntParts].pos,
				m_PlayerLoadState[type].info[nCntParts].rot, NULL);
		}
	}

	//親マトリクスセット
	for (int nCntParts = 0; nCntParts < m_PlayerLoadState[type].nPartsNum; nCntParts++)
	{
		int nNum = m_PlayerLoadState[type].info[nCntParts].nParent;
		if (nNum != -1)
		{
			m_pPlayerParts[nCntParts]->SetParent(m_pPlayerParts[nNum]->GetMatrix());
		}
		else
		{
			m_pPlayerParts[nCntParts]->SetParent(m_pCharactorMove->GetMatrix());
		}
	}

	m_PlayerLoadState[TYPE_POWER].bFlag = true;
	return S_OK;
}


