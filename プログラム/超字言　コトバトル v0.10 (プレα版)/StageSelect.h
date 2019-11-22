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
class CFade;
class CManager;
class CSetObject;
class CMeshField;
class CWall;
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STAGESELECT		(3)
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
		SELECTTYPE_SELECT_MACHINE = 0,			//�@�B�X�e�[�W
		SELECTTYPE_SELECT_WEATHER,				//�V��X�e�[�W
		SELECTTYPE_SELECT_TERRAIN,				//�n�`�X�e�[�W
		SELECTTYPE_MAX							//��Ԃ̑���
	}SELECTTYPE;

	/* �I�����ړ��̏�� */
	typedef enum
	{
		SELECTICON_STATE_NONE = 0,
		SELECTICON_STATE_MOVE_R,	//�E���
		SELECTICON_STATE_MOVE_L,	//�����
		SELECTICON_STATE_STOP,
		SELECTICON_STATE_MAX
	}SELECTICONSTATE;

	/* �X�e�[�W�ǂݍ��݂̏�� */
	typedef enum
	{
		STAGELOAD_NONE = 0,
		STAGELOAD_LOAD,
		STAGELOAD_UNLOAD,
		STAGELOAD_MAX
	}STAGELOAD;

	/* �}�X�N�̃t�F�[�h��� */
	typedef enum
	{
		MASKFADE_NONE = 0,
		MASKFADE_IN,
		MASKFADE_OUT,
		MASKFADE_MAX
	}MASKFADE;

	void InitPolygon(void);												//�|���S���̏����ݒ�
	void ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed);			//�e�N�X�`���X�N���[������
	void Selecttype(SELECTTYPE state, CFade *pFade, CManager *pManager);//�I����Ԃ̊Ǘ�
	void ProductionIcon(SELECTICONSTATE &state, SELECTTYPE type);		//�I�����̈ړ����o
	void Replacement(SELECTICONSTATE state);							//�|���S���ʒu�̓���ւ�����
	void SetStage(int nNumState);										//�X�e�[�W�����̏���
	void LoadStage(int nNum);											//�X�e�[�W�̃��[�h����
	void StageLoadState(STAGELOAD Load,int nSel);										//�X�e�[�W���[�h�̏��
	void MaskFade(void);												//�}�X�N�̃t�F�[�h����

	/* �ϐ� */
	static CScene2D *m_apScene2D[MAX_STAGESELECT_TEX];				//���o�n2D
	static CScene2D *m_apSelect2D[MAX_STAGESELECT];					//�I����2D
	static CScene2D *m_pMask2D;										//�J�����}�X�N
	static int	m_nSelect;											// �I�����Ă���ԍ�
	static CMeshField *m_pMeshField;
	static CWall *m_pWall;
	SELECTTYPE m_type;												//�I������Ă���ԍ��̏��
	char *m_pcStageName[MAX_STAGESELECT];							// �X�e�[�W�̖��O�ۊ�
	CSetObject *m_pObj;

	/* ���o�n�ϐ� */
	int m_nCntScrool;												//�X�N���[���̃J�E���^�[
	char *m_pcStageSelect[MAX_STAGESELECT];							// �X�e�[�W�̖��O�ۊ�
	D3DXVECTOR3 m_SelectPos[MAX_STAGESELECT];						//�Z���N�g�̈ʒu��ۑ�
	SELECTICONSTATE m_MoveIconState;								//�ړ��̏��
	float m_fWidth[MAX_STAGESELECT], m_fHeight[MAX_STAGESELECT];	//�c�Ɖ��̌`��ۑ����Ă���
	D3DXCOLOR m_IconCol[MAX_STAGESELECT];							//�F��ۑ����Ă���
	bool m_bRep;													//����ւ�����񂾂����t���O
	D3DXVECTOR3 m_CameraRot, m_CameraPosV,m_CameraPosR;				//�J����
	bool m_bLoad;													//�X�e�[�W�̓ǂݍ��݂��P�񂾂����t���O
	MASKFADE m_MaskFade;											//�}�X�N�̃t�F�[�h����
	float m_fMaskAlpha;
};
#endif