//=============================================================================
//
// スコア処理 [Score.h]
// Author : Kodama Yuto
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_
#include "scene.h"

class CNumber;

//==================================================================
// マクロ定義
//==================================================================
#define MAX_DIGIT	   (8)			//スコアの最大桁数
#define SCORECOUNT_MAX (99999999)	//スコアの最大値

//==================================================================
// クラスの定義
//==================================================================
class CScore : public CScene
{
public:
	CScore();
	CScore(CScene::PRIORITY);
	~CScore();

	void Set(D3DXVECTOR3 pos, D3DXVECTOR2 polygonRect,
		int nScore = 00000000,D3DXCOLOR col = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f),int nScoreDigit = 8);//nScoreDigit = スコアの桁数(1～8)

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3& GetPosition(void) { return m_Pos; };
	D3DXCOLOR& GetColor(void) { return m_Color; };
	D3DXVECTOR2& GetRect(void) { return m_PolygonRect; };
	int GetScore(void) { return m_nScore; };
	void SetScore(int nScore);
	void AddScore(int nValue);
private:
	int m_nScore;			//スコア

	D3DXVECTOR3 m_Pos;				//位置(一番右に置かれる数字の座標)
	D3DXCOLOR m_Color;				//色
	D3DXVECTOR2 m_PolygonRect;		//数字のサイズ

	std::vector<CNumber*> m_vecNumber;//数字クラスのポインタを持つ動的配列
};
#endif// !_SCORE_H_
