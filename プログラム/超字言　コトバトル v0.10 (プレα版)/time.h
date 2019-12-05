//=============================================================================
//
// 制限時間処理 [time.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
//　前方宣言
//*****************************************************************************
class CNumber;
class CBillNumber;
class CSceneBillBoard;
class CPlayer;
class CScene2D;
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIME_MAX			(3)		// タイマーの桁数
#define PLAYER_MAX			(4)		// プレイヤー最大数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTime : public CScene
{
public:
	CTime(int nPriority = 6, OBJTYPE objType = OBJTYPE_TIME);
	~CTime();

	static CTime *Create(int nNumPlayer);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void TexTime(int nTexData, int nTimeOne);

	//============================
	// 設定　取得　の関数
	//============================
	static int GetTime(void) { return m_nTime; };
	static void AddTime(int nTime);

	static bool GetTimeFlag(void) { return m_bCountFlag; };
	static void SetTimeFlag(bool bFlag) { m_bCountFlag = bFlag; };

	static int GetStageTime(void) { return m_nStageChange; }	// ステージ切替時の時間取得
private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData, int nOperation);
	CBillNumber *m_apNumber[TIME_MAX];	// ナンバーへのポインタ
	static int				m_nTime;			// 時間
	static int				m_nTimeCount;		// 時間のカウンタ
	static int				m_nTimeOld;
	static int				m_nStageChange;		// ステージが切り替わる時間
	static int				m_nTimeOne;
	int						m_nTimeNum;			// 時間の表示数字数
	int						m_nWaitTime;		// ゲーム終了時の待ち時間
	int						m_nNumPlayer;		// 人数保管
	bool					m_bStart;
	bool					m_bStageCreate;		// ステージ生成時の制限
	D3DXVECTOR3				m_pos;				// 位置
	CSceneBillBoard			*m_pColon;			// コロン

	static bool m_bCountFlag;			//時間をカウントするか



	//カウントダウン用
	float						m_fWidth, m_fHeight;			// 幅 高さ
	CScene2D					*m_pScene2D[PLAYER_MAX];		// 2Dポリゴンへのポインタ
	int							m_nColorFlash;					// 点滅カウント
	D3DXCOLOR					m_Col;							// 色
	bool						m_bCntDown;						// 押されたかどうか状態
	int							m_nType;						// 現在のタイプ
	float						m_fScale;						// 拡大縮小量
	int							m_ScaleCounter;					// 拡大縮小のカウンター
	bool						m_bEndCntDown;					// カウントダウンが終了したかどうか
	int							m_StageCounter;					// Stage生成完了までの時間

	CPlayer						*m_pPlayer[PLAYER_MAX];
};
#endif
