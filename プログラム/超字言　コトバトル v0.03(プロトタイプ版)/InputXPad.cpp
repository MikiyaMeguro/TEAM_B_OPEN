//=============================================================================
//
// XInputコントローラ入力処理 [inputXPad.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "InputXPad.h"
#include "debugProc.h"
#include "manager.h"

#define XPAD_L_DEADZONE (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE - 3000)
#define XPAD_R_DEADZONE (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE - 3000)

//===================================================================
//	静的メンバ変数宣言
//===================================================================
int CInputXPad::m_nCntXPadNum = 0;
//===================================================================
//	コンストラクタ&デストラクタ
//===================================================================
CInputXPad::CInputXPad()
{
	m_nID = m_nCntXPadNum;
	m_nCntXPadNum++;

	for (int nCntInput = 0; nCntInput < XPAD_MAX; nCntInput++)
	{
		m_State.abPadStatePress[nCntInput] = false;
		m_State.abPadStateTrigger[nCntInput] = false;
		m_State.abPadStateRelease[nCntInput] = false;
		m_State.abPadStateRepeat[nCntInput] = false;
		m_State.nCntRepeatTime[nCntInput] = 0;
	}
}
CInputXPad::~CInputXPad()
{
	m_nCntXPadNum--;
}

//===================================================================
//	初期化処理
//===================================================================
HRESULT CInputXPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));

	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(m_nID, &state);

	if (dwResult == ERROR_SUCCESS)
	{
		CheckDeadZone(state);
		m_bConnect = true;
	}
	else
	{
		m_bConnect = false;
	}
	return S_OK;
}

//===================================================================
//	終了処理
//===================================================================
void CInputXPad::Uninit(void)
{
	XInputEnable(false);
}

//===================================================================
//	更新処理
//===================================================================
void CInputXPad::Update(void)
{
	XINPUT_STATE state;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(m_nID, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		WORD RightStick = 0;

		//横がY、縦がXになっているので逆にする
		m_sLStickRotX = state.Gamepad.sThumbLY;
		m_sLStickRotY = state.Gamepad.sThumbLX;
		m_sRStickRotX = state.Gamepad.sThumbRY;
		m_sRStickRotY = state.Gamepad.sThumbRX;

		CheckDeadZone(state);
		CDebugProc::Print("cn","L_STICKROT_X : ", m_sLStickRotX);
		CDebugProc::Print("cn", "L_STICKROT_Y : ", m_sLStickRotY);
		CDebugProc::Print("cn", "R_STICKROT_X : ", m_sRStickRotX);
		CDebugProc::Print("cn", "R_STICKROT_Y : ", m_sRStickRotY);

		if (m_bConnect == false)
		{
			for (int nCntInput = 0; nCntInput < XPAD_MAX; nCntInput++)
			{
				m_State.abPadStatePress[nCntInput] = false;
				m_State.abPadStateTrigger[nCntInput] = false;
				m_State.abPadStateRelease[nCntInput] = false;
				m_State.abPadStateRepeat[nCntInput] = false;
				m_State.nCntRepeatTime[nCntInput] = 0;
			}
			m_bConnect = true;
		}

		//スティック入力を方向キー入力に変換してマージする
		state.Gamepad.wButtons |= ThumbToDPad(state.Gamepad.sThumbLX, state.Gamepad.sThumbLY, XPAD_L_DEADZONE);
		//右スティックの入力は個別に設定
		RightStick = ThumbToDPad(state.Gamepad.sThumbRX, state.Gamepad.sThumbRY, XPAD_R_DEADZONE);

		//入力情報設定
		SetInputState(XPAD_KEY::XPAD_UP, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP ? true : false));
		SetInputState(XPAD_KEY::XPAD_DOWN, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT, (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT ? true : false));
		SetInputState(XPAD_KEY::XPAD_START, (state.Gamepad.wButtons & XINPUT_GAMEPAD_START ? true : false));
		SetInputState(XPAD_KEY::XPAD_BACK, (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT_THUMB, (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT_THUMB, (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT_SHOULDER, (state.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT_SHOULDER, (state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER ? true : false));
		SetInputState(XPAD_KEY::XPAD_A, (state.Gamepad.wButtons & XINPUT_GAMEPAD_A ? true : false));
		SetInputState(XPAD_KEY::XPAD_B, (state.Gamepad.wButtons & XINPUT_GAMEPAD_B ? true : false));
		SetInputState(XPAD_KEY::XPAD_X, (state.Gamepad.wButtons & XINPUT_GAMEPAD_X ? true : false));
		SetInputState(XPAD_KEY::XPAD_Y, (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y ? true : false));
		SetInputState(XPAD_KEY::XPAD_LEFT_TRIGGER, (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHT_TRIGGER, (state.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_UP, (RightStick & XINPUT_GAMEPAD_DPAD_UP ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_DOWN, (RightStick & XINPUT_GAMEPAD_DPAD_DOWN ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_LEFT, (RightStick & XINPUT_GAMEPAD_DPAD_LEFT ? true : false));
		SetInputState(XPAD_KEY::XPAD_RIGHTSTICK_RIGHT, (RightStick & XINPUT_GAMEPAD_DPAD_RIGHT ? true : false));
	}
	else
	{
		for (int nCntInput = 0; nCntInput < XPAD_MAX; nCntInput++)
		{
			m_State.abPadStatePress[nCntInput] = false;
			m_State.abPadStateTrigger[nCntInput] = false;
			m_State.abPadStateRelease[nCntInput] = false;
			m_State.abPadStateRepeat[nCntInput] = false;
			m_State.nCntRepeatTime[nCntInput] = 0;
		}
		m_bConnect = false;
	}

}

//===================================================================
//	設定処理
//===================================================================
void CInputXPad::SetInputState(XPAD_KEY key, bool bPress)
{
	m_State.abPadStateTrigger[key] = (m_State.abPadStatePress[key] ^ bPress) & bPress;	//トリガー
	m_State.abPadStateRelease[key] = (m_State.abPadStatePress[key] ^ bPress) & m_State.abPadStatePress[key];	//リリース
	m_State.abPadStatePress[key] = bPress;	//プレス
	m_State.abPadStateRepeat[key] = false;

	if (m_State.abPadStatePress[key] == true)
	{
		m_State.nCntRepeatTime[key]++;
		if ((m_State.nCntRepeatTime[key] % REPEAT_TIME) == 1)
		{
			m_State.abPadStateRepeat[key] = true;	//リピート
		}
	}
	else
	{
		m_State.nCntRepeatTime[key] = 0;
	}

}
//===================================================================
//	スティック入力を方向キー入力に変換する処理
//===================================================================
WORD CInputXPad::ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//===================================================================
//	デッドゾーンの設定処理
//===================================================================
void CInputXPad::CheckDeadZone(XINPUT_STATE& state)
{
	// デッドゾーンの設定
	if ((state.Gamepad.sThumbLX < XPAD_L_DEADZONE &&
		state.Gamepad.sThumbLX > -XPAD_L_DEADZONE) &&
		(state.Gamepad.sThumbLY < XPAD_L_DEADZONE &&
			state.Gamepad.sThumbLY > -XPAD_L_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
	if ((state.Gamepad.sThumbRX < XPAD_R_DEADZONE &&
		state.Gamepad.sThumbRX > -XPAD_R_DEADZONE) &&
		(state.Gamepad.sThumbRY < XPAD_R_DEADZONE &&
			state.Gamepad.sThumbRY > -XPAD_R_DEADZONE))
	{
		state.Gamepad.sThumbRX = 0;
		state.Gamepad.sThumbRY = 0;
	}
}

//===================================================================
//	入力情報取得処理
//===================================================================
bool CInputXPad::GetPress(CInputXPad::XPAD_KEY key)		//プレス
{
	if (GetConnect()) { return m_State.abPadStatePress[key]; }
	return false;
}
bool CInputXPad::GetTrigger(CInputXPad::XPAD_KEY key)	//トリガー
{
	if (GetConnect()) { return m_State.abPadStateTrigger[key]; }
	return false;
}
bool CInputXPad::GetRelease(CInputXPad::XPAD_KEY key)	//リリース
{
	if (GetConnect()) { return m_State.abPadStateRelease[key]; }
	return false;
}
bool CInputXPad::GetRepeat(CInputXPad::XPAD_KEY key)	//リピート
{
	if (GetConnect()) { return m_State.abPadStateRepeat[key]; }
	return false;
}