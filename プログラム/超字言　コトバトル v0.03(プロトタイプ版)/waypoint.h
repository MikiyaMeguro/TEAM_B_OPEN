//=============================================================================
//
// 経路情報の処理 [waypoint.h]
// Author :　目黒 未来也
//
//=============================================================================
#ifndef _WAYPOINT_H_
#define _WAYPOINT_H_

#include "sceneBillboard.h"
#include "game.h"

#define MAX_WAYPOINT	(SPLIT_WAYPOINT * SPLIT_WAYPOINT)	// ウェイポイントの最大数
#define SPLIT_WAYPOINT	(10)	// ウェイポイントの縦横分割数
#define WAYPOINT_HIT	(40)	// ウェイポイントの範囲

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CWaypoint : public CSceneBillBoard //派生クラス
{
public:
	typedef struct
	{
		CSceneBillBoard *pWayPoint;
		D3DXVECTOR3 WayPointPos;
		int	nWayPointNum;
		bool bInPlayer;
	}WAYPOINT;

	CWaypoint();
	~CWaypoint();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWaypoint *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag);
	void InRange(D3DXVECTOR3 pos);
	D3DXVECTOR3 &ReturnPointMove(void);
	int CntWayPoint(void);

	// 関数
private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void ScaleSize(void);

	WAYPOINT WayPoint[MAX_WAYPOINT];

	D3DXVECTOR3 m_size;		// サイズ
	D3DXVECTOR3 m_sizeOld;	// サイズ(過去)
	bool m_bFlagUninit;		// 終了するためのフラグ
	bool m_bMoveFlag;		// 上下移動のフラグ
	bool m_bScaleFlag;		// 拡大縮小するフラグ
	int m_nWaypointNum;		// 経路情報の番号

	D3DXVECTOR3 m_pWayPointPos[8];		// ポインタ
	int nNumWayPoint;					// 行動可能な数

#ifdef _DEBUG
	int nNum2Cnt;
#endif

};

#endif