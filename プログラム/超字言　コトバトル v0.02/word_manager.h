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
#define MAX_ANSWER	(7)			// �����̐�
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
	void BulletCreate(void);

	// �擾�p�̊֐�
	int GetCntNum(void) { return m_nCntNum; }
	int GetWordNum(int nNum) { return m_aWord[nNum].nNum; }

	// �f�o�b�N�p
	void CreateOblDebug(void);
	void WordDebug(int nCntNum);

private:
	TYPE_WORD m_aWord[MAX_WORD];
	D3DXVECTOR3 AnswerNum[MAX_ANSWER];
	int m_nCreateType;
	int m_nCntNum;
	int m_nCntaAnswer;
	bool m_bPress;
};

#endif
