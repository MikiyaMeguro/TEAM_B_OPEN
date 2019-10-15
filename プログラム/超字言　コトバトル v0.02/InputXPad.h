//=============================================================================
//
// 入力処理 [inputXPad.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _INPUT_X_PAD_H_
#define _INPUT_X_PAD_H_
#include "input.h"

class CInputXPad : public CInput
{
public:
	typedef enum
	{
		XPAD_UP = 0,			//上ボタン
		XPAD_DOWN,				//下ボタン
		XPAD_LEFT,				//左ボタン
		XPAD_RIGHT,				//右ボタン
		XPAD_START,				//STARTボタン
		XPAD_BACK,				//BACKボタン
		XPAD_LEFT_THUMB,		//左スティック押し込み(L3)
		XPAD_RIGHT_THUMB,		//右スティック押し込み(R3)
		XPAD_LEFT_SHOULDER,		//LB(L1)ボタン
		XPAD_RIGHT_SHOULDER,	//RB(R1)ボタン
		XPAD_A,					//Aボタン
		XPAD_B,					//Bボタン
		XPAD_X,					//Xボタン
		XPAD_Y,					//Yボタン
		XPAD_MAX
	}XPAD_KEY;

	typedef struct
	{
		XINPUT_GAMEPAD PadStatePress;		//プレス情報
		XINPUT_GAMEPAD PadStateTrigger;		//トリガー情報
		XINPUT_GAMEPAD PadStateRelease;		//リリース情報
		XINPUT_GAMEPAD PadStateRepeat;		//リピート情報
		int nCntRepeatTime;
	}XPAD_STATE;
	CInputXPad();
	~CInputXPad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

	bool GetPress(XPAD_KEY key);
	bool GetTrigger(XPAD_KEY key);
	bool GetRelease(XPAD_KEY key);
	bool GetRepeat(XPAD_KEY key);

private:
	WORD XPadKeyConverseBit(XPAD_KEY key);

	XPAD_STATE m_PadState;
	static int m_nCntXPadNum;	//XInputコントローラーの接続数
};
#endif // !_INPUT_X_PAD_H_
