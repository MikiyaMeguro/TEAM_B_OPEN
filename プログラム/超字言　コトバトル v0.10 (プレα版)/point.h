//=============================================================================
//
// 制限時間処理 [time.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _POINT_H_
#define _POINT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_POINT_NUM			(2)		// タイマーの桁数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CPoint : public CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,	// 何もなし
		TYPR_PLAYER,	// プレイヤー
		TYPE_CPU,		// 敵
		TYPE_MAX
	}TYPE_CHARACTER;

	CPoint(int nPriority = 6, OBJTYPE objType = OBJTYPE_POINT);
	~CPoint();

	static CPoint *Create(int nID, int nNumPlayer, TYPE_CHARACTER type);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexPoint(int nTexData);

	//============================
	// 設定　取得　の関数
	//============================
	int GetPoint(void) { return m_nTotalPoint; };

	//============================
	// 加算　減算　の関数
	//============================
	void AddPoint(int nPoint);				// 加算処理
	void SubtractionPoint(int nPoint);		// 減算処理


private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData);
	void PointBGCreate(void);			// ポイントの背景生成
	void BGPosition(CScene2D *pBg);		// 背景の位置まとめ
	void UIPosition(void);				// UIの位置まとめ
	void PointPostion(int nNumPlayer, int nID);			// ポイントの位置まとめ
	void SizeChange(void);				// 増減時のサイズ変更

	CNumber *m_apNumber[MAX_POINT_NUM];	// ナンバーへのポインタ
	int m_nTotalPoint;							// トータルのポイント
	int						m_nPointNum;		// ポイントの表示数字数
	int						m_nNumPlayer;		// 人数保管
	int						m_nID;				// 自分の番号
	bool					m_bStart;
	bool					m_bSizeChange;		// ポイント増減時のサイズ変更
	D3DXVECTOR3				m_pos;				// 位置
	CScene2D				*m_pIcon;			// プレイヤーアイコン
	TYPE_CHARACTER			m_type;				// 種類
	D3DXCOLOR				m_ChangeCol;		// ポイント増減時の色
};
#endif
