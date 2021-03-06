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
class CScene2D;

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TIME_MAX			(3)		// タイマーの桁数

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
	void TexTime(int nTexData);

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
	CNumber *m_apNumber[TIME_MAX];	// ナンバーへのポインタ
	static int				m_nTime;			// 時間
	static int				m_nTimeNumCount;	// 時間の表示回数
	static int				m_nTimeCount;		// 時間のカウンタ
	static int				m_nTimeOld;
	static int				m_nStageChange;		// ステージが切り替わる時間
	int						m_nTimeNum;			// 時間の表示数字数
	int						m_nWaitTime;		// ゲーム終了時の待ち時間
	int						m_nNumPlayer;		// 人数保管
	bool					m_bStart;
	bool					m_bStageCreate;		// ステージ生成時の制限
	D3DXVECTOR3				m_pos;				// 位置
	CScene2D				*m_pColon;			// コロン

	static bool m_bCountFlag;			//時間をカウントするか

};
#endif
