//=============================================================================
//
// ì¸óÕèàóù [inputXPad.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _INPUT_X_PAD_H_
#define _INPUT_X_PAD_H_
#include "input.h"

class CInputXPad : public CInput
{
public:
	CInputXPad();
	~CInputXPad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void    Uninit(void);
	void    Update(void);
};
#endif // !_INPUT_X_PAD_H_
