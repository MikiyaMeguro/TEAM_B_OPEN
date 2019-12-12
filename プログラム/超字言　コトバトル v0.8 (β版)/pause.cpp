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
	for (int nCnt = 0; nCnt < 4; nCnt++) { m_apSelectMenu[nCnt] = NULL; }
	m_nSelect = 0;
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
		m_pBG->SetCol(D3DXCOLOR(0.5f,0.5f,0.5f,0.75f));
	}

	//�|�[�Y�����̐���
	m_pPause = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f,50.0f,0.0f),"",7);
	if (m_pPause != NULL)
	{
		m_pPause->SetObjType(OBJTYPE_PAUSE);
		m_pPause->SetWidthHeight(100.0f,50.0f);
	}
	//�Z���N�g�̐���
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_apSelectMenu[nCnt] = CScene2D::Create(D3DXVECTOR3(SCREEN_WIDTH / 2.0f, 100.0f + (nCnt * 50.0f), 0.0f), "",7);
		if (m_apSelectMenu[nCnt] != NULL)
		{
			m_apSelectMenu[nCnt]->SetObjType(OBJTYPE_PAUSE);
			m_apSelectMenu[nCnt]->SetWidthHeight(200.0f, 100.0f);

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

}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}
