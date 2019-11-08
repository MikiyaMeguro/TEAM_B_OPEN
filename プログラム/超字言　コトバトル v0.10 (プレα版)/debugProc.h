//=============================================================================
//
// デバック表示処理 [debugProc.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_

#include "main.h"
#include <string>

//========================================
// クラスの定義
//========================================
//=====================
// カメラクラス
//=====================
class CDebugProc
{
public:
	CDebugProc();		// コンストラクタ
	~CDebugProc();		// デストラクタ

	void Init(void);
	void Uninit(void);

	static void Print(char *fmt, ...);				// デバック表示
	static void ReleseStr(void);					// デバック表示を消す
	static void Draw(void);

private:
	static LPD3DXFONT m_pFont;			// フォントへのポインタ

	static std::string m_strDebug;		//デバック表示用文字列
};

#endif