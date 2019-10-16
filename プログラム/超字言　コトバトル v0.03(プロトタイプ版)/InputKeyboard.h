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
	typedef struct
	{
		BYTE KeyState;			//プレス用のキー情報
		BYTE KeyStateTrigger;	//トリガー用のキー情報
		BYTE KeyStateRelease;	//リリース用のキー情報
		BYTE KeyStateRepeat;	//リピート用のキー情報

		int nCntRepeatTime;		//リピート用のカウンタ

	}KEYBOARD_STATE;		//キー情報の構造体
	CInputKeyboard();
	~CInputKeyboard();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey);
private:
	KEYBOARD_STATE m_aState[NUM_KEY_MAX];	//キー情報構造体(キー数分)
};

#endif // !_INPUTKEYBOARD_H_
