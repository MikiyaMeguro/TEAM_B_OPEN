//---------------------------------------------------------------------
// ���[�h�Z���N�g���� [modeselect.cpp]
// Author : Mikiya Meguro
//---------------------------------------------------------------------
#include "PlayerNumSelect.h"
#include "scene.h"
#include "scene2D.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "renderer.h"
#include "load.h"
#include "texture.h"
#include "debugProc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODESELECT_WIDTH		(3.0f)		//�|���S���̑傫��(��)
#define MODESELECT_HEIGHT		(1.5f)		//�|���S���̑傫��(�c)
#define MENU_WIDTH				(450.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define MENU_HEIGHT				(250.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define MENU_INITPOS			(320.0f)	//���j���[�̏����ʒu
#define MENU_NUM_HEIGHT			(2)
#define MENU_NUM_WIDTH			(2)
#define LOGO_POS				(100.0f)
#define LOGO_WIDTH				(4.5f)		//�|���S���̑傫��(��)
#define LOGO_HEIGHT				(1.2f)		//�|���S���̑傫��(�c)

#define CAUTIONBG_WIDTH			(750.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define CAUTIONBG_HEIGHT		(450.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)
#define CAUTION_WIDTH			(650.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(��)
#define CAUTION_HEIGHT			(250.0f)	//�|���S���ƃ|���S���̊Ԃ̑傫��(�c)



//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9 CPlayerSelect::m_pTexture[MAX_PLAYER_SELECTMENU] = {};
LPDIRECT3DTEXTURE9 CPlayerSelect::m_pTextureBG = NULL;
CPlayerSelect::SELECTPLAYER CPlayerSelect::m_SelectMode = CPlayerSelect::SELECTPLAYER_NONE;
bool CPlayerSelect::m_bModeSelect = false;

//--------------------------------------------
//���[�h�Z���N�g�N���X �R���X�g���N�^
//--------------------------------------------
CPlayerSelect::CPlayerSelect(int nPriority) : CScene(7)
{
	//�l�̏�����
	m_nSelect = 0;
	m_TexMove = D3DXVECTOR3(0, 0, 0);
	m_aModeSelectMenu[0].select = SELECTTYPE_SELECT;
	m_aModeSelectMenu[1].select = SELECTTYPE_NONE;
	m_aModeSelectMenu[2].select = SELECTTYPE_NONE;
	m_bCaution = false;
	m_bCreate2D = false;
	m_nSelectCaution = 1;
	m_SelectCaution[0].select = SELECTTYPE_NONE;
	m_SelectCaution[1].select = SELECTTYPE_SELECT;
}

//--------------------------------------------
//���[�h�Z���N�g�N���X �f�X�g���N�^
//--------------------------------------------
CPlayerSelect::~CPlayerSelect()
{
}

//--------------------------------------------
//�I�u�W�F�N�g�̐���
//--------------------------------------------
CPlayerSelect *CPlayerSelect::Create(D3DXVECTOR3 pos, float m_fWidth)
{
	//���[�h�Z���N�g�̃|�C���^
	CPlayerSelect *pModeSelect;
	pModeSelect = new CPlayerSelect;

	pModeSelect->m_InitPos = pos;
	pModeSelect->m_fWidth = m_fWidth;
	pModeSelect->m_fHeight = m_fWidth;
	//���[�h�Z���N�g�̏�����
	pModeSelect->Init();
	//���[�h�Z���N�g�̏���Ԃ�
	return pModeSelect;
}


//=============================================================================
// ����������
//=============================================================================
HRESULT CPlayerSelect::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		m_apPolygon[nCnt] = NULL;
	}

	m_pSelect2D[0] = NULL;
	m_pSelect2D[1] = NULL;
	m_pCaution2D = NULL;
	m_pCaution2DBG = NULL;
	//m_pTextureBG = CLoad::GetTexture(CLoad::TEXTURE_MODESELECT_BG);
	m_pTexture[0] = CTexture::GetTexture("MENU_1P");
	m_pTexture[1] = CTexture::GetTexture("MENU_2P");
	m_pTexture[2] = CTexture::GetTexture("MENU_3P");
	m_pTexture[3] = CTexture::GetTexture("MENU_4P");

	//BG�̏�����
	m_apPolygonBG = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, m_InitPos.y, m_InitPos.z),"BLOCK");
	m_apPolygonBG->BindTexture(m_pTextureBG);
	m_apPolygonBG->SetWidthHeight(m_fWidth * 4.9f, m_fHeight * 3.5f);
	m_apPolygonBG->SetbDraw(true);

	m_InitPos.y = MENU_INITPOS;

	m_pMenuLogo = CScene2D::Create(D3DXVECTOR3(m_InitPos.x, LOGO_POS, m_InitPos.z), "MENU_NUMPLAYER");
	m_pMenuLogo->SetWidthHeight(m_fWidth * LOGO_WIDTH, m_fHeight * LOGO_HEIGHT);
	m_pMenuLogo->SetbDraw(true);



	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		if (nCnt < 2)
		{
			//�|���S���̈ʒu������ɏ�����
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x - (MENU_WIDTH / 2);
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (MENU_WIDTH * nCnt);
		}
		else if (nCnt > 1)
		{
			//�|���S���̈ʒu������ɏ�����
			m_Pos[nCnt] = m_InitPos;
			m_Pos[nCnt].x = m_InitPos.x - (MENU_WIDTH / 2);
			m_Pos[nCnt].y = m_InitPos.y + MENU_HEIGHT;
			//�ʒu�����炷
			m_Pos[nCnt].x = m_Pos[nCnt].x + (MENU_WIDTH * (nCnt - 2));
		}

		if (m_apPolygon[nCnt] == NULL)
		{
			m_apPolygon[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "BLOCK");
			m_apPolygon[nCnt]->SetWidthHeight(m_fWidth * MODESELECT_WIDTH, m_fHeight * MODESELECT_HEIGHT);
			m_apPolygon[nCnt]->BindTexture(m_pTexture[nCnt]);
			m_apPolygon[nCnt]->SetbDraw(true);
		}
	}

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
// ���[�h�Z���N�g�N���X �I������
//=============================================================================
void CPlayerSelect::Uninit(void)
{

	//������j��
	Release();
}

//=============================================================================
// ���[�h�Z���N�g�N���X �X�V����
//=============================================================================
void CPlayerSelect::Update(void)
{
	//�L�[�{�[�h�����擾
	CInputKeyboard *pInput = CManager::GetInputKeyboard();
	//�t�F�[�h���擾
	CManager *pManager = NULL;
	CFade *pFade = pManager->GetFade();


	//�T�E���h�����擾
	CSound *pSound = CManager::GetSound(0);

	//�\���ؑ�
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
	{
		m_apPolygon[nCnt]->SetbDraw(m_bModeSelect);
	}
	m_apPolygonBG->SetbDraw(m_bModeSelect);


#ifdef  _DEBUG
	if (pInput->GetTrigger(DIK_O) == true)
	{//TRUE�Ȃ�FALSE FALSE�Ȃ�TRUE
		m_bModeSelect = m_bModeSelect ? false : true;
	}
#endif

	//���[�h�Z���N�g��
	if (m_bModeSelect == true && pFade->GetFade() == CFade::FADE_NONE)
	{
		//�I������
		if (CCommand::GetCommand("DOWN") && m_bCaution == false)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect < 2)
			{
				m_nSelect = (m_nSelect + MAX_PLAYER_SELECTMENU / 2) % (MAX_PLAYER_SELECTMENU);
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("UP") && m_bCaution == false)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_SELECT);
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect > 1)
			{
				m_nSelect = m_nSelect - 2;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("RIGHT") && m_bCaution == false)
		{
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect == 1)
			{
				m_nSelect = 1;
			}
			else if (m_nSelect == 3)
			{
				m_nSelect =  3;
			}
			else
			{
				m_nSelect = (m_nSelect + 1) % 4;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}
		else if (CCommand::GetCommand("LEFT") && m_bCaution == false)
		{
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_NONE;
			if (m_nSelect == 0)
			{
				m_nSelect = 0;
			}
			else if (m_nSelect == 2)
			{
				m_nSelect = 2;
			}
			else
			{
				m_nSelect = (m_nSelect + 3) % 4;
			}
			m_aModeSelectMenu[m_nSelect].select = SELECTTYPE_SELECT;
		}

		//�G���^�[�L�[
		if (CCommand::GetCommand("ENTER")== true && m_bCaution == false)
		{
			//pSound->PlaySound(pSound->SOUND_LABEL_SE_CANCEL);
			if (m_nSelect == 0)
			{
				m_SelectMode = SELECTPLAYER_1P;
			}
			else if (m_nSelect == 1)
			{
				m_SelectMode = SELECTPLAYER_2P;
			}
			else if (m_nSelect == 2)
			{
				m_SelectMode = SELECTPLAYER_3P;
			}
			else if (m_nSelect == 3)
			{
				m_SelectMode = SELECTPLAYER_4P;
			}
			//�x����\��
			m_bCaution = true;
		}

		//�ŏI�x��	2D���쐬���ꂽ��
		if (CCommand::GetCommand("ENTER") && m_bCreate2D == true)
		{
			switch (m_SelectMode)
			{
			case SELECTPLAYER_1P:
				break;
			case SELECTPLAYER_2P:
				break;
			case SELECTPLAYER_3P:
				break;
			case SELECTPLAYER_4P:
				break;
			}
			//2D��j��
			Caution2DUninit();
			if (m_nSelectCaution == 0)
			{
				CFade::SetFade(CManager::MODE_TUTORIAL, pFade->FADE_OUT);
			}

			m_nSelectCaution = 1;
			m_SelectCaution[0].select = SELECTTYPE_NONE;
			m_SelectCaution[1].select = SELECTTYPE_SELECT;
			m_bCreate2D = false;
		}
		else if (pInput->GetTrigger(DIK_B) == true)
		{
			//2D��j��
			Caution2DUninit();
			m_nSelectCaution = 1;
			m_SelectCaution[0].select = SELECTTYPE_NONE;
			m_SelectCaution[1].select = SELECTTYPE_SELECT;
				m_bCreate2D = false;
		}

		//�x���\����
		if (m_bCaution == true)
		{
			if (m_bCreate2D == false)
			{
				//�x���𐶐�
				m_pCaution2DBG = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0), "BLOCK");
				m_pCaution2DBG->SetWidthHeight(CAUTIONBG_WIDTH, CAUTIONBG_HEIGHT);
				m_pCaution2DBG->SetbDraw(true);
				m_pCaution2DBG->BindTexture(m_pTextureBG);

				m_pCaution2D = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3.0f, 0), "BLOCK");
				m_pCaution2D->SetWidthHeight(CAUTION_WIDTH, CAUTION_HEIGHT);
				m_pCaution2D->BindTexture(CTexture::GetTexture("MENU_START"));
				m_pCaution2D->SetbDraw(true);

				//YES or NO�@�|���S������
				for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
				{
					//�|���S���̈ʒu������ɏ�����
					m_Pos[nCnt] = m_InitPos;
					m_Pos[nCnt].x = m_InitPos.x - (350 / 2);
					//�ʒu�����炷
					m_Pos[nCnt].x = m_Pos[nCnt].x + (360 * nCnt);
					m_Pos[nCnt].y = 500.0f;
					if (m_pSelect2D[nCnt] == NULL)
					{	//����
						m_pSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(m_Pos[nCnt].x, m_Pos[nCnt].y, m_Pos[nCnt].z), "MENU_START");
						m_pSelect2D[nCnt]->SetWidthHeight(600, 300);
						if (nCnt == 0)
						{
							m_pSelect2D[nCnt]->BindTexture(CTexture::GetTexture("MENU_YES"));
						}
						if (nCnt == 1)
						{
							m_pSelect2D[nCnt]->BindTexture(CTexture::GetTexture("MENU_NO"));
						}
						m_pSelect2D[nCnt]->SetbDraw(true);
					}
				}
				//2D�|���S���𐶐�����
				m_bCreate2D = true;
			}
			else
			{
				//�F�ς�
				for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
				{
					if (m_SelectCaution[nCnt].select == SELECTTYPE_SELECT)
					{//�I�𒆂̐F
						m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
					}
					else
					{//���I���̐F
						m_SelectCaution[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					}
					//���_���ւ̃|�C���^
					VERTEX_2D *pVtx;
					//���_�o�b�t�@���擾
					m_pVtxBuff = m_pSelect2D[nCnt]->GetBuff();
					//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
					//���_�J���[
					pVtx[0].col = m_SelectCaution[nCnt].col;
					pVtx[1].col = m_SelectCaution[nCnt].col;
					pVtx[2].col = m_SelectCaution[nCnt].col;
					pVtx[3].col = m_SelectCaution[nCnt].col;
					// ���_�o�b�t�@���A�����b�N����
					m_pVtxBuff->Unlock();
				}
			}

			if (CCommand::GetCommand("RIGHT") && m_bCaution == true)
			{
				m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
				//�E�[�Ŏ~�܂�
				if (m_nSelectCaution < 1)
				{
					m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
				}
				m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
			}
			else if (CCommand::GetCommand("LEFT") && m_bCaution == true)
			{
				m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_NONE;
				//���[�Ŏ~�܂�
				if (m_nSelectCaution > 0)
				{
					m_nSelectCaution = (m_nSelectCaution + 1) % MAX_CAUTIONMENU;
				}
				m_SelectCaution[m_nSelectCaution].select = SELECTTYPE_SELECT;
			}
		}

		//�F�ς�
		for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
		{
			if (m_aModeSelectMenu[nCnt].select == SELECTTYPE_SELECT)
			{//�I�𒆂̐F
				m_aModeSelectMenu[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
			}
			else
			{//���I���̐F
				m_aModeSelectMenu[nCnt].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}

			//���_���ւ̃|�C���^
			VERTEX_2D *pVtx;
			//���_�o�b�t�@���擾
			m_pVtxBuff = m_apPolygon[nCnt]->GetBuff();
			//���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
			m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
			//���_�J���[
			pVtx[0].col = m_aModeSelectMenu[nCnt].col;
			pVtx[1].col = m_aModeSelectMenu[nCnt].col;
			pVtx[2].col = m_aModeSelectMenu[nCnt].col;
			pVtx[3].col = m_aModeSelectMenu[nCnt].col;
			// ���_�o�b�t�@���A�����b�N����
			m_pVtxBuff->Unlock();
		}

		////���_���ւ̃|�C���^
		//VERTEX_2D *pVtx;
		////���_�o�b�t�@���擾
		//m_pVtxBuff = m_apPolygonBG->GetBuff();
		////���_�o�b�t�@�����b�N�����_�f�[�^�̃|�C���^���擾
		//m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
		////���_�e�N�X�`��
		//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		//// ���_�o�b�t�@���A�����b�N����
		//m_pVtxBuff->Unlock();
	}
#ifdef _DEBUG
	CDebugProc::Print("cn", "m_nSelect : ", m_nSelect);
#endif

}

//=============================================================================
// ���[�h�Z���N�g�N���X �`�揈��
//=============================================================================
void CPlayerSelect::Draw(void)
{
}

//=============================================================================
// ���[�h�Z���N�g�N���X�@�I���������[�h���擾
//=============================================================================
CPlayerSelect::SELECTPLAYER * CPlayerSelect::GetModeSelectMode(void)
{
	return &m_SelectMode;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ��ݏ���
//=============================================================================
HRESULT CPlayerSelect::Load(void)
{

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j������
//=============================================================================
void CPlayerSelect::UnLoad(void)
{
	for (int nCnt = 0; nCnt < MAX_PLAYER_SELECTMENU; nCnt++)
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
// ���[�h�Z���N�g�̏�Ԃ��擾
//=============================================================================
bool CPlayerSelect::GetModeSelectBool(void)
{
	return m_bModeSelect;
}

//=============================================================================
// ���[�h�Z���N�g�̏�Ԃ�ݒ�
//=============================================================================
void CPlayerSelect::SetModeSelectBool(bool ModeSelectBool)
{
	m_bModeSelect = ModeSelectBool;
}

//=============================================================================
// �x��2D�̔j��
//=============================================================================
void CPlayerSelect::Caution2DUninit(void)
{
	//2D��j��
	if (m_pCaution2D != NULL)
	{
		m_pCaution2D->Uninit();
		m_pCaution2D = NULL;
		m_bCaution = false;
	}
	if (m_pCaution2DBG != NULL)
	{
		m_pCaution2DBG->Uninit();
		m_pCaution2DBG = NULL;
		m_bCaution = false;
	}
	for (int nCnt = 0; nCnt < MAX_CAUTIONMENU; nCnt++)
	{
		if (m_pSelect2D[nCnt] != NULL)
		{
			m_pSelect2D[nCnt]->Uninit();
			m_pSelect2D[nCnt] = NULL;
			m_pSelect2D[nCnt] = false;
		}
	}
}

