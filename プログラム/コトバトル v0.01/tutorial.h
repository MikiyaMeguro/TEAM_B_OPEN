//=============================================================================
//
// ゲーム画面管理クラス処理 [tutorial.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_
#include "main.h"
#include "Manager.h"

//===================================================================
//	クラスの定義
//===================================================================
class CTutorial
{
public:
	CTutorial();
	~CTutorial();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
private:
};
#endif // !_TUTORIAL_H_
