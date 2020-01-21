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
	D3DXVECTOR3 pos = CSceneBillBoard::GetPos();	//�ʒu�̎擾
	D3DXVECTOR3 PosOld = pos;						// �ʒu��ۑ�
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);// �ړ�

	if (m_bPopFlag == false)
	{	// �o�����̏ꍇ
		move.y += 1.0f;
		m_size.x += 1.0f;
		m_size.y += 1.0f;
		if (m_size.x > MAX_SIZE.x) { m_size.x = MAX_SIZE.x; }
		if (m_size.y > MAX_SIZE.y) { m_size.y = MAX_SIZE.y; }
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
						pPlayer[nCntPlayer]->GetWordManager()->SetWord(m_nWordNum);
						pPlayer[nCntPlayer]->SetbSetupBullet(true);
						m_nNumPlayerGet = nCntPlayer;				// �v���C���[�ԍ����擾
						move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						m_size = D3DXVECTOR3(6.0f, 6.0f, 0.0f);
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
			if (pPlayer[m_nNumPlayerGet] == NULL)
			{
				pPlayer[m_nNumPlayerGet] = CGame::GetPlayer(m_nNumPlayerGet);	// �v���C���[���擾
				float fPlayer = pPlayer[m_nNumPlayerGet]->GetRotation().y;

				//pos = D3DXVECTOR3(sinf(fPlayer + (D3DX_PI)) + (pPlayer[m_nNumPlayerGet]->GetPosition().x + 10.0f), 40.0f, pPlayer[m_nNumPlayerGet]->GetPosition().z);
				pos = D3DXVECTOR3(pPlayer[m_nNumPlayerGet]->GetPosition().x, 50.0f, pPlayer[m_nNumPlayerGet]->GetPosition().z);
			}

			m_nCntUninit++;	// �J�E���g�̉��Z

			if ((m_nCntUninit % UNITI_TIME) == 0)
			{	// ���ԂɂȂ�����I������
				//Uninit();
				m_bFlagUninit = true;
				//return;
			}
		}

		if ((CTime::GetStageTime() % 30) == 0)
		{
			m_bFlagUninit = true;
		}
	}


	//ScaleSize();

	// �ʒu�X�V
	pos.x += move.x;
	pos.y += move.y;
	pos.z += move.z;

	CSceneBillBoard::Update();
	CSceneBillBoard::SetBillboard(pos, m_size.x, m_size.y);
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWord::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CSceneBillBoard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �ړ�����
//=============================================================================
D3DXVECTOR3 CWord::Move(D3DXVECTOR3 pos)
{
	if (m_bMoveFlag == true)
	{
		pos.y += FLOATING_MOVE;
		if (pos.y > POP_POS_Y)
		{	// �ʒu���w�肵���ꏊ���傫���ꍇ
			m_bMoveFlag = false;
		}
	}
	else if (m_bMoveFlag == false)
	{
		pos.y -= FLOATING_MOVE;
		if (pos.y < POP_POS_Y_SMALL)
		{	// �ʒu���w�肵���ꏊ��菬�����ꍇ
			m_bMoveFlag = true;
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
