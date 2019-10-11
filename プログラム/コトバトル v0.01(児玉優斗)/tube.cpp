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
	if (m_apWord[nNum] == NULL)
	{
		m_apWord[nNum] = CScene2D::Create(D3DXVECTOR3(WORD_TUBE_POS.x, (WORD_TUBE_POS.y + WORD_TUBE_SIZE.y - 80.0f) - (nNum * 65.0f), 0.0f), "WORD", 3);
		m_apWord[nNum]->SetWidthHeight(45.0f, 45.0f);	// サイズ設定
		m_apWord[nNum]->SetTex(D3DXVECTOR2(0.0f + ((nWordNum / 5) * 0.1f), 0.0f + ((nWordNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nWordNum / 5) * 0.1f), 0.2f + ((nWordNum % 5) * 0.2f)));
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
}

//=============================================================================
// 一部の文字を削除
//=============================================================================
void CTube::Delete(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD - 1; nCntWord++)
	{
		if (m_apWord[nCntWord] != NULL&& m_apWord[nCntWord + 1] != NULL)
		{
			int nNum = CGame::GetWordManager()->GetWordNum(nCntWord + 1);	// 数字を取得
			m_apWord[nCntWord]->SetTex(D3DXVECTOR2(0.0f + ((nNum / 5) * 0.1f), 0.0f + ((nNum % 5) * 0.2f)), D3DXVECTOR2(0.1f + ((nNum / 5) * 0.1f), 0.2f + ((nNum % 5) * 0.2f)));
		}
		else if (m_apWord[nCntWord] != NULL && m_apWord[nCntWord + 1] == NULL)
		{
			if (m_apWord[nCntWord] != NULL)
			{
				m_apWord[nCntWord]->Uninit();
				m_apWord[nCntWord] = NULL;
			}
		}
	}
}