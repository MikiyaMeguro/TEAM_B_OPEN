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
LPDIRECT3DTEXTURE9 CWall::m_pTexture[MAX_WALL_TEX] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CWall::CWall() : CScene3D(4, CScene::OBJTYPE_WALL)
{
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
	CScene3D::SetSizeY(size.y, size.x);
	if (nType == 0){SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_NORMAL);}
	else{SetInitAll(pos, rot, size, col, TexUV, SCENE3DTYPE_BILLBOARD); }

	if (nTexType == 0){CScene3D::BindTexture("FIELD");}
	else if (nTexType == 1){CScene3D::BindTexture("PAD");}
	else if (nTexType == 2) { CScene3D::BindTexture("TUROFLOW"); }


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

	CScene3D::SetPos(WallPos);						//	�ʒu�̐ݒ�
	CScene3D::SetRot(WallRot);						//	��]�̐ݒ�
	CScene3D::SetSizeY(WallSizeY, WallSizeX);		//	�傫���̐ݒ�

	CScene3D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CWall::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// �J�����O�Ȃ���
	CScene3D::Draw();
	//pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O�ɖ߂�

}
