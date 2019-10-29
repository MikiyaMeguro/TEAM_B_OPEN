//=============================================================================
//
// 文字の管理処理 [word_manager.cpp]
// Author : 横道 駿
//
//=============================================================================
#include "word_manager.h"
#include "input.h"
#include "InputKeyboard.h"
#include "manager.h"
#include "sceneX.h"
#include "debugProc.h"
#include "game.h"

#include "bullet.h"
#include "CameraManager.h"
//=============================================================================
// 静的メンバ変数
//=============================================================================
D3DXVECTOR3 *CWordManager::m_AnswerNum = &D3DXVECTOR3(99.0f, 99.0f, 99.0f);
int CWordManager::m_nAnswerDataNum = 0;
//=============================================================================
// コンストラクタ
//=============================================================================
CWordManager::CWordManager()
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{	// 管理の中身を初期化
		m_aWord[nCntWord].nNum = 99;
		m_aWord[nCntWord].cWord = "NULL";
		m_aWord[nCntWord].bClearFlag = false;
	}
	m_nCntNum = 0;			// 回数のカウント
	m_nCreateType = 0;		// 生成するタイプ
	m_nCntaAnswer = 0;		// 正解との比較して合っている数
	m_nPlayerID = 0;		// プレイヤーが何番かの保存
	m_bPress = false;		// 指定した文字以上をいれないフラグ
	m_bSearch = false;		// サーチを開始する時のフラグ

}
//=============================================================================
// デストラクタ
//=============================================================================
CWordManager::~CWordManager() {}

//=============================================================================
// 初期化処理
//=============================================================================
void CWordManager::Init()
{

}

//=============================================================================
// 終了処理
//=============================================================================
void CWordManager::Uninit(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CWordManager::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	CreateOblDebug();		// 数字で文字の管理(デバック用)

	if (m_nCntNum == MAX_WORD)
	{	// 最大ならこれ以上数字をいれない
		m_bPress = true;
	}

	if (m_bPress == true)
	{
		if (m_nCntaAnswer == 0)
		{
			for (int nCntAnswer = 0; nCntAnswer < MAX_ANSWER; nCntAnswer++)
			{	// 答えの数だけ回す
				for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
				{	// 答との比較
					if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; }
					else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; }
					else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; }
				}

				if (m_bAnswer[0] == true && m_bAnswer[1] == true && m_bAnswer[2] == true) { m_nCntaAnswer = MAX_WORD; }
				else if (m_nCntaAnswer < MAX_WORD)
				{
					for (int nCount = 0; nCount < MAX_WORD; nCount++)
					{
						m_bAnswer[nCount] = false;
					}
				}

				if (m_nCntaAnswer == MAX_WORD) { m_nCreateType = nCntAnswer; return; }
				else { m_nCntaAnswer = 0; }
			}
		}

		//テスト
		//if (pInputKeyboard->GetTrigger(DIK_LSHIFT))
		//{	// 弾の生成
		//	BulletCreate(0);
		//}
	}

	if (m_nCntNum != 2 && m_bSearch == true)
	{ // 持っている文字が2文字以外ならサーチのフラグを変更
		m_bSearch = false;
		delete m_fAnswerData;
		*m_fAnswerData = 99.0f;		// 空の番号をいれる
	}

#ifdef _DEBUG
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		CDebugProc::Print("cc", "m_aWord = ", m_aWord[nCntWord].cWord);
	}
#endif
}

//=============================================================================
// 設定処理
//=============================================================================
void CWordManager::SetWord(int nType)
{
	if (m_nCntNum < MAX_WORD)
	{
		m_aWord[m_nCntNum].nNum = nType;
		WordDebug(m_nCntNum);
		if (CGame::GetTube(m_nPlayerID) != NULL)
		{	// NULLチェック
			CGame::GetTube(m_nPlayerID)->SetWordNum(nType, m_nCntNum);
		}
		m_nCntNum++;
	}
}

//=============================================================================
// リセット関数
//=============================================================================
void CWordManager::Reset(void)
{
	for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
	{
		m_aWord[nCntWord].nNum = 99;
		m_aWord[nCntWord].cWord = "NULL";
	}

	for (int nCount = 0; nCount < MAX_WORD; nCount++)
	{
		m_bAnswer[nCount] = false;
	}

	m_nCntaAnswer = 0;
	m_nCntNum = 0;
	m_bPress = false;
}

//=============================================================================
// 文字の削除
//=============================================================================
void CWordManager::Delete(void)
{
	//if (CManager::GetInputKeyboard()->GetTrigger(DIK_LCONTROL))
	{
		if (m_nCntNum < 3)
		{	// 3つ以下の場合
			if (m_nCntNum > 0)
			{
				m_nCntNum--;
				if (CGame::GetTube(m_nPlayerID) != NULL)
				{	// 文字保管がNULLじゃない場合
					CGame::GetTube(m_nPlayerID)->Delete(m_nPlayerID);
				}
				m_aWord[0].nNum = 99;	// 空の状態に
				for (int nCntWord = 0; nCntWord < MAX_WORD - 1; nCntWord++)
				{
					m_aWord[nCntWord].nNum = m_aWord[nCntWord + 1].nNum;
					WordDebug(nCntWord);
				}
			}
		}
	}
}
//=============================================================================
// 弾の生成
//=============================================================================
void CWordManager::BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle)
{
	CCameraManager *pCameraManager = CManager::GetCameraManager();

	if (CGame::GetPlayer(nID) != NULL)
	{//指定したプレイヤーが存在していれば
		CCamera* pCam = pCameraManager->GetCamera(CGame::GetPlayer(nID)->GetCameraName());
		D3DXVECTOR3 BulletPos = BulletMuzzle;
		D3DXVECTOR3 BulletRot = CGame::GetPlayer(nID)->GetRotation();
		if (pCam != NULL)
		{
			BulletRot = D3DXVECTOR3(-pCam->GetRotation().x, pCam->GetRotation().y, 0.0f);
		}

		if (m_bPress == true)
		{
			if (m_nCntaAnswer == MAX_WORD)
			{	// // 指定した文字なら弾を生成する
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletPos, BulletRot, (CLoad::MODEL)m_nCreateType, 5.0f, 100, nID);
				}
			}
			else if (m_nCntaAnswer < MAX_WORD)
			{	// ゴミモデルを出す
				CModelBullet* pModel = CModelBullet::Create();
				if (pModel != NULL)
				{
					pModel->Set(BulletPos, BulletRot, CLoad::MODE_DUST, 5.0f, 100, nID);
				}
			}

			Reset();		// 設定を戻す
			if (CGame::GetTube(m_nPlayerID) != NULL)
			{
				CGame::GetTube(m_nPlayerID)->AllDelete();
			}
		}
		else if(m_bPress == false)
		{	// それ以外の場合
			if (m_nCntNum > 0)
			{
				CWordBullet* pWord = CWordBullet::Create();

				if (pWord != NULL)
				{
					pWord->Set(BulletPos, BulletRot, 5.0f, 100, GetWordNum(0), nID);
				}

				Delete();		// 文字を一部削除

			}
		}
	}
}

//=============================================================================
// Textから読み込み 答えの割り当て
//=============================================================================
void CWordManager::SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum)
{
	m_AnswerNum[nNumModel] = AnswerNum;
}

//=============================================================================
// Textから最大数読み込み 動的確保
//=============================================================================
void CWordManager::SetWordAnswerNum(int nAnswerNum)
{
	m_nAnswerDataNum = nAnswerNum;
	m_AnswerNum = new D3DXVECTOR3[m_nAnswerDataNum];
}

//=============================================================================
// 文字の組み合わせが合っているかどうかを取得
//=============================================================================
int CWordManager::SearchWord(void)
{
	if (m_nCntNum == 2 /*&& m_bSearch == false*/)
	{	// 拾った文字が２文字の場合
		int nData = 0;
		m_fAnswerData = new float[m_nAnswerDataNum];
		for (int nCntAnswer = 0; nCntAnswer < m_nAnswerDataNum; nCntAnswer++)
		{	// 答えの数だけ回す
			int nAnswer = 0;
			for (int nCntWord = 0; nCntWord < MAX_WORD; nCntWord++)
			{	// 答との比較
				if (m_AnswerNum[nCntAnswer].x == m_aWord[nCntWord].nNum && m_bAnswer[0] == false) { m_bAnswer[0] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].y == m_aWord[nCntWord].nNum && m_bAnswer[1] == false) { m_bAnswer[1] = true; nAnswer++; }
				else if (m_AnswerNum[nCntAnswer].z == m_aWord[nCntWord].nNum && m_bAnswer[2] == false) { m_bAnswer[2] = true; nAnswer++; }

				if (nAnswer == 2)
				{	// 合っている所が2箇所の場合
					for (int nCntData = 0; nCntData < MAX_WORD; nCntData++)
					{
						if (m_bAnswer[nCntData] == false)
						{	// falseの場所を探す 見つけた答えを代入
							if (nCntData == 0) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].x; }
							else if (nCntData == 1) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].y; }
							else if (nCntData == 2) { m_fAnswerData[nData] = m_AnswerNum[nCntAnswer].z; }
							nData++;		// 回数を増やす
						}
					}
					nAnswer = 0;	// 合っている回数をリセット
				}
			}

			for (int nCount = 0; nCount < MAX_WORD; nCount++)
			{	// 全てfalseに戻す
				m_bAnswer[nCount] = false;
			}
		}

		m_bSearch = true;		// Flagをtureに
		return nData;			// 答えの出た回数
	}

	return 0;
}


//=============================================================================
// 文字で生成のデバック用(数字管理)
//=============================================================================
void CWordManager::CreateOblDebug(void)
{
	CInputKeyboard *pKey = CManager::GetInputKeyboard();

	if (m_bPress == false)
	{
		if (pKey->GetPress(DIK_1))
		{	// あ行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// あ
				m_aWord[m_nCntNum].nNum = 0;
				m_aWord[m_nCntNum].cWord = "あ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// い
				m_aWord[m_nCntNum].nNum = 1;
				m_aWord[m_nCntNum].cWord = "い";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// う
				m_aWord[m_nCntNum].nNum = 2;
				m_aWord[m_nCntNum].cWord = "う";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// え
				m_aWord[m_nCntNum].nNum = 3;
				m_aWord[m_nCntNum].cWord = "え";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// え
				m_aWord[m_nCntNum].nNum = 4;
				m_aWord[m_nCntNum].cWord = "お";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_2))
		{	// か行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// か
				m_aWord[m_nCntNum].nNum = 5;
				m_aWord[m_nCntNum].cWord = "か";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// き
				m_aWord[m_nCntNum].nNum = 6;
				m_aWord[m_nCntNum].cWord = "き";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// く
				m_aWord[m_nCntNum].nNum = 7;
				m_aWord[m_nCntNum].cWord = "く";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// け
				m_aWord[m_nCntNum].nNum = 8;
				m_aWord[m_nCntNum].cWord = "け";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// こ
				m_aWord[m_nCntNum].nNum = 9;
				m_aWord[m_nCntNum].cWord = "こ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_3))
		{	// さ行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// さ
				m_aWord[m_nCntNum].nNum = 10;
				m_aWord[m_nCntNum].cWord = "さ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// し
				m_aWord[m_nCntNum].nNum = 11;
				m_aWord[m_nCntNum].cWord = "し";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// す
				m_aWord[m_nCntNum].nNum = 12;
				m_aWord[m_nCntNum].cWord = "す";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// せ
				m_aWord[m_nCntNum].nNum = 13;
				m_aWord[m_nCntNum].cWord = "せ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// そ
				m_aWord[m_nCntNum].nNum = 14;
				m_aWord[m_nCntNum].cWord = "そ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_4))
		{	// た行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// た
				m_aWord[m_nCntNum].nNum = 15;
				m_aWord[m_nCntNum].cWord = "た";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ち
				m_aWord[m_nCntNum].nNum = 16;
				m_aWord[m_nCntNum].cWord = "ち";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// つ
				m_aWord[m_nCntNum].nNum = 17;
				m_aWord[m_nCntNum].cWord = "つ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// て
				m_aWord[m_nCntNum].nNum = 18;
				m_aWord[m_nCntNum].cWord = "て";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// と
				m_aWord[m_nCntNum].nNum = 19;
				m_aWord[m_nCntNum].cWord = "と";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_5))
		{	// な行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// な
				m_aWord[m_nCntNum].nNum = 20;
				m_aWord[m_nCntNum].cWord = "な";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// に
				m_aWord[m_nCntNum].nNum = 21;
				m_aWord[m_nCntNum].cWord = "に";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ぬ
				m_aWord[m_nCntNum].nNum = 22;
				m_aWord[m_nCntNum].cWord = "ぬ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// ね
				m_aWord[m_nCntNum].nNum = 23;
				m_aWord[m_nCntNum].cWord = "ね";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// の
				m_aWord[m_nCntNum].nNum = 24;
				m_aWord[m_nCntNum].cWord = "の";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_6))
		{	// は行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// は
				m_aWord[m_nCntNum].nNum = 25;
				m_aWord[m_nCntNum].cWord = "は";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ひ
				m_aWord[m_nCntNum].nNum = 26;
				m_aWord[m_nCntNum].cWord = "ひ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ふ
				m_aWord[m_nCntNum].nNum = 27;
				m_aWord[m_nCntNum].cWord = "ふ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// へ
				m_aWord[m_nCntNum].nNum = 28;
				m_aWord[m_nCntNum].cWord = "へ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ほ
				m_aWord[m_nCntNum].nNum = 29;
				m_aWord[m_nCntNum].cWord = "ほ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_7))
		{	// ま行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ま
				m_aWord[m_nCntNum].nNum = 30;
				m_aWord[m_nCntNum].cWord = "ま";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// み
				m_aWord[m_nCntNum].nNum = 31;
				m_aWord[m_nCntNum].cWord = "み";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// む
				m_aWord[m_nCntNum].nNum = 32;
				m_aWord[m_nCntNum].cWord = "む";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// め
				m_aWord[m_nCntNum].nNum = 33;
				m_aWord[m_nCntNum].cWord = "め";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// も
				m_aWord[m_nCntNum].nNum = 34;
				m_aWord[m_nCntNum].cWord = "も";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_8))
		{	// や行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// や
				m_aWord[m_nCntNum].nNum = 35;
				m_aWord[m_nCntNum].cWord = "や";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// ゆ
				m_aWord[m_nCntNum].nNum = 36;
				m_aWord[m_nCntNum].cWord = "ゆ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// よ
				m_aWord[m_nCntNum].nNum = 37;
				m_aWord[m_nCntNum].cWord = "よ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_9))
		{	// ら行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// ら
				m_aWord[m_nCntNum].nNum = 38;
				m_aWord[m_nCntNum].cWord = "わ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// り
				m_aWord[m_nCntNum].nNum = 39;
				m_aWord[m_nCntNum].cWord = "り";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// る
				m_aWord[m_nCntNum].nNum = 40;
				m_aWord[m_nCntNum].cWord = "る";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD4))
			{	// れ
				m_aWord[m_nCntNum].nNum = 41;
				m_aWord[m_nCntNum].cWord = "れ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD5))
			{	// ろ
				m_aWord[m_nCntNum].nNum = 42;
				m_aWord[m_nCntNum].cWord = "ろ";
				m_nCntNum++;
			}
		}
		else if (pKey->GetPress(DIK_0))
		{	// わ行
			if (pKey->GetTrigger(DIK_NUMPAD1))
			{	// わ
				m_aWord[m_nCntNum].nNum = 43;
				m_aWord[m_nCntNum].cWord = "わ";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD2))
			{	// を
				m_aWord[m_nCntNum].nNum = 44;
				m_aWord[m_nCntNum].cWord = "を";
				m_nCntNum++;
			}
			else if (pKey->GetTrigger(DIK_NUMPAD3))
			{	// ん
				m_aWord[m_nCntNum].nNum = 45;
				m_aWord[m_nCntNum].cWord = "ん";
				m_nCntNum++;
			}
		}
	}

	if (m_nCntNum == MAX_WORD)
	{	// 最大ならこれ以上数字をいれない
		m_bPress = true;
	}
}

//=============================================================================
// 文字のデバック用
//=============================================================================
void CWordManager::WordDebug(int nCntNum)
{
	if (m_aWord[nCntNum].nNum == 0)
	{	// あ
		m_aWord[nCntNum].cWord = "あ";
	}
	else if (m_aWord[nCntNum].nNum == 1)
	{	// い
		m_aWord[nCntNum].cWord = "い";
	}
	else if (m_aWord[nCntNum].nNum == 2)
	{	// う
		m_aWord[nCntNum].cWord = "う";
	}
	else if (m_aWord[nCntNum].nNum == 3)
	{	// え
		m_aWord[nCntNum].cWord = "え";
	}
	else if (m_aWord[nCntNum].nNum == 4)
	{	// え
		m_aWord[nCntNum].cWord = "お";
	}
	else if (m_aWord[nCntNum].nNum == 5)
	{	// か
		m_aWord[nCntNum].cWord = "か";
	}
	else if (m_aWord[nCntNum].nNum == 6)
	{	// き
		m_aWord[nCntNum].cWord = "き";
	}
	else if (m_aWord[nCntNum].nNum == 7)
	{	// く
		m_aWord[nCntNum].cWord = "く";
	}
	else if (m_aWord[nCntNum].nNum == 8)
	{	// け
		m_aWord[nCntNum].cWord = "け";
	}
	else if (m_aWord[nCntNum].nNum == 9)
	{	// こ
		m_aWord[nCntNum].cWord = "こ";
	}
	else if (m_aWord[nCntNum].nNum == 10)
	{	// さ
		m_aWord[nCntNum].cWord = "さ";
	}
	else if (m_aWord[nCntNum].nNum == 11)
	{	// し
		m_aWord[nCntNum].cWord = "し";
	}
	else if (m_aWord[nCntNum].nNum == 12)
	{	// す
		m_aWord[nCntNum].cWord = "す";
	}
	else if (m_aWord[nCntNum].nNum == 13)
	{	// せ
		m_aWord[nCntNum].cWord = "せ";
	}
	else if (m_aWord[nCntNum].nNum == 14)
	{	// そ
		m_aWord[nCntNum].cWord = "そ";
	}
	else if (m_aWord[nCntNum].nNum == 15)
	{	// た
		m_aWord[nCntNum].cWord = "た";
	}
	else if (m_aWord[nCntNum].nNum == 16)
	{	// ち
		m_aWord[nCntNum].cWord = "ち";
	}
	else if (m_aWord[nCntNum].nNum == 17)
	{	// つ
		m_aWord[nCntNum].cWord = "つ";
	}
	else if (m_aWord[nCntNum].nNum == 18)
	{	// て
		m_aWord[nCntNum].cWord = "て";
	}
	else if (m_aWord[nCntNum].nNum == 19)
	{	// と
		m_aWord[nCntNum].cWord = "と";
	}
	else if (m_aWord[nCntNum].nNum == 20)
	{	// な
		m_aWord[nCntNum].cWord = "な";
	}
	else if (m_aWord[nCntNum].nNum == 21)
	{	// に
		m_aWord[nCntNum].cWord = "に";
	}
	else if (m_aWord[nCntNum].nNum == 22)
	{	// ぬ
		m_aWord[nCntNum].cWord = "ぬ";
	}
	else if (m_aWord[nCntNum].nNum == 23)
	{	// ね
		m_aWord[nCntNum].cWord = "ね";
	}
	else if (m_aWord[nCntNum].nNum == 24)
	{	// の
		m_aWord[nCntNum].cWord = "の";
	}
	else if (m_aWord[nCntNum].nNum == 25)
	{	// は
		m_aWord[nCntNum].cWord = "は";
	}
	else if (m_aWord[nCntNum].nNum == 26)
	{	// ひ
		m_aWord[nCntNum].cWord = "ひ";
	}
	else if (m_aWord[nCntNum].nNum == 27)
	{	// ふ
		m_aWord[nCntNum].cWord = "ふ";
	}
	else if (m_aWord[nCntNum].nNum == 28)
	{	// へ
		m_aWord[nCntNum].cWord = "へ";
	}
	else if (m_aWord[nCntNum].nNum == 29)
	{	// ほ
		m_aWord[nCntNum].cWord = "ほ";
	}
	else if (m_aWord[nCntNum].nNum == 30)
	{	// ま
		m_aWord[nCntNum].cWord = "ま";
	}
	else if (m_aWord[nCntNum].nNum == 31)
	{	// み
		m_aWord[nCntNum].cWord = "み";
	}
	else if (m_aWord[nCntNum].nNum == 32)
	{	// む
		m_aWord[nCntNum].cWord = "む";
	}
	else if (m_aWord[nCntNum].nNum == 33)
	{	// め
		m_aWord[nCntNum].cWord = "め";
	}
	else if (m_aWord[nCntNum].nNum == 34)
	{	// も
		m_aWord[nCntNum].cWord = "も";
	}
	else if (m_aWord[nCntNum].nNum == 35)
	{	// や
		m_aWord[nCntNum].cWord = "や";
	}
	else if (m_aWord[nCntNum].nNum == 36)
	{	// ゆ
		m_aWord[nCntNum].cWord = "ゆ";
	}
	else if (m_aWord[nCntNum].nNum == 37)
	{	// よ
		m_aWord[nCntNum].cWord = "よ";
	}
	else if (m_aWord[nCntNum].nNum == 38)
	{	// ら
		m_aWord[nCntNum].cWord = "わ";
	}
	else if (m_aWord[nCntNum].nNum == 39)
	{	// り
		m_aWord[nCntNum].cWord = "り";
	}
	else if (m_aWord[nCntNum].nNum == 40)
	{	// る
		m_aWord[nCntNum].cWord = "る";
	}
	else if (m_aWord[nCntNum].nNum == 41)
	{	// れ
		m_aWord[nCntNum].cWord = "れ";
	}
	else if (m_aWord[nCntNum].nNum == 42)
	{	// ろ
		m_aWord[nCntNum].cWord = "ろ";
	}
	else if (m_aWord[nCntNum].nNum == 43)
	{	// わ
		m_aWord[nCntNum].cWord = "わ";
	}
	else if (m_aWord[nCntNum].nNum == 44)
	{	// を
		m_aWord[nCntNum].cWord = "を";
	}
	else if (m_aWord[nCntNum].nNum == 45)
	{	// ん
		m_aWord[nCntNum].cWord = "ん";
	}
	else if (m_aWord[nCntNum].nNum == 99)
	{	// 空の状態
		m_aWord[nCntNum].cWord = "NULL";
	}
}