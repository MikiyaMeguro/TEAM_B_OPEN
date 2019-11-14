//=============================================================================
//
// �L�����Z���N�g�̏��� [CharaSelect.h]
// Author : �ڍ�������/��Ո�
//
//=============================================================================
#ifndef _CHARASELECT_H_
#define _CHARASELECT_H_

#include "scene.h"
#include "PlayerNumSelect.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_CHARASELECT			(4)
#define MAX_CHARASELTEX			(11)

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
		CHARACTORTYPE_NONE,
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

	/* �m��̉��o */
	typedef enum
	{
		CONFPRODUCTION_NONE = 0,	//�������Ȃ�
		CONFPRODUCTION_MOVE_START,	//�ړ��J�n
		CONFPRODUCTION_MOVE,		//�ړ�
		CONFPRODUCTION_MOVE_END,	//�ړ��I��
		CONFPRODUCTION_MAX

	}CONFPRODUCTION_STATE;

	void Initpointer(void);																//�|�C���^�̏�����
	void ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed);						//�e�N�X�`���X�N���[������
	void SelectProduction(SELECT_STATE &Sel, SELECT_STATE &Selold, CHARACTORTYPE type);	//���o����
	void InitCharaSelectPoly(void);														//�|�C���^�̏�����
	bool collision(int operation,CHARACTORTYPE type);									//�����蔻��
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);										//�ړ�����
	void SetCommand(void);																//�R�}���h�ݒ�
	void CharaSelTex(SELECT_STATE Sel, CHARACTORTYPE &type, CHARACTORTYPE &typeOld);	//�e�N�X�`�����W�Ǘ�
	bool ConfirmationSelect(void);														//�v���C���[���S���I���������m�F����												
	bool collisionConf(int operation);													//�m��|���Ƃ����蔻��
	bool ProductionConf(void);															//�m��|���̉��o

	static CScene2D *m_apScene2D[MAX_CHARASELTEX];	//�w�i�n�̃|�C���^
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];	//�I����
	static CScene2D *m_apCursor2D[MAX_CHARASELECT];	//�J�[�\��
	static CScene2D *m_apBadge2D[MAX_CHARASELECT];	//�o�b�W
	static CScene2D *m_apConfirm2D;					//�m��
	CHARACTORTYPE m_CharaType[MAX_CHARASELECT];		//�I�΂ꂽ�L�����̎��
	CHARACTORTYPE m_CharaTypeOld[MAX_CHARASELECT];	//�O��I�΂ꂽ�L�����̎��
	D3DXVECTOR3 m_move[MAX_CHARASELECT];			//�ړ���
	bool m_bPCSelMove[MAX_CHARASELECT];				//�I�΂�Ă��Ȃ����݈̂ړ��ł���
	int m_OperationNum;								//���ݑ��삵�Ă���v���C���[�ԍ�

	/* ���o�n�ϐ� */
	int m_nCntScrool;								//�X�N���[���̃J�E���^�[
	float m_fFlashAlpha;							//���o�̓����l�Ǘ�
	bool m_bConfProFinish, m_bConfProStart,m_bConf;	//���o���I�������
	float m_moveConfPro;							//�m��|���̈ړ�
	SELECT_STATE m_SelectState[MAX_CHARASELECT];	//���o�̏��
	SELECT_STATE m_SelectStateold[MAX_CHARASELECT];	//�O��̉��o��Ԃ��L�^
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;		//�v���C���[�̐l��
	CONFPRODUCTION_STATE m_CnfProState;				//�m��̉��o���

};
#endif