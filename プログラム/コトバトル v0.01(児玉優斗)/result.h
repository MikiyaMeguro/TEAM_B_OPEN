//=============================================================================
//
// リザルト処理 [result.h]
// Author : 目黒未来也
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "scene.h"

//前方宣言

//クラス（シーン2Dの派生クラス）
class CResult
{
public:
	CResult();
	~CResult();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:

};
#endif