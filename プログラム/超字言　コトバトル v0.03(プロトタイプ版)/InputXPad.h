//=============================================================================
//
// XInputコントローラ入力処理 [inputXPad.h]
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
		XPAD_LEFT_TRIGGER,		//LT(L2)ボタン
		XPAD_RIGHT_TRIGGER,		//RT(R2)ボタン
		XPAD_RIGHTSTICK_UP,		//右スティック上入力
		XPAD_RIGHTSTICK_DOWN,	//右スティック下入力
		XPAD_RIGHTSTICK_LEFT,	//右スティック右入力
		XPAD_RIGHTSTICK_RIGHT,	//右スティック左入力
		XPAD_MAX
	}XPAD_KEY;

	typedef struct
	{
		bool abPadStatePress[XPAD_MAX];			//プレス情報
		bool abPadStateTrigger[XPAD_MAX];		//トリガー情報
		bool abPadStateRelease[XPAD_MAX];		//リリース情報
		bool abPadStateRepeat[XPAD_MAX];		//リピート情報
		int nCntRepeatTime[XPAD_MAX];
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
	bool GetConnect(void) { return m_bConnect; };

	SHORT GetLStickRotX(void) { return m_sLStickRotX; };
	SHORT GetLStickRotY(void) { return m_sLStickRotY; };
	SHORT GetRStickRotX(void) { return m_sRStickRotX; };
	SHORT GetRStickRotY(void) { return m_sRStickRotY; };

private:
	void SetInputState(XPAD_KEY key,bool bPress);
	WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);
	void CheckDeadZone(XINPUT_STATE& state);

	XPAD_STATE m_State;			//入力情報
	static int m_nCntXPadNum;	//XInputコントローラーの接続数
	int m_nID;					//プレイヤーID
	bool m_bConnect;			//つながっているか

	SHORT m_sLStickRotX;
	SHORT m_sLStickRotY;
	SHORT m_sRStickRotX;
	SHORT m_sRStickRotY;
};
#endif // !_INPUT_X_PAD_H_
