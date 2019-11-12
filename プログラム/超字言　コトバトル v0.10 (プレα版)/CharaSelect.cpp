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

//============================================================================
//	�}�N����`
//============================================================================
#define SIZE_X (SCREEN_WIDTH/2)									//����
#define SIZE_Y (SCREEN_HEIGHT/2)								//�c��
#define DEFAULT_SIZE (150.0f)									//�|���S���T�C�Y�̊�{�̑傫��
#define DEFAULT_POS	(D3DXVECTOR3(0.0f,0.0f,0.0f))				//�|���S���̏����ʒu
#define CHARASELCHOICE_POS	(D3DXVECTOR3(430.0f,180.0f,0.0f))	//�I�����|���S���̈ʒu
#define CHARASELCHOICE_INTERVAL (350.0f)						//�I�����|���S�����m�̊��o
#define TEX_CORRECTION (0.0001f)								//�e�N�X�`�����W�̕␳
#define CURSOR_MOVE (2.0f)										//�J�[�\���̈ړ����x
#define CURSOR_SIZE (0.3f)										//�J�[�\���̃T�C�Y
//============================================================================
//�ÓI�����o�ϐ��錾
//============================================================================
CScene2D *CCharaSelect::m_apScene2D[MAX_CHARASELTEX] = {};
CScene2D *CCharaSelect::m_apSelect2D[MAX_CHARASELECT] = {};
CScene2D *CCharaSelect::m_apCursor2D = NULL;
CScene2D *CCharaSelect::m_apBadge2D = NULL;

//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CCharaSelect::CCharaSelect()
{
	m_move = DEFAULT_POS;
	m_bPCSelMove = false;

	/* ���o�n�ϐ������� */
	m_nCntScrool = 0;
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		m_fFlashAlpha[nCnt] = 1.0f;
		m_SelectState[nCnt] = SELECTSTATE_NOSELECT;
		m_SelectStateold[nCnt] = SELECTSTATE_NOSELECT;
		m_bPCColl[nCnt] = false;
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
	D3DXVECTOR3 pos = m_apCursor2D->GetPosition();
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();


	if (pFade->GetFade() == CFade::FADE_NONE)
	{
		//���[�h�J��
		if (m_bPCSelMove == true)
		{
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				pFade->SetFade(pManager->MODE_STAGESELECT, pFade->FADE_OUT);
			}
		}

		/* �J�[�\���ړ����� ���L�[�{�[�h����̂ݑΉ����A����R���g���[���[�Ή�  */
		if (pInputKeyboard->GetPress(DIK_D) == true)
		{//������
			if (pInputKeyboard->GetPress(DIK_W) == true)
			{//�㉟��
				m_move.x += sinf(D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{//������
				m_move.x += sinf(D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move.x += sinf(D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move.y += cosf(D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_A) == true)
		{//������
			if (pInputKeyboard->GetPress(DIK_W) == true)
			{//�㉟��
				m_move.x += sinf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.75f)*CURSOR_MOVE;
			}
			else if (pInputKeyboard->GetPress(DIK_S) == true)
			{//������
				m_move.x += sinf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.25f)*CURSOR_MOVE;
			}
			else
			{
				m_move.x += sinf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
				m_move.y += cosf(-D3DX_PI * 0.5f)*CURSOR_MOVE;
			}
		}
		else if (pInputKeyboard->GetPress(DIK_W) == true)
		{//�㉟��
			m_move.x += sinf(D3DX_PI)*CURSOR_MOVE;
			m_move.y += cosf(D3DX_PI)*CURSOR_MOVE;
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//������
			m_move.x -= sinf(D3DX_PI)*CURSOR_MOVE;
			m_move.y -= cosf(D3DX_PI)*CURSOR_MOVE;
		}
		/* �ړ��͈͐��� */
		pos = MoveRestriction(pos);

		/* �ړ� */
		pos += m_move;

		/* ���� */
		m_move = CUtilityMath::MoveCoeffient(m_move,0.3f);

		/* �ړ��𔽉f */
		m_apCursor2D->SetPosition(pos);

		/* ���I�����̂݃J�[�\���ɒǏ] */
		if (m_bPCSelMove == false)
		{
			m_apBadge2D->SetPosition(D3DXVECTOR3(m_apCursor2D->GetPosition().x, m_apCursor2D->GetPosition().y - 50.0f, m_apCursor2D->GetPosition().z));
		}

		/* �����蔻�� */
		m_bPCColl[0] = collision(CHARACTORTYPE_BALANCE);
		m_bPCColl[1] = collision(CHARACTORTYPE_POWOR);
		m_bPCColl[2] = collision(CHARACTORTYPE_SPEED);
		m_bPCColl[3] = collision(CHARACTORTYPE_REACH);

		for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
		{
			if (m_bPCColl[nCnt] == true)
			{
				if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
				{//�G���^�[����
					if (m_SelectState[nCnt] != SELECTSTATE_SELECT)
					{//�Z���N�g��Ԃ���Ȃ��i�����t���b�V���h�~�j
						m_SelectState[nCnt] = SELECTSTATE_FLASH;
						m_bPCSelMove = true;
					}
				}
			}
		}

		/* �I�������� */
		if (pInputKeyboard->GetPress(DIK_BACKSPACE) == true)
		{
			for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
			{
				if (collision((CHARACTORTYPE)nCnt) == true)
				{
					m_SelectState[(CHARACTORTYPE)nCnt] = SELECTSTATE_NOSELECT;
					m_bPCSelMove = false;
				}
			}
		}
	}
	/* �т̃e�N�X�`���X�N���[�� */
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_R, 0.005f);
	ScrollMenu(CHARASEL_POLYGONTYPE_BAND_L, -0.005f);

	/* �I�������o�֐� */
	SelectProduction(0);
	SelectProduction(1);
	SelectProduction(2);
	SelectProduction(3);

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
void CCharaSelect::SelectProduction(int SelNum)
{
	switch (m_SelectState[SelNum])
	{
	case SELECTSTATE_NONE:
		break;

	case SELECTSTATE_FLASH:		//���o��
		if (m_SelectStateold[SelNum] != SELECTSTATE_FLASH)
		{//�O��̃��[�h��Flash�ȊO�̏ꍇa�l��������
			m_fFlashAlpha[SelNum] = 1.0f;
		}
		m_apScene2D[SelNum+3]->SetbDraw(true);												//�}�X�N�̕`�悷��
		m_apScene2D[SelNum+3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[SelNum]));	//�F
		/* �I�����̃e�N�X�`�����W�̕ύX */
		m_apSelect2D[SelNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*SelNum), 0.5f+ TEX_CORRECTION),
									D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*SelNum) - TEX_CORRECTION, 1.0f));

		if (m_fFlashAlpha[SelNum] <= 0.0f)
		{//�����x��������؂���
			m_apScene2D[SelNum + 3]->SetbDraw(false);							//�}�X�N��`�悵�Ȃ��󋵂�
			m_apScene2D[SelNum + 3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	//�}�X�N�̐F����ɖ߂��Ă���
			m_fFlashAlpha[SelNum] = 0.0f;										//a�l���Y��Ȑ����ɕύX
			m_SelectState[SelNum] = SELECTSTATE_SELECT;							//�I�����ꂽ��ԂɕύX
		}
		else
		{
			m_fFlashAlpha[SelNum] -= 0.02f;
			m_apScene2D[SelNum + 3]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fFlashAlpha[SelNum]));
		}
		break;

	case SELECTSTATE_SELECT:	//�I������Ă���
		/* �I�����̃e�N�X�`�����W�̕ύX */
		m_apSelect2D[SelNum]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*SelNum), 0.5f + TEX_CORRECTION),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*SelNum) - TEX_CORRECTION, 1.0f));
		break;

	case SELECTSTATE_NOSELECT:	//�I������Ă��Ȃ�
		m_apScene2D[SelNum + 3]->SetbDraw(false);		//�}�X�N��`�悳��Ă��Ȃ���Ԃ�
		/* �I�����̃e�N�X�`�����W�̕ύX */
		m_apSelect2D[SelNum]->SetTex(D3DXVECTOR2(0.0f+((1.0f / MAX_CHARASELECT)*SelNum), 0.0f),
									D3DXVECTOR2((1.0f / MAX_CHARASELECT)+ ((1.0f / MAX_CHARASELECT)*SelNum), 0.499f));
		break;
	}

	//����̑I����Ԃ�O��̑I����ԂƂ��ĕۑ�
	m_SelectStateold[SelNum] = m_SelectState[SelNum];
}
//=============================================================================
// �|���S���̏����ݒ�
//=============================================================================
void CCharaSelect::InitCharaSelectPoly(void)
{
	/* �I���� */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		if (nCnt < MAX_CHARASELECT / 2)
		{//0,1
			m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*nCnt),
				CHARASELCHOICE_POS.y,
				CHARASELCHOICE_POS.z), "CHARACTORSEL_CHARA");
		}
		else
		{//2,3
			m_apSelect2D[nCnt] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*(nCnt - 2)),
				CHARASELCHOICE_POS.y + CHARASELCHOICE_INTERVAL,
				CHARASELCHOICE_POS.z), "CHARACTORSEL_CHARA");
		}
		/* �e�N�X�`�����W�ݒ� */
		m_apSelect2D[nCnt]->SetTex(D3DXVECTOR2(0.0f + ((1.0f / MAX_CHARASELECT)*nCnt), 0.0f),
			D3DXVECTOR2((1.0f / MAX_CHARASELECT) + ((1.0f / MAX_CHARASELECT)*nCnt) - TEX_CORRECTION, 0.445f));
		/* �T�C�Y�ݒ� */
		m_apSelect2D[nCnt]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.5f);
	}

	/* ���o */
	// �w�i
	m_apScene2D[0] = CScene2D::Create(D3DXVECTOR3(SIZE_X, SIZE_Y, 0), "PLAUERNUMSEL_BG", 1);
	m_apScene2D[0]->SetWidthHeight(DEFAULT_SIZE*6.0f, DEFAULT_SIZE*3.5f);

	//���[�h���сi���j
	m_apScene2D[1] = CScene2D::Create(D3DXVECTOR3(50.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 2);
	m_apScene2D[1]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);

	//���[�h���сi�E�j
	m_apScene2D[2] = CScene2D::Create(D3DXVECTOR3(1230.0f, SIZE_Y, 0.0f), "CHARACTORSEL_BAND", 2);
	m_apScene2D[2]->SetWidthHeight(DEFAULT_SIZE*0.5f, DEFAULT_SIZE*3.5f);
	/* �I�����̃}�X�N */
	for (int nCnt = 0; nCnt < MAX_CHARASELECT; nCnt++)
	{
		/* �����ƍ��W�ƃe�N�X�`�� */
		if (nCnt < MAX_CHARASELECT / 2)
		{//0,1
			m_apScene2D[nCnt + 3] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*nCnt),
				CHARASELCHOICE_POS.y,
				CHARASELCHOICE_POS.z), " ");
		}
		else
		{//2,3
			m_apScene2D[nCnt + 3] = CScene2D::Create(D3DXVECTOR3(CHARASELCHOICE_POS.x + (CHARASELCHOICE_INTERVAL*(nCnt - 2)),
				CHARASELCHOICE_POS.y + CHARASELCHOICE_INTERVAL,
				CHARASELCHOICE_POS.z), " ");
		}
		/* �T�C�Y�ݒ� */
		m_apScene2D[nCnt + 3]->SetWidthHeight(DEFAULT_SIZE*1.5f, DEFAULT_SIZE*1.5f);
		m_apScene2D[nCnt + 3]->SetbDraw(false);
	}

	m_apBadge2D= CScene2D::Create(CHARASELCHOICE_POS, "CHARASEL_BADGE");
	m_apBadge2D->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);
	m_apBadge2D->SetTex(D3DXVECTOR2(0.0f, 0.5f), D3DXVECTOR2(0.25f, 1.0f));

	m_apCursor2D = CScene2D::Create(CHARASELCHOICE_POS,"CHARASEL_BADGE");
	m_apCursor2D->SetWidthHeight(DEFAULT_SIZE*CURSOR_SIZE, DEFAULT_SIZE*CURSOR_SIZE);
	m_apCursor2D->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.25f, 0.5f));

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
bool CCharaSelect::collision(CHARACTORTYPE type)
{
	bool bColl = false;

	/* �����蔻�� */
	if (m_apBadge2D->GetPosition().x - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().x + (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D->GetPosition().x + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().x - (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D->GetPosition().y + DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) >= m_apSelect2D[type]->GetPosition().y - (DEFAULT_SIZE*1.0f) &&
		m_apBadge2D->GetPosition().y - DEFAULT_SIZE*(CURSOR_SIZE - 0.2f) <= m_apSelect2D[type]->GetPosition().y + (DEFAULT_SIZE*1.0f))
	{
		bColl = true;
	}

	return bColl;
}