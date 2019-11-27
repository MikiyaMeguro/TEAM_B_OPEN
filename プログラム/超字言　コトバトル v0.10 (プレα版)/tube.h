//=============================================================================
//
// �����ۊ�UI�̏��� [tube.h]
// Author : Shun Yokomichi
//
//=============================================================================
#ifndef _TUBE_H_
#define _TUBE_H_

#include "scene2D.h"
#include "word_manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CTube : public CScene2D
{
public:
	CTube(int nPriority = 3, OBJTYPE objType = OBJTYPE_UI);											// �R���X�g���N�^
	~CTube();										// �f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos);				// 2D�I�u�W�F�N�g����������
	virtual void Uninit(void);							// 2D�I�u�W�F�N�g�I������
	virtual void Update(void);							// 2D�I�u�W�F�N�g�X�V����
	virtual void Draw(void);							// 2D�I�u�W�F�N�g�`�揈��

	static CTube *Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,LPCSTR Tag, int nPriority = 3);				// �I�u�W�F�N�g�̐���

	//�ݒ�̊֐�
	void SetWordNum(int nWordNum, int nNum, int nStock);
	void SetPoint(int nPoint, int nNum, bool bPoint);
	void SetAnswer(int nAnswer, int nStock);
	void SetStockNum(int nStock) { m_nStockNum = nStock; }
	void AllDelete(void);
	void Delete(int nID, int nStock);
private:
	void Collect(void);		//�������W�߂�Tex�𐶐�
	void Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNum);

	D3DXVECTOR3 m_AnswerPos;
	CScene2D *m_apWord[MAX_WORD];
	CScene2D *m_pAnswerModel[MAX_WORD];
	int		  m_nAnswer;

	bool	 m_bModelTexFlag;
	int m_nAnswerModelNum;	// �����̔ԍ�
	int m_nStockNum;

};

#endif