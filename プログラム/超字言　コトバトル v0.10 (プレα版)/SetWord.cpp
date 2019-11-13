//---------------------------------------------------------------------
//	文字配置処理(SetWord.cpp)
//	Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "SetWord.h"
#include "game.h"
#include "fade.h"
#include "word.h"
#include "word_manager.h"
#include "sceneBillboard.h"
#include "time.h"
#include <stdlib.h>		
#include <time.h>		

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POP_TIME				(60)		// 文字獲得時から出現までの時間

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------

//--------------------------------------------
//オブジェクトクラス コンストラクタ
//--------------------------------------------
CSetWord::CSetWord() : CScene(3, CScene::OBJTYPE_SETOBJECT)
{
	m_pWordPos = NULL;
	m_AnswerNum = NULL;
	m_nAnswerNumCount = 0;
}

//--------------------------------------------
//オブジェクトクラス デストラクタ
//--------------------------------------------
CSetWord::~CSetWord()
{
}

//--------------------------------------------
//オブジェクトの生成
//--------------------------------------------
CSetWord *CSetWord::Create()
{
	//オブジェクトポインタ
	CSetWord *pSetObject = NULL;
	if (pSetObject == NULL)
	{
		pSetObject = new CSetWord;
		if (pSetObject != NULL)
		{//オブジェクトの初期化
			pSetObject->Init();
		}
	}
	//オブジェクトの情報を返す
	return pSetObject;
}

//=============================================================================
// オブジェクトの初期化処理
//=============================================================================
HRESULT CSetWord::Init()
{
	srand((unsigned int)time(0));		// ランダムのやつ

	//オブジェクト種類の設定
	CScene::SetObjType(CScene::OBJTYPE_NONE);
	m_AnswerNum = CWordManager::GetAnswerNum();
	m_nAnswer = CWordManager::GetAnswerDataNum();
	m_nRandAnswerNum = rand() % m_nAnswer;
	m_bCreate = false;
	return S_OK;
}

//=============================================================================
// オブジェクトの終了処理
//=============================================================================
void CSetWord::Uninit(void)
{
	if (m_pWordPos != NULL)
	{
		delete[] m_pWordPos;
		m_pWordPos = NULL;
	}

	//自分を消す(オブジェクトを破棄)
	Release();
}

//=============================================================================
// オブジェクトの更新処理
//=============================================================================
void CSetWord::Update(void)
{
	WordUninit();	// 文字の終了フラグが立っている場合 終了処理へ

	PopWord();		// 文字の出現
}

//=============================================================================
// オブジェクトの描画処理
//=============================================================================
void CSetWord::Draw(void)
{
}

//=============================================================================
//　位置の割り当て
//=============================================================================
void CSetWord::WordCreate(void)
{
	int nCntNum = 0;
	int nRandNum = 0;
	float fWord = 99.0f;
	while (m_nNum != nCntNum)
	{	// カウントが同じになった場合抜ける
		
		// randで位置決める
		nRandNum = rand() % m_nNum;	// 行動パターンの数字を決める

		// if文で使っているかを出す
		if (m_pWordPos[nRandNum].bUse == false)
		{
			m_pWordPos[nRandNum].bUse = true;
			if (m_nAnswerNumCount == 0) { fWord = m_AnswerNum[m_nRandAnswerNum].x; }
			if (m_nAnswerNumCount == 1) { fWord = m_AnswerNum[m_nRandAnswerNum].y; }
			if (m_nAnswerNumCount == 2) { fWord = m_AnswerNum[m_nRandAnswerNum].z; }

			CWord::Create(m_pWordPos[nRandNum].pos, 0.0f, 0.0f, "WORD", (int)fWord, nRandNum);
			// 使っている場合はカウントを回す
			nCntNum++;
			m_nAnswerNumCount++;

			if (m_nAnswerNumCount % 3 == 0)
			{
				// randで位置決める
				m_nRandAnswerNum = rand() % m_nAnswer;	// 行動パターンの数字を決める
				m_nAnswerNumCount = 0;
			}
		}
	}
}

//=============================================================================
//　文字獲得後の終了処理
//=============================================================================
void CSetWord::WordUninit(void)
{
	CScene *pScene = NULL;
	int nNum = m_nNum;

	// 先頭のオブジェクトを取得
	pScene = CScene::GetTop(5);

	while (pScene != NULL)
	{// 優先順位が弾と同じオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();
		if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_WORD)
		{// 死亡フラグが立っていないもの
			CWord *pWord = ((CWord*)pScene);		// CBulletBaseへキャスト(型の変更)
			if (pWord->GetUninitFlag() == true)
			{
				nNum = pWord->GetNum();		// 番号を取得
				m_pWordPos[nNum].bUse = false;
				pWord->Uninit();
				pWord = NULL;
			}
		}
		pScene = pSceneNext;
	}
}

//=============================================================================
//　文字の出現処理
//=============================================================================
void CSetWord::PopWord(void)
{
	float fWord = 99.0f;

	for (int nCntPos = 0; nCntPos < m_nNum; nCntPos++)
	{
		if (m_pWordPos[nCntPos].bUse == false)
		{
			m_pWordPos[nCntPos].nCntPop++;

			if ((m_pWordPos[nCntPos].nCntPop % POP_TIME) == 0)
			{
				if (m_nAnswerNumCount == 0) { fWord = m_AnswerNum[m_nRandAnswerNum].x; }
				if (m_nAnswerNumCount == 1) { fWord = m_AnswerNum[m_nRandAnswerNum].y; }
				if (m_nAnswerNumCount == 2) { fWord = m_AnswerNum[m_nRandAnswerNum].z; }

				CWord::Create(m_pWordPos[nCntPos].pos, 0.0f, 0.0f, "WORD", (int)fWord, nCntPos);
				m_nAnswerNumCount++;
				m_pWordPos[nCntPos].nCntPop = 0;
				m_pWordPos[nCntPos].bUse = true;

				if (m_nAnswerNumCount % 3 == 0)
				{
					// randで位置決める
					m_nRandAnswerNum = rand() % m_nAnswer;	// 行動パターンの数字を決める
					m_nAnswerNumCount = 0;
				}
			}


		}
	}
}

//=============================================================================
// オブジェクトの配置情報を読み込み
//=============================================================================
void CSetWord::LoadFile(char *pFileName)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//ファイル読み込み用変数
	FILE *pFile;			//ファイルポインタ
	char *pStrcur;			//現在の先頭の文字列
	char aLine[256];		//文字列
	char aStr[256];			//一時保存文字列
	int nIndex = 0;			//現在のインデックス
	int nWord = 0;			//ポップで返された値を保持
	int nNumModel = 0;		//モデルの数
	int nType = 0;			//モデルの種類
	int nCntNum = 0;
	D3DXVECTOR3 ModelPos;	//モデルの位置

	if (m_pWordPos != NULL)
	{	// 位置関係の構造体の開放
		delete[] m_pWordPos;
		m_pWordPos = NULL;
	}

	//ファイルを開く 読み込み
	pFile = fopen(pFileName, "r");
	//NULLチェック
	if (pFile != NULL)
	{
		while (1)
		{
			//文字列の先頭を設定
			pStrcur = ReadLine(pFile, &aLine[0]);
			//文字列を取り出す
			strcpy(aStr, pStrcur);

			if (memcmp(pStrcur, "NUM_MODEL = ", strlen("NUM_MODEL = ")) == 0)
			{
				//頭出し
				pStrcur += strlen("NUM_MODEL = ");
				//文字列の先頭を設定
				strcpy(aStr, pStrcur);
				//文字列抜き出し
				m_nNum = atoi(pStrcur);
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);

				if (m_pWordPos == NULL)
				{
					m_pWordPos = new Word_Pos[m_nNum];
				}

				//CWordManager::SetWordAnswerNum(nAnswerNum);
			}

			//オブジェクト読み込み
			if (memcmp(pStrcur, "MODELSET", strlen("MODELSET")) == 0)
			{
				//頭出し
				pStrcur += strlen("MODESET");
				//文字列の先頭を設定
				pStrcur = ReadLine(pFile, &aLine[0]);
				//位置
				if (memcmp(pStrcur, "POS = ", strlen("POS = ")) == 0)
				{
					//頭出し
					pStrcur += strlen("POS = ");
					//文字列の先頭を設定
					strcpy(aStr, pStrcur);

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.X代入
					ModelPos.x = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Y代入
					ModelPos.y = (float)atof(pStrcur);
					//文字数分進める
					pStrcur += nWord;

					//文字数を返してもらう
					nWord = PopString(pStrcur, &aStr[0]);
					//POS.Z代入
					ModelPos.z = (float)atof(pStrcur);
					//文字列の先頭を設定
					pStrcur = ReadLine(pFile, &aLine[0]);

					if (&m_pWordPos[nCntNum] != NULL)
					{	// 設定
						m_pWordPos[nCntNum].pos = ModelPos;
						m_pWordPos[nCntNum].bUse = false;
						m_pWordPos[nCntNum].nCntPop = 0;

						nCntNum++;
					}
				}
			}
			//モデルを生成
			if (memcmp(pStrcur, "END_MODELSET", strlen("END_MODELSET")) == 0)
			{
				//CWord::Create(D3DXVECTOR3(380.0f, 0.0f, 380.0f), 12.0f, 12.0f, "WORD", 38);

			}
			//スクリプトの終わり
			if (memcmp(pStrcur, "END_SCRIPT	", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}
	}

	//ファイルを閉じる
	fclose(pFile);

	//WordCreate();	// 文字の生成
}


//=============================================================================
//　ファイル読み込み無効文を排除
//=============================================================================
char *CSetWord::ReadLine(FILE *pFile, char *pDst)
{
	while (1)
	{
		//１行分読み込み
		fgets(&pDst[0], 256, pFile);

		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pDst, "#", strlen("#")) == 0)
		{
			pDst += strlen("\n");
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\t", strlen("\t")) == 0)
		{
			pDst += strlen("\t");
			while (1)
			{
				if (memcmp(pDst, "\t", strlen("\t")) == 0)
				{
					pDst += strlen("\t");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, " ", strlen(" ")) == 0)
		{
			pDst += strlen(" ");
			while (1)
			{
				if (memcmp(pDst, " ", strlen(" ")) == 0)
				{
					pDst += strlen(" ");
				}
				else
				{
					break;
				}
			}
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pDst, "\n", strlen("\n")) == 0)
		{
			pDst += strlen("\n");
		}
		else
		{
			break;
		}
	}
	return pDst;
}

//=============================================================================
//　ファイル読み込み先頭を排除
//=============================================================================
char * CSetWord::GetLineTop(char * pStr)
{
	while (1)
	{
		//文字列のデータ 比較する文字列 比較する文字数
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{
			pStr += strlen(" ");
			while (1)
			{
				if (memcmp(pStr, " ", strlen(" ")) == 0)
				{
					pStr += strlen(" ");
				}
				else
				{
					break;
				}
				break;
			}
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{
			pStr += strlen("\t");
			while (1)
			{
				if (memcmp(pStr, "\t", strlen("\t")) == 0)
				{
					pStr += strlen("\t");
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			break;
		}
	}
	return pStr;
}

//=============================================================================
//　文字数を返す
//=============================================================================
int CSetWord::PopString(char * pStr, char * pDest)
{
	int nWord = 0;

	while (1)
	{	//頭出し
		pStr += 1;
		nWord += 1;
		if (memcmp(pStr, " ", strlen(" ")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += 1;
			break;
		}
		if (memcmp(pStr, "\t", strlen("\t")) == 0)
		{	//頭出し
			pStr = "\0";
			nWord += strlen("\t");
			break;
		}
		//文字列のデータ 比較する文字列 比較する文字数
		else if (memcmp(pStr, "\n", strlen("\n")) == 0)
		{
			//頭出し
			nWord += strlen("\n");
			break;
		}
	}
	strcpy(pDest, pStr);
	//文字列の数を返す
	return nWord;
}
