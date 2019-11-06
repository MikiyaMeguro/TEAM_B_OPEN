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
//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CWord;

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

private:
	//メンバ変数
public:
	void LoadFile(char *pFileName);

	char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	char *GetLineTop(char *pStr);			//行の先頭を取得
	int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

	CWord *m_pWord;
	Word_Pos *m_pWordPos;
};

#endif