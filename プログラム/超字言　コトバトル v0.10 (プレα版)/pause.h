//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : Kodama Yuto
//
//	クラスの概要
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "scene.h"
#include "scene2D.h"

//=============================================================================
// クラス定義
//=============================================================================
class CPause : public CScene
{
public:
	CPause();
	CPause(int nPriority = 7);
	~CPause();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	CScene2D* m_pSelectMenu[4];//ポーズメニューの個数分用意する
};

#endif // !_PAUSE_H_
