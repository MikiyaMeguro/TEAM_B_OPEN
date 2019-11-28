//=============================================================================
//
// �L�����Z���N�g���� [CharaSelect.cpp]
// Author : �ڍ� ������/��Ձ@��
//
//=============================================================================
#include "CharaSelect.h"
#include "manager.h"
#include "debugProc.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include"game.h"
//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//����
#define SIZE_Y (SCREEN_HEIGHT/2)								//�c��
#define DEFAULT_SIZE (150.0f)									//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//�|���S���̏����ʒu
#define CHARASELCHOICE_POS	(D3DXVECTOR3(211.0f,230.0f,0.0f))	//�I�����|���S���̈ʒu
#define CURSOL_INITPOS (D3DXVECTOR3(250.0f,545.0f,0.0f))		//�J�[�\���̏����ʒu
#define CHARASELCHOICE_INTERVAL (260.0f)						//�I�����|���S�����m�̊Ԋu
#define CHARASELICON_INTERVAL (215.0f)							//�I�����A�C�R�����m�̊Ԋu
#define TEX_CORRECTION (0.001f)									//�e�N�X�`�����W�̕␳
#define CURSOR_MOVE (3.0f)										//�J�[�\���̈ړ����x
#define CURSOR_SIZE (0.3f)										//�J�[�\���̃T�C�Y

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apCursor2D[MAX_PLAYER] = {};
CScene2D *CCharaSelect::m_apBadge2D[MAX_PLAYER] = {};
CScene2D *CCharaSelect::m_apConfirm2D = NULL;
CScene2D *CCharaSelect::m_apGauge2D[MAX_PLAYER] = {};

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_PlayerNum = NULL;
	/* ���o�n�ϐ������� */
	m_nCntScrool = 0;
	m_CntFlash = 0;
	m_CntFadeF = 0;
	m_moveConfPro = 0.0f;
	m_CnfProState = CONFPRODUCTION_NONE;
	m_bConfProFinish = false;
	m_bConf = false;
	m_bConfProStart = false;
	m_bCnfFlash = false;
	m_bCharaCard = false;
	m_CharaCardProduction = CHARACARDPRO_START;
	m_fCharaCardPro_FinishWH[0] = 0.0f;
	m_fCharaCardPro_FinishWH[1] = 0.0f;
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_fFlashAlpha[nCnt] = 0.0f;
		m_fGaugeSizeX[nCnt] = 0.0f;
		m_fMaxGaugeX[nCnt]= 0.0f;
		m_nCntGauge[nCnt] = 0;
		m_move[nCnt] = DEFAULT_POS;
		m_SelectState[nCnt] = SELECTSTATE_NOSELECT;
		m_SelectStateold[nCnt] = SELECTSTATE_NOSELECT;
		m_bPCSelMove[nCnt] = false;
		m_CharaType[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeOld[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeFinal[nCnt] = CPlayer::TYPE_MAX;
		m_bBackMode[nCnt] = false;
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		m_CharaCardPro_FinishPos[nCnt] = DEFAULT_POS;
		m_fCardWidth[nCnt][0] = m_fCharaCardPro_FinishWH[0];
		m_fCardWidth[nCnt][1] = m_fCharaCardPro_FinishWH[1];
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CCharaSelect::~CCharaSelect()
{

}

//=============================================================================
// �L�����Z���N�g�̏���������
//=============================================================================
void CCharaSelect::Init(void)
{
	//�C���X�^���X
	CManager *pManager = NULL;

	/* �|�C���^�̏��������� */
	Initpointer();

	/* �|���S���̏����ݒ� */
	InitCharaSelectPoly();

	/* �R�}���h�ݒ� */
	SetCommand();
}

//=============================================================================
// �L�����Z���N�g�̏I������
//=============================================================================
void CCharaSelect::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL)
		{
			m_apSelect2D[nCnt]->Uninit();
			m_apSelect2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apCursor2D[nCnt] != NULL)
		{
			m_apCursor2D[nCnt]->Uninit();
			m_apCursor2D[nCnt] = NULL;
		}
		if (m_apBadge2D[nCnt] != NULL)
		{
			m_apBadge2D[nCnt]->Uninit();
			m_apBadge2D[nCnt] = NULL;
		}
		if (m_apGauge2D[nCnt] != NULL)
		{
			m_apGauge2D[nCnt]->Uninit();
			m_apGauge2D[nCnt] = NULL;
		}
	}
	if (m_apConfirm2D != NULL)
	{
		m_apConfirm2D->Uninit();
		m_apConfirm2D = NULL;
	}

	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �L�����Z���N�g�̍X�V����
//=============================================================================
void CCharaSelect::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	/*�J�[�h���o*/
	if (m_bCharaCard == false)
	{
		ProductionCard();
	}

	if (ConfirmationSelect() == true)
	{//�S���I������
		if (m_bConfProStart == false)
		{//���o���n�܂��Ă��Ȃ�������n�߂�
			m_CnfProState = CONFPRODUCTION_MOVE_START;
			m_bConfProStart = true;
		}
		if (m_bConfProStart == true)
		{//���o���n�܂�����
			m_bConfProFinish = ProductionConf();
		}
		if (m_bConfProFinish == true)
		{//���o���I������

			m_bConf = true;	//�I�𑀍�\�ɂ���
		}
	}
	else
	{//�S���I�����Ă��Ȃ�
		m_apConfirm2D->SetbDraw(false);
		m_bConfProFinish = false;
		m_bConf = false;
		m_bConfProStart = false;
	}
	//���[�h�J��
	if (m_bCharaCard == true)
	{
		for (int nCntXinput = 0; nCntXinput < (int)*m_PlayerNum; nCntXinput++)
		{
			Move(pFade, pManager, nCntXinput);
		}
	}

	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* �m��|���̃t���b�V�����o */
	if (m_bCnfFlash == true) { FlashConf(); }
#ifdef _DEBUG
	CDebugProc::Print("c", "�L�����Z���N�g");
#endif
}

//=============================================================================
// �L�����Z���N�g�̕`�揈��
//=============================================================================
void CCharaSelect::Draw(void)
{

}
//=============================================================================
// �R�}���h�̐ݒ�
//=============================================================================
void CCharaSelect::SetCommand(void)
{
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RIGHT);
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_D);
	CCommand::RegistCommand("RIGHT_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT);

	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_LEFT);
	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_A);
	CCommand::RegistCommand("LEFT_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT);

	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_UP);
	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_W);
	CCommand::RegistCommand("UP_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_UP);

	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_DOWN);
	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_S);
	CCommand::RegistCommand("DOWN_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_DOWN);

	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_TRIGGER, DIK_BACKSPACE);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_X);
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_TRIGGER, CInputXPad::XPAD_LEFT_SHOULDER);

	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_RETURN);
	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_A);
	CCommand::RegistCommand("RELEASE_R", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_RIGHT_SHOULDER);

	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_KEYBOARD, CCommand::INPUTSTATE_PRESS, DIK_BACKSPACE);
	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
	CCommand::RegistCommand("RELEASE_L", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_LEFT_SHOULDER);

}

//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CCharaSelect::Initpointer(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL) { m_apScene2D[nCnt] = NULL; }
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL) { m_apSelect2D[nCnt] = NULL; }
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		if (m_apCursor2D[nCnt] != NULL) { m_apCursor2D[nCnt] = NULL; }
		if (m_apBadge2D[nCnt] != NULL) { m_apBadge2D[nCnt] = NULL; }
		if (m_apGauge2D[nCnt] != NULL) { m_apGauge2D[nCnt] = NULL; }
	}
	if (m_apConfirm2D != NULL) { m_apConfirm2D = NULL; }
}
//=============================================================================
// �|���S���̏����ݒ�
//=============================================================================
void CCharaSelect::InitCharaSelectPoly(void)
{
	/* �v���C���[�̐l���擾 */
	m_PlayerNum = CPlayerSelect::GetModeSelectMode();

	/* �I���� */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELICON_INTERVAL*nCnt),
			CHARASELCHOICE_POS.y,
			CHARASELCHOICE_POS.z), "PLAYERSELECT_BACK");
		/* �T�C�Y�ݒ� */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);

		m_CharaCardPro_FinishPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();
		m_fCharaCardPro_FinishWH[0] = m_apSelect2D[nCnt]->GetSize(0);
		m_fCharaCardPro_FinishWH[1] = m_apSelect2D[nCnt]->GetSize(1);
		m_fCardWidth[nCnt][0] = m_apSelect2D[nCnt]->GetSize(0);
		m_fCardWidth[nCnt][1] = m_apSelect2D[nCnt]->GetSize(1);
	}

	/* ���o */
	// �w�i
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAYERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//���[�h���сi���j
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//���[�h���сi�E�j
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//�߂�
	m_apScene2D[3] = CScene2D::Create(D3DXVECTOR3(SIZE_X, (DEFAULT_SIZE*0.4f) / 2, 0.0f), "CHARASEL_BACKMODE");
	m_apScene2D[3]->SetWidthHeight(DEFAULT_SIZE*5.2f, DEFAULT_SIZE*0.4f);
	m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//�v���C���[�E�B���h
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 4] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "PLAYER_UIWINDOW", 2);
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 4]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));//�����ݒ�͑S��COM�A����SWICH�ōĐݒ�

		// �v���C���[�E�B���h�}�X�N
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 8] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), " ");
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 8]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 8]->SetbDraw(false);

		//�v���C���[�E�B���h�E�ɕ\������L�����N�^�[
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 12] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y + 20.0f,
			CURSOL_INITPOS.z), "CHARACTORSEL_CHARA", 2);
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 12]->SetWidthHeight(DEFAULT_SIZE*1.1f, DEFAULT_SIZE*1.2f);
		m_apScene2D[nCnt + 12]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 1.0f));
		m_apScene2D[nCnt + 12]->SetbDraw(false);

		//�o�b�W
		m_apBadge2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE");
		m_apBadge2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		//�J�[�\��
		m_apCursor2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE", 4);
		m_apCursor2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		//�߂钷�������̃Q�[�W
		m_apGauge2D[nCnt] = CScene2D::Create(D3DXVECTOR3(m_apCursor2D[nCnt]->GetPosition().x-45.0f,
			m_apCursor2D[nCnt]->GetPosition().y+50.0f,
			m_apCursor2D[nCnt]->GetPosition().z), " ", 4);
		m_apGauge2D[nCnt]->SetScene2DLeftCenter(m_apGauge2D[nCnt]->GetPosition(), DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*0.03f);
		m_apGauge2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_fMaxGaugeX[nCnt] = m_apGauge2D[nCnt]->GetSize(0);
		m_apGauge2D[nCnt]->SetbDraw(false);

		/* �v���C���[�l���ɍ��킹�Đݒ� */
		if (nCnt < (int)*m_PlayerNum)
		{
			//�J�[�\���ƃo�b�W
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.5f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.0f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 0.5f));
			// �v���C���[�E�B���h�E�̃e�N�X�`�����W
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nCnt), D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nCnt));
		}
		else
		{
			//�J�[�\���ƃo�b�W
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			// �v���C���[�E�B���h�E�̃e�N�X�`�����W
			m_apScene2D[nCnt + 4]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));
		}
	}

	/* �L�����I���m�� */
	m_apConfirm2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "PLAYER_CONFIRM");
	m_apConfirm2D->SetWidthHeight(DEFAULT_SIZE*4.5f, DEFAULT_SIZE*0.8f);
	m_apConfirm2D->SetbDraw(false);
}
//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CCharaSelect::ScrollMenu(CHARASEL_POLYGONTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;
	if (m_apScene2D[type] != NULL)
	{
		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)),
									D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}
//=============================================================================
// �I�����o����
//=============================================================================
void CCharaSelect::SelectProduction(int nNum, SELECT_STATE &Sel, SELECT_STATE &Selold, CPlayer::PLAYER_TYPE type)
{
	switch (Sel)
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//���o��
		if (Selold != SELECTSTATE_FLASH)
		{//�O��̃��[�h��Flash�ȊO�̏ꍇa�l��������
			m_fFlashAlpha[nNum] = 1.0f;
		}
		m_apScene2D[nNum + 8]->SetbDraw(true);											//�}�X�N�̕`�悷��
		m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[nNum]));	//�F
		CharaSelTex(nNum, SELECTSTATE_SELECT, type, m_CharaTypeOld[nNum]);

		if (m_fFlashAlpha[nNum] <= 0.0f)
		{//�����x��������؂���
			m_apScene2D[nNum + 8]->SetbDraw(false);								//�}�X�N��`�悵�Ȃ��󋵂�
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�}�X�N�̐F����ɖ߂��Ă���
			m_fFlashAlpha[nNum] = 0.0f;												//a�l���Y��Ȑ����ɕύX
			m_SelectState[type] = SELECTSTATE_SELECT;							//�I�����ꂽ��ԂɕύX
		}
		else
		{
			m_fFlashAlpha[nNum] -= 0.02f;
			m_apScene2D[nNum + 8]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[nNum]));
		}
		break;

	case SELECTSTATE_SELECT:	//�I������Ă���
		if (m_apScene2D[nNum + 8]->GetbDraw() != false)
		{
			m_apScene2D[nNum + 8]->SetbDraw(false);
		}
		break;

	case SELECTSTATE_NOSELECT:	//�I������Ă��Ȃ�
		if (m_apScene2D[nNum + 8]->GetbDraw() != false)
		{
			m_apScene2D[nNum + 8]->SetbDraw(false);
		}
		CharaSelTex(nNum, SELECTSTATE_NOSELECT, type, m_CharaTypeOld[nNum]);
		break;
	}

	//����̑I����Ԃ�O��̑I����ԂƂ��ĕۑ�
	Selold = Sel;
}
//=============================================================================
// �J�[�\���̈ړ�����
//=============================================================================
D3DXVECTOR3 CCharaSelect::MoveRestriction(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 mPos;
	mPos = pos;

	if (pos.y <= 0.0f + (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.y = 0.0f + (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.y >= SCREEN_HEIGHT - (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.y = SCREEN_HEIGHT - (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.x <= 100.0f + (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.x = 100.0f + (DEFAULT_SIZE*CURSOR_SIZE);
	}
	if (pos.x >= 1180.0f - (DEFAULT_SIZE*CURSOR_SIZE))
	{
		mPos.x = 1180.0f - (DEFAULT_SIZE*CURSOR_SIZE);
	}

	return mPos;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CCharaSelect::collision(int operation, CPlayer::PLAYER_TYPE type)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apBadge2D[operation]->GetPosition().x - (m_apBadge2D[operation]->GetSize(0) / 2) <= m_apSelect2D[type]->GetPosition().x + (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apBadge2D[operation]->GetPosition().x + (m_apBadge2D[operation]->GetSize(0) / 2) >= m_apSelect2D[type]->GetPosition().x - (m_apSelect2D[operation]->GetSize(0) / 2) &&
		m_apBadge2D[operation]->GetPosition().y + (m_apBadge2D[operation]->GetSize(1) / 2) >= m_apSelect2D[type]->GetPosition().y - (m_apSelect2D[operation]->GetSize(1) / 2) &&
		m_apBadge2D[operation]->GetPosition().y - (m_apBadge2D[operation]->GetSize(1) / 2) <= m_apSelect2D[type]->GetPosition().y + (m_apSelect2D[operation]->GetSize(1) / 2))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// �e�N�X�`�����W�Ǘ�
//=============================================================================
void CCharaSelect::CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type, CPlayer::PLAYER_TYPE &typeOld)
{
	switch (Sel)
	{/* �I�΂ꂽ���̃e�N�X�`�����W */
	case SELECTSTATE_SELECT:	//�I�΂�Ă���
		m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.2f + (1.0f / 5)*(int)type, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.4f + (1.0f / 5)*(int)type, 0.2f + (1.0f / 5)*nNum));
		if (type == CPlayer::TYPE_MAX)
		{//�����_���̏ꍇ
			m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
				D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
		}
		break;
	case SELECTSTATE_NOSELECT:
		m_apScene2D[nNum + 4]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
		break;
	}

	//�O��̎�ނ����݂̎�ނɏ���������
	typeOld = type;
}
//=============================================================================
// �v���C���[���S���I���������m�F����
//=============================================================================
bool CCharaSelect::ConfirmationSelect(void)
{
	bool bCnfirmation = false;
	int nCount = 0;
	for (int nCnt = 0; nCnt < (int)*m_PlayerNum; nCnt++)
	{
		if (m_bPCSelMove[nCnt] == true)
		{
			nCount++;
		}
	}

	if (nCount == (int)*m_PlayerNum)
	{
		bCnfirmation = true;
	}
	return bCnfirmation;
}
//=============================================================================
// �����蔻��
//=============================================================================
bool CCharaSelect::collisionConf(int operation)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apCursor2D[operation]->GetPosition().x - (m_apCursor2D[operation]->GetSize(0) / 2) <= m_apConfirm2D->GetPosition().x + m_apConfirm2D->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().x + (m_apCursor2D[operation]->GetSize(0) / 2) >= m_apConfirm2D->GetPosition().x - m_apConfirm2D->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().y + (m_apCursor2D[operation]->GetSize(1) / 2) >= m_apConfirm2D->GetPosition().y - m_apConfirm2D->GetSize(1) &&
		m_apCursor2D[operation]->GetPosition().y - (m_apCursor2D[operation]->GetSize(1) / 2) <= m_apConfirm2D->GetPosition().y + m_apConfirm2D->GetSize(1))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// �m��|���̉��o
//=============================================================================
bool CCharaSelect::ProductionConf(void)
{
	bool bFinish = false;
	D3DXVECTOR3 pos= m_apConfirm2D->GetPosition();
	switch (m_CnfProState)
	{
	case CONFPRODUCTION_NONE:
		break;

	case CONFPRODUCTION_MOVE_START:
		m_apConfirm2D->SetPosition(D3DXVECTOR3(0.0f- DEFAULT_SIZE*5.1f, SCREEN_HEIGHT / 2, 0.0f));
		m_apConfirm2D->SetbDraw(true);
		m_moveConfPro = 100.0f;
		m_CnfProState = CONFPRODUCTION_MOVE;
		break;

	case CONFPRODUCTION_MOVE:
		pos.x += m_moveConfPro;
		if (m_apConfirm2D->GetPosition().x >= SCREEN_WIDTH/2 - 50.0f)
		{
			m_CnfProState = CONFPRODUCTION_MOVE_END;
			m_moveConfPro = 0.0f;
		}
		else
		{
			m_apConfirm2D->SetPosition(pos);
		}
		break;

	case CONFPRODUCTION_MOVE_END:
		m_apConfirm2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		if (m_fFlashAlpha[0] <= 0.0f&&m_fFlashAlpha[1] <= 0.0f&&m_fFlashAlpha[2] <= 0.0f&&m_fFlashAlpha[3] <= 0.0f)
		{
			m_CnfProState = CONFPRODUCTION_NONE;
			bFinish = true;
		}
		break;
	}
	return bFinish;
}
//=============================================================================
// �m��|���̓_�ŏ���
//=============================================================================
void CCharaSelect::FlashConf(void)
{
	m_CntFlash++;
	if (m_CntFlash >= 3)
	{
		m_apConfirm2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
		m_CntFlash = 0;
	}
	else
	{
		m_apConfirm2D->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	}
}
//=============================================================================
// �L�����I���J�[�h�̉��o����
//=============================================================================
void CCharaSelect::ProductionCard(void)
{
	D3DXVECTOR3 pos = DEFAULT_POS;
	bool bFinish[MAX_CHARASELECT] = { false };
	switch (m_CharaCardProduction)
	{
	case CHARACARDPRO_NONE:			//�������Ȃ�
		break;

	case CHARACARDPRO_START:		//�J�n
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(-1.0f, m_CharaCardPro_FinishPos[nCnt].y, DEFAULT_POS.z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
		}
		m_CharaCardProduction = CHARACARDPRO_MOVE;
		break;

	case CHARACARDPRO_MOVE:			//�ړ�
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			pos = m_apSelect2D[nCnt]->GetPosition();
			if (pos.x >= m_CharaCardPro_FinishPos[nCnt].x)
			{
				m_apSelect2D[nCnt]->SetPosition(m_CharaCardPro_FinishPos[nCnt]);
			}
			else
			{
				pos.x += 10.0f + nCnt;
				m_apSelect2D[nCnt]->SetPosition(pos);
			}
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
		}
		if (m_apSelect2D[4]->GetPosition().x == m_CharaCardPro_FinishPos[4].x)
		{
			m_CharaCardProduction = CHARACARDPRO_TURNOVER_B;
		}
		break;

	case CHARACARDPRO_TURNOVER_B:	//���Ԃ�

		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_fCardWidth[nCnt][0] -= 10.0f;
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCardWidth[nCnt][0], m_fCharaCardPro_FinishWH[1]);
			if (m_fCardWidth[nCnt][0] <= 0.0f)
			{
				m_apSelect2D[nCnt]->BindTexture("CHARACTORSEL_CHARA");
				m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt),0.0f),
					D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt),0.5f));
				m_CharaCardProduction = CHARACARDPRO_FACEUP;
			}
		}
		break;

	case CHARACARDPRO_FACEUP:		//�\�ʂɂȂ�
		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			m_fCardWidth[nCnt][0] += 10.0f;
			m_apSelect2D[nCnt]->SetWidthHeight(m_fCardWidth[nCnt][0], m_fCharaCardPro_FinishWH[1]);
			if (m_fCardWidth[nCnt][0] >= m_fCharaCardPro_FinishWH[0])
			{
				m_apSelect2D[nCnt]->SetWidthHeight(m_fCharaCardPro_FinishWH[0], m_fCharaCardPro_FinishWH[1]);
				bFinish[nCnt] = true;
			}
		}
		if (bFinish[0] == true&& bFinish[1] == true&& bFinish[2] == true&& bFinish[3] == true&& bFinish[4] == true)
		{
			m_CharaCardProduction = CHARACARDPRO_FINISH;
		}
		break;

	case CHARACARDPRO_FINISH:		//�I��
		m_bCharaCard = true;
		m_CharaCardProduction = CHARACARDPRO_NONE;
		break;
	}
}
//=============================================================================
// ���[�h�߂�|���S���Ƃ̂����蔻��
//=============================================================================
bool CCharaSelect::collisionBackMode(int operation)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apCursor2D[operation]->GetPosition().x - (m_apCursor2D[operation]->GetSize(0) / 2) <= m_apScene2D[3]->GetPosition().x + m_apScene2D[3]->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().x + (m_apCursor2D[operation]->GetSize(0) / 2) >= m_apScene2D[3]->GetPosition().x - m_apScene2D[3]->GetSize(0) &&
		m_apCursor2D[operation]->GetPosition().y + (m_apCursor2D[operation]->GetSize(1) / 2) >= m_apScene2D[3]->GetPosition().y - m_apScene2D[3]->GetSize(1) &&
		m_apCursor2D[operation]->GetPosition().y - (m_apCursor2D[operation]->GetSize(1) / 2) <= m_apScene2D[3]->GetPosition().y + m_apScene2D[3]->GetSize(1))
	{
		bColl = true;
	}

	return bColl;
}
//=============================================================================
// �߂钷�������Q�[�W�̏���
//=============================================================================
void CCharaSelect::PressGauge(CFade *pFade, CManager *pManager, int operation)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	if (m_apGauge2D[operation]->GetbDraw() == true)
	{
		if (CCommand::GetCommand("RELEASE_L", operation) == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT01);
			m_nCntGauge[operation]++;
			if (m_nCntGauge[operation] >= 90)
			{//3�b�o������
				pFade->SetFade(pManager->MODE_SELECT, pFade->FADE_OUT);
			}
		}
		else if (CCommand::GetCommand("RELEASE_L", operation) == false)
		{
			m_nCntGauge[operation] --;
			if (m_nCntGauge[operation] <= 0)
			{
				m_nCntGauge[operation] = 0;
			}
		}
		m_fGaugeSizeX[operation] = (float)m_nCntGauge[operation] / m_fMaxGaugeX[operation];
		m_apGauge2D[operation]->SetScene2DLeftCenter(D3DXVECTOR3(m_apGauge2D[operation]->GetPosition().x-45.0f, m_apGauge2D[operation]->GetPosition().y,m_apGauge2D[operation]->GetPosition().z),
			m_fMaxGaugeX[operation] *m_fGaugeSizeX[operation], m_apGauge2D[operation]->GetSize(1));
	}

	switch (operation)
	{
	case 0:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	case 1:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		break;
	case 2:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		break;
	case 3:
		m_apGauge2D[operation]->SetCol(D3DXCOLOR(0.9f, 0.9f, 0.0f, 1.0f));
		break;

	}

}
//=============================================================================
// �ړ�����
//=============================================================================
void CCharaSelect::Move(CFade *pFade, CManager *pManager, int nControllNum)
{
	D3DXVECTOR3 pos[MAX_CHARASELECT];
	CSound *pSound = CManager::GetSound();		//	���̎擾

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{//�J�[�\���̈ʒu���擾
		if (m_apCursor2D[nCnt] != NULL)
		{
			pos[nCnt] = m_apCursor2D[nCnt]->GetPosition();
		}
	}

	//�t�F�[�h�����I����/�J�n�O�̂ݓ�������
	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		/* �I�������o�֐� */
		if (m_bConf == false)
		{
			SelectProduction(nControllNum, m_SelectState[nControllNum], m_SelectStateold[nControllNum], m_CharaType[nControllNum]);
		}

		if (m_bConf == true)
		{//�I���m�肪�\�ɂȂ�����
			DecisionCharactor(pFade, pManager, nControllNum);
		}

		/* �J�[�\���ړ�����  */
		if (CCommand::GetCommand("RIGHT_R", nControllNum) == true)
		{//������
			if (CCommand::GetCommand("UP_R", nControllNum) == true)
			{//�㉟��
				m_move[nControllNum].x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
			{//������
				m_move[nControllNum].x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move[nControllNum].x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("LEFT_R", nControllNum) == true)
		{//������
			if (CCommand::GetCommand("UP_R", nControllNum) == true)
			{//�㉟��
				m_move[nControllNum].x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
			{//������
				m_move[nControllNum].x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move[nControllNum].x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move[nControllNum].y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (CCommand::GetCommand("UP_R", nControllNum) == true)
		{//�㉟��
			m_move[nControllNum].x += sinf(D3DX_PI)*CURSOR_MOVE;
			m_move[nControllNum].y += cosf(D3DX_PI)*CURSOR_MOVE;
		}
		else if (CCommand::GetCommand("DOWN_R", nControllNum) == true)
		{//������
			m_move[nControllNum].x -= sinf(D3DX_PI)*CURSOR_MOVE;
			m_move[nControllNum].y -= cosf(D3DX_PI)*CURSOR_MOVE;
		}

		/* �ړ��͈͐��� */
		pos[nControllNum] = MoveRestriction(pos[nControllNum]);

		/* ���� */
		m_move[nControllNum].x += (0.0f - m_move[nControllNum].x) * 0.3f;
		m_move[nControllNum].y += (0.0f - m_move[nControllNum].y) * 0.3f;

		/* �ړ� */
		pos[nControllNum] += m_move[nControllNum];

		/* �ړ��𔽉f */
		m_apCursor2D[nControllNum]->SetPosition(pos[nControllNum]);

		/* ���I�����̂݃J�[�\���ɒǏ] */
		if (m_bPCSelMove[nControllNum] == false)
		{
			m_apBadge2D[nControllNum]->SetPosition(D3DXVECTOR3(m_apCursor2D[nControllNum]->GetPosition().x,
				m_apCursor2D[nControllNum]->GetPosition().y - 50.0f,
				m_apCursor2D[nControllNum]->GetPosition().z));
		}
		m_apGauge2D[nControllNum]->SetPosition(D3DXVECTOR3(m_apCursor2D[nControllNum]->GetPosition().x,
			m_apCursor2D[nControllNum]->GetPosition().y + 50.0f,
			m_apCursor2D[nControllNum]->GetPosition().z));

		/* �I�񂾃L�����N�^�[��ۑ� */
		if (collision(nControllNum, CPlayer::TYPE_BARANCE) == true)
		{//�o�����X
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.2f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//�G���^�[����
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
					m_CharaType[nControllNum] = CPlayer::TYPE_BARANCE;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_POWER) == true)
		{//�p���[
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.2f, 0.5f), D3DXVECTOR2(0.4f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);
			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//�G���^�[����
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
					m_CharaType[nControllNum] = CPlayer::TYPE_POWER;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_SPEED) == true)
		{//�X�s�[�h
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.4f, 0.5f), D3DXVECTOR2(0.6f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);

			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//�G���^�[����
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
					m_CharaType[nControllNum] = CPlayer::TYPE_SPEED;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_REACH) == true)
		{//���[�`
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.6f, 0.5f), D3DXVECTOR2(0.8f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);

			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//�G���^�[����
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
					m_CharaType[nControllNum] = CPlayer::TYPE_REACH;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else if (collision(nControllNum, CPlayer::TYPE_RANDOM) == true)
		{//�����_��
			m_apScene2D[nControllNum + 12]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			m_apScene2D[nControllNum + 12]->SetbDraw(true);

			if (CCommand::GetCommand("DECISION", nControllNum) == true)
			{//�G���^�[����
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT03);

				if (m_SelectState[nControllNum] == SELECTSTATE_NOSELECT)
				{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
					m_CharaType[nControllNum] = CPlayer::TYPE_RANDOM;
					m_SelectState[nControllNum] = SELECTSTATE_FLASH;
					m_bPCSelMove[nControllNum] = true;
				}
			}
		}
		else
		{//�ǂ̑I�����Ƃ��������Ă��Ȃ��ꍇ
			if (m_apScene2D[nControllNum + 12]->GetbDraw() == true) { m_apScene2D[nControllNum + 12]->SetbDraw(false); }
		}
		/* �I�������� */
		if (CCommand::GetCommand("DELETE", nControllNum) == true)
		{
			if (collision(nControllNum, m_CharaType[nControllNum]) == true)
			{
				m_CharaType[nControllNum] = CPlayer::TYPE_MAX;
				m_SelectState[nControllNum] = SELECTSTATE_NOSELECT;
				m_bPCSelMove[nControllNum] = false;
			}
		}

		/* ���[�h�Z���N�g�ɖ߂�|���S���Ƃ̔��� */
		m_bBackMode[nControllNum] = collisionBackMode(nControllNum);

		if (m_bBackMode[nControllNum] == true)
		{
			if (m_apBadge2D[nControllNum]->GetbDraw() == true) { m_apBadge2D[nControllNum]->SetbDraw(false); }
			if (m_apGauge2D[nControllNum]->GetbDraw() == false) { m_apGauge2D[nControllNum]->SetbDraw(true); }
			PressGauge(pFade, pManager, nControllNum);
		}
		else
		{
			if (m_apBadge2D[nControllNum]->GetbDraw() == false) { m_apBadge2D[nControllNum]->SetbDraw(true); }
			if (m_apGauge2D[nControllNum]->GetbDraw() == true) { m_apGauge2D[nControllNum]->SetbDraw(false); }
		}
		if (m_bBackMode[0] == true || m_bBackMode[1] == true || m_bBackMode[2] == true || m_bBackMode[3] == true)

		{
			m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			return;
		}
		else if (m_bBackMode[0] == false || m_bBackMode[1] == false || m_bBackMode[2] == false || m_bBackMode[3] == false)
		{
			m_apScene2D[3]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
		}
	}

}
//=============================================================================
// �m�菈��
//=============================================================================
void CCharaSelect::DecisionCharactor(CFade *pFade, CManager *pManager, int operation)
{
	CSound *pSound = CManager::GetSound();		//	���̎擾
	if (collisionConf(operation) == true)
	{//�|���S���͈͓̔�
		if (CCommand::GetCommand("DECISION", operation) == true)
		{
			m_bCnfFlash = true;
			pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECT04);

			for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
			{//�����_����I�������l������
				m_CharaTypeFinal[nCnt] = m_CharaType[nCnt];
				if (m_CharaTypeFinal[nCnt] == CPlayer::TYPE_RANDOM)
				{//�����_���������ꍇ
					m_CharaTypeFinal[nCnt] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
				}
			}
			for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
			{//�v���C���[�l�����L�����̎�ނ�n��
				CGame::SetCharaSelect(nCnt, m_CharaTypeFinal[nCnt]);
			}

			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
			}
		}
	}
}