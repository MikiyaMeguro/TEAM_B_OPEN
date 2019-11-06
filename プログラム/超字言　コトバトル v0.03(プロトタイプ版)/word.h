//=============================================================================
//
// �����̃r���{�[�h�̏��� [word.h]
// Author :  Shun Yokomici
//
//=============================================================================
#ifndef _WORD_H_
#define _WORD_H_

#include "sceneBillboard.h"
#include "game.h"

//*********************************************************************
//�r���{�[�h�N���X�̒�`
//*********************************************************************
class CWord : public CSceneBillBoard //�h���N���X
{
public:
	CWord();
	~CWord();
	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWord *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord);

	// �֐�
	D3DXVECTOR3 Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle, float fDistance);
	void Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle);				// �~�����
	void Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNumPlayer);							// ���������𑪂�
	int ComparisonDistance(int nNumPlayer);		// �����̔�r

	// �擾 �������� �ݒ�̊֐�
	int GetWordNum(void) { return m_nWordNum; }	// �����ԍ����擾
private:
	D3DXVECTOR3 Move(D3DXVECTOR3 pos);
	void ScaleSize(void);

	D3DXVECTOR3 m_size;		// �T�C�Y
	D3DXVECTOR3 m_sizeOld;	// �T�C�Y(�ߋ�)
	bool m_bFlagUninit;		// �I�����邽�߂̃t���O
	bool m_bMoveFlag;		// �㉺�ړ��̃t���O
	bool m_bScaleFlag;		// �g��k������t���O
	int m_nWordNum;			// �����̔ԍ�
	int m_nNumPlayerGet;	// �擾���ꂽ���̃v���C���[�̔ԍ�
	float m_fDistance[MAX_PLAYER];	// �v���C���[�Ƃ̋���

	int		   m_nCntUninit;	// �I������܂ł̃J�E���g
};

#endif