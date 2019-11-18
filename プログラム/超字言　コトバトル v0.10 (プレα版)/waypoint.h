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
#define SPLIT_WAYPOINT		(20)	// ウェイポイントの縦横分割数
#define WAYPOINT_HIT		(20)	// ウェイポイントの範囲
#define WAYPOINT_POS_WIDE	(40)	// ウェイポイントの横幅

//*********************************************************************
//ビルボードクラスの定義
//*********************************************************************
class CWaypoint : public CScene //派生クラス
{
public:
	typedef struct
	{
		CSceneBillBoard *pWayPoint;		//ビルボードポインター
		D3DXVECTOR3 WayPointPos;		//位置情報
		int	nWayPointNum;				//何マスで行けるか
		bool bInPlayer;					//プレイヤーが乗っているか
		bool bBlock;					//ブロックと当たっている
		bool bAdjacent;					//隣接している
	}WAYPOINT;

	typedef enum
	{
		FROMHIT_NONE,	//当たっていない
		FROMHIT_FRONT,	//手前から
		FROMHIT_BACK,	//奥から
		FROMHIT_RIGHT,	//右から
		FROMHIT_LEFT,	//左から
		FROMHIT_IN,		//自分が当たってる
		FROMHIT_MAX
	}FROMHIT;		//どこから当たったか


	CWaypoint();
	~CWaypoint();
	HRESULT Init(/*D3DXVECTOR3 pos*/);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWaypoint *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag);
	void InRange(D3DXVECTOR3 pos);
	D3DXVECTOR3 &ReturnPointMove(void);	//移動可能なマスの位置情報
	int CntWayPoint(void);				//移動可能マスが何マスあるか
	void CollisionObj(void);			//オブジェクトと当たっているか
	WAYPOINT &GetWayPoint(void);	//移動可能なマスの位置情報

	//TEST
	int GetNumTargetPoint(int nWayPoint);			//行こうとしているマス番号
	D3DXVECTOR3 GetNextWayPoint(int nWayPoint);		//隣の行けるマスを渡す
	bool GetWPbBlock(int nWayPoint) { return WayPoint[nWayPoint].bBlock; };
	int GetNowWP(void) { return m_nNumNowPoint; };
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
	int m_nTargetNum[8];				// 行動先の番号
	int m_nNumWayPoint;					// 行動可能な数

	int m_nNumNowPoint;				// 現在のマス番号
	D3DXVECTOR3 m_PlayerPos;		// プレイヤーの位置記憶

	FROMHIT m_FromHit;


#ifdef _DEBUG
	int nNum2Cnt;
#endif

};

#endif