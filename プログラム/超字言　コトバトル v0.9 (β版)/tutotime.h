//=============================================================================
//
// 制限時間処理 [tutotime.h]
// Author : Meguro Mikiya
//
//=============================================================================
#ifndef _TUTOTIME_H_
#define _TUTOTIME_H_

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
#define TUTOTIME_MAX		(2)		// タイマーの桁数
#define PLAYER_MAX			(4)		// プレイヤー最大数

//*****************************************************************************
// クラス定義
//*****************************************************************************
class CTutoTime : public CScene
{
public:
	CTutoTime(int nPriority = 6, OBJTYPE objType = OBJTYPE_TUTOTIME);
	~CTutoTime();

	static CTutoTime *Create(int nNumPlayer);
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
	static int GetSatgeNum(void) { return m_nStageNum; }		// ステージ形態の取得
private:
	void DebugKey(void);
	void TimeManagement(void);
	int PowerCalculation(int nData, int nOperation);
	void ChangeStage(void);				// ステージが切り替わることを知らせる演出
	void DefaultCol(void);				// 数字などをdefaultの色に戻す
	void CountDown(void);				// カウントダウン


	CNumber *m_apNumber[TUTOTIME_MAX][PLAYER_MAX];			// ナンバーへのポインタ
	static int				m_nTime;			// 時間
	static int				m_nTimeCount;		// 時間のカウンタ
	static int				m_nTimeOld;
	static int				m_nTimeOne;
	static int				m_nStageNum;
	int						m_nTimeNum;			// 時間の表示数字数
	int						m_nWaitTime;		// ゲーム終了時の待ち時間
	int						m_nNumPlayer;		// 人数保管
	bool					m_bStart;
	D3DXVECTOR3				m_pos;				// 位置

	static bool m_bCountFlag;			//時間をカウントするか
};
#endif
