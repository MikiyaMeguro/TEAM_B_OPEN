//=============================================================================
//
// credit処理 [credit.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _CREDIT_H_
#define _CREDIT_H_

#include "main.h"
#include "input.h"
#include "scene.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*********************************************************************
//ゲームクラスの定義
//*********************************************************************
class CCredit : public CScene //派生クラス
{
public:

	CCredit(int nPriority = 7);
	~CCredit();
	static CCredit *Create();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static HRESULT Load(void) { return S_OK; }													//読み込み
	static void UnLoad(void);																	//破棄

private:
	void SetInit(void);
	void Flash(void);	// 色の点滅

	CScene2D *m_pCredit;
	CScene2D *m_pBack;

	int	m_nCntFlash;
};

#endif