//=============================================================================
//
// ���͏��� [inputXPad.h]
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
		XPAD_UP = 0,			//��{�^��
		XPAD_DOWN,				//���{�^��
		XPAD_LEFT,				//���{�^��
		XPAD_RIGHT,				//�E�{�^��
		XPAD_START,				//START�{�^��
		XPAD_BACK,				//BACK�{�^��
		XPAD_LEFT_THUMB,		//���X�e�B�b�N��������(L3)
		XPAD_RIGHT_THUMB,		//�E�X�e�B�b�N��������(R3)
		XPAD_LEFT_SHOULDER,		//LB(L1)�{�^��
		XPAD_RIGHT_SHOULDER,	//RB(R1)�{�^��
		XPAD_A,					//A�{�^��
		XPAD_B,					//B�{�^��
		XPAD_X,					//X�{�^��
		XPAD_Y,					//Y�{�^��
		XPAD_MAX
	}XPAD_KEY;

	typedef struct
	{
		XINPUT_GAMEPAD PadStatePress;		//�v���X���
		XINPUT_GAMEPAD PadStateTrigger;		//�g���K�[���
		XINPUT_GAMEPAD PadStateRelease;		//�����[�X���
		XINPUT_GAMEPAD PadStateRepeat;		//���s�[�g���
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
	static int m_nCntXPadNum;	//XInput�R���g���[���[�̐ڑ���
};
#endif // !_INPUT_X_PAD_H_
