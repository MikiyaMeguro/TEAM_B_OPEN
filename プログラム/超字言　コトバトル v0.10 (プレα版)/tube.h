//=============================================================================
//
// 文字保管UIの処理 [tube.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TUBE_H_
#define _TUBE_H_

#include "scene2D.h"
#include "word_manager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CTube : public CScene2D
{
public:
	CTube(int nPriority = 3, OBJTYPE objType = OBJTYPE_UI);											// コンストラクタ
	~CTube();										// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos);				// 2Dオブジェクト初期化処理
	virtual void Uninit(void);							// 2Dオブジェクト終了処理
	virtual void Update(void);							// 2Dオブジェクト更新処理
	virtual void Draw(void);							// 2Dオブジェクト描画処理

	static CTube *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag, int nPriority = 3);				// オブジェクトの生成

	//設定の関数
	void SetWordNum(int nWordNum, int nNum, int nStock);
	void SetPoint(int nPoint, int nNum, bool bPoint);
	void SetAnswer(int nAnswer, int nStock);
	void SetStockNum(int nStock) { m_nStockNum = nStock; }
	void AllDelete(int nNum);
	void Delete(int nID, int nStock);

	bool GetFlag(void) { return m_bCreateFlag; }
private:
	void Collect(void);		//文字を集めてTexを生成
	void Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum);
	void UninitChack(void);	// 終了しているかどうかの確認

	D3DXVECTOR3 m_AnswerPos;
	CScene2D *m_apWord[MAX_WORD];
	CScene2D *m_pAnswerModel[MAX_WORD];
	int		  m_nAnswer;

	bool	 m_bModelTexFlag;
	bool	 m_bCreateFlag;
	int m_nAnswerModelNum;	// 答えの番号
	int m_nStockNum;

};

#endif