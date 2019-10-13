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

	};
	CInputXPad();
	~CInputXPad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);

private:
	XINPUT_STATE m_XinputState;
	static int m_nCntXPadNum;	//XInputコントローラーの接続数
};
#endif // !_INPUT_X_PAD_H_
