//=============================================================================
//
// 文字のビルボード処理 [word.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "word.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "InputKeyboard.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define AREA_CHASE		(10.0f)			// エリア
#define AREA_COILLSION	(5.0f)			// コリジョンの範囲
#define CHASE_MOVE		(0.8f)			// 追従時の速度
//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CWord::CWord() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
}

//--------------------------------------------
// デストラクタ
//--------------------------------------------
CWord::~CWord()
{
}

//--------------------------------------------
// 生成
//--------------------------------------------
CWord *CWord::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord)
{
	CWord *pWord = NULL;

	if (pWord == NULL)
	{
		pWord = new CWord;

		if (pWord != NULL)
		{
			pWord->Init(pos);
			pWord->BindTexture(Tag);
			//値の代入
			pWord->SetBillboard(pos, fHeight, fWidth);
			pWord->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_nWordNum = nWord; 
			pWord->SetTexture(nWord, 10, 5, 1);
		}
	}

	return pWord;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWord::Init(D3DXVECTOR3 pos)
{
	CSceneBillBoard::Init(pos);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWord::Uninit(void)
{
	CSceneBillBoard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWord::Update(void)
{
	// ローカル変数
	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//位置の取得
	D3DXVECTOR3 PosOld = pos;						// 位置を保存
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);// 移動
	CPlayer *pPlayer = CGame::GetPlayer();			// プレイヤーを取得
	D3DXVECTOR3 PlayerPos = pPlayer->GetPosition();	// プレイヤーの位置を取得

	//pos = Move(pos);

	if (CGame::GetWordManager()->GetCntNum() < 3)
	{	// 3個取ったら取らない
		// 文字がプレイヤーに集まる(範囲で判定を取る)
		move = Approach(pos, PlayerPos, AREA_CHASE);

		// 当たり判定(円を使った判定)
		Circle(pos, PlayerPos, AREA_COILLSION);
	}

	//ScaleSize();

	// 位置更新
	pos.x += move.x;
	//if (m_bMoveFlag == false) { pos.y += move.y; }
	//if (m_bMoveFlag == true) { pos.y -= move.y; }
	pos.z += move.z;

	if (m_bFlagUninit == true)
	{	// 終了フラグが立った場合
		CGame::GetWordManager()->SetWord(m_nWordNum);
		Uninit();
		return;
	}

	CSceneBillBoard::Update();
	CSceneBillBoard::SetBillboard(pos, m_size.x, m_size.y);
}

//=============================================================================
// 描画処理
//=============================================================================
void CWord::Draw(void)
{
	CSceneBillBoard::Draw();
}

//=============================================================================
// 移動処理
//=============================================================================
D3DXVECTOR3 CWord::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == false)
	{
		if (pos.y > 30.0f)
		{	// 位置が指定した場所より大きい場合
			m_bMoveFlag = true;
		}
	}
	else if (m_bMoveFlag == true)
	{
		if (pos.y < 0.0f + m_size.y)
		{	// 位置が指定した場所より小さい場合
			m_bMoveFlag = false;
		}
	}

	return pos;
}

//=============================================================================
// 拡大縮小の処理
//=============================================================================
void CWord::ScaleSize(void)
{
	if (m_bScaleFlag == false)
	{	// 拡大する
		m_size.x += 0.2f; 
		m_size.y += 0.2f;
		if (m_size.x > 15.0f && m_size.y > 15.0f)
		{	// 縮小するフラグへ
			m_bScaleFlag = true;
		}
	}
	else if (m_bScaleFlag == true)
	{	// 縮小する
		m_size.x -= 0.2f;
		m_size.y -= 0.2f;
		if (m_size.x < m_sizeOld.x && m_size.y < m_sizeOld.y)
		{	// 拡大するフラグへ
			m_bScaleFlag = false;
		}
	}
}

//=============================================================================
// 範囲の処理
//=============================================================================
void CWord::Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle)
{
	float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

	if (fDistance < fAngle) { m_bFlagUninit = true; }
}

//=============================================================================
// プレイヤーに集まるの処理
//=============================================================================
D3DXVECTOR3 CWord::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f,0.0f);

	// 距離を測る
	float fCircle = ((Pos.x - OtherPos.x) * (Pos.x - OtherPos.x)) + ((Pos.z - OtherPos.z) * (Pos.z - OtherPos.z));
	if (fCircle < fAngle * fAngle)
	{	// 距離内に入ったら
		// プレイヤーに近づける

		move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
		move.z = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
	}

	return move;
}
