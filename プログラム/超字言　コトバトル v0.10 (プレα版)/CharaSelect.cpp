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
#define CHARASELCHOICE_POS	(D3DXVECTOR3(211.0f,180.0f,0.0f))	//�I�����|���S���̈ʒu
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

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_PlayerNum = NULL;
	m_OperationNum = 0;
	/* ���o�n�ϐ������� */
	m_nCntScrool = 0;
	m_CntFlash = 0;
	m_CntFadeF = 0;
	m_fFlashAlpha = 1.0f;
	m_moveConfPro = 0.0f;
	m_CnfProState = CONFPRODUCTION_NONE;
	m_bConfProFinish = false;
	m_bConf = false;
	m_bConfProStart = false;
	m_bCnfFlash = false;

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		m_move[nCnt] = DEFAULT_POS;
		m_SelectState[nCnt] = SELECTSTATE_NOSELECT;
		m_SelectStateold[nCnt] = SELECTSTATE_NOSELECT;
		m_bPCSelMove[nCnt] = false;
		m_CharaType[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeOld[nCnt] = CPlayer::TYPE_MAX;
		m_CharaTypeFinal[nCnt] = CPlayer::TYPE_MAX;
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
	D3DXVECTOR3 pos[MAX_CHARASELECT];
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();
	CInputXPad *pInputX[MAX_PLAYER];
	bool bInputPad = false;
	for (int nCntXinput = 0; nCntXinput < MAX_PLAYER; nCntXinput++)
	{
		pInputX[nCntXinput] = CManager::GetXInput(nCntXinput);
	}
	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{//�J�[�\���̈ʒu���擾
		if (m_apCursor2D[nCnt] != NULL)
		{
			pos[nCnt] = m_apCursor2D[nCnt]->GetPosition();
		}
	}
	//���[�h�J��
	for (int nCntXinput = 0; nCntXinput < MAX_PLAYER; nCntXinput++)
	{
		if (pInputX[nCntXinput]->GetConnect() != NULL)
		{
			bInputPad = true;
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
				if (m_bConf == true)
				{//�I���m�肪�\�ɂȂ�����
					if (collisionConf(nCntXinput) == true)
					{//�|���S���͈͓̔�
						if (CCommand::GetCommand("DECISION", nCntXinput) == true)
						{
							m_bCnfFlash = true;
							for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
							{//�����_����I�������l������
								m_CharaTypeFinal[nCnt] = m_CharaType[nCnt];
								if (m_CharaTypeFinal[nCnt] == CPlayer::TYPE_MAX)
								{//�����_���������ꍇ
									m_CharaTypeFinal[nCnt] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
								}
							}
							for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
							{//�v���C���[�l�����L�����̎�ނ�n��
								CGame::SetCharaSelect(nCnt, m_CharaTypeFinal[nCnt]);
							}
							pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);

						}
					}
				}
			}
			else
			{//�S���I�����Ă��Ȃ�
				m_apConfirm2D->SetbDraw(false);
				m_bConfProFinish = false;
				m_bConf = false;
				m_bConfProStart = false;
			}
			//�t�F�[�h�����I����/�J�n�O�̂ݓ�������
			if (pFade->GetFade() == CFade::FADE_NONE)
			{
				/* �J�[�\���ړ�����  */
				if (CCommand::GetCommand("RIGHT_R", nCntXinput) == true)
				{//������
					if (CCommand::GetCommand("UP_R", nCntXinput) == true)
					{//�㉟��
						m_move[nCntXinput].x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
						m_move[nCntXinput].y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
					}
					else if (CCommand::GetCommand("DOWN_R", nCntXinput) == true)
					{//������
						m_move[nCntXinput].x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
						m_move[nCntXinput].y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
					}
					else
					{
						m_move[nCntXinput].x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
						m_move[nCntXinput].y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
					}
				}
				else if (CCommand::GetCommand("LEFT_R", nCntXinput) == true)
				{//������
					if (CCommand::GetCommand("UP_R", nCntXinput) == true)
					{//�㉟��
						m_move[nCntXinput].x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
						m_move[nCntXinput].y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
					}
					else if (CCommand::GetCommand("DOWN_R", nCntXinput) == true)
					{//������
						m_move[nCntXinput].x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
						m_move[nCntXinput].y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
					}
					else
					{
						m_move[nCntXinput].x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
						m_move[nCntXinput].y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
					}
				}
				else if (CCommand::GetCommand("UP_R", nCntXinput) == true)
				{//�㉟��
					m_move[nCntXinput].x += sinf(D3DX_PI)*CURSOR_MOVE;
					m_move[nCntXinput].y += cosf(D3DX_PI)*CURSOR_MOVE;
				}
				else if (CCommand::GetCommand("DOWN_R", nCntXinput) == true)
				{//������
					m_move[nCntXinput].x -= sinf(D3DX_PI)*CURSOR_MOVE;
					m_move[nCntXinput].y -= cosf(D3DX_PI)*CURSOR_MOVE;
				}

				/* �ړ��͈͐��� */
				pos[nCntXinput] = MoveRestriction(pos[nCntXinput]);

				/* ���� */
				m_move[nCntXinput].x += (0.0f - m_move[nCntXinput].x) * 0.3f;
				m_move[nCntXinput].y += (0.0f - m_move[nCntXinput].y) * 0.3f;

				/* �ړ� */
				pos[nCntXinput] += m_move[nCntXinput];

				/* �ړ��𔽉f */
				m_apCursor2D[nCntXinput]->SetPosition(pos[nCntXinput]);

				/* ���I�����̂݃J�[�\���ɒǏ] */
				if (m_bPCSelMove[nCntXinput] == false)
				{
					m_apBadge2D[nCntXinput]->SetPosition(D3DXVECTOR3(m_apCursor2D[nCntXinput]->GetPosition().x,
						m_apCursor2D[nCntXinput]->GetPosition().y - 50.0f,
						m_apCursor2D[nCntXinput]->GetPosition().z));
				}

				/* �I�񂾃L�����N�^�[��ۑ� */
				if (collision(nCntXinput, CPlayer::TYPE_BARANCE) == true)
				{//�o�����X
					m_apScene2D[nCntXinput + 11]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.2f, 1.0f));
					m_apScene2D[nCntXinput + 11]->SetbDraw(true);
					if (CCommand::GetCommand("DECISION", nCntXinput) == true)
					{//�G���^�[����
						if (m_SelectState[nCntXinput] != SELECTSTATE_SELECT)
						{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
							m_CharaType[nCntXinput] = CPlayer::TYPE_BARANCE;
							m_SelectState[nCntXinput] = SELECTSTATE_FLASH;
							m_bPCSelMove[nCntXinput] = true;
						}
					}
				}
				else if (collision(nCntXinput, CPlayer::TYPE_POWER) == true)
				{//�p���[
					m_apScene2D[nCntXinput + 11]->SetTex(D3DXVECTOR2(0.2f, 0.5f), D3DXVECTOR2(0.4f, 1.0f));
					m_apScene2D[nCntXinput + 11]->SetbDraw(true);
					if (CCommand::GetCommand("DECISION", nCntXinput) == true)
					{//�G���^�[����
						if (m_SelectState[nCntXinput] != SELECTSTATE_SELECT)
						{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
							m_CharaType[nCntXinput] = CPlayer::TYPE_POWER;
							m_SelectState[nCntXinput] = SELECTSTATE_FLASH;
							m_bPCSelMove[nCntXinput] = true;
						}
					}
				}
				else if (collision(nCntXinput, CPlayer::TYPE_SPEED) == true)
				{//�X�s�[�h
					m_apScene2D[nCntXinput + 11]->SetTex(D3DXVECTOR2(0.4f, 0.5f), D3DXVECTOR2(0.6f, 1.0f));
					m_apScene2D[nCntXinput + 11]->SetbDraw(true);

					if (CCommand::GetCommand("DECISION", nCntXinput) == true)
					{//�G���^�[����
						if (m_SelectState[nCntXinput] != SELECTSTATE_SELECT)
						{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
							m_CharaType[nCntXinput] = CPlayer::TYPE_SPEED;
							m_SelectState[nCntXinput] = SELECTSTATE_FLASH;
							m_bPCSelMove[nCntXinput] = true;
						}
					}
				}
				else if (collision(nCntXinput, CPlayer::TYPE_REACH) == true)
				{//���[�`
					m_apScene2D[nCntXinput + 11]->SetTex(D3DXVECTOR2(0.6f, 0.5f), D3DXVECTOR2(0.8f, 1.0f));
					m_apScene2D[nCntXinput + 11]->SetbDraw(true);

					if (CCommand::GetCommand("DECISION", nCntXinput) == true)
					{//�G���^�[����
						if (m_SelectState[nCntXinput] != SELECTSTATE_SELECT)
						{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
							m_CharaType[nCntXinput] = CPlayer::TYPE_REACH;
							m_SelectState[nCntXinput] = SELECTSTATE_FLASH;
							m_bPCSelMove[nCntXinput] = true;
						}
					}
				}
				else if (collision(nCntXinput, CPlayer::TYPE_MAX) == true)
				{//�����_��
					m_apScene2D[nCntXinput + 11]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
					m_apScene2D[nCntXinput + 11]->SetbDraw(true);

					if (CCommand::GetCommand("DECISION", nCntXinput) == true)
					{//�G���^�[����
						if (m_SelectState[nCntXinput] != SELECTSTATE_SELECT)
						{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
							m_CharaType[nCntXinput] = CPlayer::TYPE_MAX;
							m_SelectState[nCntXinput] = SELECTSTATE_FLASH;
							m_bPCSelMove[nCntXinput] = true;
						}
					}
				}
				else
				{//�ǂ̑I�����Ƃ��������Ă��Ȃ��ꍇ
					m_apScene2D[nCntXinput + 11]->SetbDraw(false);
				}
				/* �I�������� */
				if (CCommand::GetCommand("DELETE", nCntXinput) == true)
				{
					if (collision(nCntXinput, m_CharaType[nCntXinput]) == true)
					{
						m_CharaType[nCntXinput] = CPlayer::TYPE_MAX;
						m_SelectState[nCntXinput] = SELECTSTATE_NOSELECT;
						m_bPCSelMove[nCntXinput] = false;
					}
				}
			}
			/* �I�������o�֐� */
			SelectProduction(nCntXinput, m_SelectState[nCntXinput], m_SelectStateold[nCntXinput], m_CharaType[nCntXinput]);
		}
	}

	if (bInputPad == false)
	{
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
			if (m_bConf == true)
			{//�I���m�肪�\�ɂȂ�����
				if (collisionConf(m_OperationNum) == true)
				{//�|���S���͈͓̔�
					if (CCommand::GetCommand("DECISION") == true)
					{
						m_bCnfFlash = true;
						for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
						{//�����_����I�������l������
							m_CharaTypeFinal[nCnt] = m_CharaType[nCnt];
							if (m_CharaTypeFinal[nCnt] == CPlayer::TYPE_MAX)
							{//�����_���������ꍇ
								m_CharaTypeFinal[nCnt] = (CPlayer::PLAYER_TYPE)(rand() % CPlayer::TYPE_MAX);
							}
						}
						for (int nCnt = 0; nCnt < *m_PlayerNum; nCnt++)
						{//�v���C���[�l�����L�����̎�ނ�n��
							CGame::SetCharaSelect(nCnt, m_CharaTypeFinal[nCnt]);
						}
						pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);

					}
				}
			}
		}
		else
		{//�S���I�����Ă��Ȃ�
			m_apConfirm2D->SetbDraw(false);
			m_bConfProFinish = false;
			m_bConf = false;
			m_bConfProStart = false;
		}
		//�t�F�[�h�����I����/�J�n�O�̂ݓ�������
		if (pFade->GetFade() == CFade::FADE_NONE)
		{
			/* �J�[�\���ړ�����  */
			if (CCommand::GetCommand("RIGHT_R") == true)
			{//������
				if (CCommand::GetCommand("UP_R") == true)
				{//�㉟��
					m_move[m_OperationNum].x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
					m_move[m_OperationNum].y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				}
				else if (CCommand::GetCommand("DOWN_R") == true)
				{//������
					m_move[m_OperationNum].x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
					m_move[m_OperationNum].y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				}
				else
				{
					m_move[m_OperationNum].x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
					m_move[m_OperationNum].y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				}
			}
			else if (CCommand::GetCommand("LEFT_R") == true)
			{//������
				if (CCommand::GetCommand("UP_R") == true)
				{//�㉟��
					m_move[m_OperationNum].x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
					m_move[m_OperationNum].y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				}
				else if (CCommand::GetCommand("DOWN_R") == true)
				{//������
					m_move[m_OperationNum].x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
					m_move[m_OperationNum].y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				}
				else
				{
					m_move[m_OperationNum].x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
					m_move[m_OperationNum].y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				}
			}
			else if (CCommand::GetCommand("UP_R") == true)
			{//�㉟��
				m_move[m_OperationNum].x += sinf(D3DX_PI)*CURSOR_MOVE;
				m_move[m_OperationNum].y += cosf(D3DX_PI)*CURSOR_MOVE;
			}
			else if (CCommand::GetCommand("DOWN_R") == true)
			{//������
				m_move[m_OperationNum].x -= sinf(D3DX_PI)*CURSOR_MOVE;
				m_move[m_OperationNum].y -= cosf(D3DX_PI)*CURSOR_MOVE;
			}

			/* �ړ��͈͐��� */
			pos[m_OperationNum] = MoveRestriction(pos[m_OperationNum]);

			/* ���� */
			m_move[m_OperationNum].x += (0.0f - m_move[m_OperationNum].x) * 0.3f;
			m_move[m_OperationNum].y += (0.0f - m_move[m_OperationNum].y) * 0.3f;

			/* �ړ� */
			pos[m_OperationNum] += m_move[m_OperationNum];

			/* �ړ��𔽉f */
			m_apCursor2D[m_OperationNum]->SetPosition(pos[m_OperationNum]);

			/* ���I�����̂݃J�[�\���ɒǏ] */
			if (m_bPCSelMove[m_OperationNum] == false)
			{
				m_apBadge2D[m_OperationNum]->SetPosition(D3DXVECTOR3(m_apCursor2D[m_OperationNum]->GetPosition().x,
					m_apCursor2D[m_OperationNum]->GetPosition().y - 50.0f,
					m_apCursor2D[m_OperationNum]->GetPosition().z));
			}

			/* �I�񂾃L�����N�^�[��ۑ� */
			if (collision(m_OperationNum, CPlayer::TYPE_BARANCE) == true)
			{//�o�����X
				m_apScene2D[m_OperationNum + 11]->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.2f, 1.0f));
				m_apScene2D[m_OperationNum + 11]->SetbDraw(true);
				if (CCommand::GetCommand("DECISION") == true)
				{//�G���^�[����
					if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
					{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
						m_CharaType[m_OperationNum] = CPlayer::TYPE_BARANCE;
						m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
						m_bPCSelMove[m_OperationNum] = true;
					}
				}
			}
			else if (collision(m_OperationNum, CPlayer::TYPE_POWER) == true)
			{//�p���[
				m_apScene2D[m_OperationNum + 11]->SetTex(D3DXVECTOR2(0.2f, 0.5f), D3DXVECTOR2(0.4f, 1.0f));
				m_apScene2D[m_OperationNum + 11]->SetbDraw(true);
				if (CCommand::GetCommand("DECISION") == true)
				{//�G���^�[����
					if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
					{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
						m_CharaType[m_OperationNum] = CPlayer::TYPE_POWER;
						m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
						m_bPCSelMove[m_OperationNum] = true;
					}
				}
			}
			else if (collision(m_OperationNum, CPlayer::TYPE_SPEED) == true)
			{//�X�s�[�h
				m_apScene2D[m_OperationNum + 11]->SetTex(D3DXVECTOR2(0.4f, 0.5f), D3DXVECTOR2(0.6f, 1.0f));
				m_apScene2D[m_OperationNum + 11]->SetbDraw(true);

				if (CCommand::GetCommand("DECISION") == true)
				{//�G���^�[����
					if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
					{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
						m_CharaType[m_OperationNum] = CPlayer::TYPE_SPEED;
						m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
						m_bPCSelMove[m_OperationNum] = true;
					}
				}
			}
			else if (collision(m_OperationNum, CPlayer::TYPE_REACH) == true)
			{//���[�`
				m_apScene2D[m_OperationNum + 11]->SetTex(D3DXVECTOR2(0.6f, 0.5f), D3DXVECTOR2(0.8f, 1.0f));
				m_apScene2D[m_OperationNum + 11]->SetbDraw(true);

				if (CCommand::GetCommand("DECISION") == true)
				{//�G���^�[����
					if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
					{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
						m_CharaType[m_OperationNum] = CPlayer::TYPE_REACH;
						m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
						m_bPCSelMove[m_OperationNum] = true;
					}
				}
			}
			else if (collision(m_OperationNum, CPlayer::TYPE_MAX) == true)
			{//�����_��
				m_apScene2D[m_OperationNum + 11]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
				m_apScene2D[m_OperationNum + 11]->SetbDraw(true);

				if (CCommand::GetCommand("DECISION") == true)
				{//�G���^�[����
					if (m_SelectState[m_OperationNum] != SELECTSTATE_SELECT)
					{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
						m_CharaType[m_OperationNum] = CPlayer::TYPE_MAX;
						m_SelectState[m_OperationNum] = SELECTSTATE_FLASH;
						m_bPCSelMove[m_OperationNum] = true;
					}
				}
			}
			else
			{//�ǂ̑I�����Ƃ��������Ă��Ȃ��ꍇ
				m_apScene2D[m_OperationNum + 11]->SetbDraw(false);
			}
			/* �I�������� */
			if (CCommand::GetCommand("DELETE") == true)
			{
				if (collision(m_OperationNum, m_CharaType[m_OperationNum]) == true)
				{
					m_CharaType[m_OperationNum] = CPlayer::TYPE_MAX;
					m_SelectState[m_OperationNum] = SELECTSTATE_NOSELECT;
					m_bPCSelMove[m_OperationNum] = false;
				}
			}
		}
	}
	/* �I�������o�֐� */
	SelectProduction(m_OperationNum, m_SelectState[m_OperationNum], m_SelectStateold[m_OperationNum], m_CharaType[m_OperationNum]);
	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* �m��|���̃t���b�V�����o */
	if (m_bCnfFlash == true) { FlashConf(); }
#ifdef _DEBUG
	CDebugProc::Print("c", "�L�����Z���N�g");
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		m_OperationNum = 0;
	}
	else if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		m_OperationNum = 1;
	}
	else if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		m_OperationNum = 2;
	}
	else if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		m_OperationNum = 3;
	}

#endif
}

//=============================================================================
// �L�����Z���N�g�̕`�揈��
//=============================================================================
void CCharaSelect::Draw(void)
{

}

//=============================================================================
// �|�C���^�̏���������
//=============================================================================
void CCharaSelect::Initpointer(void)
{
	for (int nCnt = 0; nCnt < MAX_CHARASELTEX; nCnt++)
	{
		if (m_apScene2D[nCnt] != NULL)
		{
			m_apScene2D[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		if (m_apSelect2D[nCnt] != NULL)
		{
			m_apSelect2D[nCnt] = NULL;
		}
	}
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
void CCharaSelect::SelectProduction(int nNum,SELECT_STATE &Sel, SELECT_STATE &Selold,CPlayer::PLAYER_TYPE type)
{
	switch (Sel)
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//���o��
		if (Selold != SELECTSTATE_FLASH)
		{//�O��̃��[�h��Flash�ȊO�̏ꍇa�l��������
			m_fFlashAlpha = 1.0f;
		}
		m_apScene2D[nNum +7]->SetbDraw(true);											//�}�X�N�̕`�悷��
		m_apScene2D[nNum + 7]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha));	//�F
		CharaSelTex(nNum,SELECTSTATE_SELECT, type,m_CharaTypeOld[nNum]);

		if (m_fFlashAlpha <= 0.0f)
		{//�����x��������؂���
			m_apScene2D[nNum + 7]->SetbDraw(false);								//�}�X�N��`�悵�Ȃ��󋵂�
			m_apScene2D[nNum + 7]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�}�X�N�̐F����ɖ߂��Ă���
			m_fFlashAlpha = 0.0f;												//a�l���Y��Ȑ����ɕύX
			m_SelectState[type] = SELECTSTATE_SELECT;							//�I�����ꂽ��ԂɕύX
		}
		else
		{
			m_fFlashAlpha -= 0.02f;
			m_apScene2D[nNum + 7]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha));
		}
		break;

	case SELECTSTATE_SELECT:	//�I������Ă���
		break;

	case SELECTSTATE_NOSELECT:	//�I������Ă��Ȃ�
		m_apScene2D[nNum + 7]->SetbDraw(false);		//�}�X�N��`�悳��Ă��Ȃ���Ԃ�
		CharaSelTex(nNum,SELECTSTATE_NOSELECT, type,m_CharaTypeOld[nNum]);
		break;
	}

	//����̑I����Ԃ�O��̑I����ԂƂ��ĕۑ�
	Selold = Sel;
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
		///* �e�N�X�`�����W�ݒ� */
		//m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.0f),
		//	D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 0.5f));
		/* �T�C�Y�ݒ� */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.5f);
	}

	/* ���o */
	// �w�i
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAUERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//���[�h���сi���j
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//���[�h���сi�E�j
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 4);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	for (int nCnt = 0; nCnt < MAX_PLAYER; nCnt++)
	{
		//�v���C���[�E�B���h
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 3] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "PLAYER_UIWINDOW",2);
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 3]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 3]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));//�����ݒ�͑S��COM�A����SWICH�ōĐݒ�

		// �v���C���[�E�B���h�}�X�N
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 7] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), " ");
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 7]->SetWidthHeight(DEFAULT_SIZE*1.2f, DEFAULT_SIZE*1.6f);
		m_apScene2D[nCnt + 7]->SetbDraw(false);

		//�v���C���[�E�B���h�E�ɕ\������L�����N�^�[
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apScene2D[nCnt + 11] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y+20.0f,
			CURSOL_INITPOS.z), "CHARACTORSEL_CHARA",2);
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 11]->SetWidthHeight(DEFAULT_SIZE*1.1f, DEFAULT_SIZE*1.2f);
		m_apScene2D[nCnt + 11]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.5f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 1.0f));
		m_apScene2D[nCnt + 11]->SetbDraw(false);

		//�o�b�W
		m_apBadge2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE", 4);
		m_apBadge2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		//�J�[�\��
		m_apCursor2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CURSOL_INITPOS.x + (CHARASELCHOICE_INTERVAL*nCnt),
			CURSOL_INITPOS.y,
			CURSOL_INITPOS.z), "CHARASEL_BADGE", 4);
		m_apCursor2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);

		/* �v���C���[�l���ɍ��킹�Đݒ� */
		if (nCnt < (int)*m_PlayerNum)
		{
			//�J�[�\���ƃo�b�W
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.5f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + (1.0f / 5)*nCnt, 0.0f), D3DXVECTOR2((1.0f / 5) + (1.0f / 5)*nCnt, 0.5f));
			// �v���C���[�E�B���h�E�̃e�N�X�`�����W
			m_apScene2D[nCnt + 3]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nCnt), D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nCnt));
		}
		else
		{
			//�J�[�\���ƃo�b�W
			m_apBadge2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
			m_apCursor2D[nCnt]->SetTex(D3DXVECTOR2(0.8f, 0.0f), D3DXVECTOR2(1.0f, 0.5f));
			// �v���C���[�E�B���h�E�̃e�N�X�`�����W
			m_apScene2D[nCnt + 3]->SetTex(D3DXVECTOR2(0.0f, 0.8f), D3DXVECTOR2(0.2f, 1.0f));
		}
	}
	
	/* �L�����I���m�� */
	m_apConfirm2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), "PLAYER_CONFIRM");
	m_apConfirm2D->SetWidthHeight(DEFAULT_SIZE*4.5f, DEFAULT_SIZE*0.8f);
	m_apConfirm2D->SetbDraw(false);
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
	if (m_apBadge2D[operation]->GetPosition().x - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().x + (DEFAULT_SIZE*0.8f) &&
		m_apBadge2D[operation]->GetPosition().x + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().x - (DEFAULT_SIZE*0.8f) &&
		m_apBadge2D[operation]->GetPosition().y + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().y - (DEFAULT_SIZE*0.8f) &&
		m_apBadge2D[operation]->GetPosition().y - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().y + (DEFAULT_SIZE*0.8f))
	{
		bColl = true;
	}

	return bColl;
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
	CCommand::RegistCommand("DELETE", CCommand::INPUTTYPE_PAD_X, CCommand::INPUTSTATE_PRESS, CInputXPad::XPAD_X);
}

//=============================================================================
// �e�N�X�`�����W�Ǘ�
//=============================================================================
void CCharaSelect::CharaSelTex(int nNum, SELECT_STATE Sel, CPlayer::PLAYER_TYPE &type, CPlayer::PLAYER_TYPE &typeOld)
{
	switch (Sel)
	{/* �I�΂ꂽ���̃e�N�X�`�����W */
	case SELECTSTATE_SELECT:	//�I�΂�Ă���
		m_apScene2D[nNum + 3]->SetTex(D3DXVECTOR2(0.2f + (1.0f / 5)*(int)type, 0.0f + (1.0f / 5)*nNum),
			D3DXVECTOR2(0.4f + (1.0f / 5)*(int)type, 0.2f + (1.0f / 5)*nNum));
		if (type == CPlayer::TYPE_MAX)
		{//�����_���̏ꍇ
			m_apScene2D[nNum + 3]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (1.0f / 5)*nNum),
				D3DXVECTOR2(0.2f, 0.2f + (1.0f / 5)*nNum));
		}
		break;
	case SELECTSTATE_NOSELECT:
		m_apScene2D[nNum + 3]->SetTex(D3DXVECTOR2(0.0f , 0.0f + (1.0f / 5)*nNum),
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
	if (m_apCursor2D[operation]->GetPosition().x - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apConfirm2D->GetPosition().x + (DEFAULT_SIZE*3.0f) &&
		m_apCursor2D[operation]->GetPosition().x + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apConfirm2D->GetPosition().x - (DEFAULT_SIZE*3.0f) &&
		m_apCursor2D[operation]->GetPosition().y + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apConfirm2D->GetPosition().y - (DEFAULT_SIZE*0.8f) &&
		m_apCursor2D[operation]->GetPosition().y - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apConfirm2D->GetPosition().y + (DEFAULT_SIZE*0.8f))
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
		m_CnfProState = CONFPRODUCTION_NONE;
		m_apConfirm2D->SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		bFinish = true;
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