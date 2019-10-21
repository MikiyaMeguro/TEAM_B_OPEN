//=============================================================================
//
// 入力処理 [InputKeyboard.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "InputKeyboard.h"

//===================================================================
//	コンストラクタ&デストラクタ
//===================================================================
CInputKeyboard::CInputKeyboard()
{
	for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
	{
		m_aState[nCntKey].KeyState = 0;
		m_aState[nCntKey].KeyStateTrigger = 0;
		m_aState[nCntKey].KeyStateRelease = 0;
		m_aState[nCntKey].KeyStateRepeat = 0;
		m_aState[nCntKey].nCntRepeatTime = 0;
	}

}
CInputKeyboard::~CInputKeyboard()
{

}
//===================================================================
//	初期化処理
//===================================================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance, hWnd);

	// 入力デバイス(キーボード)の生成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// 協調モードを設定
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevice->Acquire();


	return S_OK;
}

//===================================================================
//	終了処理
//===================================================================
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//===================================================================
//	更新処理
//===================================================================
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	// 入力デバイスからデータを取得
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
            m_aState[nCntKey].KeyStateRelease = (m_aState[nCntKey].KeyState ^ aKeyState[nCntKey]) & m_aState[nCntKey].KeyState;//リリース
			m_aState[nCntKey].KeyStateTrigger = (m_aState[nCntKey].KeyState ^ aKeyState[nCntKey]) & aKeyState[nCntKey];//トリガー
			m_aState[nCntKey].KeyState = aKeyState[nCntKey];//プレス
			m_aState[nCntKey].KeyStateRepeat = 0;

			if (GetPress(nCntKey))
			{
				m_aState[nCntKey].nCntRepeatTime++;
				if (m_aState[nCntKey].nCntRepeatTime % REPEAT_TIME == 1)
				{
					m_aState[nCntKey].KeyStateRepeat = aKeyState[nCntKey];	//リピート
				}
			}
			else
			{
				m_aState[nCntKey].nCntRepeatTime = 0;
			}
		}
	}
	else
	{
		m_pDevice->Acquire();
	}
}

//===================================================================
// キーボードの入力情報(プレス情報)を取得
//===================================================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aState[nKey].KeyState & 0x80) ? true : false;
}
//=============================================================================
// キーボードの入力情報(トリガー情報)を取得
//=============================================================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	return(m_aState[nKey].KeyStateTrigger & 0x80) ? true : false;
}

bool CInputKeyboard::GetRelease(int nKey)
{
	return(m_aState[nKey].KeyStateRelease & 0x80) ? true : false;
}
bool CInputKeyboard::GetRepeat(int nKey)
{
	return(m_aState[nKey].KeyStateRepeat & 0x80) ? true : false;
}
