//=============================================================================
//
// �X�e�[�W�Z���N�g���� [StageSelect.cpp]
// Author : �ڍ� ������/��� ��
//
//=============================================================================
#include "StageSelect.h"
#include "manager.h"
#include "light.h"
#include "camera.h"
#include "scene3D.h"
#include "game.h"
#include "debugProc.h"
#include "scene.h"
#include "fade.h"
#include "input.h"
#include "InputKeyboard.h"
#include "SetObject.h"
#include <time.h>

//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)
#define SIZE_Y (SCREEN_HEIGHT/2)
#define DEFAULT_SIZE (150.0f)									//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS (D3DXVECTOR3(SIZE_X,SIZE_Y,0.0f))			//�������ʒu
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))				//��������]
#define DEFAULT_COL (D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))			//�������F
#define STAGESELCHOICE_POS	(D3DXVECTOR3(300.0f,300.0f,0.0f))	//�I�����|���S���̈ʒu
#define STAGESELCHOICE_INTERVAL (350.0f)						//�I�����|���S�����m�̊Ԋu
#define STAGESEL_DIFF (0.3f)									//�ړ��̕ω���
//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CScene2D *CStageSelect::m_apScene2D[MAX_STAGESELECT_TEX] = {};
CScene2D *CStageSelect::m_apSelect2D[MAX_STAGESELECT] = {};
int	CStageSelect::m_nSelect = 0;
//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect()
{
	m_nCntScrool = 0;
	m_type = SELECTTYPE_SELECT_MACHINE;
	m_MoveIconState = SELECTICON_STATE_NONE;
	m_bRep = false;

	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		m_SelectPos[nCnt] = DEFAULT_POS;
		m_IconCol[nCnt] = DEFAULT_COL;
		m_fWidth[nCnt] = 0.0f;
		m_fHeight[nCnt] = 0.0f;
	}
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CStageSelect::~CStageSelect()
{

}

//=============================================================================
// �X�e�[�W�Z���N�g�̏���������
//=============================================================================
void CStageSelect::Init(void)
{
	/*2D�|���S���̏����ݒ�*/
	InitPolygon();
}

//=============================================================================
// �X�e�[�W�Z���N�g�̏I������
//=============================================================================
void CStageSelect::Uninit(void)
{
	//�S�Ă̏I������
	CScene::ReleseAll();
}

//=============================================================================
// �X�e�[�W�Z���N�g�̍X�V����
//=============================================================================
void CStageSelect::Update(void)
{
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�C�ӂ̃L�[ENTER
	if (CCommand::GetCommand("DECISION"))
	{
		pFade->SetFade(pManager->MODE_GAME, pFade->FADE_OUT);
	}
	/* �I������ */
	if (CCommand::GetCommand("RIGHT"))
	{//�E
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 1) % MAX_STAGESELECT;
		m_MoveIconState = SELECTICON_STATE_MOVE_R;
	}
	else if (CCommand::GetCommand("LEFT"))
	{//��
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + (MAX_STAGESELECT - 1)) % MAX_STAGESELECT;
		m_MoveIconState = SELECTICON_STATE_MOVE_L;
	}

	//�I��ԍ�����ԕϐ��ɔ��f���A��Ԃɂ��킹�ď������s��
	ProductionIcon(m_MoveIconState, m_type);
	if (m_MoveIconState == SELECTICON_STATE_NONE)
	{//�ړ�������������
		m_type = (SELECTTYPE)m_nSelect;
		Selecttype(m_type);
	}

	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(STAGESELECTTYPE_BAND_R, 0.005f);
	ScrollMenu(STAGESELECTTYPE_BAND_L, -0.005f);

#ifdef _DEBUG
	CDebugProc::Print("c", "�X�e�[�W�Z���N�g");
	CDebugProc::Print("cn", "m_MoveIconState:", m_MoveIconState);
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);

#endif
}

//=============================================================================
// �X�e�[�W�Z���N�g�̕`�揈��
//=============================================================================
void CStageSelect::Draw(void)
{

}
//=============================================================================
// �|���S���̏����ݒ�
//=============================================================================
void CStageSelect::InitPolygon(void)
{
	D3DXVECTOR3 Replacement = DEFAULT_POS;

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(STAGESELCHOICE_POS.x + (STAGESELCHOICE_INTERVAL*nCnt),
			STAGESELCHOICE_POS.y,
			STAGESELCHOICE_POS.z), "STAGESEL_ICON");
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f+(1.0f/ MAX_STAGESELECT)*nCnt, 0.0f), D3DXVECTOR2((1.0f / MAX_STAGESELECT) + (1.0f / MAX_STAGESELECT)*nCnt, 1.0f));
		
		/* �I�����̏����ʒu���L������ */
		m_SelectPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();

	}
	m_IconCol[0] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_IconCol[1] = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);
	m_IconCol[2] = D3DXCOLOR(0.8f, 0.8f, 0.8f, 0.5f);

	/* �����ʒu���猩�Đ^�񒆂�0�ɂȂ�悤�ɐݒ� */
	Replacement = m_SelectPos[1];
	m_SelectPos[1] = m_SelectPos[2];
	m_SelectPos[2] = m_SelectPos[0];
	m_SelectPos[0] = Replacement;

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{/* �ʒu���Đݒ� */
		m_apSelect2D[nCnt]->SetPosition(m_SelectPos[nCnt]);
		m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
	}

	/* �T�C�Y�ݒ� */
	m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
	m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
	m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);

	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{/* �T�C�Y���擾 */
		m_fWidth[nCnt] = m_apSelect2D[nCnt]->GetSize(0);
		m_fHeight[nCnt] = m_apSelect2D[nCnt]->GetSize(1);
	}

	//�w�i
	m_apScene2D[STAGESELECTTYPE_BG] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAYERNUMSEL_BG", 1);
	m_apScene2D[STAGESELECTTYPE_BG]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);
	m_apScene2D[STAGESELECTTYPE_BG]->SetbDraw(false);

	//���[�h���сi���j
	m_apScene2D[STAGESELECTTYPE_BAND_L] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "STAGESEL_BAND", 4);
	m_apScene2D[STAGESELECTTYPE_BAND_L]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//���[�h���сi�E�j
	m_apScene2D[STAGESELECTTYPE_BAND_R] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "STAGESEL_BAND", 4);
	m_apScene2D[STAGESELECTTYPE_BAND_R]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

}
//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CStageSelect::ScrollMenu(STAGESELECTTYPE type, float fScroolSpeed)
{
	m_nCntScrool++;
	if (m_apScene2D[type] != NULL)
	{
		m_apScene2D[type]->SetTex(D3DXVECTOR2(0.0f, 0.0f + (m_nCntScrool*fScroolSpeed)),
			D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
	}
}
//=============================================================================
// �I����Ԃ̊Ǘ�
//=============================================================================
void CStageSelect::Selecttype(CStageSelect::SELECTTYPE TYPE)
{
	switch (TYPE)
	{
	case SELECTTYPE_SELECT_MACHINE:	//�@�B		
		break;

	case SELECTTYPE_SELECT_WEATHER:	//�V��
		break;

	case SELECTTYPE_SELECT_TERRAIN:	//�n�`
		break;
	}
}
//=============================================================================
// �I�����̈ړ����o
//=============================================================================
void CStageSelect::ProductionIcon(SELECTICONSTATE &state, SELECTTYPE type)
{
	float fDiffpos[MAX_STAGE] = { 0.0f ,0.0f ,0.0f };											//�ʒu��
	D3DXVECTOR2 fDiffScal[MAX_STAGE] = { D3DXVECTOR2(0.0f, 0.0f) ,D3DXVECTOR2(0.0f, 0.0f) };	//�g�k��
	float fmove[MAX_STAGE] = { 0.0f ,0.0f ,0.0f };												//�ړ���
	D3DXVECTOR2 fScal[MAX_STAGE] = { D3DXVECTOR2(0.0f, 0.0f) ,D3DXVECTOR2(0.0f, 0.0f) };		//�g�k��

	switch (state)
	{
	case SELECTICON_STATE_NONE:
		break;

	case SELECTICON_STATE_MOVE_R:
		if (m_bRep == false)
		{
			Replacement(state);
			m_bRep = true;
		}
		for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
		{
			fDiffpos[nCnt] = m_SelectPos[nCnt].x - m_apSelect2D[nCnt]->GetPosition().x;
			fDiffScal[nCnt] = D3DXVECTOR2(m_fWidth[nCnt] - m_apSelect2D[nCnt]->GetSize(0), m_fHeight[nCnt] - m_apSelect2D[nCnt]->GetSize(1));
			if (fDiffpos[nCnt] <= 0.0f)
			{
				fDiffpos[nCnt] *= -1.0f;
			}
			if (fScal[nCnt].x <= 0.0f)
			{
				fScal[nCnt].x *= -1.0f;
			}
			if (fScal[nCnt].y <= 0.0f)
			{
				fScal[nCnt].y *= -1.0f;
			}
			fmove[nCnt] = fDiffpos[nCnt] - (fDiffpos[nCnt] * STAGESEL_DIFF);
			fScal[nCnt] = D3DXVECTOR2(fDiffScal[nCnt].x - (fDiffScal[nCnt].x*STAGESEL_DIFF), fDiffScal[nCnt].y - (fDiffScal[nCnt].y*STAGESEL_DIFF));

			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(m_SelectPos[nCnt].x + fmove[nCnt], m_SelectPos[nCnt].y, m_SelectPos[nCnt].z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fWidth[nCnt] - fScal[nCnt].x, m_fHeight[nCnt] - fScal[nCnt].y);
			m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
		}

		if (fDiffpos[0] <= 1.0f&&fDiffpos[1] <= 1.0f&& fDiffpos[2] <= 1.0f)
		{//�����Ȃ��Ȃ�����ړ�����
			state = SELECTICON_STATE_STOP;
		}
		break;

	case SELECTICON_STATE_MOVE_L:
		if (m_bRep == false)
		{
			Replacement(state);
			m_bRep = true;
		}

		if (m_bRep == false)
		{
			Replacement(state);
			m_bRep = true;
		}
		for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
		{
			fDiffpos[nCnt] = m_SelectPos[nCnt].x - m_apSelect2D[nCnt]->GetPosition().x;
			fDiffScal[nCnt] = D3DXVECTOR2(m_fWidth[nCnt] - m_apSelect2D[nCnt]->GetSize(0), m_fHeight[nCnt] - m_apSelect2D[nCnt]->GetSize(1));
			if (fDiffpos[nCnt] <= 0.0f)
			{
				fDiffpos[nCnt] *= -1.0f;
			}
			if (fScal[nCnt].x <= 0.0f)
			{
				fScal[nCnt].x *= -1.0f;
			}
			if (fScal[nCnt].y <= 0.0f)
			{
				fScal[nCnt].y *= -1.0f;
			}
			fmove[nCnt] = fDiffpos[nCnt] - (fDiffpos[nCnt] * STAGESEL_DIFF);
			fScal[nCnt] = D3DXVECTOR2(fDiffScal[nCnt].x - (fDiffScal[nCnt].x*STAGESEL_DIFF), fDiffScal[nCnt].y - (fDiffScal[nCnt].y*STAGESEL_DIFF));

			m_apSelect2D[nCnt]->SetPosition(D3DXVECTOR3(m_SelectPos[nCnt].x - fmove[nCnt], m_SelectPos[nCnt].y, m_SelectPos[nCnt].z));
			m_apSelect2D[nCnt]->SetWidthHeight(m_fWidth[nCnt] - fScal[nCnt].x, m_fHeight[nCnt] - fScal[nCnt].y);
			m_apSelect2D[nCnt]->SetCol(m_IconCol[nCnt]);
		}

		if (fDiffpos[0] <= 1.0f&&fDiffpos[1] <= 1.0f&& fDiffpos[2] <= 1.0f)
		{//�����Ȃ��Ȃ�����ړ�����
			state = SELECTICON_STATE_STOP;
		}
		break;


	case SELECTICON_STATE_STOP:
		m_bRep = false;
		state = SELECTICON_STATE_NONE;
		break;
	}

}
//=============================================================================
// ���W����ւ�
//=============================================================================
void CStageSelect::Replacement(SELECTICONSTATE state)
{
	/* ���u���p�ϐ� */
	D3DXVECTOR3 Replacement = DEFAULT_POS;
	float RepW = 0.0f, RepH = 0.0f;
	D3DXCOLOR RepCol = DEFAULT_COL;

	switch (state)
	{
	case SELECTICON_STATE_MOVE_R:
		/* �ʒu */
		Replacement = m_SelectPos[1];
		m_SelectPos[1] = m_SelectPos[0];
		m_SelectPos[0] = m_SelectPos[2];
		m_SelectPos[2] = Replacement;
		/* ���� */
		RepW = m_fWidth[1];
		m_fWidth[1] = m_fWidth[0];
		m_fWidth[0] = m_fWidth[2];
		m_fWidth[2] = RepW;
		/* �c�� */
		RepH = m_fHeight[1];
		m_fHeight[1] = m_fHeight[0];
		m_fHeight[0] = m_fHeight[2];
		m_fHeight[2] = RepH;
		/* �F */
		RepCol = m_IconCol[1];
		m_IconCol[1] = m_IconCol[0];
		m_IconCol[0] = m_IconCol[2];
		m_IconCol[2] = RepCol;
		break;

	case SELECTICON_STATE_MOVE_L:
		/* �ʒu */
		Replacement = m_SelectPos[1];
		m_SelectPos[1] = m_SelectPos[2];
		m_SelectPos[2] = m_SelectPos[0];
		m_SelectPos[0] = Replacement;
		/* ���� */
		RepW = m_fWidth[1];
		m_fWidth[1] = m_fWidth[2];
		m_fWidth[2] = m_fWidth[0];
		m_fWidth[0] = RepW;
		/* �c�� */
		RepH = m_fHeight[1];
		m_fHeight[1] = m_fHeight[2];
		m_fHeight[2] = m_fHeight[0];
		m_fHeight[0] = RepH;
		/* �F */
		RepCol = m_IconCol[1];
		m_IconCol[1] = m_IconCol[2];
		m_IconCol[2] = m_IconCol[0];
		m_IconCol[0] = RepCol;
		break;
	}
}