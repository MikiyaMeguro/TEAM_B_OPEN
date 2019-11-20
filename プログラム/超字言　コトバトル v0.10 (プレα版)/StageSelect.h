//=============================================================================
//
// �X�e�[�W�Z���N�g�̏��� [StageSelect.h]
// Author : �ڍ�������
//
//=============================================================================
#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STAGESELECT			(3)
#define MAX_STAGESELECT_TEX (3)

class CStageSelect
{
public:
	CStageSelect();
	~CStageSelect();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CStageSelect *Create(void);
	static int GetStageState(void) { return m_nSelect; }

private:
	/* �|���S���̎�� */
	typedef enum
	{
		STAGESELECTTYPE_BG = 0,		//�w�i
		STAGESELECTTYPE_BAND_L,		//�сF��
		STAGESELECTTYPE_BAND_R,		//�сF�E
		STAGESELECTTYPE_MAX			//�ő吔
	}STAGESELECTTYPE;

	/* �I����� */
	typedef enum
	{
		SELECTSTATE_SELECT_MACHINE = 0,	//�@�B�X�e�[�W
		SELECTSTATE_SELECT_WEATHER,		//�V��X�e�[�W
		SELECTSTATE_SELECT_TERRAIN,		//�n�`�X�e�[�W
		SELECTSTATE_MAX					//��Ԃ̑���
	}SELECTSTATE;

	void InitPolygon(void);										//�|���S���̏����ݒ�
	void ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed);	//�e�N�X�`���X�N���[������
	void SelectState(SELECTSTATE state);						//�I����Ԃ̊Ǘ�


	/* �ϐ� */
	static CScene2D *m_apScene2D[MAX_STAGESELECT_TEX];
	static CScene2D *m_apSelect2D[MAX_STAGESELECT];
	static int	m_nSelect;										// �I�����Ă���ԍ�
	SELECTSTATE m_state;								//�I������Ă���ԍ��̏��

	/* ���o�n�ϐ� */
	int m_nCntScrool;									//�X�N���[���̃J�E���^�[
	char *m_pcStageName[MAX_STAGESELECT];				// �X�e�[�W�̖��O�ۊ�
	D3DXVECTOR3 m_SelectPos[MAX_STAGESELECT];			//�Z���N�g�̈ʒu��ۑ�

};
#endif