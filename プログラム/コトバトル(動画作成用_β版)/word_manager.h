//=============================================================================
//
// 文字の管理処理 [word_manager.h]
// Author : 横道 駿
//
//=============================================================================
#ifndef _WORE_MANAGER_H_
#define _WORE_MANAGER_H_

#include "main.h"
#include "charactor.h"
#include "player.h"
//===================================================================
// マクロ定義
//===================================================================
#define MAX_WORD	(3)			// 文字数
#define NOT_NUM		(99)		// ゴミを示す数字
#define EMPTINESS_NUM	(100)	// 空の数字
//===================================================================
// クラスの定義
//===================================================================
class CWordManager
{
public:
	typedef struct
	{
		int nNum;
		char *cWord;
		bool bClearFlag;

	}TYPE_WORD;

	// 基本関数
	void Init(void);
	void Uninit(void);
	void Update(void);

	CWordManager();
	~CWordManager();

	void Reset(void);	// リセット

	// 設定の関数
	void SetWord(int nType);
	void BulletCreate(int nID, D3DXVECTOR3 BulletMuzzle, D3DXVECTOR3 BulletRot, CPlayer::PLAYER_TYPE type, C3DCharactor* pChara = NULL);	//BulletMuzzle = 弾が出る位置	BulletRot = 弾が出る角度
	void SetID(int nID) { m_nPlayerID = nID; }
	static void SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum, D3DXVECTOR3 scale, D3DXVECTOR3 rot, int type, int Model, int nPoint);	// ファイルからリソースの読み込み
	static void SetWordAnswerNum(int nAnswerNum);
	int SearchWord(void);							// 文字の組み合わせが合うかどうか


	// 取得用の関数
	int GetCntNum(void) { return m_nCntNum; }
	int GetWordNum(int nNum) { return m_aWord[nNum].nNum; }
	int GetAnswer(void) { return m_nCreateType;	}		// 持っている文字で作れるモデルの番号を取得
	int GetStockNum(void) { return m_nCntStock; }		// ストック数の取得
	bool GetBulletFlag(void) { return m_bPress; }		// 弾が撃てるようになる条件
	float *GetAnswerData(void) { return m_fAnswerData; }	// 2文字の時に組み合わせることが出来る文字データの取得
	static D3DXVECTOR3 *GetAnswerNum(void) { return m_AnswerNum; }
	static int GetAnswerDataNum(void) { return m_nAnswerDataNum; }
	bool GetGatherFlag(void) { return m_bGatherFlag; }
	int GetStock(int nStockNum) { return m_nStock[nStockNum]; }		// ストック数の取得

	// デバック用
	void CreateOblDebug(void);
	void WordDebug(int nCntNum);

private:
	void SearchAssist(int nCntData);
	void UninitAssist(void);

	TYPE_WORD m_aWord[MAX_WORD];
	static int m_nAnswerDataNum;
	static D3DXVECTOR3 *m_AnswerNum;
	static D3DXVECTOR3 *m_Scale;
	static D3DXVECTOR3 *m_rot;
	static int *m_type;
	static int *m_nAnswerTypeModel;
	static int *m_nPoint;

	int m_nCreateType;
	int m_nCntNum;
	int m_nCntaAnswer;
	int m_nPlayerID;
	int m_nCntStock;
	int m_nStock[MAX_WORD];				// 答えモデルのストック
	float *m_fAnswerData;
	bool m_bPress;
	bool m_bSearch;					// サーチのフラグ
	bool m_bAnswer[MAX_WORD];
	bool m_bFlag;
	bool m_bAnswerCheck;
	bool m_bGatherFlag;		// 集めるフラグ

	/* デバック用*/
	void DebugWordCreate(void);
	int nDebugNUm;
	int nDebugCnt;
};

#endif
