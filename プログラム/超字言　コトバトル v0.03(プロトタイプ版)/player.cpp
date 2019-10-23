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

#include "sceneX.h"

#include "debugProc.h"
#include "bullet.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_COLLISON (D3DXVECTOR3(5.0f, 20.0f, 5.0f))			//キャラクターの当たり判定

//=============================================================================
// コンストラクタ&デストラクタ
//=============================================================================
CPlayer::CPlayer(int nPriority) : CScene(nPriority)
{
	m_bLand = false;
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pWordManager = NULL;
	m_nCntTransTime = 0;
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

	//描画用モデル生成
	m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	m_pPlayerModel->SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	//変数初期化
	m_pPlayerModel = NULL;
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	m_nCntTransTime = 0;
	//コマンドセット
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_LSHIFT);
	CCommand::RegistCommand("PLAYER_SHOTBULLET", CCommand::INPUTTYPE_CONTROLLER_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_LEFT_SHOULDER);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	//キャラ情報クラス削除
	ObjRelease(m_pCharactorMove);

	//描画モデル終了処理
	if (m_pPlayerModel != NULL)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = NULL;
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
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
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

		//描画するモデルに情報を入れる
		m_pPlayerModel->SetPosition(m_pCharactorMove->GetPosition());
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
	}

	// 弾の生成
	if (CCommand::GetCommand("PLAYER_SHOTBULLET",m_nID))
	{
		if (m_pWordManager != NULL)
		{//文字管理クラスに弾の生成を委託する
			m_pWordManager->BulletCreate(m_nID);
		}
	}

	//文字管理クラスの更新
	if (m_pWordManager != NULL) { m_pWordManager->Update(); }

	//無敵時間のカウントダウン
	if (m_nCntTransTime > 0)
	{
		m_nCntTransTime--;

		if (m_nCntTransTime % 2 == 0)
		{
			m_pPlayerModel->SetDrawFlag(!(m_pPlayerModel->GetDrawFlag()));
		}
	}
	else
	{
		m_pPlayerModel->SetDrawFlag(true);
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
	//モデルはSceneクラスの子供なので個別のDrawは必要ない
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
