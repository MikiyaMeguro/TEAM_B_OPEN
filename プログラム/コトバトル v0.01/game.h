//=============================================================================
//
// ゲーム画面管理クラス処理 [game.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "Manager.h"

//===================================================================
//	クラスの定義
//===================================================================
class CGame
{
public:
	CGame();
	~CGame();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);


private:

};
#endif // !_GAME_H_
