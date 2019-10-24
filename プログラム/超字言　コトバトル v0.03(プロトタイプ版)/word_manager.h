//=============================================================================
//
// �����̊Ǘ����� [word_manager.h]
// Author : ���� �x
//
//=============================================================================
#ifndef _WORE_MANAGER_H_
#define _WORE_MANAGER_H_

#include "main.h"

//===================================================================
// �}�N����`
//===================================================================
#define MAX_WORD	(3)			// ������
#define MAX_ANSWER	(10)			// �����̐�
//===================================================================
// �N���X�̒�`
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

	// ��{�֐�
	void Init(void);
	void Uninit(void);
	void Update(void);

	CWordManager();
	~CWordManager();

	void Reset(void);	// ���Z�b�g
	void Delete(void);	// �폜

	// �ݒ�̊֐�
	void SetWord(int nType);
	void BulletCreate(int nID,D3DXVECTOR3 BulletMuzzle);	//BulletMuzzle = �e���o��ʒu
	void SetID(int nID) { m_nPlayerID = nID; }

	// �擾�p�̊֐�
	int GetCntNum(void) { return m_nCntNum; }
	int GetWordNum(int nNum) { return m_aWord[nNum].nNum; }
	bool GetBulletFlag(void) { return m_bPress; }		// �e�����Ă�悤�ɂȂ����

	// �f�o�b�N�p
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
