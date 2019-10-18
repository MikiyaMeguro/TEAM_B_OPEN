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
//=============================================================================
// マクロ定義
//=============================================================================
#define BELTCONVEYER_MOVE			(0.7f)			// ベルトコンベアの速度
#define KNOCKBACK_MOVE_SMALL		(4.0f)			// ノックバックの強度(小)
#define KNOCKBACK_MOVE_DURING		(6.0f)			// ノックバックの強度(中)
#define KNOCKBACK_MOVE_BIG			(9.0f)			// ノックバックの強度(大)
#define GEAR_ROT_Y					(0.2f)			// ギアの回転量　ベース情報

//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//=============================================================================
// コンストラクタ
//=============================================================================
CObject::CObject()
{
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
	CObject *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		// オブジェクトクラスの生成
		pSceneX = new CObject;

		if (pSceneX != NULL)
		{
			pSceneX->BindModel(CLoad::GetBuffMat(model), CLoad::GetNumMat(model), CLoad::GetMesh(model));		// モデルの割り当て
			pSceneX->SetScale(Scale);	// スケールの設定
			pSceneX->Init(pos);			// 初期化
			pSceneX->SetRot(rot);		// 向きの設定
			pSceneX->SetCollsionType(type);	// コリジョンのタイプ設定
		}
	}

	return pSceneX;
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

	if (Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_SMALL || Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_DURING || Collsiontype == CSceneX::COLLSIONTYPE_KNOCKBACK_BIG)
	{	// コリジョンタイプがノックバッ判定を持つなら向きの回転をさせる
		D3DXVECTOR3 rot = CSceneX::GetRot();

		// 強弱の種類によって回転量を変化
		rot.y += GEAR_ROT_Y * ((int)Collsiontype - (int)COLLSIONTYPE_CONVEYOR_LEFT);

		CSceneX::SetRot(rot);
	}
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "ModelPos : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
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
void CObject::KnockBack(D3DXVECTOR3 *pMove)
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

	if (CSceneX::GetCollsionNum() == 0 || CSceneX::GetCollsionNum() == 1)
	{	// 左 又は 右 からの判定
		pMove->x *= -fknockBackMove;
	}
	else if (CSceneX::GetCollsionNum() == 2 || CSceneX::GetCollsionNum() == 3)
	{	// 前 又は 後ろ からの判定
		pMove->z *= -fknockBackMove;
	}
}
