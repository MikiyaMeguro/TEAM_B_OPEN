//=============================================================================
//
// デバック情報表示処理 [DebugProc.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _DEBUG_PROC_H_
#define _DEBUG_PROC_H_

#include "main.h"

//==================================================================
//	マクロ定義
//==================================================================
#define MAX_CHARDATA (2048)	//文字数

//==================================================================
//	クラスの定義
//==================================================================
class CDebugProc
{
public:
	CDebugProc();
	~CDebugProc();

	void    Init(void);
	void    Uninit(void);

	static void    Print(char* fmt,...);
	static void    Draw(void);

private:
	static LPD3DXFONT m_pFont;				//フォント用のポインタ
	static char m_aStr[MAX_CHARDATA];		//デバック情報表示用の変数

};
#endif // !_DEBUG_PROC_H_
