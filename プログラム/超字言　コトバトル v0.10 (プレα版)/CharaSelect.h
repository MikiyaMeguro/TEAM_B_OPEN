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
#include "player.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CPlayer;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_PLAYER				(4)
#define MAX_CHARASELECT			(5)
#define MAX_CHARASELTEX			(15)

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
		CHARASEL_POLYGONTYPE_BG = 0,		//�w�i
		CHARASEL_POLYGONTYPE_BAND_L,		//�сF��
		CHARASEL_POLYGONTYPE_BAND_R,		//�сF�E
		CHARASEL_POLYGONTYPE_MASK1,			//�}�X�NPL_1
		CHARASEL_POLYGONTYPE_MASK2,			//�}�X�NPL_2
		CHARASEL_POLYGONTYPE_MASK3,			//�}�X�NPL_3
		CHARASEL_POLYGONTYPE_MASK4,			//�}�X�NPL_4
		CHARASEL_POLYGONTYPE_PLUI_CHARA1,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_1
		CHARASEL_POLYGONTYPE_PLUI_CHARA2,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_2
		CHARASEL_POLYGONTYPE_PLUI_CHARA3,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_3
		CHARASEL_POLYGONTYPE_PLUI_CHARA4,	//�I���L�������e�v���C���[�̃E�B���h�E�ɕ\��:PL_4
		CHARASEL_POLYGONTYPE_MAX			//�ő吔

	}CHARASEL_POLYGONTYPE;

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
	void SelectProduction(SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type);	//���o����
	void InitCharaSelectPoly(void);														//�|�C���^�̏�����
	bool collision(int operation,CPlayer::PLAYER_TYPE type);									//�����蔻��
	D3DXVECTOR3 MoveRestriction(D3DXVECTOR3 pos);										//�ړ�����
	void SetCommand(void);																//�R�}���h�ݒ�
	void CharaSelTex(SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type, CPlayer::PLAYER_TYPE &typeOld);	//�e�N�X�`�����W�Ǘ�
	bool ConfirmationSelect(void);														//�v���C���[���S���I���������m�F����												
	bool collisionConf(int operation);													//�m��|���Ƃ����蔻��
	bool ProductionConf(void);															//�m��|���̉��o
	void FlashConf(void);																//�m��|���̓_��
	static CScene2D *m_apScene2D[MAX_CHARASELTEX];		//�w�i�n�̃|�C���^
	static CScene2D *m_apSelect2D[MAX_CHARASELECT];		//�I����
	static CScene2D *m_apCursor2D[MAX_PLAYER];			//�J�[�\��
	static CScene2D *m_apBadge2D[MAX_PLAYER];			//�o�b�W
	static CScene2D *m_apConfirm2D;						//�m��
	CPlayer::PLAYER_TYPE m_CharaType[MAX_PLAYER];		//�I�΂ꂽ�L�����̎��
	CPlayer::PLAYER_TYPE m_CharaTypeOld[MAX_PLAYER];	//�O��I�΂ꂽ�L�����̎��
	CPlayer::PLAYER_TYPE m_CharaTypeFinal[MAX_PLAYER];	//�ŏI�I�ɑI�΂ꂽ�L�����̎��
	D3DXVECTOR3 m_move[MAX_PLAYER];						//�ړ���
	bool m_bPCSelMove[MAX_PLAYER];						//�I�΂�Ă��Ȃ����݈̂ړ��ł���
	int m_OperationNum;									//���ݑ��삵�Ă���v���C���[�ԍ�

	/* ���o�n�ϐ� */
	int m_nCntScrool, m_CntFlash, m_CntFadeF;		//�X�N���[���̃J�E���^�[/�m�莞�̃t���b�V��/�J�ڂ܂ł̕b���J�E���^�[
	float m_fFlashAlpha;							//���o�̓����l�Ǘ�
	bool m_bConfProFinish, m_bConfProStart,m_bConf;	//���o���I�������
	bool m_bCnfFlash;								//�m�F�|���̃t���V���J�n
	float m_moveConfPro;							//�m��|���̈ړ�
	SELECT_STATE m_SelectState[MAX_PLAYER];			//���o�̏��
	SELECT_STATE m_SelectStateold[MAX_PLAYER];		//�O��̉��o��Ԃ��L�^
	CPlayerSelect::SELECTPLAYER *m_PlayerNum;		//�v���C���[�̐l��
	CONFPRODUCTION_STATE m_CnfProState;				//�m��̉��o���

};
#endif