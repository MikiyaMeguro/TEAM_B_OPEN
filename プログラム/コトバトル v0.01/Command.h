//=============================================================================
//
// CCommand::コマンド処理 [Command.cpp]
// Author : Kodama Yuto
//	クラスの概要:
//	・決定などで押すボタンを名前で管理できるクラス
//	・ResistCommand関数を使ってコマンドを登録し、GetCommand関数で取得する
//
//=============================================================================
#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "main.h"
#include "InputKeyboard.h"


//コマンドクラス
class CCommand
{
public:
	typedef enum
	{
		INPUTTYPE_KEYBOARD,				//キーボード
		INPUTTYPE_CONTROLLER_DIRECT,	//DIRECTINPUT
		INPUTTYPE_CONTROLLER_X,			//XINPUT
		INPUTTYPE_MAX
	}INPUT_TYPE;		//入力タイプ

	typedef enum
	{
		INPUTSTATE_PRESS,				//プレス(押してる間)
		INPUTSTATE_TRIGGER,				//トリガー(押した瞬間)
		INPUTSTATE_RELEASE,				//リリース(離した瞬間)
		INPUTSTATE_HOLD,				//ホールド(nフレーム間プレスした後離すまで)
		INPUTSTATE_REPEAT,				//リピート(プレスしている間nフレームごとに)
		INPUTSTATE_NOTPRESS,			//ノットプレス(押してない間)
		INPUTSTATE_MAX
	}INPUT_STATE;		//入力の属性

	typedef enum
	{
		COMMAND_ALL_TRUE,				//全てのコマンドが押されていたら
		COMMAND_EACH_TRUE,				//どれかのコマンドが押されていたら
		COMMAND_MAX
	}GET_COMMAND_OPTION;
	typedef struct
	{
		INPUT_TYPE type;		//入力タイプ
		INPUT_STATE state;		//入力の属性
		int nKey;				//キー番号
	}KeyType;			//キーの情報

	struct CommandState
	{
		LPCSTR CommandName;					//コマンドの名前
		std::vector<KeyType> vec_KeyType;	//キー情報の配列
		bool operator ==(const LPCSTR &command)
		{
			return (CommandName == command);
		}
	};	//コマンドの情報

	static void RegistCommand(LPCSTR CommandName, INPUT_TYPE InputType, INPUT_STATE InputState, int nKey);			//コマンド情報登録(作成)
	static bool GetCommand(LPCSTR CommandName, int nPlayerID = 0, GET_COMMAND_OPTION option = COMMAND_EACH_TRUE);	//コマンド呼び出し(PlayerID = コントローラの識別用)
	static void ResetCommandAll(void);
	static bool ResetCommand(LPCSTR CommandName);

private:
	static std::vector<CommandState> m_Command;		//コマンド

	static bool CheckKey_Keyboard(CInputKeyboard* pInputK,INPUT_STATE InputState, int nKey);
	static bool CheckKey_DXController(INPUT_STATE InputState, int nKey);
};

#endif // !_COMMAND_H_
