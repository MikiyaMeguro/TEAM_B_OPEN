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
	void BulletCreate(int nID,D3DXVECTOR3 BulletMuzzle,D3DXVECTOR3 BulletRot);	//BulletMuzzle = �e���o��ʒu	BulletRot = �e���o��p�x
	void SetID(int nID) { m_nPlayerID = nID; }
	static void SetWordLoad(int nNumModel, D3DXVECTOR3 AnswerNum);	// �t�@�C�����烊�\�[�X�̓ǂݍ���
	static void SetWordAnswerNum(int nAnswerNum);
	int SearchWord(void);							// �����̑g�ݍ��킹���������ǂ���


	// �擾�p�̊֐�
	int GetCntNum(void) { return m_nCntNum; }
	int GetWordNum(int nNum) { return m_aWord[nNum].nNum; }
	bool GetBulletFlag(void) { return m_bPress; }		// �e�����Ă�悤�ɂȂ����
	float *GetAnswerData(void) { return m_fAnswerData; }	// 2�����̎��ɑg�ݍ��킹�邱�Ƃ��o���镶���f�[�^�̎擾
	static D3DXVECTOR3 *GetAnswerNum(void) { return m_AnswerNum; }
	static int GetAnswerDataNum(void) { return m_nAnswerDataNum; }
	// �f�o�b�N�p
	void CreateOblDebug(void);
	void WordDebug(int nCntNum);

private:
	TYPE_WORD m_aWord[MAX_WORD];
	static int m_nAnswerDataNum;
	static D3DXVECTOR3 *m_AnswerNum;
	int m_nCreateType;
	int m_nCntNum;
	int m_nCntaAnswer;
	int m_nPlayerID;
	float *m_fAnswerData;
	bool m_bPress;
	bool m_bSearch;					// �T�[�`�̃t���O
	bool m_bAnswer[MAX_ANSWER];
};

#endif
