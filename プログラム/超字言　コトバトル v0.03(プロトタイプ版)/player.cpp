//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "player.h"
#include "manager.h"

#include "sceneX.h"

#include "debugProc.h"

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
	if (m_pCharactorMove == NULL)
	{
		if (ObjCreate(m_pCharactorMove))
		{
			m_pCharactorMove->Set(pos,rot,type,this);
		}
	}
	m_nID = (nPlayerID % 4);//範囲外の数字が入ったらそれを0～3までの数字にする

	m_pPlayerModel = CSceneX::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f),CLoad::MODEL_SAMPLE_PLAYER,1);
	m_pPlayerModel->SetObjType(CScene::OBJTYPE_PLAYER);
}

//=============================================================================
//	初期化処理
//=============================================================================
HRESULT CPlayer::Init(void)
{
	m_pPlayerModel = NULL;
	m_pCharactorMove = NULL;
	m_ChildCameraName = "";
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	ObjRelease(m_pCharactorMove);

	if (m_pPlayerModel != NULL)
	{
		m_pPlayerModel->Uninit();
		m_pPlayerModel = NULL;
	}

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

		m_pCharactorMove->Update();
		// モデルとの当たり判定
		CollisonObject(&m_pCharactorMove->GetPosition(), &D3DXVECTOR3(m_posOld.x, m_posOld.y, m_posOld.z), &m_pCharactorMove->GetMove(), PLAYER_COLLISON);

		m_pPlayerModel->SetPosition(m_pCharactorMove->GetPosition());
		m_pPlayerModel->SetRot(m_pCharactorMove->GetRotation());
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

}

//=============================================================================
// 当たり判定処理
//=============================================================================
void CPlayer::CollisonObject(D3DXVECTOR3 * pos, D3DXVECTOR3 * posOld, D3DXVECTOR3 * move, D3DXVECTOR3 radius)
{
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
				m_bLand = ((CSceneX*)pScene)->Collision(pos, posOld, move, radius);
				if (m_bLand == true)
				{// モデルに当たる
				}
			}
		}
		// 次のシーンに進める
		pScene = pSceneNext;
	}
}
