//=============================================================================
//
// 入力処理 [input.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _INPUT_H_
#define _INPUT_H_
#include "main.h"

//===================================================================
//	マクロ定義
//===================================================================
#define REPEAT_TIME (12)		//リピートの繰り返し時間
#define HOLD_TIME (30)			//ホールド時間
//==================================================================
//	クラスの定義
//==================================================================
//入力クラス
class CInput
{
public:
	//コンストラクタ&デストラクタ
	CInput();
	virtual ~CInput();

	//メンバ関数
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void    Uninit(void);
	virtual void    Update(void) = 0;

protected:
	//メンバ変数
	static LPDIRECTINPUT8	m_pInput;
	LPDIRECTINPUTDEVICE8	m_pDevice;

};

#endif //!_INPUT_H_