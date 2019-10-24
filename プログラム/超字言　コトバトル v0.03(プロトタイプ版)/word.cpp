//=============================================================================
//
// �����̃r���{�[�h���� [word.cpp]
// Author : Shun Yokomichi
//
//=============================================================================
#include "word.h"
#include "manager.h"
#include "game.h"
#include "player.h"
#include "InputKeyboard.h"
#include "PlayerNumSelect.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AREA_CHASE		(40.0f)			// �G���A
#define AREA_COILLSION	(5.0f)			// �R���W�����͈̔�
#define CHASE_MOVE		(1.0f)			// �Ǐ]���̑��x
//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CWord::CWord() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nNumPlayerGet = 0;
}

//--------------------------------------------
// �f�X�g���N�^
//--------------------------------------------
CWord::~CWord()
{
}

//--------------------------------------------
// ����
//--------------------------------------------
CWord *CWord::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord)
{
	CWord *pWord = NULL;

	if (pWord == NULL)
	{
		pWord = new CWord;

		if (pWord != NULL)
		{
			pWord->Init(pos);
			pWord->BindTexture(Tag);
			//�l�̑��
			pWord->SetBillboard(pos, fHeight, fWidth);
			pWord->m_size = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_sizeOld = D3DXVECTOR3(fHeight, fWidth, 0.0f);
			pWord->m_nWordNum = nWord;
			pWord->SetTexture(nWord, 10, 5, 1);
		}
	}

	return pWord;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWord::Init(D3DXVECTOR3 pos)
{
	CSceneBillBoard::Init(pos);
	CSceneBillBoard::SetObjType(CScene::OBJTYPE_WORD);
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWord::Uninit(void)
{
	CSceneBillBoard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWord::Update(void)
{
	// ���[�J���ϐ�
	CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
	//CPlayerSelect::SELECTPLAYER NumPlayer = CPlayerSelect::SELECTPLAYER_1P;//�e�X�g

	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//�ʒu�̎擾
	D3DXVECTOR3 PosOld = pos;						// �ʒu��ۑ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);// �ړ�
	CPlayer *pPlayer[MAX_PLAYER] = {};
	D3DXVECTOR3 PlayerPos[MAX_PLAYER];

	for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);			// �v���C���[���擾
		PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// �v���C���[�̈ʒu���擾
	}

	//pos = Move(pos);

	for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
	{
		if (pPlayer[nCntPlayer]->GetWordManager()->GetCntNum() < 3)
		{	// 3���������Ȃ�

			Distance(pos, PlayerPos[nCntPlayer], nCntPlayer);

			// �����蔻��(�~���g��������)
			Circle(pos, PlayerPos[nCntPlayer], AREA_COILLSION);

			if (m_bFlagUninit == true)
			{	// �I���t���O���������ꍇ
				pPlayer[nCntPlayer]->GetWordManager()->SetWord(m_nWordNum);
				Uninit();
				return;
			}
		}
		else
		{
			Distance(pos,D3DXVECTOR3(9999999990.0f, 0.0f, 9999999990.0f), nCntPlayer);
		}
	}

	int nNum = ComparisonDistance((int)NumPlayer);

	// �������v���C���[�ɏW�܂�(�͈͂Ŕ�������)
	move = Approach(pos, PlayerPos[nNum], AREA_CHASE, m_fDistance[nNum]);

	//ScaleSize();

	// �ʒu�X�V
	pos.x += move.x;
	//if (m_bMoveFlag == false) { pos.y += move.y; }
	//if (m_bMoveFlag == true) { pos.y -= move.y; }
	pos.z += move.z;

	CSceneBillBoard::Update();
	CSceneBillBoard::SetBillboard(pos, m_size.x, m_size.y);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWord::Draw(void)
{
	CSceneBillBoard::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
D3DXVECTOR3 CWord::Move(D3DXVECTOR3 pos)
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
void CWord::ScaleSize(void)
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
// �v���C���[�ƕ����r���{�[�h�Ƃ̋����𑪂鏈��
//=============================================================================
void CWord::Distance(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, int nNumPlayer)
{
	// �����𑪂�
	m_fDistance[nNumPlayer] = ((Pos.x - OtherPos.x) * (Pos.x - OtherPos.x)) + ((Pos.z - OtherPos.z) * (Pos.z - OtherPos.z));
}

//=============================================================================
// ���������������Ɉ�ԋ߂�������I�ԏ���
//=============================================================================
int CWord::ComparisonDistance(int nNum)
{
	int nNumPlayer = 0;

	for (int nCntPlayer = 0; nCntPlayer < (int)nNum - 1; nCntPlayer++)
	{
		if (m_fDistance[nCntPlayer] > m_fDistance[nCntPlayer + 1])
		{	// ���l����
			nNumPlayer = nCntPlayer + 1;
		}
	}

	return nNumPlayer;
}


//=============================================================================
// �͈͂̏���
//=============================================================================
void CWord::Circle(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle)
{
	float fDistance = sqrtf((Pos.x - OtherPos.x)* (Pos.x - OtherPos.x) + (Pos.z - OtherPos.z)*(Pos.z - OtherPos.z));

	if (fDistance < fAngle) { m_bFlagUninit = true; }
}

//=============================================================================
// �v���C���[�ɏW�܂�̏���
//=============================================================================
D3DXVECTOR3 CWord::Approach(D3DXVECTOR3 Pos, D3DXVECTOR3 OtherPos, float fAngle, float fDistance)
{
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f,0.0f);

	if (fDistance < fAngle * fAngle)
	{	// �������ɓ�������
		// �v���C���[�ɋ߂Â���
		move.x = sinf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
		move.z = cosf(atan2f(OtherPos.x - Pos.x, OtherPos.z - Pos.z)) * CHASE_MOVE;
	}

	return move;
}
