//=============================================================================
//
// 文字配置処理 [SetWord.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _SETWORD_H_
#define _SETWORD_H_

#include "main.h"
#include "scene.h"
#include "game.h"
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CWord;
class CSceneBillBoard;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//プレイヤークラスの定義
//*********************************************************************
class CSetWord : public CScene //派生クラス
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		bool		bUse;	// 使っているかどうか
		int			nCntPop;// 出現時間
	}Word_Pos;
	CSetWord();
	~CSetWord();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSetWord *Create();

	//*******************************
	// 取得 設定 の関数
	//*******************************
	void SetAnswer(int nNumAnswer) { m_nAnswer = nNumAnswer;}

private:
	//メンバ変数
public:
	//*******************************
	// Text読み込み用
	//*******************************
	void LoadFile(char *pFileName);

	char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	char *GetLineTop(char *pStr);			//行の先頭を取得
	int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

	void WordCreate(void);			// 位置の割り当て 
	void WordUninit(void);			// 文字獲得時の終了
	void PopWord(void);				// 文字出現

	Word_Pos *m_pWordPos;
	D3DXVECTOR3 *m_AnswerNum;		// 答えのデータ数値
	int m_nAnswer;					// 答えの総数
	int m_nNum;
	int m_nRandAnswerNum;			// 答えをランダムに
	int m_nAnswerNumCount;			// カウント
	bool m_bCreate;
};

#endif