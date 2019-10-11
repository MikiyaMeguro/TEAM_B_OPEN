//=============================================================================
//
// 文字のビルボードの処理 [word.h]
// Author :  Shun Yokomici
//
//=============================================================================
#ifndef _WORD_H_
#define _WORD_H_

#include "sceneBillboard.h"

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CWord : public CSceneBillBoard //派生クラス
{
public:
	CWord();
	~CWord();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWord *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord);

	// 関数
	D3DXVECTOR3 Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle);
	void Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle);				// 円を作る

private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void ScaleSize(void);

	D3DXVECTOR3 m_size;		// サイズ
	D3DXVECTOR3 m_sizeOld;	// サイズ(過去)
	bool m_bFlagUninit;		// 終了するためのフラグ
	bool m_bMoveFlag;		// 上下移動のフラグ
	bool m_bScaleFlag;		// 拡大縮小するフラグ
	int m_nWordNum;			// 文字の番号
};

#endif