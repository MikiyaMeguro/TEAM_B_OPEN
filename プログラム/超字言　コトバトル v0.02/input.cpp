//=============================================================================
//
// 入力処理 [input.cpp]
// Author : Kodama Yuto
//
//=============================================================================
#include "input.h"

//===================================================================
//	静的メンバ変数宣言
//===================================================================
LPDIRECTINPUT8	CInput::m_pInput = NULL;		//DirectInputデバイスのポインタ

//===================================================================
//	コンストラクタ&デストラクタ
//===================================================================
CInput::CInput()
{
	//m_pDevice = NULL;
}
CInput::~CInput()
{

}

//===================================================================
//	初期化処理
//===================================================================
HRESULT CInput::Init(HINSTANCE hInstance,HWND hWnd)
{
	if (m_pInput == NULL)
	{
		// DirectInputオブジェクトの生成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}
	return S_OK;
}

//===================================================================
//	終了処理
//===================================================================
void CInput::Uninit(void)
{
	// 入力デバイス(キーボード)の開放
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();
		m_pDevice->Release();
		m_pDevice = NULL;
	}
	// DirectInputオブジェクトの開放
	if (m_pInput != NULL)
	{
		m_pInput->Release();
		m_pInput = NULL;
	}
}


