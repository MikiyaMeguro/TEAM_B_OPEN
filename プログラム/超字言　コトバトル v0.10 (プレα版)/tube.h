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
	void SetWordNum(int nWordNum, int nNum);
	void SetAnswer(int nAnswer);
	void AllDelete(void);
	void Delete(int nID);
private:
	void Collect(void);		//文字を集めてTexを生成
	void Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum);

	D3DXVECTOR3 m_AnswerPos;
	CScene2D *m_apWord[MAX_WORD];
	CScene2D *m_pAnswerModel;
	int		  m_nAnswer;

	bool	 m_bModelTexFlag;
	int m_nAnswerModelNum;	// 答えの番号

};

#endif