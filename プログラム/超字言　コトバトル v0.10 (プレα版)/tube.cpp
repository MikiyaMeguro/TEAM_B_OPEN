//=============================================================================
//
// 文字保管のUI処理 [tube.h]
// Author : 目黒 未来也
//
//=============================================================================
#include "tube.h"
#include "manager.h"
#include "debugProc.h"
#include "input.h"
#include "scene2D.h"
#include "scene2D.h"
#include "game.h"
#include "PlayerNumSelect.h"
#include "point.h"
#include "tutorial.h"
//=============================================================================
// マクロ関数
//=============================================================================
#define WORD_POS		(CScene2D::GetPosition())			// 文字の位置
#define POS_ONE_001		(D3DXVECTOR3(WORD_POS.x - 122.0f, WORD_POS.y - 71.0f, 0.0f))		// 最初の位置
#define POS_TOW_001		(D3DXVECTOR3(WORD_POS.x - 53.0f, WORD_POS.y - 55.0f, 0.0f))		// 二つ目の位置
#define POS_THREE_001	(D3DXVECTOR3(WORD_POS.x - 10.0f, WORD_POS.y + 21.0f, 0.0f))		// 三つ目の位置

#define POS_ONE_002		(D3DXVECTOR3(WORD_POS.x - 82.0f, WORD_POS.y - 49.5f, 0.0f))		// 最初の位置
#define POS_TOW_002		(D3DXVECTOR3(WORD_POS.x - 35.0f, WORD_POS.y - 38.0f, 0.0f))		// 二つ目の位置
#define POS_THREE_002	(D3DXVECTOR3(WORD_POS.x - 7.0f, WORD_POS.y + 15.0f, 0.0f))		// 三つ目の位置

#define SIZE_000		(D3DXVECTOR2(43.0f, 57.0f))
#define SIZE_001		(D3DXVECTOR2(28.0f, 40.0f))

#define POS_ANSWER_001	(D3DXVECTOR3(WORD_POS.x - 93.0f, WORD_POS.y + 45.0f, 0.0f))		// 答えの位置
#define POS_ANSWER_STOCK_001	(D3DXVECTOR3(WORD_POS.x + 53.0f, WORD_POS.y + 72.0f, 0.0f))		// 答えの位置
#define SIZE_ANSWER_001	(D3DXVECTOR2(60.0f, 70.0f))										// 答えの位置
#define SIZE_ANSWER_STOCK_001	(D3DXVECTOR2(60.0f / 2, 70.0f / 2))										// 答えの位置


#define POS_ANSWER_002	(D3DXVECTOR3(WORD_POS.x - 62.0f, WORD_POS.y + 32.0f, 0.0f))		// 答えの位置
#define POS_ANSWER_STOCK_002	(D3DXVECTOR3(WORD_POS.x + 35.0f, WORD_POS.y + 51.0f, 0.0f))		// 三つ目の位置
#define SIZE_ANSWER_002	(D3DXVECTOR2(38.0f, 50.0f))										// 答えの位置
#define SIZE_ANSWER_STOCK_002	(D3DXVECTOR2(38.0f / 2, 48.0f / 2))										// 答えの位置

#define WHILE_1P		(70.0f)															// ストック2つ目との間
#define WHILE_2P		(47.0f)															// ストック2つ目との間

#define MOVE			(3.0f)
#define AREA			(2.0f * 2.0f)
#define WORD_SCALE		(0.5f)															// 文字が縮む速度
//=============================================================================
// シーンクラスのコンストラクタ
//=============================================================================
CTube::CTube(int nPriority, OBJTYPE objType) : CScene2D(nPriority, objType)
{
	// 値をクリア
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		m_apWord[nCntWord] = NULL;
		m_pAnswerModel[nCntWord] = NULL;
	}
	m_nAnswer = 0;
	m_bModelTexFlag = false;
	m_bCreateFlag = false;
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CTube *CTube::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag,int nPriority)
{
	CTube *pTube = NULL;

	if (pTube == NULL)
	{
		// オブジェクトクラスの生成
		pTube = new CTube(nPriority, OBJTYPE_SCENE2D);

		if (pTube != NULL)
		{
			pTube->Init(pos);
			pTube->SetWidthHeight(size.x, size.y);	// サイズ設定
			pTube->BindTexture(Tag);
		}
	}

	return pTube;
}

//=============================================================================
// デストラクタ
//=============================================================================
CTube::~CTube()
{
}

//=============================================================================
// ポリゴンの初期化処理
//=============================================================================
HRESULT CTube::Init(D3DXVECTOR3 pos)
{
	CScene2D::Init(pos);

	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (NumPlayer == 1) { m_AnswerPos = POS_ANSWER_001; }
	else if (NumPlayer != 1) { m_AnswerPos = POS_ANSWER_002; }

	return S_OK;
}

//=============================================================================
// ポリゴンの終了処理
//=============================================================================
void CTube::Uninit(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->Uninit();
			m_apWord[nCntWord] = NULL;
		}
	}

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_pAnswerModel[nCntWord] != NULL) { m_pAnswerModel[nCntWord]->Uninit(); m_pAnswerModel[nCntWord] = NULL; }
	}
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTube::Update(void)
{
	if (m_bModelTexFlag == true) { Collect(); }		// 中心点に集まる

	CScene2D::Update();
}

//=============================================================================
// ポリゴンの描画処理
//=============================================================================
void CTube::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 文字の番号設定の処理
//=============================================================================
void CTube::SetWordNum(int nWordNum, int nNum, int nStock)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR2 size = {};
	D3DXVECTOR3 StockPos = {};
	D3DXVECTOR2 StockSize = {};
	float fWhile = 0.0f;

	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (NumPlayer == 1)
	{	// 1人プレイの場合
		if (nNum == 0) { pos = POS_ONE_001; }
		else if (nNum == 1) { pos = POS_TOW_001; }
		else if (nNum == 2) { pos = POS_THREE_001; }
		size = SIZE_000;
		StockPos = POS_ANSWER_STOCK_001;
		StockSize = SIZE_ANSWER_STOCK_001;
		fWhile = WHILE_1P;
	}
	else if (NumPlayer != 1)
	{ // 1人プレイじゃない場合
		if (nNum == 0) { pos = POS_ONE_002; }
		else if (nNum == 1) { pos = POS_TOW_002; }
		else if (nNum == 2) { pos = POS_THREE_002; }
		size = SIZE_001;
		StockPos = POS_ANSWER_STOCK_002;
		StockSize = SIZE_ANSWER_STOCK_002;
		fWhile = WHILE_2P;
	}

	if (m_apWord[nNum] == NULL)
	{
		m_apWord[nNum] = CScene2D::Create(pos, "WORD", 3);
		m_apWord[nNum]->SetWidthHeight(size.x, size.y);	// サイズ設定
		m_apWord[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
	}

	if (nNum == 2)
	{
		m_bModelTexFlag = true;
		if (m_pAnswerModel[nStock] != NULL)
		{
			m_pAnswerModel[nStock]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			if (nStock == 1 || nStock == 2)
			{
				m_pAnswerModel[nStock]->SetWidthHeight(StockSize.x, StockSize.y);
				if (nStock == 1) { m_pAnswerModel[nStock]->SetPosition(StockPos); }
				else if (nStock == 2) { m_pAnswerModel[nStock]->SetPosition(D3DXVECTOR3(StockPos.x + fWhile, StockPos.y, StockPos.z)); }
			}
		}
	}
	else if (nNum < 2)
	{
		if (m_pAnswerModel[0] != NULL && nStock >= 1) { m_pAnswerModel[0]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f)); }
		SetAnswer(nWordNum, nStock);
	}
}

//=============================================================================
// 文字の番号設定の処理
//=============================================================================
void CTube::SetAnswer(int nAnswer, int nStock)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	m_nAnswerModelNum = nAnswer;

	if (m_pAnswerModel[nStock] == NULL)
	{	// 文字が3文字集まった場合場合
		D3DXVECTOR2 AnswerSize = {};
		//int nAnswerNum = 
		if (NumPlayer == 1)
		{	// 1人プレイの場合
			m_AnswerPos = POS_ANSWER_001;
			AnswerSize = SIZE_ANSWER_001;
		}
		else if (NumPlayer != 1)
		{	// 1人プレイじゃない場合
			m_AnswerPos = POS_ANSWER_002;
			AnswerSize = SIZE_ANSWER_002;
		}

		//	文字で作れるモデルをまとめた画像に変える
		m_pAnswerModel[nStock] = CScene2D::Create(m_AnswerPos, "WORD", 3);
		m_pAnswerModel[nStock]->SetWidthHeight(AnswerSize.x, AnswerSize.y);	// サイズ設定
		m_pAnswerModel[nStock]->SetTex(D3DXVECTOR2(0.0f + ((nAnswer / 5) * 0.1f), 0.0f + ((nAnswer % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nAnswer / 5) * 0.1f), 0.2f + ((nAnswer % 5) * 0.2f)));
	}
}
//=============================================================================
// 全ての文字を削除
//=============================================================================
void CTube::AllDelete(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->Uninit();
			m_apWord[nCntWord] = NULL;
		}
	}

	int nCount = 0;
	for (int nCntAnswerModel = 0; nCntAnswerModel < MAX_WORD - 1; nCntAnswerModel++)
	{
		if (m_pAnswerModel[nCntAnswerModel] != NULL && m_pAnswerModel[nCntAnswerModel + 1] != NULL)
		{
			m_pAnswerModel[nCntAnswerModel]->BindTexture(m_pAnswerModel[nCntAnswerModel + 1]->GetTexture());
			m_pAnswerModel[nCntAnswerModel]->SetTex(m_pAnswerModel[nCntAnswerModel + 1]->GetTex(0), m_pAnswerModel[nCntAnswerModel + 1]->GetTex(1));
			nCount++;
		}
	}

	if (m_pAnswerModel[nCount] != NULL) { m_pAnswerModel[nCount]->Uninit(); m_pAnswerModel[nCount] = NULL; }
}

//=============================================================================
// 一部の文字を削除
//=============================================================================
void CTube::Delete(int nID, int nStock)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD - 1; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL&& m_apWord[nCntWord + 1] != NULL)
		{
			int nNum = 0;
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				nNum = CGame::GetPlayer(nID)->GetWordManager()->GetWordNum(nCntWord + 1);	// 数字を取得
			}
			else if (CManager::GetMode() == CManager::MODE_TUTORIAL)
			{
				nNum = CTutorial::GetPlayer(nID)->GetWordManager()->GetWordNum(nCntWord + 1);	// 数字を取得
			}
			m_apWord[nCntWord]->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));

			if (m_pAnswerModel[nStock] != NULL)
			{
				m_pAnswerModel[nStock]->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));
			}
		}


		else if (m_apWord[nCntWord] != NULL && m_apWord[nCntWord + 1] == NULL)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				m_apWord[nCntWord]->Uninit();
				m_apWord[nCntWord] = NULL;
			}
		}

		if (m_apWord[0] == NULL)
		{
			if (m_pAnswerModel[nStock] != NULL)
			{
				m_pAnswerModel[nStock]->Uninit();
				m_pAnswerModel[nStock] = NULL;
			}
		}
	}

	for (int nCntAnswerModel = 0; nCntAnswerModel < MAX_WORD; nCntAnswerModel++)
	{
		if (m_pAnswerModel[nCntAnswerModel] != NULL) { m_pAnswerModel[nCntAnswerModel]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
		else if (m_pAnswerModel[nCntAnswerModel] == NULL) { break; }
	}
}

//=============================================================================
// 文字をある位置に集めてTexを生成
//=============================================================================
void CTube::Collect(void)
{
	int nCntNum = 0;
	m_bCreateFlag = true;

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			m_apWord[nCntWord]->SetWidthHeight(m_apWord[nCntWord]->GetSize(0) - WORD_SCALE, m_apWord[nCntWord]->GetSize(1) - WORD_SCALE);
			Approach(m_apWord[nCntWord]->GetPosition(), m_AnswerPos, nCntWord);
		}
		else if (m_apWord[nCntNum] == NULL) { nCntNum++; }
	}

	if (nCntNum == MAX_WORD)
	{
		m_bModelTexFlag = false;

		if (m_pAnswerModel[m_nStockNum] != NULL)
		{
			if (NOT_NUM == m_nAnswerModelNum)
			{	// ゴミモデルのtexを出す
				m_pAnswerModel[m_nStockNum]->BindTexture("ゴミ_モデル");
				m_pAnswerModel[m_nStockNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
			}
			else if (NOT_NUM != m_nAnswerModelNum)
			{	// 正解のモデルを出す
				m_pAnswerModel[m_nStockNum]->BindTexture("モデル_TEX");
				m_pAnswerModel[m_nStockNum]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * 0.125f), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
					D3DXVECTOR2(0.125f + ((m_nAnswerModelNum / 10) * 0.125f), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
			}

			for (int nCntModel = 0; nCntModel < MAX_WORD; nCntModel++)
			{
				if (m_pAnswerModel[nCntModel] != NULL)
				{
					m_pAnswerModel[nCntModel]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}
		}

		m_bCreateFlag = false;
	}
}

//=============================================================================
// プレイヤーに集まるの処理
//=============================================================================
void CTube::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// プレイヤーに近づける
	move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.y - Pos.y)) * MOVE;
	move.y = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.y - Pos.y)) * MOVE;

	if (m_apWord[nNum] != NULL)
	{
		Pos.x += move.x;
		Pos.y += move.y;

		// 範囲を測る
		float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

		m_apWord[nNum]->SetPosition(Pos);

		// 範囲内なら破棄 Flagを戻す
		if (fDistance < AREA)
		{	// 距離内に入ったら
			if (m_apWord[nNum] != NULL)
			{
				m_apWord[nNum]->Uninit();
				m_apWord[nNum] = NULL;
			}
		}

	}
}

//=============================================================================
// ポイントの処理
//=============================================================================
void CTube::SetPoint(int nPoint, int nNum, bool bPoint)
{
	CPoint *pPoint = NULL;
	if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(nNum); }
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* チュートリアルの作業によりかかった場合 ここでチュートリアルからポイントを取得 */ }

	if (pPoint != NULL)
	{
		if (bPoint == false) { pPoint->AddPoint(nPoint); }
		else if (bPoint == true) { pPoint->SubtractionPoint(nPoint); }
	}
}

