//=============================================================================
//
// オブジェクトの処理 [oblect.cpp]
// Author : 目黒 未来也
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "load.h"
#include "player.h"
#include "game.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define BELTCONVEYER_MOVE			(0.7f)			// ベルトコンベアの速度
#define KNOCKBACK_MOVE_SMALL		(4.0f)			// ノックバックの強度(小)
#define KNOCKBACK_MOVE_DURING		(6.0f)			// ノックバックの強度(中)
#define KNOCKBACK_MOVE_BIG			(9.0f)			// ノックバックの強度(大)
#define GEAR_ROT_Y					(0.1f)			// ギアの回転量　ベース情報
#define MODEL_MOVE_Y				(0.5f)			// モデル移動時の移動速度

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject()
{
	m_bMoveFlag = false;		// 移動フラグ
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 Scale, CSceneX::COLLISIONTYPE type, CLoad::MODEL model)
{
	CObject *pObject = NULL;

	if (pObject == NULL)
	{
		// オブジェクトクラスの生成
		pObject = new CObject;

		if (pObject != NULL)
		{
			pObject->SetModelType(model);
			pObject->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));		// モデルの割り当て
			pObject->SetScale(Scale);	// スケールの設定
			pObject->Init(pos);			// 初期化
			pObject->SetRot(rot);		// 向きの設定
			pObject->SetCollsionType(type);	// コリジョンのタイプ設定
			pObject->m_nRealTime = REALTIME_INITPOS;
		}
	}

	return pObject;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject::Init(D3DXVECTOR3 pos)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SCENEX);

	CSceneX::Init(pos);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject::Update(void)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();

	if (m_nRealTime == REALTIME_INITPOS)
	{	// 移動フラグがfalse 動かない場合
		D3DXVECTOR3 pos = CSceneX::GetPosition();	// 位置取得
		pos.y -= MODEL_MOVE_Y;						// 移動速度

		if (pos.y - CSceneX::GetVtxMin().y < 0)
		{	// 地面に着いた場合
			if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT || Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_BACK ||
				Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT || Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// ベルトコンベアの場合
				pos.y = pos.y - CSceneX::GetVtxMin().y;
				CSceneX::SetPosition(pos);
			}
			else if (Collsiontype != CSceneX::COLLSIONTYPE_CONVEYOR_FRONT && Collsiontype != CSceneX::COLLSIONTYPE_CONVEYOR_BACK &&
				Collsiontype != CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT && Collsiontype != CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
			{	// ベルトコンベア以外の場合
				pos.y = pos.y - CSceneX::GetVtxMin().y;
				CSceneX::SetPosition(pos);
			}
		}
		CSceneX::SetPosition(pos);
		if (pos.y == 0) { m_nRealTime = REALTIME_NONE; }
	}
	else if (m_nRealTime == REALTIME_NONE)
	{
		if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING || Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
		{	// コリジョンタイプがノックバッ判定を持つなら向きの回転をさせる
			D3DXVECTOR3 rot = CSceneX::GetRot();

			// 強弱の種類によって回転量を変化
			rot.y += GEAR_ROT_Y * ((int)Collsiontype - (int)COLLSIONTYPE_CONVEYOR_LEFT);

			CSceneX::SetRot(rot);
		}
	}
	else if (m_nRealTime == REALTIME_ENDPOS)
	{	// 移動フラグがtrue 動く場合
		D3DXVECTOR3 pos = CSceneX::GetPosition();	// 位置取得
		
		pos.y -= MODEL_MOVE_Y;						// 移動速度

		CSceneX::SetPosition(pos);

		if (pos.y + CSceneX::GetVtxMax().y < 0)
		{	// 地面より下の場合
			Uninit();
			return;
		}
	}
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RSHIFT))
	{	// 移動Flag変化用
		m_nRealTime = REALTIME_ENDPOS;
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject::Draw(void)
{
	CSceneX::Draw();
}

//=============================================================================
// ベルトコンベアの処理
//=============================================================================
void CObject::BeltConveyor(D3DXVECTOR3 *pMove)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_FRONT)
	{	// 前進する
		pMove->z += BELTCONVEYER_MOVE;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_BACK)
	{	// 後退する
		pMove->z += -BELTCONVEYER_MOVE;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_RIHHT)
	{	// 右移動
		pMove->x += -BELTCONVEYER_MOVE;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_CONVEYOR_LEFT)
	{	// 左移動
		pMove->x += BELTCONVEYER_MOVE;
	}
}

//=============================================================================
// ノックバックの処理
//=============================================================================
void CObject::KnockBack(D3DXVECTOR3 *pMove, int nID)
{
	CSceneX::COLLISIONTYPE Collsiontype = CSceneX::GetCollsionType();
	float fknockBackMove = 0.0f;	// ノックバックの強度

	if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL)
	{	// ノックバックの威力が小さい
		fknockBackMove = KNOCKBACK_MOVE_SMALL;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING)
	{	// ノックバックの威力が中ぐらい
		fknockBackMove = KNOCKBACK_MOVE_DURING;
	}
	else if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
	{	// ノックバックの威力が大きい
		fknockBackMove = KNOCKBACK_MOVE_BIG;
	}

	// プレイヤーの向きが方向転換するようになったら削除
	if (CSceneX::GetCollsionNum() == 0 || CSceneX::GetCollsionNum() == 1)
	{	// 左 又は 右 からの判定
		pMove->x *= -fknockBackMove;
	}
	else if (CSceneX::GetCollsionNum() == 2 || CSceneX::GetCollsionNum() == 3)
	{	// 前 又は 後ろ からの判定
		pMove->z *= -fknockBackMove;
	}

	// プレイヤーの向きが方向転換するようになったらコメントを外す
	/*float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
	pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);
	pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);*/
}

//=============================================================================
// モデル着地時の受ける影響の処理
//=============================================================================
void CObject::AffectedLanding(D3DXVECTOR3 *pMove, int nID)
{
	float fPlayer = CGame::GetPlayer(nID)->GetRotation().y;
	pMove->x = sinf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);
	pMove->z = cosf(fPlayer + (D3DX_PI * 1.0f)) * (20.0f);
}