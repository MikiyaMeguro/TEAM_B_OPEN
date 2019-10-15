//=============================================================================
//
// タイトル処理 [title.h]
// Author : 目黒 未来也
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "scene.h"

//前方宣言

//クラス（シーン2Dの派生クラス）
class CTitle
{
public:
	CTitle();
	~CTitle();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CTitle *Create(void);

};
#endif