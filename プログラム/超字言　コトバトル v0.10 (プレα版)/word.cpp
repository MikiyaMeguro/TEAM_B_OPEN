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
#include "tutorial.h"

#include "debugProc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define AREA_CHASE		(40.0f)			// エリア
#define AREA_COILLSION	(15.0f)			// コリジョンの範囲
#define CHASE_MOVE		(4.0f)			// 追従時の速度
#define END_POS_Y		(15.0f)			// 文字の出現した時の最終位置
#define FLOATING_MOVE	(0.5f)			// 浮遊速度
#define POP_POS_Y		(END_POS_Y + 10.0f)	// 出現後の浮遊時の最大位置
#define POP_POS_Y_SMALL		(END_POS_Y - 5.0f)	// 出現後の浮遊時の最少位置
#define MAX_SIZE		(D3DXVECTOR2(12.0f, 12.0f))	// サイズの最大値

#define UNITI_TIME		(40)			// 終了する時間
#define α_COL_TIME		(15)			// 透明度変化時の時間
#define ANIM_FRAME		(7)				// アニメーションカウンター
#define PATTERN_NUM		(10)			// パターン数
#define COL_DEFAULT		(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
#define STAGE_REST_TIME	(60)			// ステージ切り替え時の文字リセット

//--------------------------------
// 点滅関係
//--------------------------------
#define TIME_FRAME		(60)
#define FLASHING_SMALL	(0.05f)			// 点滅(小さい)
#define FLASHING_MAX	(0.2f)			// 点滅(大きい)
#define FLASHING_TIME_SMALL	(TIME_FRAME * 23)		// 点滅する始める時間
#define FLASHING_TIME_MAX	(TIME_FRAME * 28)		// 点滅が激しく時間
#define REST_TIME		(TIME_FRAME * 30)			// 点滅後に終了する時間
#define LOST_TIME		(780)			// 時間経過で消える時間


//*****************************************************************************
// 静的メンバ変数
//*****************************************************************************

//--------------------------------------------
// コンストラクタ
//--------------------------------------------
CWord::CWord() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nCntUninit = 0;
	m_bFlag = false;
	m_bPopFlag = false;
	m_bFlashingFlag = false;
	m_bRestFlag = false;
	m_fMoveY = 0.0f;
	m_col = COL_DEFAULT;
	m_pBillBoard[0] = NULL;
	m_pBillBoard[1] = NULL;
	m_nAnim = 0;
	m_nPatten = 0;
	m_colA = 0.4f;
	m_nCntFlashing = 0;
	m_nLostCut = 0;
	m_move = D3DXVECTOR3(0.0f,0.0f,0.0f);		// サイズ
	m_nLostType = 0;

	// 3文字候補時の変数
	m_bSearchFlag = false;
	m_nCntSearch = 0;
	m_nNumSearch = 0;
	m_SearchCol = NULL;

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
CWord *CWord::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight, LPCSTR Tag, int nWord, int LostType,int nNum)
{
	CWord *pWord = NULL;

	if (pWord == NULL)
	{
		pWord = new CWord;

		if (pWord != NULL)
		{
			pWord->m_nLostType = LostType;
			pWord->Init(pos);
			pWord->BindTexture(Tag);
			//値の代入
			pWord->SetBillboard(pos, fHeight, fWidth);
			pWord->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_nWordNum = nWord;
			pWord->SetTexture(nWord, 10, 5, 1);
			pWord->m_nNum = nNum;
			pWord->m_move = move;
		}
	}

	return pWord;
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CWord::Init(D3DXVECTOR3 pos)
{
	if (m_SearchCol == NULL)
	{
		int nNumSearch = *CPlayerSelect::GetModeSelectMode();
		//int nNumSearch = CPlayerSelect::SELECTPLAYER_2P;
		m_SearchCol = new D3DXCOLOR[nNumSearch + 1];

		for (int nCntCol = 0; nCntCol < nNumSearch + 1; nCntCol++)
		{
			if (&m_SearchCol[nCntCol] != NULL) { m_SearchCol[nCntCol] = COL_DEFAULT; }
		}
	}

	CSceneBillBoard::Init(pos);
	CSceneBillBoard::SetObjType(CScene::OBJTYPE_WORD);

	if (m_pBillBoard[0] == NULL)
	{
		m_pBillBoard[0] = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), 17.0f, 30.0f, "文字エフェクト");
		if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->SetTexture(5, 10, 1, 1); }
		m_pBillBoard[0]->SetObjType(CScene::OBJTYPE_WORD_EFFECT);
	}

	if (m_nLostType == 1)
	{//	時間経過で消える文字
		if (m_pBillBoard[1] == NULL)
		{
			m_pBillBoard[1] = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), 17.0f, 120.0f, "文字エフェクト");
			if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->SetTexture(5, 10, 1, 1); }
			m_pBillBoard[1]->SetObjType(CScene::OBJTYPE_WORD_EFFECT);
		}

	}


	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CWord::Uninit(void)
{
	if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
	if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
	if (&m_SearchCol != NULL) { delete[] m_SearchCol; m_SearchCol = NULL; }
	CSceneBillBoard::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CWord::Update(void)
{
	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//位置の取得
	D3DXVECTOR3 PosOld = pos;						// 位置を保存
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// 移動

	if (m_bFlag == false) { FlashingCol(); }		// 点滅の処理
	if (m_bRestFlag == true) { m_bFlagUninit = true; return; }

	if (m_bPopFlag == false)
	{	// 出現時の場合
		move.y += 1.0f;
		SizeScale(&m_size, 1.0f, MAX_SIZE);
		if (pos.y >= END_POS_Y) { m_bPopFlag = true; }
	}
	else if (m_bPopFlag == true)
	{
		if (m_bFlagUninit == true) { return; }
		// ローカル変数
		CPlayerSelect::SELECTPLAYER NumPlayer = {};
		if (CManager::GetMode() == CManager::MODE_TUTORIAL)
		{
			NumPlayer = *CPlayerSelect::GetModeSelectMode();
		}
		else if (CManager::GetMode() == CManager::MODE_GAME)
		{
			NumPlayer = CPlayerSelect::SELECTPLAYER_4P;//テスト
		}

		CPlayer *pPlayer[MAX_PLAYER] = {};
		D3DXVECTOR3 PlayerPos[MAX_PLAYER];

		if (m_bFlag == false)
		{	// 拾うことが可能な文字の場合
			for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
			{
				if (CManager::GetMode() == CManager::MODE_GAME)
				{// プレイヤーを取得
					pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);
				}
				else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
				{
					pPlayer[nCntPlayer] = CTutorial::GetPlayer(nCntPlayer);
				}

				if (pPlayer[nCntPlayer] != NULL)
				{
					PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// プレイヤーの位置を取得
				}
			}

			for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
			{
				if (pPlayer[nCntPlayer] != NULL)
				{
					if (pPlayer[nCntPlayer]->GetWordManager()->GetCntNum() < 3 && pPlayer[nCntPlayer]->GetWordManager()->GetGatherFlag() == false)
					{

						Distance(pos, PlayerPos[nCntPlayer], nCntPlayer);

						// 当たり判定(円を使った判定)
						Circle(pos, PlayerPos[nCntPlayer], AREA_COILLSION);

						if (m_bFlag == true)
						{	// 終了フラグが立った場合
							if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
							if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
							pPlayer[nCntPlayer]->GetWordManager()->SetWord(m_nWordNum);
							pPlayer[nCntPlayer]->SetbSetupBullet(true);
							move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
							m_col = COL_DEFAULT;
							if (m_nLostType == 0)
							{
								m_bFlagUninit = true;
							}
							break;
						}
					}
					else
					{	// 3個取ったら取らない
						Distance(pos, D3DXVECTOR3(9999999990.0f, 0.0f, 9999999990.0f), nCntPlayer);
					}
				}

			}

			if (m_bFlag == false)
			{	// 終了フラグが立っている場合
				int nNum = ComparisonDistance((int)NumPlayer);

				// 文字がプレイヤーに集まる(範囲で判定を取る)
				move = Approach(pos, PlayerPos[nNum], AREA_CHASE, m_fDistance[nNum]);
			}

			pos = Move(pos);
		}

		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			if (((CTime::GetStageTime() % STAGE_REST_TIME) == 0) && CManager::GetGame()->GetChangeNum() < 2)
			{
				Uninit();
				return;
			}
		}
	}
	if (m_nLostType == 1)
	{//	時間経過で消える文字
		if (m_nLostCut > LOST_TIME - 200)
		{
			m_nCntUninit++;	// カウントの加算
			m_size.x += 0.009f;
			m_size.y += 0.009f;
			//	カラーの変更
			if (m_nCntUninit % 10 == 0) { m_col.a = 0.0f; }
			else { m_col.a = 1.0f; }
		}
		if (pos.y < 15.0f)
		{//	文字エフェクトの削除
			if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
		}
		else if (pos.y > 25.0f)
		{//	下に移動させるときの加速
			move.y -= 1.0f;
		}

	}
	//if (pos.y < 15.0f)
	{
		move += m_move;
	}
	// 位置更新
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;
	if (m_pBillBoard[0] != NULL)
	{
		m_pBillBoard[0]->Setpos(D3DXVECTOR3(pos.x, 0.0f, pos.z));
	}
	CSceneBillBoard::Update();
	CSceneBillBoard::SetBillboard(pos, m_size.x, m_size.y);
	CSceneBillBoard::SetCol(m_col);
	if (m_nLostType == 1)
	{//	時間経過で消える文字
		m_nLostCut++;
		CDebugProc::Print("m_nLostCut : %d", m_nLostCut);

		if (m_move.x > 0.1f || m_move.z > 0.1f || m_move.x < -0.1f || m_move.z < -0.11f)
		{
			if (m_nLostCut > LOST_TIME-320)
			{//	フレームで消える
				if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
				if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
				Uninit();
			}
		}
		else if (m_move.x == 0.0f || m_move.z == 0.0f || m_move.x == 0.0f || m_move.z == 0.0f)
		{
			if (m_nLostCut > LOST_TIME)
			{//	フレームで消える
				if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Uninit(); m_pBillBoard[0] = NULL; }
				if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Uninit(); m_pBillBoard[1] = NULL; }
				Uninit();
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CWord::Draw(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_pBillBoard[0] != NULL) { m_pBillBoard[0]->Draw(); }
	if (m_nLostType == 1)
	{//	時間経過で消える文字
		if (m_pBillBoard[1] != NULL) { m_pBillBoard[1]->Draw(); }
	}

	CSceneBillBoard::Draw();
}

//=============================================================================
// 移動処理
//=============================================================================
D3DXVECTOR3 CWord::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == true)
	{
		pos.y += FLOATING_MOVE;
		m_colA += 0.01f;
		if (m_colA > 1.0f) { m_colA = 1.0f; }
		if (pos.y > POP_POS_Y)
		{	// 位置が指定した場所より大きい場合
			m_bMoveFlag = false;
			//m_colA = 1.0f;
		}
	}
	else if (m_bMoveFlag == false)
	{
		pos.y -= FLOATING_MOVE;
		m_colA -= 0.01f;
		if (m_colA < 0.38f) { m_colA = 0.38f; }
		if (pos.y < POP_POS_Y_SMALL)
		{	// 位置が指定した場所より小さい場合
			m_bMoveFlag = true;
			m_nCntSearch++;
			if (m_nCntSearch >= m_nNumSearch) {
				m_nCntSearch = 0; }
			//m_colA = 0.2f;
		}
	}

	if (m_pBillBoard[0] != NULL)
	{
		m_pBillBoard[0]->SetCol(D3DXCOLOR(m_SearchCol[m_nCntSearch].r, m_SearchCol[m_nCntSearch].g, m_SearchCol[m_nCntSearch].b, m_colA));
		if (m_SearchCol[m_nCntSearch] == COL_DEFAULT) { m_pBillBoard[0]->SetBillboard(m_pBillBoard[0]->GetPos(), 30.0f, 17.0f); }
		else if (m_SearchCol[m_nCntSearch] != COL_DEFAULT) { m_pBillBoard[0]->SetBillboard(m_pBillBoard[0]->GetPos(), 100.0f, 17.0f); }
	}


	return pos;
}

//=============================================================================
// 拡大縮小の処理
//=============================================================================
void CWord::SizeScale(D3DXVECTOR3 *size, float fMove, D3DXVECTOR2 MaxSize)
{
	size->x += fMove;
	size->y += fMove;

	if (fMove >= 0)
	{	// 0以上の場合
		if (size->x > MaxSize.x) { size->x = MaxSize.x; }
		if (size->y > MaxSize.y) { size->y = MaxSize.y; }
	}
	else if (fMove < 0)
	{	// 0以下の場合
		if (size->x < MaxSize.x) { size->x = MaxSize.x; }
		if (size->y < MaxSize.y) { size->y = MaxSize.y; }
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

//=============================================================================
// 3文字目に候補の色設定処理
//=============================================================================
void CWord::SetSearchCol(D3DXCOLOR col)
{
	int nNumSearch = *CPlayerSelect::GetModeSelectMode();
	//int nNumSearch = CPlayerSelect::SELECTPLAYER_2P;//テスト
	for (int nCntCol = 0; nCntCol < nNumSearch + 1; nCntCol++)
	{
		if (&m_SearchCol[nCntCol] != NULL && m_SearchCol[nCntCol] == col)
		{
			break;
		}
		else if (&m_SearchCol[nCntCol] != NULL && m_SearchCol[nCntCol] == COL_DEFAULT)
		{
			m_SearchCol[nCntCol] = col;		// 色の代入
			m_nNumSearch++;
			break;
		}
	}
}

//=============================================================================
// 3文字目候補が無くなった場合
//=============================================================================
void CWord::UninitSearchCol(D3DXCOLOR col)
{
	int nNumSearch = *CPlayerSelect::GetModeSelectMode();
	//int nNumSearch = CPlayerSelect::SELECTPLAYER_2P;//テスト

	int nNum = 0;
	for (int nCntCol = 0; nCntCol < m_nNumSearch; nCntCol++)
	{
		if (&m_SearchCol[nCntCol] != NULL && m_SearchCol[nCntCol] == col)
		{	// 色をデフォルトに戻す
			m_SearchCol[nCntCol] = COL_DEFAULT;
			nNum--;
		}
	}

	m_nNumSearch += nNum;		// 数を減らす
	if (m_nNumSearch < 0) { m_nNumSearch = 0; }

	for (int nCntCol = 0; nCntCol < nNumSearch; nCntCol++)
	{
		if (&m_SearchCol[nCntCol] != NULL && m_SearchCol[nCntCol] == COL_DEFAULT)
		{
			if (&m_SearchCol[nCntCol + 1] != NULL)
			{	// 色の入れ替え
				m_SearchCol[nCntCol] = m_SearchCol[nCntCol + 1];
				m_SearchCol[nCntCol + 1] = COL_DEFAULT;
			}
			else if (m_SearchCol[nCntCol + 1] == NULL) { m_SearchCol[nCntCol] = COL_DEFAULT; }	// 色をデフォルトに
		}
	}

}

//=============================================================================
//	点滅の処理
//=============================================================================
void CWord::FlashingCol(void)
{
	float fColA = 0.0f;
	if (m_nCntFlashing > FLASHING_TIME_MAX) { fColA = FLASHING_MAX; }
	else if (m_nCntFlashing > FLASHING_TIME_SMALL) { fColA = FLASHING_SMALL; }

	if (m_bFlashingFlag == false)
	{	// 不透明から透明
		m_col.a -= fColA;
		if (m_col.a < 0.4f) { m_col.a = 0.4f; m_bFlashingFlag = true; }
	}
	else if (m_bFlashingFlag == true)
	{	// 不透明から透明
		m_col.a += fColA;
		if (m_col.a > 1.0f) { m_col.a = 1.0f; m_bFlashingFlag = false; }
	}

	m_nCntFlashing++;

	if ((m_nCntFlashing % REST_TIME) == 0)
	{
		m_bRestFlag = true;
	}
}