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
#include "PlayerNumSelect.h"
#include "time.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define AREA_CHASE		(40.0f)			// エリア
#define AREA_COILLSION	(15.0f)			// コリジョンの範囲
#define CHASE_MOVE		(1.0f)			// 追従時の速度

#define UNITI_TIME		(40)			// 終了する時間
//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CWord::CWord() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nNumPlayerGet = 0;
	m_nCntUninit = 0;
	m_bFlag = false;
	m_bPopFlag = false;
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
CWord *CWord::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord, int nNum)
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
			pWord->m_nNum = nNum;

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
	CSceneBillBoard::SetObjType(CScene::OBJTYPE_WORD);
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
	if (m_bFlagUninit == true) { return; }
	// ローカル変数
	//CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	CPlayerSelect::SELECTPLAYER NumPlayer = CPlayerSelect::SELECTPLAYER_4P;//テスト

	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//位置の取得
	D3DXVECTOR3 PosOld = pos;						// 位置を保存
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);// 移動
	CPlayer *pPlayer[MAX_PLAYER] = {};
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];

	if (m_bFlag == false)
	{	// 拾うことが可能な文字の場合
		for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
		{
			pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);			// プレイヤーを取得
			PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// プレイヤーの位置を取得
		}

		for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
		{
			if (pPlayer[nCntPlayer]->GetWordManager()->GetCntNum() < 3)
			{

				Distance(pos, PlayerPos[nCntPlayer], nCntPlayer);

				// 当たり判定(円を使った判定)
				Circle(pos, PlayerPos[nCntPlayer], AREA_COILLSION);

				if (m_bFlag == true)
				{	// 終了フラグが立った場合
					pPlayer[nCntPlayer]->GetWordManager()->SetWord(m_nWordNum);
					pPlayer[nCntPlayer]->SetbSetupBullet(true);
					m_nNumPlayerGet = nCntPlayer;				// プレイヤー番号を取得
					move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					m_size = D3DXVECTOR3(6.0f, 6.0f, 0.0f);
					break;
				}
			}
			else
			{	// 3個取ったら取らない
				Distance(pos, D3DXVECTOR3(9999999990.0f, 0.0f, 9999999990.0f), nCntPlayer);
			}
		}

		if (m_bFlag == false)
		{	// 終了フラグが立っている場合
			int nNum = ComparisonDistance((int)NumPlayer);

			// 文字がプレイヤーに集まる(範囲で判定を取る)
			move = Approach(pos, PlayerPos[nNum], AREA_CHASE, m_fDistance[nNum]);
		}

	}

	if (m_bFlag == true)
	{	// 取得後の演出の場合
		if (pPlayer[m_nNumPlayerGet] == NULL)
		{	
			pPlayer[m_nNumPlayerGet] = CGame::GetPlayer(m_nNumPlayerGet);	// プレイヤーを取得
			float fPlayer = pPlayer[m_nNumPlayerGet]->GetRotation().y;
			
			//pos = D3DXVECTOR3(sinf(fPlayer + (D3DX_PI)) + (pPlayer[m_nNumPlayerGet]->GetPosition().x + 10.0f), 40.0f, pPlayer[m_nNumPlayerGet]->GetPosition().z);
			pos = D3DXVECTOR3(pPlayer[m_nNumPlayerGet]->GetPosition().x, 50.0f, pPlayer[m_nNumPlayerGet]->GetPosition().z);
		}

		m_nCntUninit++;	// カウントの加算

		if ((m_nCntUninit % UNITI_TIME) == 0)
		{	// 時間になったら終了する
			//Uninit();
			m_bFlagUninit = true;
			//return;
		}

		//pos = Move(pos);
	}

	if ((CTime::GetStageTime() % 30) == 0)
	{
		m_bFlagUninit = true;
	}


	//ScaleSize();

	// 位置更新
	pos.x += move.x;
	//pos.y += move.y;
	pos.z += move.z;

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
// プレイヤーと文字ビルボードとの距離を測る処理
//=============================================================================
void CWord::Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNumPlayer)
{
	// 距離を測る
	m_fDistance[nNumPlayer] = ((Pos.x - OtherPos.x) * (Pos.x - OtherPos.x)) + ((Pos.z - OtherPos.z) * (Pos.z - OtherPos.z));
}

//=============================================================================
// 測った距離を元に一番近い距離を選ぶ処理
//=============================================================================
int CWord::ComparisonDistance(int nNum)
{
	int nNumPlayer = 0;

	for (int nCntPlayer = 0; nCntPlayer < (int)nNum - 1; nCntPlayer++)
	{
		if (m_fDistance[nCntPlayer] > m_fDistance[nCntPlayer + 1])
		{	// 数値を代入
			nNumPlayer = nCntPlayer + 1;
		}
	}

	return nNumPlayer;
}


//=============================================================================
// 範囲の処理
//=============================================================================
void CWord::Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle)
{
	float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

	if (fDistance < fAngle) { m_bFlag = true; }
}

//=============================================================================
// プレイヤーに集まるの処理
//=============================================================================
D3DXVECTOR3 CWord::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle, float fDistance)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f,0.0f);

	if (fDistance < fAngle * fAngle)
	{	// 距離内に入ったら
		// プレイヤーに近づける
		move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
		move.z = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
	}

	return move;
}
