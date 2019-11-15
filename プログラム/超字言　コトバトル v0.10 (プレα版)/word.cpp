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
#include "time.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define AREA_CHASE		(40.0f)			// �G���A
#define AREA_COILLSION	(15.0f)			// �R���W�����͈̔�
#define CHASE_MOVE		(4.0f)			// �Ǐ]���̑��x
#define END_POS_Y		(15.0f)			// �����̏o���������̍ŏI�ʒu
#define FLOATING_MOVE	(0.5f)			// ���V���x
#define POP_POS_Y		(END_POS_Y + 10.0f)	// �o����̕��V���̍ő�ʒu
#define POP_POS_Y_SMALL		(END_POS_Y - 5.0f)	// �o����̕��V���̍ŏ��ʒu
#define MAX_SIZE		(D3DXVECTOR2(12.0f, 12.0f))	// �T�C�Y�̍ő�l

#define UNITI_TIME		(40)			// �I�����鎞��
#define ��_COL_TIME		(15)			// �����x�ω����̎���
#define ANIM_FRAME		(7)				// �A�j���[�V�����J�E���^�[
#define PATTERN_NUM		(10)			// �p�^�[����
//--------------------------------------------
// �R���X�g���N�^
//--------------------------------------------
CWord::CWord() : CSceneBillBoard()
{
	m_bFlagUninit = false;
	m_bMoveFlag = false;
	m_bScaleFlag = false;
	m_nNumPlayerGet = 0;
	m_nCntUninit = 0;
	m_bFlag = false;
	m_bPopFlag = false;
	m_fMoveY = 0.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_pBillBoard = NULL;
	m_nAnim = 0;
	m_nPatten = 0;
	m_colA = 0.4f;
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
CWord *CWord::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, LPCSTR Tag, int nWord, int nNum)
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
			pWord->m_nNum = nNum;
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

	if (m_pBillBoard == NULL)
	{
		m_pBillBoard = CSceneBillBoard::Create(D3DXVECTOR3(pos.x, 0.0f, pos.z), 20.0f, 30.0f, "�����G�t�F�N�g");
		if (m_pBillBoard != NULL) { m_pBillBoard->SetTexture(5, 10, 1, 1); }
		m_pBillBoard->SetObjType(CScene::OBJTYPE_WORD_EFFECT);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWord::Uninit(void)
{
	if (m_pBillBoard != NULL) { m_pBillBoard->Uninit(); m_pBillBoard = NULL; }
	CSceneBillBoard::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWord::Update(void)
{
	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//�ʒu�̎擾
	D3DXVECTOR3 PosOld = pos;						// �ʒu��ۑ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ړ�

	if (m_bPopFlag == false)
	{	// �o�����̏ꍇ
		move.y += 1.0f;
		SizeScale(&m_size, 1.0f, MAX_SIZE);
		if (pos.y >= END_POS_Y) { m_bPopFlag = true; }
	}
	else if (m_bPopFlag == true)
	{
		if (m_bFlagUninit == true) { return; }
		// ���[�J���ϐ�
		//CPlayerSelect::SELECTPLAYER NumPlayer = *CPlayerSelect::GetModeSelectMode();
		CPlayerSelect::SELECTPLAYER NumPlayer = CPlayerSelect::SELECTPLAYER_4P;//�e�X�g

		CPlayer *pPlayer[MAX_PLAYER] = {};
		D3DXVECTOR3 PlayerPos[MAX_PLAYER];

		if (m_bFlag == false)
		{	// �E�����Ƃ��\�ȕ����̏ꍇ
			for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
			{
				pPlayer[nCntPlayer] = CGame::GetPlayer(nCntPlayer);			// �v���C���[���擾
				PlayerPos[nCntPlayer] = pPlayer[nCntPlayer]->GetPosition();	// �v���C���[�̈ʒu���擾
			}

			for (int nCntPlayer = 0; nCntPlayer < (int)NumPlayer; nCntPlayer++)
			{
				if (pPlayer[nCntPlayer]->GetWordManager()->GetCntNum() < 3)
				{

					Distance(pos, PlayerPos[nCntPlayer], nCntPlayer);

					// �����蔻��(�~���g��������)
					Circle(pos, PlayerPos[nCntPlayer], AREA_COILLSION);

					if (m_bFlag == true)
					{	// �I���t���O���������ꍇ
						if (m_pBillBoard != NULL) { m_pBillBoard->Uninit(); m_pBillBoard = NULL; }
						pPlayer[nCntPlayer]->GetWordManager()->SetWord(m_nWordNum);
						pPlayer[nCntPlayer]->SetbSetupBullet(true);
						m_nNumPlayerGet = nCntPlayer;				// �v���C���[�ԍ����擾
						move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						break;
					}
				}
				else
				{	// 3���������Ȃ�
					Distance(pos, D3DXVECTOR3(9999999990.0f, 0.0f, 9999999990.0f), nCntPlayer);
				}
			}

			if (m_bFlag == false)
			{	// �I���t���O�������Ă���ꍇ
				int nNum = ComparisonDistance((int)NumPlayer);

				// �������v���C���[�ɏW�܂�(�͈͂Ŕ�������)
				move = Approach(pos, PlayerPos[nNum], AREA_CHASE, m_fDistance[nNum]);
			}

			pos = Move(pos);
		}

		if (m_bFlag == true)
		{	// �擾��̉��o�̏ꍇ
			m_fMoveY += 0.2f;
			SizeScale(&m_size, 0.5f, D3DXVECTOR2(6.0f, 6.0f));

			if (pPlayer[m_nNumPlayerGet] == NULL)
			{
				pPlayer[m_nNumPlayerGet] = CGame::GetPlayer(m_nNumPlayerGet);	// �v���C���[���擾
				float fPlayer = pPlayer[m_nNumPlayerGet]->GetRotation().y;

				//pos = D3DXVECTOR3(sinf(fPlayer + (D3DX_PI)) + (pPlayer[m_nNumPlayerGet]->GetPosition().x + 10.0f), 40.0f, pPlayer[m_nNumPlayerGet]->GetPosition().z);
				pos = D3DXVECTOR3(pPlayer[m_nNumPlayerGet]->GetPosition().x, 50.0f + m_fMoveY, pPlayer[m_nNumPlayerGet]->GetPosition().z);
			}

			m_nCntUninit++;	// �J�E���g�̉��Z

			// �����x�̕ω�
			if (m_nCntUninit > ��_COL_TIME)
			{
				m_col.a -= 0.01f;
			}

			if ((m_nCntUninit % UNITI_TIME) == 0)
			{	// ���ԂɂȂ�����I������
				//Uninit();
				m_bFlagUninit = true;
				//return;
			}
		}

		if (((CTime::GetStageTime() % 60) == 0) && CManager::GetGame()->GetChangeNum() < 2)
		{
			Uninit();
			return;
		}
	}

	// �ʒu�X�V
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;

	CSceneBillBoard::Update();
	CSceneBillBoard::SetBillboard(pos, m_size.x, m_size.y);
	CSceneBillBoard::SetCol(m_col);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWord::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_pBillBoard != NULL) { m_pBillBoard->Draw(); }
	
	CSceneBillBoard::Draw();
}

//=============================================================================
// �ړ�����
//=============================================================================
D3DXVECTOR3 CWord::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == true)
	{
		pos.y += FLOATING_MOVE;
		m_colA += 0.01f;
		if (m_colA > 1.0f) { m_colA = 1.0f; }
		if (pos.y > POP_POS_Y)
		{	// �ʒu���w�肵���ꏊ���傫���ꍇ
			m_bMoveFlag = false;
			//m_colA = 1.0f;
		}
	}
	else if (m_bMoveFlag == false)
	{
		pos.y -= FLOATING_MOVE;
		m_colA -= 0.01f;
		if (m_colA < 0.38f) { m_colA = 0.38f; }
		if (pos.y < POP_POS_Y_SMALL)
		{	// �ʒu���w�肵���ꏊ��菬�����ꍇ
			m_bMoveFlag = true;
			//m_colA = 0.2f;
		}
	}

	if (m_pBillBoard != NULL) { m_pBillBoard->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_colA)); }

	return pos;
}

//=============================================================================
// �g��k���̏���
//=============================================================================
void CWord::SizeScale(D3DXVECTOR3 *size, float fMove, D3DXVECTOR2 MaxSize)
{
	size->x += fMove;
	size->y += fMove;

	if (fMove >= 0)
	{	// 0�ȏ�̏ꍇ
		if (size->x > MaxSize.x) { size->x = MaxSize.x; }
		if (size->y > MaxSize.y) { size->y = MaxSize.y; }
	}
	else if (fMove < 0)
	{	// 0�ȉ��̏ꍇ
		if (size->x < MaxSize.x) { size->x = MaxSize.x; }
		if (size->y < MaxSize.y) { size->y = MaxSize.y; }
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

	if (fDistance < fAngle) { m_bFlag = true; }
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
