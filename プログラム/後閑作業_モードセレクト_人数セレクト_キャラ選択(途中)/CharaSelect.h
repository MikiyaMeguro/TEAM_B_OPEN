//=============================================================================
//
// �L�����Z���N�g�̏��� [CharaSelect.h]
// Author : �ڍ�������/��Ո�
//
//=============================================================================
#ifndef _CHARASELECT_H_
#define _CHARASELECT_H_

#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CHARASELECT			(4)
#define MAX_CHARASELTEX			(7)

class CCharaSelect
{
public:
	CCharaSelect();
	~CCharaSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CCharaSelect *Create(void);

private:
	/* �|���S���̎�� */
	typedef enum
	{
		CHARASEL_POLYGONTYPE_BG = 0,	//�w�i
		CHARASEL_POLYGONTYPE_BAND_L,	//�сF��
		CHARASEL_POLYGONTYPE_BAND_R,	//�сF�E
		CHARASEL_POLYGONTYPE_MASK1,		//�}�X�N����
		CHARASEL_POLYGONTYPE_MASK2,		//�}�X�N�E��
		CHARASEL_POLYGONTYPE_MASK3,		//�}�X�N����
		CHARASEL_POLYGONTYPE_MASK4,		//�}�X�N�E��
		CHARASEL_POLYGONTYPE_MAX		//�ő吔

	}CHARASEL_POLYGONTYPE;

	/* �L�����N�^�[�̎�� */
	typedef enum
	{
		CHARACTORTYPE_BALANCE = 0,
		CHARACTORTYPE_POWOR,
		CHARACTORTYPE_SPEED,
		CHARACTORTYPE_REACH,
		CHARACTORTYPE_MAX
	}CHARACTORTYPE;

	/* �I�΂�Ă邩�̏�� */
	typedef enum
	{
		SELECTSTATE_NONE = 0,
		SELECTSTATE_FLASH,
		SELECTSTATE_SELECT,
		SELECTSTATE_NOSELECT
	}SELECT_STATE;

	void Initpointer(void);											//�|�C���^�̏�����
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);	//�e�N�X�`���X�N���[������
	void SelectProduction(int SelNum);
	void InitCharaSelectPoly(void);
	bool collision(CHARACTORTYPE type);
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);

	//void SelectState(void);
	static CScene2D *m_apScene2D[MAX_CHARASELTEX];
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];
	static CScene2D *m_apCursor2D;
	static CScene2D *m_apBadge2D;

	D3DXVECTOR3 m_move;
	bool m_bPCColl[MAX_CHARASELECT];
	bool m_bPCSelMove;

	/* ���o�n�ϐ� */
	int m_nCntScrool;
	float m_fFlashAlpha[MAX_CHARASELECT];
	SELECT_STATE m_SelectState[MAX_CHARASELECT];
	SELECT_STATE m_SelectStateold[MAX_CHARASELECT];

};
#endif