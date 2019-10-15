//=============================================================================
//
// タイトル処理 [select.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _SELECT_H_
#define _SELECT_H_

#include "scene.h"

//前方宣言

//クラス（シーン2Dの派生クラス）
class CSelect
{
public:
	CSelect();
	~CSelect();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSelect *Create(void);

	//メンバ変数
private:
	int m_nTimer;		//終了タイマー加算
};
#endif