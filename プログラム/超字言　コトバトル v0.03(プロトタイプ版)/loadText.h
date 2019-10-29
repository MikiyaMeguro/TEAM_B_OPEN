//=============================================================================
//
// Text読み込み処理 [loadText.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _LOADTEXT_H_
#define _LOADTEXT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CLoadText
{
public:
	CLoadText();	// コンストラクタ
	~CLoadText();	// デストラクタ

	static void LoadFile(void);
	static char *ReadLine(FILE *pFile, char *pDst);	//1行読み込み
	static char *GetLineTop(char *pStr);			//行の先頭を取得
	static int  PopString(char *pStr, char *pDest);	//行の最後を切り捨て

private:
};

#endif