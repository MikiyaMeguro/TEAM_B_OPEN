//=============================================================================
//
// �^�C�}�[���� [time.cpp]
// Author : keisuke komatsu
//
//=============================================================================
#include "manager.h"
#include "renderer.h"
#include "point.h"
#include "number.h"
#include "game.h"
#include "fade.h"
#include "player.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CENTER_WIDTH		(SCREEN_WIDTH / 2)				// X�̒��S���W
#define TIMER_SPACE			(30.0f)							// �����Ɛ����̊Ԃ̃T�C�Y(�Q�[������)
#define TIMER_POSITION_Y	(70.0f)							// �^�C�}�[��Y���W(�Q�[������)
#define POWER_X				(10)
#define POINT_POS_1P_ONE	(D3DXVECTOR3(170.0f, 80.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define POINT_POS_2P_ONE	(D3DXVECTOR3(450.0f, 80.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define POINT_POS_3P_ONE	(D3DXVECTOR3(930.0f, 80.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define POINT_POS_4P_ONE	(D3DXVECTOR3(1210.0f, 80.0f, 0.0f))	// �������Ԃ̈ʒu(1P�����̏ꍇ)
#define POINT_POS_2P_TWO	(D3DXVECTOR3(170.0f, 440.0f, 0.0f))	// �������Ԃ̈ʒu(2 �` 4��ʂ����̏ꍇ)
#define POINT_POS_4P_TWO	(D3DXVECTOR3(1210.0f, 440.0f, 0.0f))// �������Ԃ̈ʒu(2 �` 4��ʂ����̏ꍇ)

#define WAIT_TIME_END		(180)							// �҂�����
#define MAX_POINT			(99)							// �ő吔
//=============================================================================
//	�ÓI�����o�ϐ�
//=============================================================================

//=============================================================================
// ��������
//=============================================================================
CPoint *CPoint::Create(int nID, int nNumPlayer, TYPE_CHARACTER type)
{
	CPoint *pPoint = NULL;

	//NULL�`�F�b�N
	if (pPoint == NULL)
	{//���I�m��
		pPoint = new CPoint;

		//NULL�`�F�b�N
		if (pPoint != NULL)
		{
			pPoint->PointPostion(nNumPlayer, nID);	// �|�C���g�̈ʒu�܂Ƃ�
			pPoint->m_type = type;		// ��ނ���
			pPoint->m_nNumPlayer = nNumPlayer;		// �l�����擾
			pPoint->m_nID = nID;
			//����������
			pPoint->Init();
		}
	}

	return pPoint;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPoint::CPoint(int nPriority, CScene::OBJTYPE objType) : CScene(nPriority, objType)
{
	m_nPointNum = 1;
	m_bStart = false;
	m_pIcon = NULL;
	m_nID = 0;
	m_type = TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPoint::~CPoint() {}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPoint::Init(void)
{
	int nTexData = 0;
	m_nTotalPoint = 0;
	m_nPointNum = PowerCalculation(m_nTotalPoint);

	PointBGCreate();		// �|�C���g�̔w�i����

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{	// �|�C���g�����ݒ�
		m_apNumber[nCntPoint] = new CNumber;
		m_apNumber[nCntPoint]->Init(D3DXVECTOR3((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y, m_pos.z), 0);
		m_apNumber[nCntPoint]->SetSize(D3DXVECTOR2(25.0f, 30.0f), D3DXVECTOR2((m_pos.x - TIMER_SPACE * nCntPoint), m_pos.y));
		m_apNumber[nCntPoint]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	// �����̃e�N�X�`���ݒ�
	TexPoint(nTexData);

	// UI�̐����ݒ�
	UIPosition();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPoint::Uninit(void)
{
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{	// �^�C�}�[�̔j��
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->Uninit();
			m_apNumber[nCntPoint] = NULL;
		}
	}

	if (m_pIcon != NULL)
	{
		m_pIcon->Uninit();
		m_pIcon = NULL;
	}

	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPoint::Update(void)
{
	//���݂̃��[�h�̎擾
	CManager::MODE GameMode = CManager::GetMode();
	DebugKey();		// �f�o�b�N�p

	if ((GameMode == CManager::MODE_GAME) || (GameMode == CManager::MODE_TUTORIAL))
	{//��������
	 //�Q�[��
		int nTexData = 0;
		// �����̃e�N�X�`���ݒ�
		TexPoint(nTexData);
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPoint::Draw(void)
{
	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->Draw();
		}
	}

	if (m_pIcon != NULL)
	{
		m_pIcon->Draw();
	}
}

//=============================================================================
// �^�C�}�[��Texture�Ǘ�
//=============================================================================
void CPoint::TexPoint(int nTexData)
{
	nTexData = m_nTotalPoint;

	for (int nCntPoint = 0; nCntPoint < m_nPointNum; nCntPoint++)
	{// �e�N�X�`���ɔ��f
		if (m_apNumber[nCntPoint] != NULL)
		{
			m_apNumber[nCntPoint]->SetNumber(nTexData);
			nTexData /= 10;
		}
	}
}
//=============================================================================
// �^�C�����Z����
//=============================================================================
void CPoint::AddPoint(int nPoint)
{
	if (m_nTotalPoint > 0)
	{
		m_nTotalPoint += nPoint;
	}

	if (MAX_POINT < m_nTotalPoint) { m_nTotalPoint = MAX_POINT; }
	m_nPointNum = PowerCalculation(m_nTotalPoint);
}
//=============================================================================
// �ׂ���̌v�Z
//=============================================================================
int CPoint::PowerCalculation(int nData)
{
	int nNum = 1;
	int nPower = (int)std::pow(POWER_X, nNum);
	int nDataNum = nData;
	while ((nDataNum / nPower) != 0)
	{
		nNum++;
		nPower = (int)std::pow(POWER_X, nNum);		// �ׂ��悷��(����O��Ȃ�)
		if (nNum >= MAX_POINT_NUM) { nNum = MAX_POINT_NUM; }
	}
	return nNum;
}

//=============================================================================
// ���Ԃ̊Ǘ�
//=============================================================================
void CPoint::TimeManagement(void)
{
	
}
//=============================================================================
// �f�o�b�N�p
//=============================================================================
void CPoint::DebugKey(void)
{
	
}

//=============================================================================
// �|�C���g�̔w�i����
//=============================================================================
void CPoint::PointBGCreate(void)
{
	CScene2D *pBg = NULL;

	BGPosition(pBg);
}

//=============================================================================
// �w�i�̈ʒu�ݒ�
//=============================================================================
void CPoint::BGPosition(CScene2D *pBg)
{
	// �l�����w�萔�� ���� �v���C���[ID���w�肵���ԍ��̏ꍇ
	if (m_nNumPlayer > 0 && m_nNumPlayer <= MAX_PLAYER && m_nID == 0)
	{	// ��ʍ��� (1�`4��� 1P)�̈ʒu
		pBg = CScene2D::Create(D3DXVECTOR3(120.0f, 60.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer == 1 && m_nID == 3 || m_nNumPlayer == 2 && m_nID == 1 || m_nNumPlayer > 2 && m_nNumPlayer <= MAX_PLAYER && m_nID == 1)
	{	// ��ʉE�� (1��� 4P , 2��� 2P, 3�`4��� 2P)�̈ʒu
		pBg = CScene2D::Create(D3DXVECTOR3(1160.0f, 60.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nID == 1&& m_nNumPlayer == 1)
	{	// ��ʍ��� (1��� 2P)�̈ʒu
		pBg = CScene2D::Create(D3DXVECTOR3(400.0f, 60.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nID == 2 && m_nNumPlayer == 1)
	{	// ��ʉE�� (1��� 3P)�̈ʒu
		pBg = CScene2D::Create(D3DXVECTOR3(880.0f, 60.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer > 1 && m_nNumPlayer <= MAX_PLAYER && m_nID == 2)
	{	// ��ʍ� (�Q��� 2P , 3��ʁA4��� 3P)�̈ʒu
		pBg = CScene2D::Create(D3DXVECTOR3(120.0f, 418.0f, 0.0f), "BG_FREAME", 5);
	}
	else if (m_nNumPlayer > 1 && m_nNumPlayer <= MAX_PLAYER && m_nID == 3)
	{	// ��ʉE (�Q��� �` 4��� 4P)�̈ʒu
		pBg = CScene2D::Create(D3DXVECTOR3(1160.0f, 418.0f, 0.0f), "BG_FREAME", 5);
	}

	if (pBg != NULL)
	{	// �T�C�Y�ƐF�̐ݒ�
		pBg->SetWidthHeight(150.0f, 70.0f);
		pBg->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

}

//=============================================================================
// UI�̈ʒu�ݒ�
//=============================================================================
void CPoint::UIPosition(void)
{
	char *cName[MAX_PLAYER] = { "�L����(�X�s�[�h)", "�L����(�o�����X)", "�L����(�p���[)", "�L����(���[�`)" };
	D3DXVECTOR3 posIcon = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posNumber = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 posLogo = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CScene2D *pNumber = NULL;
	CScene2D *pLogo = NULL;

	// �l�����w�萔�� ���� �v���C���[ID���w�肵���ԍ��̏ꍇ
	if (m_nNumPlayer > 0 && m_nNumPlayer <= MAX_PLAYER && m_nID == 0)
	{	// 1�`4��� 1P�̈ʒu
		posIcon = D3DXVECTOR3(65.0f, 75.0f, 0.0f);
		posNumber = D3DXVECTOR3(65.0f, 28.0f, 0.0f);
		posLogo = D3DXVECTOR3(165.0f, 32.0f, 0.0f);
	}
	else if (m_nID == 1 && m_nNumPlayer == 1)
	{	// 1��� 2P�̏ꍇ
		posIcon = D3DXVECTOR3(345.0f, 75.0f, 0.0f);
		posNumber = D3DXVECTOR3(345.0f, 28.0f, 0.0f);
		posLogo = D3DXVECTOR3(445.0f, 32.0f, 0.0f);
	}
	else if (m_nID == 2 && m_nNumPlayer == 1)
	{	// 1��� 3P�̏ꍇ
		posIcon = D3DXVECTOR3(825.0f, 75.0f, 0.0f);
		posNumber = D3DXVECTOR3(825.0f, 28.0f, 0.0f);
		posLogo = D3DXVECTOR3(925.0f, 32.0f, 0.0f);
	}
	else if (m_nID == 3 && m_nNumPlayer == 1 || m_nID == 2 && m_nNumPlayer == 2 || m_nID == 1 && m_nNumPlayer == 3 || m_nID == 1 && m_nNumPlayer == 4)
	{	// 1��� 4P, 2��� 3P, 3��� 2P, 4��� 2P�̈ʒu
		posIcon = D3DXVECTOR3(1105.0f, 75.0f, 0.0f);
		posNumber = D3DXVECTOR3(1105.0f, 28.0f, 0.0f);
		posLogo = D3DXVECTOR3(1205.0f, 32.0f, 0.0f);
	}
	else if (m_nID == 1 && m_nNumPlayer == 2 || m_nID == 2 && m_nNumPlayer == 3 || m_nID == 2 && m_nNumPlayer == 4)
	{ // 2��� 2P, 3��� 3P, 4��� 3P�̈ʒu
		posIcon = D3DXVECTOR3(65.0f, 435.0f, 0.0f);
		posNumber = D3DXVECTOR3(65.0f, 386.0f, 0.0f);
		posLogo = D3DXVECTOR3(165.0f, 390.0f, 0.0f);
	}
	else if (m_nID == 3 && m_nNumPlayer == 2 || m_nID == 3 && m_nNumPlayer == 3 || m_nID == 3 && m_nNumPlayer == 4)
	{	// 2��� 4P, 3��� 4P, 4��� 4P�̈ʒu
		posIcon = D3DXVECTOR3(1105.0f, 435.0f, 0.0f);
		posNumber = D3DXVECTOR3(1105.0f, 386.0f, 0.0f);
		posLogo = D3DXVECTOR3(1205.0f, 390.0f, 0.0f);
	}

	// �L�����N�^�[�A�C�R���̃��S
	if (m_pIcon == NULL)
	{
		m_pIcon = CScene2D::Create(posIcon, cName[3], 6);
		m_pIcon->SetWidthHeight(50.0f, 40.0f);
		m_pIcon->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}

	if (m_type == CPoint::TYPE_CPU)
	{	// CPU�̏ꍇ
		m_nID = 4;					// �����̔ԍ���5�ԂɎw��
	}

	// �L�����N�^�[�ԍ��̐�
	pNumber = CScene2D::Create(posNumber, "�v���C�l��", 6);
	pNumber->SetWidthHeight(60.0f, 20.0f);
	pNumber->SetTex(D3DXVECTOR2(0.0f, m_nID * 0.2f), D3DXVECTOR2(1.0f, (m_nID * 0.2f) + 0.2f));
	pNumber->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	// �L�����N�^�[�ԍ��̐ݒ�
	pLogo = CScene2D::Create(posLogo, "POINT", 6);
	pLogo->SetWidthHeight(60.0f, 20.0f);
	pLogo->SetCol(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));

}

//=============================================================================
// �|�C���g�̈ʒu�ݒ�
//=============================================================================
void CPoint::PointPostion(int nNumPlayer, int nID)
{
	// �l�����w�萔�� ���� �v���C���[ID���w�肵���ԍ��̏ꍇ
	if (nNumPlayer > 0 && nNumPlayer <= MAX_PLAYER && nID == 0)
	{	// 1�`4��� 1P�̈ʒu
		m_pos = POINT_POS_1P_ONE;
	}
	else if (nID == 1 && nNumPlayer == 1)
	{	// 1��� 2P�̏ꍇ
		m_pos = POINT_POS_2P_ONE;
	}
	else if (nID == 2 && nNumPlayer == 1)
	{	// 1��� 3P�̏ꍇ
		m_pos = POINT_POS_3P_ONE;
	}
	else if (nID == 3 && nNumPlayer == 1 || nID == 2 && nNumPlayer == 2 || nID == 1 && nNumPlayer == 3 || nID == 1 && nNumPlayer == 4)
	{	// 1��� 4P, 2��� 3P, 3��� 2P, 4��� 2P�̈ʒu
		m_pos = POINT_POS_4P_ONE;
	}
	else if (nID == 1 && nNumPlayer == 2 || nID == 2 && nNumPlayer == 3 || nID == 2 && nNumPlayer == 4)
	{ // 2��� 2P, 3��� 3P, 4��� 3P�̈ʒu
		m_pos = POINT_POS_2P_TWO;
	}
	else if (nID == 3 && nNumPlayer == 2 || nID == 3 && nNumPlayer == 3 || nID == 3 && nNumPlayer == 4)
	{	// 2��� 4P, 3��� 4P, 4��� 4P�̈ʒu
		m_pos = POINT_POS_4P_TWO;
	}
}