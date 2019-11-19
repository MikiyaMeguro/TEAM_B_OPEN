//---------------------------------------------------------------------
// �Z���N�g���j���[���� [SelectMenu.cpp]
// Author : Mikiya Meguro/Akane Gokan
//---------------------------------------------------------------------
#include "SelectMenu.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "PlayerNumSelect.h"
#include "fade.h"
#include "renderer.h"
#include "load.h"
#include "texture.h"
#include "debugProc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODESELECT_WIDTH		(1.0f)		//�|���S���̑傫��(��)
#define MODESELECT_HEIGHT		(1.0f)		//�|���S���̑傫��(�c)
#define MENU_WIDTH				(450.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define MENU_HEIGHT				(180.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define MENU_INITPOS			(350.0f)	//���j���[�̏����ʒu
#define MENU_NUM_HEIGHT			(2)
#define MENU_NUM_WIDTH			(2)
#define MENU_INIT_POS			(370.0f)
#define MENU_BG					(150.0f)	//�|���S���̑傫��
#define NOSELECT_MENU_SIZE		(50.0f)		//�I�΂�Ă��Ȃ��Ƃ��̃|���S���̃T�C�Y

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CSelectMenu::m_pTexture[MAX_SELECTMENU] = {};
LPDIRECT3DTEXTURE9 CSelectMenu::m_pTextureBG = NULL;
CSelectMenu::SELECT_MENU CSelectMenu::m_SelectMode = CSelectMenu::SELECT_MENU_NONE;
bool CSelectMenu::m_bModeSelect = false;

//--------------------------------------------
//�Z���N�g���j���[�N���X �R���X�g���N�^
//--------------------------------------------
CSelectMenu::CSelectMenu(int nPriority) : CScene(7)
{
	//�l�̏�����
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bModeSelect = true;

	for (int nCnt = 0; nCnt < MAX_SELETMODE_BG; nCnt++)
	{
		if (m_apPolygonBG[nCnt] != NULL)
		{
			m_apPolygonBG[nCnt] = NULL;
		}
	}

	m_fSpace = 0;
	m_fInitYpos = 0;

	/* ���o�ʕϐ��̏����� */
	m_nCntScrool = 0;
	m_nCntAnim = 0;
	m_nPatturnAnim = 0;
	m_nCntAnim2 = 0;
	m_nPatturnAnim2 = 0;
	m_fChangeMode = 0.3f;
	m_fMoveMode = 0.0f;
}

//--------------------------------------------
//�Z���N�g���j���[�N���X �f�X�g���N�^
//--------------------------------------------
CSelectMenu::~CSelectMenu()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CSelectMenu *CSelectMenu::Create(D3DXVECTOR3 pos, float m_fWidth, float fSpace, MENU_TYPE type)
{
	//�Z���N�g���j���[�̃|�C���^
	CSelectMenu *pMenuSelect;
	pMenuSelect = new CSelectMenu;
	pMenuSelect->m_MenuType = type;
	pMenuSelect->m_InitPos = pos;
	pMenuSelect->m_fWidth = m_fWidth;
	pMenuSelect->m_fHeight = m_fWidth;
	pMenuSelect->m_fSpace = fSpace;
	//�Z���N�g���j���[�̏�����
	pMenuSelect->Init();
	//�Z���N�g���j���[�̏���Ԃ�
	return pMenuSelect;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CSelectMenu::Init()
{
	switch (m_MenuType)
	{
	case MENU_TYPE_TUTORIAL:
		m_nMaxMenu = 3;
		m_fInitYpos = 350.0f;

		InitTutorialPolygon();
		break;

	case MENU_TYPE_RESULT:
		m_fInitYpos = 270.0f;
		m_nMaxMenu = 4;
		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{//���j���[�|���S���̏�����
			m_apPolygon[nCnt] = NULL;
		}

		/* ���j���[�|���S���̐ݒ� */

		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


			if (m_apPolygon[nCnt] == NULL)
			{
				m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU");
				m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 0.5f));
				m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
				m_apPolygon[nCnt]->SetbDraw(true);
			}
		}
		break;
	case MENU_TYPE_PAUSE:
		m_nMaxMenu = 2;
		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{//���j���[�|���S���̏�����
			m_apPolygon[nCnt] = NULL;
		}

		/* ���j���[�|���S���̐ݒ� */
		m_InitPos.y = MENU_INITPOS;

		for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
		{
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


			if (m_apPolygon[nCnt] == NULL)
			{
				m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU");
				m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 1.0f));
				m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
				m_apPolygon[nCnt]->SetbDraw(true);
			}
		}
		break;
	}

	//m_pTextureBG = CLoad::GetTexture(CLoad::TEXTURE_MODESELECT_BG);

	//�l�̏�����
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bModeSelect = true;
	//�I�u�W�F�N�g��ނ̐ݒ�
	CScene::SetObjType(CScene::OBJTYPE_MODESELECT);

	return S_OK;
}

//=============================================================================
// �Z���N�g���j���[�N���X �I������
//=============================================================================
void CSelectMenu::Uninit(void)
{
	//������j��
	Release();
}

//=============================================================================
// �Z���N�g���j���[�N���X �X�V����
//=============================================================================
void CSelectMenu::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�t�F�[�h���擾
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();


	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	//�Z���N�g���j���[��
	if (m_bModeSelect == true && pFade->GetFade() == CFade::FADE_NONE)
	{
		//�I������
		if (CCommand::GetCommand("RIGHT"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect < m_nMaxMenu - 1)
			{
				m_nSelect = (m_nSelect + 1) % m_nMaxMenu;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("LEFT"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect > 0)
			{
				m_nSelect = (m_nSelect + (m_nMaxMenu - 1)) % m_nMaxMenu;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}

		//�G���^�[�L�[
		if (CCommand::GetCommand("DECISION"))
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_CANCEL);
			if (m_nSelect == 0)
			{
				m_SelectMode = SELECT_MENU_ONE;
				MenuDecide(SELECT_MENU_ONE);
			}
			else if (m_nSelect == 1)
			{
				m_SelectMode = SELECT_MENU_TWO;
				MenuDecide(SELECT_MENU_TWO);
			}
			else if (m_nSelect == 2)
			{
				m_SelectMode = SELECT_MENU_THREE;
				MenuDecide(SELECT_MENU_THREE);
			}
			else if (m_nSelect == 3)
			{
				m_SelectMode = SELECT_MENU_FOUR;
				MenuDecide(SELECT_MENU_FOUR);
			}
				m_bModeSelect = false;
		}
	}

	/* ���o */
	switch (m_MenuType)
	{
	case MENU_TYPE_TUTORIAL:
		ScrollMenu(SELECTMODEBGTYPE_BAND_L, -0.005f);
		ScrollMenu(SELECTMODEBGTYPE_BAND_R, 0.005f);

		SelectModeExplanation(m_nSelect);
		SelectAnimation(m_nSelect);

		SetSelectAnimation(POLYGONTYPE_BG, ANIMTYPE_X, 8, 4, 1, 15);
		break;

	case MENU_TYPE_RESULT:
		break;

	case MENU_TYPE_PAUSE:
		break;
	}
#ifdef _DEBUG

	if (pInput->GetTrigger(DIK_O) == true)
	{//TRUE�Ȃ�FALSE FALSE�Ȃ�TRUE
		m_bModeSelect = m_bModeSelect ? false : true;
	}

	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif
}

//=============================================================================
// �Z���N�g���j���[�N���X �`�揈��
//=============================================================================
void CSelectMenu::Draw(void){}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CSelectMenu::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_SELECTMENU; nCnt++)
	{
		// �e�N�X�`���̔j��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	if (m_pTextureBG != NULL)
	{
		m_pTextureBG->Release();
		m_pTextureBG = NULL;
	}
}
//=============================================================================
// ���肵�����j���[�̏���
//=============================================================================
void CSelectMenu::MenuDecide(SELECT_MENU MenuSelect)
{
	//�t�F�[�h���擾
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();

	switch (m_MenuType)
	{
	case MENU_TYPE_TUTORIAL:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CPlayerSelect::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), 150);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
			break;
		}
		break;

	case MENU_TYPE_RESULT:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_CHARASELECT, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_STAGESELECT, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_TITLE, pFade->FADE_OUT);
			break;
		}
		break;

	case MENU_TYPE_PAUSE:
		switch (MenuSelect)
		{
		case SELECT_MENU_ONE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_TWO:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_THREE:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		case SELECT_MENU_FOUR:
			CFade::SetFade(CManager::MODE_GAME, pFade->FADE_OUT);
			break;
		}
		break;
	}
}

//=============================================================================
// ���̕����X�N���[������
//=============================================================================
void CSelectMenu::ScrollMenu(SELECTMODEBGTYPE type,float fScroolSpeed)
{
	m_nCntScrool++;

	m_apPolygonBG[type]->SetTex(D3DXVECTOR2(0.0f , 0.0f + (m_nCntScrool*fScroolSpeed)),D3DXVECTOR2(1.0f, 1.0f + (m_nCntScrool*fScroolSpeed)));
}

//=============================================================================
// �I�����Ɛ������̓�������
//=============================================================================
void CSelectMenu::SelectModeExplanation(int MenuSelect)
{
	if (m_MenuType == MENU_TYPE_TUTORIAL)
	{
		switch (MenuSelect)
		{
		case 0:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 0);	//�ړ����o����
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* ���[�h�����̃e�N�X�`�� */
			m_apPolygonBG[4]->SetAnimation(0, 0.333f, 1.0f);

			/* �A�j���[�V�����ʒu */
			m_apPolygonBG[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG, 5);		//�ړ����o����
			m_apPolygonBG[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �I��UI */
			m_apPolygonBG[9]->SetPos(m_apPolygon[0]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			break;

		case 1:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 1);	//�ړ����o����
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* ���[�h�����̃e�N�X�`�� */
			m_apPolygonBG[4]->SetAnimation(1, 0.333f, 1.0f);

			/* �A�j���[�V�����ʒu */
			m_apPolygonBG[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG, 6);		//�ړ����o����
			m_apPolygonBG[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));

			/* �I��UI */
			m_apPolygonBG[9]->SetPos(m_apPolygon[1]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			break;

		case 2:
			/* ���[�h�I���E�B���h */
			m_apPolygon[0]->SetPos(m_Pos[0], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[1]->SetPos(m_Pos[1], 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygon[2]->SetPos(m_Pos[2], 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_MENU, 2);	//�ړ����o����

			/* ���[�h�����̃e�N�X�`�� */
			m_apPolygonBG[4]->SetAnimation(2, 0.333f, 1.0f);

			/* �A�j���[�V�����ʒu */
			m_apPolygonBG[5]->SetPos(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[6]->SetPos(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), 0.0f, -NOSELECT_MENU_SIZE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_apPolygonBG[7]->SetPos(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			SelectMove(POLYGONTYPE_BG,7);		//�ړ����o����

			/* �I��UI */
			m_apPolygonBG[9]->SetPos(m_apPolygon[2]->GetPosition(), 0.0f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));

			break;
		}
	}

}
//=============================================================================
// �Z���N�g���Ă郂�[�h�̃A�j���[�V����
//=============================================================================
void CSelectMenu::SelectAnimation(int MenuSelect)
{
	if (m_MenuType == MENU_TYPE_TUTORIAL)
	{
		switch (MenuSelect)
		{
		case 0:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygonBG[5]->SetTex(D3DXVECTOR2(0.0f+(0.5f*m_nPatturnAnim),0.666f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.999f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;

		case 1:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.333f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.666f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;

		case 2:
			m_nCntAnim++;
			if (m_nCntAnim > 20)
			{
				m_nPatturnAnim++;
				m_nCntAnim = 0;

				m_apPolygonBG[7]->SetTex(D3DXVECTOR2(0.0f + (0.5f*m_nPatturnAnim), 0.0f), D3DXVECTOR2(0.5f + (0.5f*m_nPatturnAnim), 0.333f));

				if (m_nPatturnAnim > 2)
				{
					m_nPatturnAnim = 0;
				}
			}
			break;
		}
	}
}
//=============================================================================
// �Z���N�g���Ă郂�[�h�̈ړ����o
//=============================================================================
void CSelectMenu::SelectMove(POLYGONTYPE type, int MenuNum)
{
	D3DXVECTOR3 SelectPos;
	switch (type)
	{
	case POLYGONTYPE_MENU:
		SelectPos = m_apPolygon[MenuNum]->GetPosition();

		if (m_fMoveMode >= 8.0f || m_fMoveMode <= -8.0f)
		{
			m_fChangeMode *= -1.0f;
		}

		//�ړ��ʂ����Z
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygon[MenuNum]->SetPos(SelectPos,0.0f,0.0f,D3DXCOLOR(1.0f,1.0f,1.0f,1.0f));
		break;

	case POLYGONTYPE_BG:
		SelectPos = m_apPolygonBG[MenuNum]->GetPosition();

		if (m_fMoveMode >= 8.0f || m_fMoveMode <= -8.0f)
		{
			m_fChangeMode *= -1.0f;
		}

		//�ړ��ʂ����Z
		m_fMoveMode += m_fChangeMode;
		SelectPos.y += m_fMoveMode;

		m_apPolygonBG[MenuNum]->SetPos(SelectPos, 0.0f, 0.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	}

}
//=============================================================================
// �A�j���[�V��������
//=============================================================================
void CSelectMenu::SetSelectAnimation(POLYGONTYPE type, ANIMTYPE AnimType, int MenuNum, int MaxAnimPatternX, int MaxAnimPatternY, int AnimSpeed)
{
	m_nCntAnim2++;
	switch (type)
	{
	case POLYGONTYPE_MENU:
		if (AnimType == ANIMTYPE_X)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternX)
			{
				m_nPatturnAnim2 = 0;
			}
			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f/ MaxAnimPatternX)*m_nPatturnAnim2),0.0f + (1.0f / MaxAnimPatternY)),
										 D3DXVECTOR2(((1.0f / MaxAnimPatternX)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternX)*m_nPatturnAnim2),
													(1.0f / MaxAnimPatternY) + (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternY)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygon[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim2)),
										 D3DXVECTOR2((1.0f / MaxAnimPatternX)+ (1.0f / MaxAnimPatternX),
													((1.0f / MaxAnimPatternY)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim2)));
		}
		break;

	case POLYGONTYPE_BG:
		if (AnimType == ANIMTYPE_X)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternX)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f+(1.0f/MaxAnimPatternX)*m_nPatturnAnim2,
														0.0f + (1.0f / MaxAnimPatternY)),
										D3DXVECTOR2((1.0f / MaxAnimPatternX)+ ((1.0f / MaxAnimPatternX)*m_nPatturnAnim2),
													(1.0f / MaxAnimPatternY)+ (1.0f / MaxAnimPatternY)));
		}
		else if (AnimType == ANIMTYPE_Y)
		{
			if (m_nCntAnim2 > AnimSpeed)
			{
				m_nPatturnAnim2++;
				m_nCntAnim2 = 0;
			}
			if (m_nPatturnAnim2 >= MaxAnimPatternY)
			{
				m_nPatturnAnim2 = 0;
			}

			m_apPolygonBG[MenuNum]->SetTex(D3DXVECTOR2(0.0f + (1.0f / MaxAnimPatternX), 0.0f + ((1.0f / MaxAnimPatternY) *m_nPatturnAnim2)),
				D3DXVECTOR2((1.0f / MaxAnimPatternX) + (1.0f / MaxAnimPatternX),
				((1.0f / MaxAnimPatternY)*m_nPatturnAnim2) + ((1.0f / MaxAnimPatternY)*m_nPatturnAnim2)));
		}
		break;
	}
}
//=============================================================================
// �`���[�g���A���̃|���S���̏����ʒu
//=============================================================================
void CSelectMenu::InitTutorialPolygon(void)
{
	/* ���j���[�|���S���̐ݒ� */
	m_InitPos.y = MENU_INITPOS;

	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{//���j���[�|���S���̏�����
		m_apPolygon[nCnt] = NULL;
	}

	/* �w�i�ݒ� */
	//�w�i
	m_apPolygonBG[0] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_BG", 2);
	m_apPolygonBG[0]->SetWidthHeight(MENU_BG*6.0f, MENU_BG * 3.5f);

	//���[�h���сi���j
	m_apPolygonBG[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_UI", 2);
	m_apPolygonBG[1]->SetWidthHeight(MENU_BG*BAND_SIZE, MENU_BG * 3.5f);

	//���[�h���сi�E�j
	m_apPolygonBG[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SCREEN_HEIGHT / 2, m_InitPos.z), "SELECTMODE_UI", 2);
	m_apPolygonBG[2]->SetWidthHeight(MENU_BG*BAND_SIZE, MENU_BG * 3.5f);

	//�t���[��
	m_apPolygonBG[3] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 640.0f, m_InitPos.z), "FRAME", 2);
	m_apPolygonBG[3]->SetWidthHeight(SCREEN_WIDTH / 2 * 1.1f, MENU_BG * 0.7f);

	//������
	m_apPolygonBG[4] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 645.0f, m_InitPos.z), "SELECTMODE_EXPLANATION", 2);
	m_apPolygonBG[4]->SetWidthHeight(SCREEN_WIDTH / 2 * 1.0f, MENU_BG * 0.63f);
	m_apPolygonBG[4]->SetAnimation(0, 1.0f, 0.33f);

	//�A�j���[�V�����F�Q�[��
	m_apPolygonBG[5] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x - 360.0f, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygonBG[5]->SetWidthHeight(MENU_BG*1.5f, MENU_BG * 1.5f);
	m_apPolygonBG[5]->SetTex(D3DXVECTOR2(0.0f, 0.666f), D3DXVECTOR2(0.5f, 0.999f));

	//�A�j���[�V�����F�����ꗗ
	m_apPolygonBG[6] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygonBG[6]->SetWidthHeight(MENU_BG*1.55f, MENU_BG * 1.55f);
	m_apPolygonBG[6]->SetTex(D3DXVECTOR2(0.0f, 0.333f), D3DXVECTOR2(0.5f, 0.666f));

	//�A�j���[�V�����F�^�C�g���ɖ߂�
	m_apPolygonBG[7] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x + 350.0f, MENU_INIT_POS, m_InitPos.z), "TITLEBACK_A");
	m_apPolygonBG[7]->SetWidthHeight(MENU_BG*1.2f, MENU_BG * 1.2f);
	m_apPolygonBG[7]->SetAnimation(0, 0.5f, 0.333f);

	//UI_�X�e�B�b�N
	m_apPolygonBG[8] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 250.0f, m_InitPos.z), "UI_OPERATION1", 2);
	m_apPolygonBG[8]->SetWidthHeight(MENU_BG*0.7f, MENU_BG * 0.7f);
	m_apPolygonBG[8]->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 1.0f));

	//UI_�I��
	m_apPolygonBG[9] = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y - 300.0f, m_InitPos.z), "UI_SELECT");
	m_apPolygonBG[9]->SetWidthHeight(m_fWidth*1.02f, m_fHeight * 1.05f);
	m_apPolygonBG[9]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));


	for (int nCnt = 0; nCnt < m_nMaxMenu; nCnt++)
	{
		m_Pos[nCnt] = m_InitPos;
		m_Pos[nCnt].x = m_InitPos.x + m_fInitYpos;
		//�ʒu�����炷
		m_Pos[nCnt].x = m_Pos[nCnt].x + (m_fSpace * (nCnt - 2));


		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MODESELEXT_MENU", 2);
			m_apPolygon[nCnt]->SetTex(D3DXVECTOR2(0.0f + (0.333f*nCnt), 0.0f), D3DXVECTOR2(0.333f + (0.333f*nCnt), 1.0f));
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}
}