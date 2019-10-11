//=============================================================================
//
// 入力処理 [inputKeyboard.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_
#include"input.h"

//==================================================================
// マクロ定義
//==================================================================
#define	NUM_KEY_MAX			(256)	// キーの最大数

//==================================================================
//	クラスの定義
//==================================================================
//キーボード入力クラス
class CInputKeyboard : public CInput
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
private:
	BYTE m_aKeyState[NUM_KEY_MAX];
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];
};

#endif // !_INPUTKEYBOARD_H_
