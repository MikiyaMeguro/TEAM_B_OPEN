//=============================================================================
//
// �����z�u���� [SetWord.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _SETWORD_H_
#define _SETWORD_H_

#include "main.h"
#include "scene.h"
//*****************************************************************************
//�@�O���錾
//*****************************************************************************
class CWord;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_MATTEX	(20)

//*********************************************************************
//�v���C���[�N���X�̒�`
//*********************************************************************
class CSetWord : public CScene //�h���N���X
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		bool		bUse;	// �g���Ă��邩�ǂ���
		int			nCntPop;// �o������
	}Word_Pos;
	CSetWord();
	~CSetWord();
	HRESULT Init();
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CSetWord *Create();

private:
	//�����o�ϐ�
public:
	void LoadFile(char *pFileName);

	char *ReadLine(FILE *pFile, char *pDst);	//1�s�ǂݍ���
	char *GetLineTop(char *pStr);			//�s�̐擪���擾
	int  PopString(char *pStr, char *pDest);	//�s�̍Ō��؂�̂�

	CWord *m_pWord;
	Word_Pos *m_pWordPos;
};

#endif