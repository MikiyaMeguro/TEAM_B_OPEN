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
#define DEFAULT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))				//�������ʒu
#define STAGESELCHOICE_POS	(D3DXVECTOR3(300.0f,300.0f,0.0f))	//�I�����|���S���̈ʒu
#define STAGESELCHOICE_INTERVAL (350.0f)						//�I�����|���S�����m�̊Ԋu

//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CScene2D *CStageSelect::m_apScene2D[MAX_STAGESELECT_TEX] = {};
CScene2D *CStageSelect::m_apSelect2D[MAX_STAGESELECT] = {};
int CStageSelect::m_nSelect = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CStageSelect::CStageSelect()
{
	m_nCntScrool = 0;
	m_nSelect = 0;
	m_state = SELECTSTATE_SELECT_MACHINE;
	for (int nCnt = 0; nCnt < MAX_STAGE; nCnt++)
	{
		m_SelectPos[nCnt] = DEFAULT_POS;
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
		m_nSelect= (m_nSelect + 1) % MAX_STAGESELECT;
	}
	else if (CCommand::GetCommand("LEFT"))
	{//��
		//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
		m_nSelect = (m_nSelect + 2) % MAX_STAGESELECT;
	}

	//�I��ԍ�����ԕϐ��ɔ��f���A��Ԃɂ��킹�ď������s��
	m_state = (SELECTSTATE)m_nSelect;
	SelectState(m_state);

	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(STAGESELECTTYPE_BAND_R, 0.005f);
	ScrollMenu(STAGESELECTTYPE_BAND_L, -0.005f);

#ifdef _DEBUG
	CDebugProc::Print("c", "�X�e�[�W�Z���N�g");
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
	for (int nCnt = 0; nCnt < MAX_STAGESELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(STAGESELCHOICE_POS.x + (STAGESELCHOICE_INTERVAL*nCnt),
			STAGESELCHOICE_POS.y,
			STAGESELCHOICE_POS.z), "STAGESEL_ICON");
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f+(1.0f/ MAX_STAGESELECT)*nCnt, 0.0f), D3DXVECTOR2((1.0f / MAX_STAGESELECT) + (1.0f / MAX_STAGESELECT)*nCnt, 1.0f));
		/* �T�C�Y�ݒ� */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);

		/* �I�����̏����ʒu���L������ */
		m_SelectPos[nCnt] = m_apSelect2D[nCnt]->GetPosition();
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
void CStageSelect::SelectState(CStageSelect::SELECTSTATE state)
{
	switch (state)
	{
	case SELECTSTATE_SELECT_MACHINE:	//�@�B
		m_apSelect2D[0]->SetPosition(m_SelectPos[1]);
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
		m_apSelect2D[1]->SetPosition(m_SelectPos[2]);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[2]->SetPosition(m_SelectPos[0]);
		m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		break;

	case SELECTSTATE_SELECT_WEATHER:	//�V��
		m_apSelect2D[0]->SetPosition(m_SelectPos[0]);
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[1]->SetPosition(m_SelectPos[1]);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
		m_apSelect2D[2]->SetPosition(m_SelectPos[2]);
		m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		break;

	case SELECTSTATE_SELECT_TERRAIN:	//�n�`
		m_apSelect2D[0]->SetPosition(m_SelectPos[2]);
		m_apSelect2D[0]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[1]->SetPosition(m_SelectPos[0]);
		m_apSelect2D[1]->SetWidthHeight(DEFAULT_SIZE*1.0f, DEFAULT_SIZE*1.3f);
		m_apSelect2D[2]->SetPosition(m_SelectPos[1]);
		m_apSelect2D[2]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.8f);
		break;
	}
}