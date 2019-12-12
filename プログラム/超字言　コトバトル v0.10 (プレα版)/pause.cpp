//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : Kodama Yuto
//
//	�N���X�̊T�v
//
//=============================================================================
#include "pause.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^&�f�X�g���N�^
//=============================================================================
CPause::CPause(int nPriority) : CScene(nPriority,OBJTYPE_PAUSE)
{
	m_pPause = NULL;
	m_pBG = NULL;
	for (int nCnt = 0; nCnt < 4; nCnt++) {
		m_apSelectMenu[nCnt] = NULL;
		m_aMenuDefaultPos[nCnt] = D3DXVECTOR3(0.0f,0.0f,0.0f);
	}
	m_nSelect = 0;
	m_nCount = 0;
}
CPause::~CPause()
{

}

//=============================================================================
// ��������
//=============================================================================
CPause* CPause::Create(void)
{
	CPause* pPause = NULL;

	pPause = new CPause(6);

	if (pPause != NULL)
	{
		pPause->Init();
	}

	return pPause;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(void)
{
	m_nSelect = 0;
	//�w�i�̐���
	m_pBG = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f,SCREEN_HEIGHT / 2.0f,0.0f),"",6);
	if (m_pBG != NULL)
	{
		m_pBG->SetObjType(OBJTYPE_PAUSE);
		m_pBG->SetWidthHeight(SCREEN_WIDTH,SCREEN_HEIGHT);
		m_pBG->SetCol(D3DXCOLOR(0.5f,0.5f,0.5f,0.65f));
	}

	//�|�[�Y�����̐���
	m_pPause = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f,75.0f,0.0f),"",7);
	if (m_pPause != NULL)
	{
		m_pPause->SetObjType(OBJTYPE_PAUSE);
		m_pPause->SetWidthHeight(400.0f,80.0f);
	}
	//�Z���N�g�̐���
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_aMenuDefaultPos[nCnt] = D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 210.0f + (nCnt * 150.0f), 0.0f);
		m_apSelectMenu[nCnt] = CScene2D::Create(m_aMenuDefaultPos[nCnt], "",7);
		if (m_apSelectMenu[nCnt] != NULL)
		{
			m_apSelectMenu[nCnt]->SetObjType(OBJTYPE_PAUSE);
			m_apSelectMenu[nCnt]->SetWidthHeight(200.0f, 60.0f);

		}

	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	//�|���S���폜
	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apSelectMenu[nCnt] != NULL)
		{
			m_apSelectMenu[nCnt]->Uninit();
			m_apSelectMenu[nCnt] = NULL;
		}
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
{
	m_nCount++;
	float fCntHover = (float)(m_nCount +1);

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		if (m_apSelectMenu[nCnt] != NULL)
		{
			m_apSelectMenu[nCnt]->SetWidthHeight(200.0f, 60.0f);
		}
	}

	if (CCommand::GetCommand("UP"))
	{
		m_nSelect = (m_nSelect + 3) % 4;
	}
	else if (CCommand::GetCommand("DOWN"))
	{
		m_nSelect = (m_nSelect + 1) % 4;
	}

	m_apSelectMenu[m_nSelect]->SetPosition(m_aMenuDefaultPos[m_nSelect] + D3DXVECTOR3(0.0f, cosf(fCntHover / 5.0f) * 1.5f, 0.0f));
	m_apSelectMenu[m_nSelect]->SetWidthHeight(300.0f, 90.0f);

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}
