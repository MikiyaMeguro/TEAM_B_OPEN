//=============================================================================
//
// リザルト画面管理クラス処理 [result.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "Manager.h"

//===================================================================
//	クラスの定義
//===================================================================
class CResult
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void	Uninit(void);
	void	Update(void);
	void	Draw(void);
private:
};
#endif // !_RESULT_H_
