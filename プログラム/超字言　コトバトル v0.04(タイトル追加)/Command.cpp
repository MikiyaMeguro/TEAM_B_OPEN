//=============================================================================
//
// CCommand::コマンド処理 [Command.cpp]
// Author : Kodama Yuto
//
//
//	勝手に編集しないこと！！(コメントはOK)
//
//=============================================================================
#include "Command.h"
#include "Manager.h"

//===================================================================
//	静的メンバ変数宣言
//===================================================================
std::vector<CCommand::CommandState> CCommand::m_Command;

//===================================================================
//	コマンド登録処理
//===================================================================
void CCommand::RegistCommand(LPCSTR CommandName, INPUT_TYPE InputType, INPUT_STATE InputState, int nKey)
{
	CommandState One_Command;//コマンド情報格納用
	KeyType One_KeyType;	 //キー情報格納用

	//リスト内の探索(コマンド名が定義されているか探す)
	auto result = std::find(m_Command.begin(), m_Command.end(), CommandName);

	if (result == m_Command.end())
	{//コマンド名がリスト内で未定義の場合

	 /*コマンド情報設定*/
	 //コマンド名設定
		One_Command.CommandName = CommandName;

		//キー情報設定
		One_KeyType.type  = InputType;
		One_KeyType.state = InputState;
		One_KeyType.nKey  = nKey;

		One_Command.vec_KeyType.emplace_back(One_KeyType);

		//コマンド登録
		m_Command.emplace_back(One_Command);
	}
	else
	{//コマンド名が既に定義されている場合
	 //キー情報設定
		One_KeyType.type  = InputType;
		One_KeyType.state = InputState;
		One_KeyType.nKey  = nKey;

		(*result).vec_KeyType.emplace_back(One_KeyType);
	}
}

//===================================================================
//	コマンド呼び出し処理
//===================================================================
bool CCommand::GetCommand(LPCSTR CommandName, int nPlayerID, GET_COMMAND_OPTION option)
{
	CInputKeyboard* pInputK = CManager::GetInputKeyboard();	//キーボードのポインタ
	CInputXPad* pInputX = CManager::GetXInput(nPlayerID);
	bool bCommand_ETrue = false;		//COMMAND_EACH_TRUEで使用する返り値
	bool bCommand_ATrue = true;			//COMMAND_ALL_TRUEで使用する返り値

	//リスト内の探索
	auto result = std::find(m_Command.begin(), m_Command.end(), CommandName);

	if (result != m_Command.end())
	{//コマンド名が定義されていたら
		for (auto itr = (*result).vec_KeyType.begin(); itr != (*result).vec_KeyType.end(); itr++)
		{
			//trueかどうかの判定を行う
			switch ((*itr).type)
			{
			case INPUTTYPE_KEYBOARD:
				bCommand_ETrue = CheckKey_Keyboard(pInputK,(*itr).state, (*itr).nKey);
				break;
			case INPUTTYPE_CONTROLLER_DIRECT:
				break;
			case INPUTTYPE_CONTROLLER_X:
				bCommand_ETrue = CheckKey_XController(pInputX,(*itr).state, (*itr).nKey);
				break;
			}

			if (bCommand_ETrue == true && option == COMMAND_EACH_TRUE)
			{//一つでもあっていれば強制的に処理から抜ける(COMMAND_EACH_TRUEのみ)
				return bCommand_ETrue;
			}

			if (bCommand_ETrue == false)
			{//一つでもあってなければこの変数をfalseにする
				bCommand_ATrue = false;
			}
		}

	}
	else
	{//コマンドが登録されていなければfalseを返す
		return false;
	}

	return bCommand_ATrue;	//全てあっていればtrueを返す(COMMAND_ALL_TRUEのみ)
}
//===================================================================
//	コマンド全消去処理
//===================================================================
void CCommand::ResetCommandAll(void)
{
	for (auto itrCommand = m_Command.begin(); itrCommand != m_Command.end(); itrCommand++)
	{
		(*itrCommand).vec_KeyType.clear();
	}

	//初期化
	m_Command.clear();
}

//===================================================================
//	コマンド消去処理
//===================================================================
bool CCommand::ResetCommand(LPCSTR CommandName)
{
	auto result = std::find(m_Command.begin(), m_Command.end(), CommandName);
	if (result == m_Command.end())
	{//コマンド名が定義されていなければ
		return false;
	}
	else
	{//定義されていれば

		//キーの削除
		(*result).vec_KeyType.clear();
	}
	return true;
}

//===================================================================
//	キー呼び出し処理(Keyboard)
//===================================================================
bool  CCommand::CheckKey_Keyboard(CInputKeyboard* pInputK, INPUT_STATE InputState, int nKey)
{
	bool bCommand = false;									//関数の返り値
	if (pInputK != NULL)
	{
		switch (InputState)
		{
		case INPUTSTATE_PRESS:	//プレス
			bCommand = pInputK->GetPress(nKey);
			break;
		case INPUTSTATE_TRIGGER://トリガー
			bCommand = pInputK->GetTrigger(nKey);
			break;
		case INPUTSTATE_RELEASE://リリース
			bCommand = pInputK->GetRelease(nKey);
			break;
		case INPUTSTATE_NOTPRESS://ノットプレス(押してない時)
			bCommand = !(pInputK->GetPress(nKey));
			break;
		case INPUTSTATE_REPEAT://リピート
			bCommand = pInputK->GetRepeat(nKey);
			break;

		}
	}
	return bCommand;
}
bool  CCommand::CheckKey_XController(CInputXPad* pInputX, INPUT_STATE InputState, int nKey)
{
	bool bCommand = false;									//関数の返り値
	if (nKey >= CInputXPad::XPAD_MAX)
	{
		return false;
	}
	if (pInputX != NULL)
	{
		switch (InputState)
		{
		case INPUTSTATE_PRESS:	//プレス
			bCommand = pInputX->GetPress((CInputXPad::XPAD_KEY)nKey);
			break;
		case INPUTSTATE_TRIGGER://トリガー
			bCommand = pInputX->GetTrigger((CInputXPad::XPAD_KEY)nKey);
			break;
		case INPUTSTATE_RELEASE://リリース
			bCommand = pInputX->GetRelease((CInputXPad::XPAD_KEY)nKey);
			break;
		case INPUTSTATE_NOTPRESS://ノットプレス(押してない時)
			bCommand = !(pInputX->GetPress((CInputXPad::XPAD_KEY)nKey));
			break;
		case INPUTSTATE_REPEAT://リピート
			bCommand = pInputX->GetRepeat((CInputXPad::XPAD_KEY)nKey);
			break;
		}
	}

	return bCommand;

}
