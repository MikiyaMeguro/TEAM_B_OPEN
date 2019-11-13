//=============================================================================
//
// �o�H���̃r���{�[�h���� [waypoint.cpp]
// Author :�@�ڍ� ������
//
//=============================================================================
#include "waypoint.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "InputKeyboard.h"
#include "PlayerNumSelect.h"
#include "debugProc.h"

#include "sceneX.h"
#include "object.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CWaypoint::CWaypoint() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	nNumWayPoint = 0;
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CWaypoint::~CWaypoint()
{
}

//--------------------------------------------
// ����
//--------------------------------------------
CWaypoint *CWaypoint::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag)
{
	CWaypoint *pWaypoint = NULL;

	if (pWaypoint == NULL)
	{
		pWaypoint = new CWaypoint;

		if (pWaypoint != NULL)
		{
			//�l�̑��
			pWaypoint->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWaypoint->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			//�ݒ�
			pWaypoint->Init(pos);
			pWaypoint->BindTexture(Tag);
		}
	}

	return pWaypoint;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT CWaypoint::Init(D3DXVECTOR3 pos)
{
	//CSceneBillBoard::Init(pos);
	D3DXVECTOR3 InitPos(0, 0, 0);
	D3DXVECTOR3 SetPos(0, 0, 0);

	//������
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		WayPoint[nCntWayPoint].pWayPoint = NULL;
		WayPoint[nCntWayPoint].WayPointPos = D3DXVECTOR3(0, 0, 0);
		WayPoint[nCntWayPoint].bInPlayer = 0;
		WayPoint[nCntWayPoint].nWayPointNum = 9;
		WayPoint[nCntWayPoint].bInPlayer = false;
		WayPoint[nCntWayPoint].bBlock = false;
	}
	//����
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		SetPos = D3DXVECTOR3(-350.0f + InitPos.x, pos.y + InitPos.y, -350.0f + InitPos.z);

		WayPoint[nCntWayPoint].WayPointPos = SetPos;
		WayPoint[nCntWayPoint].pWayPoint = CSceneBillBoard::Create(SetPos, 0, 0, "NUMBER");
		WayPoint[nCntWayPoint].pWayPoint->Init(SetPos);
		WayPoint[nCntWayPoint].pWayPoint->SetBillboard(SetPos, m_size.x, m_size.y);
		WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
		//X�����ɂ��炷
		InitPos.x += 80;

		if (nCntWayPoint % SPLIT_WAYPOINT == SPLIT_WAYPOINT -1)
		{
			//X������߂�
			InitPos.x = 0;
			//Z�����ɂ��炷
			InitPos.z += 80;
		}
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWaypoint::Uninit(void)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].pWayPoint != NULL)
		{
			WayPoint[nCntWayPoint].pWayPoint->Uninit();
			WayPoint[nCntWayPoint].pWayPoint = NULL;
		}
	}
	CSceneBillBoard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWaypoint::Update(void)
{
	int nNowNumber = 0;		//������}�X�̔ԍ�
	int nAdjacent = 0;		//�אڂ��Ă���}�X�͉��}�X������Ă��邩
	bool bLand = false;		//�N�����}�X�ɏ���Ă���
	int nNum2Cnt = 0;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
		WayPoint[nCntWayPoint].nWayPointNum = 9;
	}

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].bInPlayer == true)
		{	//������}�X�̔ԍ�����
			nNowNumber = nCntWayPoint;
			WayPoint[nCntWayPoint].nWayPointNum = 0;
			WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
			bLand = true;
		}
	}

	//������}�X���牽�}�X������Ă��邩
	for (int nCntSplit = 1; nCntSplit < SPLIT_WAYPOINT + 3; nCntSplit++)
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			//����8�}�X
#if 1
			if (nNowNumber - 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
				|| nNowNumber + 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT + 1 == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT) % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT - 1 == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT + 1 == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT) % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT - 1 == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true)
			{//�אڂ���}�X
				WayPoint[nCntWayPoint].nWayPointNum = 1;
				WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
			}

			if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true)
			{//�אڃ}�X���痣��Ă���

				if ((nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
				{//�E���@�]�肪�o�Ȃ��}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
					WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if ((nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
				{//���� �]�肪������-1�̃}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
					WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if ((nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//�O ���������������Ƃ���0�ȉ��̎��͓���Ȃ�
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if ((nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//��� �ő吔�ȏ�̎��͓���Ȃ�
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}

				if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT - 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT + 1 && (nCntWayPoint - SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
				{	//�E�O	��(5*5�Œ����ɂ���ꍇ)�@12 - 8 == ������ + 1 && 0�ȏ� && �܂�Ԃ��Ă��Ȃ�
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nNowNumber - nCntWayPoint == (SPLIT_WAYPOINT + 1) * nCntSplit && 0 <= nCntWayPoint - SPLIT_WAYPOINT - 1 && (nCntWayPoint - SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT -1)
				{	//���O	��(5*5�Œ����ɂ���ꍇ)�@12 - 6 == ������ - 1 && 0�ȏ� && �܂�Ԃ��Ă��Ȃ�
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT + 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT + 1 && (nCntWayPoint + SPLIT_WAYPOINT + 1) % SPLIT_WAYPOINT != 0)
				{	//�E��	��(5*5�Œ����ɂ���ꍇ)�@18 - 12 == ������ + 1 && 25�ȓ� && �܂�Ԃ��Ă��Ȃ�
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - nNowNumber == (SPLIT_WAYPOINT - 1) * nCntSplit  && MAX_WAYPOINT > nCntWayPoint + SPLIT_WAYPOINT - 1 && (nCntWayPoint + SPLIT_WAYPOINT - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1)
				{	//����	��(5*5�Œ����ɂ���ꍇ)�@16 - 12 == ������ - 1 && 25�ȓ� && �܂�Ԃ��Ă��Ȃ�
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}

			}


#endif
			//���͂S�}�X
#if 0
			//�ǂ����̃}�X�ɏ�����Ƃ�
			if (nNowNumber - 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && bLand == true
				|| nNowNumber + 1 == nCntWayPoint && nCntWayPoint % SPLIT_WAYPOINT != 0 && bLand == true
				|| nNowNumber + SPLIT_WAYPOINT == nCntWayPoint && MAX_WAYPOINT > nNowNumber + SPLIT_WAYPOINT && bLand == true
				|| nNowNumber - SPLIT_WAYPOINT == nCntWayPoint && 0 <= nNowNumber - SPLIT_WAYPOINT && bLand == true)
			{//�אڂ���}�X
				WayPoint[nCntWayPoint].nWayPointNum = 1;
				WayPoint[nCntWayPoint].pWayPoint->SetTexture(2, 10, 1, 1);
			}

			if (WayPoint[nCntWayPoint].nWayPointNum == nCntSplit && bLand == true)
			{//�אڃ}�X���痣��Ă���
			 //�������̌��ߕ�
			 //��������P�}�X���ꂽ�}�X�̉E���O������ė���Ă���}�X��������
				if (nCntWayPoint + 1 && (nCntWayPoint + 1) % SPLIT_WAYPOINT != 0 && WayPoint[nCntWayPoint + 1].nWayPointNum > nCntSplit)
				{//�E���@�]�肪�o�Ȃ��}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
					WayPoint[nCntWayPoint + 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - 1 && (nCntWayPoint - 1) % SPLIT_WAYPOINT != SPLIT_WAYPOINT - 1 && WayPoint[nCntWayPoint - 1].nWayPointNum > nCntSplit)
				{//���� �]�肪������-1�̃}�X�͐܂�Ԃ��Ă���}�X�Ȃ̂Ō��Ȃ��悤�ɂ���
					WayPoint[nCntWayPoint - 1].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - 1].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint - SPLIT_WAYPOINT && (nCntWayPoint - SPLIT_WAYPOINT) >= 0 && WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//�O ���������������Ƃ���0�ȉ��̎��͓���Ȃ�
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint - SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
				if (nCntWayPoint + SPLIT_WAYPOINT && (nCntWayPoint + SPLIT_WAYPOINT) < MAX_WAYPOINT && WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum > nCntSplit)
				{//��� �ő吔�ȏ�̎��͓���Ȃ�
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].nWayPointNum = nCntSplit + 1;
					WayPoint[nCntWayPoint + SPLIT_WAYPOINT].pWayPoint->SetTexture(nCntSplit + 2, 10, 1, 1);
				}
			}
#endif
		}
	}

	//�u���b�N�ɓ������Ă���
	CollisionObj();

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_B))
	{
		for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
		{
			WayPoint[nCntWayPoint].pWayPoint->SetTexture(9, 10, 1, 1);
			WayPoint[nCntWayPoint].nWayPointNum = 9;
		}
	}

#ifdef _DEBUG

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].nWayPointNum == 1)
		{
		//	CDebugProc::Print("cfcfcf", "2�̃}�X�̈ʒu : X ", WayPoint[nCntWayPoint].WayPointPos.x, " Y ", WayPoint[nCntWayPoint].WayPointPos.y, " Z ", WayPoint[nCntWayPoint].WayPointPos.z);
			nNum2Cnt++;
		}
	}

///	CDebugProc::Print("cn", "�Q�̃}�X�̐� :", nNum2Cnt);
#endif

}

//=============================================================================
// �`�揈��
//=============================================================================
void CWaypoint::Draw(void)
{
	//CSceneBillBoard::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
D3DXVECTOR3 CWaypoint::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == false)
	{
		if (pos.y > 30.0f)
		{	// �ʒu���w�肵���ꏊ���傫���ꍇ
			m_bMoveFlag = true;
		}
	}
	else if (m_bMoveFlag == true)
	{
		if (pos.y < 0.0f + m_size.y)
		{	// �ʒu���w�肵���ꏊ��菬�����ꍇ
			m_bMoveFlag = false;
		}
	}

	return pos;
}

//=============================================================================
// �g��k���̏���
//=============================================================================
void CWaypoint::ScaleSize(void)
{
	if (m_bScaleFlag == false)
	{	// �g�傷��
		m_size.x += 0.2f;
		m_size.y += 0.2f;
		if (m_size.x > 15.0f && m_size.y > 15.0f)
		{	// �k������t���O��
			m_bScaleFlag = true;
		}
	}
	else if (m_bScaleFlag == true)
	{	// �k������
		m_size.x -= 0.2f;
		m_size.y -= 0.2f;
		if (m_size.x < m_sizeOld.x && m_size.y < m_sizeOld.y)
		{	// �g�傷��t���O��
			m_bScaleFlag = false;
		}
	}
}

//=============================================================================
// �͈͓��̏���
//=============================================================================
void CWaypoint::InRange(D3DXVECTOR3 pos)
{
	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (pos.z <= WayPoint[nCntWayPoint].WayPointPos.z + WAYPOINT_HIT && pos.z >= WayPoint[nCntWayPoint].WayPointPos.z - WAYPOINT_HIT)
		{// z�͈̔͂̒�
			if (pos.x <= WayPoint[nCntWayPoint].WayPointPos.x + WAYPOINT_HIT && pos.x >= WayPoint[nCntWayPoint].WayPointPos.x - WAYPOINT_HIT)
			{// x�͈̔͂̒�
				//�v���C���[������Ă���
				WayPoint[nCntWayPoint].pWayPoint->SetTexture(1, 10, 1, 1);
				WayPoint[nCntWayPoint].bInPlayer = true;
				WayPoint[nCntWayPoint].nWayPointNum = 0;
			}
			else
			{
				WayPoint[nCntWayPoint].bInPlayer = false;
			}
		}
		else
		{
			WayPoint[nCntWayPoint].bInPlayer = false;
		}
	}
}

//=============================================================================
// �ړ��\�Ȉʒu��Ԃ�����
//=============================================================================
D3DXVECTOR3 &CWaypoint::ReturnPointMove(void)
{
	//int nCnt = 0;
	nNumWayPoint = 0;

	for (int nCntWP = 0; nCntWP < 8; nCntWP++)
	{
		//m_pWayPointPos[nCntWP] = NULL;
		m_pWayPointPos[nCntWP] = D3DXVECTOR3(0, 0, 0);
	}

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		if (WayPoint[nCntWayPoint].nWayPointNum == 1)
		{
			m_pWayPointPos[nNumWayPoint] = WayPoint[nCntWayPoint].WayPointPos;
			nNumWayPoint++;
		}
	}
	return m_pWayPointPos[0];
}

//=============================================================================
// �ړ��\�Ȑ���Ԃ�����
//=============================================================================
int CWaypoint::CntWayPoint(void)
{
	return nNumWayPoint;
}

//=============================================================================
// �I�u�W�F�N�g���菈��
//=============================================================================
void CWaypoint::CollisionObj(void)
{
	CScene *pScene = NULL;

	for (int nCntWayPoint = 0; nCntWayPoint < MAX_WAYPOINT; nCntWayPoint++)
	{
		// �擪�̃I�u�W�F�N�g���擾
		pScene = CScene::GetTop(SCENEX_PRIORITY);

		while (pScene != NULL)
		{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
		 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
			CScene *pSceneNext = pScene->GetNext();
			if (pScene->GetDeath() == false && pScene->GetObjType() == CScene::OBJTYPE_SCENEX)
			{// ���S�t���O�������Ă��Ȃ�����
			 // �I�u�W�F�N�g�̎�ނ��m���߂�
				CSceneX *pSceneX = ((CSceneX*)pScene);		// CSceneX�փL���X�g(�^�̕ύX)
				if (pSceneX->GetCollsionType() != CSceneX::COLLISIONTYPE_NONE)
				{
					bool  bLand = pSceneX->CollisionIN(WayPoint[nCntWayPoint].WayPointPos, D3DXVECTOR3(40, 0, 40));
					CObject *pSceneObj = ((CObject*)pSceneX);

					//�I�u�W�F�N�g�ɓ�������
					if (bLand == true)
					{
						WayPoint[nCntWayPoint].bBlock = true;
						WayPoint[nCntWayPoint].nWayPointNum = 9;
					}
				}
			}
			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}
}
