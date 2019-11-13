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
//=============================================================================
// マクロ関数
//=============================================================================
#define WORD_POS	(CScene2D::GetPosition())			// 文字の位置
#define POS_ONE_001		(D3DXVECTOR3(WORD_POS.x - 69.0f, WORD_POS.y - 70.0f, 0.0f))		// 最初の位置
#define POS_TOW_001		(D3DXVECTOR3(WORD_POS.x + 29.0f, WORD_POS.y - 41.0f, 0.0f))		// 二つ目の位置
#define POS_THREE_001	(D3DXVECTOR3(WORD_POS.x + 54.0f, WORD_POS.y + 64.0f, 0.0f))		// 三つ目の位置

#define POS_ONE_002		(D3DXVECTOR3(WORD_POS.x - 46.0f, WORD_POS.y - 52.5f, 0.0f))		// 最初の位置
#define POS_TOW_002		(D3DXVECTOR3(WORD_POS.x + 19.0f, WORD_POS.y - 31.0f, 0.0f))		// 二つ目の位置
#define POS_THREE_002	(D3DXVECTOR3(WORD_POS.x + 36.0f, WORD_POS.y + 48.0f, 0.0f))		// 三つ目の位置

#define SIZE_000	(D3DXVECTOR2(47.0f, 54.0f))
#define SIZE_001	(D3DXVECTOR2(30.0f, 40.0f))

#define POS_ANSWER_001	(D3DXVECTOR3(WORD_POS.x - 50.0f, WORD_POS.y + 44.0f, 0.0f))		// 答えの位置
#define SIZE_ANSWER_001	(D3DXVECTOR2(60.0f, 70.0f))		// 答えの位置

#define POS_ANSWER_002	(D3DXVECTOR3(WORD_POS.x - 32.0f, WORD_POS.y + 32.0f, 0.0f))		// 答えの位置
#define SIZE_ANSWER_002	(D3DXVECTOR2(47.0f, 60.0f))		// 答えの位置

#define MOVE			(3.0f)
//=============================================================================
// シーンクラスのコンストラクタ
//=============================================================================
CTube::CTube(int nPriority, OBJTYPE objType) : CScene2D(nPriority, objType)
{
	// 値をクリア
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		m_apWord[nCntWord] = NULL;
	}
	m_pAnswerModel = NULL;
	m_nAnswer = 0;
	m_bModelTexFlag = false;
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

	if (m_pAnswerModel != NULL) { m_pAnswerModel->Uninit(); m_pAnswerModel = NULL; }

	CScene2D::Uninit();
}

//=============================================================================
// ポリゴンの更新処理
//=============================================================================
void CTube::Update(void)
{
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
void CTube::SetWordNum(int nWordNum, int nNum)
{
	D3DXVECTOR3 pos = {};
	D3DXVECTOR2 size = {};
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (NumPlayer == 1)
	{	// 1人プレイの場合
		if (nNum == 0) { pos = POS_ONE_001; }
		else if (nNum == 1) { pos = POS_TOW_001; }
		else if (nNum == 2) { pos = POS_THREE_001; }
		size = SIZE_000;
	}
	else if (NumPlayer != 1)
	{ // 1人プレイじゃない場合
		if (nNum == 0) { pos = POS_ONE_002; }
		else if (nNum == 1) { pos = POS_TOW_002; }
		else if (nNum == 2) { pos = POS_THREE_002; }
		size = SIZE_001;
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
		/*for (int nCntNum = 0; nCntNum < MAX_WORD; nCntNum++)
		{
			if (m_apWord[nCntNum] != NULL)
			{
				m_apWord[nCntNum]->SetCol(D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f));
			}
		}*/
	}
	else if (nNum < 2)
	{
		SetAnswer(nWordNum);
	}
}

//=============================================================================
// 文字の番号設定の処理
//=============================================================================
void CTube::SetAnswer(int nAnswer)
{
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();

	if (m_pAnswerModel == NULL)
	{	// 文字が3文字集まった場合場合
		D3DXVECTOR3 AnswerPos = {};
		D3DXVECTOR2 AnswerSize = {};
		//int nAnswerNum = 
		if (NumPlayer == 1)
		{	// 1人プレイの場合
			AnswerPos = POS_ANSWER_001;
			AnswerSize = SIZE_ANSWER_001;
		}
		else if (NumPlayer != 1)
		{	// 1人プレイじゃない場合
			AnswerPos = POS_ANSWER_002;
			AnswerSize = SIZE_ANSWER_002;
		}

		//	文字で作れるモデルをまとめた画像に変える
		m_pAnswerModel = CScene2D::Create(AnswerPos, "WORD", 3);
		m_pAnswerModel->SetWidthHeight(AnswerSize.x, AnswerSize.y);	// サイズ設定
		m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f + ((nAnswer / 5) * 0.1f), 0.0f + ((nAnswer % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nAnswer / 5) * 0.1f), 0.2f + ((nAnswer % 5) * 0.2f)));
	}
	else if (m_pAnswerModel != NULL)
	{
		if (NOT_NUM == nAnswer)
		{
			m_pAnswerModel->BindTexture("ゴミ_モデル");
			m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 1.0f));
		}
		else if(NOT_NUM != nAnswer)
		{
			m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f + ((nAnswer / 5) * 0.1f), 0.0f + ((nAnswer % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nAnswer / 5) * 0.1f), 0.2f + ((nAnswer % 5) * 0.2f)));
		}
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

	if (m_pAnswerModel != NULL) { m_pAnswerModel->Uninit(); m_pAnswerModel = NULL; }
}

//=============================================================================
// 一部の文字を削除
//=============================================================================
void CTube::Delete(int nID)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD - 1; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL&& m_apWord[nCntWord + 1] != NULL)
		{
			int nNum = CGame::GetPlayer(nID)->GetWordManager()->GetWordNum(nCntWord + 1);	// 数字を取得
			m_apWord[nCntWord]->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));

			if (m_pAnswerModel != NULL)
			{
				m_pAnswerModel->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));
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
			if (m_pAnswerModel != NULL)
			{
				m_pAnswerModel->Uninit();
				m_pAnswerModel = NULL;
			}
		}
	}
}

//=============================================================================
// 文字をある位置に集めてTexを生成
//=============================================================================
void CTube::Collect(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL)
		{
			//Approach(m_apWord[nCntWord]->GetPosition, );
		}
	}
}

//=============================================================================
// プレイヤーに集まるの処理
//=============================================================================
D3DXVECTOR3 CTube::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// プレイヤーに近づける
	move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * MOVE;
	move.z = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * MOVE;

	return move;
}
