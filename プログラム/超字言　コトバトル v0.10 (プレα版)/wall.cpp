//=============================================================================
//
// �Ǐ��� [wall.cpp]
// Author : YUTARO ABE
//
//=============================================================================

//*****************************************************************************
// �w�b�_�t�@�C���̃C���N���[�h
//*****************************************************************************
#include "scene3D.h"		// �V�[��3D
#include "manager.h"		// �}�l�[�W���[
#include "renderer.h"		// �����_���[
#include "wall.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �ÓI�����o�ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWall::CWall() : CScene3D(4, CScene::OBJTYPE_WALL)
{
	m_nType = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCounter = 0;
	m_nAnimCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CWall::~CWall()
{
}

//=============================================================================
//	�A�C�e���̐���
//=============================================================================
CWall *CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType, int nTexType)
{
	CWall *pWall = {};

	if (pWall == NULL)
	{//	�A�C�e���̐���
		pWall = new CWall;
		if (pWall != NULL)
		{//�A�C�e���̏�����
			pWall->Init(pos, rot, size, col, TexUV, nType, nTexType);
		}
	}
	return pWall;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CWall::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, D3DXVECTOR2 TexUV, int nType, int nTexType)
{
	CScene3D::SetTexUV(TexUV);
	CScene3D::SetPos(pos);
	CScene3D::SetRot(rot);
	CScene3D::Init();
	CScene3D::SetColor(col);
	if (size.z > 0.1f)
	{
		CScene3D::SetSize(size.z, size.x);
	}
	else if (size.y > 0.1f) { CScene3D::SetSizeY(size.y, size.x); }
	m_nType = nTexType;
	if (nType == 0) { SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_NORMAL); }
	else { SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_BILLBOARD); }

	if (m_nType == 0) { CScene3D::BindTexture("FIELD"); }
	else if (m_nType == 1) { CScene3D::BindTexture("PAD"); }
	else if (m_nType == 2) { CScene3D::BindTexture("TUROFLOW000"); }
	else if (m_nType == 3) { CScene3D::BindTexture("TUROFLOW001"); }
	else if (m_nType == 4) { CScene3D::BindTexture("NEXT"); }
	else if (m_nType == 5) { CScene3D::BindTexture("FIELD002"); }
	else if (m_nType == 6) { CScene3D::BindTexture("FIELD002"); }
	else if (m_nType == 7) { CScene3D::BindTexture("FIELD002"); }


	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CWall::Uninit(void)
{
	CScene3D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CWall::Update(void)
{
	D3DXVECTOR3 WallPos = CScene3D::GetPos();		//	�ʒu�̎擾
	D3DXVECTOR3 WallRot = CScene3D::GetRot();		//	��]�̎擾
	float WallSizeY = CScene3D::GetSizeY();			//	���̎擾
	float WallSizeX = CScene3D::GetSizeX();			//	���̎擾

	if (m_nType == 4)
	{//	�{�^���@�\��
		m_nCounter++;
		if (m_nCounter < 60) { m_move.y = 0.3f; }
		else if (m_nCounter < 120) { m_move.y = -0.3f; }
		else if (m_nCounter == 120) { m_nCounter = 0; }
	}

	if (m_nType == 5)
	{//	��̗����
		m_nCounter++;
		if (m_nCounter > 3750)
		{
			Uninit();
		}
	}
	else if (m_nType == 6)
	{//	��̗����
		m_nCounter++;
		if (m_nCounter % 10 == 0)
		{
			m_nAnimCounter++;
			SetAnimation(m_nAnimCounter, 0.9f, 1.0f);
		}
		if (m_nCounter > 3750)
		{
			CWall::Create(D3DXVECTOR3(-200.0f, 5.0f, 0.0f), D3DXVECTOR3(D3DX_PI * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(40.0f, 400.0f, 0.0f),
				D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f), D3DXVECTOR2(5.0f, 5.0f), 0, 7);
			Uninit();
		}
	}

	WallPos += m_move;
	CScene3D::SetPos(WallPos);						//	�ʒu�̐ݒ�
	CScene3D::SetRot(WallRot);						//	��]�̐ݒ�
	CScene3D::SetSizeY(WallSizeY, WallSizeX);		//	�傫���̐ݒ�
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWall::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_nType == 6 || m_nType == 5)
	{//	��͗��ʉ�����
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O�Ȃ���
	}
	CScene3D::Draw();
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O�ɖ߂�

}
