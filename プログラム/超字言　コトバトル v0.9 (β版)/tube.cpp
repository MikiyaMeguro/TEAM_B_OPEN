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
#define AREA_STAR		(5.0f * 5.0f)

#define WORD_SCALE		(0.5f)															// 文字が縮む速度
#define STAR_POS		(D3DXVECTOR3(640.0f, 300.0f, 0.0f))
#define UNINIT_TIME		(15 * 60)															// 文字取得後終了するまでのフレーム
#define FLASHING_TIME	(8 * 60)															// 文字取得後終了するまでのフレーム
#define FLASHING_TIME_SECOND	(12 * 60)															// 文字取得後終了するまでのフレーム
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
		m_pShootingStar[nCntWord] = NULL;
		m_anAnswerNum[nCntWord] = 0;
	}

	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_sizeAnswer = D3DXVECTOR2(0.0f, 0.0f);
	m_nAnswer = 0;
	m_nStockNum = 0;
	m_nAnswerModelNum = 0;
	m_nCntUninit = 0;
	m_bModelTexFlag = false;
	m_bCreateFlag = false;
	m_bTowardFlag = false;
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

	if (NumPlayer == 1) { m_AnswerPos = POS_ANSWER_001; m_size = SIZE_000; }
	else if (NumPlayer != 1) { m_AnswerPos = POS_ANSWER_002; m_size = SIZE_001; }

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

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_pShootingStar[nCntWord] != NULL) { m_pShootingStar[nCntWord]->Uninit(); m_pShootingStar[nCntWord] = NULL; }
	}
	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTube::Update(void)
{
	if (m_bModelTexFlag == true) { Collect(); }		// 中心点に集まる

	Toward();

	WordCreate2D();

	if (m_bSizeFlag == true)
	{	// サイズ変更
		if (m_pAnswerModel[m_nStockNum] != NULL)
		{
			D3DXVECTOR2 size = D3DXVECTOR2(m_pAnswerModel[m_nStockNum]->GetSize(0), m_pAnswerModel[m_nStockNum]->GetSize(1));
			SizeChange(size);
		}
	}

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
	D3DXVECTOR3 ToWardPos = {};
	float fWhile = 0.0f;
	//m_anAnswerNum[nNum] = nWordNum;

	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (m_bCreateFlag == true)
	{
		UninitChack(true);		// 終了しているかどうかの確認
	}

	if (NumPlayer == 1)
	{	// 1人プレイの場合
		if (nNum == 0) { pos = POS_ONE_001; }
		else if (nNum == 1) { pos = POS_TOW_001; }
		else if (nNum == 2) { pos = POS_THREE_001; }
		ToWardPos = STAR_POS;
		if (nNum == 2)
		{
			m_sizeAnswer = SIZE_ANSWER_STOCK_001;
		}
	}
	else if (NumPlayer != 1)
	{ // 1人プレイじゃない場合
		if (nNum == 0) { pos = POS_ONE_002; }
		else if (nNum == 1) { pos = POS_TOW_002; }
		else if (nNum == 2) { pos = POS_THREE_002; }

		if (nNum == 2)
		{
			m_sizeAnswer = SIZE_ANSWER_STOCK_002;
		}
	}

	if(NumPlayer == 2)
	{
		if (m_nID == 0) { ToWardPos = D3DXVECTOR3(640.0f, 150.0f, 0.0f); }
		else if (m_nID == 1) { ToWardPos = D3DXVECTOR3(640.0f, 550.0f, 0.0f); }
	}
	else if (NumPlayer == 3 || NumPlayer == 4)
	{
		if (m_nID == 0) { ToWardPos = D3DXVECTOR3(340.0f, 150.0f, 0.0f); }
		if (m_nID == 1) { ToWardPos = D3DXVECTOR3(940.0f, 150.0f, 0.0f); }
		if (m_nID == 2) { ToWardPos = D3DXVECTOR3(340.0f, 550.0f, 0.0f); }
		if (m_nID == 3) { ToWardPos = D3DXVECTOR3(940.0f, 550.0f, 0.0f); }
	}



	if (m_apWord[nNum] == NULL)
	{
		m_apWord[nNum] = CScene2D::Create(pos, "WORD", 3);
		m_apWord[nNum]->SetWidthHeight(0.0f, 0.0f);	// サイズ設定
		m_apWord[nNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_apWord[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
	}

	if (m_pShootingStar[nNum] == NULL)
	{
		m_pShootingStar[nNum] = CScene2D::Create(ToWardPos, "WORD", 3);
		m_pShootingStar[nNum]->SetWidthHeight(0.0f, 0.0f);	// サイズ設定
		m_pShootingStar[nNum]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pShootingStar[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
	}

	if (nNum == 2)
	{
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				 m_apWord[nCntWord]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); 
			}
		}

		m_bCreateFlag = true;
		//m_bModelTexFlag = true;
	}
}

//=============================================================================
// 文字の番号設定の処理
//=============================================================================
void CTube::SetAnswer(int nAnswer, int nStock)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	D3DXVECTOR3 StockPos = {};
	float fWhile = 0.0f;
	m_nAnswerModelNum = nAnswer;

	if (NumPlayer == 1)
	{	// 1人プレイの場合
		StockPos = POS_ANSWER_STOCK_001;
		fWhile = WHILE_1P;
	}
	else if (NumPlayer != 1)
	{ // 1人プレイじゃない場合
		StockPos = POS_ANSWER_STOCK_002;
		fWhile = WHILE_2P;
	}

	if (m_pAnswerModel[nStock] == NULL)
	{	// 文字が3文字集まった場合場合
		D3DXVECTOR2 AnswerSize = {};
		//int nAnswerNum =
		if (NumPlayer == 1)
		{	// 1人プレイの場合
			m_AnswerPos = POS_ANSWER_001;
			if (nStock == 0)
			{
				m_sizeAnswer = SIZE_ANSWER_001;
			}
		}
		else if (NumPlayer != 1)
		{	// 1人プレイじゃない場合
			m_AnswerPos = POS_ANSWER_002;
			if (nStock == 0)
			{
				m_sizeAnswer = SIZE_ANSWER_002;
			}
		}

		if (NOT_NUM == m_nAnswerModelNum)
		{	// ゴミモデルのtexを出す
			m_pAnswerModel[nStock] = CScene2D::Create(m_AnswerPos, "ゴミ_モデル", 3);
			m_pAnswerModel[nStock]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
		else if (NOT_NUM != m_nAnswerModelNum)
		{	// 正解のモデルを出す
			m_pAnswerModel[nStock] = CScene2D::Create(m_AnswerPos, "モデル_TEX", 3);
			m_pAnswerModel[nStock]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * (1.0f / 12.0f)), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
						D3DXVECTOR2((1.0f / 12.0f) + ((m_nAnswerModelNum / 10) * (1.0f / 12.0f)), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
		}
		//	文字で作れるモデルをまとめた画像に変える
		m_pAnswerModel[nStock]->SetWidthHeight(0.0f, 0.0f);	// サイズ設定
		m_pAnswerModel[nStock]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	if (m_pAnswerModel[nStock] != NULL)
	{
		if (nStock == 1 || nStock == 2)
		{
			m_pAnswerModel[nStock]->SetWidthHeight(0.0f, 0.0f);
			if (nStock == 1) { m_pAnswerModel[nStock]->SetPosition(StockPos); }
			else if (nStock == 2) { m_pAnswerModel[nStock]->SetPosition(D3DXVECTOR3(StockPos.x + fWhile, StockPos.y, StockPos.z)); }
		}
	}
}
//=============================================================================
// 全ての文字を削除
//=============================================================================
void CTube::AllDelete(int nNum)
{
	for (int nCntWord = nNum; nCntWord < MAX_WORD; nCntWord++)
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
// 文字をある位置に集めてTexを生成
//=============================================================================
void CTube::Collect(void)
{
	int nCntNum = 0;

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			if (m_apWord[nCntWord]->GetCol() != D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)) { m_apWord[nCntWord]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)); }
			m_apWord[nCntWord]->SetWidthHeight(m_apWord[nCntWord]->GetSize(0) - WORD_SCALE, m_apWord[nCntWord]->GetSize(1) - WORD_SCALE);
			Approach(m_apWord[nCntWord]->GetPosition(), m_AnswerPos, nCntWord);
		}
		else if (m_apWord[nCntNum] == NULL) { nCntNum++; }
	}

	if (nCntNum == MAX_WORD)
	{
		if (m_pAnswerModel[m_nStockNum] != NULL)
		{
			D3DXVECTOR2 size = D3DXVECTOR2(m_pAnswerModel[m_nStockNum]->GetSize(0), m_pAnswerModel[m_nStockNum]->GetSize(1));

			//if (NOT_NUM == m_nAnswerModelNum)
			//{	// ゴミモデルのtexを出す
			//	m_pAnswerModel[m_nStockNum]->BindTexture("ゴミ_モデル");
			//	m_pAnswerModel[m_nStockNum]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
			//}
			//else if (NOT_NUM != m_nAnswerModelNum)
			//{	// 正解のモデルを出す
			//	m_pAnswerModel[m_nStockNum]->BindTexture("モデル_TEX");
			//	m_pAnswerModel[m_nStockNum]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * 0.125f), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
			//		D3DXVECTOR2(0.125f + ((m_nAnswerModelNum / 10) * 0.125f), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
			//}

			for (int nCntModel = 0; nCntModel < MAX_WORD; nCntModel++)
			{
				if (m_pAnswerModel[nCntModel] != NULL)
				{
					m_pAnswerModel[nCntModel]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				}
			}

			SizeChange(size);	// サイズの変化
		}
	}

	m_nCntUninit = 0;
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
	CSound *pSound = CManager::GetSound();		//	音の取得
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();


	CPoint *pPoint = NULL;
	if (CManager::GetMode() == CManager::MODE_GAME) { pPoint = CGame::GetPoint(nNum); }
	else if (CManager::GetMode() == CManager::MODE_TUTORIAL) { /* チュートリアルの作業によりかかった場合 ここでチュートリアルからポイントを取得 */ }

	//m_bSizeFlag = false;	// サイズ変更のフラグをfalseに

	if (pPoint != NULL)
	{
		if (bPoint == false) { pPoint->AddPoint(nPoint);
		pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTUP, 3.0f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTUP);
		}
		else if (bPoint == true) { pPoint->SubtractionPoint(nPoint);
		pSound->SetVolume(CSound::SOUND_LABEL_SE_POINTDOWN, 3.0f);
		pSound->PlaySound(CSound::SOUND_LABEL_SE_POINTDOWN);
		}
	}
}

//=============================================================================
// 終了いてるかどうかの確認処理
//=============================================================================
void CTube::UninitChack(bool bFlag)
{
	if (bFlag == true)
	{	// フラグがtrueなら文字を破棄
		m_bSizeFlag = true;
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				m_apWord[nCntWord]->Uninit();
				m_apWord[nCntWord] = NULL;
			}
		}
	}

	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_pShootingStar[nCntWord] != NULL) { m_pShootingStar[nCntWord]->Uninit(); m_pShootingStar[nCntWord] = NULL; }
	}

	m_bModelTexFlag = false;
	int nCount = 0;

	for (int nCntTex = 0; nCntTex < m_nStockNum; nCntTex++)
	{
		if (m_pAnswerModel[nCntTex] != NULL) { nCount++; }
		else if (m_pAnswerModel[nCntTex] == NULL) { break; }
	}

	if (m_pAnswerModel[nCount] != NULL)
	{
		//if (NOT_NUM == m_nAnswerModelNum)
		//{	// ゴミモデルのtexを出す
		//	m_pAnswerModel[nCount]->BindTexture("ゴミ_モデル");
		//	m_pAnswerModel[nCount]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		//}
		//else if (NOT_NUM != m_nAnswerModelNum)
		//{	// 正解のモデルを出す
		//	m_pAnswerModel[nCount]->BindTexture("モデル_TEX");
		//	m_pAnswerModel[nCount]->SetTex(D3DXVECTOR2(0.0f + ((m_nAnswerModelNum / 10) * 0.125f), 0.0f + ((m_nAnswerModelNum % 10) * 0.1f)),
		//		D3DXVECTOR2(0.125f + ((m_nAnswerModelNum / 10) * 0.125f), 0.1f + ((m_nAnswerModelNum % 10) * 0.1f)));
		//}

		for (int nCntModel = 0; nCntModel < MAX_WORD; nCntModel++)
		{
			if (m_pAnswerModel[nCntModel] != NULL)
			{
				m_pAnswerModel[nCntModel]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}

		//m_pAnswerModel[m_nStockNum]->SetWidthHeight(m_sizeAnswer.x, m_sizeAnswer.y);

		if (m_nAnswerModelNum != NOT_NUM)
		{
			int nCntSound = 0;
			nCntSound = m_nAnswerModelNum + (int)CSound::SOUND_LABEL_WORDVOICE_KURUMA;	// 車のボイスから

			CManager::GetSound()->SetVolume((CSound::SOUND_LABEL)nCntSound, 5.0f);
			CManager::GetSound()->PlaySoundA((CSound::SOUND_LABEL)nCntSound);
		}
	}

	m_nAnswerModelNum = 0;
	m_nCntUninit = 0;
	m_bCreateFlag = false;
}

//=============================================================================
// 目的の場所に向かう処理
//=============================================================================
void CTube::Toward(void)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	float fMove = 0.0f;

	if (NumPlayer == 1) { fMove = 12.0f; }
	else if (NumPlayer != 1) { fMove = 10.0f; }


	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL && m_pShootingStar[nCntWord] != NULL)
		{
			float fDistance = 0.0f;
			float fRot = m_pShootingStar[nCntWord]->GetRot();
			D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			D3DXVECTOR3 pos = m_pShootingStar[nCntWord]->GetPosition();
			D3DXVECTOR2 size = D3DXVECTOR2(m_pShootingStar[nCntWord]->GetSize(0), m_pShootingStar[nCntWord]->GetSize(1));

			// 移動方向調整
			pos.y -= 3.0f;

			// 向き加算
			//fRot += 0.1f;

			// 目的地と自身の位置を測る
			move.x = sinf(atan2f(m_apWord[nCntWord]->GetPosition().x - m_pShootingStar[nCntWord]->GetPosition().x, m_apWord[nCntWord]->GetPosition().y - m_pShootingStar[nCntWord]->GetPosition().y)) * fMove;
			move.y = cosf(atan2f(m_apWord[nCntWord]->GetPosition().x - m_pShootingStar[nCntWord]->GetPosition().x, m_apWord[nCntWord]->GetPosition().y - m_pShootingStar[nCntWord]->GetPosition().y)) * fMove;

			pos += move;

			// サイズ調整
			size.x += 1.0f;
			size.y += 1.0f;

			// 位置とサイズ, 向き設定
			m_pShootingStar[nCntWord]->SetPosition(pos);
			m_pShootingStar[nCntWord]->SetWidthHeight(size.x, size.y);
			//m_pShootingStar[nCntWord]->SetRot(fRot);

			// 目的地の範囲に入ったら削除
			fDistance = sqrtf((m_pShootingStar[nCntWord]->GetPosition().x - m_apWord[nCntWord]->GetPosition().x)* (m_pShootingStar[nCntWord]->GetPosition().x - m_apWord[nCntWord]->GetPosition().x) +
				(m_pShootingStar[nCntWord]->GetPosition().z - m_apWord[nCntWord]->GetPosition().z)*(m_pShootingStar[nCntWord]->GetPosition().z - m_apWord[nCntWord]->GetPosition().z));


			// 範囲内にはいったら削除
			if (fDistance < AREA_STAR)
			{
				if (m_pShootingStar[nCntWord] != NULL) { m_pShootingStar[nCntWord]->Uninit(); m_pShootingStar[nCntWord] = NULL; }
			}
		}
	}
}

//=============================================================================
// 文字の表示2D処理
//=============================================================================
void CTube::WordCreate2D(void)
{
	int nCount = 0;
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL && m_pShootingStar[nCntWord] == NULL)
		{
			D3DXVECTOR2 size = D3DXVECTOR2(m_apWord[nCntWord]->GetSize(0), m_apWord[nCntWord]->GetSize(1));
			// サイズを拡大
			size.x += 2.14f;
			size.y += 2.38f;

			// 指定したサイズ以上の場合
			if (size.x > m_size.x ) { size.x = m_size.x; }
			if (size.y > m_size.y) { size.y = m_size.y; }

			if (size.x >= m_size.x && size.y >= m_size.y)
			{
				nCount++;
			}

			m_apWord[nCntWord]->SetWidthHeight(size.x, size.y);
		}
	}

	if (nCount == MAX_WORD) { m_bModelTexFlag = true; }		// 中心点に集まる
	else if (nCount == MAX_WORD - 1) { WordUninit(); }
}

//=============================================================================
// サイズ変化の処理
//=============================================================================
void CTube::SizeChange(D3DXVECTOR2 size)
{
	// サイズを拡大
	size.x += 2.14f;
	size.y += 2.38f;

	// 指定したサイズ以上の場合
	if (size.x > m_sizeAnswer.x) { size.x = m_sizeAnswer.x; }
	if (size.y > m_sizeAnswer.y) { size.y = m_sizeAnswer.y; }

	if (size.x >= m_sizeAnswer.x && size.y >= m_sizeAnswer.y)
	{
		if (m_bModelTexFlag == true && m_nAnswerModelNum != NOT_NUM)
		{
			int nCntSound = 0;
			nCntSound = m_nAnswerModelNum + (int)CSound::SOUND_LABEL_WORDVOICE_KURUMA;	// 車のボイスから

			CManager::GetSound()->SetVolume((CSound::SOUND_LABEL)nCntSound, 5.0f);
			CManager::GetSound()->PlaySoundA((CSound::SOUND_LABEL)nCntSound);
		}
		m_bModelTexFlag = false;
		m_bCreateFlag = false;
		m_bSizeFlag = false;

		m_nAnswerModelNum = 0;
	}

	if (m_pAnswerModel[m_nStockNum] != NULL)
	{
		m_pAnswerModel[m_nStockNum]->SetWidthHeight(size.x, size.y);
	}
}

//=============================================================================
// 文字取得後、終了するまでの時間
//=============================================================================
void CTube::WordUninit(void)
{
	// カウントを回す
	m_nCntUninit++;

	// カウントが指定した値以上の場合
	if (m_nCntUninit > FLASHING_TIME && m_nCntUninit < FLASHING_TIME_SECOND)
	{	// 点滅処理
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				D3DXCOLOR fCol = m_apWord[nCntWord]->GetCol();

				if (fCol.a > 0.3f) { fCol.a -= 0.05f; }
				else { fCol.a = 1.0f; }
				m_apWord[nCntWord]->SetCol(fCol);
			}
		}
	}
	else if (m_nCntUninit >= FLASHING_TIME_SECOND && m_nCntUninit < UNINIT_TIME)
	{	// 点滅処理
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				D3DXCOLOR fCol = m_apWord[nCntWord]->GetCol();

				if (fCol.a > 0.3f) { fCol.a -= 0.2f; }
				else { fCol.a = 1.0f; }
				m_apWord[nCntWord]->SetCol(fCol);
			}
		}
	}
	if ((m_nCntUninit % UNINIT_TIME) == 0)
	{	// 持っている文字を破棄する
		for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
		{
			if (m_apWord[nCntWord] != NULL) { m_apWord[nCntWord]->Uninit(); m_apWord[nCntWord] = NULL; }
		}
		m_nCntUninit = 0;

		CManager::GetPlayer(m_nID)->GetWordManager()->WordReset();
	}
}