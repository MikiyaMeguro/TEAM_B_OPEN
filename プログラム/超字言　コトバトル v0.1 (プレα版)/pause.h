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

	static CPause* Create(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
private:
	CScene2D* m_pBG;			//ポーズの背景用
	CScene2D* m_pPause;		   //ポーズの文字表示用のポリゴン
	CScene2D* m_apSelectMenu[4];//ポーズメニュー用のポリゴン
	D3DXVECTOR3 m_aMenuDefaultPos[4];
	int m_nSelect;		//セレクトメニュー干渉用の変数
};
#endif // !_PAUSE_H_
