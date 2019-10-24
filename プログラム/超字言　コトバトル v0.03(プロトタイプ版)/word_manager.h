//=============================================================================
//
// 文字の管理処理 [word_manager.h]
// Author : 横道 駿
//
//=============================================================================
#ifndef _WORE_MANAGER_H_
#define _WORE_MANAGER_H_

#include "main.h"

//===================================================================
// マクロ定義
//===================================================================
#define MAX_WORD	(3)			// 文字数
#define MAX_ANSWER	(10)			// 答えの数
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
	void Delete(void);	// 削除

	// 設定の関数
	void SetWord(int nType);
	void BulletCreate(int nID,D3DXVECTOR3 BulletMuzzle);	//BulletMuzzle = 弾が出る位置
	void SetID(int nID) { m_nPlayerID = nID; }

	// 取得用の関数
	int GetCntNum(void) { return m_nCntNum; }
	int GetWordNum(int nNum) { return m_aWord[nNum].nNum; }
	bool GetBulletFlag(void) { return m_bPress; }		// 弾が撃てるようになる条件

	// デバック用
	void CreateOblDebug(void);
	void WordDebug(int nCntNum);

private:
	TYPE_WORD m_aWord[MAX_WORD];
	D3DXVECTOR3 AnswerNum[MAX_ANSWER];
	int m_nCreateType;
	int m_nCntNum;
	int m_nCntaAnswer;
	int m_nPlayerID;
	bool m_bPress;
	bool m_bAnswer[MAX_ANSWER];
};

#endif
